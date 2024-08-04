#ifndef SIM_MATRIX_H
#define SIM_MATRIX_H

#include <memory>
#include <vector>
#include <glad/glad.h>

#include "particles/material.h"

namespace powder_sim
{
	class Particle;
	class Chunk;

	class SimMatrix {
	public:
		//Creates matrix. Make sure that the max area is < 100,000,000.
		SimMatrix(int width, int height, int chunk_size);
		SimMatrix(SimMatrix&) = default;
		SimMatrix(SimMatrix&&) = default;
		SimMatrix& operator=(const SimMatrix&) = default;
		SimMatrix& operator=(SimMatrix&&) = default;


		~SimMatrix();


		void Swap(int x1, int y1, int x2, int y2);
		void UpdateParticle(int x, int y);
		void UpdateChunk(int x, int y);
		void IncrementUpdateNumber();
		void SetParticle(Material material, int x, int y);
		void WakeUpNeighbours(int x, int y);
		//Wakes up chunk at particle's position
		void WakeUpChunk(int particle_x, int particle_y);

		//Getters

		[[nodiscard]] Particle* GetParticle(int x, int y) const;
		//Returns material of a particle at a given point
		[[nodiscard]] Material GetMaterial(int x, int y) const;
		[[nodiscard]] const std::vector<GLubyte>* GetColorData() const;
		[[nodiscard]] int GetWidth() const;
		[[nodiscard]] int GetHeight() const;

	private:
		//Update color data
		void ChangeColorAt(int x, int y, std::array<GLubyte, 4> color);
		void SwapColorData(int x1, int y1, int x2, int y2);

		//Accounts for the border before setting the particle
		void SetParticleInternal(Particle* part, int x, int y);
		[[nodiscard]] int GetColorIndexFromCoordinates(int x, int y) const;
		[[nodiscard]] bool IsInBounds(int x, int y) const;

		void WakeUpChunkAt(int chunk_x, int chunk_y);

		//Current update number
		int update_number_;
		int width_, height_;
		int chunk_size_;
		int x_chunks_num;
		int y_chunks_num;
		Particle* border_particle_;
		std::vector<Particle*> matrix_;
		std::vector<Chunk> chunks_;
		std::vector<GLubyte> color_data_;
	};
}
#endif // SIM_MATRIX_H
