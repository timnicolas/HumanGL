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

        Model(const char *path, Shader &shader, Shader &cubeShader, \
		float const &animationSpeed, float const &dtTime);
		Model(Model const &src);
		virtual ~Model();

		Model &operator=(Model const &rhs);

		Shader					&getShader() const;
		Shader					&getCubeShader() const;
		std::vector<Mesh>		getMeshes() const;
		std::string				getDirectory() const;
		std::vector<Texture>	getTexturesLoaded() const;

		mat::Vec3				getMinPos() const;
		mat::Vec3				getMaxPos() const;
		mat::Mat4				&getModel();
		mat::Mat4				&getModelScale();
		const mat::Mat4			&getModel() const;
		const mat::Mat4			&getModelScale() const;
		float const				&getAnimationSpeed() const;
		float const				&getDtTime() const;

		bool					&isDrawMesh();
		bool					isDrawMesh() const;
		bool					&isDrawCube();
		bool					isDrawCube() const;

		std::map<std::string, int>	getBoneMap() const;
		std::array<BoneInfo, MAX_BONES>	getBoneInfo() const;
		std::array<float, MAX_BONES * 16>	getBoneInfoUniform() const;
		std::array<float, MAX_BONES * 3>	getBonePosUniform() const;
		u_int32_t				getActBoneId() const;
		mat::Mat4				getGlobalTransform() const;
		mat::Mat4				getGlobalInverseTransform() const;
		void					loadNextAnimation();

		u_int32_t				getCubeVbo() const;
		u_int32_t				getCubeVao() const;

		void		draw();

		static const float		_cubeData[];

		class AssimpError : public std::exception {
			public:
				virtual const char* what() const throw();
		};
		class AnimationError : public AssimpError {
			public:
				AnimationError(std::string const &msg) : _msg(msg) {}
				virtual const char * what() const throw() {
					return _msg.c_str();
				}
			private:
				std::string _msg;
		};
	private:
		void					loadModel(std::string path);
		void					processNode(aiNode *node, const aiScene *scene);
		Mesh					processMesh(aiMesh *mesh, const aiScene *scene);
		std::vector<Texture>	loadMaterialTextures(const aiScene *scene, aiMaterial *mat, aiTextureType type, TextureT textType);
		void					setBonesTransform(float animationTime, aiNode *node, const aiScene *scene, mat::Mat4 parentTransform);
		void					setBonesPos(aiNode *node, mat::Mat4 parentTransform);
		const aiNodeAnim*		findNodeAnim(const aiAnimation* animation, const std::string nodeName);
		void					calcInterpolatedPosition(mat::Vec3 &out, float animationTime, const aiNodeAnim* nodeAnim);
		void					calcInterpolatedRotation(mat::Quaternion &out, float animationTime, const aiNodeAnim* nodeAnim);
		void					calcInterpolatedScaling(mat::Vec3 &out, float animationTime, const aiNodeAnim* nodeAnim);
		u_int32_t				findPosition(float animationTime, const aiNodeAnim* nodeAnim);
		u_int32_t				findRotation(float animationTime, const aiNodeAnim* nodeAnim);
		u_int32_t				findScaling(float animationTime, const aiNodeAnim* nodeAnim);
		void					sendBones(int shaderId);

		void					updateMinMaxPos(mat::Vec3 pos);
		void					calcModelMatrix();
		void					sendCubeData();

		Shader					&_shader;
		Shader					&_cubeShader;
		std::vector<Mesh>		_meshes;
		std::string				_directory;
		std::vector<Texture>	_texturesLoaded;

		mat::Vec3				_minPos;
		mat::Vec3				_maxPos;
		mat::Mat4				_model;  // position in real world
		mat::Mat4				_modelScale;
		float const				&_animationSpeed;
		float					_animationTime;
		float const				&_dtTime;

		std::map<std::string, int>	_boneMap; // maps a bone name to its index
		std::array<BoneInfo, MAX_BONES>	_boneInfo;
		std::array<mat::Vec3, MAX_BONES> _bonePos;

		// all datas ready to send to vertex shader (uniform mat4[MAX_BONES])
		std::array<float, MAX_BONES * 16>	_boneInfoUniform;
		std::array<float, MAX_BONES * 3>	_bonePosUniform;

		u_int32_t				_actBoneId = 0;
		mat::Mat4				_globalTransform;
		mat::Mat4				_globalInverseTransform;
		aiAnimation				*_curAnimation;
		uint32_t				_curAnimationId;
		bool					_isAnimated;
		const aiScene			*_scene;
		Assimp::Importer		_importer;

		u_int32_t				_cubeVbo;
		u_int32_t				_cubeVao;

		bool					_drawMesh;
		bool					_drawCube;
};

#endif
