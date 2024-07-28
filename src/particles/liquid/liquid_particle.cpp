#include "liquid_particle.h"


LiquidParticle::LiquidParticle(Material element, const std::array<GLubyte, 4>& color) :
	Particle(element, color)
{}

void LiquidParticle::Move(SimMatrix& matrix, int x, int y) {
	if (matrix.GetParticle(x, y - 1)->GetMaterial() == Material::kAir) { //Check south
		matrix.Swap(x, y, x, y - 1);
	}
	else if (matrix.GetParticle(x - 1, y - 1)->GetMaterial() == Material::kAir) { //Check south-west
		matrix.Swap(x, y, x - 1, y - 1);
	} 
	else if (matrix.GetParticle(x + 1, y - 1)->GetMaterial() == Material::kAir) { //Check south-east
		matrix.Swap(x, y, x + 1, y - 1);
	}
	else if (matrix.GetParticle(x - 1, y)->GetMaterial() == Material::kAir) { //Check west
		matrix.Swap(x, y, x - 1, y);
	}
	else if (matrix.GetParticle(x + 1, y)->GetMaterial() == Material::kAir) { //Check east
		matrix.Swap(x, y, x + 1, y);
	}
	//Stop if no possible moves
}
