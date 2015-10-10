#version 400

uniform sampler s;
uniform sampler sA[4];
uniform texture2D t2d;
uniform texture3D t3d[4];
uniform int i;

sampler2D s2D = sampler2D(t2d, s);
sampler3D s3d[4] = sampler3D[4](t3d, sA[2]);

out vec4 color;

void main()
{
    color = texture(s2D, vec2(0.5));
    color += texture(s3d[i], vec3(0.5));
    color += texture(sampler2D(t2d, s), vec2(0.5));
}
