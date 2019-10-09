#include "Model.hpp"
#include <limits>

Model::Model(const char *path)
: _minPos(std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max()),
  _maxPos(std::numeric_limits<float>::min(), std::numeric_limits<float>::min(), std::numeric_limits<float>::min()),
  _model(mat::Mat4(1.0f)) {
	loadModel(path);
	calcModelMatrix();
}

Model::Model(Model const &src) {
	*this = src;
}

Model::~Model() {
	free(boneInfoUniform);
}

Model &Model::operator=(Model const &rhs) {
	if (this != &rhs) {
		_meshes = rhs.getMeshes();
		_directory = rhs.getDirectory();
		_texturesLoaded = rhs.getTexturesLoaded();
	}
	return *this;
}

void	Model::draw(Shader &shader) {
	glUniformMatrix4fv(glGetUniformLocation(shader.id, "bones"), MAX_BONES, GL_TRUE, boneInfoUniform);
	for (auto &mesh : _meshes)
		mesh.draw(shader);
}

void	Model::loadModel(std::string path) {
	Assimp::Importer	import;
	const aiScene		*scene;

	scene = import.ReadFile(path, \
	aiProcess_Triangulate | \
	aiProcess_FlipUVs | \
	aiProcess_GenNormals | \
	aiProcess_GenUVCoords);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cerr << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		throw Model::AssimpError();
	}
	_directory = path.substr(0, path.find_last_of('/'));

	processNode(scene->mRootNode, scene);

	boneInfoUniform = static_cast<float*>(malloc(sizeof(float) * MAX_BONES * 16));
	for (uint i=0; i < MAX_BONES; i++) {
		for (uint j=0; j < 16; j++) {
			boneInfoUniform[i*16 + j] = boneInfo[i].boneOffset.getData()[j];
		}
	}
}

void	Model::processNode(aiNode *node, const aiScene *scene) {
	aiMesh	*mesh;

	// process all the node's _meshes (if any)
	for (u_int32_t i = 0; i < node->mNumMeshes; i++) {
		mesh = scene->mMeshes[node->mMeshes[i]];
		_meshes.push_back(processMesh(mesh, scene));
	}
	// recursion with each of its children
	for (u_int32_t i = 0; i < node->mNumChildren; ++i)
		processNode(node->mChildren[i], scene);
}

Material	loadMaterial(aiMaterial *mat) {
	Material material;
	aiColor3D color(0.f, 0.f, 0.f);
	float shininess;

	mat->Get(AI_MATKEY_COLOR_DIFFUSE, color);
	material.diffuse = mat::Vec3(color.r, color.g, color.b);

	mat->Get(AI_MATKEY_COLOR_AMBIENT, color);
	material.ambient = mat::Vec3(color.r, color.g, color.b);

	mat->Get(AI_MATKEY_COLOR_SPECULAR, color);
	material.specular = mat::Vec3(color.r, color.g, color.b);

	mat->Get(AI_MATKEY_SHININESS, shininess);
	material.shininess = shininess;

	return material;
}

// update min/max pos to use later to scale and center the model
void	Model::updateMinMaxPos(mat::Vec3 pos) {
	if (pos.x > _maxPos.x)
		_maxPos.x = pos.x;
	if (pos.y > _maxPos.y)
		_maxPos.y = pos.y;
	if (pos.z > _maxPos.z)
		_maxPos.z = pos.z;

	if (pos.x < _minPos.x)
		_minPos.x = pos.x;
	if (pos.y < _minPos.y)
		_minPos.y = pos.y;
	if (pos.z < _minPos.z)
		_minPos.z = pos.z;
}

// calculate the model matrix to scale and center the Model
void	Model::calcModelMatrix() {
	float		maxDiff;
	float		scale;
	mat::Vec3	transl;

	_model = mat::Mat4(1.0f);

	// calculate scale
	maxDiff = _maxPos.x - _minPos.x;
	if (maxDiff < _maxPos.y - _minPos.y)
		maxDiff = _maxPos.y - _minPos.y;
	if (maxDiff < _maxPos.z - _minPos.z)
		maxDiff = _maxPos.z - _minPos.z;
	maxDiff /= 2;
	scale = 1.0f / maxDiff;
	// apply the scale
	_model = _model.scale(mat::Vec3(scale, scale, scale));

	// calculate the translation
	transl.x = -((_minPos.x + _maxPos.x) / 2);
	transl.y = -((_minPos.y + _maxPos.y) / 2);
	transl.z = -((_minPos.z + _maxPos.z) / 2);
	// verification due to float precision
	transl.x = scale * ((transl.x < 0.00001f && transl.x > -0.00001f) ? 0.0f : transl.x);
	transl.y = scale * ((transl.y < 0.00001f && transl.y > -0.00001f) ? 0.0f : transl.y);
	transl.z = scale * ((transl.z < 0.00001f && transl.z > -0.00001f) ? 0.0f : transl.z);
	// apply the translation
	_model = _model.translate(transl);
}


Mesh	Model::processMesh(aiMesh *mesh, const aiScene *scene) {
	std::vector<VertexMat>	vertices;
	VertexMat				vertex;

	std::vector<u_int32_t>	indices;
	aiFace					face;

	std::vector<Texture>	textures;
	aiMaterial				*material;
	std::vector<Texture>	diffuseMaps;
	std::vector<Texture>	specularMaps;

	for (u_int32_t i = 0; i < mesh->mNumVertices; ++i) {
		// process vertex positions
		vertex.pos.x = mesh->mVertices[i].x;
		vertex.pos.y = mesh->mVertices[i].y;
		vertex.pos.z = mesh->mVertices[i].z;
		// update the min/max pos
		updateMinMaxPos(vertex.pos);
		// process vertex normals
		vertex.norm.x = mesh->mNormals[i].x;
		vertex.norm.y = mesh->mNormals[i].y;
		vertex.norm.z = mesh->mNormals[i].z;
		// process vertex texture coordinates
		vertex.texCoords = mat::Vec2(0.0f, 0.0f);
		if (mesh->mTextureCoords[0]) {
			vertex.texCoords.x = mesh->mTextureCoords[0][i].x;
			vertex.texCoords.y = mesh->mTextureCoords[0][i].y;
		}

		vertices.push_back(vertex);
	}

    // process indices
	for (u_int32_t i = 0; i < mesh->mNumFaces; ++i) {
		face = mesh->mFaces[i];
		// all face is conposed of 3 indices due to aiProcess_Triangulate
		for (u_int32_t j = 0; j < face.mNumIndices; ++j)
			indices.push_back(face.mIndices[j]);
	}

	// process material
	material = scene->mMaterials[mesh->mMaterialIndex];

	diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, \
	TextureT::difuse);
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

	specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, \
	TextureT::specular);
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    Mesh ret = Mesh(vertices, indices, textures, loadMaterial(material));
	for (uint i=0; i < mesh->mNumBones; i++) {
        uint boneIndex = 0;
        std::string boneName(mesh->mBones[i]->mName.data);

        if (boneMap.find(boneName) == boneMap.end()) {
            boneIndex = actBoneId;
            actBoneId++;
            BoneInfo bi;
            boneInfo[actBoneId] = bi;
        }
        else {
            boneIndex = boneMap[boneName];
        }

        boneMap[boneName] = boneIndex;
        boneInfo[boneIndex].boneOffset = aiToMat4(mesh->mBones[i]->mOffsetMatrix);

		for (uint j = 0; j < mesh->mBones[i]->mNumWeights; j++) {
			int vertexID = mesh->mBones[i]->mWeights[j].mVertexId;
			float weight = mesh->mBones[i]->mWeights[j].mWeight;
			if (weight <= 0.1)
				continue;
			ret.addBoneData(boneIndex, weight, vertexID);
		}
	}
	return ret;
}

std::vector<Texture>	Model::loadMaterialTextures(aiMaterial *mat, \
aiTextureType type, TextureT textType) {
    std::vector<Texture>	textures;
	aiString				str;
	Texture					texture;
	bool					skip;

    for (u_int32_t i = 0; i < mat->GetTextureCount(type); ++i) {
        mat->GetTexture(type, i, &str);

		skip = false;

		// verify if the texture has been loaded already
		for (u_int32_t j = 0; j < _texturesLoaded.size(); ++j) {
			if (std::strcmp(_texturesLoaded[j].path.data(), str.C_Str()) == 0) {
				textures.push_back(_texturesLoaded[j]);
				skip = true;
				break;
			}
		}

		// if not, load it
		if (!skip) {
			texture.id = textureFromFile(str.C_Str(), _directory);
			texture.type = textType;
			texture.path = str.C_Str();
			textures.push_back(texture);
			// save to _texturesLoaded array to skip duplicate textures loading later
			_texturesLoaded.push_back(texture);
		}
    }
    return textures;
}

const char* Model::AssimpError::what() const throw() {
    return ("Assimp failed to load the model!");
}

std::vector<Mesh>		Model::getMeshes() const {
	return _meshes;
}
std::string				Model::getDirectory() const {
	return _directory;
}
std::vector<Texture>	Model::getTexturesLoaded() const {
	return _texturesLoaded;
}
mat::Mat4	Model::getModelM() const {
	return _model;
}
