#include <array>
#include <cstring>

#include "particle.h"


namespace powder_sim
{
	int Particle::DEBUG_UPDATED_THIS_FRAME;

	Material Particle::GetMaterial() const {
		return element_;
	}

	const std::array<GLubyte, 4>& Particle::GetColor() const {
		return color_;
	}

	void Particle::SetColor(const std::array<GLubyte, 4>& color) {
		std::memcpy(color_.data(), color.data(), sizeof(GLubyte) * color.size());
	}


	void Particle::Update(SimMatrix& matrix, int x, int y, int update_number) {
		if (update_number == last_update_number_) return;

		if (!is_sleeping_) {
			DEBUG_UPDATED_THIS_FRAME++;
			matrix.WakeUpChunk(x, y);
			Move(matrix, x, y);
			last_update_number_ = update_number;
		}
	}

	void Particle::WakeUp() {
		is_sleeping_ = false;
	}

	int Particle::GetLastUpdateNumber() const {
		return last_update_number_;
	}

	Particle::Particle(Material element, const std::array<GLubyte, 4>& color) :
		last_update_number_(-1),
		is_sleeping_(false),
		element_(element),
		color_{ color }
	{}
}
