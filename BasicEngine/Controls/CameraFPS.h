#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <freeglut\freeglut.h>

namespace BasicEngine
{
	namespace Controls
	{
		class CameraFPS
		{
		public:
			//CameraFPS(glm::mat4& viewMatrix);
			//~CameraFPS();

			static void Init(glm::mat4* _viewMatrix);
			static void Init(glm::mat4* _viewMatrix, float _movmentSpeed, float _mouseXSensitivity, float _mouseYSensitivity);
			static void UpdateView();
			static void MouseMove(int x, int y);
			static glm::mat4 GetViewMatrix();
			static void KeyPressed(const unsigned char key, int x, int y);
			static void MousePressed(int button, int state, int x, int y);
			static void setMovmentSpeed(float _movmentSpeed);
			static void setMouseXSensitivity(float _mouseXSensitivity);
			static void setMouseYSensitivity(float _mouseYSensitivity);

		private:
			static glm::mat4* viewMatrix;
			static double keyYaw, keyPitch, keyRoll;
			static glm::quat cameraQuat;
			static glm::vec3 eyeVector;
			static bool isMousePressed;
			static glm::vec2 mousePosition;
			static float yaw, pitch, roll;
			static float movmentSpeed, mouseXSensitivity, mouseYSensitivity;

		};
	}
}