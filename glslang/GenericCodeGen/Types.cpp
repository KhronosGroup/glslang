
//
//Copyright (C) 2002-2005  3Dlabs Inc. Ltd.
//Copyright (C) 2012-2016 LunarG, Inc.
//Copyright (C) 2015-2016 Google, Inc.
//Copyright (C) 2016 Oxide Games
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

#include "../Include/Types.h"

namespace glslang {

void TSampler::deepCopy(const TSampler& copyOf)
{
    if (copyOf.samplerType != nullptr)
    {
        samplerType = new TType;
        samplerType->deepCopy(*copyOf.samplerType);
    }
    else
        samplerType = nullptr;

    dim = copyOf.dim;;
    arrayed = copyOf.arrayed;
    shadow = copyOf.shadow;
    ms = copyOf.ms;
    image = copyOf.image;
    combined = copyOf.combined;
    sampler = copyOf.sampler;
    external = copyOf.external;
}

TBasicType TSampler::getBasicType() const
{
    if (samplerType == nullptr)
        return EbtVoid;
    else
        return samplerType->getBasicType();

}

void TSampler::clear()
{
    samplerType = nullptr;
    dim = EsdNone;
    arrayed = false;
    shadow = false;
    ms = false;
    image = false;
    combined = false;
    sampler = false;
    external = false;
}

// make a combined sampler and texture, basic type
void TSampler::set(TBasicType t, TSamplerDim d, bool a , bool s , bool m )
{
    clear();
    samplerType = new TType(t);
    dim = d;
    arrayed = a;
    shadow = s;
    ms = m;
    combined = true;
}

// make a combined sampler and texture
void  TSampler::set(TType *t, TSamplerDim d, bool a, bool s, bool m)
{
    clear();
    samplerType = t;
    dim = d;
    arrayed = a;
    shadow = s;
    ms = m;
    combined = true;
}

// make an image
void  TSampler::setImage(TType *t, TSamplerDim d, bool a , bool s, bool m)
{
    clear();
    samplerType = t;
    dim = d;
    arrayed = a;
    shadow = s;
    ms = m;
    image = true;
}


// make an image, basic type
void  TSampler::setImage(TBasicType t, TSamplerDim d, bool a, bool s, bool m)
{
    clear();
    samplerType = new TType(t);
    dim = d;
    arrayed = a;
    shadow = s;
    ms = m;
    image = true;
}

// make a texture with no sampler
void  TSampler::setTexture(TType *t, TSamplerDim d, bool a, bool s , bool m )
{
    clear();
    samplerType = t;
    dim = d;
    arrayed = a;
    shadow = s;
    ms = m;
}

// make a texture with no sampler, basic type
void  TSampler::setTexture(TBasicType t, TSamplerDim d, bool a, bool s, bool m)
{
    clear();
    samplerType = new TType(t);
    dim = d;
    arrayed = a;
    shadow = s;
    ms = m;
}


// make a subpass input attachment
void  TSampler::setSubpass(TType *t, bool m)
{
    clear();
    samplerType = t;
    image = true;
    dim = EsdSubpass;
    ms = m;
}

// make a subpass input attachment, basic type
void  TSampler::setSubpass(TBasicType t, bool m)
{
    clear();
    samplerType = new TType(t);
    image = true;
    dim = EsdSubpass;
    ms = m;
}

// make a pure sampler, no texture, no image, nothing combined, the 'sampler' keyword
void  TSampler::setPureSampler(bool s)
{
    clear();
    sampler = true;
    shadow = s;
}

bool  TSampler::operator==(const TSampler& right) const
{
    bool bTypesEqual = true;
    if (samplerType == nullptr && right.samplerType != nullptr)
        bTypesEqual = false;
    else if (samplerType != nullptr && right.samplerType == nullptr )
        bTypesEqual = false;
    //For now, just check if there base types match, there appear to be cases where the some of the intrinsic functions have type info
    //in them that don't need to, like GetDimensions. Perhaps a baseless type is needed.
    else if(samplerType != nullptr && right.samplerType != nullptr )
        bTypesEqual = (samplerType->getBasicType() == right.samplerType->getBasicType());

    return bTypesEqual &&
        dim == right.dim &&
        arrayed == right.arrayed &&
        shadow == right.shadow &&
        ms == right.ms &&
        image == right.image &&
        combined == right.combined &&
        sampler == right.sampler &&
        external == right.external;
}

bool  TSampler::operator!=(const TSampler& right) const
{
    return !operator==(right);
}

TString  TSampler::getString() const
{
    TString s;

    if (sampler) {
        s.append("sampler");
        return s;
    }

    switch (samplerType->getBasicType()) {
    case EbtFloat:               break;
    case EbtInt:  s.append("i"); break;
    case EbtUint: s.append("u"); break;
    case EbtInt64:  s.append("i64"); break;
    case EbtUint64: s.append("u64"); break;
    default:  break;  // some compilers want this
    }
    if (image) {
        if (dim == EsdSubpass)
            s.append("subpass");
        else
            s.append("image");
    }
    else if (combined) {
        s.append("sampler");
    }
    else {
        s.append("texture");
    }
    if (external) {
        s.append("ExternalOES");
        return s;
    }
    switch (dim) {
    case Esd1D:      s.append("1D");      break;
    case Esd2D:      s.append("2D");      break;
    case Esd3D:      s.append("3D");      break;
    case EsdCube:    s.append("Cube");    break;
    case EsdRect:    s.append("2DRect");  break;
    case EsdBuffer:  s.append("Buffer");  break;
    case EsdSubpass: s.append("Input"); break;
    default:  break;  // some compilers want this
    }
    if (ms)
        s.append("MS");
    if (arrayed)
        s.append("Array");
    if (shadow)
        s.append("Shadow");

    return s;
}
}