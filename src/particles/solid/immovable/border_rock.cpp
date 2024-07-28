#include "border_rock.h"

#include <iostream>

BorderRock::BorderRock() :
	ImmovableSolidParticle(Material::kBorderRock, {0, 0, 0, 0}) {
}

BorderRock::~BorderRock() {
	std::cout << "BORDER ROCK IS REPLACED!!!!" << '\n';
}

BorderRock* BorderRock::Clone() const {
	return new BorderRock(*this);
}
