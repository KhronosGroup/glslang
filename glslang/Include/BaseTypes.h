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

#ifndef _BASICTYPES_INCLUDED_
#define _BASICTYPES_INCLUDED_

namespace glslang {

//
// Basic type.  Arrays, vectors, sampler details, etc., are orthogonal to this.
//
enum TBasicType {
    EbtVoid,
    EbtFloat,
    EbtDouble,
    EbtInt,
    EbtUint,
    EbtBool,
    EbtSampler,
    EbtStruct,
    EbtBlock,
    EbtNumTypes
};

//
// Qualifiers and built-ins.  These are mainly used to see what can be read
// or written, and by the machine dependent translator to know which registers
// to allocate variables in.  Since built-ins tend to go to different registers
// than varying or uniform, it makes sense they are peers, not sub-classes.
//
enum TStorageQualifier {
    EvqTemporary,     // For temporaries (within a function), read/write
    EvqGlobal,        // For globals read/write
    EvqConst,         // User-defined constant values, will be semantically constant and constant folded
    EvqVaryingIn,     // pipeline input, read only
    EvqVaryingOut,    // pipeline ouput, read/write
    EvqUniform,       // read only, shader with app
    EvqBuffer,        // read only, shader with app
    
    // parameters
    EvqIn,            // also, for 'in' in the grammar before we know if it's a pipeline input or an 'in' parameter
    EvqOut,           // also, for 'out' in the grammar before we know if it's a pipeline output or an 'out' parameter
    EvqInOut,

    EvqConstReadOnly, // read-only types, not having a constant value or constant-value semantics

    // built-ins read by vertex shader
    EvqVertexId,
    EvqInstanceId,

    // built-ins written by vertex shader
    EvqPosition,
    EvqPointSize,
    EvqClipVertex,

    // built-ins read by fragment shader
    EvqFace,
    EvqFragCoord,
    EvqPointCoord,

    // built-ins written by fragment shader
    EvqFragColor,
    EvqFragDepth,

    // end of list
    EvqLast,
};

// These will show up in error messages
__inline const char* GetStorageQualifierString(TStorageQualifier q) 
{
    switch (q) {
    case EvqTemporary:      return "temporary";      break;
    case EvqGlobal:         return "global";         break;
    case EvqConst:          return "const";          break;
    case EvqConstReadOnly:  return "const (read only)"; break;
    case EvqVaryingIn:      return "in";             break;
    case EvqVaryingOut:     return "out";            break;
    case EvqUniform:        return "uniform";        break;
    case EvqIn:             return "in";             break;
    case EvqOut:            return "out";            break;
    case EvqInOut:          return "inout";          break;
    case EvqVertexId:       return "gl_VertexId";    break;
    case EvqInstanceId:     return "gl_InstanceId";  break;
    case EvqPosition:       return "gl_Position";    break;
    case EvqPointSize:      return "gl_PointSize";   break;
    case EvqClipVertex:     return "gl_ClipVertex";  break;
    case EvqFace:           return "gl_FrontFacing"; break;
    case EvqFragCoord:      return "gl_FragCoord";   break;
    case EvqPointCoord:     return "gl_PointCoord";  break;
    case EvqFragColor:      return "fragColor";      break;
    case EvqFragDepth:      return "gl_FragDepth";   break;
    default:                return "unknown qualifier";
    }
}

// In this enum, order matters; users can assume higher precision is a bigger value
// and EpqNone is 0.
enum TPrecisionQualifier {
    EpqNone = 0,
    EpqLow,
    EpqMedium,
    EpqHigh
};

__inline const char* GetPrecisionQualifierString(TPrecisionQualifier p)
{
    switch(p) {
    case EpqNone:   return "";        break;
    case EpqLow:    return "lowp";    break;
    case EpqMedium: return "mediump"; break;
    case EpqHigh:   return "highp";   break;
    default:        return "unknown precision qualifier";
    }
}

} // end namespace glslang

#endif // _BASICTYPES_INCLUDED_
