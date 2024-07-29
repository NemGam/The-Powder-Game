#ifndef ROCK_H
#define ROCK_H

#include "particles/solid/immovable/immovable_solid_particle.h"

class Stone :
    public ImmovableSolidParticle
{
public:
    Stone();


    Stone* Clone() const override;
};

#endif // ROCK_H
