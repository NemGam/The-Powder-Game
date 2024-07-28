#include "sand.h"


Sand::Sand() :
	MovableSolidParticle(Material::kSand, {252, 165, 3, 0}) {
}

Sand* Sand::Clone() const {
	return new Sand(*this);
}
