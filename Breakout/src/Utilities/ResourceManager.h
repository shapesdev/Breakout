#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include <GL/glew.h>

#include "Texture2D.h"
#include "Shader.h"

class ResourceManager
{
public:
	static std::map<std::string, Shader> Shaders;
	static std::map<std::string, Texture2D> Textures;

	static Shader LoadShader(const char *file, std::string name);
	static Shader GetShader(std::string name);
	static Texture2D LoadTexture(const char *file, bool alpha, std::string name);
	static Texture2D GetTexture(std::string name);
	static void Clear();
private:
	ResourceManager() {}
	static Shader LoadShaderFromFile(const char *filePath);
	static Texture2D LoadTextureFromFile(const char *filePath, bool alpha);
};

#endif

