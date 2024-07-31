#ifndef PARTICLE_CREATOR_H
#define PARTICLE_CREATOR_H

#include <unordered_map>

#include "particles/material.h"
#include "particles/particle.h"

namespace powder_sim
{
	class ParticleCreator
	{
	public:
		ParticleCreator(const ParticleCreator&) = delete;
		ParticleCreator& operator=(const ParticleCreator&) = delete;


		//Returns copy of the particle with the given element
		static Particle* GetParticleByMaterial(Material material, bool randomize_color = true);

	private:
		ParticleCreator();

		~ParticleCreator();


		static ParticleCreator& GetInstance();


		std::unordered_map<Material, Particle*> particles_;
	};
}
#endif // PARTICLE_CREATOR_H
