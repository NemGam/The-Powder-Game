#include <iostream>

#include "brush.h"
#include "core/input_manager.h"
#include "core/utils.h"

namespace powder_sim
{
	Brush::Brush(const Window* window, SimMatrix* matrix) :
		current_material_(Material::kSand),
		matrix_(matrix),
		window_(window),
		radius_(5)
	{}

	void Brush::SetRadius(int radius) {
		if (radius_ <= 0) return;

		radius_ = radius;
	}

	void Brush::SetMaterial(Material material) {
		current_material_ = material;
	}

	void Brush::CreateParticles(double x, double y) const {
		Fill(current_material_, x, y);
	}

	void Brush::EraseParticles(double x, double y) const {
		Fill(Material::kAir, x, y, true);
	}

	void Brush::Fill(Material material, double x, double y, bool force_replace) const {
		auto [x_coord, y_coord] = utils::FromWindowToMatrix(window_, matrix_, x, y);
		int minI = std::max(x_coord - radius_, 0);
		int maxI = std::min(x_coord + radius_, matrix_->GetWidth() - 1);
		int minJ = std::max(y_coord - radius_, 0);
		int maxJ = std::min(y_coord + radius_, matrix_->GetHeight() - 1);

		for (int i = minI; i <= maxI; i++) {
			for (int j = minJ; j <= maxJ; j++) {
				if (force_replace || matrix_->GetMaterial(i, j) == Material::kAir) {
					matrix_->SetParticle(material, i, j);
				}
				//if (random::Random() <= chance)
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

		if (InputManager::IsKeyDown(GLFW_KEY_3)) {
			SetMaterial(Material::kStone);
		}
	}
}
