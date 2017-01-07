#version 450

#extension GL_KHX_multiview : enable

out vec4 color;

void main() {
    color = vec4(gl_ViewIndexKHR, 0, 0, 0);
}
