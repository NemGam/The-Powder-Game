#include "particles/gas/gas_particle.h"

void GasParticle::Move(SimMatrix& matrix, int x, int y) {
	return;
}

GasParticle::GasParticle(ElementType element, const std::array<GLubyte, 4>& color)
	: Particle(element, color)
{}

