#include "movable_solid_particle.h"

void MovableSolidParticle::Move(SimMatrix& matrix, int x, int y) {
}

MovableSolidParticle::MovableSolidParticle(Material element, const std::array<GLubyte, 4>& color) :
	SolidParticle(element, color) {
}
