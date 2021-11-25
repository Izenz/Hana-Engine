#include "Mesh.h"
#include "Globals.h"
#include "Application.h"

void Mesh::LoadVBO(const aiMesh* mesh) {
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	unsigned vertex_size = (sizeof(float)*3 + sizeof(float) * 2); // For each vertex 3 pos coordinates + 2 texture coordinates (?)
	unsigned buffer_size = vertex_size*mesh->mNumVertices;
	glBufferData(GL_ARRAY_BUFFER, buffer_size, nullptr, GL_STATIC_DRAW);

	unsigned position_size = sizeof(float) * 3 * mesh->mNumVertices;
	glBufferSubData(GL_ARRAY_BUFFER, 0, position_size, mesh->mVertices);

	unsigned uv_offset = position_size;
	unsigned uv_size = sizeof(float) * 2 * mesh->mNumVertices;
	float2* uvs = (float2*)(glMapBufferRange(GL_ARRAY_BUFFER, uv_offset, uv_size, GL_MAP_WRITE_BIT));

	for (unsigned i = 0; i < mesh->mNumVertices; ++i) {
		uvs[i] = float2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[i][0].y);
	}

	glUnmapBuffer(GL_ARRAY_BUFFER);
	num_vertices = mesh->mNumVertices;
}

void Mesh::LoadEBO(const aiMesh* mesh) {
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	unsigned index_size = sizeof(unsigned) * mesh->mNumFaces*3;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_size, nullptr, GL_STATIC_DRAW);
	unsigned* indices = (unsigned*)(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_MAP_WRITE_BIT));

	// for...

}
