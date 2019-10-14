#version 410 core

#define MAX_BONES 100
#define NUM_BONES_PER_VERTEX 4

layout (location = 5) in vec3 cubePos;
layout (location = 6) in vec3 cubeNormal;
layout (location = 7) in vec2 cubeTexCoords;

out vec2 texCoords;
out	vec3 fragPos;
out	vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
// uniform mat4 bones[MAX_BONES];

void main() {
    // mat4 boneTransform = mat4(1.0);
    // for (int i=0; i < NUM_BONES_PER_VERTEX; i++) {
    //     boneTransform += bones[bonesID[i]] * bonesWeight[i];
    // }

    // vec4 pos = boneTransform * vec4(cubePos, 1.0);
    vec4 pos = vec4(cubePos, 1.0);

    // vec4 boneNormal = boneTransform * vec4(aNormal, 0);
    vec4 boneNormal = vec4(cubeNormal, 0);

	texCoords = cubeTexCoords;
	fragPos = cubePos;
	// normal = mat3(transpose(inverse(model))) * boneNormal.xyz;
	normal = boneNormal.xyz;
	gl_Position = projection * view * model * pos;
}
