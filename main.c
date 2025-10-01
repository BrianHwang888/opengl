#include <glad/gl.h>
#include <GLFW/glfw3.h>

int main() {
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(600, 600, "OpenGL", NULL, NULL);
	glfwMakeContextCurrent(window);

	gladLoadGL(glfwGetProcAddress);

	float t[] = {
		-0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f
	};
	uint32_t v;
	glGenBuffers(1, &v);
	glBindBuffer(GL_ARRAY_BUFFER, v);
	glBufferData(GL_ARRAY_BUFFER, sizeof(t) * sizeof(t)/sizeof(t[0]), &t[0], 			GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	while(!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
