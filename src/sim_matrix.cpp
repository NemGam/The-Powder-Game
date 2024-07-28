#include <algorithm>
#include <iostream>
#include <glad/glad.h>

#include "sim_matrix.h"
#include "particles.h"
#include "particle_creator.h"
#include "particles/solid/immovable/border_rock.h"

SimMatrix::SimMatrix(int width, int height) :
	update_flag_(true),
	width_(width),
	height_(height),
	matrix_(height, std::vector<Particle*>(width))
{
	border_particle_ = std::make_unique<BorderRock>();
	color_data_.resize(width * height * 4);
	std::cout << (width * height * 4) << std::endl;
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			Particle* part = new Air();
			matrix_[i][j] = part;
			ChangeColorAt(j, i, part->GetColor());
		}
	}
}

SimMatrix::~SimMatrix() {
	for (int i = 0; i < height_; ++i) {
		for (int j = 0; j < width_; ++j) {
			delete matrix_[i][j];
		}
	}
}

void SimMatrix::Swap(int x1, int y1, int x2, int y2) {
	if (!(IsInBounds(x1, y1) && IsInBounds(x2, y2))) return;

	SwapColorData(x1, y1, x2, y2);
	std::swap(matrix_[y1][x1], matrix_[y2][x2]);
}

void SimMatrix::Update(int x, int y) {
	if (matrix_[y][x]->GetUpdateFlag() == update_flag_) return;

	matrix_[y][x]->Update(*this, x, y);
}

void SimMatrix::SetParticle(Material material, int x, int y) {
	if (!IsInBounds(x, y)) return;

	delete matrix_[y][x];

	Particle* particle = ParticleCreator::GetParticleByMaterial(material);
	matrix_[y][x] = particle;
	ChangeColorAt(x, y, particle->GetColor());
	
}

Particle* SimMatrix::GetParticle(int x, int y) const {
	if (!IsInBounds(x, y)) return border_particle_.get();
	return matrix_[y][x];
}

const std::vector<GLubyte>* SimMatrix::GetColorData() const {
	return &color_data_;
}

int SimMatrix::GetWidth() const {
	return width_;
}

int SimMatrix::GetHeight() const {
	return height_;
}

void SimMatrix::FlipUpdateFlag() {
	update_flag_ = !update_flag_;
}

void SimMatrix::ChangeColorAt(int x, int y, std::array<GLubyte, 4> color) {
	//std::memcpy(color_data_[y][x].data(), color.data(), color.size());
	int ind = GetColorIndexFromCoordinates(x, y);
	color_data_[ind] = color[0];
	color_data_[ind + 1] = color[1];
	color_data_[ind + 2] = color[2];
	color_data_[ind + 3] = color[3];
}

void SimMatrix::SwapColorData(int x1, int y1, int x2, int y2) {
	int ind1 = GetColorIndexFromCoordinates(x1, y1), ind2 = GetColorIndexFromCoordinates(x2, y2);
	std::swap(color_data_[ind1], color_data_[ind2]);
	std::swap(color_data_[ind1 + 1], color_data_[ind2 + 1]);
	std::swap(color_data_[ind1 + 2], color_data_[ind2 + 2]);
	std::swap(color_data_[ind1 + 3], color_data_[ind2 + 3]);
}

int SimMatrix::GetColorIndexFromCoordinates(int x, int y) const {
	return (y * width_ + x) * 4;
}

bool SimMatrix::IsInBounds(int x, int y) const {
	return (0 <= x && x < width_ && 0 <= y && y < height_);
}
