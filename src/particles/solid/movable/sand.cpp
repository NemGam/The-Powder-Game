#include "sand.h"


Sand::Sand() :
	MovableSolidParticle(ElementType::kSand, { 252, 165, 3, 0})
{}

void Sand::Move(SimMatrix& matrix, int x, int y) {
	if (matrix.GetParticle(x, y - 1)->GetElement() == ElementType::kAir) { //Check south
		matrix.Swap(x, y, x, y - 1);
	}
	else if (matrix.GetParticle(x - 1, y - 1)->GetElement() == ElementType::kAir) { //Check south-west
		matrix.Swap(x, y, x - 1, y - 1);
	}
	else if (matrix.GetParticle(x + 1, y - 1)->GetElement() == ElementType::kAir) { //Check south-east
		matrix.Swap(x, y, x + 1, y - 1);
	}
	//Stop if no possible moves
}
