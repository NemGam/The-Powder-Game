#include "movable_solid_particle.h"
#include "globals.h"
#include "core/random.h"

namespace powder_sim
{
	void MovableSolidParticle::Move(SimMatrix& matrix, int x, int y) {

		//Check south
		if (matrix.GetMaterial(x, y - 1) == Material::kAir || matrix.GetMaterial(x, y - 1) == Material::kWater) {
			// for (int i = 2; i <= kGravity; i++) {
			// 	if (matrix.GetMaterial(x, y - i) == Material::kAir)
			// 		continue;
			//
			// 	matrix.Swap(x, y, x, y - (i - 1));
			// 	return;
			// }
			//
			// matrix.Swap(x, y, x, y - kGravity);
			for (int i = 1; i <= kGravity; i++) {
				if (matrix.GetMaterial(x, y - i) == Material::kAir || matrix.GetMaterial(x, y - i) == Material::kWater)
					matrix.Swap(x, y - (i - 1), x, y - i);
				else
					break;
				
			}
			return;
		}
		//Check sides
		Material leftM = matrix.GetMaterial(x - 1, y - 1);
		Material rightM = matrix.GetMaterial(x + 1, y - 1);
		bool left = (leftM == Material::kAir) || (leftM == Material::kWater);
		bool right = (rightM == Material::kAir) || (rightM == Material::kWater);

		if (left && right) {
			if (random::RandomUnit() <= 0.5) {
				matrix.Swap(x, y, x - 1, y - 1);
			}
			else {
				matrix.Swap(x, y, x + 1, y - 1);
			}
			return;
		}

		if (left) {
			matrix.Swap(x, y, x - 1, y - 1);
			return;
		}

		if (right){
			matrix.Swap(x, y, x + 1, y - 1);
			return;
		}


		//Stop if no possible moves
		is_sleeping_ = true;
	}

	MovableSolidParticle::MovableSolidParticle(Material element, const std::array<GLubyte, 4>& color) :
		SolidParticle(element, color) {
	}
}
