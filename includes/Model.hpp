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
		/* bones */
		struct BoneInfo {
			mat::Mat4 boneOffset;
			mat::Mat4 finalTransformation;
			BoneInfo() {
				boneOffset = mat::Mat4();
				finalTransformation = mat::Mat4();
			}
		};

		std::map<std::string, int>	boneMap; // maps a bone name to its index
		BoneInfo	boneInfo[MAX_BONES];  // all bones
		// all datas ready to send to vertex shader (uniform mat4[MAX_BONES])
		float		*boneInfoUniform;
		u_int32_t	actBoneId = 0;
		mat::Mat4	globalTransform;

		void					loadModel(std::string path);
		void					processNode(aiNode *node, const aiScene *scene);
		Mesh					processMesh(aiMesh *mesh, const aiScene *scene);
		std::vector<Texture>	loadMaterialTextures(aiMaterial *mat, \
		aiTextureType type, TextureT textType);
		void					setBonesTransform(aiNode *node, mat::Mat4 parentTransform);

		void					updateMinMaxPos(mat::Vec3 pos);
		void					initScale();
		void					calcModelMatrix();

		std::vector<Mesh>		_meshes;
		std::string				_directory;
		std::vector<Texture>	_texturesLoaded;

		mat::Vec3				_minPos;
		mat::Vec3				_maxPos;
		mat::Mat4				_model;
		float					_modelScale;
};

#endif
