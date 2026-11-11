#version 460
#extension GL_EXT_ray_tracing : enable
#extension GL_EXT_shader_invocation_reorder : enable
#extension GL_EXT_ray_tracing_position_fetch : enable
layout(binding = 0) buffer block {
	vec3 op;
};
void main()
{
	hitObjectEXT hObj;
	hitObjectRecordEmptyEXT(hObj);
	vec3 positions[3];
	hitObjectGetIntersectionTriangleVertexPositionsEXT(hObj, positions);
	op = positions[0] + positions[1] + positions[2];
}
