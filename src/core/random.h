#ifndef RANDOM_H
#define RANDOM_H
#include <cstdint>


namespace random {
	constexpr uint32_t kUintMax = static_cast<uint32_t>(-1);

	//Generates a random number from 0 to 1 inclusive.
	float Random();
}

#endif // RANDOM_H
