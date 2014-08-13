#version 420 core

layout(binding = 0) uniform atomic_uint counter;

uint func(atomic_uint c)
{
    return atomicCounterIncrement(c);
}

uint func2(out atomic_uint c) // ERROR
{
    return counter;           // ERROR, type mismatch
    return atomicCounter(counter);
}

void main()
{
     atomic_uint non_uniform_counter; // ERROR
     uint val = atomicCounter(counter);
     atomicCounterDecrement(counter);
}

layout(binding = 1, offset = 3) uniform atomic_uint countArr[4];
uniform int i;

void opac()
{
    counter + counter;  // ERROR
    -counter;           // ERROR
    int a[3];
    a[counter];         // ERROR
    countArr[2];
    countArr[i];
    counter = 4;        // ERROR
}

in atomic_uint acin;    // ERROR
atomic_uint acg;        // ERROR

