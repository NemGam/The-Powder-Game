#include <iostream>

#include "brush.h"
#include "core/input_manager.h"
#include "core/utils.h"
#include "core/random.h"

Brush::Brush(const Window* window, SimMatrix* matrix) :
	current_material_(Material::kSand),
	matrix_(matrix),
	window_(window),
	radius_(5)
{}

void Brush::SetMaterial(Material material) {
	//std::cout << "Chosen particle is " << static_cast<int>(particle->GetMaterial()) << '\n';
	current_material_ = material;
}

void Brush::CreateParticles(double x, double y) const {
	auto [x_coord, y_coord] = utils::FromWindowToMatrix(window_, matrix_, x, y);

	for (int i = x_coord - radius_; i <= x_coord + radius_; i++) {
		for (int j = y_coord - radius_; j <= y_coord + radius_; j++) {
			if (random::Random() > 0.5f)
				matrix_->SetParticle(current_material_, i, j);
		}
	}
}

void Brush::EraseParticles(double x, double y) const {
	auto [x_coord, y_coord] = utils::FromWindowToMatrix(window_, matrix_, x, y);

	for (int i = x_coord - radius_; i <= x_coord + radius_; i++) {
		for (int j = y_coord - radius_; j <= y_coord + radius_; j++) {
			matrix_->SetParticle(Material::kAir, i, j);
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

	if (InputManager::IsKeyDown(GLFW_KEY_1)) {
		SetMaterial(Material::kSand);
	}

	if (InputManager::IsKeyDown(GLFW_KEY_2)) {
		SetMaterial(Material::kWater);
	}
}
