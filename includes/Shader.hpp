#ifndef SHADER_HPP
# define SHADER_HPP

# define GLFW_INCLUDE_GLCOREARB
# include <GLFW/glfw3.h>
# include <string>
# include <iostream>

class Shader {
	public:
		Shader(const char *vertexPath, const char *fragmentPath, \
		const char *geometryPath = nullptr);
		Shader(Shader const &src);
		virtual ~Shader();

		Shader &operator=(Shader const &rhs);

		void	use();
		void	setBool(const std::string &name, bool value) const;
		void	setInt(const std::string &name, int value) const;
		void	setFloat(const std::string &name, float value) const;
		void	setVec2(const std::string &name, float x, float y) const;
		void	setVec3(const std::string &name, float x, float y, float z) const;
		void	setVec4(const std::string &name, float x, float y, float z, float w);
		// need to add matrix uniform functions when created

		u_int32_t	id;
	private:
};

#endif
