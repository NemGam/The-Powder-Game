#include "movable_solid_particle.h"
#include "globals.h"

namespace powder_sim
{
	void MovableSolidParticle::Move(SimMatrix& matrix, int x, int y) {

		if (matrix.GetMaterial(x, y - 1) == Material::kAir || matrix.GetMaterial(x, y - 1) == Material::kWater) {
			for (int i = 2; i < kGravity; i++) {
				if (matrix.GetMaterial(x, y - i) == Material::kAir || matrix.GetMaterial(x, y - i) == Material::kWater)
					continue;

				matrix.Swap(x, y, x, y - (i - 1));
				return;
			}

			matrix.Swap(x, y, x, y - 3);
			//Check south

		}
		else if (matrix.GetParticle(x - 1, y - 1)->GetMaterial() == Material::kAir || matrix.GetMaterial(x - 1, y - 1) == Material::kWater) {
			//Check south-west
			matrix.Swap(x, y, x - 1, y - 1);
		}
		else if (matrix.GetParticle(x + 1, y - 1)->GetMaterial() == Material::kAir || matrix.GetMaterial(x + 1, y - 1) == Material::kWater) {
			//Check south-east
			matrix.Swap(x, y, x + 1, y - 1);
		}
		else {
			is_sleeping_ = true;
		}
		//Stop if no possible moves
	}

	MovableSolidParticle::MovableSolidParticle(Material element, const std::array<GLubyte, 4>& color) :
		SolidParticle(element, color) {
	}
}