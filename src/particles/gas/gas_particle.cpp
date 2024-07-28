#include "particles/gas/gas_particle.h"

GasParticle::GasParticle(Material element, const std::array<GLubyte, 4>& color)
	: Particle(element, color) {
}
