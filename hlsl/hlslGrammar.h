//
// Copyright (C) 2016 Google, Inc.
// Copyright (C) 2016 LunarG, Inc.
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
//    Neither the name of Google, Inc., nor the names of its
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

#ifndef HLSLGRAMMAR_H_
#define HLSLGRAMMAR_H_

#include "hlslParseHelper.h"
#include "hlslOpMap.h"
#include "hlslTokenStream.h"

namespace glslang {

    class TAttributeMap;
    class TFunctionDeclarator;

    // Should just be the grammar aspect of HLSL.
    // Described in more detail in hlslGrammar.cpp.

    class HlslGrammar : public HlslTokenStream {
    public:
        HlslGrammar(HlslScanContext& scanner, HlslParseContext& parseContext)
            : HlslTokenStream(scanner), parseContext(parseContext), intermediate(parseContext.intermediate) { }
        virtual ~HlslGrammar() { }

        bool parse();

    protected:
        HlslGrammar();
        HlslGrammar& operator=(const HlslGrammar&);

        void expected(const char*);
        void unimplemented(const char*);
        bool acceptIdentifier(HlslToken&);
        bool acceptCompilationUnit();
        bool acceptDeclarationList(TIntermNode*&);
        bool acceptDeclaration(TIntermNode*&);
        bool acceptControlDeclaration(TIntermNode*& node);
        bool acceptSamplerDeclarationDX9(TType&);
        bool acceptSamplerState();
        bool acceptFullySpecifiedType(TType&);
        bool acceptFullySpecifiedType(TType&, TIntermNode*& nodeList);
        bool acceptQualifier(TQualifier&);
        bool acceptLayoutQualifierList(TQualifier&);
        bool acceptType(TType&);
        bool acceptType(TType&, TIntermNode*& nodeList);
        bool acceptTemplateVecMatBasicType(TBasicType&);
        bool acceptVectorTemplateType(TType&);
        bool acceptMatrixTemplateType(TType&);
        bool acceptTessellationDeclType();
        bool acceptTessellationPatchTemplateType(TType&);
        bool acceptStreamOutTemplateType(TType&, TLayoutGeometry&);
        bool acceptOutputPrimitiveGeometry(TLayoutGeometry&);
        bool acceptAnnotations(TQualifier&);
        bool acceptSamplerType(TType&);
        bool acceptTextureType(TType&);
        bool acceptStructBufferType(TType&);
        bool acceptStruct(TType&, TIntermNode*& nodeList);
        bool acceptStructDeclarationList(TTypeList*&, TIntermNode*& nodeList, TVector<TFunctionDeclarator>&);
        bool acceptMemberFunctionDefinition(TIntermNode*& nodeList, const TType&, const TString& memberName,
                                            TFunctionDeclarator&);
        bool acceptFunctionParameters(TFunction&);
        bool acceptParameterDeclaration(TFunction&);
        bool acceptFunctionDefinition(TFunctionDeclarator&, TIntermNode*& nodeList, TVector<HlslToken>* deferredTokens);
        bool acceptFunctionBody(TFunctionDeclarator& declarator, TIntermNode*& nodeList);
        bool acceptParenExpression(TIntermTyped*&);
        bool acceptExpression(TIntermTyped*&);
        bool acceptInitializer(TIntermTyped*&);
        bool acceptAssignmentExpression(TIntermTyped*&);
        bool acceptConditionalExpression(TIntermTyped*&);
        bool acceptBinaryExpression(TIntermTyped*&, PrecedenceLevel);
        bool acceptUnaryExpression(TIntermTyped*&);
        bool acceptPostfixExpression(TIntermTyped*&);
        bool acceptConstructor(TIntermTyped*&);
        bool acceptFunctionCall(const TSourceLoc&, TString& name, TIntermTyped*&, TIntermTyped* objectBase);
        bool acceptArguments(TFunction*, TIntermTyped*&);
        bool acceptLiteral(TIntermTyped*&);
        bool acceptCompoundStatement(TIntermNode*&);
        bool acceptStatement(TIntermNode*&);
        bool acceptScopedStatement(TIntermNode*&);
        bool acceptScopedCompoundStatement(TIntermNode*&);
        bool acceptNestedStatement(TIntermNode*&);
        void acceptAttributes(TAttributeMap&);
        bool acceptSelectionStatement(TIntermNode*&);
        bool acceptSwitchStatement(TIntermNode*&);
        bool acceptIterationStatement(TIntermNode*&);
        bool acceptJumpStatement(TIntermNode*&);
        bool acceptCaseLabel(TIntermNode*&);
        bool acceptDefaultLabel(TIntermNode*&);
        void acceptArraySpecifier(TArraySizes*&);
        bool acceptPostDecls(TQualifier&);
        bool acceptDefaultParameterDeclaration(const TType&, TIntermTyped*&);

        bool captureBlockTokens(TVector<HlslToken>& tokens);

        HlslParseContext& parseContext;  // state of parsing and helper functions for building the intermediate
        TIntermediate& intermediate;     // the final product, the intermediate representation, includes the AST
    };

} // end namespace glslang

#endif // HLSLGRAMMAR_H_
