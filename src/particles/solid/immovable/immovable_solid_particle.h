#ifndef IMMOVABLE_SOLID_PARTICLE_H
#define IMMOVABLE_SOLID_PARTICLE_H

#include "particles/solid/solid_particle.h"

namespace powder_sim
{
	class ImmovableSolidParticle :
		public SolidParticle {
	public:
		void Move(SimMatrix& matrix, int x, int y) final;

	protected:
		ImmovableSolidParticle(Material element, const std::array<GLubyte, 4>& color);
	};
}
#endif // IMMOVABLE_SOLID_PARTICLE_H
