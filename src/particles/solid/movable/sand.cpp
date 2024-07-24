#include "sand.h"

#include <iostream>

Sand::Sand() :
	MovableSolidParticle(ElementType::kSand, { 252, 165, 3, 0})
{
}

void Sand::Move(SimMatrix& matrix, int x, int y) {
	if (matrix.GetParticle(x, y - 1)->GetElement() == ElementType::kAir) {
		matrix.Swap(x, y, x, y - 1);
	}
}
