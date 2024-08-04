#include "solid_particle.h"

namespace powder_sim
{

	SolidParticle::SolidParticle(Material element, const std::array<GLubyte, 4>& color) :
		Particle(element, color) {
	}
}
