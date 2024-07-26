#include "simulation.h"
#include "particles/particle.h"
#include "particles/gas/air.h"
#include "particles/solid/movable/sand.h"

Simulation::Simulation(const Window* window, int width, int height) :
	window_(window),
	matrix_(width, height),
	brush_(window, &matrix_),
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

float timer = 0;
void Simulation::Update(float dt) {
	timer += dt;
	if (timer >= 2) {
		matrix_.SetParticle(new Sand(), width_ / 2, height_ - 1);
		timer = 0;
	}
	brush_.Update();
	for (int i = 0; i < height_; ++i) {
		for (int j = 0; j < width_; ++j) {
			matrix_.Update(j, i);
		}
	}
}

SimMatrix& Simulation::GetMatrix() {
	return matrix_;
}

