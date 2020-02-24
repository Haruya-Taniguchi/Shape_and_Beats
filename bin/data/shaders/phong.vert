#version 150
precision mediump float;
in vec3 position;
in vec4 color;
in vec3 normal;
uniform mat4 mvpMatrix;
out vec3 vNormal;
out vec4 vColor;


void main(void){
    vNormal     = normal;
    vColor      = color;
    gl_Position = mvpMatrix * vec4(position, 1.0);
}