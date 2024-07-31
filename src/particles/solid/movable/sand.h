#ifndef SAND_PARTICLE_H
#define SAND_PARTICLE_H

#include "particles/solid/movable/movable_solid_particle.h"

namespace powder_sim
{
	class Sand final :
		public MovableSolidParticle
	{
	public:
		Sand();

		[[nodiscard]] Sand* Clone() const override;
	};
}
#endif // SAND_PARTICLE_H
