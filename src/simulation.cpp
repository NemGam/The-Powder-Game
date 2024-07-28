#include "simulation.h"

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
	for (int i = 0; i < height_; ++i) {
		for (int j = 0; j < width_; ++j) {
			matrix_.Update(j, i);
		}
	}
	matrix_.FlipUpdateFlag();
}

SimMatrix& Simulation::GetMatrix() {
	return matrix_;
}
