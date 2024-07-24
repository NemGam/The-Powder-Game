#ifndef MOVABLE_SOLID_PARTICLE_H
#define MOVABLE_SOLID_PARTICLE_H
#include "solid_particle.h"

class MovableSolidParticle :
    public SolidParticle
{
public:
	void Move(SimMatrix& matrix, int x, int y) override;

protected:
	MovableSolidParticle(ElementType element, const std::array<GLubyte, 4>& color);
};

#endif // MOVABLE_SOLID_PARTICLE_H
