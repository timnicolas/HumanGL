#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in ivec4 bonesID;
layout (location = 4) in vec4 bonesWeight;

const int MAX_BONES = 100;

out vec2 texCoords;
out	vec3 fragPos;
out	vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 bones[MAX_BONES];

void main() {

    mat4 boneTransform = bones[0] * 0.3;
    boneTransform += bones[1] * 0.3;
    boneTransform += bones[2] * 0.2;
    boneTransform += bones[3] * 0.2;

    // mat4 boneTransform = bones[bonesID[0]] * bonesWeight[0];
    // boneTransform += bones[bonesID[1]] * bonesWeight[1];
    // boneTransform += bones[bonesID[2]] * bonesWeight[2];
    // boneTransform += bones[bonesID[3]] * bonesWeight[3];

    vec4 pos = boneTransform * vec4(aPos, 1.0);

	texCoords = aTexCoords;
	fragPos = vec3(model * vec4(aPos, 1.0));
	normal = mat3(transpose(inverse(model))) * aNormal;
	// gl_Position = projection * view * model * vec4(aPos, 1.0);
	gl_Position = projection * view * model * pos;
}
