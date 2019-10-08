//
// Copyright (C) 2002-2005  3Dlabs Inc. Ltd.
// Copyright (C) 2012-2013 LunarG, Inc.
// Copyright (C) 2017 ARM Limited.
// Copyright (C) 2015-2018 Google, Inc.
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
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
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
// ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//

//
// Do not edit the .y file, only edit the .m4 file.
// The .y bison file is not a source file, it is a derivitive of the .m4 file.
// The m4 file needs to be processed by m4 to generate the .y bison file.
//
// Code sandwiched between a pair:
//
//    GLSLANG_WEB_EXCLUDE_ON
//      ...
//      ...
//      ...
//    GLSLANG_WEB_EXCLUDE_OFF
//
// Will be exluded from the grammar when m4 is executed as:
//
//    m4 -P -DGLSLANG_WEB
//
// It will be included when m4 is executed as:
//
//    m4 -P
//




/**
 * This is bison grammar and productions for parsing all versions of the
 * GLSL shading languages.
 */
%{

/* Based on:
ANSI C Yacc grammar

In 1985, Jeff Lee published his Yacc grammar (which is accompanied by a
matching Lex specification) for the April 30, 1985 draft version of the
ANSI C standard.  Tom Stockfisch reposted it to net.sources in 1987; that
original, as mentioned in the answer to question 17.25 of the comp.lang.c
FAQ, can be ftp'ed from ftp.uu.net, file usenet/net.sources/ansi.c.grammar.Z.

I intend to keep this version as close to the current C Standard grammar as
possible; please let me know if you discover discrepancies.

Jutta Degener, 1995
*/

#include "SymbolTable.h"
#include "ParseHelper.h"
#include "../Public/ShaderLang.h"
#include "attribute.h"

using namespace glslang;

%}

%define parse.error verbose

%union {
    struct {
        glslang::TSourceLoc loc;
        union {
            glslang::TString *string;
            int i;
            unsigned int u;
            long long i64;
            unsigned long long u64;
            bool b;
            double d;
        };
        glslang::TSymbol* symbol;
    } lex;
    struct {
        glslang::TSourceLoc loc;
        glslang::TOperator op;
        union {
            TIntermNode* intermNode;
            glslang::TIntermNodePair nodePair;
            glslang::TIntermTyped* intermTypedNode;
            glslang::TAttributes* attributes;
        };
        union {
            glslang::TPublicType type;
            glslang::TFunction* function;
            glslang::TParameter param;
            glslang::TTypeLoc typeLine;
            glslang::TTypeList* typeList;
            glslang::TArraySizes* arraySizes;
            glslang::TIdentifierList* identifierList;
        };
        glslang::TArraySizes* typeParameters;
    } interm;
}

%{

/* windows only pragma */
#ifdef _MSC_VER
    #pragma warning(disable : 4065)
    #pragma warning(disable : 4127)
    #pragma warning(disable : 4244)
#endif

#define parseContext (*pParseContext)
#define yyerror(context, msg) context->parserError(msg)

extern int yylex(YYSTYPE*, TParseContext&);

%}

%parse-param {glslang::TParseContext* pParseContext}
%lex-param {parseContext}
%pure-parser  // enable thread safety
%expect 1     // One shift reduce conflict because of if | else

%token <lex> CONST BOOL INT UINT FLOAT
%token <lex> BVEC2 BVEC3 BVEC4
%token <lex> IVEC2 IVEC3 IVEC4
%token <lex> UVEC2 UVEC3 UVEC4
%token <lex> VEC2 VEC3 VEC4
%token <lex> MAT2 MAT3 MAT4
%token <lex> MAT2X2 MAT2X3 MAT2X4
%token <lex> MAT3X2 MAT3X3 MAT3X4
%token <lex> MAT4X2 MAT4X3 MAT4X4

// combined image/sampler
%token <lex> SAMPLER2D SAMPLER3D SAMPLERCUBE SAMPLER2DSHADOW
%token <lex> SAMPLERCUBESHADOW SAMPLER2DARRAY
%token <lex> SAMPLER2DARRAYSHADOW ISAMPLER2D ISAMPLER3D ISAMPLERCUBE
%token <lex> ISAMPLER2DARRAY USAMPLER2D USAMPLER3D
%token <lex> USAMPLERCUBE USAMPLER2DARRAY

// separate image/sampler
%token <lex> SAMPLER SAMPLERSHADOW
%token <lex>  TEXTURE2D  TEXTURE3D  TEXTURECUBE  TEXTURE2DARRAY
%token <lex> ITEXTURE2D ITEXTURE3D ITEXTURECUBE ITEXTURE2DARRAY
%token <lex> UTEXTURE2D UTEXTURE3D UTEXTURECUBE UTEXTURE2DARRAY



%token <lex> LEFT_OP RIGHT_OP
%token <lex> INC_OP DEC_OP LE_OP GE_OP EQ_OP NE_OP
%token <lex> AND_OP OR_OP XOR_OP MUL_ASSIGN DIV_ASSIGN ADD_ASSIGN
%token <lex> MOD_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN
%token <lex> SUB_ASSIGN

%token <lex> LEFT_PAREN RIGHT_PAREN LEFT_BRACKET RIGHT_BRACKET LEFT_BRACE RIGHT_BRACE DOT
%token <lex> COMMA COLON EQUAL SEMICOLON BANG DASH TILDE PLUS STAR SLASH PERCENT
%token <lex> LEFT_ANGLE RIGHT_ANGLE VERTICAL_BAR CARET AMPERSAND QUESTION

%token <lex> INVARIANT
%token <lex> HIGH_PRECISION MEDIUM_PRECISION LOW_PRECISION PRECISION
%token <lex> PACKED RESOURCE SUPERP

%token <lex> FLOATCONSTANT INTCONSTANT UINTCONSTANT BOOLCONSTANT
%token <lex> IDENTIFIER TYPE_NAME
%token <lex> CENTROID IN OUT INOUT
%token <lex> STRUCT VOID WHILE
%token <lex> BREAK CONTINUE DO ELSE FOR IF DISCARD RETURN SWITCH CASE DEFAULT
%token <lex> UNIFORM SHARED
%token <lex> FLAT SMOOTH LAYOUT



%type <interm> assignment_operator unary_operator
%type <interm.intermTypedNode> variable_identifier primary_expression postfix_expression
%type <interm.intermTypedNode> expression integer_expression assignment_expression
%type <interm.intermTypedNode> unary_expression multiplicative_expression additive_expression
%type <interm.intermTypedNode> relational_expression equality_expression
%type <interm.intermTypedNode> conditional_expression constant_expression
%type <interm.intermTypedNode> logical_or_expression logical_xor_expression logical_and_expression
%type <interm.intermTypedNode> shift_expression and_expression exclusive_or_expression inclusive_or_expression
%type <interm.intermTypedNode> function_call initializer condition conditionopt

%type <interm.intermNode> translation_unit function_definition
%type <interm.intermNode> statement simple_statement
%type <interm.intermNode> statement_list switch_statement_list compound_statement
%type <interm.intermNode> declaration_statement selection_statement selection_statement_nonattributed expression_statement
%type <interm.intermNode> switch_statement switch_statement_nonattributed case_label
%type <interm.intermNode> declaration external_declaration
%type <interm.intermNode> for_init_statement compound_statement_no_new_scope
%type <interm.nodePair> selection_rest_statement for_rest_statement
%type <interm.intermNode> iteration_statement iteration_statement_nonattributed jump_statement statement_no_new_scope statement_scoped
%type <interm> single_declaration init_declarator_list

%type <interm> parameter_declaration parameter_declarator parameter_type_specifier

%type <interm> array_specifier
%type <interm.type> invariant_qualifier interpolation_qualifier storage_qualifier precision_qualifier
%type <interm.type> layout_qualifier layout_qualifier_id_list layout_qualifier_id

%type <interm.typeParameters> type_parameter_specifier
%type <interm.typeParameters> type_parameter_specifier_opt
%type <interm.typeParameters> type_parameter_specifier_list

%type <interm.type> type_qualifier fully_specified_type type_specifier
%type <interm.type> single_type_qualifier
%type <interm.type> type_specifier_nonarray
%type <interm.type> struct_specifier
%type <interm.typeLine> struct_declarator
%type <interm.typeList> struct_declarator_list struct_declaration struct_declaration_list
%type <interm> block_structure
%type <interm.function> function_header function_declarator
%type <interm.function> function_header_with_parameters
%type <interm> function_call_header_with_parameters function_call_header_no_parameters function_call_generic function_prototype
%type <interm> function_call_or_method function_identifier function_call_header

%type <interm.identifierList> identifier_list



%start translation_unit
%%

variable_identifier
    : IDENTIFIER {
        $$ = parseContext.handleVariable($1.loc, $1.symbol, $1.string);
    }
    ;

primary_expression
    : variable_identifier {
        $$ = $1;
    }
    | LEFT_PAREN expression RIGHT_PAREN {
        $$ = $2;
        if ($$->getAsConstantUnion())
            $$->getAsConstantUnion()->setExpression();
    }
    | FLOATCONSTANT {
        $$ = parseContext.intermediate.addConstantUnion($1.d, EbtFloat, $1.loc, true);
    }
    | INTCONSTANT {
        $$ = parseContext.intermediate.addConstantUnion($1.i, $1.loc, true);
    }
    | UINTCONSTANT {
        parseContext.fullIntegerCheck($1.loc, "unsigned literal");
        $$ = parseContext.intermediate.addConstantUnion($1.u, $1.loc, true);
    }
    | BOOLCONSTANT {
        $$ = parseContext.intermediate.addConstantUnion($1.b, $1.loc, true);
    }

    ;

postfix_expression
    : primary_expression {
        $$ = $1;
    }
    | postfix_expression LEFT_BRACKET integer_expression RIGHT_BRACKET {
        $$ = parseContext.handleBracketDereference($2.loc, $1, $3);
    }
    | function_call {
        $$ = $1;
    }
    | postfix_expression DOT IDENTIFIER {
        $$ = parseContext.handleDotDereference($3.loc, $1, *$3.string);
    }
    | postfix_expression INC_OP {
        parseContext.variableCheck($1);
        parseContext.lValueErrorCheck($2.loc, "++", $1);
        $$ = parseContext.handleUnaryMath($2.loc, "++", EOpPostIncrement, $1);
    }
    | postfix_expression DEC_OP {
        parseContext.variableCheck($1);
        parseContext.lValueErrorCheck($2.loc, "--", $1);
        $$ = parseContext.handleUnaryMath($2.loc, "--", EOpPostDecrement, $1);
    }
    ;

integer_expression
    : expression {
        parseContext.integerCheck($1, "[]");
        $$ = $1;
    }
    ;

function_call
    : function_call_or_method {
        $$ = parseContext.handleFunctionCall($1.loc, $1.function, $1.intermNode);
        delete $1.function;
    }
    ;

function_call_or_method
    : function_call_generic {
        $$ = $1;
    }
    ;

function_call_generic
    : function_call_header_with_parameters RIGHT_PAREN {
        $$ = $1;
        $$.loc = $2.loc;
    }
    | function_call_header_no_parameters RIGHT_PAREN {
        $$ = $1;
        $$.loc = $2.loc;
    }
    ;

function_call_header_no_parameters
    : function_call_header VOID {
        $$ = $1;
    }
    | function_call_header {
        $$ = $1;
    }
    ;

function_call_header_with_parameters
    : function_call_header assignment_expression {
        TParameter param = { 0, new TType };
        param.type->shallowCopy($2->getType());
        $1.function->addParameter(param);
        $$.function = $1.function;
        $$.intermNode = $2;
    }
    | function_call_header_with_parameters COMMA assignment_expression {
        TParameter param = { 0, new TType };
        param.type->shallowCopy($3->getType());
        $1.function->addParameter(param);
        $$.function = $1.function;
        $$.intermNode = parseContext.intermediate.growAggregate($1.intermNode, $3, $2.loc);
    }
    ;

function_call_header
    : function_identifier LEFT_PAREN {
        $$ = $1;
    }
    ;

// Grammar Note:  Constructors look like functions, but are recognized as types.

function_identifier
    : type_specifier {
        // Constructor
        $$.intermNode = 0;
        $$.function = parseContext.handleConstructorCall($1.loc, $1);
    }
    | postfix_expression {
        //
        // Should be a method or subroutine call, but we haven't recognized the arguments yet.
        //
        $$.function = 0;
        $$.intermNode = 0;

        TIntermMethod* method = $1->getAsMethodNode();
        if (method) {
            $$.function = new TFunction(&method->getMethodName(), TType(EbtInt), EOpArrayLength);
            $$.intermNode = method->getObject();
        } else {
            TIntermSymbol* symbol = $1->getAsSymbolNode();
            if (symbol) {
                parseContext.reservedErrorCheck(symbol->getLoc(), symbol->getName());
                TFunction *function = new TFunction(&symbol->getName(), TType(EbtVoid));
                $$.function = function;
            } else
                parseContext.error($1->getLoc(), "function call, method, or subroutine call expected", "", "");
        }

        if ($$.function == 0) {
            // error recover
            TString* empty = NewPoolTString("");
            $$.function = new TFunction(empty, TType(EbtVoid), EOpNull);
        }
    }

    ;

unary_expression
    : postfix_expression {
        parseContext.variableCheck($1);
        $$ = $1;
        if (TIntermMethod* method = $1->getAsMethodNode())
            parseContext.error($1->getLoc(), "incomplete method syntax", method->getMethodName().c_str(), "");
    }
    | INC_OP unary_expression {
        parseContext.lValueErrorCheck($1.loc, "++", $2);
        $$ = parseContext.handleUnaryMath($1.loc, "++", EOpPreIncrement, $2);
    }
    | DEC_OP unary_expression {
        parseContext.lValueErrorCheck($1.loc, "--", $2);
        $$ = parseContext.handleUnaryMath($1.loc, "--", EOpPreDecrement, $2);
    }
    | unary_operator unary_expression {
        if ($1.op != EOpNull) {
            char errorOp[2] = {0, 0};
            switch($1.op) {
            case EOpNegative:   errorOp[0] = '-'; break;
            case EOpLogicalNot: errorOp[0] = '!'; break;
            case EOpBitwiseNot: errorOp[0] = '~'; break;
            default: break; // some compilers want this
            }
            $$ = parseContext.handleUnaryMath($1.loc, errorOp, $1.op, $2);
        } else {
            $$ = $2;
            if ($$->getAsConstantUnion())
                $$->getAsConstantUnion()->setExpression();
        }
    }
    ;
// Grammar Note:  No traditional style type casts.

unary_operator
    : PLUS  { $$.loc = $1.loc; $$.op = EOpNull; }
    | DASH  { $$.loc = $1.loc; $$.op = EOpNegative; }
    | BANG  { $$.loc = $1.loc; $$.op = EOpLogicalNot; }
    | TILDE { $$.loc = $1.loc; $$.op = EOpBitwiseNot;
              parseContext.fullIntegerCheck($1.loc, "bitwise not"); }
    ;
// Grammar Note:  No '*' or '&' unary ops.  Pointers are not supported.

multiplicative_expression
    : unary_expression { $$ = $1; }
    | multiplicative_expression STAR unary_expression {
        $$ = parseContext.handleBinaryMath($2.loc, "*", EOpMul, $1, $3);
        if ($$ == 0)
            $$ = $1;
    }
    | multiplicative_expression SLASH unary_expression {
        $$ = parseContext.handleBinaryMath($2.loc, "/", EOpDiv, $1, $3);
        if ($$ == 0)
            $$ = $1;
    }
    | multiplicative_expression PERCENT unary_expression {
        parseContext.fullIntegerCheck($2.loc, "%");
        $$ = parseContext.handleBinaryMath($2.loc, "%", EOpMod, $1, $3);
        if ($$ == 0)
            $$ = $1;
    }
    ;

additive_expression
    : multiplicative_expression { $$ = $1; }
    | additive_expression PLUS multiplicative_expression {
        $$ = parseContext.handleBinaryMath($2.loc, "+", EOpAdd, $1, $3);
        if ($$ == 0)
            $$ = $1;
    }
    | additive_expression DASH multiplicative_expression {
        $$ = parseContext.handleBinaryMath($2.loc, "-", EOpSub, $1, $3);
        if ($$ == 0)
            $$ = $1;
    }
    ;

shift_expression
    : additive_expression { $$ = $1; }
    | shift_expression LEFT_OP additive_expression {
        parseContext.fullIntegerCheck($2.loc, "bit shift left");
        $$ = parseContext.handleBinaryMath($2.loc, "<<", EOpLeftShift, $1, $3);
        if ($$ == 0)
            $$ = $1;
    }
    | shift_expression RIGHT_OP additive_expression {
        parseContext.fullIntegerCheck($2.loc, "bit shift right");
        $$ = parseContext.handleBinaryMath($2.loc, ">>", EOpRightShift, $1, $3);
        if ($$ == 0)
            $$ = $1;
    }
    ;

relational_expression
    : shift_expression { $$ = $1; }
    | relational_expression LEFT_ANGLE shift_expression {
        $$ = parseContext.handleBinaryMath($2.loc, "<", EOpLessThan, $1, $3);
        if ($$ == 0)
            $$ = parseContext.intermediate.addConstantUnion(false, $2.loc);
    }
    | relational_expression RIGHT_ANGLE shift_expression  {
        $$ = parseContext.handleBinaryMath($2.loc, ">", EOpGreaterThan, $1, $3);
        if ($$ == 0)
            $$ = parseContext.intermediate.addConstantUnion(false, $2.loc);
    }
    | relational_expression LE_OP shift_expression  {
        $$ = parseContext.handleBinaryMath($2.loc, "<=", EOpLessThanEqual, $1, $3);
        if ($$ == 0)
            $$ = parseContext.intermediate.addConstantUnion(false, $2.loc);
    }
    | relational_expression GE_OP shift_expression  {
        $$ = parseContext.handleBinaryMath($2.loc, ">=", EOpGreaterThanEqual, $1, $3);
        if ($$ == 0)
            $$ = parseContext.intermediate.addConstantUnion(false, $2.loc);
    }
    ;

equality_expression
    : relational_expression { $$ = $1; }
    | equality_expression EQ_OP relational_expression  {
        parseContext.arrayObjectCheck($2.loc, $1->getType(), "array comparison");
        parseContext.opaqueCheck($2.loc, $1->getType(), "==");
        parseContext.specializationCheck($2.loc, $1->getType(), "==");
        parseContext.referenceCheck($2.loc, $1->getType(), "==");
        $$ = parseContext.handleBinaryMath($2.loc, "==", EOpEqual, $1, $3);
        if ($$ == 0)
            $$ = parseContext.intermediate.addConstantUnion(false, $2.loc);
    }
    | equality_expression NE_OP relational_expression {
        parseContext.arrayObjectCheck($2.loc, $1->getType(), "array comparison");
        parseContext.opaqueCheck($2.loc, $1->getType(), "!=");
        parseContext.specializationCheck($2.loc, $1->getType(), "!=");
        parseContext.referenceCheck($2.loc, $1->getType(), "!=");
        $$ = parseContext.handleBinaryMath($2.loc, "!=", EOpNotEqual, $1, $3);
        if ($$ == 0)
            $$ = parseContext.intermediate.addConstantUnion(false, $2.loc);
    }
    ;

and_expression
    : equality_expression { $$ = $1; }
    | and_expression AMPERSAND equality_expression {
        parseContext.fullIntegerCheck($2.loc, "bitwise and");
        $$ = parseContext.handleBinaryMath($2.loc, "&", EOpAnd, $1, $3);
        if ($$ == 0)
            $$ = $1;
    }
    ;

exclusive_or_expression
    : and_expression { $$ = $1; }
    | exclusive_or_expression CARET and_expression {
        parseContext.fullIntegerCheck($2.loc, "bitwise exclusive or");
        $$ = parseContext.handleBinaryMath($2.loc, "^", EOpExclusiveOr, $1, $3);
        if ($$ == 0)
            $$ = $1;
    }
    ;

inclusive_or_expression
    : exclusive_or_expression { $$ = $1; }
    | inclusive_or_expression VERTICAL_BAR exclusive_or_expression {
        parseContext.fullIntegerCheck($2.loc, "bitwise inclusive or");
        $$ = parseContext.handleBinaryMath($2.loc, "|", EOpInclusiveOr, $1, $3);
        if ($$ == 0)
            $$ = $1;
    }
    ;

logical_and_expression
    : inclusive_or_expression { $$ = $1; }
    | logical_and_expression AND_OP inclusive_or_expression {
        $$ = parseContext.handleBinaryMath($2.loc, "&&", EOpLogicalAnd, $1, $3);
        if ($$ == 0)
            $$ = parseContext.intermediate.addConstantUnion(false, $2.loc);
    }
    ;

logical_xor_expression
    : logical_and_expression { $$ = $1; }
    | logical_xor_expression XOR_OP logical_and_expression  {
        $$ = parseContext.handleBinaryMath($2.loc, "^^", EOpLogicalXor, $1, $3);
        if ($$ == 0)
            $$ = parseContext.intermediate.addConstantUnion(false, $2.loc);
    }
    ;

logical_or_expression
    : logical_xor_expression { $$ = $1; }
    | logical_or_expression OR_OP logical_xor_expression  {
        $$ = parseContext.handleBinaryMath($2.loc, "||", EOpLogicalOr, $1, $3);
        if ($$ == 0)
            $$ = parseContext.intermediate.addConstantUnion(false, $2.loc);
    }
    ;

conditional_expression
    : logical_or_expression { $$ = $1; }
    | logical_or_expression QUESTION {
        ++parseContext.controlFlowNestingLevel;
    }
      expression COLON assignment_expression {
        --parseContext.controlFlowNestingLevel;
        parseContext.boolCheck($2.loc, $1);
        parseContext.rValueErrorCheck($2.loc, "?", $1);
        parseContext.rValueErrorCheck($5.loc, ":", $4);
        parseContext.rValueErrorCheck($5.loc, ":", $6);
        $$ = parseContext.intermediate.addSelection($1, $4, $6, $2.loc);
        if ($$ == 0) {
            parseContext.binaryOpError($2.loc, ":", $4->getCompleteString(), $6->getCompleteString());
            $$ = $6;
        }
    }
    ;

assignment_expression
    : conditional_expression { $$ = $1; }
    | unary_expression assignment_operator assignment_expression {
        parseContext.arrayObjectCheck($2.loc, $1->getType(), "array assignment");
        parseContext.opaqueCheck($2.loc, $1->getType(), "=");
        parseContext.storage16BitAssignmentCheck($2.loc, $1->getType(), "=");
        parseContext.specializationCheck($2.loc, $1->getType(), "=");
        parseContext.lValueErrorCheck($2.loc, "assign", $1);
        parseContext.rValueErrorCheck($2.loc, "assign", $3);
        $$ = parseContext.intermediate.addAssign($2.op, $1, $3, $2.loc);
        if ($$ == 0) {
            parseContext.assignError($2.loc, "assign", $1->getCompleteString(), $3->getCompleteString());
            $$ = $1;
        }
    }
    ;

assignment_operator
    : EQUAL {
        $$.loc = $1.loc;
        $$.op = EOpAssign;
    }
    | MUL_ASSIGN {
        $$.loc = $1.loc;
        $$.op = EOpMulAssign;
    }
    | DIV_ASSIGN {
        $$.loc = $1.loc;
        $$.op = EOpDivAssign;
    }
    | MOD_ASSIGN {
        parseContext.fullIntegerCheck($1.loc, "%=");
        $$.loc = $1.loc;
        $$.op = EOpModAssign;
    }
    | ADD_ASSIGN {
        $$.loc = $1.loc;
        $$.op = EOpAddAssign;
    }
    | SUB_ASSIGN {
        $$.loc = $1.loc;
        $$.op = EOpSubAssign;
    }
    | LEFT_ASSIGN {
        parseContext.fullIntegerCheck($1.loc, "bit-shift left assign");
        $$.loc = $1.loc; $$.op = EOpLeftShiftAssign;
    }
    | RIGHT_ASSIGN {
        parseContext.fullIntegerCheck($1.loc, "bit-shift right assign");
        $$.loc = $1.loc; $$.op = EOpRightShiftAssign;
    }
    | AND_ASSIGN {
        parseContext.fullIntegerCheck($1.loc, "bitwise-and assign");
        $$.loc = $1.loc; $$.op = EOpAndAssign;
    }
    | XOR_ASSIGN {
        parseContext.fullIntegerCheck($1.loc, "bitwise-xor assign");
        $$.loc = $1.loc; $$.op = EOpExclusiveOrAssign;
    }
    | OR_ASSIGN {
        parseContext.fullIntegerCheck($1.loc, "bitwise-or assign");
        $$.loc = $1.loc; $$.op = EOpInclusiveOrAssign;
    }
    ;

expression
    : assignment_expression {
        $$ = $1;
    }
    | expression COMMA assignment_expression {
        parseContext.samplerConstructorLocationCheck($2.loc, ",", $3);
        $$ = parseContext.intermediate.addComma($1, $3, $2.loc);
        if ($$ == 0) {
            parseContext.binaryOpError($2.loc, ",", $1->getCompleteString(), $3->getCompleteString());
            $$ = $3;
        }
    }
    ;

constant_expression
    : conditional_expression {
        parseContext.constantValueCheck($1, "");
        $$ = $1;
    }
    ;

declaration
    : function_prototype SEMICOLON {
        parseContext.handleFunctionDeclarator($1.loc, *$1.function, true /* prototype */);
        $$ = 0;
        // TODO: 4.0 functionality: subroutines: make the identifier a user type for this signature
    }
    | init_declarator_list SEMICOLON {
        if ($1.intermNode && $1.intermNode->getAsAggregate())
            $1.intermNode->getAsAggregate()->setOperator(EOpSequence);
        $$ = $1.intermNode;
    }
    | PRECISION precision_qualifier type_specifier SEMICOLON {
        parseContext.profileRequires($1.loc, ENoProfile, 130, 0, "precision statement");
        // lazy setting of the previous scope's defaults, has effect only the first time it is called in a particular scope
        parseContext.symbolTable.setPreviousDefaultPrecisions(&parseContext.defaultPrecision[0]);
        parseContext.setDefaultPrecision($1.loc, $3, $2.qualifier.precision);
        $$ = 0;
    }
    | block_structure SEMICOLON {
        parseContext.declareBlock($1.loc, *$1.typeList);
        $$ = 0;
    }
    | block_structure IDENTIFIER SEMICOLON {
        parseContext.declareBlock($1.loc, *$1.typeList, $2.string);
        $$ = 0;
    }
    | block_structure IDENTIFIER array_specifier SEMICOLON {
        parseContext.declareBlock($1.loc, *$1.typeList, $2.string, $3.arraySizes);
        $$ = 0;
    }
    | type_qualifier SEMICOLON {
        parseContext.globalQualifierFixCheck($1.loc, $1.qualifier);
        parseContext.updateStandaloneQualifierDefaults($1.loc, $1);
        $$ = 0;
    }
    | type_qualifier IDENTIFIER SEMICOLON {
        parseContext.checkNoShaderLayouts($1.loc, $1.shaderQualifiers);
        parseContext.addQualifierToExisting($1.loc, $1.qualifier, *$2.string);
        $$ = 0;
    }
    | type_qualifier IDENTIFIER identifier_list SEMICOLON {
        parseContext.checkNoShaderLayouts($1.loc, $1.shaderQualifiers);
        $3->push_back($2.string);
        parseContext.addQualifierToExisting($1.loc, $1.qualifier, *$3);
        $$ = 0;
    }
    ;

block_structure
    : type_qualifier IDENTIFIER LEFT_BRACE { parseContext.nestedBlockCheck($1.loc); } struct_declaration_list RIGHT_BRACE {
        --parseContext.structNestingLevel;
        parseContext.blockName = $2.string;
        parseContext.globalQualifierFixCheck($1.loc, $1.qualifier);
        parseContext.checkNoShaderLayouts($1.loc, $1.shaderQualifiers);
        parseContext.currentBlockQualifier = $1.qualifier;
        $$.loc = $1.loc;
        $$.typeList = $5;
    }

identifier_list
    : COMMA IDENTIFIER {
        $$ = new TIdentifierList;
        $$->push_back($2.string);
    }
    | identifier_list COMMA IDENTIFIER {
        $$ = $1;
        $$->push_back($3.string);
    }
    ;

function_prototype
    : function_declarator RIGHT_PAREN  {
        $$.function = $1;
        $$.loc = $2.loc;
    }
    ;

function_declarator
    : function_header {
        $$ = $1;
    }
    | function_header_with_parameters {
        $$ = $1;
    }
    ;


function_header_with_parameters
    : function_header parameter_declaration {
        // Add the parameter
        $$ = $1;
        if ($2.param.type->getBasicType() != EbtVoid)
            $1->addParameter($2.param);
        else
            delete $2.param.type;
    }
    | function_header_with_parameters COMMA parameter_declaration {
        //
        // Only first parameter of one-parameter functions can be void
        // The check for named parameters not being void is done in parameter_declarator
        //
        if ($3.param.type->getBasicType() == EbtVoid) {
            //
            // This parameter > first is void
            //
            parseContext.error($2.loc, "cannot be an argument type except for '(void)'", "void", "");
            delete $3.param.type;
        } else {
            // Add the parameter
            $$ = $1;
            $1->addParameter($3.param);
        }
    }
    ;

function_header
    : fully_specified_type IDENTIFIER LEFT_PAREN {
        if ($1.qualifier.storage != EvqGlobal && $1.qualifier.storage != EvqTemporary) {
            parseContext.error($2.loc, "no qualifiers allowed for function return",
                               GetStorageQualifierString($1.qualifier.storage), "");
        }
        if ($1.arraySizes)
            parseContext.arraySizeRequiredCheck($1.loc, *$1.arraySizes);

        // Add the function as a prototype after parsing it (we do not support recursion)
        TFunction *function;
        TType type($1);

        // Potentially rename shader entry point function.  No-op most of the time.
        parseContext.renameShaderFunction($2.string);

        // Make the function
        function = new TFunction($2.string, type);
        $$ = function;
    }
    ;

parameter_declarator
    // Type + name
    : type_specifier IDENTIFIER {
        if ($1.arraySizes) {
            parseContext.profileRequires($1.loc, ENoProfile, 120, E_GL_3DL_array_objects, "arrayed type");
            parseContext.profileRequires($1.loc, EEsProfile, 300, 0, "arrayed type");
            parseContext.arraySizeRequiredCheck($1.loc, *$1.arraySizes);
        }
        if ($1.basicType == EbtVoid) {
            parseContext.error($2.loc, "illegal use of type 'void'", $2.string->c_str(), "");
        }
        parseContext.reservedErrorCheck($2.loc, *$2.string);

        TParameter param = {$2.string, new TType($1)};
        $$.loc = $2.loc;
        $$.param = param;
    }
    | type_specifier IDENTIFIER array_specifier {
        if ($1.arraySizes) {
            parseContext.profileRequires($1.loc, ENoProfile, 120, E_GL_3DL_array_objects, "arrayed type");
            parseContext.profileRequires($1.loc, EEsProfile, 300, 0, "arrayed type");
            parseContext.arraySizeRequiredCheck($1.loc, *$1.arraySizes);
        }
        TType* type = new TType($1);
        type->transferArraySizes($3.arraySizes);
        type->copyArrayInnerSizes($1.arraySizes);

        parseContext.arrayOfArrayVersionCheck($2.loc, type->getArraySizes());
        parseContext.arraySizeRequiredCheck($3.loc, *$3.arraySizes);
        parseContext.reservedErrorCheck($2.loc, *$2.string);

        TParameter param = { $2.string, type };

        $$.loc = $2.loc;
        $$.param = param;
    }
    ;

parameter_declaration
    //
    // With name
    //
    : type_qualifier parameter_declarator {
        $$ = $2;
        if ($1.qualifier.precision != EpqNone)
            $$.param.type->getQualifier().precision = $1.qualifier.precision;
        parseContext.precisionQualifierCheck($$.loc, $$.param.type->getBasicType(), $$.param.type->getQualifier());

        parseContext.checkNoShaderLayouts($1.loc, $1.shaderQualifiers);
        parseContext.parameterTypeCheck($2.loc, $1.qualifier.storage, *$$.param.type);
        parseContext.paramCheckFix($1.loc, $1.qualifier, *$$.param.type);

    }
    | parameter_declarator {
        $$ = $1;

        parseContext.parameterTypeCheck($1.loc, EvqIn, *$1.param.type);
        parseContext.paramCheckFixStorage($1.loc, EvqTemporary, *$$.param.type);
        parseContext.precisionQualifierCheck($$.loc, $$.param.type->getBasicType(), $$.param.type->getQualifier());
    }
    //
    // Without name
    //
    | type_qualifier parameter_type_specifier {
        $$ = $2;
        if ($1.qualifier.precision != EpqNone)
            $$.param.type->getQualifier().precision = $1.qualifier.precision;
        parseContext.precisionQualifierCheck($1.loc, $$.param.type->getBasicType(), $$.param.type->getQualifier());

        parseContext.checkNoShaderLayouts($1.loc, $1.shaderQualifiers);
        parseContext.parameterTypeCheck($2.loc, $1.qualifier.storage, *$$.param.type);
        parseContext.paramCheckFix($1.loc, $1.qualifier, *$$.param.type);
    }
    | parameter_type_specifier {
        $$ = $1;

        parseContext.parameterTypeCheck($1.loc, EvqIn, *$1.param.type);
        parseContext.paramCheckFixStorage($1.loc, EvqTemporary, *$$.param.type);
        parseContext.precisionQualifierCheck($$.loc, $$.param.type->getBasicType(), $$.param.type->getQualifier());
    }
    ;

parameter_type_specifier
    : type_specifier {
        TParameter param = { 0, new TType($1) };
        $$.param = param;
        if ($1.arraySizes)
            parseContext.arraySizeRequiredCheck($1.loc, *$1.arraySizes);
    }
    ;

init_declarator_list
    : single_declaration {
        $$ = $1;
    }
    | init_declarator_list COMMA IDENTIFIER {
        $$ = $1;
        parseContext.declareVariable($3.loc, *$3.string, $1.type);
    }
    | init_declarator_list COMMA IDENTIFIER array_specifier {
        $$ = $1;
        parseContext.declareVariable($3.loc, *$3.string, $1.type, $4.arraySizes);
    }
    | init_declarator_list COMMA IDENTIFIER array_specifier EQUAL initializer {
        $$.type = $1.type;
        TIntermNode* initNode = parseContext.declareVariable($3.loc, *$3.string, $1.type, $4.arraySizes, $6);
        $$.intermNode = parseContext.intermediate.growAggregate($1.intermNode, initNode, $5.loc);
    }
    | init_declarator_list COMMA IDENTIFIER EQUAL initializer {
        $$.type = $1.type;
        TIntermNode* initNode = parseContext.declareVariable($3.loc, *$3.string, $1.type, 0, $5);
        $$.intermNode = parseContext.intermediate.growAggregate($1.intermNode, initNode, $4.loc);
    }
    ;

single_declaration
    : fully_specified_type {
        $$.type = $1;
        $$.intermNode = 0;

    }
    | fully_specified_type IDENTIFIER {
        $$.type = $1;
        $$.intermNode = 0;
        parseContext.declareVariable($2.loc, *$2.string, $1);
    }
    | fully_specified_type IDENTIFIER array_specifier {
        $$.type = $1;
        $$.intermNode = 0;
        parseContext.declareVariable($2.loc, *$2.string, $1, $3.arraySizes);
    }
    | fully_specified_type IDENTIFIER array_specifier EQUAL initializer {
        $$.type = $1;
        TIntermNode* initNode = parseContext.declareVariable($2.loc, *$2.string, $1, $3.arraySizes, $5);
        $$.intermNode = parseContext.intermediate.growAggregate(0, initNode, $4.loc);
    }
    | fully_specified_type IDENTIFIER EQUAL initializer {
        $$.type = $1;
        TIntermNode* initNode = parseContext.declareVariable($2.loc, *$2.string, $1, 0, $4);
        $$.intermNode = parseContext.intermediate.growAggregate(0, initNode, $3.loc);
    }

// Grammar Note:  No 'enum', or 'typedef'.

fully_specified_type
    : type_specifier {
        $$ = $1;

        parseContext.globalQualifierTypeCheck($1.loc, $1.qualifier, $$);
        if ($1.arraySizes) {
            parseContext.profileRequires($1.loc, ENoProfile, 120, E_GL_3DL_array_objects, "arrayed type");
            parseContext.profileRequires($1.loc, EEsProfile, 300, 0, "arrayed type");
        }
        parseContext.precisionQualifierCheck($$.loc, $$.basicType, $$.qualifier);
    }
    | type_qualifier type_specifier  {
        parseContext.globalQualifierFixCheck($1.loc, $1.qualifier);
        parseContext.globalQualifierTypeCheck($1.loc, $1.qualifier, $2);

        if ($2.arraySizes) {
            parseContext.profileRequires($2.loc, ENoProfile, 120, E_GL_3DL_array_objects, "arrayed type");
            parseContext.profileRequires($2.loc, EEsProfile, 300, 0, "arrayed type");
        }

        if ($2.arraySizes && parseContext.arrayQualifierError($2.loc, $1.qualifier))
            $2.arraySizes = nullptr;

        parseContext.checkNoShaderLayouts($2.loc, $1.shaderQualifiers);
        $2.shaderQualifiers.merge($1.shaderQualifiers);
        parseContext.mergeQualifiers($2.loc, $2.qualifier, $1.qualifier, true);
        parseContext.precisionQualifierCheck($2.loc, $2.basicType, $2.qualifier);

        $$ = $2;

        if (! $$.qualifier.isInterpolation() &&
            ((parseContext.language == EShLangVertex   && $$.qualifier.storage == EvqVaryingOut) ||
             (parseContext.language == EShLangFragment && $$.qualifier.storage == EvqVaryingIn)))
            $$.qualifier.smooth = true;
    }
    ;

invariant_qualifier
    : INVARIANT {
        parseContext.globalCheck($1.loc, "invariant");
        parseContext.profileRequires($$.loc, ENoProfile, 120, 0, "invariant");
        $$.init($1.loc);
        $$.qualifier.invariant = true;
    }
    ;

interpolation_qualifier
    : SMOOTH {
        parseContext.globalCheck($1.loc, "smooth");
        parseContext.profileRequires($1.loc, ENoProfile, 130, 0, "smooth");
        parseContext.profileRequires($1.loc, EEsProfile, 300, 0, "smooth");
        $$.init($1.loc);
        $$.qualifier.smooth = true;
    }
    | FLAT {
        parseContext.globalCheck($1.loc, "flat");
        parseContext.profileRequires($1.loc, ENoProfile, 130, 0, "flat");
        parseContext.profileRequires($1.loc, EEsProfile, 300, 0, "flat");
        $$.init($1.loc);
        $$.qualifier.flat = true;
    }

    ;

layout_qualifier
    : LAYOUT LEFT_PAREN layout_qualifier_id_list RIGHT_PAREN {
        $$ = $3;
    }
    ;

layout_qualifier_id_list
    : layout_qualifier_id {
        $$ = $1;
    }
    | layout_qualifier_id_list COMMA layout_qualifier_id {
        $$ = $1;
        $$.shaderQualifiers.merge($3.shaderQualifiers);
        parseContext.mergeObjectLayoutQualifiers($$.qualifier, $3.qualifier, false);
    }

layout_qualifier_id
    : IDENTIFIER {
        $$.init($1.loc);
        parseContext.setLayoutQualifier($1.loc, $$, *$1.string);
    }
    | IDENTIFIER EQUAL constant_expression {
        $$.init($1.loc);
        parseContext.setLayoutQualifier($1.loc, $$, *$1.string, $3);
    }
    | SHARED { // because "shared" is both an identifier and a keyword
        $$.init($1.loc);
        TString strShared("shared");
        parseContext.setLayoutQualifier($1.loc, $$, strShared);
    }
    ;



type_qualifier
    : single_type_qualifier {
        $$ = $1;
    }
    | type_qualifier single_type_qualifier {
        $$ = $1;
        if ($$.basicType == EbtVoid)
            $$.basicType = $2.basicType;

        $$.shaderQualifiers.merge($2.shaderQualifiers);
        parseContext.mergeQualifiers($$.loc, $$.qualifier, $2.qualifier, false);
    }
    ;

single_type_qualifier
    : storage_qualifier {
        $$ = $1;
    }
    | layout_qualifier {
        $$ = $1;
    }
    | precision_qualifier {
        parseContext.checkPrecisionQualifier($1.loc, $1.qualifier.precision);
        $$ = $1;
    }
    | interpolation_qualifier {
        // allow inheritance of storage qualifier from block declaration
        $$ = $1;
    }
    | invariant_qualifier {
        // allow inheritance of storage qualifier from block declaration
        $$ = $1;
    }

    ;

storage_qualifier
    : CONST {
        $$.init($1.loc);
        $$.qualifier.storage = EvqConst;  // will later turn into EvqConstReadOnly, if the initializer is not constant
    }
    | INOUT {
        parseContext.globalCheck($1.loc, "inout");
        $$.init($1.loc);
        $$.qualifier.storage = EvqInOut;
    }
    | IN {
        parseContext.globalCheck($1.loc, "in");
        $$.init($1.loc);
        // whether this is a parameter "in" or a pipeline "in" will get sorted out a bit later
        $$.qualifier.storage = EvqIn;
    }
    | OUT {
        parseContext.globalCheck($1.loc, "out");
        $$.init($1.loc);
        // whether this is a parameter "out" or a pipeline "out" will get sorted out a bit later
        $$.qualifier.storage = EvqOut;
    }
    | CENTROID {
        parseContext.profileRequires($1.loc, ENoProfile, 120, 0, "centroid");
        parseContext.profileRequires($1.loc, EEsProfile, 300, 0, "centroid");
        parseContext.globalCheck($1.loc, "centroid");
        $$.init($1.loc);
        $$.qualifier.centroid = true;
    }
    | UNIFORM {
        parseContext.globalCheck($1.loc, "uniform");
        $$.init($1.loc);
        $$.qualifier.storage = EvqUniform;
    }

    ;



type_specifier
    : type_specifier_nonarray type_parameter_specifier_opt {
        $$ = $1;
        $$.qualifier.precision = parseContext.getDefaultPrecision($$);
        $$.typeParameters = $2;
    }
    | type_specifier_nonarray type_parameter_specifier_opt array_specifier {
        parseContext.arrayOfArrayVersionCheck($3.loc, $3.arraySizes);
        $$ = $1;
        $$.qualifier.precision = parseContext.getDefaultPrecision($$);
        $$.typeParameters = $2;
        $$.arraySizes = $3.arraySizes;
    }
    ;

array_specifier
    : LEFT_BRACKET RIGHT_BRACKET {
        $$.loc = $1.loc;
        $$.arraySizes = new TArraySizes;
        $$.arraySizes->addInnerSize();
    }
    | LEFT_BRACKET conditional_expression RIGHT_BRACKET {
        $$.loc = $1.loc;
        $$.arraySizes = new TArraySizes;

        TArraySize size;
        parseContext.arraySizeCheck($2->getLoc(), $2, size, "array size");
        $$.arraySizes->addInnerSize(size);
    }
    | array_specifier LEFT_BRACKET RIGHT_BRACKET {
        $$ = $1;
        $$.arraySizes->addInnerSize();
    }
    | array_specifier LEFT_BRACKET conditional_expression RIGHT_BRACKET {
        $$ = $1;

        TArraySize size;
        parseContext.arraySizeCheck($3->getLoc(), $3, size, "array size");
        $$.arraySizes->addInnerSize(size);
    }
    ;

type_parameter_specifier_opt
    : type_parameter_specifier {
        $$ = $1;
    }
    | /* May be null */ {
        $$ = 0;
    }
    ;

type_parameter_specifier
    : LEFT_ANGLE type_parameter_specifier_list RIGHT_ANGLE {
        $$ = $2;
    }
    ;

type_parameter_specifier_list
    : unary_expression {
        $$ = new TArraySizes;

        TArraySize size;
        parseContext.arraySizeCheck($1->getLoc(), $1, size, "type parameter");
        $$->addInnerSize(size);
    }
    | type_parameter_specifier_list COMMA unary_expression {
        $$ = $1;

        TArraySize size;
        parseContext.arraySizeCheck($3->getLoc(), $3, size, "type parameter");
        $$->addInnerSize(size);
    }
    ;

type_specifier_nonarray
    : VOID {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtVoid;
    }
    | FLOAT {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtFloat;
    }
    | INT {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtInt;
    }
    | UINT {
        parseContext.fullIntegerCheck($1.loc, "unsigned integer");
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtUint;
    }
    | BOOL {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtBool;
    }
    | VEC2 {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtFloat;
        $$.setVector(2);
    }
    | VEC3 {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtFloat;
        $$.setVector(3);
    }
    | VEC4 {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtFloat;
        $$.setVector(4);
    }
    | BVEC2 {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtBool;
        $$.setVector(2);
    }
    | BVEC3 {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtBool;
        $$.setVector(3);
    }
    | BVEC4 {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtBool;
        $$.setVector(4);
    }
    | IVEC2 {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtInt;
        $$.setVector(2);
    }
    | IVEC3 {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtInt;
        $$.setVector(3);
    }
    | IVEC4 {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtInt;
        $$.setVector(4);
    }
    | UVEC2 {
        parseContext.fullIntegerCheck($1.loc, "unsigned integer vector");
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtUint;
        $$.setVector(2);
    }
    | UVEC3 {
        parseContext.fullIntegerCheck($1.loc, "unsigned integer vector");
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtUint;
        $$.setVector(3);
    }
    | UVEC4 {
        parseContext.fullIntegerCheck($1.loc, "unsigned integer vector");
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtUint;
        $$.setVector(4);
    }
    | MAT2 {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtFloat;
        $$.setMatrix(2, 2);
    }
    | MAT3 {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtFloat;
        $$.setMatrix(3, 3);
    }
    | MAT4 {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtFloat;
        $$.setMatrix(4, 4);
    }
    | MAT2X2 {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtFloat;
        $$.setMatrix(2, 2);
    }
    | MAT2X3 {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtFloat;
        $$.setMatrix(2, 3);
    }
    | MAT2X4 {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtFloat;
        $$.setMatrix(2, 4);
    }
    | MAT3X2 {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtFloat;
        $$.setMatrix(3, 2);
    }
    | MAT3X3 {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtFloat;
        $$.setMatrix(3, 3);
    }
    | MAT3X4 {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtFloat;
        $$.setMatrix(3, 4);
    }
    | MAT4X2 {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtFloat;
        $$.setMatrix(4, 2);
    }
    | MAT4X3 {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtFloat;
        $$.setMatrix(4, 3);
    }
    | MAT4X4 {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtFloat;
        $$.setMatrix(4, 4);
    }

    | SAMPLER2D {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtFloat, Esd2D);
    }
    | SAMPLER3D {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtFloat, Esd3D);
    }
    | SAMPLERCUBE {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtFloat, EsdCube);
    }
    | SAMPLER2DSHADOW {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtFloat, Esd2D, false, true);
    }
    | SAMPLERCUBESHADOW {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtFloat, EsdCube, false, true);
    }
    | SAMPLER2DARRAY {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtFloat, Esd2D, true);
    }
    | SAMPLER2DARRAYSHADOW {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtFloat, Esd2D, true, true);
    }

    | ISAMPLER2D {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtInt, Esd2D);
    }
    | ISAMPLER3D {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtInt, Esd3D);
    }
    | ISAMPLERCUBE {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtInt, EsdCube);
    }
    | ISAMPLER2DARRAY {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtInt, Esd2D, true);
    }
    | USAMPLER2D {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtUint, Esd2D);
    }
    | USAMPLER3D {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtUint, Esd3D);
    }
    | USAMPLERCUBE {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtUint, EsdCube);
    }

    | USAMPLER2DARRAY {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtUint, Esd2D, true);
    }
    | TEXTURE2D {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setTexture(EbtFloat, Esd2D);
    }
    | TEXTURE3D {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setTexture(EbtFloat, Esd3D);
    }
    | TEXTURE2DARRAY {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setTexture(EbtFloat, Esd2D, true);
    }
    | TEXTURECUBE {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setTexture(EbtFloat, EsdCube);
    }
    | ITEXTURE2D {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setTexture(EbtInt, Esd2D);
    }
    | ITEXTURE3D {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setTexture(EbtInt, Esd3D);
    }
    | ITEXTURECUBE {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setTexture(EbtInt, EsdCube);
    }
    | ITEXTURE2DARRAY {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setTexture(EbtInt, Esd2D, true);
    }
    | UTEXTURE2D {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setTexture(EbtUint, Esd2D);
    }
    | UTEXTURE3D {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setTexture(EbtUint, Esd3D);
    }
    | UTEXTURECUBE {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setTexture(EbtUint, EsdCube);
    }
    | UTEXTURE2DARRAY {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setTexture(EbtUint, Esd2D, true);
    }
    | SAMPLER {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setPureSampler(false);
    }
    | SAMPLERSHADOW {
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setPureSampler(true);
    }

    | struct_specifier {
        $$ = $1;
        $$.qualifier.storage = parseContext.symbolTable.atGlobalLevel() ? EvqGlobal : EvqTemporary;
        parseContext.structTypeCheck($$.loc, $$);
    }
    | TYPE_NAME {
        //
        // This is for user defined type names.  The lexical phase looked up the
        // type.
        //
        if (const TVariable* variable = ($1.symbol)->getAsVariable()) {
            const TType& structure = variable->getType();
            $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
            $$.basicType = EbtStruct;
            $$.userDef = &structure;
        } else
            parseContext.error($1.loc, "expected type name", $1.string->c_str(), "");
    }
    ;

precision_qualifier
    : HIGH_PRECISION {
        parseContext.profileRequires($1.loc, ENoProfile, 130, 0, "highp precision qualifier");
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        parseContext.handlePrecisionQualifier($1.loc, $$.qualifier, EpqHigh);
    }
    | MEDIUM_PRECISION {
        parseContext.profileRequires($1.loc, ENoProfile, 130, 0, "mediump precision qualifier");
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        parseContext.handlePrecisionQualifier($1.loc, $$.qualifier, EpqMedium);
    }
    | LOW_PRECISION {
        parseContext.profileRequires($1.loc, ENoProfile, 130, 0, "lowp precision qualifier");
        $$.init($1.loc, parseContext.symbolTable.atGlobalLevel());
        parseContext.handlePrecisionQualifier($1.loc, $$.qualifier, EpqLow);
    }
    ;

struct_specifier
    : STRUCT IDENTIFIER LEFT_BRACE { parseContext.nestedStructCheck($1.loc); } struct_declaration_list RIGHT_BRACE {
        TType* structure = new TType($5, *$2.string);
        parseContext.structArrayCheck($2.loc, *structure);
        TVariable* userTypeDef = new TVariable($2.string, *structure, true);
        if (! parseContext.symbolTable.insert(*userTypeDef))
            parseContext.error($2.loc, "redefinition", $2.string->c_str(), "struct");
        $$.init($1.loc);
        $$.basicType = EbtStruct;
        $$.userDef = structure;
        --parseContext.structNestingLevel;
    }
    | STRUCT LEFT_BRACE { parseContext.nestedStructCheck($1.loc); } struct_declaration_list RIGHT_BRACE {
        TType* structure = new TType($4, TString(""));
        $$.init($1.loc);
        $$.basicType = EbtStruct;
        $$.userDef = structure;
        --parseContext.structNestingLevel;
    }
    ;

struct_declaration_list
    : struct_declaration {
        $$ = $1;
    }
    | struct_declaration_list struct_declaration {
        $$ = $1;
        for (unsigned int i = 0; i < $2->size(); ++i) {
            for (unsigned int j = 0; j < $$->size(); ++j) {
                if ((*$$)[j].type->getFieldName() == (*$2)[i].type->getFieldName())
                    parseContext.error((*$2)[i].loc, "duplicate member name:", "", (*$2)[i].type->getFieldName().c_str());
            }
            $$->push_back((*$2)[i]);
        }
    }
    ;

struct_declaration
    : type_specifier struct_declarator_list SEMICOLON {
        if ($1.arraySizes) {
            parseContext.profileRequires($1.loc, ENoProfile, 120, E_GL_3DL_array_objects, "arrayed type");
            parseContext.profileRequires($1.loc, EEsProfile, 300, 0, "arrayed type");
            if (parseContext.isEsProfile())
                parseContext.arraySizeRequiredCheck($1.loc, *$1.arraySizes);
        }

        $$ = $2;

        parseContext.voidErrorCheck($1.loc, (*$2)[0].type->getFieldName(), $1.basicType);
        parseContext.precisionQualifierCheck($1.loc, $1.basicType, $1.qualifier);

        for (unsigned int i = 0; i < $$->size(); ++i) {
            TType type($1);
            type.setFieldName((*$$)[i].type->getFieldName());
            type.transferArraySizes((*$$)[i].type->getArraySizes());
            type.copyArrayInnerSizes($1.arraySizes);
            parseContext.arrayOfArrayVersionCheck((*$$)[i].loc, type.getArraySizes());
            (*$$)[i].type->shallowCopy(type);
        }
    }
    | type_qualifier type_specifier struct_declarator_list SEMICOLON {
        if ($2.arraySizes) {
            parseContext.profileRequires($2.loc, ENoProfile, 120, E_GL_3DL_array_objects, "arrayed type");
            parseContext.profileRequires($2.loc, EEsProfile, 300, 0, "arrayed type");
            if (parseContext.isEsProfile())
                parseContext.arraySizeRequiredCheck($2.loc, *$2.arraySizes);
        }

        $$ = $3;

        parseContext.memberQualifierCheck($1);
        parseContext.voidErrorCheck($2.loc, (*$3)[0].type->getFieldName(), $2.basicType);
        parseContext.mergeQualifiers($2.loc, $2.qualifier, $1.qualifier, true);
        parseContext.precisionQualifierCheck($2.loc, $2.basicType, $2.qualifier);

        for (unsigned int i = 0; i < $$->size(); ++i) {
            TType type($2);
            type.setFieldName((*$$)[i].type->getFieldName());
            type.transferArraySizes((*$$)[i].type->getArraySizes());
            type.copyArrayInnerSizes($2.arraySizes);
            parseContext.arrayOfArrayVersionCheck((*$$)[i].loc, type.getArraySizes());
            (*$$)[i].type->shallowCopy(type);
        }
    }
    ;

struct_declarator_list
    : struct_declarator {
        $$ = new TTypeList;
        $$->push_back($1);
    }
    | struct_declarator_list COMMA struct_declarator {
        $$->push_back($3);
    }
    ;

struct_declarator
    : IDENTIFIER {
        $$.type = new TType(EbtVoid);
        $$.loc = $1.loc;
        $$.type->setFieldName(*$1.string);
    }
    | IDENTIFIER array_specifier {
        parseContext.arrayOfArrayVersionCheck($1.loc, $2.arraySizes);

        $$.type = new TType(EbtVoid);
        $$.loc = $1.loc;
        $$.type->setFieldName(*$1.string);
        $$.type->transferArraySizes($2.arraySizes);
    }
    ;

initializer
    : assignment_expression {
        $$ = $1;
    }

    ;



declaration_statement
    : declaration { $$ = $1; }
    ;

statement
    : compound_statement  { $$ = $1; }
    | simple_statement    { $$ = $1; }
    ;

// Grammar Note:  labeled statements for switch statements only; 'goto' is not supported.

simple_statement
    : declaration_statement { $$ = $1; }
    | expression_statement  { $$ = $1; }
    | selection_statement   { $$ = $1; }
    | switch_statement      { $$ = $1; }
    | case_label            { $$ = $1; }
    | iteration_statement   { $$ = $1; }
    | jump_statement        { $$ = $1; }

    ;



compound_statement
    : LEFT_BRACE RIGHT_BRACE { $$ = 0; }
    | LEFT_BRACE {
        parseContext.symbolTable.push();
        ++parseContext.statementNestingLevel;
    }
      statement_list {
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        --parseContext.statementNestingLevel;
    }
      RIGHT_BRACE {
        if ($3 && $3->getAsAggregate())
            $3->getAsAggregate()->setOperator(EOpSequence);
        $$ = $3;
    }
    ;

statement_no_new_scope
    : compound_statement_no_new_scope { $$ = $1; }
    | simple_statement                { $$ = $1; }
    ;

statement_scoped
    : {
        ++parseContext.controlFlowNestingLevel;
    }
      compound_statement  {
        --parseContext.controlFlowNestingLevel;
        $$ = $2;
    }
    | {
        parseContext.symbolTable.push();
        ++parseContext.statementNestingLevel;
        ++parseContext.controlFlowNestingLevel;
    }
      simple_statement {
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        --parseContext.statementNestingLevel;
        --parseContext.controlFlowNestingLevel;
        $$ = $2;
    }

compound_statement_no_new_scope
    // Statement that doesn't create a new scope, for selection_statement, iteration_statement
    : LEFT_BRACE RIGHT_BRACE {
        $$ = 0;
    }
    | LEFT_BRACE statement_list RIGHT_BRACE {
        if ($2 && $2->getAsAggregate())
            $2->getAsAggregate()->setOperator(EOpSequence);
        $$ = $2;
    }
    ;

statement_list
    : statement {
        $$ = parseContext.intermediate.makeAggregate($1);
        if ($1 && $1->getAsBranchNode() && ($1->getAsBranchNode()->getFlowOp() == EOpCase ||
                                            $1->getAsBranchNode()->getFlowOp() == EOpDefault)) {
            parseContext.wrapupSwitchSubsequence(0, $1);
            $$ = 0;  // start a fresh subsequence for what's after this case
        }
    }
    | statement_list statement {
        if ($2 && $2->getAsBranchNode() && ($2->getAsBranchNode()->getFlowOp() == EOpCase ||
                                            $2->getAsBranchNode()->getFlowOp() == EOpDefault)) {
            parseContext.wrapupSwitchSubsequence($1 ? $1->getAsAggregate() : 0, $2);
            $$ = 0;  // start a fresh subsequence for what's after this case
        } else
            $$ = parseContext.intermediate.growAggregate($1, $2);
    }
    ;

expression_statement
    : SEMICOLON  { $$ = 0; }
    | expression SEMICOLON  { $$ = static_cast<TIntermNode*>($1); }
    ;

selection_statement
    : selection_statement_nonattributed {
        $$ = $1;
    }


selection_statement_nonattributed
    : IF LEFT_PAREN expression RIGHT_PAREN selection_rest_statement {
        parseContext.boolCheck($1.loc, $3);
        $$ = parseContext.intermediate.addSelection($3, $5, $1.loc);
    }
    ;

selection_rest_statement
    : statement_scoped ELSE statement_scoped {
        $$.node1 = $1;
        $$.node2 = $3;
    }
    | statement_scoped {
        $$.node1 = $1;
        $$.node2 = 0;
    }
    ;

condition
    // In 1996 c++ draft, conditions can include single declarations
    : expression {
        $$ = $1;
        parseContext.boolCheck($1->getLoc(), $1);
    }
    | fully_specified_type IDENTIFIER EQUAL initializer {
        parseContext.boolCheck($2.loc, $1);

        TType type($1);
        TIntermNode* initNode = parseContext.declareVariable($2.loc, *$2.string, $1, 0, $4);
        if (initNode)
            $$ = initNode->getAsTyped();
        else
            $$ = 0;
    }
    ;

switch_statement
    : switch_statement_nonattributed {
        $$ = $1;
    }


switch_statement_nonattributed
    : SWITCH LEFT_PAREN expression RIGHT_PAREN {
        // start new switch sequence on the switch stack
        ++parseContext.controlFlowNestingLevel;
        ++parseContext.statementNestingLevel;
        parseContext.switchSequenceStack.push_back(new TIntermSequence);
        parseContext.switchLevel.push_back(parseContext.statementNestingLevel);
        parseContext.symbolTable.push();
    }
    LEFT_BRACE switch_statement_list RIGHT_BRACE {
        $$ = parseContext.addSwitch($1.loc, $3, $7 ? $7->getAsAggregate() : 0);
        delete parseContext.switchSequenceStack.back();
        parseContext.switchSequenceStack.pop_back();
        parseContext.switchLevel.pop_back();
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        --parseContext.statementNestingLevel;
        --parseContext.controlFlowNestingLevel;
    }
    ;

switch_statement_list
    : /* nothing */ {
        $$ = 0;
    }
    | statement_list {
        $$ = $1;
    }
    ;

case_label
    : CASE expression COLON {
        $$ = 0;
        if (parseContext.switchLevel.size() == 0)
            parseContext.error($1.loc, "cannot appear outside switch statement", "case", "");
        else if (parseContext.switchLevel.back() != parseContext.statementNestingLevel)
            parseContext.error($1.loc, "cannot be nested inside control flow", "case", "");
        else {
            parseContext.constantValueCheck($2, "case");
            parseContext.integerCheck($2, "case");
            $$ = parseContext.intermediate.addBranch(EOpCase, $2, $1.loc);
        }
    }
    | DEFAULT COLON {
        $$ = 0;
        if (parseContext.switchLevel.size() == 0)
            parseContext.error($1.loc, "cannot appear outside switch statement", "default", "");
        else if (parseContext.switchLevel.back() != parseContext.statementNestingLevel)
            parseContext.error($1.loc, "cannot be nested inside control flow", "default", "");
        else
            $$ = parseContext.intermediate.addBranch(EOpDefault, $1.loc);
    }
    ;

iteration_statement
    : iteration_statement_nonattributed {
        $$ = $1;
    }


iteration_statement_nonattributed
    : WHILE LEFT_PAREN {
        if (! parseContext.limits.whileLoops)
            parseContext.error($1.loc, "while loops not available", "limitation", "");
        parseContext.symbolTable.push();
        ++parseContext.loopNestingLevel;
        ++parseContext.statementNestingLevel;
        ++parseContext.controlFlowNestingLevel;
    }
      condition RIGHT_PAREN statement_no_new_scope {
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        $$ = parseContext.intermediate.addLoop($6, $4, 0, true, $1.loc);
        --parseContext.loopNestingLevel;
        --parseContext.statementNestingLevel;
        --parseContext.controlFlowNestingLevel;
    }
    | DO {
        ++parseContext.loopNestingLevel;
        ++parseContext.statementNestingLevel;
        ++parseContext.controlFlowNestingLevel;
    }
      statement WHILE LEFT_PAREN expression RIGHT_PAREN SEMICOLON {
        if (! parseContext.limits.whileLoops)
            parseContext.error($1.loc, "do-while loops not available", "limitation", "");

        parseContext.boolCheck($8.loc, $6);

        $$ = parseContext.intermediate.addLoop($3, $6, 0, false, $4.loc);
        --parseContext.loopNestingLevel;
        --parseContext.statementNestingLevel;
        --parseContext.controlFlowNestingLevel;
    }
    | FOR LEFT_PAREN {
        parseContext.symbolTable.push();
        ++parseContext.loopNestingLevel;
        ++parseContext.statementNestingLevel;
        ++parseContext.controlFlowNestingLevel;
    }
      for_init_statement for_rest_statement RIGHT_PAREN statement_no_new_scope {
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        $$ = parseContext.intermediate.makeAggregate($4, $2.loc);
        TIntermLoop* forLoop = parseContext.intermediate.addLoop($7, reinterpret_cast<TIntermTyped*>($5.node1), reinterpret_cast<TIntermTyped*>($5.node2), true, $1.loc);
        if (! parseContext.limits.nonInductiveForLoops)
            parseContext.inductiveLoopCheck($1.loc, $4, forLoop);
        $$ = parseContext.intermediate.growAggregate($$, forLoop, $1.loc);
        $$->getAsAggregate()->setOperator(EOpSequence);
        --parseContext.loopNestingLevel;
        --parseContext.statementNestingLevel;
        --parseContext.controlFlowNestingLevel;
    }
    ;

for_init_statement
    : expression_statement {
        $$ = $1;
    }
    | declaration_statement {
        $$ = $1;
    }
    ;

conditionopt
    : condition {
        $$ = $1;
    }
    | /* May be null */ {
        $$ = 0;
    }
    ;

for_rest_statement
    : conditionopt SEMICOLON {
        $$.node1 = $1;
        $$.node2 = 0;
    }
    | conditionopt SEMICOLON expression  {
        $$.node1 = $1;
        $$.node2 = $3;
    }
    ;

jump_statement
    : CONTINUE SEMICOLON {
        if (parseContext.loopNestingLevel <= 0)
            parseContext.error($1.loc, "continue statement only allowed in loops", "", "");
        $$ = parseContext.intermediate.addBranch(EOpContinue, $1.loc);
    }
    | BREAK SEMICOLON {
        if (parseContext.loopNestingLevel + parseContext.switchSequenceStack.size() <= 0)
            parseContext.error($1.loc, "break statement only allowed in switch and loops", "", "");
        $$ = parseContext.intermediate.addBranch(EOpBreak, $1.loc);
    }
    | RETURN SEMICOLON {
        $$ = parseContext.intermediate.addBranch(EOpReturn, $1.loc);
        if (parseContext.currentFunctionType->getBasicType() != EbtVoid)
            parseContext.error($1.loc, "non-void function must return a value", "return", "");
        if (parseContext.inMain)
            parseContext.postEntryPointReturn = true;
    }
    | RETURN expression SEMICOLON {
        $$ = parseContext.handleReturnValue($1.loc, $2);
    }
    | DISCARD SEMICOLON {
        parseContext.requireStage($1.loc, EShLangFragment, "discard");
        $$ = parseContext.intermediate.addBranch(EOpKill, $1.loc);
    }
    ;

// Grammar Note:  No 'goto'.  Gotos are not supported.

translation_unit
    : external_declaration {
        $$ = $1;
        parseContext.intermediate.setTreeRoot($$);
    }
    | translation_unit external_declaration {
        if ($2 != nullptr) {
            $$ = parseContext.intermediate.growAggregate($1, $2);
            parseContext.intermediate.setTreeRoot($$);
        }
    }
    ;

external_declaration
    : function_definition {
        $$ = $1;
    }
    | declaration {
        $$ = $1;
    }

    ;

function_definition
    : function_prototype {
        $1.function = parseContext.handleFunctionDeclarator($1.loc, *$1.function, false /* not prototype */);
        $1.intermNode = parseContext.handleFunctionDefinition($1.loc, *$1.function);
    }
    compound_statement_no_new_scope {
        //   May be best done as post process phase on intermediate code
        if (parseContext.currentFunctionType->getBasicType() != EbtVoid && ! parseContext.functionReturnsValue)
            parseContext.error($1.loc, "function does not return a value:", "", $1.function->getName().c_str());
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        $$ = parseContext.intermediate.growAggregate($1.intermNode, $3);
        parseContext.intermediate.setAggregateOperator($$, EOpFunction, $1.function->getType(), $1.loc);
        $$->getAsAggregate()->setName($1.function->getMangledName().c_str());

        // store the pragma information for debug and optimize and other vendor specific
        // information. This information can be queried from the parse tree
        $$->getAsAggregate()->setOptimize(parseContext.contextPragma.optimize);
        $$->getAsAggregate()->setDebug(parseContext.contextPragma.debug);
        $$->getAsAggregate()->setPragmaTable(parseContext.contextPragma.pragmaTable);
    }
    ;



%%
