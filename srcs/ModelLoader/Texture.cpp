#include "Texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "lib/stb_image.h"

u_int32_t	textureFromFile(const std::string path, const std::string &directory) {
	std::string	filename;
	u_int32_t	textureID;
    int			nrComponents;
    int			width;
    int			height;
	u_char		*data;
	GLenum		format;


	filename = directory + '/' + std::string(path);
	data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);

	if (data) {
		glGenTextures(1, &textureID);
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;
		else {
			std::cout << "Error in component per pixel (" << nrComponents << ")\n";
			throw TextureFailToLoad();
		}

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
		throw TextureFailToLoad();
	}

    return textureID;
}

u_int32_t	textureFromFbx(const aiScene *scene, int loactionId) {
	u_int32_t	textureID;
	int			nrComponents;
	int			width;
	int			height;
	u_char		*data;
	GLenum		format;

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	auto texture = scene->mTextures[loactionId];

	if (texture->mHeight == 0) {
		data = stbi_load_from_memory(reinterpret_cast<unsigned char*>(texture->pcData), \
			texture->mWidth, &width, &height, &nrComponents, 0);
	}
	else {
		data = stbi_load_from_memory(reinterpret_cast<unsigned char*>(texture->pcData), \
			texture->mWidth * texture->mHeight, &width, &height, &nrComponents, 0);
	}

	if (nrComponents == 1) {
		format = GL_RED;
	}
	else if (nrComponents == 3) {
		format = GL_RGB;
	}
	else if (nrComponents == 4) {
		format = GL_RGBA;
	}
	else {
		std::cout << "Error in component per pixel (" << nrComponents << ")\n";
		throw TextureFailToLoad();
	}

	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, \
	GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_image_free(data);

    return textureID;
}
