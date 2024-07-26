#ifndef UTILS_H
#define UTILS_H
#include "sim_matrix.h"
#include "window.h"

namespace utils {

	std::tuple<int, int> FromWindowToMatrix(const Window* window, const SimMatrix* matrix, double x, double y);
}


#endif // UTILS_H
