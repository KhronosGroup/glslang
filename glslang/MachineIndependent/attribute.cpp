//
// Copyright (C) 2017 LunarG, Inc.
// Copyright (C) 2018 Google, Inc.
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

#include "attribute.h"
#include "../Include/intermediate.h"
#include "ParseHelper.h"

namespace glslang {

    // extract integers out of attribute arguments stored in attribute aggregate
    bool TAttributeArgs::getInt(int& value, int argNum) const 
    {
        const TConstUnion* intConst = getConstUnion(EbtInt, argNum);

        if (intConst == nullptr)
            return false;

        value = intConst->getIConst();
        return true;
    };

    // extract strings out of attribute arguments stored in attribute aggregate.
    // convert to lower case if converToLower is true (for case-insensitive compare convenience)
    bool TAttributeArgs::getString(TString& value, int argNum, bool convertToLower) const 
    {
        const TConstUnion* stringConst = getConstUnion(EbtString, argNum);

        if (stringConst == nullptr)
            return false;

        value = *stringConst->getSConst();

        // Convenience.
        if (convertToLower)
            std::transform(value.begin(), value.end(), value.begin(), ::tolower);

        return true;
    };

    // Helper to get attribute const union.  Returns nullptr on failure.
    const TConstUnion* TAttributeArgs::getConstUnion(TBasicType basicType, int argNum) const
    {
        if (argNum >= args->getSequence().size())
            return nullptr;

        const TConstUnion* constVal = &args->getSequence()[argNum]->getAsConstantUnion()->getConstArray()[0];
        if (constVal == nullptr || constVal->getType() != basicType)
            return nullptr;

        return constVal;
    }

} // end namespace glslang
