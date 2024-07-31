#ifndef VERTEX_H
#define VERTEX_H
#include <array>

namespace powder_sim
{
	struct Vertex {
		Vertex(std::array<float, 2> position, std::array<float, 2> texture_coords);
		std::array<float, 2> position;
		std::array<float, 2> texture_coordinates;
	};
}
#endif // VERTEX_H
