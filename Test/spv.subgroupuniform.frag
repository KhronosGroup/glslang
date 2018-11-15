#version 450

#extension GL_EXT_subgroupuniform_qualifier : enable

layout(location=0) subgroupuniformEXT in vec4 su_inv4;
subgroupuniformEXT float su_gf;
layout(location=1) in subgroupuniformEXT flat int su_ii;

layout(binding=0, input_attachment_index = 0) uniform subpassInput        inputAttachmentDyn[];
layout(binding=1)                             uniform samplerBuffer       uniformTexelBufferDyn[];
layout(binding=2, r32f)                       uniform imageBuffer         storageTexelBufferDyn[];
layout(binding=3)                             uniform uname { float a; }  uniformBuffer[];
layout(binding=4)                             buffer  bname { float b; }  storageBuffer[];
layout(binding=5)                             uniform sampler2D           sampledImage[];
layout(binding=6, r32f)                       uniform image2D             storageImage[];
layout(binding=7, input_attachment_index = 1) uniform subpassInput        inputAttachment[];
layout(binding=8)                             uniform samplerBuffer       uniformTexelBuffer[];
layout(binding=9, r32f)                       uniform imageBuffer         storageTexelBuffer[];

subgroupuniformEXT int foo(subgroupuniformEXT int nupi, subgroupuniformEXT out int f)
{
    return nupi;
}

void main()
{
    subgroupuniformEXT int su_li;
    int dyn_i;

    int a = foo(su_li, su_li);
    su_li = subgroupuniformEXT(a) + subgroupuniformEXT(a * 2);

    float b;
    b = su_inv4.x * su_gf;

    subgroupuniformEXT vec4 v;
    subgroupuniformEXT mat4 m;
    subgroupuniformEXT struct S { int a; } s;
    ivec4 uv;

    vec4 implicitlySubgroupuniform = m * v;

    // Although in SPIR-V the above's SSA node will be implicitly subgroup
    // uniform, because its type is not qualified it won't propagate its
    // uniformity further
    vec4 loseImplicitlySubgroupuniform = implicitlySubgroupuniform * 4.0f;

    // Check there is a warning for initializing something with unknown
    // uniformity to a subgroup uniform variable
    subgroupuniformEXT vec4 gainingUniformity = loseImplicitlySubgroupuniform;

    // Check that there is a warning on assignment too
    gainingUniformity = loseImplicitlySubgroupuniform;

    // But there is no warning for initializing a constant
    subgroupuniformEXT vec4 initializingFromConstant = vec4(4.0f);

    // Check there is no warning on assignment too
    initializingFromConstant = vec4(4.0f);
}
