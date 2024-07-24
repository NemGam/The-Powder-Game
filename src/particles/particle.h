#ifndef PARTICLE_H
#define PARTICLE_H

#include <array>
#include "element_type.h"
#include "../sim_matrix.h"

class Particle
{
public:
	Particle() = default;

	virtual ~Particle() = default;

	ElementType GetElement() const;

	std::array<GLubyte, 4>& GetColor();

	void Update(SimMatrix& matrix, int x, int y);

	void virtual Move(SimMatrix& matrix, int x, int y) = 0;


protected:
	Particle(ElementType element, const std::array<GLubyte, 4>& color);

	ElementType element_;
	std::array<GLubyte, 4> color_;
};

#endif // PARTICLE_H
