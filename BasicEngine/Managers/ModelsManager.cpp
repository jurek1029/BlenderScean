#include "ModelsManager.h"
#include "../Rendering/Models/Model.h"
#include "../Engine.h"

using namespace BasicEngine;
using namespace Managers;
using namespace Rendering;

ModelsManager::ModelsManager()
{
	/*
	Models::Triangle* triangle = new Models::Triangle();
	triangle->SetProgram(ShaderManager::GetShader("colorShader"));
	triangle->Create();
	gameModelList["triangle"] = triangle;

	Models::Quad* quad = new Models::Quad();
	quad->SetProgram(ShaderManager::GetShader("colorShader"));
	quad->Create();
	gameModelList["quad"] = quad;

	Models::Cube* cube = new Models::Cube();
	cube->SetProgram(ShaderManager::GetShader("colorShader"));
	cube->Create();
	gameModelList["cube"] = cube;
	*/

}

ModelsManager::~ModelsManager()
{
	for (auto model : gameModelList)
	{
		delete model.second;
	}
	gameModelList.clear();
}

void ModelsManager::DeleteModel(const std::string& gameModelName)
{
	IGameObject* model = gameModelList[gameModelName];
	model->Destroy();
	gameModelList.erase(gameModelName);
}

void ModelsManager::SetModel(const std::string& gameObjectName, IGameObject* gameObject)
{
	gameModelList[gameObjectName.c_str()] = gameObject;
}

IGameObject& ModelsManager::GetModel(const std::string& gameModelName) const
{
	return (*gameModelList.at(gameModelName));
}

void ModelsManager::Update()
{
	for( auto model: gameModelList)
	{
		model.second->Update();
	}
}

void ModelsManager::Draw()
{
	for (auto model : gameModelList)
	{
		model.second->Draw();
	}
}

void ModelsManager::Draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix)
{
	for (auto model : gameModelList)
	{
		if (model.second->toDraw)
		{
			if (temp == model.second->program->program) model.second->Draw();
			else
			{
				temp = model.second->program->program;
				glUseProgram(temp);
				model.second->program->configureShader(projectionMatrix, viewMatrix);
				model.second->Draw();
			}
		}
	}

	if (DEBUG)
	{
		for (auto model : gameModelList)
		{
			if (model.second->toDraw)
			{
				if (temp == model.second->programDebug->program) model.second->DrawDebug();
				else
				{
					temp = model.second->programDebug->program;
					glUseProgram(temp);
					model.second->programDebug->configureShader(projectionMatrix, viewMatrix);
					model.second->DrawDebug();
				}
			}
		}
	}

}

