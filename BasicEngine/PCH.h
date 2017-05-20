#pragma once

//STD
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <memory>
#include <map>
#include<time.h>
#include<stdarg.h>

//OpenGL
#include <glew/glew.h>
#include <freeglut\freeglut.h>

//glm
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/quaternion.hpp>

//SOIL
#include "soil\SOIL.h"

//Init
#include "Core\Init\ContextInfo.h"
#include "Core\Init\FramebufferInfo.h"
#include "Core\Init\WindowInfo.h"
#include "Core\Init\InitGLEW.h"
#include "Core\Init\IListener.h"
#include "Core\Init\DebugOutput.h"
#include "Core\Init\InitGLUT.h"

//Core
#include "Core\IComponent.h"
#include "Core\IObject.h"

//Controls
#include "Controls\CameraFPS.h"

//Shaders
#include "Shaders\IShader.h"
#include "Shaders\ShaderComponent.h"
#include "Shaders\ShaderDebug.h"
#include "Shaders\ShaderDefault.h"
#include "Shaders\ShaderMirrorCube.h"
#include "Shaders\ShaderShadow.h"
#include "Shaders\ShaderSkyBox.h"

//Textures
#include "Rendering\Texture\BMPHeaders.h"
#include "Rendering\Texture\TextureLoader.h"

//Rendering
#include "Rendering\IGameObject.h"
#include "Rendering\VertexFormat.h"

//Models
#include "Rendering\Models\Model.h"
#include "Rendering\Models\Mesh.h"
#include "Rendering\Models\Cube.h"
#include "Rendering\Models\Quad.h"
#include "Rendering\Models\Triangle.h"
#include "Rendering\Models\MeshFlat.h"
#include "Rendering\Models\MeshFlatTextured.h"
#include "Rendering\Models\MeshTextured.h"

//Manageres
#include "Managers\TextureManager.h"
#include "Managers\ModelsManager.h"
#include "Managers\ShaderManager.h"
#include "Managers\SceneManager.h"
#include "Managers\LoaderManager.h"

//Models dependent
#include "Rendering\Models\MeshMirror.h"
#include "Rendering\Models\MirrorCube.h"
#include "Rendering\Models\SkyBox.h"

//Engine 
#include "Engine.h"
