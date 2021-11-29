#version 330
out vec4 color;

//in vec3 Color;
in vec2 uv0;

uniform sampler2D lenaTexture;

void main(){
	//color = vec4(Color, 1.0f);
	color = texture2D(lenaTexture, uv0);
}