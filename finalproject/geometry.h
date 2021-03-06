#pragma once

#include <GL/glew.h>      // OpenGL Extension Wrangler -
#include <glm/glm.hpp>      // OpenGL math library
#include "shader_util.h"
#include <stdexcept>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 normal;

	Vertex();
	Vertex(glm::vec3 position, glm::vec3 color, glm::vec3 normal);
};
struct VertexComponents
{
	unsigned char dimensions;
	unsigned int size;
	GLenum dataType;

	VertexComponents(unsigned char dimensions, unsigned int size, GLenum dataType)
		:dimensions(dimensions), size(size), dataType(dataType)
	{}
};

GLuint create_handle(std::vector<VertexComponents> format, void* vertexBuffer, unsigned int vertexCount, unsigned int* indexBuffer, unsigned int indexCount, GLenum primitive);
GLuint create_quad(glm::vec3 color, shader_prog* shader);
GLuint create_textured_quad(glm::vec3 color, shader_prog* shader);
GLuint create_sphere(float radius, int width_segments, int height_segments, glm::vec3 color, int& chopper_body_triangle_count, shader_prog* shader);
GLuint create_cube(glm::vec3 color, shader_prog* shader);

