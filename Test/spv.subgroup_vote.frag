#version 440

#extension GL_ARB_shader_group_vote : enable

flat in int idx;
out vec4 color;

void main() {
    bool b = (idx == 4);
    if (anyInvocationARB(b)) {
        color = vec4(1);
    }
    else if (allInvocationsARB(b)) {
        color = vec4(2);
    }
    else if (allInvocationsEqualARB(b)) {
        color = vec4(3);
    }
    else {
        color = vec4(4);
    }
}