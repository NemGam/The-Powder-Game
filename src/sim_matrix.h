#ifndef SIM_MATRIX_H
#define SIM_MATRIX_H

#include <memory>
#include <vector>
#include <glad/glad.h>

#include "particles/material.h"

namespace powder_sim
{
	class Particle;

	class SimMatrix {
	public:
		//Creates matrix. Make sure that the max area is < 100000000.
		SimMatrix(int width, int height);
		SimMatrix(SimMatrix&) = delete;
		SimMatrix(SimMatrix&&) = delete;
		SimMatrix& operator=(const SimMatrix&) = delete;
		SimMatrix&& operator=(SimMatrix&&) = delete;


		~SimMatrix();


		void Swap(int x1, int y1, int x2, int y2);
		void Update(int x, int y);
		void WakeUpNeighbours(int x, int y) const;
		void SetParticle(Material material, int x, int y);
		[[nodiscard]] Particle* GetParticle(int x, int y) const;
		//Returns material of a particle at a given point
		[[nodiscard]] Material GetMaterial(int x, int y) const;
		[[nodiscard]] const std::vector<GLubyte>* GetColorData() const;
		[[nodiscard]] int GetWidth() const;
		[[nodiscard]] int GetHeight() const;
		void FlipUpdateFlag();

	private:
		//Update color data
		void ChangeColorAt(int x, int y, std::array<GLubyte, 4> color);
		void SwapColorData(int x1, int y1, int x2, int y2);
		[[nodiscard]] int GetColorIndexFromCoordinates(int x, int y) const;
		[[nodiscard]] bool IsInBounds(int x, int y) const;

		//Flag that defines the "updated" flag.
		//Allows to avoid resetting every particle's update flag at the end of the frame.
		bool update_flag_;
		int width_;
		int height_;
		std::unique_ptr<Particle> border_particle_;
		std::vector<std::vector<Particle*>> matrix_;
		std::vector<GLubyte> color_data_;
	};
}
#endif // SIM_MATRIX_H
