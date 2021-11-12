#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	unsigned int ID;

	Shader() {}
	Shader &Use();
	void Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource);

	void SetBool(const std::string& name, bool value, bool useShader = false);
	void SetInt(const std::string& name, int value, bool useShader = false);
	void SetFloat(const std::string& name, float value, bool useShader = false);

	void SetVector2f(const char* name, float x, float y, bool useShader = false);
	void SetVector2f(const char* name, const glm::vec2& value, bool useShader = false);

	void SetVector3f(const char* name, float x, float y, float z, bool useShader = false);
	void SetVector3f(const char* name, const glm::vec3& value, bool useShader = false);

	void SetVector4f(const char* name, float x, float y, float z, float w, bool useShader = false);
	void SetVector4f(const char* name, const glm::vec4& value, bool useShader = false);

	void SetMatrix2(const char* name, const glm::mat2& mat, bool useShader = false);
	void SetMatrix3(const char* name, const glm::mat3& mat, bool useShader = false);
	void SetMatrix4(const char* name, const glm::mat4& mat, bool useShader = false);

private:
	void CheckCompileErrors(unsigned int shader, std::string type);
};

#endif

