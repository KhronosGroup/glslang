#version 100

varying vec3 color;

lowp vec2 foo(mediump vec3 mv3)
{
    highp vec4 hv4;
    return hv4.xy;
}

int global_medium;

precision highp int;

int global_high;

void main()
{
    lowp int sum = global_medium + global_high;

    gl_FragColor = vec4(color, 1.0f);

    int level1_high;
    sum += level1_high;

    precision lowp int;
    int level1_low;
    sum += level1_low;

    {
        int level2_low;
        sum += level2_low;
        
        precision highp int;
        int level2_high;
        sum += level2_high;
        do {
            if (1) {
                precision mediump int;
                int level4_medium;
                sum += level4_medium;
            }
            int level3_high;
            sum += level3_high;
        } while (1);	
        int level2_high2;
        sum += level2_high2;
    }
    int level1_low3;
    sum += level1_low3;
}
