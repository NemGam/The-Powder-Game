#pragma once
#include "solid_particle.h"
class ImmovableSolidParticle :
    public SolidParticle
{
public:
    void Move(SimMatrix& matrix, int x, int y) final;

protected:
    ImmovableSolidParticle(ElementType element, const std::array<GLubyte, 4>& color);
};

