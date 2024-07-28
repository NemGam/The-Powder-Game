#ifndef PARTICLE_H
#define PARTICLE_H

#include <array>

#include "material.h"
#include "sim_matrix.h"

class Particle {
public:
	Particle() = default;
	

	virtual ~Particle() = default;


	[[nodiscard]] Material GetMaterial() const;
	[[nodiscard]] const std::array<GLubyte, 4>& GetColor() const;
	void SetColor(const std::array<GLubyte, 4>& color);
	void Update(SimMatrix& matrix, int x, int y);
	virtual void Move(SimMatrix& matrix, int x, int y) = 0;
	void WakeUp();
	[[nodiscard]] bool GetUpdateFlag() const;


	static int DEBUG_UPDATED;


	friend class ParticleCreator;

protected:
	Particle(Material element, const std::array<GLubyte, 4>& color);


	[[nodiscard]] virtual Particle* Clone() const = 0;


	bool update_flag_;
	bool is_sleeping_;
	Material element_;
	std::array<GLubyte, 4> color_;
};

#endif // PARTICLE_H
