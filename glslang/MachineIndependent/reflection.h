//
// Copyright (C) 2013-2016 LunarG, Inc.
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

#ifndef _REFLECTION_INCLUDED
#define _REFLECTION_INCLUDED

#include "../Public/ShaderLang.h"
#include "../Include/Types.h"

#include <list>
#include <set>

//
// A reflection database and its interface, consistent with the OpenGL API reflection queries.
//

namespace glslang {

class TIntermediate;
class TIntermAggregate;
class TReflectionTraverser;

// Data needed for just a single object at the granularity exchanged by the reflection API
class TObjectReflection {
public:
    TObjectReflection(const TString& pName, const TType& pType, int pOffset, int pGLDefineType, int pSize, int pIndex) :
        name(pName), offset(pOffset),
        glDefineType(pGLDefineType), size(pSize), index(pIndex), counterIndex(-1), type(pType.clone()) { }

    const TType* const getType() const { return type; }
    int getBinding() const
    {
        if (type == nullptr || !type->getQualifier().hasBinding())
            return -1;
        return type->getQualifier().layoutBinding;
    }
    void dump() const
    {
        printf("%s: offset %d, type %x, size %d, index %d, binding %d",
               name.c_str(), offset, glDefineType, size, index, getBinding() );

        if (counterIndex != -1)
            printf(", counter %d", counterIndex);

        printf("\n");
    }
    static TObjectReflection badReflection() { return TObjectReflection(); }

    TString name;
    int offset;
    int glDefineType;
    int size;         // data size in bytes for a block, array size for a (non-block) object that's an array
    int index;
    int counterIndex;

protected:
    TObjectReflection() : offset(-1), glDefineType(-1), size(-1), index(-1), type(nullptr) { }

    const TType* type;
};

// The full reflection database
class TReflection {
public:
    TReflection() : badReflection(TObjectReflection::badReflection())
    { 
        for (int dim=0; dim<3; ++dim)
            localSize[dim] = 0;
    }

    virtual ~TReflection() {}

    // grow the reflection stage by stage
    bool addStage(EShLanguage, const TIntermediate&);

    // for mapping a uniform index to a uniform object's description
    int getNumUniforms() { return (int)indexToUniform.size(); }
    const TObjectReflection& getUniform(int i) const
    {
        if (i >= 0 && i < (int)indexToUniform.size())
            return indexToUniform[i];
        else
            return badReflection;
    }

    // for mapping a block index to the block's description
    int getNumUniformBlocks() const { return (int)indexToUniformBlock.size(); }
    const TObjectReflection& getUniformBlock(int i) const
    {
        if (i >= 0 && i < (int)indexToUniformBlock.size())
            return indexToUniformBlock[i];
        else
            return badReflection;
    }

    // for mapping an attribute index to the attribute's description
    int getNumAttributes() { return (int)indexToAttribute.size(); }
    const TObjectReflection& getAttribute(int i) const
    {
        if (i >= 0 && i < (int)indexToAttribute.size())
            return indexToAttribute[i];
        else
            return badReflection;
    }

    // for mapping any name to its index (block names, uniform names and attribute names)
    int getIndex(const char* name) const
    {
        TNameToIndex::const_iterator it = nameToIndex.find(name);
        if (it == nameToIndex.end())
            return -1;
        else
            return it->second;
    }

    EShLanguageMask getUniformStages(int i) const
    {
        if (i >= 0 && i < (int)indexToUniform.size())
            return uniformStages[i];
        else
            return EShLanguageMask(0);
    }

    const TQualifier* getUniformQualifier(int i) const
    {
        if (i >= 0 && i < (int)indexToUniform.size())
            return uniformQualifiers[i];
        else
            return &badQualifier;
    }

    // VaryingIns
    int getNumInVaryings() { return (int)indexToVaryingIn.size(); }
    const TObjectReflection& getVaryingIn(int i) const
    {
        if (i >= 0 && i < (int)indexToVaryingIn.size())
            return indexToVaryingIn[i];
        else
            return badReflection;
    }

    int getVaryingInIndex(const char* name) const
    {
        TNameToIndex::const_iterator it = varyingInNameToIndex.find(name);
        if (it == varyingInNameToIndex.end())
            return -1;
        else
            return it->second;
    }

    const TQualifier* getVaryingInQualifier(int i) const
    {
        if (i >= 0 && i < (int)indexToVaryingIn.size())
            return varyingInQualifiers[i];
        else
            return &badQualifier;
    }

    void setVaryingInLocation(int i, int location)
    {
        if (i >= 0 && i < (int)indexToVaryingIn.size())
            varyingInQualifiers[i]->setLocation(location);
    }

    // VaryingOuts
    int getNumOutVaryings() { return (int)indexToVaryingOut.size(); }
    const TObjectReflection& getVaryingOut(int i) const
    {
        if (i >= 0 && i < (int)indexToVaryingOut.size())
            return indexToVaryingOut[i];
        else
            return badReflection;
    }

    int getVaryingOutIndex(const char* name) const
    {
        TNameToIndex::const_iterator it = varyingOutNameToIndex.find(name);
        if (it == varyingOutNameToIndex.end())
            return -1;
        else
            return it->second;
    }

    const TQualifier* getVaryingOutQualifier(int i) const
    {
        if (i >= 0 && i < (int)indexToVaryingOut.size())
            return varyingOutQualifiers[i];
        else
            return &badQualifier;
    }

    void setVaryingOutLocation(int i, int location)
    {
        if(i >= 0 && i < (int)indexToVaryingOut.size())
            varyingOutQualifiers[i]->setLocation(location);
    }

    const TQualifier* getAttributeQualifier(int i) const
    {
        if (i >= 0 && i < (int)indexToAttribute.size())
            return varyingInQualifiers[i];
        else
            return &badQualifier;
    }

    void setAttributeLocation(int i, int location)
    {
        if (i >= 0 && i < (int)indexToAttribute.size()){
            varyingInQualifiers[i]->setLocation(location);
        }
    }

    int getNumLiveBuiltIns(void) const { return (int)builtInsNameToIndex.size(); }
    int getBuiltInIndex(const char* name) const
    {
        TNameToIndex::const_iterator it = builtInsNameToIndex.find(name);
        if (it == builtInsNameToIndex.end())
            return -1;
        else
            return it->second;
    }

    const TQualifier* getBuiltInQualifier(int index) const
    {
        if (index >= 0 && index < (int)builtInsQualifiers.size())
            return builtInsQualifiers[index];
        else
            return &badQualifier;
    }

    const TObjectReflection& getBuiltIn(int i) const
    {
        if (i >= 0 && i < (int)indexToBuiltin.size())
            return indexToBuiltin[i];
        else
            return badReflection;
    }

    // see getIndex(const char*)
    int getIndex(const TString& name) const { return getIndex(name.c_str()); }

    // Thread local size
    unsigned getLocalSize(int dim) const { return dim <= 2 ? localSize[dim] : 0; }

    int getNumLiveFunctions(void) { return (int)liveFunctions.size(); }
    const char* getFunctionName(int index) { return liveFunctions[index].c_str(); }

    void dump();

protected:
    friend class glslang::TReflectionTraverser;

    void buildCounterIndices(const TIntermediate&);
    void buildAttributeReflection(EShLanguage, const TIntermediate&);

    // Need a TString hash: typedef std::unordered_map<TString, int> TNameToIndex;
    typedef std::map<TString, int> TNameToIndex;
    typedef std::vector<TObjectReflection> TMapIndexToReflection;

    TObjectReflection badReflection; // return for queries of -1 or generally out of range; has expected descriptions with in it for this
    TNameToIndex nameToIndex;        // maps names to indexes; can hold all types of data: uniform/buffer and which function names have been processed
    TMapIndexToReflection indexToUniform;
    TMapIndexToReflection indexToUniformBlock;
    TMapIndexToReflection indexToAttribute;

    unsigned int localSize[3];

    TQualifier                      badQualifier;

    std::vector<EShLanguageMask>    uniformStages;
    std::vector<const TQualifier *> uniformQualifiers;

    std::vector<int>                attributeIndices;

    TNameToIndex                    varyingInNameToIndex;
    TMapIndexToReflection           indexToVaryingIn;
    std::vector<const TQualifier *> varyingInQualifiers;

    TNameToIndex                    varyingOutNameToIndex;
    TMapIndexToReflection           indexToVaryingOut;
    std::vector<const TQualifier *> varyingOutQualifiers;

    TNameToIndex                    builtInsNameToIndex;
    TMapIndexToReflection           indexToBuiltin;
    std::vector<const TQualifier *> builtInsQualifiers;

    std::vector<TString>            liveFunctions;
};

} // end namespace glslang

#endif // _REFLECTION_INCLUDED
