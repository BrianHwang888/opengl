struct material {
	unsigned int texture;
};

struct material* create_material(const char* file);
void delete_material(struct material* mat);
void use(struct material* mat, int unit);
