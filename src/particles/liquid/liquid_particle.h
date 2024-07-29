#ifndef LIQUID_PARTICLE_H
#define LIQUID_PARTICLE_H

#include "particles/particle.h"

class LiquidParticle
	: public Particle
{
public:
	void Move(SimMatrix& matrix, int x, int y) override;

protected:
	LiquidParticle(Material element, const std::array<GLubyte, 4>& color, int dispersion_rate);


	int dispersion_rate_;
};

#endif // LIQUID_PARTICLE_H
