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
	int width{ 0 }, height{ 0 }, comp{ 0 };
	unsigned char* data{ nullptr };

public:
	texture();
	texture(const std::string& filename);
	~texture();
	//TODO operator overload
	GLuint vbo_texture{ 0 };

	void free();
	void upload();
	void load(const std::string& filename);
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

	std::vector<vertex> vx;
	std::vector<int> indices;
	std::string name;
	size_t indices_size{ 0 };
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
	size_t _indices{ 0 };
public:
	
	virtual ~model();
	virtual void draw();
	virtual bool upload();
	virtual void attach_program(std::shared_ptr<program> p);

	std::shared_ptr<program> prg_;
	std::shared_ptr<mesh> m;
	GLuint vao{ 0 };
};


class texture_model : public model {
public:
	texture_model(std::string mesh_path, std::string texture_path, bool is_left_handed = true);
	~texture_model() override;

	void draw() override;
	bool upload() override;
	//void attach_program(std::shared_ptr<program> p) override;

	std::shared_ptr<texture> t;
};