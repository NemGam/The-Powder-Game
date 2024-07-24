#ifndef SAND_PARTICLE_H
#define SAND_PARTICLE_H
#include "../../movable_solid_particle.h"
class Sand final :
    public MovableSolidParticle
{
public:
	Sand();


	void Move(SimMatrix& matrix, int x, int y) override;

};

#endif // SAND_PARTICLE_H
