#pragma once

#include "framework.h"
#include "shader.h"


struct color_vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
};

struct vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;
};

class texture {
protected:
	int width_{ 0 }, height_{ 0 }, comp_{ 0 };
	unsigned char* data_{ nullptr };
	std::string path_;
public:
	texture(const std::string& filename);
	texture(const std::shared_ptr<std::vector<unsigned char>> data);
	~texture();
	//TODO operator overload
	GLuint vbo_texture{ 0 };

	void free();
	void load();
	void upload();
	void activate();
	void operator=(GLuint val);
	operator GLuint();
};

class mesh {
public:
	mesh();
	mesh(std::string& mesh_path, bool is_left_handed = true);
	virtual ~mesh();
	virtual void free();
	virtual bool upload();
	virtual bool load_mesh(std::string& mesh_path, bool is_left_handed);

	std::vector<vertex> vertices;
	std::vector<int> indices;
	std::string name;
	size_t size_of_indices{ 0 };
	GLuint vbo_vertices{ 0 }, ebo_indices{ 0 };
	float shininess{ 16.0 };
	glm::vec3 specular{ 0.5, 0.5, 0.5 };
};

class light : public mesh {
public:
	glm::vec3 position{ 0, 0, 0 };
	glm::vec3 specular{ 0.4, 0.4, 0.4 };
	glm::vec3 ambient{ 0.2, 0.2, 0.2 };
	glm::vec3 diffuse{ 0.9, 0.9, 0.9 };
};

class point_light : public light {
public:
	bool upload() override;
	bool load_mesh(const std::string& mesh_path, const std::string& texture_path = "");
};

class directional_light : public light {
public:
	directional_light();
	directional_light(glm::vec3 p);
	bool upload() override;
	bool load_mesh(const std::string& mesh_path, const std::string& texture_path = "");
};

class model {
protected:
	
	size_t size_of_indices{ 0 };
public:
	model();
	virtual ~model();
	virtual void draw();
	virtual bool upload();
	virtual void attach_program(std::shared_ptr<program> p);

	std::shared_ptr<program> prg;
	std::shared_ptr<mesh> m;
	GLuint vao{ 0 };
	glm::mat4 mat_model;
};


class texture_model : public model {
public:
	texture_model();
	texture_model(std::string mesh_path, std::string texture_path, bool is_left_handed = true);
	~texture_model() override;

	void draw() override;
	bool upload() override;

	std::string path_;
	std::shared_ptr<texture> tex;
};