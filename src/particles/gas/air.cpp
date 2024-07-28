#include "air.h"

Air::Air() :
	GasParticle(Material::kAir, {0, 0, 0, 0})
{}

Air* Air::Clone() const {
	return new Air(*this);
}

void Air::Move(SimMatrix& matrix, int x, int y) {
	return;
}
