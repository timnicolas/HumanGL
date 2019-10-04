#ifndef MODEL_HPP
# define MODEL_HPP

# include "Mesh.hpp"
# include "Texture.hpp"
# include <assimp/Importer.hpp>
# include <assimp/scene.h>
# include <assimp/postprocess.h>

class Model {
	public:
        Model(char *path);
		Model(Model const &src);
		virtual ~Model();

		Model &operator=(Model const &rhs);

		void Draw(Shader shader);
	private:
		void	loadModel(std::string path);
		void	processNode(aiNode *node, const aiScene *scene);
		Mesh	processMesh(aiMesh *mesh, const aiScene *scene);
		std::vector<Texture>	loadMaterialTextures(aiMaterial *mat, aiTextureType type, TextureT textType);

		std::vector<Mesh>		meshes;
		std::string				directory;
		std::vector<Texture>	textures_loaded;
};

#endif
