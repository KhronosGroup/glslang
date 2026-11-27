#version 460 core
#extension GL_EXT_ray_tracing : require
#extension GL_AMDX_multi_level_acceleration_structure : require

#if GL_AMDX_multi_level_acceleration_structure != 1
#error GL_AMDX_multi_level_acceleration_structure must be defined as 1
#endif

layout(location = 0) rayPayloadInEXT vec4 result;

void main()
{
    uint count = gl_HitInstanceLevelAMDX;
    int customIndex = getInstanceCustomIndexAtLevelAMDX(0u);
    int instanceId = getInstanceIdAtLevelAMDX(0u);
    mat4x3 objectToWorld = getObjectToWorldAtLevelAMDX(0u);
    mat4x3 worldToObject = getWorldToObjectAtLevelAMDX(0u);
    mat3x4 transposed = transpose(objectToWorld);
    result = vec4(float(count), float(customIndex), float(instanceId),
                  worldToObject[3].x + transposed[0].w);

    for (uint level = 0u; level < count; ++level) {
        result.y += float(getInstanceCustomIndexAtLevelAMDX(level));
        result.z += float(getInstanceIdAtLevelAMDX(level));
        result.w += getObjectToWorldAtLevelAMDX(level)[3].x + getWorldToObjectAtLevelAMDX(level)[3].x;
    }

    result.y += float(gl_InstanceCustomIndexEXT);
    result.z += float(gl_InstanceID);
    result.w += gl_ObjectToWorldEXT[3].x + gl_WorldToObjectEXT[3].x;
}
