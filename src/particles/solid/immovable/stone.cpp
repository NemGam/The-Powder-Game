#include "stone.h"

namespace powder_sim
{
	Stone::Stone() :
		ImmovableSolidParticle(Material::kStone, { 150, 150, 150, 1 })
	{}

	Stone* Stone::Clone() const {
		return new Stone(*this);
	}
}
