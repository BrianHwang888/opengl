#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_utils.h"
#include "material.h"
#include "mesh.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window) {
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

unsigned int make_shader_module(const char* file_path, unsigned int module_type) {
	const char* file_source = read_entire_file(file_path);
	unsigned int shader_module = glCreateShader(module_type);
	glShaderSource(shader_module, 1, &file_source, NULL);
	glCompileShader(shader_module);
	
	int success;
	glGetShaderiv(shader_module, GL_COMPILE_STATUS, &success);
	if(!success) {
		char error_log[1024];
		glGetShaderInfoLog(shader_module, 1024, NULL, error_log);
		perror(error_log);
	}
	free((char*)file_source); //cast to char* to remove free const warning
	
	return shader_module;
}

unsigned int make_shader(const char* vertex_file_path, const char* fragment_file_path) {
	unsigned int modules[2];
	modules[0] = make_shader_module("src/shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	modules[1] = make_shader_module("src/shaders/fragment_shader.glsl", GL_FRAGMENT_SHADER);

	int modules_size = sizeof(modules) / sizeof(modules[0]);
	unsigned int shader = glCreateProgram();
	for(int i = 0; i < modules_size; i++) {
		glAttachShader(shader, modules[i]);
	}
	glLinkProgram(shader);

	int success;
	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if(!success) {
		char error_log[1024];
		glGetProgramInfoLog(shader, 1024, NULL, error_log);
		perror(error_log);
	}

	for(int i = 0; i < modules_size; i++) {
		glDeleteShader(modules[i]);
	}

	return shader;
}

int main() {
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL", NULL, NULL);
	if(window == NULL) {
		printf("Failed to create GLFW window\n");
		return EXIT_FAILURE;
	}
	glfwMakeContextCurrent(window);

	if(!gladLoadGL(glfwGetProcAddress)) {
		printf("Failed to initialize GLAD\n");
		return EXIT_FAILURE;
	}
	
	unsigned int shader = make_shader("src/shaders/vertex_shader.glsl", "src/shaders/fragment_shader.glsl");
	
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	struct mesh* triangle = create_equilateral_triangle();
	struct mesh* quad = create_quad();
	
	struct material* potato = create_material("img/Patates.jpg");
	struct material* mask = create_material("img/mask.jpg");

	glUseProgram(shader);
	glUniform1i(glGetUniformLocation(shader, "potato"), 0);
	glUniform1i(glGetUniformLocation(shader, "mask"), 1);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	while(!glfwWindowShouldClose(window)) {
		process_input(window);

		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shader);
		//draw(triangle);
		use(potato, 0);
		use(mask, 1);
		draw(quad);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	delete_mesh(triangle);
	free(triangle);
	delete_material(potato);
	free(potato);
	delete_material(mask);
	free(mask);
	glDeleteProgram(shader);
	glfwTerminate();
	return EXIT_SUCCESS;
}
