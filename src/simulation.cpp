#include "simulation.h"

#include <functional>
#include <iostream>
#include <thread>

#include "particles/particle.h"

namespace powder_sim
{
	Simulation::Simulation(const Window* window, int width, int height) :
		matrix_(width, height),

		brush_(window, &matrix_),
		width_(width),
		height_(height)
	{}

	void Simulation::Start() {

	}

	void Simulation::UpdatePart(int x, int y, int width, int height) {
		bool dir = false;
		for (int i = height - 1; i >= y; --i) {
			if (dir) {
				for (int j = x; j < width; ++j) {
					matrix_.Update(j, i);
				}
			}
			else {
				for (int j = width - 1; j >= x; --j) {
					matrix_.Update(j, i);
				}
			}

			dir = !dir;
		}
	}


	void Simulation::Update(float dt) {
		brush_.Update();

		constexpr int threads_num = 3;

		//NEW METHOD

		//Odd threads
		std::thread t1([&] { UpdatePart(0, 0, 
			static_cast<int>(static_cast<float>(width_) / threads_num), height_); });

		std::thread t3([&] { UpdatePart(static_cast<int>(width_ *  2.0f / threads_num), 0, 
			static_cast<int>(width_ * 3.0f / threads_num), height_); });
		
		
		t1.join();
		t3.join();
		
		//Even threads
		std::thread t2([&] { UpdatePart(static_cast<int>(static_cast<float>(width_) / threads_num), 0, 
			static_cast<int>(width_ * 2.0f / threads_num), height_); });
		
		t2.join();

		matrix_.FlipUpdateFlag();
	}

	SimMatrix& Simulation::GetMatrix() {
		return matrix_;
	}
}
