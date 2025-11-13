#version 460

uniform UBO {
    int x;
};

out vec4 outColor;

void main() {
    int x = 41;
    {
        int x = 42;
        outColor = vec4(x);
    }
}