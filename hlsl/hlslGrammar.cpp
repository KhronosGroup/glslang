//
//Copyright (C) 2016 Google, Inc.
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
// with all other work being farmed out to hlslParseHelper.cpp, which it turn
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

// Load 'token' with the next token in the stream of tokens.
void HlslGrammar::advanceToken()
{
    scanContext.tokenize(token);
}

// Return true and advance to the next token if the current token is the
// expected (passed in) token class.
bool HlslGrammar::acceptTokenClass(EHlslTokenClass tokenClass)
{
    if (token.tokenClass == tokenClass) {
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

    while (token.tokenClass != EHTokNone) {
        // externalDeclaration
        TIntermNode* declarationNode;
        if (! acceptDeclaration(declarationNode))
            return false;

        // hook it up
        unitNode = parseContext.intermediate.growAggregate(unitNode, declarationNode);
    }

    // set root of AST
    parseContext.intermediate.setTreeRoot(unitNode);

    return true;
}

// declaration
//      : SEMICOLON
//      : fully_specified_type ;
//      | fully_specified_type identifier ;
//      | fully_specified_type identifier = expression ;
//      | fully_specified_type identifier function_parameters ;         // function prototype
//      | fully_specified_type function_parameters compound_statement   // function definition
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
    if (token.tokenClass == EHTokIdentifier) {
        TSourceLoc declLoc = token.loc;
        TString* declName = token.string;
        advanceToken();

        // = expression
        TIntermTyped* expressionNode = nullptr;
        if (acceptTokenClass(EHTokEqual)) {
            if (! acceptExpression(expressionNode)) {
                expected("initializer");
                return false;
            }
        }

        // ;
        if (acceptTokenClass(EHTokSemicolon)) {
            node = parseContext.declareVariable(declLoc, *declName, type, 0, expressionNode);
            return true;
        }
    }

    // no identifier, just ;
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
    switch (token.tokenClass) {
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
    if (! token.isType)
        return false;

    switch (token.tokenClass) {
    case EHTokInt:
    case EHTokInt1:
    case EHTokDword:
        new(&type) TType(EbtInt);
        break;
    case EHTokFloat:
    case EHTokFloat1:
        new(&type) TType(EbtFloat);
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

    case EHTokInt2:
        new(&type) TType(EbtInt, EvqTemporary, 2);
        break;
    case EHTokInt3:
        new(&type) TType(EbtInt, EvqTemporary, 3);
        break;
    case EHTokInt4:
        new(&type) TType(EbtInt, EvqTemporary, 4);
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

    case EHTokFloat2x2:
        new(&type) TType(EbtFloat, EvqTemporary, 0, 2, 2);
        break;
    case EHTokFloat2x3:
        new(&type) TType(EbtFloat, EvqTemporary, 0, 3, 2);
        break;
    case EHTokFloat2x4:
        new(&type) TType(EbtFloat, EvqTemporary, 0, 4, 2);
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
    case EHTokFloat4x2:
        new(&type) TType(EbtFloat, EvqTemporary, 0, 2, 4);
        break;
    case EHTokFloat4x3:
        new(&type) TType(EbtFloat, EvqTemporary, 0, 3, 4);
        break;
    case EHTokFloat4x4:
        new(&type) TType(EbtFloat, EvqTemporary, 0, 4, 4);
        break;

    default:
        return false;
    }

    advanceToken();

    return true;
}

// expression
//      : identifier
//      | ( expression )
//      | type(...)                 // constructor
//      | literal
//      | identifier operator identifier   // to be generalized to all expressions
//
bool HlslGrammar::acceptExpression(TIntermTyped*& node)
{
    // identifier
    if (token.tokenClass == EHTokIdentifier) {
        node = parseContext.handleVariable(token.loc, token.symbol, token.string);
        return true;
    }

    // ( expression )
    if (acceptTokenClass(EHTokLeftParen)) {
        if (! acceptExpression(node)) {
            expected("expression");
            return false;
        }
        if (! acceptTokenClass(EHTokRightParen)) {
            expected("right parenthesis");
            return false;
        }

        return true;
    }

    // literal
    if (acceptLiteral(node))
        return true;

    // type(...)     // constructor
    if (acceptConstructor(node))
        return true;

    // identifier operator identifier
    if (token.tokenClass == EHTokIdentifier) {
        TIntermTyped* left = parseContext.handleVariable(token.loc, token.symbol, token.string);
        advanceToken();

        // operator
        TOperator op;
        if (! acceptOperator(op))
            return false;
        TSourceLoc loc = token.loc;

        // right
        if (token.tokenClass == EHTokIdentifier) {
            TIntermTyped* right = parseContext.handleVariable(token.loc, token.symbol, token.string);
            advanceToken();
            node = parseContext.intermediate.addBinaryMath(op, left, right, loc);
        } else
            return false;
    } else
        return false;

    return true;
}

// constructor
//      : type arguments
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
        TIntermAggregate* arguments = nullptr;
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

// arguments
//      : ( expression , expression, ... )
//
// The arguments are pushed onto the 'function' argument list and
// onto the 'arguments' aggregate.
//
bool HlslGrammar::acceptArguments(TFunction* function, TIntermAggregate*& arguments)
{
    // (
    if (! acceptTokenClass(EHTokLeftParen))
        return false;

    do {
        // expression
        TIntermTyped* arg;
        if (! acceptExpression(arg))
            break;

        // hook it up
        parseContext.handleFunctionArgument(function, arguments, arg);

        // ,
        if (! acceptTokenClass(EHTokComma))
            break;
    } while (true);

    // )
    if (! acceptTokenClass(EHTokRightParen)) {
        expected("right parenthesis");
        return false;
    }

    return true;
}

bool HlslGrammar::acceptLiteral(TIntermTyped*& node)
{
    switch (token.tokenClass) {
    case EHTokIntConstant:
        node = parseContext.intermediate.addConstantUnion(token.i, token.loc, true);
        break;
    case EHTokFloatConstant:
        node = parseContext.intermediate.addConstantUnion(token.d, EbtFloat, token.loc, true);
        break;
    case EHTokDoubleConstant:
        node = parseContext.intermediate.addConstantUnion(token.d, EbtDouble, token.loc, true);
        break;
    case EHTokBoolConstant:
        node = parseContext.intermediate.addConstantUnion(token.b, token.loc, true);
        break;

    default:
        return false;
    }

    advanceToken();

    return true;
}

bool HlslGrammar::acceptOperator(TOperator& op)
{
    switch (token.tokenClass) {
    case EHTokPlus:
        op = EOpAdd;
        break;
    default:
        return false;
    }

    advanceToken();

    return true;
}

bool HlslGrammar::acceptCompoundStatement()
{
    return false;
}

} // end namespace glslang
