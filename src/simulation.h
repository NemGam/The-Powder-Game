#ifndef SIMULATION_H
#define SIMULATION_H

#include "sim_matrix.h"

class Simulation
{
public:

	Simulation(int width, int height);

	void Start();
	void Update(float dt);

	SimMatrix& GetMatrix();

private:
	SimMatrix matrix_;
	int width_;
	int height_;
};

#endif // SIMULATION_H
