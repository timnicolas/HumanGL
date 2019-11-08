#ifndef MATERIAL_HPP
# define MATERIAL_HPP

#include "commonInclude.hpp"

class Material {
	public:
		Material(const mat::Vec3 diffuse = mat::Vec3(.36f, .34f, .32f), \
		const mat::Vec3 specular = mat::Vec3(.3f, .3f, .3f), \
		const mat::Vec3 ambient = mat::Vec3(0.2f, 0.2f, 0.2f), \
		const float shininess = 16.0f);
		Material(Material const &src);
		virtual ~Material();

		Material &operator=(Material const &rhs);

		mat::Vec3	diffuse;
		mat::Vec3	specular;
		mat::Vec3	ambient;
		float		shininess;

	private:
};

std::ostream & operator << (std::ostream &out, const Material &c);

#endif
