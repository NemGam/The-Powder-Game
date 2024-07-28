#include "sand.h"

#include "core/random.h"


Sand::Sand() :
	MovableSolidParticle(Material::kSand, {242, 165, 3, 0}) {
}

Sand* Sand::Clone() const {
	return new Sand(*this);
}
