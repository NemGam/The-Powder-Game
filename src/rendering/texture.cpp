#include "texture.h"

#include <utility>
#include <glad/glad.h>

Texture::Texture(int width, int height) :
	width_(width),
	height_(height)
{
	Initialize();
}

void Texture::SetDynamicData(const std::vector<GLubyte>* dynamic_data) {
	data_ = dynamic_data;
}

void Texture::Draw() {
	glBindTexture(GL_TEXTURE_2D, id_);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_,
		height_, 0, GL_RGBA, GL_UNSIGNED_BYTE,
		data_->data());
	glActiveTexture(GL_TEXTURE0);
	//glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width_, height_, GL_RGBA, GL_UNSIGNED_BYTE, &data_);
}

const std::vector<GLubyte>* Texture::GetData() const {
	return data_;
}

int Texture::GetWidth() const {
	return width_;
}

int Texture::GetHeight() const {
	return height_;
}

unsigned int Texture::GetId() const {
	return id_;
}

void Texture::Initialize() {
	
	glGenTextures(1, &id_);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, id_);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}
