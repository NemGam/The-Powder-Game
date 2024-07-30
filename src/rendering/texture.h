#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>
#include <vector>
#include <glad/glad.h>

class Texture {
public:
	//Will generate an empty texture
	Texture(int width, int height);

	//Binds an external data pointer to avoid copying if it updates often.
	//Pass a null pointer to unbind it. Be careful not to remove the data before unbinding.
	void SetDynamicData(const std::vector<GLubyte>* dynamic_data);
	void Draw();
	const std::vector<GLubyte>* GetData() const;
	int GetWidth() const;
	int GetHeight() const;
	unsigned int GetId() const;
private:
	void Initialize();


	unsigned int id_;
	std::string path_;
	int width_;
	int height_;
	const std::vector<GLubyte>* data_;
};

#endif // TEXTURE_H
