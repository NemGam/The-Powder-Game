#include "particle_creator.h"
#include "particles.h"
#include "particles/solid/immovable/border_rock.h"

Particle* ParticleCreator::GetParticleByMaterial(Material material) {
	return GetInstance().particles_[material]->Clone();
}

ParticleCreator::ParticleCreator() {
	particles_ = {
		{Material::kAir, new Air()},
		{Material::kBorderRock, new BorderRock()},
		{Material::kSand, new Sand()},
		//{Material::kStone, new Stone()},
		{Material::kWater, new Water()},
	};
}

ParticleCreator::~ParticleCreator() {
	for(auto it = particles_.begin(); it != particles_.end(); ++it) {
		delete it->second;
	}
}

ParticleCreator& ParticleCreator::GetInstance() {
	static ParticleCreator instance;
	return instance;
}
