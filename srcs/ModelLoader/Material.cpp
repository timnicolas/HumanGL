#include "Material.hpp"

Material::Material(const mat::Vec3 diffuse, const mat::Vec3 specular, \
const mat::Vec3 ambient, const float shininess)
: diffuse(diffuse),
  specular(specular),
  ambient(ambient),
  shininess(shininess) {
}

Material::Material(Material const &src) {
	*this = src;
}

Material::~Material() {
}

Material &Material::operator=(Material const &rhs) {
	if (this != &rhs) {
		diffuse = rhs.diffuse;
		specular = rhs.specular;
		ambient = rhs.ambient;
		shininess = rhs.shininess;
	}
	return *this;
}


std::ostream & operator << (std::ostream &out, const Material &m) {
	out << "material_____________" << std::endl;
	out << " diffuse: (" << m.diffuse.x << ", " << m.diffuse.y << ", " << m.diffuse.z << ")" << std::endl;
	out << " specular: (" << m.specular.x << ", " << m.specular.y << ", " << m.specular.z << ")" << std::endl;
	out << " ambient: (" << m.ambient.x << ", " << m.ambient.y << ", " << m.ambient.z << ")" << std::endl;
	out << " shininess: " << m.shininess << std::endl;
	return out;
}
