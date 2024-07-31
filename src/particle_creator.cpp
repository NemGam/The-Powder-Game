#include "particle_creator.h"

#include <algorithm>

#include "particles.h"
#include "core/random.h"
#include "particles/solid/immovable/border_rock.h"

namespace powder_sim
{
	Particle* ParticleCreator::GetParticleByMaterial(Material material, bool randomize_color) {
		Particle* particle = GetInstance().particles_[material]->Clone();
		if (randomize_color) {
			auto color = particle->GetColor();
			for (int i = 0; i < 3; i++)
				color[i] = std::clamp(color[i] + static_cast<int>(random::RandomUnit() * 15), 0, 255);
			particle->SetColor(color);
		}
		return particle;
	}

	ParticleCreator::ParticleCreator() {
		particles_ = {
			{Material::kAir, new Air()},
			{Material::kBorderRock, new BorderRock()},
			{Material::kSand, new Sand()},
			{Material::kStone, new Stone()},
			{Material::kWater, new Water()},
		};
	}

	ParticleCreator::~ParticleCreator() {
		for (auto it = particles_.begin(); it != particles_.end(); ++it) {
			delete it->second;
		}
	}

	ParticleCreator& ParticleCreator::GetInstance() {
		static ParticleCreator instance;
		return instance;
	}
}
