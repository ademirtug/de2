#include "pch.h"
#include "framework.h"
#include "shader.h"


shader::shader(GLenum shader_type)
{
	id = glCreateShader(shader_type);
}

shader::shader(GLenum shader_type, std::string filepath) : shader(shader_type)
{
	std::fstream f;
	f.open(filepath, std::fstream::in | std::fstream::binary);
	if (!f.is_open())
		return;

	std::string contents, line;
	while (getline(f, line) )
		contents += line;
	
	f.close();
	compile(contents);
}


shader::~shader()
{
	if (id > 0)
		glDeleteShader(id);
}


void shader::compile(const std::string& source)
{
	if (source.length() < 1)
		return;

	const GLchar* src = static_cast<const GLchar*>(source.c_str());

	glShaderSource(id, 1, &src, 0);
	glCompileShader(id);

	GLint shader_compiled;
	glGetShaderiv(id, GL_COMPILE_STATUS, &shader_compiled);
	if (shader_compiled == GL_FALSE)
	{
		GLsizei log_length = 0;
		GLchar message[1024];
		glGetProgramInfoLog(id, 1024, &log_length, message);
		throw std::exception(std::string(message, log_length).c_str());
	}
}


void shader::operator=(GLuint val)
{
	id = val;
}


//uniform::uniform(program& sp, const std::string& name)
//{
//	_sp = sp;
//	uni = glGetUniformLocation(_sp, name.c_str());
//}
//
//void uniform::operator=(float v)
//{
//
//	glUniform1f(uni, v);
//
//}

//void uniform::operator=(mat4* mat)
//{
//	glUniformMatrix4fv(uni, 1, GL_FALSE/*column major*/, mat->mat);
//}


//void uniform::operator=(std::initializer_list<GLfloat> v)
//{
//	if (v.size() == 2)
//		glUniform2f(uni, *v.begin(), *(v.begin() + 1));
//}
//
//void uniform::operator=(glm::mat4 v)
//{
//	glUniformMatrix4fv(uni, 1, GL_FALSE, (GLfloat*)&v[0]);
//}
//
//uniform::~uniform()
//{
//}

program::program() {
	id = glCreateProgram();
}
program::program(std::string program_name, std::string vertex, std::string frag) : program()
{
	vertex_shader vs(vertex);
	frag_shader fs(frag);

	attach_shader(vs);
	attach_shader(fs);
	link();
}


program::~program(void)
{
	if (id > 0)
		glDeleteProgram(id);
}


void program::attach_shader(shader& s)
{
	glAttachShader(id, s);
}

void program::link()
{
	glLinkProgram(id);

	GLint program_linked;
	glGetProgramiv(id, GL_LINK_STATUS, &program_linked);
	if (program_linked != GL_TRUE)
	{
		GLsizei log_length = 0;
		GLchar message[1024];
		glGetProgramInfoLog(id, 1024, &log_length, message);
		throw std::exception(std::string(message, log_length).c_str());
	}

}

GLuint program::get_id(){
	return id;
}
void program::use() {
	glUseProgram(id);
}

void program::operator=(GLuint val){
	id = val;
}


void program::setuniform(const std::string& name, GLint v){
	glUniform1i(glGetUniformLocation(id, name.c_str()), v);
}

void program::setuniform(const std::string& name, GLfloat v){
	glUniform1f(glGetUniformLocation(id, name.c_str()), v);
}

void program::setuniform(const std::string& name, const glm::vec3& v){
	glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, &v[0]);
}

void program::setuniform(const std::string& name, const glm::mat4& v){
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &v[0][0]);
}