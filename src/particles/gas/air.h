#ifndef AIR_H
#define AIR_H

#include "particles/gas/gas_particle.h"

class Air final :
	public GasParticle
{
public:
	Air();

	Air* Clone() const override;

	void Move(SimMatrix& matrix, int x, int y) override;
};

#endif // AIR_H
