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
		matrix_((height + 2) * (width + 2))
	{
		Particle::DEBUG_UPDATED = 0;
		if (width * height > 5000000) {
			std::cerr << "Matrix area must be < 5,000,000" << '\n';
		}

		color_data_.resize(width * height * 4);
		std::cout << (width * height) << '\n';

		//No need to create copies of this particle
		Particle* border_rock = ParticleCreator::GetParticleByMaterial(Material::kBorderRock, false);

		for (int y = 0; y < height + 2; ++y) {
			for (int x = 0; x < width + 2; ++x) {

				//Creating a border
				if (y == 0 || x == 0 || x == width + 1 || y == height + 1) {
					//SetParticleInternal adjusts position, which is not desirable in case of the borders.
					SetParticleInternal(border_rock, x - 1, y - 1);
					continue;
				}

				Particle* part = ParticleCreator::GetParticleByMaterial(Material::kAir, true);
				SetParticleInternal(part, x - 1, y - 1);
				ChangeColorAt(x - 1, y - 1, part->GetColor());
			}
		}

	}

	SimMatrix::~SimMatrix() {
		bool border_deleted = false;
		for (int y = 0; y < height_ + 2; ++y) {
			for (int x = 0; x < width_ + 2; ++x) {

				//Deleting border (only once)
				if (y == 0 || x == 0 || x == width_ + 1 || y == height_ + 1) {
					if (border_deleted) continue;

					border_deleted = true;
					delete matrix_[y * (width_ + 2) + x];

					continue;
				}

				delete matrix_[y * (width_ + 2) + x];
			}
		}
		std::cout << "Matrix has been destroyed\n";
	}

	void SimMatrix::Swap(int x1, int y1, int x2, int y2) {
		std::swap(matrix_[(y1 + 1) * (width_ + 2) + (x1 + 1)], matrix_[(y2 + 1) * (width_ + 2) + (x2 + 1)]);
		WakeUpNeighbours(x1, y1);
		WakeUpNeighbours(x2, y2);
		SwapColorData(x1, y1, x2, y2);
	}

	void SimMatrix::Update(int x, int y) {
		if (GetParticle(x, y)->GetUpdateFlag() == update_flag_) return;
		GetParticle(x, y)->Update(*this, x, y);
	}

	void SimMatrix::WakeUpNeighbours(int x, int y) const {
		for (int i = x - 1; i <= x + 1; i++) {
			for (int j = y - 1; j <= y + 1; j++) {
				GetParticle(i, j)->WakeUp();
			}
		}
	}

	void SimMatrix::SetParticle(Material material, int x, int y) {
		Particle* particle = ParticleCreator::GetParticleByMaterial(material);
		SetParticleInternal(particle, x, y);
		ChangeColorAt(x, y, particle->GetColor());
		WakeUpNeighbours(x, y);
	}


	Particle* SimMatrix::GetParticle(int x, int y) const {
		return matrix_[(y + 1) * (width_ + 2) + (x + 1)];
	}

	Material SimMatrix::GetMaterial(int x, int y) const {
		return GetParticle(x, y)->GetMaterial();
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

	void SimMatrix::SetParticleInternal(Particle* part, int x, int y) {
		const int ind = (y + 1) * (width_ + 2) + (x + 1);
		delete matrix_[ind];
		matrix_[ind] = part;
	}

	int SimMatrix::GetColorIndexFromCoordinates(int x, int y) const {
		return (y * width_ + x) * 4;
	}

	bool SimMatrix::IsInBounds(int x, int y) const {
		return (0 <= x && x < width_ && 0 <= y && y < height_);
	}
}