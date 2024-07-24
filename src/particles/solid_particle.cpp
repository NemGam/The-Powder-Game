#include "solid_particle.h"

void SolidParticle::Move(SimMatrix& matrix, int x, int y) {
}

SolidParticle::SolidParticle(ElementType element, const std::array<GLubyte, 4>& color) :
	Particle(element, color)
{}
