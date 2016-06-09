//
//Copyright (C) 2016 Google, Inc.
//Copyright (C) 2016 LunarG, Inc.
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
//    Neither the name of Google, Inc., nor the names of its
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
// This is a set of mutually recursive methods implementing the HLSL grammar.
// Generally, each returns
//  - through an argument: a type specifically appropriate to which rule it
//    recognized
//  - through the return value: true/false to indicate whether or not it
//    recognized its rule
//
// As much as possible, only grammar recognition should happen in this file,
// with all other work being farmed out to hlslParseHelper.cpp, which in turn
// will build the AST.
//
// The next token, yet to be "accepted" is always sitting in 'token'.
// When a method says it accepts a rule, that means all tokens involved
// in the rule will have been consumed, and none left in 'token'.
//

#include "hlslTokens.h"
#include "hlslGrammar.h"

namespace glslang {

// Root entry point to this recursive decent parser.
// Return true if compilation unit was successfully accepted.
bool HlslGrammar::parse()
{
    advanceToken();
    return acceptCompilationUnit();
}

void HlslGrammar::expected(const char* syntax)
{
    parseContext.error(token.loc, "Expected", syntax, "");
}

// Only process the next token if it is an identifier.
// Return true if it was an identifier.
bool HlslGrammar::acceptIdentifier(HlslToken& idToken)
{
    if (peekTokenClass(EHTokIdentifier)) {
        idToken = token;
        advanceToken();
        return true;
    }

    return false;
}

// compilationUnit
//      : list of externalDeclaration
//
bool HlslGrammar::acceptCompilationUnit()
{
    TIntermNode* unitNode = nullptr;

    while (! peekTokenClass(EHTokNone)) {
        // externalDeclaration
        TIntermNode* declarationNode;
        if (! acceptDeclaration(declarationNode))
            return false;

        // hook it up
        unitNode = intermediate.growAggregate(unitNode, declarationNode);
    }

    // set root of AST
    intermediate.setTreeRoot(unitNode);

    return true;
}

// declaration
//      : SEMICOLON
//      : fully_specified_type SEMICOLON
//      | fully_specified_type identifier SEMICOLON
//      | fully_specified_type identifier = expression SEMICOLON
//      | fully_specified_type identifier function_parameters SEMICOLON                          // function prototype
//      | fully_specified_type identifier function_parameters COLON semantic compound_statement  // function definition
//
// 'node' could get created if the declaration creates code, like an initializer
// or a function body.
//
bool HlslGrammar::acceptDeclaration(TIntermNode*& node)
{
    node = nullptr;

    // fully_specified_type
    TType type;
    if (! acceptFullySpecifiedType(type))
        return false;

    // identifier
    HlslToken idToken;
    if (acceptIdentifier(idToken)) {
        // = expression
        TIntermTyped* expressionNode = nullptr;
        if (acceptTokenClass(EHTokAssign)) {
            if (! acceptExpression(expressionNode)) {
                expected("initializer");
                return false;
            }
        }

        // SEMICOLON
        if (acceptTokenClass(EHTokSemicolon)) {
            node = parseContext.declareVariable(idToken.loc, *idToken.string, type, 0, expressionNode);
            return true;
        }

        // function_parameters
        TFunction* function = new TFunction(idToken.string, type);
        if (acceptFunctionParameters(*function)) {
            // COLON semantic
            acceptSemantic();

            // compound_statement
            if (peekTokenClass(EHTokLeftBrace))
                return acceptFunctionDefinition(*function, node);

            // SEMICOLON
            if (acceptTokenClass(EHTokSemicolon))
                return true;

            return false;
        }
    }

    // SEMICOLON
    if (acceptTokenClass(EHTokSemicolon))
        return true;

    return true;
}

// fully_specified_type
//      : type_specifier
//      | type_qualifier type_specifier
//
bool HlslGrammar::acceptFullySpecifiedType(TType& type)
{
    // type_qualifier
    TQualifier qualifier;
    qualifier.clear();
    acceptQualifier(qualifier);

    // type_specifier
    if (! acceptType(type))
        return false;
    type.getQualifier() = qualifier;

    return true;
}

// If token is a qualifier, return its token class and advance to the next
// qualifier.  Otherwise, return false, and don't advance.
void HlslGrammar::acceptQualifier(TQualifier& qualifier)
{
    switch (peek()) {
    case EHTokUniform:
        qualifier.storage = EvqUniform;
        break;
    case EHTokConst:
        qualifier.storage = EvqConst;
        break;
    default:
        return;
    }

    advanceToken();
}

// If token is for a type, update 'type' with the type information,
// and return true and advance.
// Otherwise, return false, and don't advance
bool HlslGrammar::acceptType(TType& type)
{
    switch (peek()) {
    case EHTokVoid:
        new(&type) TType(EbtVoid);
        break;

    case EHTokFloat:
        new(&type) TType(EbtFloat);
        break;
    case EHTokFloat1:
        new(&type) TType(EbtFloat);
        type.makeVector();
        break;
    case EHTokFloat2:
        new(&type) TType(EbtFloat, EvqTemporary, 2);
        break;
    case EHTokFloat3:
        new(&type) TType(EbtFloat, EvqTemporary, 3);
        break;
    case EHTokFloat4:
        new(&type) TType(EbtFloat, EvqTemporary, 4);
        break;

    case EHTokDouble:
        new(&type) TType(EbtDouble);
        break;
    case EHTokDouble1:
        new(&type) TType(EbtDouble);
        type.makeVector();
        break;
    case EHTokDouble2:
        new(&type) TType(EbtDouble, EvqTemporary, 2);
        break;
    case EHTokDouble3:
        new(&type) TType(EbtDouble, EvqTemporary, 3);
        break;
    case EHTokDouble4:
        new(&type) TType(EbtDouble, EvqTemporary, 4);
        break;

    case EHTokInt:
    case EHTokDword:
        new(&type) TType(EbtInt);
        break;
    case EHTokInt1:
        new(&type) TType(EbtInt);
        type.makeVector();
        break;
    case EHTokInt2:
        new(&type) TType(EbtInt, EvqTemporary, 2);
        break;
    case EHTokInt3:
        new(&type) TType(EbtInt, EvqTemporary, 3);
        break;
    case EHTokInt4:
        new(&type) TType(EbtInt, EvqTemporary, 4);
        break;

    case EHTokUint:
        new(&type) TType(EbtUint);
        break;
    case EHTokUint1:
        new(&type) TType(EbtUint);
        type.makeVector();
        break;
    case EHTokUint2:
        new(&type) TType(EbtUint, EvqTemporary, 2);
        break;
    case EHTokUint3:
        new(&type) TType(EbtUint, EvqTemporary, 3);
        break;
    case EHTokUint4:
        new(&type) TType(EbtUint, EvqTemporary, 4);
        break;

    case EHTokBool:
        new(&type) TType(EbtBool);
        break;
    case EHTokBool1:
        new(&type) TType(EbtBool);
        type.makeVector();
        break;
    case EHTokBool2:
        new(&type) TType(EbtBool, EvqTemporary, 2);
        break;
    case EHTokBool3:
        new(&type) TType(EbtBool, EvqTemporary, 3);
        break;
    case EHTokBool4:
        new(&type) TType(EbtBool, EvqTemporary, 4);
        break;

    case EHTokInt1x1:
        new(&type) TType(EbtInt, EvqTemporary, 0, 1, 1);
        break;
    case EHTokInt1x2:
        new(&type) TType(EbtInt, EvqTemporary, 0, 2, 1);
        break;
    case EHTokInt1x3:
        new(&type) TType(EbtInt, EvqTemporary, 0, 3, 1);
        break;
    case EHTokInt1x4:
        new(&type) TType(EbtInt, EvqTemporary, 0, 4, 1);
        break;
    case EHTokInt2x1:
        new(&type) TType(EbtInt, EvqTemporary, 0, 1, 2);
        break;
    case EHTokInt2x2:
        new(&type) TType(EbtInt, EvqTemporary, 0, 2, 2);
        break;
    case EHTokInt2x3:
        new(&type) TType(EbtInt, EvqTemporary, 0, 3, 2);
        break;
    case EHTokInt2x4:
        new(&type) TType(EbtInt, EvqTemporary, 0, 4, 2);
        break;
    case EHTokInt3x1:
        new(&type) TType(EbtInt, EvqTemporary, 0, 1, 3);
        break;
    case EHTokInt3x2:
        new(&type) TType(EbtInt, EvqTemporary, 0, 2, 3);
        break;
    case EHTokInt3x3:
        new(&type) TType(EbtInt, EvqTemporary, 0, 3, 3);
        break;
    case EHTokInt3x4:
        new(&type) TType(EbtInt, EvqTemporary, 0, 4, 3);
        break;
    case EHTokInt4x1:
        new(&type) TType(EbtInt, EvqTemporary, 0, 1, 4);
        break;
    case EHTokInt4x2:
        new(&type) TType(EbtInt, EvqTemporary, 0, 2, 4);
        break;
    case EHTokInt4x3:
        new(&type) TType(EbtInt, EvqTemporary, 0, 3, 4);
        break;
    case EHTokInt4x4:
        new(&type) TType(EbtInt, EvqTemporary, 0, 4, 4);
        break;

    case EHTokUint1x1:
        new(&type) TType(EbtUint, EvqTemporary, 0, 1, 1);
        break;
    case EHTokUint1x2:
        new(&type) TType(EbtUint, EvqTemporary, 0, 2, 1);
        break;
    case EHTokUint1x3:
        new(&type) TType(EbtUint, EvqTemporary, 0, 3, 1);
        break;
    case EHTokUint1x4:
        new(&type) TType(EbtUint, EvqTemporary, 0, 4, 1);
        break;
    case EHTokUint2x1:
        new(&type) TType(EbtUint, EvqTemporary, 0, 1, 2);
        break;
    case EHTokUint2x2:
        new(&type) TType(EbtUint, EvqTemporary, 0, 2, 2);
        break;
    case EHTokUint2x3:
        new(&type) TType(EbtUint, EvqTemporary, 0, 3, 2);
        break;
    case EHTokUint2x4:
        new(&type) TType(EbtUint, EvqTemporary, 0, 4, 2);
        break;
    case EHTokUint3x1:
        new(&type) TType(EbtUint, EvqTemporary, 0, 1, 3);
        break;
    case EHTokUint3x2:
        new(&type) TType(EbtUint, EvqTemporary, 0, 2, 3);
        break;
    case EHTokUint3x3:
        new(&type) TType(EbtUint, EvqTemporary, 0, 3, 3);
        break;
    case EHTokUint3x4:
        new(&type) TType(EbtUint, EvqTemporary, 0, 4, 3);
        break;
    case EHTokUint4x1:
        new(&type) TType(EbtUint, EvqTemporary, 0, 1, 4);
        break;
    case EHTokUint4x2:
        new(&type) TType(EbtUint, EvqTemporary, 0, 2, 4);
        break;
    case EHTokUint4x3:
        new(&type) TType(EbtUint, EvqTemporary, 0, 3, 4);
        break;
    case EHTokUint4x4:
        new(&type) TType(EbtUint, EvqTemporary, 0, 4, 4);
        break;

    case EHTokBool1x1:
        new(&type) TType(EbtBool, EvqTemporary, 0, 1, 1);
        break;
    case EHTokBool1x2:
        new(&type) TType(EbtBool, EvqTemporary, 0, 2, 1);
        break;
    case EHTokBool1x3:
        new(&type) TType(EbtBool, EvqTemporary, 0, 3, 1);
        break;
    case EHTokBool1x4:
        new(&type) TType(EbtBool, EvqTemporary, 0, 4, 1);
        break;
    case EHTokBool2x1:
        new(&type) TType(EbtBool, EvqTemporary, 0, 1, 2);
        break;
    case EHTokBool2x2:
        new(&type) TType(EbtBool, EvqTemporary, 0, 2, 2);
        break;
    case EHTokBool2x3:
        new(&type) TType(EbtBool, EvqTemporary, 0, 3, 2);
        break;
    case EHTokBool2x4:
        new(&type) TType(EbtBool, EvqTemporary, 0, 4, 2);
        break;
    case EHTokBool3x1:
        new(&type) TType(EbtBool, EvqTemporary, 0, 1, 3);
        break;
    case EHTokBool3x2:
        new(&type) TType(EbtBool, EvqTemporary, 0, 2, 3);
        break;
    case EHTokBool3x3:
        new(&type) TType(EbtBool, EvqTemporary, 0, 3, 3);
        break;
    case EHTokBool3x4:
        new(&type) TType(EbtBool, EvqTemporary, 0, 4, 3);
        break;
    case EHTokBool4x1:
        new(&type) TType(EbtBool, EvqTemporary, 0, 1, 4);
        break;
    case EHTokBool4x2:
        new(&type) TType(EbtBool, EvqTemporary, 0, 2, 4);
        break;
    case EHTokBool4x3:
        new(&type) TType(EbtBool, EvqTemporary, 0, 3, 4);
        break;
    case EHTokBool4x4:
        new(&type) TType(EbtBool, EvqTemporary, 0, 4, 4);
        break;

    case EHTokFloat1x1:
        new(&type) TType(EbtFloat, EvqTemporary, 0, 1, 1);
        break;
    case EHTokFloat1x2:
        new(&type) TType(EbtFloat, EvqTemporary, 0, 2, 1);
        break;
    case EHTokFloat1x3:
        new(&type) TType(EbtFloat, EvqTemporary, 0, 3, 1);
        break;
    case EHTokFloat1x4:
        new(&type) TType(EbtFloat, EvqTemporary, 0, 4, 1);
        break;
    case EHTokFloat2x1:
        new(&type) TType(EbtFloat, EvqTemporary, 0, 1, 2);
        break;
    case EHTokFloat2x2:
        new(&type) TType(EbtFloat, EvqTemporary, 0, 2, 2);
        break;
    case EHTokFloat2x3:
        new(&type) TType(EbtFloat, EvqTemporary, 0, 3, 2);
        break;
    case EHTokFloat2x4:
        new(&type) TType(EbtFloat, EvqTemporary, 0, 4, 2);
        break;
    case EHTokFloat3x1:
        new(&type) TType(EbtFloat, EvqTemporary, 0, 1, 3);
        break;
    case EHTokFloat3x2:
        new(&type) TType(EbtFloat, EvqTemporary, 0, 2, 3);
        break;
    case EHTokFloat3x3:
        new(&type) TType(EbtFloat, EvqTemporary, 0, 3, 3);
        break;
    case EHTokFloat3x4:
        new(&type) TType(EbtFloat, EvqTemporary, 0, 4, 3);
        break;
    case EHTokFloat4x1:
        new(&type) TType(EbtFloat, EvqTemporary, 0, 1, 4);
        break;
    case EHTokFloat4x2:
        new(&type) TType(EbtFloat, EvqTemporary, 0, 2, 4);
        break;
    case EHTokFloat4x3:
        new(&type) TType(EbtFloat, EvqTemporary, 0, 3, 4);
        break;
    case EHTokFloat4x4:
        new(&type) TType(EbtFloat, EvqTemporary, 0, 4, 4);
        break;

    case EHTokDouble1x1:
        new(&type) TType(EbtDouble, EvqTemporary, 0, 1, 1);
        break;
    case EHTokDouble1x2:
        new(&type) TType(EbtDouble, EvqTemporary, 0, 2, 1);
        break;
    case EHTokDouble1x3:
        new(&type) TType(EbtDouble, EvqTemporary, 0, 3, 1);
        break;
    case EHTokDouble1x4:
        new(&type) TType(EbtDouble, EvqTemporary, 0, 4, 1);
        break;
    case EHTokDouble2x1:
        new(&type) TType(EbtDouble, EvqTemporary, 0, 1, 2);
        break;
    case EHTokDouble2x2:
        new(&type) TType(EbtDouble, EvqTemporary, 0, 2, 2);
        break;
    case EHTokDouble2x3:
        new(&type) TType(EbtDouble, EvqTemporary, 0, 3, 2);
        break;
    case EHTokDouble2x4:
        new(&type) TType(EbtDouble, EvqTemporary, 0, 4, 2);
        break;
    case EHTokDouble3x1:
        new(&type) TType(EbtDouble, EvqTemporary, 0, 1, 3);
        break;
    case EHTokDouble3x2:
        new(&type) TType(EbtDouble, EvqTemporary, 0, 2, 3);
        break;
    case EHTokDouble3x3:
        new(&type) TType(EbtDouble, EvqTemporary, 0, 3, 3);
        break;
    case EHTokDouble3x4:
        new(&type) TType(EbtDouble, EvqTemporary, 0, 4, 3);
        break;
    case EHTokDouble4x1:
        new(&type) TType(EbtDouble, EvqTemporary, 0, 1, 4);
        break;
    case EHTokDouble4x2:
        new(&type) TType(EbtDouble, EvqTemporary, 0, 2, 4);
        break;
    case EHTokDouble4x3:
        new(&type) TType(EbtDouble, EvqTemporary, 0, 3, 4);
        break;
    case EHTokDouble4x4:
        new(&type) TType(EbtDouble, EvqTemporary, 0, 4, 4);
        break;

    default:
        return false;
    }

    advanceToken();

    return true;
}

// function_parameters
//      : LEFT_PAREN parameter_declaration COMMA parameter_declaration ... RIGHT_PAREN
//      | LEFT_PAREN VOID RIGHT_PAREN
//
bool HlslGrammar::acceptFunctionParameters(TFunction& function)
{
    // LEFT_PAREN
    if (! acceptTokenClass(EHTokLeftParen))
        return false;

    // VOID RIGHT_PAREN
    if (! acceptTokenClass(EHTokVoid)) {
        do {
            // parameter_declaration
            if (! acceptParameterDeclaration(function))
                break;

            // COMMA
            if (! acceptTokenClass(EHTokComma))
                break;
        } while (true);
    }

    // RIGHT_PAREN
    if (! acceptTokenClass(EHTokRightParen)) {
        expected(")");
        return false;
    }

    return true;
}

// parameter_declaration
//      : fully_specified_type
//      | fully_specified_type identifier
//
bool HlslGrammar::acceptParameterDeclaration(TFunction& function)
{
    // fully_specified_type
    TType* type = new TType;
    if (! acceptFullySpecifiedType(*type))
        return false;

    // identifier
    HlslToken idToken;
    acceptIdentifier(idToken);

    TParameter param = { idToken.string, type };
    function.addParameter(param);

    return true;
}

// Do the work to create the function definition in addition to
// parsing the body (compound_statement).
bool HlslGrammar::acceptFunctionDefinition(TFunction& function, TIntermNode*& node)
{
    TFunction* functionDeclarator = parseContext.handleFunctionDeclarator(token.loc, function, false /* not prototype */);

    // This does a pushScope()
    node = parseContext.handleFunctionDefinition(token.loc, *functionDeclarator);

    // compound_statement
    TIntermNode* functionBody = nullptr;
    if (acceptCompoundStatement(functionBody)) {
        node = intermediate.growAggregate(node, functionBody);
        intermediate.setAggregateOperator(node, EOpFunction, functionDeclarator->getType(), token.loc);
        node->getAsAggregate()->setName(functionDeclarator->getMangledName().c_str());
        parseContext.popScope();

        return true;
    }

    return false;
}

// Accept an expression with parenthesis around it, where
// the parenthesis ARE NOT expression parenthesis, but the
// syntactically required ones like in "if ( expression )"
//
// Note this one is not set up to be speculative; as it gives
// errors if not found.
//
bool HlslGrammar::acceptParenExpression(TIntermTyped*& expression)
{
    // LEFT_PAREN
    if (! acceptTokenClass(EHTokLeftParen))
        expected("(");

    if (! acceptExpression(expression)) {
        expected("expression");
        return false;
    }

    // RIGHT_PAREN
    if (! acceptTokenClass(EHTokRightParen))
        expected(")");

    return true;
}

// The top-level full expression recognizer.
//
// expression
//      : assignment_expression COMMA assignment_expression COMMA assignment_expression ...
//
bool HlslGrammar::acceptExpression(TIntermTyped*& node)
{
    node = nullptr;

    // assignment_expression
    if (! acceptAssignmentExpression(node))
        return false;

    if (! peekTokenClass(EHTokComma))
        return true;

    do {
        // ... COMMA
        TSourceLoc loc = token.loc;
        advanceToken();

        // ... assignment_expression
        TIntermTyped* rightNode = nullptr;
        if (! acceptAssignmentExpression(rightNode)) {
            expected("assignment expression");
            return false;
        }

        node = intermediate.addComma(node, rightNode, loc);

        if (! peekTokenClass(EHTokComma))
            return true;
    } while (true);
}

// Accept an assignment expression, where assignment operations
// associate right-to-left.  This is, it is implicit, for example
//
//    a op (b op (c op d))
//
// assigment_expression
//      : binary_expression op binary_expression op binary_expression ...
//
bool HlslGrammar::acceptAssignmentExpression(TIntermTyped*& node)
{
    if (! acceptBinaryExpression(node, PlLogicalOr))
        return false;

    TOperator assignOp = HlslOpMap::assignment(peek());
    if (assignOp == EOpNull)
        return true;

    // ... op
    TSourceLoc loc = token.loc;
    advanceToken();

    // ... binary_expression
    // But, done by recursing this function, which automatically
    // gets the right-to-left associativity.
    TIntermTyped* rightNode = nullptr;
    if (! acceptAssignmentExpression(rightNode)) {
        expected("assignment expression");
        return false;
    }

    node = intermediate.addAssign(assignOp, node, rightNode, loc);

    if (! peekTokenClass(EHTokComma))
        return true;

    return true;
}

// Accept a binary expression, for binary operations that
// associate left-to-right.  This is, it is implicit, for example
//
//    ((a op b) op c) op d
//
// binary_expression
//      : expression op expression op expression ...
//
// where 'expression' is the next higher level in precedence.
//
bool HlslGrammar::acceptBinaryExpression(TIntermTyped*& node, PrecedenceLevel precedenceLevel)
{
    if (precedenceLevel > PlMul)
        return acceptUnaryExpression(node);

    // assignment_expression
    if (! acceptBinaryExpression(node, (PrecedenceLevel)(precedenceLevel + 1)))
        return false;

    TOperator op = HlslOpMap::binary(peek());
    PrecedenceLevel tokenLevel = HlslOpMap::precedenceLevel(op);
    if (tokenLevel < precedenceLevel)
        return true;

    do {
        // ... op
        TSourceLoc loc = token.loc;
        advanceToken();

        // ... expression
        TIntermTyped* rightNode = nullptr;
        if (! acceptBinaryExpression(rightNode, (PrecedenceLevel)(precedenceLevel + 1))) {
            expected("expression");
            return false;
        }

        node = intermediate.addBinaryMath(op, node, rightNode, loc);

        if (! peekTokenClass(EHTokComma))
            return true;
    } while (true);
}

// unary_expression
//      : (type) unary_expression
//      | + unary_expression
//      | - unary_expression
//      | ! unary_expression
//      | ~ unary_expression
//      | ++ unary_expression
//      | -- unary_expression
//      | postfix_expression
//
bool HlslGrammar::acceptUnaryExpression(TIntermTyped*& node)
{
    // (type) unary_expression
    // Have to look two steps ahead, because this could be, e.g., a
    // postfix_expression instead, since that also starts with at "(".
    if (acceptTokenClass(EHTokLeftParen)) {
        TType castType;
        if (acceptType(castType)) {
            if (! acceptTokenClass(EHTokRightParen)) {
                expected(")");
                return false;
            }

            // We've matched "(type)" now, get the expression to cast
            TSourceLoc loc = token.loc;
            if (! acceptUnaryExpression(node))
                return false;

            // Hook it up like a constructor
            TFunction* constructorFunction = parseContext.handleConstructorCall(loc, castType);
            if (constructorFunction == nullptr) {
                expected("type that can be constructed");
                return false;
            }
            TIntermTyped* arguments = nullptr;
            parseContext.handleFunctionArgument(constructorFunction, arguments, node);
            node = parseContext.handleFunctionCall(loc, constructorFunction, arguments);

            return true;
        } else {
            // This isn't a type cast, but it still started "(", so if it is a
            // unary expression, it can only be a postfix_expression, so try that.
            // Back it up first.
            recedeToken();
            return acceptPostfixExpression(node);
        }
    }

    // peek for "op unary_expression"
    TOperator unaryOp = HlslOpMap::preUnary(peek());
    
    // postfix_expression (if no unary operator)
    if (unaryOp == EOpNull)
        return acceptPostfixExpression(node);

    // op unary_expression
    TSourceLoc loc = token.loc;
    advanceToken();
    if (! acceptUnaryExpression(node))
        return false;

    // + is a no-op
    if (unaryOp == EOpAdd)
        return true;

    node = intermediate.addUnaryMath(unaryOp, node, loc);

    return node != nullptr;
}

// postfix_expression
//      : LEFT_PAREN expression RIGHT_PAREN
//      | literal
//      | constructor
//      | identifier
//      | function_call
//      | postfix_expression LEFT_BRACKET integer_expression RIGHT_BRACKET
//      | postfix_expression DOT IDENTIFIER
//      | postfix_expression INC_OP
//      | postfix_expression DEC_OP
//
bool HlslGrammar::acceptPostfixExpression(TIntermTyped*& node)
{
    // Not implemented as self-recursive:
    // The logical "right recursion" is done with an loop at the end

    // idToken will pick up either a variable or a function name in a function call
    HlslToken idToken;

    // Find something before the postfix operations, as they can't operate
    // on nothing.  So, no "return true", they fall through, only "return false".
    if (acceptTokenClass(EHTokLeftParen)) {
        // LEFT_PAREN expression RIGHT_PAREN
        if (! acceptExpression(node)) {
            expected("expression");
            return false;
        }
        if (! acceptTokenClass(EHTokRightParen)) {
            expected(")");
            return false;
        }
    } else if (acceptLiteral(node)) {
        // literal (nothing else to do yet), go on to the 
    } else if (acceptConstructor(node)) {
        // constructor (nothing else to do yet)
    } else if (acceptIdentifier(idToken)) {
        // identifier or function_call name
        if (! peekTokenClass(EHTokLeftParen)) {
            node = parseContext.handleVariable(idToken.loc, token.string);
        } else if (acceptFunctionCall(idToken, node)) {
            // function_call (nothing else to do yet)
        } else {
            expected("function call arguments");
            return false;
        }
    } else {
        // nothing found, can't post operate
        return false;
    }

    // Something was found, chain as many postfix operations as exist.
    do {
        TSourceLoc loc = token.loc;
        TOperator postOp = HlslOpMap::postUnary(peek());

        // Consume only a valid post-unary operator, otherwise we are done.
        switch (postOp) {
        case EOpIndexDirectStruct:
        case EOpIndexIndirect:
        case EOpPostIncrement:
        case EOpPostDecrement:
            advanceToken();
            break;
        default:
            return true;
        }

        // We have a valid post-unary operator, process it.
        switch (postOp) {
        case EOpIndexDirectStruct:
            // todo
            break;
        case EOpIndexIndirect:
        {
            TIntermTyped* indexNode = nullptr;
            if (! acceptExpression(indexNode) ||
                ! peekTokenClass(EHTokRightBracket)) {
                expected("expression followed by ']'");
                return false;
            }
            // todo:      node = intermediate.addBinaryMath(
        }
        case EOpPostIncrement:
        case EOpPostDecrement:
            node = intermediate.addUnaryMath(postOp, node, loc);
            break;
        default:
            assert(0);
            break;
        }
    } while (true);
}

// constructor
//      : type argument_list
//
bool HlslGrammar::acceptConstructor(TIntermTyped*& node)
{
    // type
    TType type;
    if (acceptType(type)) {
        TFunction* constructorFunction = parseContext.handleConstructorCall(token.loc, type);
        if (constructorFunction == nullptr)
            return false;

        // arguments
        TIntermTyped* arguments = nullptr;
        if (! acceptArguments(constructorFunction, arguments)) {
            expected("constructor arguments");
            return false;
        }

        // hook it up
        node = parseContext.handleFunctionCall(arguments->getLoc(), constructorFunction, arguments);

        return true;
    }

    return false;
}

// Handle intrinsics that require simple decompositions to AST
//
void HlslGrammar::decomposeIntrinsic(HlslToken idToken, TIntermTyped*& node, TIntermTyped* arguments)
{
    // HLSL intrinsics can be pass through to native AST opcodes, or decomposed here to existing AST
    // opcodes for compatibility with existing software stacks.
    static const bool decomposeHlslIntrinsics = true;

    if (!decomposeHlslIntrinsics || !node->getAsOperator())
        return;
    
    const TIntermAggregate* argAggregate = arguments ? arguments->getAsAggregate() : nullptr;
    TIntermAggregate* fnAggregate = node->getAsAggregate();
    TIntermUnary*     fnUnary     = node->getAsUnaryNode();

    const TOperator  op = node->getAsOperator()->getOp();

    switch (op) {
    case EOpGenMul:
        {
            // mul(a,b) -> MatrixTimesMatrix, MatrixTimesVector, MatrixTimesScalar, VectorTimesScalar, Dot, Mul
            TIntermTyped* arg0 = argAggregate->getSequence()[0]->getAsTyped();
            TIntermTyped* arg1 = argAggregate->getSequence()[1]->getAsTyped();

            TIntermTyped* mul = nullptr;

            if (arg0->isMatrix() && arg1->isMatrix()) {             // mat * mat
                mul = new TIntermBinary(EOpMatrixTimesMatrix);
            } else if (arg0->isMatrix() && arg1->isVector()) {      // mat * vec
                mul = new TIntermBinary(EOpMatrixTimesVector);
            } else if (arg0->isVector() && arg1->isMatrix()) {      // vec * mat
                mul = new TIntermBinary(EOpVectorTimesMatrix);
            } else if (arg0->isVector() && arg1->isScalar()) {      // vec * scalar
                mul = new TIntermBinary(EOpVectorTimesScalar);
            } else if (arg0->isScalar() && arg1->isVector()) {      // scalar * vec
                mul = new TIntermBinary(EOpVectorTimesScalar);
                std::swap(arg0, arg1);
            } else if (arg0->isMatrix() && arg1->isScalar()) {      // mat * scalar
                mul = new TIntermBinary(EOpMatrixTimesScalar);
            } else if (arg0->isScalar() && arg1->isMatrix()) {      // scalar * mat
                mul = new TIntermBinary(EOpMatrixTimesScalar);
                std::swap(arg0, arg1);
            } else if (arg0->isVector() && arg1->isVector()) {      // vec * vec
                fnAggregate->setOperator(EOpDot);
                mul = fnAggregate;
            } else if (arg0->isScalar() && arg1->isScalar()) {      // scalar * scalar
                mul = new TIntermBinary(EOpMul);
            } else {
                expected("types in mul()");
            }

            if (mul->getAsBinaryNode()) {
                mul->getAsBinaryNode()->setLeft(arg0);
                mul->getAsBinaryNode()->setRight(arg1);
            }

            mul->setType(node->getType());
            mul->setLoc(idToken.loc);
            node = mul;

            break;
        }

    case EOpRcp:
        {
            // rcp(a) -> 1 / a

            TIntermTyped* arg0 = fnUnary->getOperand();
            TBasicType   type0 = arg0->getBasicType();
            TIntermTyped* div = new TIntermBinary(EOpDiv);
            div->getAsBinaryNode()->setLeft(intermediate.addConstantUnion(1, type0, idToken.loc, true));
            div->getAsBinaryNode()->setRight(arg0);
            div->setLoc(idToken.loc);

            div->setType(node->getType());
            node = div;

            break;
        }

    case EOpSaturate:
        {
            // saturate(a) -> clamp(a,0,1)

            TIntermTyped* arg0 = fnUnary->getOperand();
            TBasicType   type0 = arg0->getBasicType();
            TIntermTyped* clamp = new TIntermAggregate(EOpClamp);
            clamp->getAsAggregate()->getSequence().push_back(arg0);
            clamp->getAsAggregate()->getSequence().push_back(intermediate.addConstantUnion(0, type0, idToken.loc, true));
            clamp->getAsAggregate()->getSequence().push_back(intermediate.addConstantUnion(1, type0, idToken.loc, true));
            clamp->setLoc(idToken.loc);

            clamp->setType(node->getType());
            node = clamp;

            break;
        }

    case EOpSinCos:
        {
            // sincos(a,b,c) -> b = sin(a), c = cos(a)

            TIntermTyped* arg0 = argAggregate->getSequence()[0]->getAsTyped();
            TIntermTyped* arg1 = argAggregate->getSequence()[1]->getAsTyped();
            TIntermTyped* arg2 = argAggregate->getSequence()[2]->getAsTyped();

            TIntermAggregate* compoundStatement = nullptr;
            TIntermUnary*     sinStatement      = new TIntermUnary(EOpSin);
            TIntermUnary*     cosStatement      = new TIntermUnary(EOpCos);
            TIntermBinary*    sinAssign         = new TIntermBinary(EOpAssign);
            TIntermBinary*    cosAssign         = new TIntermBinary(EOpAssign);

            sinStatement->setOperand(arg0);    // create sin
            sinStatement->setLoc(idToken.loc);
            sinStatement->setType(arg0->getType());
            sinAssign->setLeft(arg1);
            sinAssign->setRight(sinStatement);
            sinAssign->setLoc(idToken.loc);
            sinAssign->setType(arg0->getType());

            cosStatement->setOperand(arg0);    // create cos
            cosStatement->setLoc(idToken.loc);
            cosStatement->setType(arg0->getType());
            cosAssign->setLeft(arg2);
            cosAssign->setRight(cosStatement);
            cosAssign->setLoc(idToken.loc);
            cosAssign->setType(arg0->getType());

            compoundStatement = intermediate.growAggregate(compoundStatement, sinAssign);
            compoundStatement = intermediate.growAggregate(compoundStatement, cosAssign);
            compoundStatement->setOperator(EOpSequence);
            compoundStatement->setLoc(idToken.loc);

            node = compoundStatement;

            break;
        }

    case EOpClip:
        {
            // clip(a) -> if (any(a<0)) discard;

            TIntermTyped*  arg0 = fnUnary->getOperand();
            TBasicType     type0 = arg0->getBasicType();
            TIntermTyped*  compareNode = nullptr;

            // For non-scalars: per experiments with FXC compiler, discard if ANY < 0.
            if (!arg0->isScalar()) {
                TIntermAggregate* lessNode = new TIntermAggregate(EOpLessThan);

                // compare: a < 0
                lessNode->getSequence().push_back(arg0);
                lessNode->setLoc(idToken.loc);

                // make array of bools matching dimensions of input type
                lessNode->setType(TType(EbtBool, EvqTemporary, 
                                        arg0->getType().getVectorSize(),
                                        arg0->getType().getMatrixCols(),
                                        arg0->getType().getMatrixRows()));

                compareNode = new TIntermUnary(EOpAny);
                compareNode->getAsUnaryNode()->setOperand(lessNode);
                compareNode->setLoc(idToken.loc);

                // calculate # of components for comparison const.
                const int constComponentCount = 
                    std::max(arg0->getType().getVectorSize(), 1) *
                    std::max(arg0->getType().getMatrixCols(), 1) *
                    std::max(arg0->getType().getMatrixRows(), 1);


                TConstUnion zero;
                zero.setDConst(0.0);
                TConstUnionArray zeros(constComponentCount, zero);

                lessNode->getSequence().push_back(intermediate.addConstantUnion(zeros, arg0->getType(), idToken.loc, true));
            } else {
                TIntermBinary* lessNode = new TIntermBinary(EOpLessThan);
                lessNode->setLeft(arg0);
                lessNode->setLoc(idToken.loc);
                
                lessNode->setRight(intermediate.addConstantUnion(0, type0, idToken.loc, true));

                compareNode = lessNode;
            }

            compareNode->setType(TType(EbtBool));
            
            TIntermBranch* killNode = new TIntermBranch(EOpKill, nullptr);
            killNode->setLoc(idToken.loc);

            node = new TIntermSelection(compareNode, killNode, nullptr);
            node->setLoc(idToken.loc);
            
            break;
        }

    case EOpLog10:
        {
            // log10(a) -> log2(a) * 0.301029995663981  (== 1/log2(10))
            TIntermTyped*  arg0 = fnUnary->getOperand();

            TIntermUnary* log2Node = new TIntermUnary(EOpLog2);
            log2Node->setOperand(arg0);
            log2Node->setLoc(idToken.loc);
            log2Node->setType(node->getType());

            TIntermTyped* mul = new TIntermBinary(EOpMul);
            mul->getAsBinaryNode()->setLeft(log2Node);
            mul->getAsBinaryNode()->setRight(intermediate.addConstantUnion(0.301029995663981f, EbtFloat, idToken.loc, true));
            mul->setLoc(idToken.loc);

            mul->setType(node->getType());
            node = mul;

            break;
        }

    default:
        break; // most pass through unchanged
    }
}


// The function_call identifier was already recognized, and passed in as idToken.
//
// function_call
//      : [idToken] arguments
//
bool HlslGrammar::acceptFunctionCall(HlslToken idToken, TIntermTyped*& node)
{
    // arguments
    TFunction* function = new TFunction(idToken.string, TType(EbtVoid));
    TIntermTyped* arguments = nullptr;
    if (! acceptArguments(function, arguments))
        return false;

    node = parseContext.handleFunctionCall(idToken.loc, function, arguments);

    decomposeIntrinsic(idToken, node, arguments);
    
    return true;
}

// arguments
//      : LEFT_PAREN expression COMMA expression COMMA ... RIGHT_PAREN
//
// The arguments are pushed onto the 'function' argument list and
// onto the 'arguments' aggregate.
//
bool HlslGrammar::acceptArguments(TFunction* function, TIntermTyped*& arguments)
{
    // LEFT_PAREN
    if (! acceptTokenClass(EHTokLeftParen))
        return false;

    do {
        // expression
        TIntermTyped* arg;
        if (! acceptAssignmentExpression(arg))
            break;

        // hook it up
        parseContext.handleFunctionArgument(function, arguments, arg);

        // COMMA
        if (! acceptTokenClass(EHTokComma))
            break;
    } while (true);

    // RIGHT_PAREN
    if (! acceptTokenClass(EHTokRightParen)) {
        expected(")");
        return false;
    }

    return true;
}

bool HlslGrammar::acceptLiteral(TIntermTyped*& node)
{
    switch (token.tokenClass) {
    case EHTokIntConstant:
        node = intermediate.addConstantUnion(token.i, token.loc, true);
        break;
    case EHTokFloatConstant:
        node = intermediate.addConstantUnion(token.d, EbtFloat, token.loc, true);
        break;
    case EHTokDoubleConstant:
        node = intermediate.addConstantUnion(token.d, EbtDouble, token.loc, true);
        break;
    case EHTokBoolConstant:
        node = intermediate.addConstantUnion(token.b, token.loc, true);
        break;

    default:
        return false;
    }

    advanceToken();

    return true;
}

// compound_statement
//      : LEFT_CURLY statement statement ... RIGHT_CURLY
//
bool HlslGrammar::acceptCompoundStatement(TIntermNode*& retStatement)
{
    TIntermAggregate* compoundStatement = nullptr;

    // LEFT_CURLY
    if (! acceptTokenClass(EHTokLeftBrace))
        return false;

    // statement statement ...
    TIntermNode* statement = nullptr;
    while (acceptStatement(statement)) {
        // hook it up
        compoundStatement = intermediate.growAggregate(compoundStatement, statement);
    }
    if (compoundStatement)
        compoundStatement->setOperator(EOpSequence);

    retStatement = compoundStatement;

    // RIGHT_CURLY
    return acceptTokenClass(EHTokRightBrace);
}

bool HlslGrammar::acceptScopedStatement(TIntermNode*& statement)
{
    parseContext.pushScope();
    bool result = acceptStatement(statement);
    parseContext.popScope();

    return result;
}

bool HlslGrammar::acceptScopedCompoundStatement(TIntermNode*& statement)
{
    parseContext.pushScope();
    bool result = acceptCompoundStatement(statement);
    parseContext.popScope();

    return result;
}

// statement
//      : attributes attributed_statement
//
// attributed_statement
//      : compound_statement
//      | SEMICOLON
//      | expression SEMICOLON
//      | declaration_statement
//      | selection_statement
//      | switch_statement
//      | case_label
//      | iteration_statement
//      | jump_statement
//
bool HlslGrammar::acceptStatement(TIntermNode*& statement)
{
    statement = nullptr;

    // attributes
    acceptAttributes();

    // attributed_statement
    switch (peek()) {
    case EHTokLeftBrace:
        return acceptScopedCompoundStatement(statement);

    case EHTokIf:
        return acceptSelectionStatement(statement);

    case EHTokSwitch:
        return acceptSwitchStatement(statement);

    case EHTokFor:
    case EHTokDo:
    case EHTokWhile:
        return acceptIterationStatement(statement);

    case EHTokContinue:
    case EHTokBreak:
    case EHTokDiscard:
    case EHTokReturn:
        return acceptJumpStatement(statement);

    case EHTokCase:
        return acceptCaseLabel(statement);

    case EHTokSemicolon:
        return acceptTokenClass(EHTokSemicolon);

    case EHTokRightBrace:
        // Performance: not strictly necessary, but stops a bunch of hunting early,
        // and is how sequences of statements end.
        return false;

    default:
        {
            // declaration
            if (acceptDeclaration(statement))
                return true;

            // expression
            TIntermTyped* node;
            if (acceptExpression(node))
                statement = node;
            else
                return false;

            // SEMICOLON (following an expression)
            if (! acceptTokenClass(EHTokSemicolon)) {
                expected(";");
                return false;
            }
        }
    }

    return true;
}

// attributes
//      : list of zero or more of:  LEFT_BRACKET attribute RIGHT_BRACKET
//
// attribute:
//      : UNROLL
//      | UNROLL LEFT_PAREN literal RIGHT_PAREN
//      | FASTOPT
//      | ALLOW_UAV_CONDITION
//      | BRANCH
//      | FLATTEN
//      | FORCECASE
//      | CALL
//
void HlslGrammar::acceptAttributes()
{
    // For now, accept the [ XXX(X) ] syntax, but drop.
    // TODO: subset to correct set?  Pass on?
    do {
        // LEFT_BRACKET?
        if (! acceptTokenClass(EHTokLeftBracket))
            return;

        // attribute
        if (peekTokenClass(EHTokIdentifier)) {
            // 'token.string' is the attribute
            advanceToken();
        } else if (! peekTokenClass(EHTokRightBracket)) {
            expected("identifier");
            advanceToken();
        }

        // (x)
        if (acceptTokenClass(EHTokLeftParen)) {
            TIntermTyped* node;
            if (! acceptLiteral(node))
                expected("literal");
            // 'node' has the literal in it
            if (! acceptTokenClass(EHTokRightParen))
                expected(")");
        }

        // RIGHT_BRACKET
        if (acceptTokenClass(EHTokRightBracket))
            continue;

        expected("]");
        return;

    } while (true);
}

// selection_statement
//      : IF LEFT_PAREN expression RIGHT_PAREN statement
//      : IF LEFT_PAREN expression RIGHT_PAREN statement ELSE statement
//
bool HlslGrammar::acceptSelectionStatement(TIntermNode*& statement)
{
    TSourceLoc loc = token.loc;

    // IF
    if (! acceptTokenClass(EHTokIf))
        return false;

    // so that something declared in the condition is scoped to the lifetimes
    // of the then-else statements
    parseContext.pushScope();

    // LEFT_PAREN expression RIGHT_PAREN
    TIntermTyped* condition;
    if (! acceptParenExpression(condition))
        return false;

    // create the child statements
    TIntermNodePair thenElse = { nullptr, nullptr };

    // then statement
    if (! acceptScopedStatement(thenElse.node1)) {
        expected("then statement");
        return false;
    }

    // ELSE
    if (acceptTokenClass(EHTokElse)) {
        // else statement
        if (! acceptScopedStatement(thenElse.node2)) {
            expected("else statement");
            return false;
        }
    }

    // Put the pieces together
    statement = intermediate.addSelection(condition, thenElse, loc);
    parseContext.popScope();

    return true;
}

bool HlslGrammar::acceptSwitchStatement(TIntermNode*& statement)
{
    return false;
}

// iteration_statement
//      : WHILE LEFT_PAREN condition RIGHT_PAREN statement
//      | DO LEFT_BRACE statement RIGHT_BRACE WHILE LEFT_PAREN expression RIGHT_PAREN SEMICOLON
//      | FOR LEFT_PAREN for_init_statement for_rest_statement RIGHT_PAREN statement
//
// Non-speculative, only call if it needs to be found; WHILE or DO or FOR already seen.
bool HlslGrammar::acceptIterationStatement(TIntermNode*& statement)
{
    TSourceLoc loc = token.loc;
    TIntermTyped* condition = nullptr;

    EHlslTokenClass loop = peek();
    assert(loop == EHTokDo || loop == EHTokFor || loop == EHTokWhile);

    //  WHILE or DO or FOR
    advanceToken();

    switch (loop) {
    case EHTokWhile:
        // so that something declared in the condition is scoped to the lifetime
        // of the while sub-statement
        parseContext.pushScope();
        parseContext.nestLooping();

        // LEFT_PAREN condition RIGHT_PAREN
        if (! acceptParenExpression(condition))
            return false;

        // statement
        if (! acceptScopedStatement(statement)) {
            expected("while sub-statement");
            return false;
        }

        parseContext.unnestLooping();
        parseContext.popScope();

        statement = intermediate.addLoop(statement, condition, nullptr, true, loc);

        return true;

    case EHTokDo:
        parseContext.nestLooping();

        if (! acceptTokenClass(EHTokLeftBrace))
            expected("{");

        // statement
        if (! peekTokenClass(EHTokRightBrace) && ! acceptScopedStatement(statement)) {
            expected("do sub-statement");
            return false;
        }

        if (! acceptTokenClass(EHTokRightBrace))
            expected("}");

        // WHILE
        if (! acceptTokenClass(EHTokWhile)) {
            expected("while");
            return false;
        }

        // LEFT_PAREN condition RIGHT_PAREN
        TIntermTyped* condition;
        if (! acceptParenExpression(condition))
            return false;

        if (! acceptTokenClass(EHTokSemicolon))
            expected(";");

        parseContext.unnestLooping();

        statement = intermediate.addLoop(statement, condition, 0, false, loc);

        return true;

    case EHTokFor:
    {
        // LEFT_PAREN
        if (! acceptTokenClass(EHTokLeftParen))
            expected("(");

        // so that something declared in the condition is scoped to the lifetime
        // of the for sub-statement
        parseContext.pushScope();

        // initializer SEMI_COLON
        TIntermTyped* initializer = nullptr; // TODO, "for (initializer" needs to support decl. statement
        acceptExpression(initializer);
        if (! acceptTokenClass(EHTokSemicolon))
            expected(";");

        parseContext.nestLooping();

        // condition SEMI_COLON
        acceptExpression(condition);
        if (! acceptTokenClass(EHTokSemicolon))
            expected(";");

        // iterator SEMI_COLON
        TIntermTyped* iterator = nullptr;
        acceptExpression(iterator);
        if (! acceptTokenClass(EHTokRightParen))
            expected(")");

        // statement
        if (! acceptScopedStatement(statement)) {
            expected("for sub-statement");
            return false;
        }

        statement = intermediate.addForLoop(statement, initializer, condition, iterator, true, loc);

        parseContext.popScope();
        parseContext.unnestLooping();

        return true;
    }

    default:
        return false;
    }
}

// jump_statement
//      : CONTINUE SEMICOLON
//      | BREAK SEMICOLON
//      | DISCARD SEMICOLON
//      | RETURN SEMICOLON
//      | RETURN expression SEMICOLON
//
bool HlslGrammar::acceptJumpStatement(TIntermNode*& statement)
{
    switch (peek()) {
    case EHTokContinue:
    case EHTokBreak:
    case EHTokDiscard:
        // TODO
        return false;

    case EHTokReturn:
        // return
        if (acceptTokenClass(EHTokReturn)) {
            // expression
            TIntermTyped* node;
            if (acceptExpression(node)) {
                // hook it up
                statement = intermediate.addBranch(EOpReturn, node, token.loc);
            } else
                statement = intermediate.addBranch(EOpReturn, token.loc);

            // SEMICOLON
            if (! acceptTokenClass(EHTokSemicolon)) {
                expected(";");
                return false;
            }

            return true;
        }

    default:
        return false;
    }
}


bool HlslGrammar::acceptCaseLabel(TIntermNode*& statement)
{
    return false;
}

// COLON semantic
bool HlslGrammar::acceptSemantic()
{
    // COLON
    if (acceptTokenClass(EHTokColon)) {
        // semantic
        HlslToken idToken;
        if (! acceptIdentifier(idToken)) {
            expected("semantic");
            return false;
        }
    }

    return true;
}

} // end namespace glslang
