#ifndef MESH_H
#define MESH_H

#include <vector>

#include "shader.h"
#include "texture.h"
#include "vertex.h"

class Mesh {
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Texture texture);


	~Mesh();


	void Render(Shader& shader);
	Texture& GetTexture();

private:
	void Initialize();

	
	std::vector<Vertex> vertices_;
	std::vector<unsigned int> indices_;
	Texture texture_;

	unsigned int vao_;
	unsigned int vbo_, ebo_;
};
#endif // MESH_H
