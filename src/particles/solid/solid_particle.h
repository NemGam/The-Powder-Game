#ifndef SOLID_PARTICLE_H
#define SOLID_PARTICLE_H

#include "particles/particle.h"

namespace powder_sim
{
	class SolidParticle :
		public Particle
	{
	public:
		void Move(SimMatrix& matrix, int x, int y) override;

	protected:
		SolidParticle(Material element, const std::array<GLubyte, 4>& color);
	};
}
#endif // SOLID_PARTICLE_H
