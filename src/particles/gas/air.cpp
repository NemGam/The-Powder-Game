#include "air.h"


namespace powder_sim
{
	Air::Air() :
		GasParticle(Material::kAir, { 0, 0, 0, 0 })
	{}

	Air* Air::Clone() const {
		return new Air(*this);
	}

	void Air::Move(SimMatrix& matrix, int x, int y) {
		is_sleeping_ = true;
		return;
	}
}
