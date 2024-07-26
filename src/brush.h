#ifndef BRUSH_H
#define BRUSH_H
#include "sim_matrix.h"
#include "window.h"

class Brush
{
public:
	Brush(const Window* window, SimMatrix* matrix);


	void Update();

private:
	void CreateParticles(double x, double y);
	void EraseParticles(double x, double y);

	SimMatrix* matrix_;
	const Window* window_;
	int radius_;
};

#endif // BRUSH_H
