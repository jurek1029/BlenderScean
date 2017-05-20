#include "../PCH.h"

using namespace BasicEngine::Controls;

glm::mat4* CameraFPS::viewMatrix = nullptr;
glm::vec3 CameraFPS::eyeVector;
bool CameraFPS::isMousePressed;
glm::vec2 CameraFPS::mousePosition;

float CameraFPS::yaw, CameraFPS::pitch, CameraFPS::roll;
float CameraFPS::movmentSpeed = 0.12, CameraFPS::mouseXSensitivity = 0.025f, CameraFPS::mouseYSensitivity = 0.025;
//double CameraFPS::keyYaw, CameraFPS::keyPitch, CameraFPS::keyRoll;
//glm::quat CameraFPS::cameraQuat;


void CameraFPS::Init(glm::mat4* _viewMatrix)
{
	CameraFPS::viewMatrix = _viewMatrix;
	glutMotionFunc(MouseMove);
	glutMouseFunc(MousePressed);
	glutKeyboardFunc(KeyPressed);
}

void CameraFPS::Init(glm::mat4* _viewMatrix, float _movmentSpeed, float _mouseXSensitivity, float _mouseYSensitivity)
{
	Init(_viewMatrix);
	movmentSpeed = _mouseXSensitivity;
	mouseXSensitivity = _mouseXSensitivity;
	mouseYSensitivity = _mouseYSensitivity;
}

void CameraFPS::UpdateView()
{
	/*
	glm::quat keyQuat = glm::quat(glm::vec3(keyPitch, keyYaw, keyRoll));
	keyPitch = keyYaw = keyRoll = 0;

	cameraQuat = keyQuat * cameraQuat;
	cameraQuat = glm::normalize(cameraQuat);
	glm::mat4 rotate = glm::mat4_cast(cameraQuat);

	glm::mat4 translate = glm::mat4(1.0f);
	translate = glm::translate(translate, -eyeVector);

	*viewMatrix = rotate * translate;
	*/
	glm::mat4 matRoll = glm::mat4(1.0f);
	glm::mat4 matPitch = glm::mat4(1.0f);
	glm::mat4 matYaw = glm::mat4(1.0f);

	matRoll = glm::rotate(matRoll, roll, glm::vec3(0.0f, 0.0f, 1.0f));
	matPitch = glm::rotate(matPitch, pitch, glm::vec3(1.0f, 0.0f, 0.0f));
	matYaw = glm::rotate(matYaw, yaw, glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 rotate = matRoll * matPitch * matYaw;

	glm::mat4 translate = glm::mat4(1.0f);
	translate = glm::translate(translate, -eyeVector);

	*viewMatrix = rotate * translate;
}

glm::mat4 CameraFPS::GetViewMatrix()
{
	return *viewMatrix;
}
//when we press key
void CameraFPS::KeyPressed(const unsigned char key, int x, int y)
{
	float dx = 0; //how much we strafe on x
	float dz = 0; //how much we walk on z
	switch (key)
	{
	case 'w':
	{
		dz = -2;
		break;
	}

	case 's':
	{
		dz = 2;
		break;
	}
	case 'a':
	{
		dx = -2;
		break;
	}

	case 'd':
	{
		dx = 2;
		break;
	}
	default:
		break;
	}

	glm::mat4 mat = GetViewMatrix();
	glm::vec3 forward(mat[0][2], mat[1][2], mat[2][2]);
	glm::vec3 strafe(mat[0][0], mat[1][0], mat[2][0]);

	eyeVector += (-dz * forward + dx * strafe) * movmentSpeed;

	UpdateView();
}

void CameraFPS::MouseMove(int x, int y)
{
	/*
	if (isMousePressed == false)
	return;
	glm::vec2 mouse_delta = glm::vec2(x, y) - mousePosition;

	keyYaw = mouseXSensitivity * mouse_delta.x;
	keyPitch = mouseYSensitivity * mouse_delta.y;

	mousePosition = glm::vec2(x, y);
	UpdateView();
	*/
	if (isMousePressed == false)
		return;

	glm::vec2 mouse_delta = glm::vec2(x, y) - mousePosition;

	yaw -= mouseXSensitivity * mouse_delta.x;
	pitch -= mouseYSensitivity * mouse_delta.y;

	mousePosition = glm::vec2(x, y);
	UpdateView();
}

void CameraFPS::MousePressed(int button, int state, int x, int y)
{
	if (state == GLUT_UP)
	{
		isMousePressed = false;
	}
	if (state == GLUT_DOWN)
	{
		isMousePressed = true;
		mousePosition.x = x;
		mousePosition.y = y;
	}
}

void CameraFPS::setMovmentSpeed(float _movmentSpeed)
{
	movmentSpeed = _movmentSpeed;
}

void CameraFPS::setMouseXSensitivity(float _mouseXSensitivity)
{
	mouseXSensitivity = _mouseXSensitivity;
}

void CameraFPS::setMouseYSensitivity(float _mouseYSensitivity)
{
	mouseYSensitivity = _mouseYSensitivity;
}
