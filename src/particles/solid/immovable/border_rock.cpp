#include "border_rock.h"

#include <iostream>

namespace powder_sim
{
	BorderRock::BorderRock() :
		ImmovableSolidParticle(Material::kBorderRock, { 100, 100, 100 }) {
	}

	BorderRock* BorderRock::Clone() const {
		return new BorderRock(*this);
	}
}
