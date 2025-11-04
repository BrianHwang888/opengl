#ifndef MESH_H
#define MESH_H

struct mesh {
	unsigned int EBO, VBO, VAO, vertex_count;
};

struct mesh* create_equilateral_triangle();
void draw(struct mesh* object);
void delete_mesh(struct mesh* object);
#endif
