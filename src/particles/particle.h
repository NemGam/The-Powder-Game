#ifndef PARTICLE_H
#define PARTICLE_H

#include <array>

#include "material.h"
#include "sim_matrix.h"

namespace powder_sim
{
	class SimMatrix;

	class Particle {
	public:
		Particle() = default;
		Particle(const Particle&) = default;
		Particle(Particle&&) = default;
		Particle& operator=(const Particle&) = default;
		Particle& operator=(Particle&&) = default;


		virtual ~Particle() = default;


		[[nodiscard]] Material GetMaterial() const;
		//Returns color in the form of RGBA, where every element is in between 0 and 255. A is not used.
		[[nodiscard]] const std::array<GLubyte, 4>& GetColor() const;
		[[nodiscard]] int GetLastUpdateNumber() const;
		void SetColor(const std::array<GLubyte, 4>& color);
		void Update(SimMatrix& matrix, int x, int y, int update_number);
		void WakeUp();
		virtual void Move(SimMatrix& matrix, int x, int y) = 0;


		static int DEBUG_UPDATED_THIS_FRAME;


		friend class ParticleCreator;

	protected:
		Particle(Material element, const std::array<GLubyte, 4>& color);


		[[nodiscard]] virtual Particle* Clone() const = 0;

		//The last frame this particle was actually updated.
		int last_update_number_;
		bool is_sleeping_;
		Material element_;
		std::array<GLubyte, 4> color_;
	};
}
#endif // PARTICLE_H
