#include "sand.h"

#include "core/random.h"

namespace powder_sim
{
	Sand::Sand() :
		MovableSolidParticle(Material::kSand, { 242, 165, 3 }) {
	}

	Sand* Sand::Clone() const {
		return new Sand(*this);
	}
}