#ifndef TEXTURE_HPP
# define TEXTURE_HPP

#include <stdexcept>
# include "commonInclude.hpp"
#include "Mesh.hpp"

u_int32_t	textureFromFile(const char *path, const std::string &directory);
void		textureFromFbx(const aiScene *scene, std::vector<Texture> &textures, TextureT textType);

class TextureFailToLoad : public std::exception {
	public:
		char const * what() const throw() {
			return "failed to load texture";
		}
};

#endif
