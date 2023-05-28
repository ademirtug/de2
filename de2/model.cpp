#include "pch.h"
#include "model.h"
#include <iterator>
#include <fstream>
#include <sstream>
#include "shader.h"
#include <stb_image.h>
#include "de2.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


template<typename Out> void split(const std::string& s, char delim, Out result) {
	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		*(result++) = item;
	}
}
std::vector<std::string> split(const std::string& s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, std::back_inserter(elems));
	return elems;
}
std::vector<int> split_i(const std::string& s, char delim) {
	std::stringstream ss(s);
	std::string i;
	std::vector<int> r;
	while (std::getline(ss, i, delim)) {
		r.push_back(atoi(i.c_str()));
	}
	return r;
}

//TEXTURE
//texture::texture() {
//}

texture::texture(const std::string& filename) {
	path_ = filename;
	load();
}
texture::texture(const std::shared_ptr<std::vector<unsigned char>> data) {
	data_ = stbi_load_from_memory(data->data(), data->size(), &width_, &height_, &comp_, STBI_rgb_alpha);
}
texture::~texture() {
	free();
	glDeleteBuffers(1, &vbo_texture);
}
void texture::free() {
	if (data_ != nullptr)
		stbi_image_free(data_);
	data_ = nullptr;
}
void texture::load() {
	//TODO: crash happens if the image is corrupted
	data_ = stbi_load(path_.c_str(), &width_, &height_, &comp_, 0);
	if (data_ == nullptr)
		throw std::runtime_error("failed to load image file: " + path_);
}

void texture::upload() {
	glGenTextures(1, &vbo_texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, vbo_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, comp_ == 3 ? GL_RGB : GL_RGBA, width_, height_, 0, comp_ == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, data_);
	glGenerateMipmap(GL_TEXTURE_2D);

	free();
}
void texture::activate() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, vbo_texture);
}
void texture::operator=(GLuint val)
{
	vbo_texture = val;
}
texture::operator GLuint() {
	return vbo_texture;
}



//MESH
mesh::mesh() {
}
mesh::mesh(std::string& mesh_path, bool is_left_handed) {
	//std::cout << "mesh -> " << mesh_path << std::endl;
	load_mesh(mesh_path, is_left_handed);
}
mesh::~mesh() {
	//std::cout << "~mesh -> " << name << std::endl;
	glDeleteBuffers(1, &vbo_vertices);
	glDeleteBuffers(1, &ebo_indices);
}
bool mesh::load_mesh(std::string& mesh_path, bool is_left_handed) {
	//TODO: for god sake use assimp
	std::vector<glm::vec3> vs;
	std::vector<glm::vec2> vt;
	std::vector<glm::vec3> vn;
	std::unordered_map<std::string, vertex> mvx;
	std::vector<vertex> vvx;
	std::vector<std::string> icombos;

	name = mesh_path;
	std::fstream f;
	f.open(mesh_path, std::fstream::in | std::fstream::binary);
	if (!f.is_open())
		throw std::runtime_error("could not open file");

	try {
		std::string line;
		while (getline(f, line)) {
			std::istringstream ss(line);
			std::string cmd;
			ss >> cmd;

			if (cmd == "v") {
				glm::vec3 v;
				ss >> v.x >> v.y >> v.z;
				v.z = v.z + (v.z * 2.0f * (is_left_handed - 1));// if(is_left_handed) v.z*=-1;
				vs.push_back(v);
			}
			else if (cmd == "vt") {
				glm::vec2 v;
				ss >> v.x >> v.y;
				vt.push_back(v);
			}
			else if (cmd == "vn") {
				glm::vec3 v;
				ss >> v.x >> v.y >> v.z;
				v.z = v.z + (v.z * 2.0f * (is_left_handed - 1));
				vn.push_back(v);
			}
			else if (cmd == "f") {
				while (!ss.eof()) {
					std::string sect;
					ss >> sect;
					if (sect == "")
						continue;

					icombos.push_back(sect);

					if (!mvx.contains(sect)) {

						auto vc = split(sect, '/');
						vertex ve;
						ve.position = vs[(atoi(vc[0].c_str()) - 1)];
						if (vc[1].size()) {
							ve.uv = vt[atoi(vc[1].c_str()) - 1];
						}
						if (vc[2].size()) {
							ve.normal = vn[atoi(vc[2].c_str()) - 1];
						}
						mvx[sect] = ve;
					}
				}
			}
		}
		f.close();
		for (auto it : mvx) {
			vertices.push_back(it.second);
		}
		vertices.reserve(mvx.size());
		for (std::string combo : icombos) {
			size_t idx = std::distance(mvx.begin(), mvx.find(combo));
			indices.push_back(idx);
		}
		size_of_indices = indices.size();
	}
	catch (...) {
		f.close();
		return false;
	}

	return true;
}
void mesh::free() {
	vertices.clear();
	indices.clear();
}
bool mesh::upload() {
	if (vbo_vertices)
		return true;

	try {
		glGenBuffers(1, &vbo_vertices);
		glGenBuffers(1, &ebo_indices);

 		glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_indices);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), indices.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, normal));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, uv));
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		free();
	}
	catch (...) {
		throw std::runtime_error("failed to load mesh: " + name);
	}

	return true;
}

//POINT LIGHT
bool point_light::upload() {
	return true;
}
bool point_light::load_mesh(const std::string& mesh_path, const std::string& texture_path) {
	return true;
}

//DIRECTIONAL LIGHT
directional_light::directional_light() {

}
directional_light::directional_light(glm::vec3 p) {
	position = p;
}
bool directional_light::upload() {
	return true;
}
bool directional_light::load_mesh(const std::string& mesh_path, const std::string& texture_path) {
	return true;
}

//MODEL
model::model() {
	mat_model = glm::mat4(1.0f);
}

model::~model() {
	//std::cout << "~model -> " << m->name << std::endl;
} 
bool model::upload() {
	throw std::exception("model::upload not implemented");
}
void model::draw() {
	throw std::exception("model::upload not implemented");
}
void model::attach_program(std::shared_ptr<program> p) {
	prg = p;
}

//TEXTURE MODEL
texture_model::texture_model() {

}
texture_model::texture_model(std::string mesh_path, std::string texture_path, bool is_left_handed) {
	m = make_shared<mesh>(mesh_path, is_left_handed);
	tex = std::make_shared<texture>(texture_path);
}
texture_model::~texture_model() {
	//glDeleteVertexArrays(1, &vao);
}
bool texture_model::upload() {
	//std::cout << "texture_model::upload() -> (" << m->name << ", "<<  vao <<")" << std::endl;
	if (vao > 0)
		return true;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	m->upload();
	tex->upload();
	glBindVertexArray(0);
	return true;
}
void texture_model::draw() {
	prg->use();
	prg->setuniform("model", mat_model);
	prg->setuniform("material.specular", m->specular);
	prg->setuniform("material.shininess", m->shininess);

	glBindVertexArray(vao);
	tex->activate();
	glDrawElements(GL_TRIANGLES, m->size_of_indices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}


