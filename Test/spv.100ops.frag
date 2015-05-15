#version 100

lowp float foo();

uniform int low, high;

lowp float face1 = 11.0;

void main()
{
    int z = 3;

    if (2 * low + 1 < high)
        ++z;

    gl_FragColor = face1 * vec4(z) + foo();
}

lowp float face2 = -2.0;

lowp float foo()
{
    // testing if face2 initializer insert logic is correct in main
    return face2;
}
