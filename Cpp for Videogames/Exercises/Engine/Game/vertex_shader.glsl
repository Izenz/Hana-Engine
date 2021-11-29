#version 330
layout(location = 0) in vec3 pos;
//layout(location = 1) in vec3 color;
layout(location = 1) in vec2 vertex_uv;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

//out vec3 Color;
out vec2 uv0;

void main(){
	gl_Position = proj * view * model * vec4(pos, 1.0);
	//Color = color;
	uv0 = vertex_uv;
}