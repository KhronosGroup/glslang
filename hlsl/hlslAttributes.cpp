//
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

#include "hlslAttributes.h"
#include <cstdlib>
#include <cctype>
#include <algorithm>

namespace glslang {
    // Map the given string to an attribute enum from TAttributeType,
    // or EatNone if invalid.
    TAttributeType TAttributeMap::attributeFromName(const TString& nameSpace, const TString& name)
    {
        // These are case insensitive.
        TString lowername(name);
        std::transform(lowername.begin(), lowername.end(), lowername.begin(), ::tolower);
        TString lowernameSpace(nameSpace);
        std::transform(lowernameSpace.begin(), lowernameSpace.end(), lowernameSpace.begin(), ::tolower);

        // handle names within a namespace

        if (lowernameSpace == "vk") {
            if (lowername == "input_attachment_index")
                return EatInputAttachment;
            else if (lowername == "location")
                return EatLocation;
            else if (lowername == "binding")
                return EatBinding;
            else if (lowername == "global_cbuffer_binding")
                return EatGlobalBinding;
        } else if (lowernameSpace.size() > 0)
            return EatNone;

        // handle names with no namespace

        if (lowername == "allow_uav_condition")
            return EatAllow_uav_condition;
        else if (lowername == "branch")
            return EatBranch;
        else if (lowername == "call")
            return EatCall;
        else if (lowername == "domain")
            return EatDomain;
        else if (lowername == "earlydepthstencil")
            return EatEarlyDepthStencil;
        else if (lowername == "fastopt")
            return EatFastOpt;
        else if (lowername == "flatten")
            return EatFlatten;
        else if (lowername == "forcecase")
            return EatForceCase;
        else if (lowername == "instance")
            return EatInstance;
        else if (lowername == "maxtessfactor")
            return EatMaxTessFactor;
        else if (lowername == "maxvertexcount")
            return EatMaxVertexCount;
        else if (lowername == "numthreads")
            return EatNumThreads;
        else if (lowername == "outputcontrolpoints")
            return EatOutputControlPoints;
        else if (lowername == "outputtopology")
            return EatOutputTopology;
        else if (lowername == "partitioning")
            return EatPartitioning;
        else if (lowername == "patchconstantfunc")
            return EatPatchConstantFunc;
        else if (lowername == "unroll")
            return EatUnroll;
        else if (lowername == "loop")
            return EatLoop;
        else
            return EatNone;
    }

    // Look up entry, inserting if it's not there, and if name is a valid attribute name
    // as known by attributeFromName.
    TAttributeType TAttributeMap::setAttribute(const TString& nameSpace, const TString* name, TIntermAggregate* value)
    {
        if (name == nullptr)
            return EatNone;

        const TAttributeType attr = attributeFromName(nameSpace, *name);

        if (attr != EatNone)
            attributes[attr] = value;

        return attr;
    }

    // Look up entry (const version), and return aggregate node.  This cannot change the map.
    const TIntermAggregate* TAttributeMap::operator[](TAttributeType attr) const
    {
        const auto entry = attributes.find(attr);

        return (entry == attributes.end()) ? nullptr : entry->second;
    }

    // True if entry exists in map (even if value is nullptr)
    bool TAttributeMap::contains(TAttributeType attr) const
    {
        return attributes.find(attr) != attributes.end();
    }

    // extract integers out of attribute arguments stored in attribute aggregate
    bool TAttributeMap::getInt(TAttributeType attr, int& value, int argNum) const 
    {
        const TConstUnion* intConst = getConstUnion(attr, EbtInt, argNum);

        if (intConst == nullptr)
            return false;

        value = intConst->getIConst();
        return true;
    };

    // extract strings out of attribute arguments stored in attribute aggregate.
    // convert to lower case if converToLower is true (for case-insensitive compare convenience)
    bool TAttributeMap::getString(TAttributeType attr, TString& value, int argNum, bool convertToLower) const 
    {
        const TConstUnion* stringConst = getConstUnion(attr, EbtString, argNum);

        if (stringConst == nullptr)
            return false;

        value = *stringConst->getSConst();

        // Convenience.
        if (convertToLower)
            std::transform(value.begin(), value.end(), value.begin(), ::tolower);

        return true;
    };

    // Helper to get attribute const union.  Returns nullptr on failure.
    const TConstUnion* TAttributeMap::getConstUnion(TAttributeType attr, TBasicType basicType, int argNum) const
    {
        const TIntermAggregate* attrAgg = (*this)[attr];
        if (attrAgg == nullptr)
            return nullptr;

        if (argNum >= int(attrAgg->getSequence().size()))
            return nullptr;

        const TConstUnion* constVal = &attrAgg->getSequence()[argNum]->getAsConstantUnion()->getConstArray()[0];
        if (constVal == nullptr || constVal->getType() != basicType)
            return nullptr;
        
        return constVal;
    }

} // end namespace glslang
