#include "simulation.h"

namespace powder_sim
{
	Simulation::Simulation(const Window* window, int width, int height) :
		matrix_(width, height),

		brush_(window, &matrix_),
		width_(width),
		height_(height)
	{}

	void Simulation::Start() {

	}

	void Simulation::Update(float dt) {
		brush_.Update();
		bool dir = false;
		for (int i = height_ - 1; i >= 0; --i) {
			if (dir) {
				for (int j = 0; j < width_; ++j) {
					matrix_.Update(j, i);
				}
			}
			else {
				for (int j = width_ - 1; j >= 0; --j) {
					matrix_.Update(j, i);
				}
			}
			dir = !dir;
		}
		matrix_.FlipUpdateFlag();
	}

	SimMatrix& Simulation::GetMatrix() {
		return matrix_;
	}
}