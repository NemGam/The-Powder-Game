#ifndef BRUSH_H
#define BRUSH_H

#include <memory>

#include "sim_matrix.h"
#include "core/window.h"
#include "particles/material.h"

class Brush {
public:
	Brush(const Window* window, SimMatrix* matrix);


	void SetMaterial(Material material);
	void Update();

private:
	void CreateParticles(double x, double y) const;
	void EraseParticles(double x, double y) const;

	Material current_material_;
	SimMatrix* matrix_;
	const Window* window_;
	int radius_;
};

#endif // BRUSH_H
