#version 450

uniform sampler s;
uniform sampler sA[4];
uniform texture2D t2d;
uniform texture3D t3d[4];
uniform int i;

sampler2D s2Db1 = sampler2D(t2d);       // ERROR, need 2 args
sampler2D s2Db2 = sampler2D(s, s);      // ERROR, wrong type
sampler2D s2Db3 = sampler2D(i, i);      // ERROR, wrong type
sampler2D s2Db4 = sampler2D(t2d, i);    // ERROR, wrong type
sampler2D s2Db5 = sampler2D(t2d, t2d);  // ERROR, wrong type
sampler2D s2Db6 = sampler2D(t2d, sA);   // ERROR, wrong type

sampler3D s3Db1 = sampler2D(t2d, s);              // ERROR, can't convert
uniform texture3D t3d5[5];
sampler3D s3d[4] = sampler3D[4](t3d5, sA[2]);     // ERROR, array size mismatch
writeonly uniform image2D i2d;
sampler2D s2Db7 = sampler2D(i2d, s);              // ERROR, image instead of texture
sampler2D s2Db8 = sampler2D(t3d[1], s);           // ERROR, 3D not 2D
sampler3D s3db1[4] = sampler3D[5](t3d5, sA[2]);   // ERROR, array size mismatch
sampler3D s3db2[4] = sampler3D[4](t3d[1], sA[2]); // ERROR, array/scalar mismatch

sampler2D s2D = sampler2D(t2d, s);
sampler3D s3d[4] = sampler3D[4](t3d, sA[2]);

out vec4 color;

void main()
{
    color = texture(s2D, vec2(0.5));
    color += texture(s3d[i], vec3(0.5));
}
