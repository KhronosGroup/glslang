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
// Definition of the in-memory high-level intermediate representation
// of shaders.  This is a tree that parser creates.
//
// Nodes in the tree are defined as a hierarchy of classes derived from 
// TIntermNode. Each is a node in a tree.  There is no preset branching factor;
// each node can have it's own type of list of children.
//

#ifndef __INTERMEDIATE_H
#define __INTERMEDIATE_H

#include "../Include/Common.h"
#include "../Include/Types.h"
#include "../Include/ConstantUnion.h"

namespace glslang {

//
// Operators used by the high-level (parse tree) representation.
//
enum TOperator {
    EOpNull,            // if in a node, should only mean a node is still being built
    EOpSequence,        // denotes a list of statements, or parameters, etc.
    EOpLinkerObjects,   // for aggregate node of objects the linker may need, if not reference by the rest of the AST
    EOpFunctionCall,    
    EOpFunction,        // For function definition
    EOpParameters,      // an aggregate listing the parameters to a function

    //
    // Unary operators
    //
    
    EOpNegative,
    EOpLogicalNot,
    EOpVectorLogicalNot,
    EOpBitwiseNot,

    EOpPostIncrement,
    EOpPostDecrement,
    EOpPreIncrement,
    EOpPreDecrement,

    EOpConvIntToBool,
    EOpConvUintToBool,
    EOpConvFloatToBool,
    EOpConvDoubleToBool,
    EOpConvBoolToFloat,
    EOpConvIntToFloat,
    EOpConvUintToFloat,
    EOpConvDoubleToFloat,
    EOpConvUintToInt,
    EOpConvFloatToInt,
    EOpConvBoolToInt,
    EOpConvDoubleToInt,
    EOpConvIntToUint,
    EOpConvFloatToUint,
    EOpConvBoolToUint,
    EOpConvDoubleToUint,
    EOpConvIntToDouble,
    EOpConvUintToDouble,
    EOpConvFloatToDouble,
    EOpConvBoolToDouble,

    //
    // binary operations
    //

    EOpAdd,
    EOpSub,
    EOpMul,
    EOpDiv,
    EOpMod,
    EOpRightShift,
    EOpLeftShift,
    EOpAnd,
    EOpInclusiveOr,
    EOpExclusiveOr,
    EOpEqual,
    EOpNotEqual,
    EOpVectorEqual,
    EOpVectorNotEqual,
    EOpLessThan,
    EOpGreaterThan,
    EOpLessThanEqual,
    EOpGreaterThanEqual,
    EOpComma,

    EOpVectorTimesScalar,
    EOpVectorTimesMatrix,
    EOpMatrixTimesVector,
    EOpMatrixTimesScalar,

    EOpLogicalOr,
    EOpLogicalXor,
    EOpLogicalAnd,

    EOpIndexDirect,
    EOpIndexIndirect,
    EOpIndexDirectStruct,

    EOpVectorSwizzle,

    EOpMethod,

    //
    // Built-in functions potentially mapped to operators
    //

    EOpRadians,
    EOpDegrees,
    EOpSin,
    EOpCos,
    EOpTan,
    EOpAsin,
    EOpAcos,
    EOpAtan,
    EOpSinh,
    EOpCosh,
    EOpTanh,
    EOpAsinh,
    EOpAcosh,
    EOpAtanh,

    EOpPow,
    EOpExp,
    EOpLog,
    EOpExp2,
    EOpLog2,
    EOpSqrt,
    EOpInverseSqrt,

    EOpAbs,
    EOpSign,
    EOpFloor,
    EOpTrunc,
    EOpRound,
    EOpRoundEven,
    EOpCeil,
    EOpFract,
    EOpModf,
    EOpMin,
    EOpMax,
    EOpClamp,
    EOpMix,
    EOpStep,
    EOpSmoothStep,

    EOpIsNan,
    EOpIsInf,

    EOpFloatBitsToInt,
    EOpFloatBitsToUint,
    EOpIntBitsToFloat,
    EOpUintBitsToFloat,
    EOpPackSnorm2x16,
    EOpUnpackSnorm2x16,
    EOpPackUnorm2x16,
    EOpUnpackUnorm2x16,
    EOpPackHalf2x16,
    EOpUnpackHalf2x16,

    EOpLength,
    EOpDistance,
    EOpDot,
    EOpCross,
    EOpNormalize,
    EOpFaceForward,
    EOpReflect,
    EOpRefract,

    EOpDPdx,            // Fragment only
    EOpDPdy,            // Fragment only
    EOpFwidth,          // Fragment only

    EOpMatrixTimesMatrix,
    EOpOuterProduct,
    EOpDeterminant,
    EOpMatrixInverse,
    EOpTranspose,

    EOpEmitVertex,           // geometry only
    EOpEndPrimitive,         // geometry only
    EOpEmitStreamVertex,     // geometry only
    EOpEndStreamPrimitive,   // geometry only

    EOpBarrier,
    EOpMemoryBarrier,
    EOpMemoryBarrierAtomicCounter,
    EOpMemoryBarrierBuffer,
    EOpMemoryBarrierImage,
    EOpMemoryBarrierShared,  // compute only
    EOpGroupMemoryBarrier,   // compute only

    EOpAny,
    EOpAll,

    //
    // Branch
    //

    EOpKill,            // Fragment only
    EOpReturn,
    EOpBreak,
    EOpContinue,
    EOpCase,
    EOpDefault,

    //
    // Constructors
    //

    EOpConstructGuardStart,
    EOpConstructInt,
    EOpConstructUint,
    EOpConstructBool,
    EOpConstructFloat,
    EOpConstructDouble,
    EOpConstructVec2,
    EOpConstructVec3,
    EOpConstructVec4,
    EOpConstructDVec2,
    EOpConstructDVec3,
    EOpConstructDVec4,
    EOpConstructBVec2,
    EOpConstructBVec3,
    EOpConstructBVec4,
    EOpConstructIVec2,
    EOpConstructIVec3,
    EOpConstructIVec4,
    EOpConstructUVec2,
    EOpConstructUVec3,
    EOpConstructUVec4,
    EOpConstructMat2x2,
    EOpConstructMat2x3,
    EOpConstructMat2x4,
    EOpConstructMat3x2,
    EOpConstructMat3x3,
    EOpConstructMat3x4,
    EOpConstructMat4x2,
    EOpConstructMat4x3,
    EOpConstructMat4x4,
    EOpConstructDMat2x2,
    EOpConstructDMat2x3,
    EOpConstructDMat2x4,
    EOpConstructDMat3x2,
    EOpConstructDMat3x3,
    EOpConstructDMat3x4,
    EOpConstructDMat4x2,
    EOpConstructDMat4x3,
    EOpConstructDMat4x4,
    EOpConstructStruct,
    EOpConstructGuardEnd,

    //
    // moves
    //
    
    EOpAssign,
    EOpAddAssign,
    EOpSubAssign,
    EOpMulAssign,
    EOpVectorTimesMatrixAssign,
    EOpVectorTimesScalarAssign,
    EOpMatrixTimesScalarAssign,
    EOpMatrixTimesMatrixAssign,
    EOpDivAssign,
    EOpModAssign,
    EOpAndAssign,
    EOpInclusiveOrAssign,
    EOpExclusiveOrAssign,
    EOpLeftShiftAssign,
    EOpRightShiftAssign,

    //
    // Array operators
    //

    EOpArrayLength,
};

class TIntermTraverser;
class TIntermOperator;
class TIntermAggregate;
class TIntermUnary;
class TIntermBinary;
class TIntermConstantUnion;
class TIntermSelection;
class TIntermSwitch;
class TIntermBranch;
class TIntermTyped;
class TIntermMethod;
class TIntermSymbol;

} // end namespace glslang

//
// Base class for the tree nodes
//
// (Put outside the glslang namespace, as it's used as part of the external interface.)
//
class TIntermNode {
public:
    POOL_ALLOCATOR_NEW_DELETE(glslang::GetThreadPoolAllocator())

    TIntermNode() { loc.line = 0; loc.string = 0; }
    virtual glslang::TSourceLoc getLoc() const { return loc; }
    virtual void setLoc(glslang::TSourceLoc l) { loc = l; }
    virtual void traverse(glslang::TIntermTraverser*) = 0;
    virtual glslang::TIntermTyped*         getAsTyped()         { return 0; }
    virtual glslang::TIntermOperator*      getAsOperator()      { return 0; }
    virtual glslang::TIntermConstantUnion* getAsConstantUnion() { return 0; }
    virtual glslang::TIntermAggregate*     getAsAggregate()     { return 0; }
    virtual glslang::TIntermUnary*         getAsUnaryNode()     { return 0; }
    virtual glslang::TIntermBinary*        getAsBinaryNode()    { return 0; }
    virtual glslang::TIntermSelection*     getAsSelectionNode() { return 0; }
    virtual glslang::TIntermSwitch*        getAsSwitchNode()    { return 0; }
    virtual glslang::TIntermMethod*        getAsMethodNode()    { return 0; }
    virtual glslang::TIntermSymbol*        getAsSymbolNode()    { return 0; }
    virtual glslang::TIntermBranch*        getAsBranchNode()    { return 0; }
    virtual ~TIntermNode() { }
protected:
    glslang::TSourceLoc loc;
};

namespace glslang {

//
// This is just to help yacc.
//
struct TIntermNodePair {
    TIntermNode* node1;
    TIntermNode* node2;
};

//
// Intermediate class for nodes that have a type.
//
class TIntermTyped : public TIntermNode {
public:
	TIntermTyped(const TType& t) { type.shallowCopy(t); }
    virtual TIntermTyped* getAsTyped()         { return this; }
    virtual void setType(const TType& t) { type.shallowCopy(t); }
    virtual const TType& getType() const { return type; }
    virtual TType& getWritableType() { return type; }
    
    virtual TBasicType getBasicType() const { return type.getBasicType(); }
    virtual TQualifier& getQualifier() { return type.getQualifier(); }
    virtual const TQualifier& getQualifier() const { return type.getQualifier(); }
    virtual void propagatePrecision(TPrecisionQualifier);
    virtual int getVectorSize() const { return type.getVectorSize(); }
    virtual int getMatrixCols() const { return type.getMatrixCols(); }
    virtual int getMatrixRows() const { return type.getMatrixRows(); }
    virtual bool isMatrix() const { return type.isMatrix(); }
    virtual bool isArray()  const { return type.isArray(); }
    virtual bool isVector() const { return type.isVector(); }
    virtual bool isScalar() const { return type.isScalar(); }
    virtual bool isStruct() const { return type.isStruct(); }
    TString getCompleteString() const { return type.getCompleteString(); }

protected:
    TType type;
};

//
// Handle for, do-while, and while loops.
//
class TIntermLoop : public TIntermNode {
public:
    TIntermLoop(TIntermNode* aBody, TIntermTyped* aTest, TIntermTyped* aTerminal, bool testFirst) : 
        body(aBody),
        test(aTest),
        terminal(aTerminal),
        first(testFirst) { }
    virtual void traverse(TIntermTraverser*);
    TIntermNode*  getBody() { return body; }
    TIntermTyped* getTest() { return test; }
    TIntermTyped* getTerminal() { return terminal; }
    bool testFirst() { return first; }
protected:
    TIntermNode* body;       // code to loop over
    TIntermTyped* test;      // exit condition associated with loop, could be 0 for 'for' loops
    TIntermTyped* terminal;  // exists for for-loops
    bool first;              // true for while and for, not for do-while
};

//
// Handle case, break, continue, return, and kill.
//
class TIntermBranch : public TIntermNode {
public:
    TIntermBranch(TOperator op, TIntermTyped* e) :
        flowOp(op),
        expression(e) { }
    virtual TIntermBranch* getAsBranchNode() { return this; }
    virtual void traverse(TIntermTraverser*);
    TOperator getFlowOp() { return flowOp; }
    TIntermTyped* getExpression() { return expression; }
protected:
    TOperator flowOp;
    TIntermTyped* expression;
};

//
// Represent method names before seeing their calling signature
// or resolving them to operations.  Just an expression as the base object
// and a textural name.
//
class TIntermMethod : public TIntermTyped {
public:
    TIntermMethod(TIntermTyped* o, const TType& t, const TString& m) : TIntermTyped(t), object(o), method(m) { }
    virtual TIntermMethod* getAsMethodNode() { return this; }
    virtual const TString& getMethodName() const { return method; }
    virtual TIntermTyped* getObject() const { return object; }
    virtual void traverse(TIntermTraverser*);
protected:
    TIntermTyped* object;
    TString method;
};

//
// Nodes that correspond to symbols or constants in the source code.
//
class TIntermSymbol : public TIntermTyped {
public:
	// if symbol is initialized as symbol(sym), the memory comes from the poolallocator of sym. If sym comes from
	// per process threadPoolAllocator, then it causes increased memory usage per compile
	// it is essential to use "symbol = sym" to assign to symbol
    TIntermSymbol(int i, const TString& n, const TType& t) : 
        TIntermTyped(t), id(i) { name = n;} 
    virtual int getId() const { return id; }
    virtual const TString& getName() const { return name; }
    virtual void traverse(TIntermTraverser*);
    virtual TIntermSymbol* getAsSymbolNode() { return this; }
    void setConstArray(const TConstUnionArray& c) { unionArray = c; }
    const TConstUnionArray& getConstArray() const { return unionArray; }
protected:
    int id;
    TString name;
    TConstUnionArray unionArray;
};

class TIntermConstantUnion : public TIntermTyped {
public:
    TIntermConstantUnion(const TConstUnionArray& ua, const TType& t) : TIntermTyped(t), unionArray(ua) { }
    const TConstUnionArray& getConstArray() const { return unionArray; }
    virtual TIntermConstantUnion* getAsConstantUnion()  { return this; }
    virtual void traverse(TIntermTraverser*);
    virtual TIntermTyped* fold(TOperator, TIntermTyped*);
    virtual TIntermTyped* fold(TOperator, const TType&);
protected:
    const TConstUnionArray unionArray;
};

//
// Intermediate class for node types that hold operators.
//
class TIntermOperator : public TIntermTyped {
public:
    TIntermOperator* getAsOperator() { return this; }
    TOperator getOp() { return op; }
    bool modifiesState() const;
    bool isConstructor() const;
    virtual bool promote() { return true; }
protected:
    TIntermOperator(TOperator o) : TIntermTyped(TType(EbtFloat)), op(o) {}
    TIntermOperator(TOperator o, TType& t) : TIntermTyped(t), op(o) {}   
    TOperator op;
};

//
// Nodes for all the basic binary math operators.
//
class TIntermBinary : public TIntermOperator {
public:
    TIntermBinary(TOperator o) : TIntermOperator(o) {}
    virtual void traverse(TIntermTraverser*);
    virtual void setLeft(TIntermTyped* n) { left = n; }
    virtual void setRight(TIntermTyped* n) { right = n; }
    virtual TIntermTyped* getLeft() const { return left; }
    virtual TIntermTyped* getRight() const { return right; }
    virtual TIntermBinary* getAsBinaryNode() { return this; }
    virtual bool promote();
    virtual void updatePrecision();
protected:
    TIntermTyped* left;
    TIntermTyped* right;
};

//
// Nodes for unary math operators.
//
class TIntermUnary : public TIntermOperator {
public:
    TIntermUnary(TOperator o, TType& t) : TIntermOperator(o, t), operand(0) {}
    TIntermUnary(TOperator o) : TIntermOperator(o), operand(0) {}
    virtual void traverse(TIntermTraverser*);
    virtual void setOperand(TIntermTyped* o) { operand = o; }
    virtual TIntermTyped* getOperand() { return operand; }
    virtual TIntermUnary* getAsUnaryNode() { return this; }
    virtual bool promote();
    virtual void updatePrecision();
protected:
    TIntermTyped* operand;
};

typedef TVector<TIntermNode*> TIntermSequence;
typedef TVector<int> TQualifierList;
//
// Nodes that operate on an arbitrary sized set of children.
//
class TIntermAggregate : public TIntermOperator {
public:
    TIntermAggregate() : TIntermOperator(EOpNull), userDefined(false), pragmaTable(0) { }
    TIntermAggregate(TOperator o) : TIntermOperator(o), pragmaTable(0) { }
	~TIntermAggregate() { delete pragmaTable; }
    virtual TIntermAggregate* getAsAggregate() { return this; }
    virtual void setOperator(TOperator o) { op = o; }
    virtual TIntermSequence& getSequence() { return sequence; }
    virtual const TIntermSequence& getSequence() const { return sequence; }
	virtual void setName(const TString& n) { name = n; }
    virtual const TString& getName() const { return name; }
    virtual void traverse(TIntermTraverser*);
    virtual void setUserDefined() { userDefined = true; }
    virtual bool isUserDefined() { return userDefined; }
    virtual TQualifierList& getQualifierList() { return qualifier; }
    virtual const TQualifierList& getQualifierList() const { return qualifier; }
	void setOptimize(bool o) { optimize = o; }
	void setDebug(bool d) { debug = d; }
	bool getOptimize() { return optimize; }
	bool getDebug() { return debug; }
	void addToPragmaTable(const TPragmaTable& pTable);
	const TPragmaTable& getPragmaTable() const { return *pragmaTable; }
protected:
	TIntermAggregate(const TIntermAggregate&); // disallow copy constructor
	TIntermAggregate& operator=(const TIntermAggregate&); // disallow assignment operator
    TIntermSequence sequence;
    TQualifierList qualifier;
	TString name;
    bool userDefined; // used for user defined function names
	bool optimize;
	bool debug;
	TPragmaTable* pragmaTable;
};

//
// For if tests.
//
class TIntermSelection : public TIntermTyped {
public:
    TIntermSelection(TIntermTyped* cond, TIntermNode* trueB, TIntermNode* falseB) :
        TIntermTyped(TType(EbtVoid)), condition(cond), trueBlock(trueB), falseBlock(falseB) {}
    TIntermSelection(TIntermTyped* cond, TIntermNode* trueB, TIntermNode* falseB, const TType& type) :
        TIntermTyped(type), condition(cond), trueBlock(trueB), falseBlock(falseB) {}
    virtual void traverse(TIntermTraverser*);
    virtual TIntermTyped* getCondition() const { return condition; }
    virtual TIntermNode* getTrueBlock() const { return trueBlock; }
    virtual TIntermNode* getFalseBlock() const { return falseBlock; }
    virtual TIntermSelection* getAsSelectionNode() { return this; }
protected:
    TIntermTyped* condition;
    TIntermNode* trueBlock;
    TIntermNode* falseBlock;
};

//
// For switch statements.  Designed use is that a switch will have sequence of nodes
// that are either case/default nodes or a *single* node that represents all the code
// in between (if any) consecutive case/defaults.  So, a traversal need only deal with
// 0 or 1 nodes per case/default statement.
//
class TIntermSwitch : public TIntermNode {
public:
    TIntermSwitch(TIntermTyped* cond, TIntermAggregate* b) : condition(cond), body(b) { }
    virtual void traverse(TIntermTraverser*);
    virtual TIntermNode* getCondition() const { return condition; }
    virtual TIntermAggregate* getBody() const { return body; }
    virtual TIntermSwitch* getAsSwitchNode() { return this; }
protected:
    TIntermTyped* condition;
    TIntermAggregate* body;
};

//
// For traversing the tree.  User should derive from this, 
// put their traversal specific data in it, and then pass
// it to a Traverse method.
//
// When using this, just fill in the methods for nodes you want visited.
// Return false from a pre-visit to skip visiting that node's subtree.
//
// Explicitly set postVisit to true if you want post visiting, otherwise,
// filled in methods will only be called at pre-visit time (before processing
// the subtree).
//
// If you only want post-visits, explicitly turn off preVisit and turn on postVisit.
//
class TIntermTraverser {
public:
    POOL_ALLOCATOR_NEW_DELETE(GetThreadPoolAllocator())

    TIntermTraverser() : 
        visitSymbol(0), 
        visitConstantUnion(0),
        visitBinary(0),
        visitUnary(0),
        visitSelection(0),
        visitAggregate(0),
        visitLoop(0),
        visitBranch(0),
        visitSwitch(0),
        depth(0),
        preVisit(true),
        postVisit(false),
        rightToLeft(false) {}

    void (*visitSymbol)(TIntermSymbol*, TIntermTraverser*);
    void (*visitConstantUnion)(TIntermConstantUnion*, TIntermTraverser*);
    bool (*visitBinary)(bool preVisit, TIntermBinary*, TIntermTraverser*);
    bool (*visitUnary)(bool preVisit, TIntermUnary*, TIntermTraverser*);
    bool (*visitSelection)(bool preVisit, TIntermSelection*, TIntermTraverser*);
    bool (*visitAggregate)(bool preVisit, TIntermAggregate*, TIntermTraverser*);
    bool (*visitLoop)(bool preVisit, TIntermLoop*, TIntermTraverser*);
    bool (*visitBranch)(bool preVisit, TIntermBranch*,  TIntermTraverser*);
    bool (*visitSwitch)(bool preVisit, TIntermSwitch*,  TIntermTraverser*);

    int  depth;
    bool preVisit;
    bool postVisit;
    bool rightToLeft;
};

} // end namespace glslang

#endif // __INTERMEDIATE_H
