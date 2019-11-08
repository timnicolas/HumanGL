#ifndef TEXTURE_HPP
# define TEXTURE_HPP

#include <stdexcept>
# include "commonInclude.hpp"
#include "Mesh.hpp"

u_int32_t	textureFromFile(const std::string path, const std::string &directory, \
	bool inSpaceSRGB);
u_int32_t	textureFromFbx(const aiScene *scene, int loactionId, bool inSpaceSRGB);

class TextureFailToLoad : public std::exception {
	public:
		char const * what() const throw() {
			return "failed to load texture";
		}
};

#endif
