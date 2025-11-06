#include <glad/gl.h>
#include <stdlib.h>
#include <stdio.h>

#include "mesh.h"

//creates an equilateral triangle in the middle of the screen 
//colors, starting from the bottom left corner going clockwise, is red, blue, green
//returns allocated memory
struct mesh* create_equilateral_triangle() {
	struct mesh* equilateral_triangle = (struct mesh*)malloc(sizeof(struct mesh));
	float data[] = {
		-0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 1.0f,
		0.0f, 0.5f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f
	};
	int element_indices[] = {
		0, 1, 2
	};

	equilateral_triangle->vertex_count = 3;
	glGenVertexArrays(1, &equilateral_triangle->VAO);
	glBindVertexArray(equilateral_triangle->VAO);

	glGenBuffers(1, &equilateral_triangle->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, equilateral_triangle->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data) * sizeof(float), data, GL_STATIC_DRAW);

	//position
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	//color
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0,
			(void*)(sizeof(float) * equilateral_triangle->vertex_count * 4));
	glEnableVertexAttribArray(1);

	//elements
	glGenBuffers(1, &equilateral_triangle->EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, equilateral_triangle->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(element_indices) * sizeof(float),
		element_indices, GL_STATIC_DRAW);


	return equilateral_triangle;
}

struct mesh* create_quad() {
	struct mesh* quad = (struct mesh*)malloc(sizeof(struct mesh));
	float data[] = {
		1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 1.0f,
		-1.0f, 1.0f, 0.0f, 1.0f,

		1.0f, 0.0f, 0.0f, 1.0f,
                0.0f, 1.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f
        };

	int pos_indices[] = {
		0, 1, 3, 2, 3, 1
	};
	quad->vertex_count = 6;

	glGenVertexArrays(1, &quad->VAO);
	glBindVertexArray(quad->VAO);

	glGenBuffers(1, &quad->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, quad->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data) * sizeof(float), data, GL_STATIC_DRAW);

	//position
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	//color
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float) * 16));
	glEnableVertexAttribArray(1);

	//element
	glGenBuffers(1, &quad->EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(pos_indices) * sizeof(float), pos_indices,
			GL_STATIC_DRAW);

	return quad;
}

//draws a given mesh using elemental buffers
void draw(struct mesh* object) {
	glBindVertexArray(object->VAO);
	glDrawElements(GL_TRIANGLES, object->vertex_count, GL_UNSIGNED_INT, 0);
}

//draws a given mesh using array
void draw_array(struct mesh* object) {
	glBindVertexArray(object->VAO);
	glDrawArrays(GL_TRIANGLES, 0, object->vertex_count);
}

//deletes VAO & VBO of given mesh
void delete_mesh(struct mesh* object) {
	glDeleteVertexArrays(1, &object->VAO);
	glDeleteBuffers(1, &object->VBO);
	glDeleteBuffers(1, &object->EBO);
}

