#include "utils.h"

namespace utils {
	std::tuple<int, int> FromWindowToMatrix(const Window* window, const SimMatrix* matrix, double x, double y) {

		float x_ratio = static_cast<float>(matrix->GetWidth()) / static_cast<float>(window->GetWidth());
		float y_ratio = static_cast<float>(matrix->GetHeight()) / static_cast<float>(window->GetHeight());

		return { static_cast<int>(x * x_ratio), static_cast<int>(y * y_ratio) };
	}
}

