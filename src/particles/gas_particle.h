#pragma once
#include "particle.h"
class GasParticle :
    public Particle
{
public:
    void Move(SimMatrix& matrix, int x, int y) override;

protected:
    GasParticle(ElementType element, const std::array<GLubyte, 4>& color);
};

