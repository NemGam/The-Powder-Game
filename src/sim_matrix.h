#ifndef SIM_MATRIX_H
#define SIM_MATRIX_H
#include <memory>
#include <vector>
#include <glad/glad.h>

class Particle;

class SimMatrix
{
public:
	SimMatrix(int width, int height);


	~SimMatrix();


	void Swap(int x1, int y1, int x2, int y2);
	void Update(int x, int y);

	void SetParticle(Particle* particle, int x, int y);
	Particle* GetParticle(int x, int y) const;

	const std::vector<GLubyte>* GetColorData() const;


private:
	int width_;
	int height_;
	std::unique_ptr<Particle> border_particle_;
	std::vector<std::vector<Particle*>> matrix_;
	std::vector<GLubyte> color_data_;


	//Update color data
	void ChangeColorAt(int x, int y, std::array<GLubyte, 4> color);
	void SwapColorData(int x1, int y1, int x2, int y2);
	int GetColorIndexFromCoordinates(int x, int y) const;
	bool IsInBounds(int x, int y) const;

};

#endif // SIM_MATRIX_H
