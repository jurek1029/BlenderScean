#include "../PCH.h"

using namespace BasicEngine::Managers;
using namespace BasicEngine::Rendering::Models;

LoaderManager::LoaderManager(TextureManager* textureManager) : textureManager(textureManager)
{
}

LoaderManager::LoaderManager(TextureManager* textureManager, std::vector<std::string> _files) : textureManager(textureManager)
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

	char c;
	int len;
	int mask;
	char* name = nullptr, *texture = nullptr, *path = nullptr;

	errno_t out = fopen_s(&file, _file.c_str(), "rb");
	if (out != 0)
	{
		printf("errno %d /n", out);
		return;
	}
	while (fread(&c, sizeof(char), 1, file) > 0)
	{
		switch (c)
		{
			case 'n':
				fread(&len, sizeof(int), 1, file);
				meshes.reserve(len);
				break;
			case 'o':
				//meshes.emplace_back();			

				fread(&mask, sizeof(int), 1, file);
				if(mask > 19) meshes.emplace_back(new MirrorCube);
				else if (mask > 15) meshes.emplace_back(new MeshMirror);
				else if(mask > 7) meshes.emplace_back(new SkyBox);
				else {
					switch (mask)
					{
					case 0: meshes.emplace_back(new Mesh); break;
					case 1: meshes.emplace_back(new Mesh); break;
					case 2: meshes.emplace_back(new MeshTextured); break;
					case 3: meshes.emplace_back(new MeshTextured); break;
					case 4:meshes.emplace_back(new MeshFlat); break;
					case 5:meshes.emplace_back(new MeshFlat); break;
					case 6:meshes.emplace_back(new MeshFlatTextured); break;
					case 7:meshes.emplace_back(new MeshFlatTextured); break;
					}
				}
				
				fread(&len, sizeof(int), 1, file);
				name = new char[len];
				fread(name, sizeof(char), len, file);

				break;
			case 'c':
				fread(&c, sizeof(char), 1, file);
				switch (c)
				{
				case 'v':
					fread(&len, sizeof(int), 1, file);
					if (mask > 3 && mask < 8) dynamic_cast<MeshFlat*>(meshes.back())->vertexCount = len;
					if (mask > 19) dynamic_cast<MirrorCube*>(meshes.back())->vertexCount = len;
					switch (mask > 3? mask % 4: mask)
					{
					case 0:
					{
						VertexFormatP* array = new VertexFormatP[len];
						fread(array, sizeof(VertexFormatP), len, file);
						dynamic_cast<Mesh*>(meshes.back())->Create<VertexFormatP>(name,array, len);
						delete[] array;
						delete[] name;
						break;
					}
					case 1:
					{
						VertexFormatN* array = new VertexFormatN[len];
						fread(array, sizeof(VertexFormatN), len, file);
						dynamic_cast<Mesh*>(meshes.back())->Create<VertexFormatN>(name, array, len);
						delete[] array;
						delete[] name;
						break;
					}
					case 2:
					{
						VertexFormatUV* array = new VertexFormatUV[len];
						fread(array, sizeof(VertexFormatUV), len, file);
						dynamic_cast<Mesh*>(meshes.back())->Create<VertexFormatUV>(name, array, len);
						delete[] array;
						delete[] name;
						break;
					}
					case 3:
					{
						VertexFormatNUV* array = new VertexFormatNUV[len];
						fread(array, sizeof(VertexFormatNUV), len, file);
						dynamic_cast<Mesh*>(meshes.back())->Create<VertexFormatNUV>(name,array, len);
						delete[] array;
						delete[] name;
						break;
					}
					}
					break;
				case 'f':
				{
					fread(&len, sizeof(int), 1, file);
					unsigned int* indicies = new unsigned int[len*3];
					fread(indicies, sizeof(unsigned int), len * 3, file);
					dynamic_cast<Mesh*>(meshes.back())->SetIndices(indicies,len*3);
					delete[] indicies;
					break;
				}
				case 't':
					fread(&len, sizeof(int), 1, file); // dlugosc nazwy textury
					texture = new char[len]; 
					fread(texture, sizeof(char), len, file); // nazwy textury
					fread(&len, sizeof(int), 1, file); // dlugosc sciezki wzglednej do textury
					if (len > 0)// -1 oznacza ten sam katalog
					{
						path = new char[len]; 
						fread(path, sizeof(char), len, file); // sciezka do textury
						dynamic_cast<Mesh*>(meshes.back())->SetTexture(texture, textureManager->GetTexture((std::string)path + (std::string)texture)); // ustawienie zaladowaniej textury
						delete[] path;
					}
					else dynamic_cast<Mesh*>(meshes.back())->SetTexture(texture, textureManager->GetTexture(texture));

					delete[] texture;
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
				dynamic_cast<Mesh*>(meshes.back())->SetMaterial(dColor, sColor, alpha);
				break;
			}
			case 's':
			{
				//glm::vec4 mirror;
				//fread(&mirror, sizeof(glm::vec4), 1, file);
				//meshes.back().SetMirrorParamters(mirror);

				fread(&len, sizeof(int), 1, file); // dlugosc sciezki wzglednej do shaderow
				if (len > 0)// -1 oznacza ten sam katalog
				{
					dynamic_cast<Mesh*>(meshes.back())->ShadersPath = string(len, '\0');
					fread(&dynamic_cast<Mesh*>(meshes.back())->ShadersPath[0], sizeof(char), len, file); // sciezka do shaderow

					fread(&len, sizeof(int), 1, file); // dlugosc nazwy fragmentShadera
					dynamic_cast<Mesh*>(meshes.back())->FragmentShaderName = string(len, '\0');
					fread(&dynamic_cast<Mesh*>(meshes.back())->FragmentShaderName[0], sizeof(char), len, file); // nazwa fragmentShadera

					fread(&len, sizeof(int), 1, file); // dlugosc nazwy VertexShadera
					dynamic_cast<Mesh*>(meshes.back())->VertexShaderName = string(len, '\0');
					fread(&dynamic_cast<Mesh*>(meshes.back())->VertexShaderName[0], sizeof(char), len, file); // nazwa VertexShadera
				}
				break;
			}
		}
	}
	fclose(file);
	delete file;
}

void LoaderManager::loadFiles()
{
	for(auto fileToLoad : files)
	{	
		loadFile(fileToLoad);
	}
}

template< typename T >
struct array_deleter
{
	void operator ()(T const * p)
	{
		delete[] p;
	}
};