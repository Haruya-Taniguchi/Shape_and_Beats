
#version 150
precision mediump float;

flat in vec4 vColor;
flat in vec3 vNormal;
out vec4 outputColor;
 
void main(){
    outputColor = vColor;
}