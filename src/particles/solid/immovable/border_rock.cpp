#include "border_rock.h"

#include <iostream>

namespace powder_sim
{
	BorderRock::BorderRock() :
		ImmovableSolidParticle(Material::kBorderRock, { 0, 0, 0, 0 }) {
	}

	BorderRock* BorderRock::Clone() const {
		return new BorderRock(*this);
	}
}
