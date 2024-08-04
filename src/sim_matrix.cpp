#include <algorithm>
#include <iostream>
#include <glad/glad.h>
#include <climits>

#include "sim_matrix.h"
#include "core/chunk.h"
#include "particle_creator.h"

namespace powder_sim
{
	SimMatrix::SimMatrix(int width, int height, int chunk_size) :
		update_number_(0),
		width_(width),
		height_(height),
		chunk_size_(chunk_size),
		matrix_((height + 2) * (width + 2))
	{
		Particle::DEBUG_UPDATED_THIS_FRAME = 0;
		if (width * height > 5000000) {
			std::cerr << "Matrix area must be < 5,000,000" << '\n';
		}

		color_data_.resize(width * height * 4);
		std::cout << (width * height) << '\n';

		//No need to create copies of this particle
		border_particle_ = ParticleCreator::GetParticleByMaterial(Material::kBorder, false);

		for (int y = 0; y < height + 2; ++y) {
			for (int x = 0; x < width + 2; ++x) {

				//Creating a border
				if (y == 0 || x == 0 || x == width + 1 || y == height + 1) {
					//SetParticleInternal adjusts position, which is not desirable in case of the borders.
					SetParticleInternal(border_particle_, x - 1, y - 1);
					continue;
				}

				Particle* part = ParticleCreator::GetParticleByMaterial(Material::kAir, true);
				SetParticleInternal(part, x - 1, y - 1);
				ChangeColorAt(x - 1, y - 1, part->GetColor());
			}
		}

		//Create chunks
		x_chunks_num = width / chunk_size;
		y_chunks_num = height / chunk_size;

		for (int y = 0; y < y_chunks_num; ++y) {
			for (int x = 0; x < x_chunks_num; ++x) {
				chunks_.emplace_back(x, y, chunk_size, this);
			}
		}
	}

	SimMatrix::~SimMatrix() {
		for (int y = 1; y < height_ + 1; ++y) {
			for (int x = 1; x < width_ + 1; ++x) {

				delete matrix_[y * (width_ + 2) + x];
			}
		}
		delete border_particle_;
		std::cout << "Matrix has been destroyed\n";
	}

	void SimMatrix::Swap(int x1, int y1, int x2, int y2) {
		std::swap(matrix_[(y1 + 1) * (width_ + 2) + (x1 + 1)], matrix_[(y2 + 1) * (width_ + 2) + (x2 + 1)]);
		WakeUpNeighbours(x1, y1);
		WakeUpNeighbours(x2, y2);
		SwapColorData(x1, y1, x2, y2);
	}

	void SimMatrix::UpdateParticle(int x, int y) {
		GetParticle(x, y)->Update(*this, x, y, update_number_);
	}

	void SimMatrix::WakeUpNeighbours(int x, int y) {
		for (int i = x - 1; i <= x + 1; i++) {
			for (int j = y - 1; j <= y + 1; j++) {
				GetParticle(i, j)->WakeUp();
				WakeUpChunk(i, j);
			}
		}
	}

	void SimMatrix::WakeUpChunk(int particle_x, int particle_y) {
		int chunk_x = particle_x / chunk_size_;
		int chunk_y = particle_y / chunk_size_;
		WakeUpChunkAt(chunk_x, chunk_y);
	}

	void SimMatrix::SetParticle(Material material, int x, int y) {
		Particle* particle = ParticleCreator::GetParticleByMaterial(material);
		SetParticleInternal(particle, x, y);
		ChangeColorAt(x, y, particle->GetColor());
		WakeUpNeighbours(x, y);
		WakeUpChunk(x, y);
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

	void SimMatrix::UpdateChunk(int x, int y) {
		chunks_[y * x_chunks_num + x].Update();
	}

	void SimMatrix::IncrementUpdateNumber() {
		//std::cout << "Actually updated: " << Particle::DEBUG_UPDATED << '\n';
		Particle::DEBUG_UPDATED_THIS_FRAME = 0;

		//This will introduce some artifacts if a particle was not updated for a really long time, ~68 years
		update_number_ = (update_number_ + 1) % INT_MAX;
		std::cout << "Update: " << update_number_ << '\n';
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

	void SimMatrix::WakeUpChunkAt(int chunk_x, int chunk_y) {
		if (chunk_x < 0 || chunk_x >= x_chunks_num || chunk_y < 0 || chunk_y >= y_chunks_num) return;
		chunks_[chunk_y * x_chunks_num + chunk_x].WakeUp();
	}
}
