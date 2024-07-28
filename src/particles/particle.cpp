#include <array>
#include "particle.h"

Material Particle::GetElement() const {
	return element_;
}

const std::array<GLubyte, 4>& Particle::GetColor() const{
	return color_;
}

void Particle::Update(SimMatrix& matrix, int x, int y) {
	Move(matrix, x, y);
}

bool Particle::GetUpdateFlag() const {
	return update_flag_;
}

Particle::Particle(Material element, const std::array<GLubyte, 4>& color) :
	update_flag_(false),
	element_(element),
	color_{color}
{}
