#version 330 core
out vec4 frag_color;

in vec4 vertex_color;
in vec2 fragment_tex_coord;

uniform sampler2D material;
uniform sampler2D mask;

void main() {
	vec3 base_color = texture(material, fragment_tex_coord).rgb;
	float alpha = texture(mask, fragment_tex_coord).r;
	frag_color = vec4(base_color, alpha);
}
