#version 410 core

#define MAX_BONES 100
#define NUM_BONES_PER_VERTEX 4

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in ivec4 bonesID;
layout (location = 4) in vec4 bonesWeight;

out vec2 texCoords;
out	vec3 fragPos;
out	vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 modelScale;
uniform mat4 bones[MAX_BONES];

void main() {
    mat4 boneTransform = mat4(1.0);
    for (int i=0; i < NUM_BONES_PER_VERTEX; i++) {
        boneTransform += bones[bonesID[i]] * bonesWeight[i];
    }

    vec4 pos = boneTransform * vec4(aPos, 1.0);

    vec4 boneNormal = boneTransform * vec4(aNormal, 0);

	texCoords = aTexCoords;
	fragPos = vec3(modelScale * vec4(aPos, 1.0));
	normal = mat3(transpose(inverse(modelScale))) * boneNormal.xyz;

	gl_Position = projection * view * model * modelScale * pos;
}
