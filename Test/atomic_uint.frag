#version 420 core

layout(binding = 0) uniform atomic_uint counter;

uint func(atomic_uint c)
{
    return atomicCounterIncrement(c);
}

uint func2(out atomic_uint c) // ERROR
{
    return counter;
}

void main()
{
     atomic_uint non_uniform_counter; // ERROR
     uint val = atomicCounter(counter);
     atomicCounterDecrement(counter);
}
