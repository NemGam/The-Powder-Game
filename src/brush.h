#ifndef BRUSH_H
#define BRUSH_H

#include "sim_matrix.h"
#include "rendering/window.h"
#include "particles/material.h"

namespace powder_sim
{
	class Brush {
	public:
		Brush(const Window* window, SimMatrix* matrix);

		void SetRadius(int radius);
		void SetMaterial(Material material);
		void Update();

	private:

		//Creates a square of particles with the current radius and material.
		//Internally uses Fill().
		void CreateParticles(double x, double y) const;

		//Creates a square of Air particles with the current radius.
		//Internally uses Fill().
		void EraseParticles(double x, double y) const;

		//Fills the square area with particles of a given material, where x and y are
		//the coordinates of its center. Does not replace already present particles
		//(any particle that is not Air) unless specified by the force_replace.
		void Fill(Material material, double x, double y, bool force_replace = false) const;

		Material current_material_;
		SimMatrix* matrix_;
		const Window* window_;
		int radius_;
	};
}

#endif // BRUSH_H
