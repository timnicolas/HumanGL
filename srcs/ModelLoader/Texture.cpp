#include "Texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "lib/stb_image.h"

u_int32_t	textureFromFile(const char *path, const std::string &directory) {
	std::string	filename;
	u_int32_t	textureID;
    int			nrComponents;
    int			width;
    int			height;
	u_char		*data;
	GLenum		format;


	glGenTextures(1, &textureID);

	filename = directory + '/' + std::string(path);
	data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);

	if (data) {
		format = GL_RGB;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, \
		GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else {
		std::cerr << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

    return textureID;
}
