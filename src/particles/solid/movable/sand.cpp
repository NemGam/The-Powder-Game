#include "sand.h"


Sand::Sand() :
	MovableSolidParticle(Material::kSand, {252, 165, 3, 0}) {
}

Sand* Sand::Clone() const {
	return new Sand(*this);
}

void Sand::Move(SimMatrix& matrix, int x, int y) {
	if (matrix.GetParticle(x, y - 1)->GetElement() == Material::kAir) {
		//Check south
		matrix.Swap(x, y, x, y - 1);
	}
	else if (matrix.GetParticle(x - 1, y - 1)->GetElement() == Material::kAir) {
		//Check south-west
		matrix.Swap(x, y, x - 1, y - 1);
	}
	else if (matrix.GetParticle(x + 1, y - 1)->GetElement() == Material::kAir) {
		//Check south-east
		matrix.Swap(x, y, x + 1, y - 1);
	}
	//Stop if no possible moves
}
