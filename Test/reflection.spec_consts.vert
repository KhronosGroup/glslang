#version 440 core

layout(constant_id = 0) const float constDeadFloat = 1.0;
layout(constant_id = 1) const float constLiveFloat = 2.0;
layout(constant_id = 2) const int constLiveInt1 = -1;
layout(constant_id = 3) const int constLiveInt2 = -1;
layout(constant_id = 4) const int constLiveIndirect = -1;

layout(constant_id = 5) const int constLiveArrayDimension1 = 1;
layout(constant_id = 6) const int constLiveArrayDimension2 = 1;
layout(constant_id = 7) const int constLiveArrayDimension3 = 1;
layout(constant_id = 8) const int constLiveArrayDimension4 = 1;
layout(constant_id = 9) const int constLiveArrayDimension5 = 1;
layout(constant_id = 10) const int constLiveArrayDimension6 = 1;
layout(constant_id = 11) const int constLiveIndirectArrayDimension = 1;
layout(constant_id = 12) const int constDeadArrayDimension = 1;

const uint someConst1 = uint(constLiveIndirect + 1);
const uint someConst2 = uint(constLiveIndirectArrayDimension);

layout(binding = 1, std140) uniform uniformBlock1 {
	vec3 liveUniform1[constLiveArrayDimension1];
};

layout(binding = 2, std140) uniform uniformBlock2 {
	vec3 liveUniform2[constLiveArrayDimension2][2];
};

layout(binding = 3, std140) uniform uniformBlock3 {
	vec3 liveUniform3[1 + uint(constLiveArrayDimension3)][2];
};

layout(binding = 4, std140) uniform uniformBlock4 {
	vec3 liveUniform4[constLiveArrayDimension4 + 2 + constLiveArrayDimension5];
};

layout(binding = 5, std140) uniform uniformBlock5 {
	vec3 liveUniform5[someConst2];
};

layout(binding = 6, std140) uniform uniformBlock6 {
	vec3 deadUniform6[constDeadArrayDimension];
};

layout(location = 0) out vec3 outLive[constLiveArrayDimension6 + 1];

vec3 deadFunction(float f)
{
    return vec3(constDeadFloat * f);
}

vec3 liveFunction(float f)
{
    return vec3(constLiveFloat * f);
}

vec3 liveFunction2()
{
	return vec3(constLiveInt1);
}

void main()
{
    vec3 v3 = vec3(0.0);

	v3 += liveFunction(1.0);

	if (constLiveInt2 == 0)
		v3 += liveFunction2();

	if (false)
		v3 += deadFunction(1.0);

	v3 += vec3(1 + someConst1 + 1);

	v3 += liveUniform1[gl_VertexIndex];
	v3 += liveUniform2[gl_VertexIndex][gl_InstanceIndex];
	v3 += liveUniform3[gl_VertexIndex][gl_InstanceIndex];
	v3 += liveUniform4[gl_VertexIndex];
	v3 += liveUniform5[gl_VertexIndex];

	if (false)
		v3 += deadUniform6[gl_VertexIndex];

    gl_Position = vec4(v3, 1.0);
	outLive[0] = v3;
}
