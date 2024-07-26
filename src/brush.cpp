#include "brush.h"
#include "input_manager.h"
#include "utils.h"
#include "particles/gas/air.h"
#include "particles/solid/movable/sand.h"

Brush::Brush(const Window* window, SimMatrix* matrix) :
	matrix_(matrix),
	window_(window),
	radius_(5)
{}

void Brush::CreateParticles(double x, double y) {
	auto [x_coord, y_coord] = utils::FromWindowToMatrix(window_, matrix_, x, y);

	for (int i = x_coord - radius_; i < x_coord + radius_; i++) {
		for (int j = y_coord - radius_; j < y_coord + radius_; j++) {
			matrix_->SetParticle(new Sand(), i, j);
		}
	}
}

void Brush::EraseParticles(double x, double y) {
	int x_coord = static_cast<int>(x);
	int y_coord = static_cast<int>(y);

	for (int i = x_coord - radius_; i < x_coord + radius_; i++) {
		for (int j = y_coord - radius_; j < y_coord + radius_; j++) {
			matrix_->SetParticle(new Air(), i, j);
		}
	}
}

void Brush::Update() {
	if (InputManager::GetInstance().IsMouseButtonDown(GLFW_MOUSE_BUTTON_1)) {
		auto [x, y] = InputManager::GetInstance().GetMousePosition();
		CreateParticles(x, y);
	}
	else if (InputManager::GetInstance().IsMouseButtonDown(GLFW_MOUSE_BUTTON_2)) {
		auto [x, y] = InputManager::GetInstance().GetMousePosition();
		EraseParticles(x, y);
	}
}
