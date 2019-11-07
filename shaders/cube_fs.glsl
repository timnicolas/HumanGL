#version 410 core
out vec4	fragColor;

in vec2		texCoords;
in vec3		fragPos;
in vec3		normal;

struct	ColorData {
	bool		isTexture;
	vec3		color;
	sampler2D	texture;
};

struct	Material {
	ColorData	diffuse;
	ColorData	specular;
	float		shininess;
};

struct DirLight {
	vec3		direction;

	vec3		ambient;
	vec3		diffuse;
	vec3		specular;
};

uniform vec3		viewPos;
uniform Material	material;
uniform DirLight	dirLight;

vec3 calcDirLight(DirLight light, vec3 norm, vec3 viewDir) {
	vec3	lightDir = normalize(-light.direction);
	// diffuse
	float	diff = max(dot(norm, lightDir), 0.0);
	// specular
	vec3	reflectDir = reflect(-lightDir, norm);
	float	spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	// use texture or color for the diffuse
	vec3	ambient = light.ambient;
	vec3	diffuse = light.diffuse;
	if (material.diffuse.isTexture) {
		ambient *= vec3(texture(material.diffuse.texture, texCoords));
		diffuse *= diff * vec3(texture(material.diffuse.texture, texCoords));
	}
	else {
		ambient *= material.diffuse.color;
		diffuse *= diff * material.diffuse.color;
	}

	// use texture or color for the specular
	vec3 specular = light.specular;
	if (material.specular.isTexture)
		specular *= spec * vec3(texture(material.specular.texture, texCoords));
	else
		specular *= spec * material.specular.color;

	return (ambient + diffuse + specular);
}

void main() {
	vec3	norm = normalize(normal);
	vec3	viewDir = normalize(viewPos - fragPos);

	// Directional lighting
	vec3	result = calcDirLight(dirLight, norm, viewDir);

	fragColor = vec4(result, 1.0);
	// fragColor = vec4(0.2, 0.9, 0.2, 1.0);
}
