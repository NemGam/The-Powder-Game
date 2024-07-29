#include "liquid_particle.h"


LiquidParticle::LiquidParticle(Material element, const std::array<GLubyte, 4>& color, int dispersion_rate) :
	Particle(element, color),
	dispersion_rate_(dispersion_rate)
{}

void LiquidParticle::Move(SimMatrix& matrix, int x, int y) {
	if (matrix.GetMaterial(x, y - 1) == Material::kAir) { //Check south
		matrix.Swap(x, y, x, y - 1);
	}
	//else if (matrix.GetParticle(x - 1, y - 1)->GetMaterial() == Material::kAir) { //Check south-west
	//	matrix.Swap(x, y, x - 1, y - 1);
	//} 
	//else if (matrix.GetParticle(x + 1, y - 1)->GetMaterial() == Material::kAir) { //Check south-east
	//	matrix.Swap(x, y, x + 1, y - 1);
	//}
	else if (matrix.GetMaterial(x - 1, y) == Material::kAir) { //Check west
		for(int i = 2; i <= dispersion_rate_; i++) {
			if (matrix.GetMaterial(x - i, y) == Material::kAir)
				continue;

			matrix.Swap(x, y, x - (i - 1), y);
			return;
		}

		matrix.Swap(x, y, x - 1, y);
		
	}
	else if (matrix.GetMaterial(x + 1, y) == Material::kAir) { //Check east
		for (int i = 2; i <= dispersion_rate_; i++) {
			if (matrix.GetMaterial(x + i, y) == Material::kAir)
				continue;

			matrix.Swap(x, y, x + (i - 1), y);
			return;
		}

		matrix.Swap(x, y, x + 1, y);
	}
	else {
		is_sleeping_ = true;
	}
	//Stop if no possible moves
}
