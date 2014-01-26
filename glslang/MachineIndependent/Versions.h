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
#ifndef _VERSIONS_INCLUDED_
#define _VERSIONS_INCLUDED_

//
// Help manage multiple profiles, versions, extensions etc.
//

//
// Profiles are set up for masking operations, so queries can be done on multiple
// profiles at the same time.
//
// Don't maintain an ordinal set of enums (0,1,2,3...) to avoid all possible
// defects from mixing the two different forms.
//
typedef enum {
    EBadProfile           = 0,
    ENoProfile            = (1 << 0), // only for desktop, before profiles showed up
    ECoreProfile          = (1 << 1),
    ECompatibilityProfile = (1 << 2),
    EEsProfile            = (1 << 3)
} EProfile;

namespace glslang {

//
// The behaviors from the GLSL "#extension extension_name : behavior"
//
typedef enum {
    EBhMissing = 0,
    EBhRequire,
    EBhEnable,
    EBhWarn,
    EBhDisable,
    EBhDisablePartial    // use as initial state of an extension that is only partially implemented
} TExtensionBehavior;

//
// Symbolic names for extensions.  Strings may be directly used when calling the
// functions, but better to have the compiler do spelling checks.
//
const char* const GL_OES_texture_3D               = "GL_OES_texture_3D";
const char* const GL_OES_standard_derivatives     = "GL_OES_standard_derivatives";
const char* const GL_EXT_frag_depth               = "GL_EXT_frag_depth";
const char* const GL_OES_EGL_image_external       = "GL_OES_EGL_image_external";
const char* const GL_EXT_shader_texture_lod       = "GL_EXT_shader_texture_lod";

const char* const GL_ARB_texture_rectangle        = "GL_ARB_texture_rectangle";
const char* const GL_3DL_array_objects            = "GL_3DL_array_objects";
const char* const GL_ARB_shading_language_420pack = "GL_ARB_shading_language_420pack";
const char* const GL_ARB_texture_gather           = "GL_ARB_texture_gather";
const char* const GL_ARB_gpu_shader5              = "GL_ARB_gpu_shader5";
const char* const GL_ARB_separate_shader_objects  = "GL_ARB_separate_shader_objects";
const char* const GL_ARB_tessellation_shader      = "GL_ARB_tessellation_shader";
const char* const GL_ARB_enhanced_layouts         = "GL_ARB_enhanced_layouts";
const char* const GL_ARB_texture_cube_map_array   = "GL_ARB_texture_cube_map_array";

} // end namespace glslang

#endif // _VERSIONS_INCLUDED_
