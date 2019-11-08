#ifndef MESH_HPP
# define MESH_HPP

#include "commonInclude.hpp"
#include "Shader.hpp"
# include "Material.hpp"
#include <vector>
#include <map>

enum class TextureT {
	difuse,
	specular,
	normal
};

static const std::string	gTextType[] =
{
	"diffuse",
	"specular",
	"normal"
};
struct VertexMat {  // contain matrix objects
	mat::Vec3	pos;
	mat::Vec3	norm;
	mat::Vec2	texCoords;
	mat::Vec3	tangents;
	int			bonesID[NUM_BONES_PER_VERTEX];
	float		bonesW[NUM_BONES_PER_VERTEX];

	VertexMat() :
		pos(mat::Vec3()),
		norm(mat::Vec3()),
		texCoords(mat::Vec2()),
		tangents(mat::Vec3()),
		bonesID{0},
		bonesW{0} {
	}
};
struct Vertex {  // contain pointer on data on matrix object
	float posx, posy, posz;
	float normx, normy, normz;
	float texCoordsx, texCoordsy;
	float tangentsx, tangentsy, tangentsz;
	int bonesID[NUM_BONES_PER_VERTEX];
	float bonesW[NUM_BONES_PER_VERTEX];
};

struct Texture {
	u_int32_t	id;
	TextureT	type;
	std::string	path;
};

class Mesh {
	public:
		Mesh(std::vector<VertexMat> vertices_, std::vector<u_int32_t> indices_, \
		std::vector<Texture> textures_, Material material_);
		Mesh(Mesh const &src);
		virtual ~Mesh();

		Mesh &operator=(Mesh const &rhs);

		u_int32_t	getVao() const;
		u_int32_t	getVbo() const;
		u_int32_t	getEbo() const;

		void		draw(Shader &sh) const;
		void		addBoneData(u_int32_t boneID, float weight, u_int32_t vertexID);
		void		setupMesh();

		std::vector<VertexMat>	vertices;
		std::vector<u_int32_t>	indices;
		std::vector<Texture>	textures;
		Material				material;
	private:

        u_int32_t	_vao;
        u_int32_t	_vbo;
        u_int32_t	_ebo;
};

#endif
