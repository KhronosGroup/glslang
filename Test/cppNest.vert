#define ON

float sum = 0.0;

void main()
{

#ifdef ON
//yes
sum += 1.0;

    #ifdef OFF
    //no
    sum += 20.0;
    #endif

    #if defined(ON)
    //yes
    sum += 300.0;
    #endif

#endif


#if defined(OFF)
//no
sum += 4000.0;

#if !defined(ON)
//no
sum += 50000.0;
#endif

    //no
    sum += 0.1;
    #ifdef ON
        //no
        sum += 0.2;
    #endif

    //no
    sum += 0.01;
    #ifdef ON
        //no
        sum += 0.02;
    #else
        //no
        sum += 0.03;
    #endif

//no
    sum + 0.3;

#endif


#if !defined(OFF)
//yes
sum += 600000.0;

    #if defined(ON) && !defined(OFF)
    //yes
    sum += 80000000.0;

        #if defined(OFF) || defined(ON)
        //yes
        sum += 900000000.0;

            #if defined(ON) && defined(OFF)
                //no
                sum += 0.7;
            #elif !defined(OFF)
                //yes
                sum += 7000000.0;
            #endif

        #endif

    #endif

#endif

// sum should be 987600301.0
    gl_Position = vec4(sum);
}
