#version 410 core
out vec4 fragColor;

in vec2 texCoords;

uniform sampler2D texture_diffuse1;

void main() {
	// fragColor = texture(texture_diffuse1, texCoords);
	fragColor = vec4(1, 0, 0, 1);
}
