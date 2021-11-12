#include "ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include "stb_image/stb_image.h"

struct ShaderProgramSouce {
	std::string VertexSource;
	std::string FragmentSource;
	std::string GeometrySource;
};

std::map<std::string, Shader> ResourceManager::Shaders;
std::map<std::string, Texture2D> ResourceManager::Textures;

Shader ResourceManager::LoadShader(const char* file, std::string name) {
	Shaders[name] = LoadShaderFromFile(file);
	return Shaders[name];
}
Shader ResourceManager::GetShader(std::string name) {
	return Shaders[name];
}
Texture2D ResourceManager::LoadTexture(const char* file, bool alpha, std::string name) {
	Textures[name] = LoadTextureFromFile(file, alpha);
	return Textures[name];
}
Texture2D ResourceManager::GetTexture(std::string name) {
	return Textures[name];
}
void ResourceManager::Clear() {
	for (auto iter : Shaders) {
		glDeleteProgram(iter.second.ID);
	}
	for (auto iter : Textures) {
		glDeleteProgram(iter.second.ID);
	}
}

Shader ResourceManager::LoadShaderFromFile(const char* filePath) {
	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1, GEOMETRY = 2
	};

	ShaderProgramSouce source;

	std::string line;
	std::ifstream stream(filePath);

	std::stringstream ss[3];
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos) {
				type = ShaderType::FRAGMENT;
			}
			else if (line.find("geometry") != std::string::npos) {
				type == ShaderType::GEOMETRY;
			}
		}
		else {
			ss[(int)type] << line << '\n';
		}
	}

	source.VertexSource = ss[0].str();
	source.FragmentSource = ss[1].str();
	source.GeometrySource = ss[2].str();

	const char* vShaderCode = source.VertexSource.c_str();
	const char* fShaderCode = source.FragmentSource.c_str();
	const char* gShaderCode = source.GeometrySource.c_str();

	Shader shader;
	shader.Compile(vShaderCode, fShaderCode, gShaderCode != nullptr ? gShaderCode : nullptr);
	return shader;
}
Texture2D ResourceManager::LoadTextureFromFile(const char* filePath, bool alpha) {
	Texture2D texture;
	int width, height, nrChannels;
	if (alpha) {
		texture.Internal_Format = GL_RGBA;
		texture.Image_Format = GL_RGBA;
	}
	unsigned char* data = stbi_load(filePath, &width, &height, &nrChannels, 0);
	texture.Generate(width, height, data);
	stbi_image_free(data);
	return texture;
}
