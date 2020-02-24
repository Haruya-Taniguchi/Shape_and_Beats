#version 150
precision mediump float;

uniform mat4 invMatrix;
uniform vec3 lightDirection;
uniform vec3 eyeDirection;
uniform vec4 ambientColor;
in vec3 vNormal;
in vec4 vColor;
out vec4 outputColor;
void main(void){
	vec3  invLight  = normalize(invMatrix * vec4(lightDirection, 0.0)).xyz;
	vec3  invEye    = normalize(invMatrix * vec4(eyeDirection, 0.0)).xyz;
	vec3  halfLE    = normalize(invLight + invEye);
	float diffuse   = clamp(dot(vNormal, invLight), 0.0, 1.0);
	float specular  = pow(clamp(dot(vNormal, halfLE), 0.0, 1.0), 50.0);
	vec4  destColor = vColor * vec4(vec3(diffuse), 1.0) + vec4(vec3(specular), 1.0) + ambientColor;
	/*
	vec4  destColor;
	if(diffuse+specular > 0.99){
		destColor = vec4(1.0,1.0,1.0,1.0);
	}else if(diffuse+specular > 0.1){
		destColor = vec4(0.8,0.8,0.8,1.0);
	}else if(diffuse+specular > 0.05){
		destColor = vec4(0.4,0.4,0.4,1.0);
	}else{
		destColor = vec4(0.2,0.2,0.2,1.0);
	}
	*/
	outputColor    = destColor;
}