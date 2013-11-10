#define ON1
#define ON2

float sum = 0.0;

void main()
{
#if defined(ON1) && (defined(OFF) || defined(ON2))
//yes
    sum += 1.0;
#endif

#if !defined(ON1) || (defined(OFF) || (!defined(OFF2) && defined(ON2)))
//yes
    sum += 20.0;
#endif

#if defined(ON1) && (defined(OFF) || !defined(ON2))
//no
    sum += 0.1;
#endif

#if !defined(ON1) || (defined(OFF) || !defined(OFF2) && !defined(ON2))
//no
    sum += 0.2;
#endif

#if !defined(ON1) || !defined(OFF) || defined(ON2) && defined(OFF2)
//yes
    sum += 300.0;
#endif

#if (!defined(ON1) || !defined(OFF) || defined(ON2)) && defined(OFF2)
//no
    sum += 0.4;
#endif

// sum should be 321.0
    gl_Position = vec4(sum);
}

#define ADD(a, b) a + b + ((a) + ((b)));

float foo()
{
    return ADD(gl_Position.xyxwx, 3.0)  // ERROR, should be this line number
    return ADD(gl_Position.y, 3.0)
}

#if 0
// ERROR, EOF