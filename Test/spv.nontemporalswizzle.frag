#version 460

#pragma use_vulkan_memory_model

#extension GL_EXT_nontemporal_keyword: require

// Reading a nontemporal value through a swizzle. The flag is carried on the
// access chain, and pushing the swizzle onto that chain must combine the two
// sets of flags rather than replace them. Both loads below must therefore
// carry the Nontemporal memory operand.
layout(binding=0) buffer nontemporal NONTEMPORAL_BLOCK {
    vec4 blk_in;
    vec2 blk_out;
};

layout(binding=1) buffer BLOCK_NONTEMPORAL {
    nontemporal vec4 mem_in;
    vec2 mem_out;
};

void main() {
    blk_out = blk_in.xy;
    mem_out = mem_in.zw;
}
