#version 460 core
#extension GL_EXT_ray_tracing : require
#extension GL_EXT_spirv_intrinsics : require

spirv_decorate(extensions = ["SPV_AMDX_multi_level_acceleration_structure"], capabilities = [5191], 11, 5190)
in uint hitInstanceLevelAMDX;

spirv_instruction(extensions = ["SPV_AMDX_multi_level_acceleration_structure"], capabilities = [5191], id = 5193)
uint getInstanceCustomIndexAtLevelAMDX(uint level);
spirv_instruction(extensions = ["SPV_AMDX_multi_level_acceleration_structure"], capabilities = [5191], id = 5194)
uint getInstanceIdAtLevelAMDX(uint level);
spirv_instruction(extensions = ["SPV_AMDX_multi_level_acceleration_structure"], capabilities = [5191], id = 5195)
mat4x3 getObjectToWorldAtLevelAMDX(uint level);
spirv_instruction(extensions = ["SPV_AMDX_multi_level_acceleration_structure"], capabilities = [5191], id = 5196)
mat4x3 getWorldToObjectAtLevelAMDX(uint level);

layout(location = 0) rayPayloadInEXT vec4 result;

void main()
{
    result.x = float(hitInstanceLevelAMDX);
    result.y = float(getInstanceCustomIndexAtLevelAMDX(0u));
    result.z = float(getInstanceIdAtLevelAMDX(0u));
    result.w = getObjectToWorldAtLevelAMDX(0u)[3].x + getWorldToObjectAtLevelAMDX(0u)[3].x;

    for (uint level = 0u; level < hitInstanceLevelAMDX; ++level) {
        result.y += float(getInstanceCustomIndexAtLevelAMDX(level));
        result.z += float(getInstanceIdAtLevelAMDX(level));
        result.w += getObjectToWorldAtLevelAMDX(level)[3].x + getWorldToObjectAtLevelAMDX(level)[3].x;
    }
}
