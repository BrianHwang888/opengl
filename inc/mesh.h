#ifndef MESH_H
#define MESH_H

struct mesh {
	unsigned int EBO, VBO, VAO, vertex_count;
};

struct mesh* create_equilateral_triangle();
struct mesh* create_quad();
void draw(struct mesh* object);
void draw_array(struct mesh* object);
void delete_mesh(struct mesh* object);
#endif
