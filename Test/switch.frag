#version 300 es

uniform int c, d;
in highp float x;

void main()
{
    float f;
    int a[2];

    switch(f) { // ERROR
    }

    switch(a) { // ERROR
    }

    switch(c)
    {
    }

    switch(c)
    {
    case 2:    // ERROR, not enough stuff
    }

    switch(c)
    {
        f = sin(x); // ERRROR
    case 2:    // ERROR, not enough stuff
        f = cos(x);
        break;
    }

    switch (c) {
    case 1:
        f = sin(x);
        break;
    case 2:
        f = cos(x);
        break;
    default:
        f = tan(x);
    }

    switch (c) {
    case 1:
        f = sin(x);
        break;
    case 2:
        switch (d) {
        case 1:
            f = x * x * x;
            break;
        case 2:
            f = x * x;
            break;
        }
        break;
    default:
        f = tan(x);
    }

    break; // ERROR
}
