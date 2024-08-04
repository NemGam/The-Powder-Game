#include "liquid_particle.h"

#include "globals.h"

namespace powder_sim
{
	LiquidParticle::LiquidParticle(Material element, const std::array<GLubyte, 4>& color, int dispersion_rate) :
		Particle(element, color),
		dispersion_rate_(dispersion_rate)
	{}

	void LiquidParticle::Move(SimMatrix& matrix, int x, int y) {
		if (matrix.GetMaterial(x, y - 1) == Material::kAir) { //Check south
			for (int i = 1; i <= kGravity; i++) {
				if (matrix.GetMaterial(x, y - i) == Material::kAir)
					matrix.Swap(x, y - (i - 1), x, y - i);
				else
					break;
			}

		}
		else if (matrix.GetMaterial(x - 1, y) == Material::kAir) { //Check west
			for (int i = 1; i <= dispersion_rate_; i++) {
				if (matrix.GetMaterial(x - i, y) == Material::kAir)
					matrix.Swap(x - (i - 1), y, x - i, y);
				else
					break;
			}
		}
		else if (matrix.GetMaterial(x + 1, y) == Material::kAir) { //Check east
			for (int i = 1; i <= dispersion_rate_; i++) {
				if (matrix.GetMaterial(x + i, y) == Material::kAir)
					matrix.Swap(x + (i - 1), y, x + i, y);
				else
					break;
			}
		}
		else {
			is_sleeping_ = true;
		}
		//Stop if no possible moves
	}
}
