#include <array>
#include "particle.h"

int Particle::DEBUG_UPDATED;

Material Particle::GetMaterial() const {
	return element_;
}

const std::array<GLubyte, 4>& Particle::GetColor() const{
	return color_;
}

void Particle::SetColor(const std::array<GLubyte, 4>& color) {
	color_[0] = color[0];
	color_[1] = color[1];
	color_[2] = color[2];
	color_[3] = color[3];
}


void Particle::Update(SimMatrix& matrix, int x, int y) {
	if (!is_sleeping_) {
		DEBUG_UPDATED++;
		Move(matrix, x, y);
		update_flag_ = !update_flag_;
	}
		
}

void Particle::WakeUp() {
	is_sleeping_ = false;
}

bool Particle::GetUpdateFlag() const {
	return update_flag_;
}

Particle::Particle(Material element, const std::array<GLubyte, 4>& color) :
	update_flag_(false),
	is_sleeping_(false),
	element_(element),
	color_{color}
{}
