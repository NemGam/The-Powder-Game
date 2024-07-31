#include "random.h"

#include <iostream>
#include <ostream>

#include "xoshiro128p.h"

namespace powder_sim
{
	namespace random {
		float Random() {
			uint32_t num = next();

			return static_cast<float>(num) / static_cast<float>(kUintMax);
		}

		float RandomUnit() {
			return Random() * 2 - 1;
		}
	}
}
