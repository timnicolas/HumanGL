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

		std::vector<Mesh>		getMeshes() const;
		std::string				getDirectory() const;
		std::vector<Texture>	getTexturesLoaded() const;
		mat::Mat4				getModelM() const;

		void		draw(Shader &shader);

		class AssimpError : public std::exception {
			public:
				virtual const char* what() const throw();
		};
	private:
		void					loadModel(std::string path);
		void					processNode(aiNode *node, const aiScene *scene);
		Mesh					processMesh(aiMesh *mesh, const aiScene *scene);
		std::vector<Texture>	loadMaterialTextures(aiMaterial *mat, \
		aiTextureType type, TextureT textType);

		void					updateMinMaxPos(mat::Vec3 pos);
		void					calcModelMatrix();

		std::vector<Mesh>		_meshes;
		std::string				_directory;
		std::vector<Texture>	_texturesLoaded;

		mat::Vec3				_minPos;
		mat::Vec3				_maxPos;
		mat::Mat4				_model;
};

#endif
