/**
BSD 2-Clause License

Copyright (c) 2019, Viktor Latypov
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**/

#ifndef C_SHADER_TYPES_H_INCLUDED
#define C_SHADER_TYPES_H_INCLUDED

/* EShLanguage counterpart */
typedef enum {
    SH_STAGE_VERTEX,
    SH_STAGE_TESSCONTROL,
    SH_STAGE_TESSEVALUATION,
    SH_STAGE_GEOMETRY,
    SH_STAGE_FRAGMENT,
    SH_STAGE_COMPUTE,
    SH_STAGE_RAYGEN_NV,
    SH_STAGE_INTERSECT_NV,
    SH_STAGE_ANYHIT_NV,
    SH_STAGE_CLOSESTHIT_NV,
    SH_STAGE_MISS_NV,
    SH_STAGE_CALLABLE_NV,
    SH_STAGE_TASK_NV,
    SH_STAGE_MESH_NV,
    SH_STAGE_COUNT,
} glslang_stage_t;         // would be better as stage, but this is ancient now

/* EShLanguageMask counterpart */
typedef enum {
    SH_STAGE_VERTEX_MASK          = (1 << SH_STAGE_VERTEX),
    SH_STAGE_TESSCONTROL_MASK     = (1 << SH_STAGE_TESSCONTROL),
    SH_STAGE_TESSEVALUATION_MASK  = (1 << SH_STAGE_TESSEVALUATION),
    SH_STAGE_GEOMETRY_MASK        = (1 << SH_STAGE_GEOMETRY),
    SH_STAGE_FRAGMENT_MASK        = (1 << SH_STAGE_FRAGMENT),
    SH_STAGE_COMPUTE_MASK         = (1 << SH_STAGE_COMPUTE),
    SH_STAGE_RAYGEN_NV_MASK       = (1 << SH_STAGE_RAYGEN_NV),
    SH_STAGE_INTERSECT_NV_MASK    = (1 << SH_STAGE_INTERSECT_NV),
    SH_STAGE_ANYHIT_NV_MASK       = (1 << SH_STAGE_ANYHIT_NV),
    SH_STAGE_CLOSESTHIT_NV_MASK   = (1 << SH_STAGE_CLOSESTHIT_NV),
    SH_STAGE_MISS_NV_MASK         = (1 << SH_STAGE_MISS_NV),
    SH_STAGE_CALLABLE_NV_MASK     = (1 << SH_STAGE_CALLABLE_NV),
    SH_STAGE_TASK_NV_MASK         = (1 << SH_STAGE_TASK_NV),
    SH_STAGE_MESH_NV_MASK         = (1 << SH_STAGE_MESH_NV),
} glslang_stage_mask_t;

/* EShSource counterpart */
typedef enum {
    SH_SOURCE_NONE,
    SH_SOURCE_GLSL,
    SH_SOURCE_HLSL,
} glslang_source_t;

/* EShClient counterpart */
typedef enum {
    SH_CLIENT_NONE,
    SH_CLIENT_VULKAN,
    SH_CLIENT_OPENGL,
} glslang_client_t;

/* EShTargetLanguage counterpart */
typedef enum {
    SH_TARGET_NONE,
    SH_TARGET_SPV,
} glslang_target_language_t;

/* SH_TARGET_ClientVersion counterpart */
typedef enum {
    SH_TARGET_VULKAN_1_0 = (1 << 22),
    SH_TARGET_VULKAN_1_1 = (1 << 22) | (1 << 12),
    SH_TARGET_OPENGL_450 = 450,
} glslang_target_client_version_t;

/* SH_TARGET_LanguageVersion counterpart */
typedef enum {
    SH_TARGET_SPV_1_0 = (1 << 16),
    SH_TARGET_SPV_1_1 = (1 << 16) | (1 << 8),
    SH_TARGET_SPV_1_2 = (1 << 16) | (2 << 8),
    SH_TARGET_SPV_1_3 = (1 << 16) | (3 << 8),
    SH_TARGET_SPV_1_4 = (1 << 16) | (4 << 8),
    SH_TARGET_SPV_1_5 = (1 << 16) | (5 << 8),
} glslang_target_language_version_t;

/* EShExecutable counterpart */
typedef enum {
    SH_EX_VERTEX_FRAGMENT,
    SH_EX_FRAGMENT
} glslang_executable_t;

/* EShOptimizationLevel counterpart  */
typedef enum {
    SH_OPT_NO_GENERATION,
    SH_OPT_NONE,
    SH_OPT_SIMPLE,
    SH_OPT_FULL,
} glslang_optimization_level_t;

/* EShTextureSamplerTransformMode counterpart */
typedef enum {
    SH_TEX_SAMP_TRANS_KEEP,
    SH_TEX_SAMP_TRANS_UPGRADE_TEXTURE_REMOVE_SAMPLER,
} glslang_texture_sampler_transform_mode_t;

/* EShMessages counterpart */
typedef enum {
    SH_MSG_DEFAULT                 = 0,
    SH_MSG_RELAXED_ERRORS          = (1 << 0),
    SH_MSG_SUPPRESS_WARNINGS       = (1 << 1),
    SH_MSG_AST                     = (1 << 2),
    SH_MSG_SPV_RULES               = (1 << 3),
    SH_MSG_VULKAN_RULES            = (1 << 4),
    SH_MSG_ONLY_PREPROCESSOR       = (1 << 5),
    SH_MSG_READ_HLSL               = (1 << 6),
    SH_MSG_CASCADING_ERRORS        = (1 << 7),
    SH_MSG_KEEP_UNCALLED           = (1 << 8),
    SH_MSG_HLSL_OFFSETS            = (1 << 9),
    SH_MSG_DEBUG_INFO              = (1 << 10),
    SH_MSG_HLSL_ENABLE_16BIT_TYPES = (1 << 11),
    SH_MSG_HLSL_LEGALIZATION       = (1 << 12),
    SH_MSG_HLSL_DX9_COMPATIBLE     = (1 << 13),
    SH_MSG_BUILTIN_SYMBOL_TABLE    = (1 << 14),
} glslang_messages_t;

/* EShReflectionOptions counterpart */
typedef enum
{
    SH_REFLECTION_DEFAULT             = 0,
    SH_REFLECTION_STRICT_ARRAY_SUFFIX = (1 << 0),
    SH_REFLECTION_BASIC_ARRAY_SUFFIX  = (1 << 1),
    SH_REFLECTION_INTERMEDIATE_IOO    = (1 << 2),
    SH_REFLECTION_SEPARATE_BUFFERS    = (1 << 3),
    SH_REFLECTION_ALL_BLOCK_VARIABLES = (1 << 4),
    SH_REFLECTION_UNWRAP_IO_BLOCKS    = (1 << 5),
} glslang_reflection_options_t;

/* EProfile counterpart (from Versions.h) */
typedef enum {
    SH_BAD_PROFILE           = 0,
    SH_NO_PROFILE            = (1 << 0),
    SH_CORE_PROFILE          = (1 << 1),
    SH_COMPATIBILITY_PROFILE = (1 << 2),
    SH_ES_PROFILE            = (1 << 3)
} glslang_profile_t;

#endif

