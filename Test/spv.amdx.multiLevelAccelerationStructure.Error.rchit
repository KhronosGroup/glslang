#version 460 core
#extension GL_EXT_ray_tracing : require

layout(location = 0) rayPayloadInEXT vec4 result;

void extensionDisabled()
{
    result.x = float(gl_HitInstanceLevelAMDX); // ERROR: MLAS extension disabled
    result.y = float(getInstanceCustomIndexAtLevelAMDX(0u)); // ERROR
    result.z = float(getInstanceIdAtLevelAMDX(0u)); // ERROR
    result.w = getObjectToWorldAtLevelAMDX(0u)[3].x; // ERROR
    result.w = getWorldToObjectAtLevelAMDX(0u)[3].x; // ERROR
}

#extension GL_AMDX_multi_level_acceleration_structure : require

void readOnlyBuiltin()
{
    gl_HitInstanceLevelAMDX = 1u; // ERROR: read-only input
}

#extension GL_EXT_ray_tracing : disable

void baseExtensionDisabled()
{
    uint count = gl_HitInstanceLevelAMDX; // ERROR: ray tracing extension disabled
    int customIndex = getInstanceCustomIndexAtLevelAMDX(0u); // ERROR
    int instanceId = getInstanceIdAtLevelAMDX(0u); // ERROR
    mat4x3 objectToWorld = getObjectToWorldAtLevelAMDX(0u); // ERROR
    mat4x3 worldToObject = getWorldToObjectAtLevelAMDX(0u); // ERROR
}

void main() {}
