#include "simulation.h"

#include <iostream>
#include <thread>

#include "globals.h"

namespace powder_sim
{
	Simulation::Simulation(const Window* window, int width, int height) :
		matrix_(width, height, kChunkSize),

		brush_(window, &matrix_),
		width_(width),
		height_(height)
	{}

	void Simulation::Start() {
		//Implement thread pooling? Should improve the performance
	}

	void Simulation::UpdatePart(int x, int y, int width, int height) {
		for (int i = height - 1; i >= y; --i) {
			for (int j = width - 1; j >= x; --j) {
				matrix_.UpdateChunk(j, i);
			}
		}
	}


	void Simulation::Update(float dt) {
		brush_.Update();


		//Separating threads to avoid any race conditions.
		//Each thread will process one quadrant of the matrix.

		const int x_chunks_num = width_ / kChunkSize;
		const int y_chunks_num = width_ / kChunkSize;

		//Bottom-left
		std::thread t1([&] { UpdatePart(0, 0, x_chunks_num / 2, y_chunks_num / 2); }); 

		//Bottom-right
		std::thread t2([&] { UpdatePart(x_chunks_num / 2, 0, x_chunks_num, y_chunks_num / 2); }); 

		//Top-left
		std::thread t3([&] { UpdatePart(0, y_chunks_num / 2, x_chunks_num / 2, y_chunks_num); }); 

		//Top-right
		std::thread t4([&] { UpdatePart(x_chunks_num / 2, y_chunks_num / 2, x_chunks_num, y_chunks_num); }); 
		
		t1.join();
		t2.join();
		t3.join();
		t4.join();

		matrix_.IncrementUpdateNumber();
	}

	SimMatrix& Simulation::GetMatrix() {
		return matrix_;
	}
}
