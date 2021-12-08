#include "Mesh.h"
#include "Globals.h"
#include "Application.h"

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

bool Mesh::Load(aiMesh* mesh) {
	LoadVBO(mesh);
	LoadEBO(mesh);
	CreateVAO();

	isLoaded = true;
	return true;
}

void Mesh::LoadVBO(const aiMesh* mesh) {
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	unsigned vertex_size = (sizeof(float) * 3 + sizeof(float) * 2); // For each vertex 3 pos coordinates + 2 texture coordinates (?)
	unsigned buffer_size = vertex_size * mesh->mNumVertices;
	glBufferData(GL_ARRAY_BUFFER, buffer_size, nullptr, GL_STATIC_DRAW);

	unsigned position_size = sizeof(float) * 3 * mesh->mNumVertices;
	glBufferSubData(GL_ARRAY_BUFFER, 0, position_size, mesh->mVertices);

	unsigned uv_offset = position_size;
	unsigned uv_size = sizeof(float) * 2 * mesh->mNumVertices;
	float2* uvs = (float2*)(glMapBufferRange(GL_ARRAY_BUFFER, uv_offset, uv_size, GL_MAP_WRITE_BIT));

	for (unsigned i = 0; i < mesh->mNumVertices; ++i) {
		uvs[i] = float2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
	}

	glUnmapBuffer(GL_ARRAY_BUFFER);
	num_vertices = mesh->mNumVertices;
}

void Mesh::LoadEBO(const aiMesh* mesh) {
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	unsigned index_size = sizeof(unsigned) * mesh->mNumFaces * 3;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_size, nullptr, GL_STATIC_DRAW);
	unsigned* indices = (unsigned*)(glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, 0, index_size, GL_MAP_WRITE_BIT));

	for (unsigned i = 0; i < mesh->mNumFaces; ++i) {
		assert(mesh->mFaces[i].mNumIndices == 3);

		*(indices++) = mesh->mFaces[i].mIndices[0];
		*(indices++) = mesh->mFaces[i].mIndices[1];
		*(indices++) = mesh->mFaces[i].mIndices[2];
	}

	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	num_indices = mesh->mNumFaces * 3;

}

void Mesh::CreateVAO() {
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float) * 3 * num_vertices));
}

void Mesh::Draw(const std::vector<Texture>& model_textures) {
	unsigned program = App->program->GetCurrentProgram();

	// TODO: Get camera out of editor.
	float4x4 view = App->editor->cam->GetViewMatrix();
	float4x4 proj = App->editor->cam->GetProjMatrix();
	float4x4 model = float4x4::identity;

	glUseProgram(program);
	
	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_TRUE, &model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_TRUE, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "proj"), 1, GL_TRUE, &proj[0][0]);
	

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, model_textures[0].id);	// FORNOW 0 is hardcoded since we only support one texture per model.
	glUniform1i(glGetUniformLocation(program, "diffuse"), 0);

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, nullptr);

	glUseProgram(0);
}