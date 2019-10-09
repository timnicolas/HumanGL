#include "Material.hpp"

Material::Material(const mat::Vec3 diffuse, const mat::Vec3 specular, \
const mat::Vec3 ambient, const float shininess)
: _diffuse(diffuse),
  _specular(specular),
  _ambient(ambient),
  _shininess(shininess) {
}

Material::Material(Material const &src) {
	*this = src;
}

Material::~Material() {
}

Material &Material::operator=(Material const &rhs) {
	if (this != &rhs) {
		_diffuse = rhs.getDiffuse();
		_specular = rhs.getSpecular();
		_ambient = rhs.getAmbient();
		_shininess = rhs.getShininess();
	}
	return *this;
}

mat::Vec3	Material::getDiffuse() const {
	return _diffuse;
}
mat::Vec3	Material::getSpecular() const {
	return _specular;
}
mat::Vec3	Material::getAmbient() const {
	return _ambient;
}
float		Material::getShininess() const {
	return _shininess;
}

