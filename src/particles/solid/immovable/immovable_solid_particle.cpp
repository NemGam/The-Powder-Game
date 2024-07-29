#include "immovable_solid_particle.h"

void ImmovableSolidParticle::Move(SimMatrix& matrix, int x, int y) {
	is_sleeping_ = true;
	return;
}

ImmovableSolidParticle::ImmovableSolidParticle(Material element, const std::array<GLubyte, 4>& color) :
	SolidParticle(element, color) {
}
