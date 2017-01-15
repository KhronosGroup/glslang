#version 450

in layout(location = 0) vec4 xyz;


void main(){
  gl_Position = xyz;
}