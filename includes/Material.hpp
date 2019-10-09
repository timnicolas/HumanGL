#ifndef MATERIAL_HPP
# define MATERIAL_HPP

#include "commonInclude.hpp"

class Material {
	public:
		Material(const mat::Vec3 diffuse = mat::Vec3(0.906f, 0.906f, 0.906f), \
		const mat::Vec3 specular = mat::Vec3(0.1f, 0.1f, 0.1f), \
		const mat::Vec3 ambient = mat::Vec3(0.2f, 0.2f, 0.2f), \
		const float shininess = 0.15f);
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
