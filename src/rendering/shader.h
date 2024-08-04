#ifndef SHADER_H
#define SHADER_H
#include <string>

namespace powder_sim
{
	class Shader
	{
	public:
		explicit Shader(const std::string& filepath);


		[[nodiscard]] unsigned int GetId() const;

	private:
		struct ShaderSource {
			std::string vertex;
			std::string fragment;
		};


		unsigned int id_;
		static unsigned int CreateShader(const std::string& vertex_shader, const std::string& fragment_shader);
		static unsigned int CompileShader(unsigned int type, const std::string& source);
		static ShaderSource ParseShader(const std::string& filepath);
	};
}
#endif // SHADER_H
