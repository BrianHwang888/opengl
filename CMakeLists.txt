cmake_minimum_required(VERSION 3.17)

project(tri)

find_package(OpenGL REQUIRED)

add_executable(
	${PROJECT_NAME} 
	src/main.c
	src/gl.c
	src/shaders
	src/utils/file_utils.c
	src/mesh.c
)

target_include_directories(
	${PROJECT_NAME}
	PRIVATE
	inc
)

target_link_libraries(
	${PROJECT_NAME}
	OpenGL::GL
       	dl
       	glfw
)
