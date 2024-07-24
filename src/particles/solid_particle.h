#ifndef SOLID_PARTICLE_H
#define SOLID_PARTICLE_H

#include "particle.h"

class SolidParticle :
    public Particle
{
public:
    void Move(SimMatrix& matrix, int x, int y) override;

protected:
    SolidParticle(ElementType element, const std::array<GLubyte, 4>& color);
};

#endif // SOLID_PARTICLE_H
