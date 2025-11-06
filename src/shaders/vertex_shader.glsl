#version 330 core

layout (location = 0) in vec4 aPos;
layout (location = 1) in vec4 aColor;

out vec4 vertex_color;

void main() {
	gl_Position = aPos;
	vertex_color = aColor;
}
