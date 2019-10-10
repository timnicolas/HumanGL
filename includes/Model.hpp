#ifndef MODEL_HPP
# define MODEL_HPP

# include "Mesh.hpp"
# include "Texture.hpp"
# include <assimp/Importer.hpp>
# include <assimp/scene.h>
# include <assimp/postprocess.h>
# include <array>

class Model {
	public:
		struct BoneInfo {
			mat::Mat4 boneOffset;
			mat::Mat4 finalTransformation;
			BoneInfo() {
				boneOffset = mat::Mat4();
				finalTransformation = mat::Mat4();
			}
		};

        Model(const char *path);
		Model(Model const &src);
		virtual ~Model();

		Model &operator=(Model const &rhs);

		std::vector<Mesh>		getMeshes() const;
		std::string				getDirectory() const;
		std::vector<Texture>	getTexturesLoaded() const;

		mat::Vec3				getMinPos() const;
		mat::Vec3				getMaxPos() const;
		mat::Mat4				getModel() const;
		float					getModelScale() const;

		std::map<std::string, int>	getBoneMap() const;
		std::array<BoneInfo, MAX_BONES>	getBoneInfo() const;
		float					*getBoneInfoUniform() const;
		u_int32_t				getActBoneId() const;
		mat::Mat4				getGlobalTransform() const;


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

		std::map<std::string, int>	_boneMap; // maps a bone name to its index
		std::array<BoneInfo, MAX_BONES>	_boneInfo;

		// all datas ready to send to vertex shader (uniform mat4[MAX_BONES])
		float					*_boneInfoUniform;
		u_int32_t				_actBoneId = 0;
		mat::Mat4				_globalTransform;
};

#endif
