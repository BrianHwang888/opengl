#include <stdio.h>

#include "glad/gl.h"
#include "material.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//Create material struct using image file
struct material* create_material(const char* file) {
	int width, height, channels;
	struct material* mat = (struct material*)malloc(sizeof(struct material));
	unsigned char* data = stbi_load(file, &width, &height, &channels, STBI_rgb_alpha);
	if(stbi_failure_reason()) {
		printf("stbi failure: %s\n", stbi_failure_reason());
	}

	glCreateTextures(GL_TEXTURE_2D, 1, &mat->texture);
	glBindTexture(GL_TEXTURE_2D, mat->texture);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
			width, height, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	return mat;
}

void delete_material(struct material* mat) {
	glDeleteTextures(1, &mat->texture);
}

void use(struct material* mat, int unit) {
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, mat->texture);
}

