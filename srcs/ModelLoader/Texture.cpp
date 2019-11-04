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


	filename = directory + '/' + std::string(path);
	data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);

	if (data) {
		glGenTextures(1, &textureID);
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
		throw TextureFailToLoad();
	}

    return textureID;
}

void		textureFromFbx(const aiScene *scene, std::vector<Texture> &textures) {
	Texture			texture;
	auto			textureIds = new GLuint[scene->mNumTextures];
	aiString		str;
	unsigned char	*image_data = nullptr;
	int				components_per_pixel;
	int				width;
	int				height;

	glGenTextures(scene->mNumTextures, textureIds);
	// upload textures
	for(size_t ti = 0; ti < scene->mNumTextures; ti++) {
		glGenTextures(1, &textureIds[ti]);
		glBindTexture(GL_TEXTURE_2D, textureIds[ti]);
		auto texture_ = scene->mTextures[ti];
		if (texture_->mHeight == 0) {
			image_data = stbi_load_from_memory(reinterpret_cast<unsigned char*>(texture_->pcData), texture_->mWidth, &width, &height, &components_per_pixel, 0);
		}
		else {
			image_data = stbi_load_from_memory(reinterpret_cast<unsigned char*>(texture_->pcData), texture_->mWidth * texture_->mHeight, &width, &height, &components_per_pixel, 0);
		}

		GLenum format;
		if (components_per_pixel == 1) {
			format = GL_RED;
		}
		else if (components_per_pixel == 3) {
			format = GL_RGB;
		}
		else if (components_per_pixel == 4) {
			format = GL_RGBA;
		}
		else {
			std::cout << "Error in component per pixel (" << components_per_pixel << ")\n";
			throw TextureFailToLoad();
		}
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0,
			format, GL_UNSIGNED_BYTE, image_data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		texture.id = textureIds[ti];
		texture.path = str.C_Str();
		textures.push_back(texture);
	}
}
