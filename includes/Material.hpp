#ifndef MATERIAL_HPP
# define MATERIAL_HPP

#include "commonInclude.hpp"

class Material {
	public:
		Material(const mat::Vec3 diffuse = mat::Vec3(0.906f, 0.906f, 0.906f), \
		const mat::Vec3 specular = mat::Vec3(1, 1, 1), \
		const mat::Vec3 ambient = mat::Vec3(0.2f, 0.2f, 0.2f), \
		const float shininess = 0.15);
		Material(Material const &src);
		virtual ~Material();

		Material &operator=(Material const &rhs);

		mat::Vec3	getDiffuse() const;
		mat::Vec3	getSpecular() const;
		mat::Vec3	getAmbient() const;
		float		getShininess() const;
	private:
		mat::Vec3	_diffuse;
		mat::Vec3	_specular;
		mat::Vec3	_ambient;
		float		_shininess;
};

#endif
