#include "Mesh.hpp"

Mesh::Mesh(std::vector<VertexMat> vertices_, std::vector<u_int32_t> indices_, \
std::vector<Texture> textures_, Material material_)
:	vertices(vertices_),
	indices(indices_),
	textures(textures_),
	material(material_)
{}

Mesh::Mesh(Mesh const &src) {
	*this = src;
}

Mesh::~Mesh() {
}

Mesh &Mesh::operator=(Mesh const &rhs) {
	if (this != &rhs) {
		vertices = rhs.vertices;
		indices = rhs.indices;
		textures = rhs.textures;
		material = rhs.material;
		_vao = rhs.getVao();
		_vbo = rhs.getVbo();
		_ebo = rhs.getEbo();
	}
	return *this;
}

void	Mesh::draw(Shader &sh) const {
	bool	diffuseText = false;
	bool	specularText = false;
	bool	normalText = false;

	sh.use();
	for (u_int16_t i = 0; i < textures.size(); ++i) {
		glActiveTexture(GL_TEXTURE0 + i);

		if (textures[i].type == TextureT::difuse && !diffuseText) {
			diffuseText = true;
			sh.setBool("material.diffuse.isTexture", true);
			sh.setInt("material.diffuse.texture", i);
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}
		else if (textures[i].type == TextureT::specular && !specularText) {
			specularText = true;
			sh.setBool("material.specular.isTexture", true);
			sh.setInt("material.specular.texture", i);
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}
		else if (textures[i].type == TextureT::normal && !normalText) {
			normalText = true;
			sh.setBool("material.normalMap.isTexture", true);
			sh.setInt("material.normalMap.texture", i);
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}
	}
	glActiveTexture(GL_TEXTURE0);

	if (!diffuseText) {
		sh.setBool("material.diffuse.isTexture", false);
		sh.setVec3("material.diffuse.color", material.diffuse);
	}
	if (!specularText) {
		sh.setBool("material.specular.isTexture", false);
		sh.setVec3("material.specular.color", material.specular);
	}
	if (!normalText) {
		sh.setBool("material.normalMap.isTexture", false);
		sh.setVec3("material.normalMap.color", mat::Vec3(0, 0, 1));
	}
	sh.setFloat("material.shininess", material.shininess);

	// drawing mesh
	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void	Mesh::setupMesh() {
	// create real vertex object to send to the bufferData in openGL
	std::vector<Vertex> vert;
	for (u_int32_t i=0; i < vertices.size(); i++) {
		Vertex v = Vertex{
			vertices[i].pos.x, vertices[i].pos.y, vertices[i].pos.z,
			vertices[i].norm.x, vertices[i].norm.y, vertices[i].norm.z,
			vertices[i].texCoords.x, vertices[i].texCoords.y,
			vertices[i].tangents.x, vertices[i].tangents.y, vertices[i].tangents.z,
			{0},
			{0}
		};
		for (u_int32_t j=0; j < NUM_BONES_PER_VERTEX; j++) {
			v.bonesID[j] = vertices[i].bonesID[j];
			v.bonesW[j] = vertices[i].bonesW[j];
		}
		vert.push_back(v);
	}

	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glGenBuffers(1, &_ebo);

	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, vert.size() * sizeof(Vertex), &(vert[0]), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(u_int32_t), &indices[0], GL_STATIC_DRAW);

	// vertex pos
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, posx));
	glEnableVertexAttribArray(0);
	// vertex norm
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normx));
	glEnableVertexAttribArray(1);
	// vertex textCoords
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, texCoordsx));
	glEnableVertexAttribArray(2);
	// vertex tangent
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, tangentsx));
	glEnableVertexAttribArray(3);
	// vertex bones IDs
	glVertexAttribIPointer(4, NUM_BONES_PER_VERTEX, GL_INT, sizeof(Vertex), (void *)offsetof(Vertex, bonesID));
	glEnableVertexAttribArray(4);
	// vertex bones weight
	glVertexAttribPointer(5, NUM_BONES_PER_VERTEX, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, bonesW));
	glEnableVertexAttribArray(5);

    glBindVertexArray(0);
}

u_int32_t	Mesh::getVao() const {
	return _vao;
}
u_int32_t	Mesh::getVbo() const {
	return _vbo;
}
u_int32_t	Mesh::getEbo() const {
	return _ebo;
}

// add boneId ad weight to the mesh
void Mesh::addBoneData(u_int32_t boneID, float weight, u_int32_t vertexID) {
	for (u_int32_t i = 0; i < NUM_BONES_PER_VERTEX; ++i) {
		// if the vertex bone weight as not been set
		if (vertices[vertexID].bonesW[i] == 0.0f) {
			vertices[vertexID].bonesID[i] = boneID;
			vertices[vertexID].bonesW[i] = weight;
			return;
		}
	}
	std::cerr << "too many bones in Mesh -> max: " << NUM_BONES_PER_VERTEX << "\n";
}