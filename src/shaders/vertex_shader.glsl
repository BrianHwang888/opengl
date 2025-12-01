#version 330 core

layout (location = 0) in vec4 aPos;
layout (location = 1) in vec4 aColor;

out vec4 vertex_color;
out vec2 fragment_tex_coord;

void main() {
	gl_Position = aPos;
	vertex_color = aColor;
	fragment_tex_coord = vec2(0.5f, -0.5f) * (aPos.xy + vec2(1.0f));
}
