#version 150
precision mediump float;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 mvpMatrix;
uniform mat4 invMatrix;
uniform float time;
uniform vec3 lightDirection;
uniform vec3 eyeDirection;
uniform vec4 ambientColor;
uniform vec4 bgColor;

in vec3 position;
in vec4 color;
in vec3 normal;

out vec3 vNormal;
out vec4 vColor;

void main() {
    vec3  invLight = normalize(invMatrix * vec4(lightDirection, 0.0)).xyz;
	vec3  invEye   = normalize(invMatrix * vec4(eyeDirection, 0.0)).xyz;
	vec3  halfLE   = normalize(invLight + invEye);
	float specular = pow(clamp(dot(normal, halfLE), 0.0, 1.0), 100.0);
    float diffuse  = clamp(dot(normal, invLight), 0.1, 1.0);
	vColor = mix(color,bgColor,diffuse) + vec4(vec3(specular), 1.0) + ambientColor;
    vNormal = normal;
    gl_Position = mvpMatrix * vec4(position, 1.0);
}