#include "simulation.h"
#include "particles/particle.h"
#include "particles/gas/air.h"
#include "particles/solid/movable/sand.h"

Simulation::Simulation(int width, int height) :
	matrix_(width, height),
	width_(width),
	height_(height)
{
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			matrix_.SetParticle(new Air(), j, i);
		}
	}
}

void Simulation::Start() {
	matrix_.SetParticle(new Sand(), width_ / 2, height_ / 2);
}


void Simulation::Update() {
	for (int i = 0; i < height_; ++i) {
		for (int j = 0; j < width_; ++j) {
			matrix_.Update(j, i);
		}
	}
}

SimMatrix& Simulation::GetMatrix() {
	return matrix_;
}

