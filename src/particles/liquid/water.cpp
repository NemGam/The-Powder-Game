#include "water.h"

namespace powder_sim
{
	Water::Water() :
		LiquidParticle(Material::kWater, { 0, 0, 255, 1 }, 5)
	{}

	Water* Water::Clone() const {
		return new Water(*this);
	}
}
