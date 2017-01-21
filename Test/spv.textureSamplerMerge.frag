#version 400

uniform sampler smp1;
uniform texture2D tex1;

uniform samplerShadow smp2;
uniform texture2D tex2;

uniform sampler smp3[2];
uniform texture2D tex3[2];

in vec2 coord;
in float cmp;

vec4 test1(texture2D t, sampler s, vec2 c)
{
  return texture(sampler2D(t, s), c);
}

void main()
{
  vec4 color = texture(sampler2D(tex3[0], smp3[1]), coord);
  color += texture(sampler2D(tex3[1], smp3[0]), coord);
  gl_FragColor = test1(tex1, smp1, coord) * vec4(texture(sampler2DShadow(tex2, smp2), vec3(coord, cmp)));
}