#include "particle.h"
#include <array>

ElementType Particle::GetElement() const {
	return element_;
}

std::array<GLubyte, 4>& Particle::GetColor() {
	return color_;
}

void Particle::Update(SimMatrix& matrix, int x, int y) {
	Move(matrix, x, y);
}

Particle::Particle(ElementType element, const std::array<GLubyte, 4>& color) :
	element_(element),
	color_{color}
{}
