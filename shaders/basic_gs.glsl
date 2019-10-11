#version 410 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

out VS_OUT {
	vec2	texCoords;
	vec3	fragPos;
	vec3	normal;
} gs_out;

in VS_OUT {
	vec2	texCoords;
	vec3	fragPos;
	vec3	normal;
} gs_in[];

void main() {
    gl_Position = gl_in[0].gl_Position;
    gs_out.texCoords = gs_in[0].texCoords;
    gs_out.fragPos = gs_in[0].fragPos;
    gs_out.normal = gs_in[0].normal;
    EmitVertex();

    gl_Position = gl_in[1].gl_Position;
    gs_out.texCoords = gs_in[1].texCoords;
    gs_out.fragPos = gs_in[1].fragPos;
    gs_out.normal = gs_in[1].normal;
    EmitVertex();

    gl_Position = gl_in[2].gl_Position;
    gs_out.texCoords = gs_in[2].texCoords;
    gs_out.fragPos = gs_in[2].fragPos;
    gs_out.normal = gs_in[2].normal;
    EmitVertex();

    EndPrimitive();
}
