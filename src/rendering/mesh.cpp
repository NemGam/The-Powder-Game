#include <utility>

#include "mesh.h"

namespace powder_sim
{
	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned> indices, Texture& texture) :
		vertices_(std::move(vertices)),
		indices_(std::move(indices)),
		texture_(texture)
	{
		Initialize();
	}

	Mesh::~Mesh() {
		glDeleteVertexArrays(1, &vao_);
		glDeleteBuffers(1, &vbo_);
		glDeleteBuffers(1, &ebo_);
	}

	void Mesh::Render(Shader& shader) {
		glUniform1i(glGetUniformLocation(shader.GetId(), "aTexture"), 0);
		texture_.Draw();
		//glBindTexture(GL_TEXTURE_2D, texture_.GetId());
		glBindVertexArray(vao_);
		glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices_.size()), GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);
	}

	Texture& Mesh::GetTexture() {
		return texture_;
	}

	void Mesh::Initialize() {
		glGenVertexArrays(1, &vao_);
		glGenBuffers(1, &vbo_);
		glGenBuffers(1, &ebo_);

		glBindVertexArray(vao_);

		glBindBuffer(GL_ARRAY_BUFFER, vbo_);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices_.size(), vertices_.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices_.size(), indices_.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr); //position

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(sizeof(std::array<int, 2>))); //texPos

		glBindVertexArray(0);
	}
}