#version 450

#extension GL_KHX_device_group : enable

out vec4 color;

void main() {
    color = vec4(gl_DeviceIndexKHR, 0, 0, 0);
}
