#include "Shader.h"
#include <iostream>

Shader &Shader::Use() {
	glUseProgram(this->ID);
	return *this;
}

void Shader::Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource) {
	unsigned int vShader, fShader, gShader;

	vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &vertexSource, NULL);
	glCompileShader(vShader);
	CheckCompileErrors(vShader, "VERTEX");

	fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &fragmentSource, NULL);
	glCompileShader(fShader);
	CheckCompileErrors(fShader, "FRAGMENT");

	if (geometrySource != nullptr) {
		gShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(gShader, 1, &fragmentSource, NULL);
		glCompileShader(gShader);
		CheckCompileErrors(gShader, "GEOMETRY");
	}

	this->ID = glCreateProgram();
	glAttachShader(this->ID, vShader);
	glAttachShader(this->ID, fShader);
	if (geometrySource != nullptr) {
		glAttachShader(this->ID, gShader);
	}
	glLinkProgram(this->ID);
	CheckCompileErrors(this->ID, "PROGRAM");

	glDeleteShader(vShader);
	glDeleteShader(fShader);
	if (geometrySource != nullptr) {
		glDeleteShader(gShader);
	}
}

void Shader::SetBool(const std::string& name, bool value, bool useShader) {
	if (useShader) {
		this->Use();
		glUniform1i(glGetUniformLocation(this->ID, name.c_str()), (int)value);
	}
}
void Shader::SetInt(const std::string& name, int value, bool useShader) {
	if (useShader) {
		this->Use();
		glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value);
	}
}
void Shader::SetFloat(const std::string& name, float value, bool useShader) {
	if (useShader) {
		this->Use();
		glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value);
	}
}

void Shader::SetVector2f(const char* name, float x, float y, bool useShader) {
	if (useShader) {
		this->Use();
		glUniform2f(glGetUniformLocation(this->ID, name), x, y);
	}
}
void Shader::SetVector2f(const char* name, const glm::vec2& value, bool useShader) {
	if (useShader) {
		this->Use();
		glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
	}
}

void Shader::SetVector3f(const char* name, float x, float y, float z, bool useShader) {
	if (useShader) {
		this->Use();
		glUniform3f(glGetUniformLocation(this->ID, name), x, y, z);
	}
}
void Shader::SetVector3f(const char* name, const glm::vec3& value, bool useShader) {
	if (useShader) {
		this->Use();
		glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z);
	}
}

void Shader::SetVector4f(const char* name, float x, float y, float z, float w, bool useShader) {
	if (useShader) {
		this->Use();
		glUniform4f(glGetUniformLocation(this->ID, name), x, y, z, w);
	}
}
void Shader::SetVector4f(const char* name, const glm::vec4& value, bool useShader) {
	if (useShader) {
		this->Use();
		glUniform4f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z, value.w);
	}
}

void Shader::SetMatrix2(const char* name, const glm::mat2& mat, bool useShader) {
	if (useShader) {
		this->Use();
		glUniformMatrix2fv(glGetUniformLocation(this->ID, name), 1, GL_FALSE, glm::value_ptr(mat));
	}
}
void Shader::SetMatrix3(const char* name, const glm::mat3& mat, bool useShader) {
	if (useShader) {
		this->Use();
		glUniformMatrix3fv(glGetUniformLocation(this->ID, name), 1, GL_FALSE, glm::value_ptr(mat));
	}
}
void Shader::SetMatrix4(const char *name, const glm::mat4& mat, bool useShader) {
	if (useShader) {
		this->Use();
		glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, GL_FALSE, glm::value_ptr(mat));
	}
}

void Shader::CheckCompileErrors(unsigned int shader, std::string type) {
	int success;
	char infoLog[1024];
	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR: SHADER COMPILATION FAILED OF TYPE " << type << "\n" << infoLog << std::endl;
		}
	}
	else {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR: SHADER PROGRAM LINKING FAILED OF TYPE " << type << "\n" << infoLog << std::endl;
		}
	}
}