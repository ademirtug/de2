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

//MESH
mesh::mesh() {
}
mesh::mesh(std::string& mesh_path, bool is_left_handed) {
	load_mesh(mesh_path, is_left_handed);
}
mesh::~mesh() {
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
			vx.push_back(it.second);
		}
		vx.reserve(mvx.size());
		for (std::string combo : icombos) {
			size_t idx = std::distance(mvx.begin(), mvx.find(combo));
			indices.push_back(idx);
		}
		indices_size = indices.size();
	}
	catch (...) {
		f.close();
		return false;
	}

	return true;
}
void mesh::free() {
	vx.clear();
	indices.clear();
}
bool mesh::upload() {
	try {
		glGenBuffers(1, &vbo_vertices);
		glGenBuffers(1, &ebo_indices);

 		glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * vx.size(), vx.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_indices);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), indices.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, normal));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, uv));
		glEnableVertexAttribArray(2);

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
model::~model() {

}
bool model::upload() {
	return false;
}
void model::draw() {
	
}
void model::attach_program(std::shared_ptr<program> p) {
	prg_ = p;
}
//TEXTURE MODEL
texture_model::texture_model(std::string mesh_path, std::string texture_path, bool is_left_handed) {
	m = make_shared<mesh>(mesh_path, is_left_handed);
	t = std::make_shared<texture>(texture_path);
}
texture_model::~texture_model() {
	//glDeleteVertexArrays(1, &vao);
}
bool texture_model::upload() {
	try {
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		
		m->upload();
		t->upload();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	catch (...) {
		return false;
	}
	return true;
}

void texture_model::draw() {
	prg_->use();
	prg_->setuniform("model", glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f)));
	prg_->setuniform("material.specular", m->specular);
	prg_->setuniform("material.shininess", m->shininess);

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, m->indices_size, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}


//TEXTURE
texture::texture() {
}

texture::texture(const std::string& filename) : texture() {
	load(filename);
}
texture::~texture() {
	free();
	glDeleteBuffers(1, &vbo_texture);
}
void texture::free() {
	if (data != nullptr)
		stbi_image_free(data);
	data = nullptr;
}
void texture::load(const std::string& filename) {
	free();

	data = stbi_load(filename.c_str(), &width, &height, &comp, 0);
	if (data == nullptr)
		throw std::runtime_error("failed to load image file: " + filename);
}

void texture::upload() {
	glGenTextures(1, &vbo_texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, vbo_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	free();
}
void texture::operator=(GLuint val)
{
	vbo_texture = val;
}
texture::operator GLuint() {
	return vbo_texture;
}
