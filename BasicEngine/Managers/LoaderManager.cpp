#include "LoaderManager.h"
#include "../Rendering/Models/Mesh.h"
#include "../Engine.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace BasicEngine::Managers;
using namespace BasicEngine::Rendering::Models;

LoaderManager::LoaderManager(BasicEngine::Engine* _engine): engine(std::move(_engine))
{
}

LoaderManager::LoaderManager(BasicEngine::Engine* _engine,std::vector<std::string> _files):engine(std::move(_engine))
{
	files = _files;
}

LoaderManager::~LoaderManager()
{	
}

void LoaderManager::setFiles(std::vector<std::string> _files)
{
	files = _files;
}

std::vector<std::string> LoaderManager::getFiles()
{
	return files;
}

void LoaderManager::loadFile(std::string _file)
{
	FILE *file = new FILE();
	Mesh model;
	bool afterFirst = true;
	char c;
	int len;
	int mask;
	char* name, *texture;

	errno_t out = fopen_s(&file, _file.c_str(), "rb");
	if (out != 0)
	{
		printf("errno %d /n", out);
		return;
	}
	fread(&c, sizeof(char), 1, file);
	printf("%c\n", c);
	switch (c)
	{
		case 'o':
			fread(&mask, sizeof(int), 1, file);
			printf("%d\n", mask);
			fread(&len, sizeof(int), 1, file);
			name = new char[len];
			fread(&name, sizeof(char), len, file);
			printf("%s\n", name);
			if (afterFirst) engine->GetModelsManager()->SetModel(name, &model);
			afterFirst = false;
			model = Mesh();
			break;
		case 'c':
			fread(&c, sizeof(char), 1, file);
			switch (c)
			{
			case 'v':
				fread(&len, sizeof(int), 1, file);
				switch (mask)
				{
				case 0:
				{
					std::vector<VertexFormatP> ver(len);
					fread(&ver, sizeof(VertexFormatP), len, file);
					model.Create<VertexFormatP>(ver, mask);
					break;
				}
				case 1:
				{
					std::vector<VertexFormatN> ver(len);
					fread(&ver, sizeof(VertexFormatN), len, file);
					model.Create<VertexFormatN>(ver, mask);
					break;
				}
				case 2:
				{
					std::vector<VertexFormatUV> ver(len);
					fread(&ver, sizeof(VertexFormatUV), len, file);
					model.Create<VertexFormatUV>(ver, mask);
					break;
				}
				case 3:
				{
					std::vector<VertexFormatNUV> ver(len);
					fread(&ver, sizeof(VertexFormatNUV), len, file);
					model.Create<VertexFormatNUV>(ver, mask);
					break;
				}
				}
				break;
			case 'f':
			{
				fread(&len, sizeof(int), 1, file);
				std::vector<int> indicies(len);
				fread(&indicies, sizeof(int), len * 3, file);
				model.SetIndices(indicies);
				break;
			}
			case 't':
				fread(&len, sizeof(int), 1, file);
				texture = new char[len];
				fread(&texture, sizeof(char), len, file);
				break;
			}
			break;
		case 'm':
		{
			glm::vec3 dColor;
			glm::vec4 sColor;
			float alpha;
			fread(&dColor, sizeof(glm::vec3), 1, file);
			fread(&sColor, sizeof(glm::vec4), 1, file);
			fread(&alpha, sizeof(float), 1, file);
			model.SetMaterial(dColor, sColor, alpha);
			break;
		}
		case 's':
		{
			glm::vec4 mirror;
			fread(&mirror, sizeof(glm::vec4), 1, file);
			model.SetMirrorParamters(mirror);
			break;
		}
	}
}

void LoaderManager::loadFiles()
{
	for(auto fileToLoad : files)
	{	
		loadFile(fileToLoad);
	}
}