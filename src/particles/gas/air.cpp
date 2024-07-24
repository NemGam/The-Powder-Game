#include "air.h"


Air::Air() :
	GasParticle(ElementType::kAir, {0, 0, 0, 0})
{} 

void Air::Move(SimMatrix& matrix, int x, int y) {
	return;
}
