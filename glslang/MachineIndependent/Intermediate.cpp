//
//Copyright (C) 2002-2005  3Dlabs Inc. Ltd.
//Copyright (C) 2012-2013 LunarG, Inc.
//
//All rights reserved.
//
//Redistribution and use in source and binary forms, with or without
//modification, are permitted provided that the following conditions
//are met:
//
//    Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//    Redistributions in binary form must reproduce the above
//    copyright notice, this list of conditions and the following
//    disclaimer in the documentation and/or other materials provided
//    with the distribution.
//
//    Neither the name of 3Dlabs Inc. Ltd. nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
//THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
//FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
//COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
//INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
//BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
//CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
//ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
//POSSIBILITY OF SUCH DAMAGE.
//

//
// Build the intermediate representation.
//

#include "localintermediate.h"
#include "QualifierAlive.h"
#include "RemoveTree.h"
#include <float.h>

////////////////////////////////////////////////////////////////////////////
//
// First set of functions are to help build the intermediate representation.
// These functions are not member functions of the nodes.
// They are called from parser productions.
//
/////////////////////////////////////////////////////////////////////////////

//
// Add a terminal node for an identifier in an expression.
//
// Returns the added node.
//
TIntermSymbol* TIntermediate::addSymbol(int id, const TString& name, const TType& type, TSourceLoc line)
{
    TIntermSymbol* node = new TIntermSymbol(id, name, type);
    node->setLine(line);

    return node;
}

//
// Connect two nodes with a new parent that does a binary operation on the nodes.
//
// Returns the added node.
//
TIntermTyped* TIntermediate::addBinaryMath(TOperator op, TIntermTyped* left, TIntermTyped* right, TSourceLoc line)
{
    if (left->getType().getBasicType() == EbtBlock || right->getType().getBasicType() == EbtBlock)
        return 0;

    switch (op) {
    case EOpLessThan:
    case EOpGreaterThan:
    case EOpLessThanEqual:
    case EOpGreaterThanEqual:
        if (left->getType().isMatrix() || left->getType().isArray() || left->getType().isVector() || left->getType().getBasicType() == EbtStruct) {
            return 0;
        }
        break;
    case EOpLogicalOr:
    case EOpLogicalXor:
    case EOpLogicalAnd:
        if (left->getType().getBasicType() != EbtBool || left->getType().isMatrix() || left->getType().isArray() || left->getType().isVector()) {
            return 0;
        }
        break;
    case EOpAdd:
    case EOpSub:
    case EOpDiv:
    case EOpMul:
        if (left->getType().getBasicType() == EbtStruct || left->getType().getBasicType() == EbtBool || left->getType().isArray())
            return 0;
    default: break; // some compilers want this
    }

    // 
    // First try converting the children to compatible types.
    //
    TIntermTyped* child = addConversion(op, left->getType(), right);
    if (child)
        right = child;
    else {
        child = addConversion(op, right->getType(), left);
        if (child)
            left = child;
        else
            return 0;
    }
    
    //
    // Need a new node holding things together then.  Make
    // one and promote it to the right type.
    //
    TIntermBinary* node = new TIntermBinary(op);
    if (line == 0)
        line = right->getLine();
    node->setLine(line);

    node->setLeft(left);
    node->setRight(right);
    if (! node->promote(infoSink))
        return 0;
        
    //
    // If they are both constants, they must be folded.
    //

    TIntermConstantUnion *leftTempConstant = left->getAsConstantUnion();
    TIntermConstantUnion *rightTempConstant = right->getAsConstantUnion();
    if (leftTempConstant && rightTempConstant) {
        TIntermTyped* folded = leftTempConstant->fold(node->getOp(), rightTempConstant, infoSink);
        if (folded)
            return folded;
        else
            infoSink.info.message(EPrefixInternalError, "Constant folding failed", line);
    }

    return node;
}

//
// Connect two nodes through an assignment.
//
// Returns the added node.
//
TIntermTyped* TIntermediate::addAssign(TOperator op, TIntermTyped* left, TIntermTyped* right, TSourceLoc line)
{
    //
    // Like adding binary math, except the conversion can only go
    // from right to left.
    //
    TIntermBinary* node = new TIntermBinary(op);
    if (line == 0)
        line = left->getLine();
    node->setLine(line);

    TIntermTyped* child = addConversion(op, left->getType(), right);
    if (child == 0)
        return 0;

    node->setLeft(left);
    node->setRight(child);
    if (! node->promote(infoSink))
        return 0;

    return node;
}

//
// Connect two nodes through an index operator, where the left node is the base
// of an array or struct, and the right node is a direct or indirect offset.
//
// Returns the added node.
// The caller should set the type of the returned node.
//
TIntermTyped* TIntermediate::addIndex(TOperator op, TIntermTyped* base, TIntermTyped* index, TSourceLoc line)
{
    TIntermBinary* node = new TIntermBinary(op);
    if (line == 0)
        line = index->getLine();
    node->setLine(line);
    node->setLeft(base);
    node->setRight(index);

    // caller should set the type

    return node;
}

//
// Add one node as the parent of another that it operates on.
//
// Returns the added node.
//
TIntermTyped* TIntermediate::addUnaryMath(TOperator op, TIntermNode* childNode, TSourceLoc line)
{
    TIntermTyped* child = childNode->getAsTyped();

    if (child->getType().getBasicType() == EbtBlock)
        return 0;

    if (child == 0) {
        infoSink.info.message(EPrefixInternalError, "Bad type in AddUnaryMath", line);
        return 0;
    }

    switch (op) {
    case EOpLogicalNot:
        if (child->getType().getBasicType() != EbtBool || child->getType().isMatrix() || child->getType().isArray() || child->getType().isVector()) {
            return 0;
        }
        break;

    case EOpPostIncrement:
    case EOpPreIncrement:
    case EOpPostDecrement:
    case EOpPreDecrement:
    case EOpNegative:
        if (child->getType().getBasicType() == EbtStruct || child->getType().isArray())
            return 0;
    default: break; // some compilers want this
    }

    //
    // Do we need to promote the operand?
    //
    TBasicType newType = EbtVoid;
    switch (op) {
    case EOpConstructInt:    newType = EbtInt;    break;
    case EOpConstructUint:   newType = EbtUint;   break;
    case EOpConstructBool:   newType = EbtBool;   break;
    case EOpConstructFloat:  newType = EbtFloat;  break;
    case EOpConstructDouble: newType = EbtDouble; break;
    default: break; // some compilers want this
    }

    if (newType != EbtVoid) {
        child = addConversion(op, TType(newType, EvqTemporary, child->getVectorSize(),
                                                               child->getMatrixCols(),
                                                               child->getMatrixRows()),
                              child);
        if (child == 0)
            return 0;
    }

    //
    // For constructors, we are now done, it was all in the conversion.
    //
    switch (op) {
    case EOpConstructInt:
    case EOpConstructUint:
    case EOpConstructBool:
    case EOpConstructFloat:
    case EOpConstructDouble:
        return child;
    default: break; // some compilers want this
    }

    //
    // Make a new node for the operator.
    //
    TIntermUnary* node = new TIntermUnary(op);
    if (line == 0)
        line = child->getLine();
    node->setLine(line);
    node->setOperand(child);
    
    if (! node->promote(infoSink))
        return 0;

    if (child->getAsConstantUnion())
        return child->getAsConstantUnion()->fold(op, node->getType(), infoSink);

    return node;
}

TIntermTyped* TIntermediate::addBuiltInFunctionCall(TOperator op, bool unary, TIntermNode* childNode, const TType& returnType)
{
    if (unary) {
        //
        // Treat it like a unary operator.
        // addUnaryMath() should get the type correct on its own;
        // including constness (which would differ from the prototype).
        //        
        TIntermTyped* child = childNode->getAsTyped();
        if (child == 0) {
            infoSink.info.message(EPrefixInternalError, "Bad type in AddUnaryMath", child->getLine());

            return 0;
        }

        if (child->getAsConstantUnion())

            return child->getAsConstantUnion()->fold(op, returnType, infoSink);

        TIntermUnary* node = new TIntermUnary(op);
        node->setLine(child->getLine());
        node->setOperand(child);
        node->setType(returnType);

        // propagate precision up from child
        if (returnType.getQualifier().precision == EpqNone && profile == EEsProfile)
            node->getQualifier().precision = child->getQualifier().precision;

        // propagate precision down to child
        if (node->getQualifier().precision != EpqNone &&
            child->getQualifier().precision == EpqNone)
            child->getQualifier().precision = node->getQualifier().precision;

        return node;
    } else {
        // setAggregateOperater() calls fold() for constant folding
        TIntermTyped* node = setAggregateOperator(childNode, op, returnType, childNode->getLine());

        if (returnType.getQualifier().precision == EpqNone && profile == EEsProfile) {
            // get maximum precision from arguments, for the built-in's return precision

            TIntermSequence& sequence = node->getAsAggregate()->getSequence();
            TPrecisionQualifier maxPq = EpqNone;
            for (unsigned int arg = 0; arg < sequence.size(); ++arg)
                maxPq = std::max(maxPq, sequence[arg]->getAsTyped()->getQualifier().precision);
            node->getQualifier().precision = maxPq;
        }

        if (node->getQualifier().precision != EpqNone) {
            TIntermSequence& sequence = node->getAsAggregate()->getSequence();
            for (unsigned int arg = 0; arg < sequence.size(); ++arg)
                if (sequence[arg]->getAsTyped()->getQualifier().precision == EpqNone)
                    sequence[arg]->getAsTyped()->getQualifier().precision = node->getQualifier().precision;
        }

        return node;
    }
}

//
// This is the safe way to change the operator on an aggregate, as it
// does lots of error checking and fixing.  Especially for establishing
// a function call's operation on it's set of parameters.  Sequences
// of instructions are also aggregates, but they just direnctly set
// their operator to EOpSequence.
//
// Returns an aggregate node, which could be the one passed in if
// it was already an aggregate.
//
TIntermTyped* TIntermediate::setAggregateOperator(TIntermNode* node, TOperator op, const TType& type, TSourceLoc line)
{
    TIntermAggregate* aggNode;

    //
    // Make sure we have an aggregate.  If not turn it into one.
    //
    if (node) {
        aggNode = node->getAsAggregate();
        if (aggNode == 0 || aggNode->getOp() != EOpNull) {
            //
            // Make an aggregate containing this node.
            //
            aggNode = new TIntermAggregate();
            aggNode->getSequence().push_back(node);
            if (line == 0)
                line = node->getLine();
        }
    } else
        aggNode = new TIntermAggregate();

    //
    // Set the operator.
    //
    aggNode->setOperator(op);
    if (line != 0)
        aggNode->setLine(line);

    aggNode->setType(type);

    return fold(aggNode);
}

//
// Convert one type to another.
//
// Returns the node representing the conversion, which could be the same
// node passed in if no conversion was needed.
//
// Return 0 if a conversion can't be done.
//
TIntermTyped* TIntermediate::addConversion(TOperator op, const TType& type, TIntermTyped* node)
{
    //
    // Does the base type allow operation?
    //
    switch (node->getBasicType()) {
    case EbtVoid:
    case EbtSampler:
        return 0;
    default: break;
    }

    //
    // Otherwise, if types are identical, no problem
    //
    if (type == node->getType())
        return node;

    //
    // If one's a structure, then no conversions.
    //
    if (type.getStruct() || node->getType().getStruct())
        return 0;

    //
    // If one's an array, then no conversions.
    //
    if (type.isArray() || node->getType().isArray())
        return 0;

    // Note: callers are responsible for other aspects of shape, 
    // like vector and matrix sizes.

    TBasicType promoteTo;
    
    switch (op) {
    //
    // Explicit conversions (unary operations)
    //
    case EOpConstructBool:
        promoteTo = EbtBool;
        break;
    case EOpConstructFloat:
        promoteTo = EbtFloat;
        break;
    case EOpConstructInt:
        promoteTo = EbtInt;
        break;
    case EOpConstructUint:
        promoteTo = EbtUint;
        break;

    //
    // List all the binary ops that can implicitly convert one operand to the other's type;
    // This implements the 'policy' for implicit type conversion.
    // 
    case EOpLessThan:
    case EOpGreaterThan:
    case EOpLessThanEqual:
    case EOpGreaterThanEqual:
    case EOpEqual:
    case EOpNotEqual:

    case EOpAdd:
    case EOpSub:
    case EOpMul:
    case EOpDiv:

    case EOpVectorTimesScalar:
    case EOpVectorTimesMatrix:
    case EOpMatrixTimesVector:
    case EOpMatrixTimesScalar:

    case EOpAssign:
    case EOpAddAssign:
    case EOpSubAssign:
    case EOpMulAssign:
    case EOpVectorTimesScalarAssign:
    case EOpMatrixTimesScalarAssign:
    case EOpDivAssign:
    case EOpModAssign:

    case EOpSequence:
    case EOpConstructStruct:

        if (type.getBasicType() == node->getType().getBasicType())
            return node;

        if (canImplicitlyPromote(node->getType().getBasicType(), type.getBasicType()))
            promoteTo = type.getBasicType();
        else
            return 0;

        break;

    // Shifts can have mixed types as long as they are integer, without converting.
    // It's the left operand's type that determines the resulting type, so no issue
    // with assign shift ops either.
    case EOpLeftShift:
    case EOpRightShift:
    case EOpLeftShiftAssign:
    case EOpRightShiftAssign:
        if ((type.getBasicType() == EbtInt || 
             type.getBasicType() == EbtUint) &&
            (node->getType().getBasicType() == EbtInt || 
             node->getType().getBasicType() == EbtUint))

            return node;
        else
            return 0;

    default:
        // default is to require a match; all exceptions should have case statements above

        if (type.getBasicType() == node->getType().getBasicType())
            return node;
        else
            return 0;
    }
    
    if (node->getAsConstantUnion()) {

        return promoteConstantUnion(promoteTo, node->getAsConstantUnion());
    } else {    
        //
        // Add a new newNode for the conversion.
        //
        TIntermUnary* newNode = 0;

        TOperator newOp = EOpNull;

        // This is 'mechanism' here, it does any conversion told.  The policy comes
        // from the shader or the above code.
        switch (promoteTo) {
        case EbtDouble:
            //switch (node->getBasicType()) {
            //case EbtInt:   newOp = EOpConvIntToDouble;   break;
            //case EbtUint:  newOp = EOpConvUintToDouble;  break;
            //case EbtBool:  newOp = EOpConvBoolToDouble;  break;
            //case EbtFloat: newOp = EOpConvFloatToDouble; break;
            //default:
                infoSink.info.message(EPrefixInternalError, "Bad promotion node", node->getLine());
                return 0;
            //}
            break;
        case EbtFloat:
            switch (node->getBasicType()) {
            case EbtInt:    newOp = EOpConvIntToFloat;  break;
            case EbtUint:   newOp = EOpConvUintToFloat; break;
            case EbtBool:   newOp = EOpConvBoolToFloat; break;
            case EbtDouble: newOp = EOpConvDoubleToFloat; break;
            default:
                infoSink.info.message(EPrefixInternalError, "Bad promotion node", node->getLine());
                return 0;
            }
            break;
        case EbtBool:
            switch (node->getBasicType()) {
            case EbtInt:    newOp = EOpConvIntToBool;   break;
            case EbtUint:   newOp = EOpConvUintToBool; break;
            case EbtFloat:  newOp = EOpConvFloatToBool; break;
            case EbtDouble: newOp = EOpConvDoubleToBool; break;
            default:
                infoSink.info.message(EPrefixInternalError, "Bad promotion node", node->getLine());
                return 0;
            }
            break;
        case EbtInt:
            switch (node->getBasicType()) {
            case EbtUint:   newOp = EOpConvUintToInt;  break;
            case EbtBool:   newOp = EOpConvBoolToInt;  break;
            case EbtFloat:  newOp = EOpConvFloatToInt; break;
            case EbtDouble: newOp = EOpConvDoubleToInt; break;
            default:
                infoSink.info.message(EPrefixInternalError, "Bad promotion node", node->getLine());
                return 0;
            }
            break;
        case EbtUint:
            switch (node->getBasicType()) {
            case EbtInt:    newOp = EOpConvIntToUint;   break;
            case EbtBool:   newOp = EOpConvBoolToUint;  break;
            case EbtFloat:  newOp = EOpConvFloatToUint; break;
            case EbtDouble: newOp = EOpConvDoubleToUint; break;
            default:
                infoSink.info.message(EPrefixInternalError, "Bad promotion node", node->getLine());
                return 0;
            }
            break;
        default: 
            infoSink.info.message(EPrefixInternalError, "Bad promotion type", node->getLine());
            return 0;
        }

        TType type(promoteTo, EvqTemporary, node->getVectorSize(), node->getMatrixCols(), node->getMatrixRows());
        newNode = new TIntermUnary(newOp, type);
        newNode->setLine(node->getLine());
        newNode->setOperand(node);

        return newNode;
    }
}

//
// See if the 'from' type is allowed to be implicitly converted to the 
// 'to' type.  This is not about vector/array/struct, only about basic type.
//
bool TIntermediate::canImplicitlyPromote(TBasicType from, TBasicType to)
{
    if (profile == EEsProfile || version == 110)
        return 0;

    switch (to) {
    case EbtDouble:
        switch (from) {
        case EbtInt:
        case EbtUint:
        case EbtFloat:
        case EbtDouble:
            return true;
        default:
            return false;
        }
    case EbtFloat:
        switch (from) {
        case EbtInt:
        case EbtUint:
        case EbtFloat:
            return true;
        default:
            return false;
        }
    case EbtUint:
        switch (from) {
        case EbtInt:
        case EbtUint:
            return true;
        default:
            return false;
        }
    case EbtInt:
        switch (from) {
        case EbtInt:
            return true;
        default:
            return false;
        }
    default:
        return false;
    }
}

//
// Safe way to combine two nodes into an aggregate.  Works with null pointers, 
// a node that's not a aggregate yet, etc.
//
// Returns the resulting aggregate, unless 0 was passed in for 
// both existing nodes.
//
TIntermAggregate* TIntermediate::growAggregate(TIntermNode* left, TIntermNode* right, TSourceLoc line)
{
    if (left == 0 && right == 0)
        return 0;

    TIntermAggregate* aggNode = 0;
    if (left)
        aggNode = left->getAsAggregate();
    if (!aggNode || aggNode->getOp() != EOpNull) {
        aggNode = new TIntermAggregate;
        if (left)
            aggNode->getSequence().push_back(left);
    }

    if (right)
        aggNode->getSequence().push_back(right);

    if (line != 0)
        aggNode->setLine(line);

    return aggNode;
}

//
// Turn an existing node into an aggregate.
//
// Returns an aggregate, unless 0 was passed in for the existing node.
//
TIntermAggregate* TIntermediate::makeAggregate(TIntermNode* node, TSourceLoc line)
{
    if (node == 0)
        return 0;

    TIntermAggregate* aggNode = new TIntermAggregate;
    aggNode->getSequence().push_back(node);

    if (line != 0)
        aggNode->setLine(line);
    else
        aggNode->setLine(node->getLine());

    return aggNode;
}

//
// For "if" test nodes.  There are three children; a condition,
// a true path, and a false path.  The two paths are in the
// nodePair.
//
// Returns the selection node created.
//
TIntermNode* TIntermediate::addSelection(TIntermTyped* cond, TIntermNodePair nodePair, TSourceLoc line)
{
    //
    // For compile time constant selections, prune the code and 
    // test now.
    //
    
    if (cond->getAsTyped() && cond->getAsTyped()->getAsConstantUnion()) {
        if (cond->getAsTyped()->getAsConstantUnion()->getUnionArrayPointer()->getBConst())
            return nodePair.node1;
        else
            return nodePair.node2;
    }

    TIntermSelection* node = new TIntermSelection(cond, nodePair.node1, nodePair.node2);
    node->setLine(line);

    return node;
}


TIntermTyped* TIntermediate::addComma(TIntermTyped* left, TIntermTyped* right, TSourceLoc line)
{
    if (left->getType().getQualifier().storage == EvqConst && 
        right->getType().getQualifier().storage == EvqConst) {
        return right;
    } else {
        TIntermTyped *commaAggregate = growAggregate(left, right, line);
        commaAggregate->getAsAggregate()->setOperator(EOpComma);
        commaAggregate->setType(right->getType());
        commaAggregate->getTypePointer()->getQualifier().storage = EvqTemporary;
        return commaAggregate;
    }
}

TIntermTyped* TIntermediate::addMethod(TIntermTyped* object, const TType& type, const TString* name, TSourceLoc line)
{
    TIntermMethod* method = new TIntermMethod(object, type, *name);
    method->setLine(line);

    return method;
}

//
// For "?:" test nodes.  There are three children; a condition,
// a true path, and a false path.  The two paths are specified
// as separate parameters.
//
// Returns the selection node created, or 0 if one could not be.
//
TIntermTyped* TIntermediate::addSelection(TIntermTyped* cond, TIntermTyped* trueBlock, TIntermTyped* falseBlock, TSourceLoc line)
{
    //
    // Get compatible types.
    //
    TIntermTyped* child = addConversion(EOpSequence, trueBlock->getType(), falseBlock);
    if (child)
        falseBlock = child;
    else {
        child = addConversion(EOpSequence, falseBlock->getType(), trueBlock);
        if (child)
            trueBlock = child;
        else
            return 0;
    }

    //
    // See if all the operands are constant, then fold it otherwise not.
    //

    if (cond->getAsConstantUnion() && trueBlock->getAsConstantUnion() && falseBlock->getAsConstantUnion()) {
        if (cond->getAsConstantUnion()->getUnionArrayPointer()->getBConst())
            return trueBlock;
        else
            return falseBlock;
    }

    //
    // Make a selection node.
    //
    TIntermSelection* node = new TIntermSelection(cond, trueBlock, falseBlock, trueBlock->getType());
    node->setLine(line);

    return node;
}

//
// Constant terminal nodes.  Has a union that contains bool, float or int constants
//
// Returns the constant union node created.
//

TIntermConstantUnion* TIntermediate::addConstantUnion(constUnion* unionArrayPointer, const TType& t, TSourceLoc line)
{
    TIntermConstantUnion* node = new TIntermConstantUnion(unionArrayPointer, t);
    node->setLine(line);

    return node;
}

TIntermTyped* TIntermediate::addSwizzle(TVectorFields& fields, TSourceLoc line)
{
    
    TIntermAggregate* node = new TIntermAggregate(EOpSequence);

    node->setLine(line);
    TIntermConstantUnion* constIntNode;
    TIntermSequence &sequenceVector = node->getSequence();
    constUnion* unionArray;

    for (int i = 0; i < fields.num; i++) {
        unionArray = new constUnion[1];
        unionArray->setIConst(fields.offsets[i]);
        constIntNode = addConstantUnion(unionArray, TType(EbtInt, EvqConst), line);
        sequenceVector.push_back(constIntNode);
    }

    return node;
}

//
// Create loop nodes.
//
TIntermNode* TIntermediate::addLoop(TIntermNode* body, TIntermTyped* test, TIntermTyped* terminal, bool testFirst, TSourceLoc line)
{
    TIntermNode* node = new TIntermLoop(body, test, terminal, testFirst);
    node->setLine(line);
    
    return node;
}

//
// Add branches.
//
TIntermBranch* TIntermediate::addBranch(TOperator branchOp, TSourceLoc line)
{
    return addBranch(branchOp, 0, line);
}

TIntermBranch* TIntermediate::addBranch(TOperator branchOp, TIntermTyped* expression, TSourceLoc line)
{
    TIntermBranch* node = new TIntermBranch(branchOp, expression);
    node->setLine(line);

    return node;
}

//
// This is to be executed once the final root is put on top by the parsing
// process.
//
bool TIntermediate::postProcess(TIntermNode* root, EShLanguage language)
{
    if (root == 0)
        return true;

    //
    // First, finish off the top level sequence, if any
    //
    TIntermAggregate* aggRoot = root->getAsAggregate();
    if (aggRoot && aggRoot->getOp() == EOpNull)
        aggRoot->setOperator(EOpSequence);

    return true;
}

//
// This deletes the tree.
//
void TIntermediate::remove(TIntermNode* root)
{
    if (root)
        RemoveAllTreeNodes(root);
}

////////////////////////////////////////////////////////////////
//
// Member functions of the nodes used for building the tree.
//
////////////////////////////////////////////////////////////////

//
// Say whether or not an operation node changes the value of a variable.
//
// Returns true if state is modified.
//
bool TIntermOperator::modifiesState() const
{
    switch (op) {    
    case EOpPostIncrement: 
    case EOpPostDecrement: 
    case EOpPreIncrement:  
    case EOpPreDecrement:  
    case EOpAssign:    
    case EOpAddAssign: 
    case EOpSubAssign: 
    case EOpMulAssign: 
    case EOpVectorTimesMatrixAssign:
    case EOpVectorTimesScalarAssign:
    case EOpMatrixTimesScalarAssign:
    case EOpMatrixTimesMatrixAssign:
    case EOpDivAssign: 
    case EOpModAssign: 
    case EOpAndAssign: 
    case EOpInclusiveOrAssign: 
    case EOpExclusiveOrAssign: 
    case EOpLeftShiftAssign:   
    case EOpRightShiftAssign:  
        return true;
    default:
        return false;
    }
}

//
// returns true if the operator is for one of the constructors
//
bool TIntermOperator::isConstructor() const
{
    return op > EOpConstructGuardStart && op < EOpConstructGuardEnd;
}

//
// Make sure the type of a unary operator is appropriate for its 
// combination of operation and operand type.
//
// Returns false in nothing makes sense.
//
bool TIntermUnary::promote(TInfoSink&)
{
    switch (op) {
    case EOpLogicalNot:
        if (operand->getBasicType() != EbtBool)

            return false;
        break;
    case EOpBitwiseNot:
        if (operand->getBasicType() != EbtInt &&
            operand->getBasicType() != EbtUint)

            return false;
        break;
    case EOpNegative:
    case EOpPostIncrement:
    case EOpPostDecrement:
    case EOpPreIncrement:
    case EOpPreDecrement:
        if (operand->getBasicType() != EbtInt && 
            operand->getBasicType() != EbtUint && 
            operand->getBasicType() != EbtFloat)

            return false;
        break;

    default:
        if (operand->getBasicType() != EbtFloat)

            return false;
    }

    setType(operand->getType());
    getTypePointer()->getQualifier().storage = EvqTemporary;

    return true;
}

//
// Establishes the type of the resultant operation, as well as
// makes the operator the correct one for the operands.
//
// Returns false if operator can't work on operands.
//
bool TIntermBinary::promote(TInfoSink& infoSink)
{
    //
    // Arrays have to be exact matches.
    //
    if ((left->isArray() || right->isArray()) && (left->getType() != right->getType()))
        return false;

    //
    // Base assumption:  just make the type the same as the left
    // operand.  Then only deviations from this need be coded.
    //
    setType(left->getType());
    type.getQualifier().storage = EvqTemporary;

    // Fix precision qualifiers
    if (right->getQualifier().precision > getQualifier().precision)
        getQualifier().precision = right->getQualifier().precision;
    if (getQualifier().precision != EpqNone) {
        left->propagatePrecision(getQualifier().precision);
        right->propagatePrecision(getQualifier().precision);
    }

    //
    // Array operations.
    //
    if (left->isArray()) {

        switch (op) {

        //
        // Promote to conditional
        //
        case EOpEqual:
        case EOpNotEqual:
            setType(TType(EbtBool));
            break;

        case EOpAssign:
            // array information was correctly set above
            break;

        default:
            return false;
        }

        return true;
    }
    
    //
    // All scalars.  Code after this test assumes this case is removed!
    //
    if (left->getVectorSize() == 1 && right->getVectorSize() == 1) {

        switch (op) {

        //
        // Promote to conditional
        //
        case EOpEqual:
        case EOpNotEqual:
        case EOpLessThan:
        case EOpGreaterThan:
        case EOpLessThanEqual:
        case EOpGreaterThanEqual:
            setType(TType(EbtBool));
            break;

        //
        // And and Or operate only on conditionals
        //
        case EOpLogicalAnd:
        case EOpLogicalOr:
            if (left->getBasicType() != EbtBool || right->getBasicType() != EbtBool)
                return false;           
            setType(TType(EbtBool));
            break;

        //
        // Check for integer only operands.
        //
        case EOpMod:
        case EOpRightShift:
        case EOpLeftShift:
        case EOpAnd:
        case EOpInclusiveOr:
        case EOpExclusiveOr:
            if ( left->getBasicType() != EbtInt &&  left->getBasicType() != EbtUint ||
                right->getBasicType() != EbtInt && right->getBasicType() != EbtUint)
                return false;
            break;
        case EOpModAssign:
        case EOpAndAssign:
        case EOpInclusiveOrAssign:
        case EOpExclusiveOrAssign:
        case EOpLeftShiftAssign:
        case EOpRightShiftAssign:
            if ( left->getBasicType() != EbtInt &&  left->getBasicType() != EbtUint ||
                right->getBasicType() != EbtInt && right->getBasicType() != EbtUint)
                return false;
            // fall through

        //
        // Everything else should have matching types
        //
        default:
            if (left->getBasicType() != right->getBasicType() ||
                left->isMatrix()     != right->isMatrix())
                return false;
        }

        return true;
    }

    //
    // Can these two operands be combined?
    //
    TBasicType basicType = left->getBasicType();
    switch (op) {
    case EOpMul:
        if (!left->isMatrix() && right->isMatrix()) {
            if (left->isVector()) {
                if (left->getVectorSize() != right->getMatrixRows())
                    return false;
                op = EOpVectorTimesMatrix;
                setType(TType(basicType, EvqTemporary, right->getMatrixCols()));
            } else {
                op = EOpMatrixTimesScalar;
                setType(TType(basicType, EvqTemporary, 0, right->getMatrixCols(), right->getMatrixRows()));
            }
        } else if (left->isMatrix() && !right->isMatrix()) {
            if (right->isVector()) {
                if (left->getMatrixCols() != right->getVectorSize())
                    return false;
                op = EOpMatrixTimesVector;
                setType(TType(basicType, EvqTemporary, left->getMatrixRows()));
            } else {
                op = EOpMatrixTimesScalar;
            }
        } else if (left->isMatrix() && right->isMatrix()) {
            if (left->getMatrixCols() != right->getMatrixRows())
                return false;
            op = EOpMatrixTimesMatrix;
            setType(TType(basicType, EvqTemporary, 0, right->getMatrixCols(), left->getMatrixRows()));
        } else if (!left->isMatrix() && !right->isMatrix()) {
            if (left->isVector() && right->isVector()) {
                if (left->getVectorSize() != right->getVectorSize())
                    return false;
                // leave as component product
            } else if (left->isVector() || right->isVector()) {
                op = EOpVectorTimesScalar;
                if (right->getVectorSize() > 1)
                    setType(TType(basicType, EvqTemporary, right->getVectorSize()));
            }
        } else {
            infoSink.info.message(EPrefixInternalError, "Missing elses", getLine());
            return false;
        }
        break;
    case EOpMulAssign:
        if (!left->isMatrix() && right->isMatrix()) {
            if (left->isVector()) {
                if (left->getVectorSize() != right->getMatrixRows() || left->getVectorSize() != right->getMatrixCols())
                    return false;
                op = EOpVectorTimesMatrixAssign;
            } else {
                return false;
            }
        } else if (left->isMatrix() && !right->isMatrix()) {
            if (right->isVector()) {
                return false;
            } else {
                op = EOpMatrixTimesScalarAssign;
            }
        } else if (left->isMatrix() && right->isMatrix()) {
            if (left->getMatrixCols() != left->getMatrixRows() || left->getMatrixCols() != right->getMatrixCols() || left->getMatrixCols() != right->getMatrixRows())
                return false;
            op = EOpMatrixTimesMatrixAssign;
        } else if (!left->isMatrix() && !right->isMatrix()) {
            if (left->isVector() && right->isVector()) {
                // leave as component product
            } else if (left->isVector() || right->isVector()) {
                if (! left->isVector())
                    return false;
                op = EOpVectorTimesScalarAssign;
            }
        } else {
            infoSink.info.message(EPrefixInternalError, "Missing elses", getLine());
            return false;
        }
        break;      
    case EOpAssign:
        if (left->getVectorSize() != right->getVectorSize() || left->getMatrixCols() != right->getMatrixCols() || left->getMatrixRows() != right->getMatrixRows())
            return false;
        // fall through
    case EOpAdd:
    case EOpSub:
    case EOpDiv:
    case EOpMod:
    case EOpAddAssign:
    case EOpSubAssign:
    case EOpDivAssign:
    case EOpModAssign:
        if (left->isMatrix() && right->isVector() ||
            left->isVector() && right->isMatrix() ||
            left->getBasicType() != right->getBasicType())
            return false;
        if (left->isMatrix() && right->isMatrix() && (left->getMatrixCols() != right->getMatrixCols() || left->getMatrixRows() != right->getMatrixRows()))
            return false;
        if (left->isVector() && right->isVector() && left->getVectorSize() != right->getVectorSize())
            return false;
        if (right->isVector() || right->isMatrix())
            setType(TType(basicType, EvqTemporary, right->getVectorSize(), right->getMatrixCols(), right->getMatrixRows()));
        break;
        
    case EOpEqual:
    case EOpNotEqual:
    case EOpLessThan:
    case EOpGreaterThan:
    case EOpLessThanEqual:
    case EOpGreaterThanEqual:
        if (left->isMatrix() && right->isVector() ||
            left->isVector() && right->isMatrix() ||
            left->getBasicType() != right->getBasicType())
            return false;
        setType(TType(EbtBool));
        break;

    default:
        return false;
    }

    //
    // One more check for assignment.  The Resulting type has to match the left operand.
    //
    switch (op) {
    case EOpAssign:
    case EOpAddAssign:
    case EOpSubAssign:
    case EOpMulAssign:
    case EOpDivAssign:
    case EOpModAssign:
    case EOpAndAssign:
    case EOpInclusiveOrAssign:
    case EOpExclusiveOrAssign:
    case EOpLeftShiftAssign:
    case EOpRightShiftAssign:
        if (getType() != left->getType())
            return false;
        break;
    default: 
        break;
    }
    
    return true;
}

void TIntermTyped::propagatePrecision(TPrecisionQualifier newPrecision)
{
    if (getQualifier().precision != EpqNone || (getBasicType() != EbtInt && getBasicType() != EbtUint && getBasicType() != EbtFloat))
        return;

    getQualifier().precision = newPrecision;

    TIntermBinary* binaryNode = getAsBinaryNode();
    if (binaryNode) {
        binaryNode->getLeft()->propagatePrecision(newPrecision);
        binaryNode->getRight()->propagatePrecision(newPrecision);
    }

    TIntermUnary* unaryNode = getAsUnaryNode();
    if (unaryNode)
        unaryNode->getOperand()->propagatePrecision(newPrecision);

    TIntermAggregate* aggregateNode = getAsAggregate();
    if (aggregateNode) {
        TIntermSequence operands = aggregateNode->getSequence();
        for (unsigned int i = 0; i < operands.size(); ++i) {
            TIntermTyped* typedNode = operands[i]->getAsTyped();
            if (! typedNode)
                break;
            typedNode->propagatePrecision(newPrecision);
        }
    }

    TIntermSelection* selectionNode = getAsSelectionNode();
    if (selectionNode) {
        TIntermTyped* typedNode = selectionNode->getTrueBlock()->getAsTyped();
        if (typedNode) {
            typedNode->propagatePrecision(newPrecision);
            typedNode = selectionNode->getFalseBlock()->getAsTyped();
            if (typedNode)
                typedNode->propagatePrecision(newPrecision);
        }
    }

    // TODO: functionality: propagate precision for
    //    comma operator:  just through the last operand
    //    ":?" and ",": where is this triggered?
    //    built-in function calls: how much to propagate to arguments?
    //    length()?
    //    indexing?
}

TIntermTyped* TIntermediate::promoteConstantUnion(TBasicType promoteTo, TIntermConstantUnion* node) 
{
    if (node->getType().isArray())
        infoSink.info.message(EPrefixInternalError, "Cannot promote array", node->getLine());

    constUnion *rightUnionArray = node->getUnionArrayPointer();
    int size = node->getType().getObjectSize();

    constUnion *leftUnionArray = new constUnion[size];

    for (int i=0; i < size; i++) {        
        switch (promoteTo) {
        case EbtFloat:
            switch (node->getType().getBasicType()) {
            case EbtInt:
                leftUnionArray[i].setFConst(static_cast<float>(rightUnionArray[i].getIConst()));
                break;
            case EbtUint:
                leftUnionArray[i].setFConst(static_cast<float>(rightUnionArray[i].getUConst()));
                break;
            case EbtBool:
                leftUnionArray[i].setFConst(static_cast<float>(rightUnionArray[i].getBConst()));
                break;
            case EbtFloat:
                leftUnionArray[i] = rightUnionArray[i];
                break;
            case EbtDouble:
                leftUnionArray[i].setFConst(static_cast<float>(rightUnionArray[i].getBConst()));
                break;
            default: 
                infoSink.info.message(EPrefixInternalError, "Cannot promote", node->getLine());
                return 0;
            }                
            break;
        case EbtDouble:
            switch (node->getType().getBasicType()) {
            case EbtInt:
                leftUnionArray[i].setDConst(static_cast<float>(rightUnionArray[i].getIConst()));
                break;
            case EbtUint:
                leftUnionArray[i].setDConst(static_cast<float>(rightUnionArray[i].getUConst()));
                break;
            case EbtBool:
                leftUnionArray[i].setDConst(static_cast<float>(rightUnionArray[i].getBConst()));
                break;
            case EbtFloat:
                leftUnionArray[i].setDConst(static_cast<float>(rightUnionArray[i].getFConst()));
                break;
            case EbtDouble:
                leftUnionArray[i] = rightUnionArray[i];
                break;
            default: 
                infoSink.info.message(EPrefixInternalError, "Cannot promote", node->getLine());
                return 0;
            }                
            break;
        case EbtInt:
            switch (node->getType().getBasicType()) {
            case EbtInt:
                leftUnionArray[i] = rightUnionArray[i];
                break;
            case EbtUint:
                leftUnionArray[i].setIConst(static_cast<int>(rightUnionArray[i].getUConst()));
                break;
            case EbtBool:
                leftUnionArray[i].setIConst(static_cast<int>(rightUnionArray[i].getBConst()));
                break;
            case EbtFloat:
                leftUnionArray[i].setIConst(static_cast<int>(rightUnionArray[i].getFConst()));
                break;
            case EbtDouble:
                leftUnionArray[i].setIConst(static_cast<int>(rightUnionArray[i].getDConst()));
                break;
            default: 
                infoSink.info.message(EPrefixInternalError, "Cannot promote", node->getLine());
                return 0;
            }                
            break;
        case EbtUint:
            switch (node->getType().getBasicType()) {
            case EbtInt:
                leftUnionArray[i].setUConst(static_cast<unsigned int>(rightUnionArray[i].getIConst()));
                break;
            case EbtUint:
                leftUnionArray[i] = rightUnionArray[i];
                break;
            case EbtBool:
                leftUnionArray[i].setUConst(static_cast<unsigned int>(rightUnionArray[i].getBConst()));
                break;
            case EbtFloat:
                leftUnionArray[i].setUConst(static_cast<unsigned int>(rightUnionArray[i].getFConst()));
                break;
            case EbtDouble:
                leftUnionArray[i].setUConst(static_cast<unsigned int>(rightUnionArray[i].getDConst()));
                break;
            default: 
                infoSink.info.message(EPrefixInternalError, "Cannot promote", node->getLine());
                return 0;
            }                
            break;
        case EbtBool:
            switch (node->getType().getBasicType()) {
            case EbtInt:
                leftUnionArray[i].setBConst(rightUnionArray[i].getIConst() != 0);
                break;
            case EbtUint:
                leftUnionArray[i].setBConst(rightUnionArray[i].getUConst() != 0);
                break;
            case EbtBool:
                leftUnionArray[i] = rightUnionArray[i];
                break;
            case EbtFloat:
                leftUnionArray[i].setBConst(rightUnionArray[i].getFConst() != 0.0f);
                break;
            case EbtDouble:
                leftUnionArray[i].setBConst(rightUnionArray[i].getDConst() != 0.0f);
                break;
            default: 
                infoSink.info.message(EPrefixInternalError, "Cannot promote", node->getLine());
                return 0;
            }
            break;
        default:
            infoSink.info.message(EPrefixInternalError, "Incorrect data type found", node->getLine());
            return 0;
        }    
    }
    
    const TType& t = node->getType();
    
    return addConstantUnion(leftUnionArray, TType(promoteTo, t.getQualifier().storage, t.getVectorSize(), t.getMatrixCols(), t.getMatrixRows()), 
                            node->getLine());
}

void TIntermAggregate::addToPragmaTable(const TPragmaTable& pTable)
{
    assert(!pragmaTable);
    pragmaTable = new TPragmaTable();
    *pragmaTable = pTable;
}

