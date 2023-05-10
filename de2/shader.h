#pragma once
#include "glad/glad.h"
#include <string>
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtc/matrix_transform.hpp"


class shader
{
	GLuint id;
public:
	shader(GLenum shader_type);
	shader(GLenum shader_type, std::string filepath);
	virtual ~shader();


	virtual void compile(const std::string& source);
	operator GLuint() { return id; }
	void operator=(GLuint);
};

class vertex_shader : public shader {
public:
	vertex_shader () : shader(GL_VERTEX_SHADER){}
	vertex_shader(std::string filepath) : shader(GL_VERTEX_SHADER, filepath) {}
};
class frag_shader : public shader {
public:
	frag_shader() : shader(GL_FRAGMENT_SHADER) {}
	frag_shader(std::string filepath) : shader(GL_FRAGMENT_SHADER, filepath) {}
};

class program
{
protected:
	GLuint id;
	
public:
	program();
	program(std::string program_name, std::string vertex, std::string frag);
	virtual ~program(void);

	void attach_shader(shader& s);
	void link();
	void use();
	GLuint get_id();

	void setuniform(const std::string& name, GLfloat v);
	void setuniform(const std::string& name, GLint v);
	void setuniform(const std::string& name, const glm::vec3& v);
	void setuniform(const std::string& name, const glm::mat4& v);

	operator GLuint() { return id; }
	void operator=(GLuint);

	std::string name;
};

//class uniform
//{
//protected:
//	GLint uni;
//	program _sp;
//public:
//	uniform(program& sp, const std::string& _name);
//	virtual ~uniform();
//
//	void operator=(float v);
//	void operator=(std::initializer_list<GLfloat> v);
//	void operator=(glm::mat4 v);
//};


