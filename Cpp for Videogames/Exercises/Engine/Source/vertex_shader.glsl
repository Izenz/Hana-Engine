#version 330
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 color;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

out vec3 Color;

void main(){
	//gl_Position = vec4(pos, 1.0);
	gl_Position = proj * view * model * vec4(pos, 1.0);
	Color = color;
}