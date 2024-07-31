#include <algorithm>
#include <iostream>
#include <glad/glad.h>

#include "sim_matrix.h"
#include "particle_creator.h"
#include "particles/solid/immovable/border_rock.h"

namespace powder_sim
{
	SimMatrix::SimMatrix(int width, int height) :
		update_flag_(true),
		width_(width),
		height_(height),
		matrix_(height + 2, std::vector<Particle*>(width + 2))
	{
		Particle::DEBUG_UPDATED = 0;
		if (width * height > 10000000) {
			std::cerr << "Matrix area must be < 10,000,000" << '\n';
		}
		border_particle_ = std::make_unique<BorderRock>();
		color_data_.resize(width * height * 4);
		std::cout << (width * height * 4) << '\n';

		for (int i = 0; i < height + 2; ++i) {
			for (int j = 0; j < width + 2; ++j) {

				//Creating a border
				if (i == 0 || j == 0 || j == width + 1 || i == height + 1) {
					matrix_[i][j] = ParticleCreator::GetParticleByMaterial(Material::kBorderRock, false);
					continue;
				}
				Particle* part = ParticleCreator::GetParticleByMaterial(Material::kAir, false);
				matrix_[i][j] = part;
				ChangeColorAt(j - 1, i - 1, part->GetColor());
			}
		}
	}

	SimMatrix::~SimMatrix() {
		for (int i = 0; i < height_ + 2; ++i) {
			for (int j = 0; j < width_ + 2; ++j) {
				delete matrix_[i][j];
			}
		}
		std::cout << "Matrix has been destroyed\n";
	}

	void SimMatrix::Swap(int x1, int y1, int x2, int y2) {
		//Border
		y1++; x1++; y2++; x2++;
		std::swap(matrix_[y1][x1], matrix_[y2][x2]);
		WakeUpNeighbours(x1, y1);
		WakeUpNeighbours(x2, y2);
		SwapColorData(x1 - 1, y1 - 1, x2 - 1, y2 - 1);
	}

	void SimMatrix::Update(int x, int y) {
		if (matrix_[y + 1][x + 1]->GetUpdateFlag() == update_flag_) return;
		matrix_[y + 1][x + 1]->Update(*this, x, y);
	}

	void SimMatrix::WakeUpNeighbours(int x, int y) const {
		for (int i = x - 1; i <= x + 1; i++) {
			for (int j = y - 1; j <= y + 1; j++) {
				matrix_[j][i]->WakeUp();
			}
		}
	}

	void SimMatrix::SetParticle(Material material, int x, int y) {
		//Don't forget about the border!
		x++; y++;

		delete matrix_[y][x];

		Particle* particle = ParticleCreator::GetParticleByMaterial(material);
		matrix_[y][x] = particle;
		ChangeColorAt(x - 1, y - 1, particle->GetColor());
		WakeUpNeighbours(x, y);
	}



	Particle* SimMatrix::GetParticle(int x, int y) const {
		return matrix_[y + 1][x + 1];
	}

	Material SimMatrix::GetMaterial(int x, int y) const {
		return matrix_[y + 1][x + 1]->GetMaterial();
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
		//std::cout << "Actually updated: " << Particle::DEBUG_UPDATED << '\n';
		Particle::DEBUG_UPDATED = 0;
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
}