#version 300 es
precision mediump float;
in lowp float lowfin;
in mediump float mediumfin;
in highp vec4 highfin;

uniform highp int uniform_high;
uniform mediump int uniform_medium;
uniform lowp int uniform_low;
uniform bvec2 ub2;

out mediump vec4 mediumfout;

highp float global_highp;

lowp vec2 foo(mediump vec3 mv3)
{
    return highfin.xy;
}

bool boolfun(bvec2 bv2)
{
    return bv2 == bvec2(false, true);
}

void main()
{
    lowp int sum = uniform_medium + uniform_high;

    sum += uniform_high;
    sum += uniform_low;
    
    // test maxing precisions of args to get precision of builtin
    lowp float arg1 = 3.2;
    mediump float arg2 = 1023908.2;
    lowp float d = distance(lowfin, mediumfin);

    global_highp = length(highfin);

    highp vec4 local_highp = vec4(global_highp);

    mediumfout = vec4(sin(d)) + arg2 + local_highp;

    sum += 4 + ((ivec2(uniform_low) * ivec2(uniform_high) + ivec2((/* comma operator */uniform_low, uniform_high)))).x;

    mediumfout += vec4(sum);

    if (boolfun(ub2))
        ++mediumfout;
}
