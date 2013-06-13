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

/**
 * This is bison grammar and production code for parsing the OpenGL 2.0 shading
 * languages.
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

#ifdef _WIN32
    #define YYPARSE_PARAM parseContext
    #define YYPARSE_PARAM_DECL TParseContext&
    #define YY_DECL int yylex(YYSTYPE* pyylval, TParseContext& parseContext)
    #define YYLEX_PARAM parseContext
#else
    #define YYPARSE_PARAM parseContextLocal
    #define parseContext (*((TParseContext*)(parseContextLocal)))
    #define YY_DECL int yylex(YYSTYPE* pyylval, void* parseContextLocal)
    #define YYLEX_PARAM (void*)(parseContextLocal)
#endif

extern void yyerror(const char*);

%}

%union {
    struct {
        TSourceLoc line;
        union {
            TString *string;
            int i;
            unsigned int u;
            bool b;
            double d;
        };
        TSymbol* symbol;
    } lex;
    struct {
        TSourceLoc line;
        TOperator op;
        union {
            TIntermNode* intermNode;
            TIntermNodePair nodePair;
            TIntermTyped* intermTypedNode;
            TIntermAggregate* intermAggregate;
        };
        union {
            TPublicType type;
            TFunction* function;
            TParameter param;
            TTypeLine typeLine;
            TTypeList* typeList;
            TArraySizes arraySizes;
        };
    } interm;
}

%{
#ifndef _WIN32
    extern int yylex(YYSTYPE*, void*);
#endif
%}

%pure_parser /* Just in case is called from multiple threads */
%expect 1 /* One shift reduce conflict because of if | else */

%token <lex> ATTRIBUTE VARYING
%token <lex> CONST BOOL FLOAT DOUBLE INT UINT
%token <lex> BREAK CONTINUE DO ELSE FOR IF DISCARD RETURN SWITCH CASE DEFAULT SUBROUTINE
%token <lex> BVEC2 BVEC3 BVEC4 IVEC2 IVEC3 IVEC4 UVEC2 UVEC3 UVEC4 VEC2 VEC3 VEC4
%token <lex> MAT2 MAT3 MAT4 CENTROID IN OUT INOUT
%token <lex> UNIFORM PATCH SAMPLE BUFFER SHARED
%token <lex> COHERENT VOLATILE RESTRICT READONLY WRITEONLY
%token <lex> DVEC2 DVEC3 DVEC4 DMAT2 DMAT3 DMAT4
%token <lex> NOPERSPECTIVE FLAT SMOOTH LAYOUT

%token <lex> MAT2X2 MAT2X3 MAT2X4
%token <lex> MAT3X2 MAT3X3 MAT3X4
%token <lex> MAT4X2 MAT4X3 MAT4X4
%token <lex> DMAT2X2 DMAT2X3 DMAT2X4
%token <lex> DMAT3X2 DMAT3X3 DMAT3X4
%token <lex> DMAT4X2 DMAT4X3 DMAT4X4
%token <lex> ATOMIC_UINT

%token <lex> SAMPLER1D SAMPLER2D SAMPLER3D SAMPLERCUBE SAMPLER1DSHADOW SAMPLER2DSHADOW
%token <lex> SAMPLERCUBESHADOW SAMPLER1DARRAY SAMPLER2DARRAY SAMPLER1DARRAYSHADOW
%token <lex> SAMPLER2DARRAYSHADOW ISAMPLER1D ISAMPLER2D ISAMPLER3D ISAMPLERCUBE
%token <lex> ISAMPLER1DARRAY ISAMPLER2DARRAY USAMPLER1D USAMPLER2D USAMPLER3D
%token <lex> USAMPLERCUBE USAMPLER1DARRAY USAMPLER2DARRAY
%token <lex> SAMPLER2DRECT SAMPLER2DRECTSHADOW ISAMPLER2DRECT USAMPLER2DRECT
%token <lex> SAMPLERBUFFER ISAMPLERBUFFER USAMPLERBUFFER
%token <lex> SAMPLERCUBEARRAY SAMPLERCUBEARRAYSHADOW
%token <lex> ISAMPLERCUBEARRAY USAMPLERCUBEARRAY
%token <lex> SAMPLER2DMS ISAMPLER2DMS USAMPLER2DMS
%token <lex> SAMPLER2DMSARRAY ISAMPLER2DMSARRAY USAMPLER2DMSARRAY

%token <lex> IMAGE1D IIMAGE1D UIMAGE1D IMAGE2D IIMAGE2D
%token <lex> UIMAGE2D IMAGE3D IIMAGE3D UIMAGE3D
%token <lex> IMAGE2DRECT IIMAGE2DRECT UIMAGE2DRECT
%token <lex> IMAGECUBE IIMAGECUBE UIMAGECUBE
%token <lex> IMAGEBUFFER IIMAGEBUFFER UIMAGEBUFFER
%token <lex> IMAGE1DARRAY IIMAGE1DARRAY UIMAGE1DARRAY
%token <lex> IMAGE2DARRAY IIMAGE2DARRAY UIMAGE2DARRAY
%token <lex> IMAGECUBEARRAY IIMAGECUBEARRAY UIMAGECUBEARRAY
%token <lex> IMAGE2DMS IIMAGE2DMS UIMAGE2DMS
%token <lex> IMAGE2DMSARRAY IIMAGE2DMSARRAY UIMAGE2DMSARRAY

%token <lex> STRUCT VOID WHILE

%token <lex> IDENTIFIER TYPE_NAME
%token <lex> FLOATCONSTANT DOUBLECONSTANT INTCONSTANT UINTCONSTANT BOOLCONSTANT
%token <lex> FIELD_SELECTION
%token <lex> LEFT_OP RIGHT_OP
%token <lex> INC_OP DEC_OP LE_OP GE_OP EQ_OP NE_OP
%token <lex> AND_OP OR_OP XOR_OP MUL_ASSIGN DIV_ASSIGN ADD_ASSIGN
%token <lex> MOD_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN
%token <lex> SUB_ASSIGN

%token <lex> LEFT_PAREN RIGHT_PAREN LEFT_BRACKET RIGHT_BRACKET LEFT_BRACE RIGHT_BRACE DOT
%token <lex> COMMA COLON EQUAL SEMICOLON BANG DASH TILDE PLUS STAR SLASH PERCENT
%token <lex> LEFT_ANGLE RIGHT_ANGLE VERTICAL_BAR CARET AMPERSAND QUESTION

%token <lex> INVARIANT PRECISE
%token <lex> HIGH_PRECISION MEDIUM_PRECISION LOW_PRECISION PRECISION

%type <interm> assignment_operator unary_operator
%type <interm.intermTypedNode> variable_identifier primary_expression postfix_expression
%type <interm.intermTypedNode> expression integer_expression assignment_expression
%type <interm.intermTypedNode> unary_expression multiplicative_expression additive_expression
%type <interm.intermTypedNode> relational_expression equality_expression
%type <interm.intermTypedNode> conditional_expression constant_expression
%type <interm.intermTypedNode> logical_or_expression logical_xor_expression logical_and_expression
%type <interm.intermTypedNode> shift_expression and_expression exclusive_or_expression inclusive_or_expression
%type <interm.intermTypedNode> function_call initializer initializer_list condition conditionopt

%type <interm.intermNode> translation_unit function_definition
%type <interm.intermNode> statement simple_statement
%type <interm.intermAggregate>  statement_list switch_statement_list compound_statement
%type <interm.intermNode> declaration_statement selection_statement expression_statement
%type <interm.intermNode> switch_statement case_label
%type <interm.intermNode> declaration external_declaration
%type <interm.intermNode> for_init_statement compound_statement_no_new_scope
%type <interm.nodePair> selection_rest_statement for_rest_statement
%type <interm.intermNode> iteration_statement jump_statement statement_no_new_scope
%type <interm> single_declaration init_declarator_list

%type <interm> parameter_declaration parameter_declarator parameter_type_specifier

%type <interm> array_specifier
%type <interm.type> precise_qualifier invariant_qualifier interpolation_qualifier storage_qualifier precision_qualifier
%type <interm.type> layout_qualifier layout_qualifier_id_list layout_qualifier_id

%type <interm.type> type_qualifier fully_specified_type type_specifier
%type <interm.type> single_type_qualifier
%type <interm.type> type_specifier_nonarray
%type <interm.type> struct_specifier
%type <interm.typeLine> struct_declarator
%type <interm.typeList> struct_declarator_list struct_declaration struct_declaration_list type_name_list
%type <interm> block_structure
%type <interm.function> function_header function_declarator
%type <interm.function> function_header_with_parameters
%type <interm> function_call_header_with_parameters function_call_header_no_parameters function_call_generic function_prototype
%type <interm> function_call_or_method function_identifier function_call_header

%start translation_unit
%%

variable_identifier
    : IDENTIFIER {
        $$ = parseContext.handleVariable($1.line, $1.symbol, $1.string);
    }
    ;

primary_expression
    : variable_identifier {
        $$ = $1;
    }
    | INTCONSTANT {
        constUnion *unionArray = new constUnion[1];
        unionArray->setIConst($1.i);
        $$ = parseContext.intermediate.addConstantUnion(unionArray, TType(EbtInt, EvqConst), $1.line);
    }
    | UINTCONSTANT {        
        parseContext.fullIntegerCheck($1.line, "unsigned literal");
        constUnion *unionArray = new constUnion[1];
        unionArray->setUConst($1.u);
        $$ = parseContext.intermediate.addConstantUnion(unionArray, TType(EbtUint, EvqConst), $1.line);
    }
    | FLOATCONSTANT {
        constUnion *unionArray = new constUnion[1];
        unionArray->setDConst($1.d);
        $$ = parseContext.intermediate.addConstantUnion(unionArray, TType(EbtFloat, EvqConst), $1.line);
    }
    | DOUBLECONSTANT {
        parseContext.doubleCheck($1.line, "double literal");
        constUnion *unionArray = new constUnion[1];
        unionArray->setDConst($1.d);
        $$ = parseContext.intermediate.addConstantUnion(unionArray, TType(EbtDouble, EvqConst), $1.line);
    }
    | BOOLCONSTANT {
        constUnion *unionArray = new constUnion[1];
        unionArray->setBConst($1.b);
        $$ = parseContext.intermediate.addConstantUnion(unionArray, TType(EbtBool, EvqConst), $1.line);
    }
    | LEFT_PAREN expression RIGHT_PAREN {
        $$ = $2;
    }
    ;

postfix_expression
    : primary_expression {
        $$ = $1;
    }
    | postfix_expression LEFT_BRACKET integer_expression RIGHT_BRACKET {
        parseContext.variableCheck($1);
        if (!$1->isArray() && !$1->isMatrix() && !$1->isVector()) {
            if ($1->getAsSymbolNode())
                parseContext.error($2.line, " left of '[' is not of type array, matrix, or vector ", $1->getAsSymbolNode()->getSymbol().c_str(), "");
            else
                parseContext.error($2.line, " left of '[' is not of type array, matrix, or vector ", "expression", "");
        }
        if ($1->getType().getQualifier().storage == EvqConst && $3->getQualifier().storage == EvqConst) {
            if ($1->isArray()) { // constant folding for arrays
                $$ = parseContext.addConstArrayNode($3->getAsConstantUnion()->getUnionArrayPointer()->getIConst(), $1, $2.line);
            } else if ($1->isVector()) {  // constant folding for vectors
                TVectorFields fields;
                fields.num = 1;
                fields.offsets[0] = $3->getAsConstantUnion()->getUnionArrayPointer()->getIConst(); // need to do it this way because v.xy sends fields integer array
                $$ = parseContext.addConstVectorNode(fields, $1, $2.line);
            } else if ($1->isMatrix()) { // constant folding for matrices
                $$ = parseContext.addConstMatrixNode($3->getAsConstantUnion()->getUnionArrayPointer()->getIConst(), $1, $2.line);
            }
        } else {
            if ($3->getQualifier().storage == EvqConst) {
                int index = $3->getAsConstantUnion()->getUnionArrayPointer()->getIConst();
                if (! $1->isArray() && ($1->isVector() && $1->getType().getVectorSize() <= index ||
                                        $1->isMatrix() && $1->getType().getMatrixCols() <= index))
                    parseContext.error($2.line, "", "[", "index out of range '%d'", $3->getAsConstantUnion()->getUnionArrayPointer()->getIConst());
                else {
                    if ($1->isArray()) {
                        if ($1->getType().getArraySize() == 0) {
                            if ($1->getType().getMaxArraySize() <= $3->getAsConstantUnion()->getUnionArrayPointer()->getIConst())
                                parseContext.arraySetMaxSize($1->getAsSymbolNode(), $1->getTypePointer(), $3->getAsConstantUnion()->getUnionArrayPointer()->getIConst(), true, $2.line);
                            else
                                parseContext.arraySetMaxSize($1->getAsSymbolNode(), $1->getTypePointer(), 0, false, $2.line);
                        } else if ( $3->getAsConstantUnion()->getUnionArrayPointer()->getIConst() >= $1->getType().getArraySize() ||
                                    $3->getAsConstantUnion()->getUnionArrayPointer()->getIConst() < 0)
                            parseContext.error($2.line, "", "[", "array index out of range '%d'", $3->getAsConstantUnion()->getUnionArrayPointer()->getIConst());
                    }
                    $$ = parseContext.intermediate.addIndex(EOpIndexDirect, $1, $3, $2.line);
                }
            } else {
                if ($1->isArray() && $1->getType().getArraySize() == 0)
                    parseContext.error($2.line, "", "[", "array must be redeclared with a size before being indexed with a variable");
                if ($1->getBasicType() == EbtBlock)
                    parseContext.requireProfile($1->getLine(), static_cast<EProfileMask>(~EEsProfileMask), "variable indexing block array");

                $$ = parseContext.intermediate.addIndex(EOpIndexIndirect, $1, $3, $2.line);
            }
        }

        if ($$ == 0) {
            constUnion *unionArray = new constUnion[1];
            unionArray->setDConst(0.0);
            $$ = parseContext.intermediate.addConstantUnion(unionArray, TType(EbtFloat, EvqConst), $2.line);
        } else {
            TType newType($1->getType());
            newType.dereference();
            $$->setType(newType);
            // TODO: testing: write a set of dereference tests
        }
    }
    | function_call {
        $$ = $1;
    }
    | postfix_expression DOT FIELD_SELECTION {
        parseContext.variableCheck($1);
        if ($1->isArray()) {
            //
            // It can only be a method (e.g., length), which can't be resolved until
            // we later see the function calling syntax.  Save away the name for now.
            //

            // TODO: semantics: if next token is not "(", then this is an error

            if (*$3.string == "length") {
                parseContext.profileRequires($3.line, ENoProfile, 120, "GL_3DL_array_objects", ".length");
                $$ = parseContext.intermediate.addMethod($1, TType(EbtInt), $3.string, $2.line);
            } else {
                parseContext.error($3.line, "only the length method is supported for array", $3.string->c_str(), "");
                $$ = $1;
            }
        } else if ($1->isVector()) {
            TVectorFields fields;
            if (! parseContext.parseVectorFields(*$3.string, $1->getVectorSize(), fields, $3.line)) {
                fields.num = 1;
                fields.offsets[0] = 0;
            }

            if ($1->getType().getQualifier().storage == EvqConst) { // constant folding for vector fields
                $$ = parseContext.addConstVectorNode(fields, $1, $3.line);
                if ($$ == 0)
                    $$ = $1;
                else
                    $$->setType(TType($1->getBasicType(), EvqConst, (int) (*$3.string).size()));
            } else {
                if (fields.num == 1) {
                    constUnion *unionArray = new constUnion[1];
                    unionArray->setIConst(fields.offsets[0]);
                    TIntermTyped* index = parseContext.intermediate.addConstantUnion(unionArray, TType(EbtInt, EvqConst), $3.line);
                    $$ = parseContext.intermediate.addIndex(EOpIndexDirect, $1, index, $2.line);
                    $$->setType(TType($1->getBasicType(), EvqTemporary, $1->getType().getQualifier().precision));
                } else {
                    TString vectorString = *$3.string;
                    TIntermTyped* index = parseContext.intermediate.addSwizzle(fields, $3.line);
                    $$ = parseContext.intermediate.addIndex(EOpVectorSwizzle, $1, index, $2.line);
                    $$->setType(TType($1->getBasicType(), EvqTemporary, $1->getType().getQualifier().precision, (int) vectorString.size()));
                }
            }
        } else if ($1->isMatrix())
            parseContext.error($2.line, "field selection not allowed on matrix", ".", "");
        else if ($1->getBasicType() == EbtStruct || $1->getBasicType() == EbtBlock) {
            bool fieldFound = false;
            TTypeList* fields = $1->getType().getStruct();
            if (fields == 0) {
                parseContext.error($2.line, "structure has no fields", "Internal Error", "");
                $$ = $1;
            } else {
                unsigned int i;
                for (i = 0; i < fields->size(); ++i) {
                    if ((*fields)[i].type->getFieldName() == *$3.string) {
                        fieldFound = true;
                        break;
                    }
                }
                if (fieldFound) {
                    if ($1->getType().getQualifier().storage == EvqConst) {
                        $$ = parseContext.addConstStruct(*$3.string, $1, $2.line);
                        if ($$ == 0)
                            $$ = $1;
                        else {
                            $$->setType(*(*fields)[i].type);
                            // change the qualifier of the return type, not of the structure field
                            // as the structure definition is shared between various structures.
                            $$->getTypePointer()->getQualifier().storage = EvqConst;
                        }
                    } else {
                        constUnion *unionArray = new constUnion[1];
                        unionArray->setIConst(i);
                        TIntermTyped* index = parseContext.intermediate.addConstantUnion(unionArray, TType(EbtInt, EvqConst), $3.line);
                        $$ = parseContext.intermediate.addIndex(EOpIndexDirectStruct, $1, index, $2.line);
                        $$->setType(*(*fields)[i].type);
                    }
                } else {
                    parseContext.error($2.line, " no such field in structure", $3.string->c_str(), "");
                    $$ = $1;
                }
            }
        } else {
            parseContext.error($2.line, " dot operator requires structure, array, vector, or matrix on left hand side", $3.string->c_str(), "");
            $$ = $1;
        }
        // don't delete $3.string, it's from the pool
    }
    | postfix_expression INC_OP {
        parseContext.variableCheck($1);
        parseContext.lValueErrorCheck($2.line, "++", $1);
        $$ = parseContext.intermediate.addUnaryMath(EOpPostIncrement, $1, $2.line);
        if ($$ == 0) {
            parseContext.unaryOpError($2.line, "++", $1->getCompleteString());
            $$ = $1;
        }
    }
    | postfix_expression DEC_OP {
        parseContext.variableCheck($1);
        parseContext.lValueErrorCheck($2.line, "--", $1);
        $$ = parseContext.intermediate.addUnaryMath(EOpPostDecrement, $1, $2.line);
        if ($$ == 0) {
            parseContext.unaryOpError($2.line, "--", $1->getCompleteString());
            $$ = $1;
        }
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
        TFunction* fnCall = $1.function;
        TOperator op = fnCall->getBuiltInOp();
        if (op == EOpArrayLength) {
            // TODO: semantics: check for no arguments to .length()
            int length;
            if ($1.intermNode->getAsTyped() == 0 || ! $1.intermNode->getAsTyped()->getType().isArray() || $1.intermNode->getAsTyped()->getType().getArraySize() == 0) {
                parseContext.error($1.line, "", fnCall->getName().c_str(), "array must be declared with a size before using this method");
                length = 1;
            } else
                length = $1.intermNode->getAsTyped()->getType().getArraySize();

            constUnion *unionArray = new constUnion[1];
            unionArray->setIConst(length);
            $$ = parseContext.intermediate.addConstantUnion(unionArray, TType(EbtInt, EvqConst), $1.line);
        } else if (op != EOpNull) {
            //
            // Then this should be a constructor.
            // Don't go through the symbol table for constructors.
            // Their parameters will be verified algorithmically.
            //
            TType type(EbtVoid);  // use this to get the type back
            if (parseContext.constructorError($1.line, $1.intermNode, *fnCall, op, type)) {
                $$ = 0;
            } else {
                //
                // It's a constructor, of type 'type'.
                //
                $$ = parseContext.addConstructor($1.intermNode, type, op, fnCall, $1.line);
                if ($$ == 0)
                    parseContext.error($1.line, "cannot construct with these arguments", type.getCompleteString().c_str(), "");
            }

            if ($$ == 0)
                $$ = parseContext.intermediate.setAggregateOperator(0, op, type, $1.line);
        } else {
            //
            // Not a constructor.  Find it in the symbol table.
            //
            const TFunction* fnCandidate;
            bool builtIn;
            fnCandidate = parseContext.findFunction($1.line, fnCall, &builtIn);
            if (fnCandidate) {
                //
                // A declared function.  But, it might still map to a built-in
                // operation.
                //
                op = fnCandidate->getBuiltInOp();
                if (builtIn && op != EOpNull) {
                    // A function call mapped to a built-in operation.
                    $$ = parseContext.intermediate.addBuiltInFunctionCall(op, fnCandidate->getParamCount() == 1, $1.intermNode, fnCandidate->getReturnType());
                    if ($$ == 0)  {
                        parseContext.error($1.intermNode->getLine(), " wrong operand type", "Internal Error",
                            "built in unary operator function.  Type: %s",
                            static_cast<TIntermTyped*>($1.intermNode)->getCompleteString().c_str());
                        YYERROR;
                    }
                } else {
                    // This is a real function call
                    $$ = parseContext.intermediate.setAggregateOperator($1.intermAggregate, EOpFunctionCall, fnCandidate->getReturnType(), $1.line);

                    // this is how we know whether the given function is a builtIn function or a user defined function
                    // if builtIn == false, it's a userDefined -> could be an overloaded builtIn function also
                    // if builtIn == true, it's definitely a builtIn function with EOpNull
                    if (!builtIn)
                        $$->getAsAggregate()->setUserDefined();
                    $$->getAsAggregate()->setName(fnCandidate->getMangledName());

                    TStorageQualifier qual;
                    TQualifierList& qualifierList = $$->getAsAggregate()->getQualifierList();
                    for (int i = 0; i < fnCandidate->getParamCount(); ++i) {
                        qual = (*fnCandidate)[i].type->getQualifier().storage;
                        if (qual == EvqOut || qual == EvqInOut) {
                            if (parseContext.lValueErrorCheck($$->getLine(), "assign", $$->getAsAggregate()->getSequence()[i]->getAsTyped()))
                                parseContext.error($1.intermNode->getLine(), "Constant value cannot be passed for 'out' or 'inout' parameters.", "Error", "");
                        }
                        qualifierList.push_back(qual);
                    }

                    // built-in texturing functions get their return value precision from the precision of the sampler
                    if (builtIn && fnCandidate->getReturnType().getQualifier().precision == EpqNone &&
                        fnCandidate->getParamCount() > 0 && (*fnCandidate)[0].type->getBasicType() == EbtSampler)
                        $$->getQualifier().precision = $$->getAsAggregate()->getSequence()[0]->getAsTyped()->getQualifier().precision;
                }
            } else {
                // error message was put out by PaFindFunction()
                // Put on a dummy node for error recovery
                constUnion *unionArray = new constUnion[1];
                unionArray->setDConst(0.0);
                $$ = parseContext.intermediate.addConstantUnion(unionArray, TType(EbtFloat, EvqConst), $1.line);
            }
        }
        delete fnCall;
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
        $$.line = $2.line;
    }
    | function_call_header_no_parameters RIGHT_PAREN {
        $$ = $1;
        $$.line = $2.line;
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
        TParameter param = { 0, new TType($2->getType()) };
        $1.function->addParameter(param);
        $$.function = $1.function;
        $$.intermNode = $2;
    }
    | function_call_header_with_parameters COMMA assignment_expression {
        TParameter param = { 0, new TType($3->getType()) };
        $1.function->addParameter(param);
        $$.function = $1.function;
        $$.intermNode = parseContext.intermediate.growAggregate($1.intermNode, $3, $2.line);
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
        //
        // Constructor
        //
        $$.function = 0;
        $$.intermNode = 0;

        if ($1.arraySizes) {
            parseContext.profileRequires($1.line, ENoProfile, 120, "GL_3DL_array_objects", "arrayed constructor");
            parseContext.profileRequires($1.line, EEsProfile, 300, "GL_3DL_array_objects", "arrayed constructor");
        }

        $1.qualifier.precision = EpqNone;
        if ($1.userDef) {
            TString tempString = "";
            TType type($1);
            TFunction *function = new TFunction(&tempString, type, EOpConstructStruct);
            $$.function = function;
        } else {
            TOperator op = EOpNull;
            switch ($1.basicType) {
            case EbtFloat:
                if ($1.matrixCols) {
                    switch ($1.matrixCols) {
                    case 2:
                        switch ($1.matrixRows) {
                        case 2: op = EOpConstructMat2x2; break;
                        case 3: op = EOpConstructMat2x3; break;
                        case 4: op = EOpConstructMat2x4; break;
                        default: break; // some compilers want this
                        }
                        break;
                    case 3:
                        switch ($1.matrixRows) {
                        case 2: op = EOpConstructMat3x2; break;
                        case 3: op = EOpConstructMat3x3; break;
                        case 4: op = EOpConstructMat3x4; break;
                        default: break; // some compilers want this
                        }
                        break;
                    case 4:
                        switch ($1.matrixRows) {
                        case 2: op = EOpConstructMat4x2; break;
                        case 3: op = EOpConstructMat4x3; break;
                        case 4: op = EOpConstructMat4x4; break;
                        default: break; // some compilers want this
                        }
                        break;
                    default: break; // some compilers want this
                    }
                } else {
                    switch($1.vectorSize) {
                    case 1: op = EOpConstructFloat; break;
                    case 2: op = EOpConstructVec2;  break;
                    case 3: op = EOpConstructVec3;  break;
                    case 4: op = EOpConstructVec4;  break;
                    default: break; // some compilers want this
                    }
                }
                break;
            case EbtDouble:
                if ($1.matrixCols) {
                    switch ($1.matrixCols) {
                    case 2:
                        switch ($1.matrixRows) {
                        case 2: op = EOpConstructDMat2x2; break;
                        case 3: op = EOpConstructDMat2x3; break;
                        case 4: op = EOpConstructDMat2x4; break;
                        default: break; // some compilers want this
                        }
                        break;
                    case 3:
                        switch ($1.matrixRows) {
                        case 2: op = EOpConstructDMat3x2; break;
                        case 3: op = EOpConstructDMat3x3; break;
                        case 4: op = EOpConstructDMat3x4; break;
                        default: break; // some compilers want this
                        }
                        break;
                    case 4:
                        switch ($1.matrixRows) {
                        case 2: op = EOpConstructDMat4x2; break;
                        case 3: op = EOpConstructDMat4x3; break;
                        case 4: op = EOpConstructDMat4x4; break;
                        default: break; // some compilers want this
                        }
                        break;
                    }
                } else {
                    switch($1.vectorSize) {
                    case 1: op = EOpConstructDouble; break;
                    case 2: op = EOpConstructDVec2;  break;
                    case 3: op = EOpConstructDVec3;  break;
                    case 4: op = EOpConstructDVec4;  break;
                    default: break; // some compilers want this
                    }
                }
                break;
            case EbtInt:
                switch($1.vectorSize) {
                case 1: op = EOpConstructInt;   break;
                case 2: op = EOpConstructIVec2; break;
                case 3: op = EOpConstructIVec3; break;
                case 4: op = EOpConstructIVec4; break;
                default: break; // some compilers want this
                }
                break;
            case EbtUint:
                switch($1.vectorSize) {
                case 1: op = EOpConstructUint;  break;
                case 2: op = EOpConstructUVec2; break;
                case 3: op = EOpConstructUVec3; break;
                case 4: op = EOpConstructUVec4; break;
                default: break; // some compilers want this
                }
                break;
            case EbtBool:
                switch($1.vectorSize) {
                case 1:  op = EOpConstructBool;  break;
                case 2:  op = EOpConstructBVec2; break;
                case 3:  op = EOpConstructBVec3; break;
                case 4:  op = EOpConstructBVec4; break;
                default: break; // some compilers want this
                }
                break;
            default: break; // some compilers want this
            }
            if (op == EOpNull) {
                parseContext.error($1.line, "cannot construct this type", TType::getBasicString($1.basicType), "");
                $1.basicType = EbtFloat;
                op = EOpConstructFloat;
            }
            TString tempString = "";
            TType type($1);
            TFunction *function = new TFunction(&tempString, type, op);
            $$.function = function;
        }
    }
    | postfix_expression {
        //
        // Should be a method or subroutine call, but we don't have arguments yet.
        //
        $$.function = 0;
        $$.intermNode = 0;

        TIntermMethod* method = $1->getAsMethodNode();
        if (method) {
            if (method->getObject()->isArray()) {
                $$.function = new TFunction(&method->getMethodName(), TType(EbtInt), EOpArrayLength);
                $$.intermNode = method->getObject();
            } else
                parseContext.error(method->getLine(), "only arrays have methods", "", "");
        } else {
            TIntermSymbol* symbol = $1->getAsSymbolNode();
            if (symbol) {
                parseContext.reservedErrorCheck(symbol->getLine(), symbol->getSymbol());
                TFunction *function = new TFunction(&symbol->getSymbol(), TType(EbtVoid));
                $$.function = function;
            } else
                parseContext.error($1->getLine(), "function call, method or subroutine call expected", "", "");
        }

        if ($$.function == 0) {
            // error recover
            TString empty("");
            $$.function = new TFunction(&empty, TType(EbtVoid), EOpNull);
        }
    }
    ;

unary_expression
    : postfix_expression {
        parseContext.variableCheck($1);
        $$ = $1;
    }
    | INC_OP unary_expression {
        parseContext.lValueErrorCheck($1.line, "++", $2);
        $$ = parseContext.intermediate.addUnaryMath(EOpPreIncrement, $2, $1.line);
        if ($$ == 0) {
            parseContext.unaryOpError($1.line, "++", $2->getCompleteString());
            $$ = $2;
        }
    }
    | DEC_OP unary_expression {
        parseContext.lValueErrorCheck($1.line, "--", $2);
        $$ = parseContext.intermediate.addUnaryMath(EOpPreDecrement, $2, $1.line);
        if ($$ == 0) {
            parseContext.unaryOpError($1.line, "--", $2->getCompleteString());
            $$ = $2;
        }
    }
    | unary_operator unary_expression {
        if ($1.op != EOpNull) {
            $$ = parseContext.intermediate.addUnaryMath($1.op, $2, $1.line);
            if ($$ == 0) {
                char errorOp[2] = {0, 0};
                switch($1.op) {
                case EOpNegative:   errorOp[0] = '-'; break;
                case EOpLogicalNot: errorOp[0] = '!'; break;
                case EOpBitwiseNot: errorOp[0] = '~'; break;
                default: break; // some compilers want this
                }
                parseContext.unaryOpError($1.line, errorOp, $2->getCompleteString());
                $$ = $2;
            }
        } else
            $$ = $2;
    }
    ;
// Grammar Note:  No traditional style type casts.

unary_operator
    : PLUS  { $$.line = $1.line; $$.op = EOpNull; }
    | DASH  { $$.line = $1.line; $$.op = EOpNegative; }
    | BANG  { $$.line = $1.line; $$.op = EOpLogicalNot; }
    | TILDE { $$.line = $1.line; $$.op = EOpBitwiseNot; }
    ;
// Grammar Note:  No '*' or '&' unary ops.  Pointers are not supported.

multiplicative_expression
    : unary_expression { $$ = $1; }
    | multiplicative_expression STAR unary_expression {
        $$ = parseContext.intermediate.addBinaryMath(EOpMul, $1, $3, $2.line);
        if ($$ == 0) {
            parseContext.binaryOpError($2.line, "*", $1->getCompleteString(), $3->getCompleteString());
            $$ = $1;
        }
    }
    | multiplicative_expression SLASH unary_expression {
        $$ = parseContext.intermediate.addBinaryMath(EOpDiv, $1, $3, $2.line);
        if ($$ == 0) {
            parseContext.binaryOpError($2.line, "/", $1->getCompleteString(), $3->getCompleteString());
            $$ = $1;
        }
    }
    | multiplicative_expression PERCENT unary_expression {
        $$ = parseContext.intermediate.addBinaryMath(EOpMod, $1, $3, $2.line);
        if ($$ == 0) {
            parseContext.binaryOpError($2.line, "%", $1->getCompleteString(), $3->getCompleteString());
            $$ = $1;
        }
    }
    ;

additive_expression
    : multiplicative_expression { $$ = $1; }
    | additive_expression PLUS multiplicative_expression {
        $$ = parseContext.intermediate.addBinaryMath(EOpAdd, $1, $3, $2.line);
        if ($$ == 0) {
            parseContext.binaryOpError($2.line, "+", $1->getCompleteString(), $3->getCompleteString());
            $$ = $1;
        }
    }
    | additive_expression DASH multiplicative_expression {
        $$ = parseContext.intermediate.addBinaryMath(EOpSub, $1, $3, $2.line);
        if ($$ == 0) {
            parseContext.binaryOpError($2.line, "-", $1->getCompleteString(), $3->getCompleteString());
            $$ = $1;
        }
    }
    ;

shift_expression
    : additive_expression { $$ = $1; }
    | shift_expression LEFT_OP additive_expression {
        parseContext.fullIntegerCheck($2.line, "bit shift left");
        $$ = parseContext.intermediate.addBinaryMath(EOpLeftShift, $1, $3, $2.line);
        if ($$ == 0) {
            parseContext.binaryOpError($2.line, "<<", $1->getCompleteString(), $3->getCompleteString());
            $$ = $1;
        }
    }
    | shift_expression RIGHT_OP additive_expression {
        parseContext.fullIntegerCheck($2.line, "bit shift right");
        $$ = parseContext.intermediate.addBinaryMath(EOpRightShift, $1, $3, $2.line);
        if ($$ == 0) {
            parseContext.binaryOpError($2.line, ">>", $1->getCompleteString(), $3->getCompleteString());
            $$ = $1;
        }
    }
    ;

relational_expression
    : shift_expression { $$ = $1; }
    | relational_expression LEFT_ANGLE shift_expression {
        $$ = parseContext.intermediate.addBinaryMath(EOpLessThan, $1, $3, $2.line);
        if ($$ == 0) {
            parseContext.binaryOpError($2.line, "<", $1->getCompleteString(), $3->getCompleteString());
            constUnion *unionArray = new constUnion[1];
            unionArray->setBConst(false);
            $$ = parseContext.intermediate.addConstantUnion(unionArray, TType(EbtBool, EvqConst), $2.line);
        }
    }
    | relational_expression RIGHT_ANGLE shift_expression  {
        $$ = parseContext.intermediate.addBinaryMath(EOpGreaterThan, $1, $3, $2.line);
        if ($$ == 0) {
            parseContext.binaryOpError($2.line, ">", $1->getCompleteString(), $3->getCompleteString());
            constUnion *unionArray = new constUnion[1];
            unionArray->setBConst(false);
            $$ = parseContext.intermediate.addConstantUnion(unionArray, TType(EbtBool, EvqConst), $2.line);
        }
    }
    | relational_expression LE_OP shift_expression  {
        $$ = parseContext.intermediate.addBinaryMath(EOpLessThanEqual, $1, $3, $2.line);
        if ($$ == 0) {
            parseContext.binaryOpError($2.line, "<=", $1->getCompleteString(), $3->getCompleteString());
            constUnion *unionArray = new constUnion[1];
            unionArray->setBConst(false);
            $$ = parseContext.intermediate.addConstantUnion(unionArray, TType(EbtBool, EvqConst), $2.line);
        }
    }
    | relational_expression GE_OP shift_expression  {
        $$ = parseContext.intermediate.addBinaryMath(EOpGreaterThanEqual, $1, $3, $2.line);
        if ($$ == 0) {
            parseContext.binaryOpError($2.line, ">=", $1->getCompleteString(), $3->getCompleteString());
            constUnion *unionArray = new constUnion[1];
            unionArray->setBConst(false);
            $$ = parseContext.intermediate.addConstantUnion(unionArray, TType(EbtBool, EvqConst), $2.line);
        }
    }
    ;

equality_expression
    : relational_expression { $$ = $1; }
    | equality_expression EQ_OP relational_expression  {
        $$ = parseContext.intermediate.addBinaryMath(EOpEqual, $1, $3, $2.line);
        if ($$ == 0) {
            parseContext.binaryOpError($2.line, "==", $1->getCompleteString(), $3->getCompleteString());
            constUnion *unionArray = new constUnion[1];
            unionArray->setBConst(false);
            $$ = parseContext.intermediate.addConstantUnion(unionArray, TType(EbtBool, EvqConst), $2.line);
        } else if (($1->isArray() || $3->isArray()))
            parseContext.profileRequires($2.line, ENoProfile, 120, "GL_3DL_array_objects", "==");
    }
    | equality_expression NE_OP relational_expression {
        $$ = parseContext.intermediate.addBinaryMath(EOpNotEqual, $1, $3, $2.line);
        if ($$ == 0) {
            parseContext.binaryOpError($2.line, "!=", $1->getCompleteString(), $3->getCompleteString());
            constUnion *unionArray = new constUnion[1];
            unionArray->setBConst(false);
            $$ = parseContext.intermediate.addConstantUnion(unionArray, TType(EbtBool, EvqConst), $2.line);
        } else if (($1->isArray() || $3->isArray()))
            parseContext.profileRequires($2.line, ENoProfile, 120, "GL_3DL_array_objects", "!=");
    }
    ;

and_expression
    : equality_expression { $$ = $1; }
    | and_expression AMPERSAND equality_expression {
        parseContext.fullIntegerCheck($2.line, "bitwise and");
        $$ = parseContext.intermediate.addBinaryMath(EOpAnd, $1, $3, $2.line);
        if ($$ == 0) {
            parseContext.binaryOpError($2.line, "&", $1->getCompleteString(), $3->getCompleteString());
            $$ = $1;
        }
    }
    ;

exclusive_or_expression
    : and_expression { $$ = $1; }
    | exclusive_or_expression CARET and_expression {
        parseContext.fullIntegerCheck($2.line, "bitwise exclusive or");
        $$ = parseContext.intermediate.addBinaryMath(EOpExclusiveOr, $1, $3, $2.line);
        if ($$ == 0) {
            parseContext.binaryOpError($2.line, "^", $1->getCompleteString(), $3->getCompleteString());
            $$ = $1;
        }
    }
    ;

inclusive_or_expression
    : exclusive_or_expression { $$ = $1; }
    | inclusive_or_expression VERTICAL_BAR exclusive_or_expression {
        parseContext.fullIntegerCheck($2.line, "bitwise inclusive or");
        $$ = parseContext.intermediate.addBinaryMath(EOpInclusiveOr, $1, $3, $2.line);
        if ($$ == 0) {
            parseContext.binaryOpError($2.line, "|", $1->getCompleteString(), $3->getCompleteString());
            $$ = $1;
        }
    }
    ;

logical_and_expression
    : inclusive_or_expression { $$ = $1; }
    | logical_and_expression AND_OP inclusive_or_expression {
        $$ = parseContext.intermediate.addBinaryMath(EOpLogicalAnd, $1, $3, $2.line);
        if ($$ == 0) {
            parseContext.binaryOpError($2.line, "&&", $1->getCompleteString(), $3->getCompleteString());
            constUnion *unionArray = new constUnion[1];
            unionArray->setBConst(false);
            $$ = parseContext.intermediate.addConstantUnion(unionArray, TType(EbtBool, EvqConst), $2.line);
        }
    }
    ;

logical_xor_expression
    : logical_and_expression { $$ = $1; }
    | logical_xor_expression XOR_OP logical_and_expression  {
        $$ = parseContext.intermediate.addBinaryMath(EOpLogicalXor, $1, $3, $2.line);
        if ($$ == 0) {
            parseContext.binaryOpError($2.line, "^^", $1->getCompleteString(), $3->getCompleteString());
            constUnion *unionArray = new constUnion[1];
            unionArray->setBConst(false);
            $$ = parseContext.intermediate.addConstantUnion(unionArray, TType(EbtBool, EvqConst), $2.line);
        }
    }
    ;

logical_or_expression
    : logical_xor_expression { $$ = $1; }
    | logical_or_expression OR_OP logical_xor_expression  {
        $$ = parseContext.intermediate.addBinaryMath(EOpLogicalOr, $1, $3, $2.line);
        if ($$ == 0) {
            parseContext.binaryOpError($2.line, "||", $1->getCompleteString(), $3->getCompleteString());
            constUnion *unionArray = new constUnion[1];
            unionArray->setBConst(false);
            $$ = parseContext.intermediate.addConstantUnion(unionArray, TType(EbtBool, EvqConst), $2.line);
        }
    }
    ;

conditional_expression
    : logical_or_expression { $$ = $1; }
    | logical_or_expression QUESTION expression COLON assignment_expression {
        parseContext.boolCheck($2.line, $1);

        $$ = parseContext.intermediate.addSelection($1, $3, $5, $2.line);
        if ($$ == 0) {
            parseContext.binaryOpError($2.line, ":", $3->getCompleteString(), $5->getCompleteString());
            $$ = $5;
        }
    }
    ;

assignment_expression
    : conditional_expression { $$ = $1; }
    | unary_expression assignment_operator assignment_expression {
        parseContext.lValueErrorCheck($2.line, "assign", $1);
        $$ = parseContext.intermediate.addAssign($2.op, $1, $3, $2.line);
        if ($$ == 0) {
            parseContext.assignError($2.line, "assign", $1->getCompleteString(), $3->getCompleteString());
            $$ = $1;
        } else if (($1->isArray() || $3->isArray()))
            parseContext.profileRequires($2.line, ENoProfile, 120, "GL_3DL_array_objects", "=");
    }
    ;

assignment_operator
    : EQUAL        { $$.line = $1.line; $$.op = EOpAssign; }
    | MUL_ASSIGN   { $$.line = $1.line; $$.op = EOpMulAssign; }
    | DIV_ASSIGN   { $$.line = $1.line; $$.op = EOpDivAssign; }
    | MOD_ASSIGN   { $$.line = $1.line; $$.op = EOpModAssign; }
    | ADD_ASSIGN   { $$.line = $1.line; $$.op = EOpAddAssign; }
    | SUB_ASSIGN   { $$.line = $1.line; $$.op = EOpSubAssign; }
    | LEFT_ASSIGN  {
        parseContext.fullIntegerCheck($1.line, "bit-shift left assign");
        $$.line = $1.line; $$.op = EOpLeftShiftAssign;
    }
    | RIGHT_ASSIGN {
        parseContext.fullIntegerCheck($1.line, "bit-shift right assign");
        $$.line = $1.line; $$.op = EOpRightShiftAssign;
    }
    | AND_ASSIGN   {
        parseContext.fullIntegerCheck($1.line, "bitwise-and assign");
        $$.line = $1.line; $$.op = EOpAndAssign;
    }
    | XOR_ASSIGN   {
        parseContext.fullIntegerCheck($1.line, "bitwise-xor assign");
        $$.line = $1.line; $$.op = EOpExclusiveOrAssign;
    }
    | OR_ASSIGN    {
        parseContext.fullIntegerCheck($1.line, "bitwise-or assign");
        $$.line = $1.line; $$.op = EOpInclusiveOrAssign;
    }
    ;

expression
    : assignment_expression {
        $$ = $1;
    }
    | expression COMMA assignment_expression {
        $$ = parseContext.intermediate.addComma($1, $3, $2.line);
        if ($$ == 0) {
            parseContext.binaryOpError($2.line, ",", $1->getCompleteString(), $3->getCompleteString());
            $$ = $3;
        }
    }
    ;

constant_expression
    : conditional_expression {
        parseContext.constCheck($1);
        $$ = $1;
    }
    ;

declaration
    : function_prototype SEMICOLON {
        $$ = 0;
        // TODO: 4.0 functionality: subroutines: make the identifier a user type for this signature
    }
    | init_declarator_list SEMICOLON {
        if ($1.intermAggregate)
            $1.intermAggregate->setOperator(EOpSequence);
        $$ = $1.intermAggregate;
    }
    | PRECISION precision_qualifier type_specifier SEMICOLON {
        parseContext.profileRequires($1.line, ENoProfile, 130, 0, "precision statement");

        // lazy setting of the previous scope's defaults, only takes on first one in a particular scope
        parseContext.symbolTable.setPreviousDefaultPrecisions(&parseContext.defaultPrecision[0]);

		parseContext.setDefaultPrecision($1.line, $3, $2.qualifier.precision);
        $$ = 0;
    }
    | block_structure SEMICOLON {
        parseContext.addBlock($1.line, *$1.typeList);
        $$ = 0;
    }
    | block_structure IDENTIFIER SEMICOLON {
        parseContext.addBlock($1.line, *$1.typeList, $2.string);
        $$ = 0;
    }
    | block_structure IDENTIFIER array_specifier SEMICOLON {
        parseContext.addBlock($1.line, *$1.typeList, $2.string, $3.arraySizes);
        $$ = 0;
    }
    | type_qualifier SEMICOLON {
        // setting defaults
        $$ = 0;
    }
    | type_qualifier IDENTIFIER SEMICOLON {
        // TODO: functionality: track what variables are declared with INVARIANT
        // precise foo;
        // invariant foo;
        $$ = 0;
    }
    | type_qualifier IDENTIFIER identifier_list SEMICOLON {
        // TODO: functionality: track what variables are declared with INVARIANT
        // precise foo, bar;
        // invariant foo, bar;
        $$ = 0;
    }
    ;

block_structure
    : type_qualifier IDENTIFIER LEFT_BRACE { parseContext.nestedBlockCheck($1.line); } struct_declaration_list RIGHT_BRACE {
        --parseContext.structNestingLevel;
        parseContext.blockName = $2.string;
        parseContext.blockType = $1;
        $$.line = $1.line;
        $$.typeList = $5;
    }

identifier_list
    : COMMA IDENTIFIER {
    }
    | identifier_list COMMA IDENTIFIER {
    }
    ;

function_prototype
    : function_declarator RIGHT_PAREN  {
        // ES can't declare prototypes inside functions
        if (! parseContext.symbolTable.atGlobalLevel())
            parseContext.requireProfile($2.line, static_cast<EProfileMask>(~EEsProfileMask), "local function declaration");

        //
        // Multiple declarations of the same function are allowed.
        //
        // If this is a definition, the definition production code will check for redefinitions
        // (we don't know at this point if it's a definition or not).
        //
        // Redeclarations (full prototype match) are allowed.  But, return types and parameter qualifiers must match.
        //
        // ES does not allow redeclaring or hiding of built-in functions.
        //
        bool builtIn;
        TSymbol* symbol = parseContext.symbolTable.find($1->getMangledName(), &builtIn);
        if (symbol && symbol->getAsFunction() && builtIn)
            parseContext.requireProfile($2.line, static_cast<EProfileMask>(~EEsProfileMask), "redeclaration of built-in function");
        TFunction* prevDec = symbol ? symbol->getAsFunction() : 0;
        if (prevDec) {
            if (prevDec->getReturnType() != $1->getReturnType()) {
                parseContext.error($2.line, "overloaded functions must have the same return type", $1->getReturnType().getCompleteTypeString().c_str(), "");
            }
            for (int i = 0; i < prevDec->getParamCount(); ++i) {
                if ((*prevDec)[i].type->getQualifier().storage != (*$1)[i].type->getQualifier().storage)
                    parseContext.error($2.line, "overloaded functions must have the same parameter qualifiers", (*$1)[i].type->getStorageQualifierString(), "");
            }
        }

        //
        // If this is a redeclaration, it could also be a definition,
        // in which case, we want to use the variable names from this one, and not the one that's
        // being redeclared.  So, pass back up this declaration, not the one in the symbol table.
        //
        $$.function = $1;
        $$.line = $2.line;

        if (! parseContext.symbolTable.insert(*$$.function))
            parseContext.error($2.line, "illegal redeclaration", $$.function->getName().c_str(), "");
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
            parseContext.error($2.line, "cannot be an argument type except for '(void)'", "void", "");
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
            parseContext.error($2.line, "no qualifiers allowed for function return",
                               getStorageQualifierString($1.qualifier.storage), "");
        }

        // Add the function as a prototype after parsing it (we do not support recursion)
        TFunction *function;
        TType type($1);
        function = new TFunction($2.string, type);
        $$ = function;
    }
    ;

parameter_declarator
    // Type + name
    : type_specifier IDENTIFIER {
        if ($1.arraySizes) {
            parseContext.profileRequires($1.line, ENoProfile, 120, "GL_3DL_array_objects", "arrayed type");
            parseContext.profileRequires($1.line, EEsProfile, 300, 0, "arrayed type");
            parseContext.arraySizeRequiredCheck($1.line, $1.arraySizes->front());
        }
        if ($1.basicType == EbtVoid) {
            parseContext.error($2.line, "illegal use of type 'void'", $2.string->c_str(), "");
        }
        parseContext.reservedErrorCheck($2.line, *$2.string);

        TParameter param = {$2.string, new TType($1)};
        $$.line = $2.line;
        $$.param = param;
    }
    | type_specifier IDENTIFIER array_specifier {
        if ($1.arraySizes) {
            parseContext.profileRequires($1.line, ENoProfile, 120, "GL_3DL_array_objects", "arrayed type");
            parseContext.profileRequires($1.line, EEsProfile, 300, 0, "arrayed type");
            parseContext.arraySizeRequiredCheck($1.line, $1.arraySizes->front());
        }

        parseContext.arraySizeRequiredCheck($3.line, $3.arraySizes->front());
        parseContext.reservedErrorCheck($2.line, *$2.string);

        $1.arraySizes = $3.arraySizes;

        TParameter param = { $2.string, new TType($1)};
        $$.line = $2.line;
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

        parseContext.parameterSamplerCheck($2.line, $1.qualifier.storage, *$$.param.type);
        parseContext.paramCheck($1.line, $1.qualifier.storage, $$.param.type);
    }
    | parameter_declarator {
        $$ = $1;

        parseContext.parameterSamplerCheck($1.line, EvqIn, *$1.param.type);
        parseContext.paramCheck($1.line, EvqTemporary, $$.param.type);
    }
    //
    // Without name
    //
    | type_qualifier parameter_type_specifier {
        $$ = $2;
        if ($1.qualifier.precision != EpqNone)
            $$.param.type->getQualifier().precision = $1.qualifier.precision;

        parseContext.parameterSamplerCheck($2.line, $1.qualifier.storage, *$$.param.type);
        parseContext.paramCheck($1.line, $1.qualifier.storage, $$.param.type);
    }
    | parameter_type_specifier {
        $$ = $1;

        parseContext.parameterSamplerCheck($1.line, EvqIn, *$1.param.type);
        parseContext.paramCheck($1.line, EvqTemporary, $$.param.type);
    }
    ;

parameter_type_specifier
    : type_specifier {
        TParameter param = { 0, new TType($1) };
        $$.param = param;
    }
    ;

init_declarator_list
    : single_declaration {
        $$ = $1;
    }
    | init_declarator_list COMMA IDENTIFIER {
        $$ = $1;
        parseContext.nonInitConstCheck($3.line, *$3.string, $$.type);
        parseContext.nonInitCheck($3.line, *$3.string, $$.type);
    }
    | init_declarator_list COMMA IDENTIFIER array_specifier {
        parseContext.nonInitConstCheck($3.line, *$3.string, $1.type);
        if (parseContext.profile == EEsProfile)
            parseContext.arraySizeRequiredCheck($4.line, $4.arraySizes->front());
        
        $$ = $1;

        if (! parseContext.arrayQualifierError($4.line, $1.type)) {
            $1.type.arraySizes = $4.arraySizes;
            TVariable* variable;
            parseContext.arrayCheck($4.line, *$3.string, $1.type, variable);
        }
    }
    | init_declarator_list COMMA IDENTIFIER array_specifier EQUAL initializer {
        $$ = $1;

        TVariable* variable = 0;
        if (! parseContext.arrayQualifierError($4.line, $1.type)) {
            $1.type.arraySizes = $4.arraySizes;
            parseContext.arrayCheck($4.line, *$3.string, $1.type, variable);
        }

        parseContext.profileRequires($5.line, ENoProfile, 120, "GL_3DL_array_objects", "initializer");

        TIntermNode* intermNode;
        if (! parseContext.executeInitializerError($3.line, *$3.string, $1.type, $6, intermNode, variable)) {
            //
            // build the intermediate representation
            //
            if (intermNode)
                $$.intermAggregate = parseContext.intermediate.growAggregate($1.intermNode, intermNode, $5.line);
            else
                $$.intermAggregate = $1.intermAggregate;
        } else
            $$.intermAggregate = 0;
    }
    | init_declarator_list COMMA IDENTIFIER EQUAL initializer {
        $$ = $1;

        TIntermNode* intermNode;
        if (!parseContext.executeInitializerError($3.line, *$3.string, $1.type, $5, intermNode)) {
            //
            // build the intermediate representation
            //
            if (intermNode)
                $$.intermAggregate = parseContext.intermediate.growAggregate($1.intermNode, intermNode, $4.line);
            else
                $$.intermAggregate = $1.intermAggregate;
        } else
            $$.intermAggregate = 0;
    }
    ;

single_declaration
    : fully_specified_type {
        $$.type = $1;
        $$.intermAggregate = 0;
        parseContext.updateDefaults($1.line, $$.type, 0);
    }
    | fully_specified_type IDENTIFIER {
        $$.intermAggregate = 0;
        $$.type = $1;

        parseContext.nonInitConstCheck($2.line, *$2.string, $$.type);
        parseContext.nonInitCheck($2.line, *$2.string, $$.type);
        
        parseContext.updateDefaults($2.line, $$.type, $2.string);
    }
    | fully_specified_type IDENTIFIER array_specifier {
        $$.intermAggregate = 0;
        parseContext.nonInitConstCheck($2.line, *$2.string, $1);        
        if (parseContext.profile == EEsProfile)
            parseContext.arraySizeRequiredCheck($3.line, $3.arraySizes->front());

        $$.type = $1;

        if (! parseContext.arrayQualifierError($3.line, $1)) {
            $1.arraySizes = $3.arraySizes;
            TVariable* variable;
            parseContext.arrayCheck($3.line, *$2.string, $1, variable);
        }
        parseContext.updateDefaults($2.line, $$.type, $2.string);
    }
    | fully_specified_type IDENTIFIER array_specifier EQUAL initializer {
        $$.intermAggregate = 0;
        $$.type = $1;

        TVariable* variable = 0;
        if (! parseContext.arrayQualifierError($3.line, $1)) {
            $1.arraySizes = $3.arraySizes;
            parseContext.arrayCheck($3.line, *$2.string, $1, variable);
        }

        parseContext.profileRequires($4.line, ENoProfile, 120, "GL_3DL_array_objects", "initializer");

        TIntermNode* intermNode;
        if (!parseContext.executeInitializerError($2.line, *$2.string, $1, $5, intermNode, variable)) {
            //
            // Build intermediate representation
            //
            if (intermNode)
                $$.intermAggregate = parseContext.intermediate.makeAggregate(intermNode, $4.line);
            else
                $$.intermAggregate = 0;
        } else
            $$.intermAggregate = 0;
    }
    | fully_specified_type IDENTIFIER EQUAL initializer {
        $$.type = $1;

        TIntermNode* intermNode;
        if (!parseContext.executeInitializerError($2.line, *$2.string, $1, $4, intermNode)) {
            //
            // Build intermediate representation
            //
            if (intermNode)
                $$.intermAggregate = parseContext.intermediate.makeAggregate(intermNode, $3.line);
            else
                $$.intermAggregate = 0;
        } else
            $$.intermAggregate = 0;
    }

// Grammar Note:  No 'enum', or 'typedef'.

fully_specified_type
    : type_specifier {
        $$ = $1;

        if ($1.arraySizes) {
            parseContext.profileRequires($1.line, ENoProfile, 120, "GL_3DL_array_objects", "arrayed type");
            parseContext.profileRequires($1.line, EEsProfile, 300, 0, "arrayed type");
            if (parseContext.profile == EEsProfile)
                parseContext.arraySizeRequiredCheck($1.line, $1.arraySizes->front());
        }
    }
    | type_qualifier type_specifier  {
        parseContext.globalQualifierFix($1.line, $1.qualifier, $2);

        if ($2.arraySizes) {
            parseContext.profileRequires($2.line, ENoProfile, 120, "GL_3DL_array_objects", "arrayed type");
            parseContext.profileRequires($2.line, EEsProfile, 300, 0, "arrayed type");
            if (parseContext.profile == EEsProfile)
                parseContext.arraySizeRequiredCheck($2.line, $2.arraySizes->front());
        }

        if ($2.arraySizes && parseContext.arrayQualifierError($2.line, $1))
            $2.arraySizes = 0;
        
        parseContext.mergeQualifiers($2.line, $2, $1, true);

        $$ = $2;

        if (! $$.qualifier.isInterpolation() && parseContext.language == EShLangFragment)
            $$.qualifier.smooth = true;
    }
    ;

invariant_qualifier
    : INVARIANT {
        parseContext.profileRequires($$.line, ENoProfile, 120, 0, "invariant");
        $$.init($1.line);
        $$.qualifier.invariant = true;
    }
    ;

interpolation_qualifier
    : SMOOTH {
        parseContext.globalCheck($1.line, parseContext.symbolTable.atGlobalLevel(), "smooth");
        parseContext.profileRequires($1.line, ENoProfile, 130, 0, "smooth");
        parseContext.profileRequires($1.line, EEsProfile, 300, 0, "smooth");
        $$.init($1.line);
        $$.qualifier.smooth = true;
    }
    | FLAT {
        parseContext.globalCheck($1.line, parseContext.symbolTable.atGlobalLevel(), "flat");
        parseContext.profileRequires($1.line, ENoProfile, 130, 0, "flat");
        parseContext.profileRequires($1.line, EEsProfile, 300, 0, "flat");
        $$.init($1.line);
        $$.qualifier.flat = true;
    }
    | NOPERSPECTIVE {
        parseContext.globalCheck($1.line, parseContext.symbolTable.atGlobalLevel(), "noperspective");
        parseContext.requireProfile($1.line, static_cast<EProfileMask>(~EEsProfileMask), "noperspective");
        parseContext.profileRequires($1.line, ENoProfile, 130, 0, "noperspective");
        $$.init($1.line);
        $$.qualifier.nopersp = true;
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
        parseContext.mergeLayoutQualifiers($2.line, $$.qualifier, $3.qualifier);
    }

layout_qualifier_id
    : IDENTIFIER {
        $$.init($1.line);
        parseContext.setLayoutQualifier($1.line, $$, *$1.string);
    }
    | IDENTIFIER EQUAL INTCONSTANT {
        $$.init($1.line);
        parseContext.setLayoutQualifier($1.line, $$, *$1.string, $3.i);
    }
    | SHARED { // because "shared" is both an identifier and a keyword
        $$.init($1.line);
        TString strShared("shared");
        parseContext.setLayoutQualifier($1.line, $$, strShared);
    }
    ;

precise_qualifier
    : PRECISE {
        $$.init($1.line);
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

        parseContext.mergeQualifiers($$.line, $$, $2, false);
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
    | precise_qualifier {
        // allow inheritance of storage qualifier from block declaration
        $$ = $1;
    }
    ;

storage_qualifier
    : CONST {
        $$.init($1.line);
        $$.qualifier.storage = EvqConst;
    }
    | ATTRIBUTE {
        parseContext.requireStage($1.line, EShLangVertexMask, "attribute");
        parseContext.checkDeprecated($1.line, ECoreProfile, 130, "attribute");
        parseContext.checkDeprecated($1.line, ENoProfile, 130, "attribute");
        parseContext.requireNotRemoved($1.line, ECoreProfile, 420, "attribute");
        parseContext.requireNotRemoved($1.line, EEsProfile, 300, "attribute");

        parseContext.globalCheck($1.line, parseContext.symbolTable.atGlobalLevel(), "attribute");

        $$.init($1.line);
        $$.qualifier.storage = EvqVaryingIn;
    }
    | VARYING {
        parseContext.checkDeprecated($1.line, ENoProfile, 130, "varying");
        parseContext.checkDeprecated($1.line, ECoreProfile, 130, "varying");
        parseContext.requireNotRemoved($1.line, ECoreProfile, 420, "varying");
        parseContext.requireNotRemoved($1.line, EEsProfile, 300, "varying");

        parseContext.globalCheck($1.line, parseContext.symbolTable.atGlobalLevel(), "varying");

        $$.init($1.line);
        if (parseContext.language == EShLangVertex)
            $$.qualifier.storage = EvqVaryingOut;
        else
            $$.qualifier.storage = EvqVaryingIn;
    }
    | INOUT {
        parseContext.globalCheck($1.line, parseContext.symbolTable.atGlobalLevel(), "out");
        $$.init($1.line);
        $$.qualifier.storage = EvqInOut;
    }
    | IN {
        parseContext.globalCheck($1.line, parseContext.symbolTable.atGlobalLevel(), "in");
        $$.init($1.line);
        $$.qualifier.storage = EvqIn;
    }
    | OUT {
        parseContext.globalCheck($1.line, parseContext.symbolTable.atGlobalLevel(), "out");
        $$.init($1.line);
        $$.qualifier.storage = EvqOut;
    }
    | CENTROID {
        parseContext.profileRequires($1.line, ENoProfile, 120, 0, "centroid");
        parseContext.profileRequires($1.line, EEsProfile, 300, 0, "centroid");
        parseContext.globalCheck($1.line, parseContext.symbolTable.atGlobalLevel(), "centroid");
        $$.init($1.line);
        $$.qualifier.centroid = true;
    }
    | PATCH {
        parseContext.globalCheck($1.line, parseContext.symbolTable.atGlobalLevel(), "patch");
        $$.init($1.line);
        $$.qualifier.patch = true;
    }
    | SAMPLE {
        parseContext.globalCheck($1.line, parseContext.symbolTable.atGlobalLevel(), "sample");
        $$.init($1.line);
        $$.qualifier.sample = true;
    }
    | UNIFORM {
        parseContext.globalCheck($1.line, parseContext.symbolTable.atGlobalLevel(), "uniform");
        $$.init($1.line);
        $$.qualifier.storage = EvqUniform;
    }
    | BUFFER {
        parseContext.globalCheck($1.line, parseContext.symbolTable.atGlobalLevel(), "buffer");
        $$.init($1.line);
        $$.qualifier.storage = EvqUniform; // TODO: 4.0 functionality: implement BUFFER
    }
    | SHARED {
        parseContext.requireProfile($1.line, static_cast<EProfileMask>(~EEsProfileMask), "shared");
        parseContext.profileRequires($1.line, ECoreProfile, 430, 0, "shared");
        parseContext.requireStage($1.line, EShLangComputeMask, "shared");
        $$.init($1.line);
        $$.qualifier.shared = true;
    }
    | COHERENT {
        $$.init($1.line);
        $$.qualifier.coherent = true;
    }
    | VOLATILE {
        $$.init($1.line);
        $$.qualifier.volatil = true;
    }
    | RESTRICT {
        $$.init($1.line);
        $$.qualifier.restrict = true;
    }
    | READONLY {
        $$.init($1.line);
        $$.qualifier.readonly = true;
    }
    | WRITEONLY {
        $$.init($1.line);
        $$.qualifier.writeonly = true;
    }
    | SUBROUTINE {
        parseContext.globalCheck($1.line, parseContext.symbolTable.atGlobalLevel(), "subroutine");
        $$.init($1.line);
        $$.qualifier.storage = EvqUniform;
    }
    | SUBROUTINE LEFT_PAREN type_name_list RIGHT_PAREN {
        parseContext.globalCheck($1.line, parseContext.symbolTable.atGlobalLevel(), "subroutine");
        $$.init($1.line);
        $$.qualifier.storage = EvqUniform;
        // TODO: 4.0 semantics: subroutines
        // 1) make sure each identifier is a type declared earlier with SUBROUTINE
        // 2) save all of the identifiers for future comparison with the declared function
    }
    ;

type_name_list
    : TYPE_NAME {
        // TODO: 4.0 functionality: subroutine type to list
    }
    | type_name_list COMMA TYPE_NAME {
    }
    ;

type_specifier
    : type_specifier_nonarray {
        $$ = $1;
        $$.qualifier.precision = parseContext.defaultPrecision[$$.basicType];
    }
    | type_specifier_nonarray array_specifier {        
        $$ = $1;
        $$.qualifier.precision = parseContext.defaultPrecision[$$.basicType];
        $$.arraySizes = $2.arraySizes;
    }
    ;

array_specifier
    : LEFT_BRACKET RIGHT_BRACKET {
        $$.line = $1.line;
        $$.arraySizes = NewPoolTArraySizes();
        $$.arraySizes->push_back(0);
    }
    | LEFT_BRACKET constant_expression RIGHT_BRACKET {
        $$.line = $1.line;
        $$.arraySizes = NewPoolTArraySizes();

        int size;
        parseContext.arraySizeCheck($2->getLine(), $2, size);
        $$.arraySizes->push_back(size);
    }
    | array_specifier LEFT_BRACKET RIGHT_BRACKET {
        $$ = $1;
        $$.arraySizes->push_back(0);
    }
    | array_specifier LEFT_BRACKET constant_expression RIGHT_BRACKET {
        $$ = $1;

        int size;
        parseContext.arraySizeCheck($3->getLine(), $3, size);
        $$.arraySizes->push_back(size);
    }
    ;

type_specifier_nonarray
    : VOID {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtVoid;
    }
    | FLOAT {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtFloat;
    }
    | DOUBLE {
        parseContext.doubleCheck($1.line, "double");
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtDouble;
    }
    | INT {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtInt;
    }
    | UINT {
        parseContext.fullIntegerCheck($1.line, "unsigned integer");
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtUint;
    }
    | BOOL {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtBool;
    }
    | VEC2 {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtFloat;
        $$.setVector(2);
    }
    | VEC3 {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtFloat;
        $$.setVector(3);
    }
    | VEC4 {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtFloat;
        $$.setVector(4);
    }
    | DVEC2 {
        parseContext.doubleCheck($1.line, "double vector");
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtDouble;
        $$.setVector(2);
    }
    | DVEC3 {
        parseContext.doubleCheck($1.line, "double vector");
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtDouble;
        $$.setVector(3);
    }
    | DVEC4 {
        parseContext.doubleCheck($1.line, "double vector");
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtDouble;
        $$.setVector(4);
    }
    | BVEC2 {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtBool;
        $$.setVector(2);
    }
    | BVEC3 {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtBool;
        $$.setVector(3);
    }
    | BVEC4 {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtBool;
        $$.setVector(4);
    }
    | IVEC2 {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtInt;
        $$.setVector(2);
    }
    | IVEC3 {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtInt;
        $$.setVector(3);
    }
    | IVEC4 {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtInt;
        $$.setVector(4);
    }
    | UVEC2 {
        parseContext.fullIntegerCheck($1.line, "unsigned integer vector");
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtUint;
        $$.setVector(2);
    }
    | UVEC3 {
        parseContext.fullIntegerCheck($1.line, "unsigned integer vector");
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtUint;
        $$.setVector(3);
    }
    | UVEC4 {
        parseContext.fullIntegerCheck($1.line, "unsigned integer vector");
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtUint;
        $$.setVector(4);
    }
    | MAT2 {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtFloat;
        $$.setMatrix(2, 2);
    }
    | MAT3 {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtFloat;
        $$.setMatrix(3, 3);
    }
    | MAT4 {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtFloat;
        $$.setMatrix(4, 4);
    }
    | MAT2X2 {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtFloat;
        $$.setMatrix(2, 2);
    }
    | MAT2X3 {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtFloat;
        $$.setMatrix(2, 3);
    }
    | MAT2X4 {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtFloat;
        $$.setMatrix(2, 4);
    }
    | MAT3X2 {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtFloat;
        $$.setMatrix(3, 2);
    }
    | MAT3X3 {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtFloat;
        $$.setMatrix(3, 3);
    }
    | MAT3X4 {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtFloat;
        $$.setMatrix(3, 4);
    }
    | MAT4X2 {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtFloat;
        $$.setMatrix(4, 2);
    }
    | MAT4X3 {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtFloat;
        $$.setMatrix(4, 3);
    }
    | MAT4X4 {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtFloat;
        $$.setMatrix(4, 4);
    }
    | DMAT2 {
        parseContext.doubleCheck($1.line, "double matrix");
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtDouble;
        $$.setMatrix(2, 2);
    }
    | DMAT3 {
        parseContext.doubleCheck($1.line, "double matrix");
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtDouble;
        $$.setMatrix(3, 3);
    }
    | DMAT4 {
        parseContext.doubleCheck($1.line, "double matrix");
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtDouble;
        $$.setMatrix(4, 4);
    }
    | DMAT2X2 {
        parseContext.doubleCheck($1.line, "double matrix");
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtDouble;
        $$.setMatrix(2, 2);
    }
    | DMAT2X3 {
        parseContext.doubleCheck($1.line, "double matrix");
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtDouble;
        $$.setMatrix(2, 3);
    }
    | DMAT2X4 {
        parseContext.doubleCheck($1.line, "double matrix");
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtDouble;
        $$.setMatrix(2, 4);
    }
    | DMAT3X2 {
        parseContext.doubleCheck($1.line, "double matrix");
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtDouble;
        $$.setMatrix(3, 2);
    }
    | DMAT3X3 {
        parseContext.doubleCheck($1.line, "double matrix");
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtDouble;
        $$.setMatrix(3, 3);
    }
    | DMAT3X4 {
        parseContext.doubleCheck($1.line, "double matrix");
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtDouble;
        $$.setMatrix(3, 4);
    }
    | DMAT4X2 {
        parseContext.doubleCheck($1.line, "double matrix");
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtDouble;
        $$.setMatrix(4, 2);
    }
    | DMAT4X3 {
        parseContext.doubleCheck($1.line, "double matrix");
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtDouble;
        $$.setMatrix(4, 3);
    }
    | DMAT4X4 {
        parseContext.doubleCheck($1.line, "double matrix");
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtDouble;
        $$.setMatrix(4, 4);
    }
    | ATOMIC_UINT {
        // TODO: 4.2 functionality: add type
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtInt;
    }
    | SAMPLER1D {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtFloat, Esd1D);
    }
    | SAMPLER2D {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtFloat, Esd2D);
    }
    | SAMPLER3D {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtFloat, Esd3D);
    }
    | SAMPLERCUBE {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtFloat, EsdCube);
    }
    | SAMPLER1DSHADOW {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtFloat, Esd1D, false, true);
    }
    | SAMPLER2DSHADOW {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtFloat, Esd2D, false, true);
    }
    | SAMPLERCUBESHADOW {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtFloat, EsdCube, false, true);
    }
    | SAMPLER1DARRAY {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtFloat, Esd1D, true);
    }
    | SAMPLER2DARRAY {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtFloat, Esd2D, true);
    }
    | SAMPLER1DARRAYSHADOW {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtFloat, Esd1D, true, true);
    }
    | SAMPLER2DARRAYSHADOW {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtFloat, Esd2D, true, true);
    }
    | SAMPLERCUBEARRAY {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtFloat, EsdCube, true);
    }
    | SAMPLERCUBEARRAYSHADOW {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtFloat, EsdCube, true, true);
    }
    | ISAMPLER1D {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtInt, Esd1D);
    }
    | ISAMPLER2D {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtInt, Esd2D);
    }
    | ISAMPLER3D {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtInt, Esd3D);
    }
    | ISAMPLERCUBE {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtInt, EsdCube);
    }
    | ISAMPLER1DARRAY {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtInt, Esd1D, true);
    }
    | ISAMPLER2DARRAY {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtInt, Esd2D, true);
    }
    | ISAMPLERCUBEARRAY {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtInt, Esd3D, true);
    }
    | USAMPLER1D {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtUint, Esd1D);
    }
    | USAMPLER2D {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtUint, Esd2D);
    }
    | USAMPLER3D {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtUint, Esd3D);
    }
    | USAMPLERCUBE {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtUint, EsdCube);
    }
    | USAMPLER1DARRAY {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtUint, Esd1D, true);
    }
    | USAMPLER2DARRAY {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtUint, Esd2D, true);
    }
    | USAMPLERCUBEARRAY {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtUint, EsdCube, true);
    }
    | SAMPLER2DRECT {
        parseContext.profileRequires($1.line, ENoProfile, 140, "GL_ARB_texture_rectangle", "rectangle texture");

        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtFloat, EsdRect);
    }
    | SAMPLER2DRECTSHADOW {
        parseContext.profileRequires($1.line, ECoreProfile, 140, "GL_ARB_texture_rectangle", "rectangle texture");

        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtFloat, EsdRect, false, true);
    }
    | ISAMPLER2DRECT {
        parseContext.profileRequires($1.line, ECoreProfile, 140, "GL_ARB_texture_rectangle", "rectangle texture");

        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtInt, EsdRect);
    }
    | USAMPLER2DRECT {
        parseContext.profileRequires($1.line, ECoreProfile, 140, "GL_ARB_texture_rectangle", "rectangle texture");

        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtUint, EsdRect);
    }
    | SAMPLERBUFFER {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtFloat, EsdBuffer);
    }
    | ISAMPLERBUFFER {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtInt, EsdBuffer);
    }
    | USAMPLERBUFFER {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtUint, EsdBuffer);
    }
    | SAMPLER2DMS {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtFloat, Esd2D, false, false, true);
    }
    | ISAMPLER2DMS {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtInt, Esd2D, false, false, true);
    }
    | USAMPLER2DMS {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtUint, Esd2D, false, false, true);
    }
    | SAMPLER2DMSARRAY {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtFloat, Esd2D, true, false, true);
    }
    | ISAMPLER2DMSARRAY {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtInt, Esd2D, true, false, true);
    }
    | USAMPLER2DMSARRAY {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.set(EbtUint, Esd2D, true, false, true);
    }
    | IMAGE1D {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setImage(EbtFloat, Esd1D);
    }
    | IIMAGE1D {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setImage(EbtInt, Esd1D);
    }
    | UIMAGE1D {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setImage(EbtUint, Esd1D);
    }
    | IMAGE2D {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setImage(EbtFloat, Esd2D);
    }
    | IIMAGE2D {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setImage(EbtInt, Esd2D);
    }
    | UIMAGE2D {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setImage(EbtUint, Esd2D);
    }
    | IMAGE3D {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setImage(EbtFloat, Esd3D);
    }
    | IIMAGE3D {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setImage(EbtInt, Esd3D);
    }
    | UIMAGE3D {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setImage(EbtUint, Esd3D);
    }
    | IMAGE2DRECT {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setImage(EbtFloat, EsdRect);
    }
    | IIMAGE2DRECT {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setImage(EbtInt, EsdRect);
    }
    | UIMAGE2DRECT {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setImage(EbtUint, EsdRect);
    }
    | IMAGECUBE {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setImage(EbtFloat, EsdCube);
    }
    | IIMAGECUBE {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setImage(EbtInt, EsdCube);
    }
    | UIMAGECUBE {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setImage(EbtUint, EsdCube);
    }
    | IMAGEBUFFER {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setImage(EbtFloat, EsdBuffer);
    }
    | IIMAGEBUFFER {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setImage(EbtInt, EsdBuffer);
    }
    | UIMAGEBUFFER {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setImage(EbtUint, EsdBuffer);
    }
    | IMAGE1DARRAY {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setImage(EbtFloat, Esd1D, true);
    }
    | IIMAGE1DARRAY {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setImage(EbtInt, Esd1D, true);
    }
    | UIMAGE1DARRAY {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setImage(EbtUint, Esd1D, true);
    }
    | IMAGE2DARRAY {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setImage(EbtFloat, Esd2D, true);
    }
    | IIMAGE2DARRAY {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setImage(EbtInt, Esd2D, true);
    }
    | UIMAGE2DARRAY {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setImage(EbtUint, Esd2D, true);
    }
    | IMAGECUBEARRAY {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setImage(EbtFloat, EsdCube, true);
    }
    | IIMAGECUBEARRAY {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setImage(EbtInt, EsdCube, true);
    }
    | UIMAGECUBEARRAY {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setImage(EbtUint, EsdCube, true);
    }
    | IMAGE2DMS {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setImage(EbtFloat, Esd2D, false, false, true);
    }
    | IIMAGE2DMS {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setImage(EbtInt, Esd2D, false, false, true);
    }
    | UIMAGE2DMS {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setImage(EbtUint, Esd2D, false, false, true);
    }
    | IMAGE2DMSARRAY {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setImage(EbtFloat, Esd2D, true, false, true);
    }
    | IIMAGE2DMSARRAY {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setImage(EbtInt, Esd2D, true, false, true);
    }
    | UIMAGE2DMSARRAY {
        $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
        $$.basicType = EbtSampler;
        $$.sampler.setImage(EbtUint, Esd2D, true, false, true);
    }
    | struct_specifier {
        $$ = $1;
        $$.qualifier.storage = parseContext.symbolTable.atGlobalLevel() ? EvqGlobal : EvqTemporary;
    }
    | TYPE_NAME {
        //
        // This is for user defined type names.  The lexical phase looked up the
        // type.
        //
        if (TVariable* variable = ($1.symbol)->getAsVariable()) {
            const TType& structure = variable->getType();
            $$.init($1.line, parseContext.symbolTable.atGlobalLevel());
            $$.basicType = EbtStruct;
            $$.userDef = &structure;
        } else
            parseContext.error($1.line, "expected type name", $1.string->c_str(), "");
    }
    ;

precision_qualifier
    : HIGH_PRECISION {
        parseContext.profileRequires($1.line, ENoProfile, 130, 0, "highp precision qualifier");
        $$.init($1.line);
        if (parseContext.profile == EEsProfile)
		    $$.qualifier.precision = EpqHigh;
    }
    | MEDIUM_PRECISION {
        parseContext.profileRequires($1.line, ENoProfile, 130, 0, "mediump precision qualifier");
        $$.init($1.line);
        if (parseContext.profile == EEsProfile)
	    	$$.qualifier.precision = EpqMedium;
    }
    | LOW_PRECISION {
        parseContext.profileRequires($1.line, ENoProfile, 130, 0, "lowp precision qualifier");
        $$.init($1.line);
        if (parseContext.profile == EEsProfile)
    		$$.qualifier.precision = EpqLow;
    }
    ;

struct_specifier
    : STRUCT IDENTIFIER LEFT_BRACE { parseContext.nestedStructCheck($1.line); } struct_declaration_list RIGHT_BRACE {
        TType* structure = new TType($5, *$2.string);
        TVariable* userTypeDef = new TVariable($2.string, *structure, true);
        if (! parseContext.symbolTable.insert(*userTypeDef))
            parseContext.error($2.line, "redefinition", $2.string->c_str(), "struct");
        $$.init($1.line);
        $$.basicType = EbtStruct;
        $$.userDef = structure;
        --parseContext.structNestingLevel;
    }
    | STRUCT LEFT_BRACE { parseContext.nestedStructCheck($1.line); } struct_declaration_list RIGHT_BRACE {
        TType* structure = new TType($4, TString(""));
        $$.init($1.line);
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
                    parseContext.error((*$2)[i].line, "duplicate member name:", "", (*$2)[i].type->getFieldName().c_str());
            }
            $$->push_back((*$2)[i]);
        }
    }
    ;

struct_declaration
    : type_specifier struct_declarator_list SEMICOLON {
        if ($1.arraySizes) {
            parseContext.profileRequires($1.line, ENoProfile, 120, "GL_3DL_array_objects", "arrayed type");
            parseContext.profileRequires($1.line, EEsProfile, 300, 0, "arrayed type");
            if (parseContext.profile == EEsProfile)
                parseContext.arraySizeRequiredCheck($1.line, $1.arraySizes->front());
        }

        $$ = $2;

        parseContext.voidErrorCheck($1.line, (*$2)[0].type->getFieldName(), $1);

        for (unsigned int i = 0; i < $$->size(); ++i)
            (*$$)[i].type->mergeType($1);
    }
    | type_qualifier type_specifier struct_declarator_list SEMICOLON {
        if ($2.arraySizes) {
            parseContext.profileRequires($2.line, ENoProfile, 120, "GL_3DL_array_objects", "arrayed type");
            parseContext.profileRequires($2.line, EEsProfile, 300, 0, "arrayed type");
            if (parseContext.profile == EEsProfile)
                parseContext.arraySizeRequiredCheck($2.line, $2.arraySizes->front());
        }

        $$ = $3;

        parseContext.voidErrorCheck($2.line, (*$3)[0].type->getFieldName(), $2);
        parseContext.mergeQualifiers($2.line, $2, $1, true);

        for (unsigned int i = 0; i < $$->size(); ++i)
            (*$$)[i].type->mergeType($2);
    }
    ;

struct_declarator_list
    : struct_declarator {
        $$ = NewPoolTTypeList();
        $$->push_back($1);
    }
    | struct_declarator_list COMMA struct_declarator {
        $$->push_back($3);
    }
    ;

struct_declarator
    : IDENTIFIER {
        $$.type = new TType(EbtVoid);
        $$.line = $1.line;
        $$.type->setFieldName(*$1.string);
    }
    | IDENTIFIER array_specifier {        
        if (parseContext.profile == EEsProfile)
            parseContext.arraySizeRequiredCheck($2.line, $2.arraySizes->front());
        $$.type = new TType(EbtVoid);
        $$.line = $1.line;
        $$.type->setFieldName(*$1.string);
        $$.type->setArraySizes($2.arraySizes);
    }
    ;

initializer
    : assignment_expression {
        $$ = $1;
    }
    | LEFT_BRACE initializer_list RIGHT_BRACE {
        $$ = $2;
    }
    | LEFT_BRACE initializer_list COMMA RIGHT_BRACE {
        $$ = $2;
    }
    ;

initializer_list
    : initializer {
        $$ = $1;
    }
    | initializer_list COMMA initializer {
        // TODO: 4.2 functionality: implement the initializer list
        $$ = $3;
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
    | LEFT_BRACE { parseContext.symbolTable.push(); }
      statement_list { parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]); }
      RIGHT_BRACE {
        if ($3 != 0)
            $3->setOperator(EOpSequence);
        $$ = $3;
    }
    ;

statement_no_new_scope
    : compound_statement_no_new_scope { $$ = $1; }
    | simple_statement                { $$ = $1; }
    ;

compound_statement_no_new_scope
    // Statement that doesn't create a new scope, for selection_statement, iteration_statement
    : LEFT_BRACE RIGHT_BRACE {
        $$ = 0;
    }
    | LEFT_BRACE statement_list RIGHT_BRACE {
        if ($2)
            $2->setOperator(EOpSequence);
        $$ = $2;
    }
    ;

statement_list
    : statement {
        $$ = parseContext.intermediate.makeAggregate($1, 0);
        if ($1 && $1->getAsBranchNode() && ($1->getAsBranchNode()->getFlowOp() == EOpCase ||
                                            $1->getAsBranchNode()->getFlowOp() == EOpDefault)) {
            parseContext.wrapupSwitchSubsequence(0, $1);
            $$ = 0;  // start a fresh subsequence for what's after this case
        }
    }
    | statement_list statement {
        if ($2 && $2->getAsBranchNode() && ($2->getAsBranchNode()->getFlowOp() == EOpCase || 
                                            $2->getAsBranchNode()->getFlowOp() == EOpDefault)) {
            parseContext.wrapupSwitchSubsequence($1, $2);
            $$ = 0;  // start a fresh subsequence for what's after this case
        } else
            $$ = parseContext.intermediate.growAggregate($1, $2, 0);
    }
    ;

expression_statement
    : SEMICOLON  { $$ = 0; }
    | expression SEMICOLON  { $$ = static_cast<TIntermNode*>($1); }
    ;

selection_statement
    : IF LEFT_PAREN expression RIGHT_PAREN selection_rest_statement {
        parseContext.boolCheck($1.line, $3);
        $$ = parseContext.intermediate.addSelection($3, $5, $1.line);
    }
    ;

selection_rest_statement
    : statement ELSE statement {
        $$.node1 = $1;
        $$.node2 = $3;
    }
    | statement {
        $$.node1 = $1;
        $$.node2 = 0;
    }
    ;

condition
    // In 1996 c++ draft, conditions can include single declarations
    : expression {
        $$ = $1;
        parseContext.boolCheck($1->getLine(), $1);
    }
    | fully_specified_type IDENTIFIER EQUAL initializer {
        TIntermNode* intermNode;
        parseContext.boolCheck($2.line, $1);

        if (parseContext.executeInitializerError($2.line, *$2.string, $1, $4, intermNode))
            $$ = 0;
        else
            $$ = $4;
    }
    ;

switch_statement
    : SWITCH LEFT_PAREN expression RIGHT_PAREN {
        // start new switch sequence on the switch stack
        parseContext.switchSequenceStack.push_back(new TIntermSequence);
    } 
    LEFT_BRACE switch_statement_list RIGHT_BRACE {
        $$ = parseContext.addSwitch($1.line, $3, $7);
        delete parseContext.switchSequenceStack.back();
        parseContext.switchSequenceStack.pop_back();
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
        $$ = parseContext.intermediate.addBranch(EOpCase, $2, $1.line);
    }
    | DEFAULT COLON {
        $$ = parseContext.intermediate.addBranch(EOpDefault, $1.line);
    }
    ;

iteration_statement
    : WHILE LEFT_PAREN {
        parseContext.symbolTable.push();
        ++parseContext.loopNestingLevel;
    }
      condition RIGHT_PAREN statement_no_new_scope {
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        $$ = parseContext.intermediate.addLoop($6, $4, 0, true, $1.line);
        --parseContext.loopNestingLevel;
    }
    | DO { ++parseContext.loopNestingLevel; } statement WHILE LEFT_PAREN expression RIGHT_PAREN SEMICOLON {
        parseContext.boolCheck($8.line, $6);

        $$ = parseContext.intermediate.addLoop($3, $6, 0, false, $4.line);
        --parseContext.loopNestingLevel;
    }
    | FOR LEFT_PAREN {
        parseContext.symbolTable.push();
        ++parseContext.loopNestingLevel;
    }
      for_init_statement for_rest_statement RIGHT_PAREN statement_no_new_scope {
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        $$ = parseContext.intermediate.makeAggregate($4, $2.line);
        $$ = parseContext.intermediate.growAggregate(
                $$,
                parseContext.intermediate.addLoop($7, reinterpret_cast<TIntermTyped*>($5.node1), reinterpret_cast<TIntermTyped*>($5.node2), true, $1.line),
                $1.line);
        $$->getAsAggregate()->setOperator(EOpSequence);
        --parseContext.loopNestingLevel;
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
            parseContext.error($1.line, "continue statement only allowed in loops", "", "");
        $$ = parseContext.intermediate.addBranch(EOpContinue, $1.line);
    }
    | BREAK SEMICOLON {
        if (parseContext.loopNestingLevel + parseContext.switchSequenceStack.size() <= 0)
            parseContext.error($1.line, "break statement only allowed in switch and loops", "", "");
        $$ = parseContext.intermediate.addBranch(EOpBreak, $1.line);
    }
    | RETURN SEMICOLON {
        $$ = parseContext.intermediate.addBranch(EOpReturn, $1.line);
        if (parseContext.currentFunctionType->getBasicType() != EbtVoid)
            parseContext.error($1.line, "non-void function must return a value", "return", "");
    }
    | RETURN expression SEMICOLON {
        $$ = parseContext.intermediate.addBranch(EOpReturn, $2, $1.line);
        parseContext.functionReturnsValue = true;
        if (parseContext.currentFunctionType->getBasicType() == EbtVoid)
            parseContext.error($1.line, "void function cannot return a value", "return", "");
        else if (*(parseContext.currentFunctionType) != $2->getType())
            parseContext.error($1.line, "function return is not matching type:", "return", "");
    }
    | DISCARD SEMICOLON {
        parseContext.requireStage($1.line, EShLangFragmentMask, "discard");
        $$ = parseContext.intermediate.addBranch(EOpKill, $1.line);
    }
    ;

// Grammar Note:  No 'goto'.  Gotos are not supported.

translation_unit
    : external_declaration {
        $$ = $1;
        parseContext.treeRoot = $$;
    }
    | translation_unit external_declaration {
        $$ = parseContext.intermediate.growAggregate($1, $2, 0);
        parseContext.treeRoot = $$;
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
        TFunction& function = *($1.function);
        TSymbol* symbol = parseContext.symbolTable.find(function.getMangledName());
        TFunction* prevDec = symbol ? symbol->getAsFunction() : 0;

        if (! prevDec)
            parseContext.error($1.line, "can't find function name", function.getName().c_str(), "");

        //
        // Note:  'prevDec' could be 'function' if this is the first time we've seen function
        // as it would have just been put in the symbol table.  Otherwise, we're looking up
        // an earlier occurance.
        //
        if (prevDec && prevDec->isDefined()) {
            //
            // Then this function already has a body.
            //
            parseContext.error($1.line, "function already has a body", function.getName().c_str(), "");
        }
        if (prevDec) {
            prevDec->setDefined();
            //
            // Remember the return type for later checking for RETURN statements.
            //
            parseContext.currentFunctionType = &(prevDec->getReturnType());
        } else
             parseContext.currentFunctionType = new TType(EbtVoid);
        parseContext.functionReturnsValue = false;

        //
        // Raise error message if main function takes any parameters or return anything other than void
        //
        if (function.getName() == "main") {
            if (function.getParamCount() > 0)
                parseContext.error($1.line, "function cannot take any parameter(s)", function.getName().c_str(), "");
            if (function.getReturnType().getBasicType() != EbtVoid)
                parseContext.error($1.line, "", function.getReturnType().getCompleteTypeString().c_str(), "main function cannot return a value");
        }

        //
        // New symbol table scope for body of function plus its arguments
        //
        parseContext.symbolTable.push();

        //
        // Insert parameters into the symbol table.
        // If the parameter has no name, it's not an error, just don't insert it
        // (could be used for unused args).
        //
        // Also, accumulate the list of parameters into the HIL, so lower level code
        // knows where to find parameters.
        //
        TIntermAggregate* paramNodes = new TIntermAggregate;
        for (int i = 0; i < function.getParamCount(); i++) {
            TParameter& param = function[i];
            if (param.name != 0) {
                TVariable *variable = new TVariable(param.name, *param.type);
                //
                // Insert the parameters with name in the symbol table.
                //
                if (! parseContext.symbolTable.insert(*variable)) {
                    parseContext.error($1.line, "redefinition", variable->getName().c_str(), "");
                    delete variable;
                }
                //
                // Transfer ownership of name pointer to symbol table.
                //
                param.name = 0;

                //
                // Add the parameter to the HIL
                //
                paramNodes = parseContext.intermediate.growAggregate(
                                               paramNodes,
                                               parseContext.intermediate.addSymbol(variable->getUniqueId(),
                                                                       variable->getName(),
                                                                       variable->getType(), $1.line),
                                               $1.line);
            } else {
                paramNodes = parseContext.intermediate.growAggregate(paramNodes, parseContext.intermediate.addSymbol(0, "", *param.type, $1.line), $1.line);
            }
        }
        parseContext.intermediate.setAggregateOperator(paramNodes, EOpParameters, TType(EbtVoid), $1.line);
        $1.intermAggregate = paramNodes;
        parseContext.loopNestingLevel = 0;
    }
    compound_statement_no_new_scope {
        //   May be best done as post process phase on intermediate code
        if (parseContext.currentFunctionType->getBasicType() != EbtVoid && ! parseContext.functionReturnsValue)
            parseContext.error($1.line, "function does not return a value:", "", $1.function->getName().c_str());
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        $$ = parseContext.intermediate.growAggregate($1.intermAggregate, $3, 0);
        parseContext.intermediate.setAggregateOperator($$, EOpFunction, $1.function->getReturnType(), $1.line);
        $$->getAsAggregate()->setName($1.function->getMangledName().c_str());

        // store the pragma information for debug and optimize and other vendor specific
        // information. This information can be queried from the parse tree
        $$->getAsAggregate()->setOptimize(parseContext.contextPragma.optimize);
        $$->getAsAggregate()->setDebug(parseContext.contextPragma.debug);
        $$->getAsAggregate()->addToPragmaTable(parseContext.contextPragma.pragmaTable);
    }
    ;

%%
