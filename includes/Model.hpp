#ifndef MODEL_HPP
# define MODEL_HPP

# include "Mesh.hpp"
# include "Texture.hpp"
# include <assimp/Importer.hpp>
# include <assimp/scene.h>
# include <assimp/postprocess.h>

class Model {
	public:
        Model(const char *path);
		Model(Model const &src);
		virtual ~Model();

		Model &operator=(Model const &rhs);

		void draw(Shader &shader);

		class AssimpError : public std::exception {
			public:
				virtual const char* what() const throw();
		};
	private:
		void	loadModel(std::string path);
		void	processNode(aiNode *node, const aiScene *scene);
		Mesh	processMesh(aiMesh *mesh, const aiScene *scene);
		std::vector<Texture>	loadMaterialTextures(aiMaterial *mat, aiTextureType type, TextureT textType);

		std::vector<Mesh>		meshes;
		std::string				directory;
		std::vector<Texture>	texturesLoaded;
};

#endif
