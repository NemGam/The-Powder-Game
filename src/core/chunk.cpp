#include <iostream>


#include "chunk.h"
#include "particle_creator.h"

namespace powder_sim  {
	Chunk::Chunk(int x, int y, int size, SimMatrix* matrix) :
		is_sleeping_next_frame_(true),
		is_sleeping_(false),
		size_(size),
		offset_x_(x * size),
		offset_y_(y * size),
		matrix_(matrix)
	{}

	void Chunk::WakeUp() {
		//std::cout << "Woke up at " << x_ << " " << y_ << '\n';
		is_sleeping_next_frame_ = false;
	}

	void Chunk::Update() {
		is_sleeping_ = is_sleeping_next_frame_;
		is_sleeping_next_frame_ = true;

		if (is_sleeping_) return;
		//std::cout << "Updated at " << x_ << " " << y_ << '\n';

		bool dir = false;
		for (int y = size_ - 1; y > -1; --y) {
			if (dir) {
				for (int x = 0; x < size_; ++x) {
					matrix_->UpdateParticle(offset_x_ + x, offset_y_ + y);
				}
			}
			else {
				for (int x = size_ - 1; x > -1; --x) {
					matrix_->UpdateParticle(offset_x_ + x, offset_y_ + y);
				}
			}
			dir = !dir;
		}
	}

	bool Chunk::IsSleeping() const {
		return is_sleeping_;
	}

	int Chunk::GetSize() const {
		return size_;
	}
}

