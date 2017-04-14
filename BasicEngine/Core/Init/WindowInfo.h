#pragma once
#include <string>

namespace BasicEngine
{
	namespace Core
	{
		struct WindowInfo
		{
			std::string name;
			int width, height;
			int positionX, positionY;
			bool isReshapable;

			WindowInfo()
			{
				name = "OpenGL Scean";
				width = 800; height = 600;
				positionX = 300;
				positionY = 300;
				isReshapable = true;
			}

			WindowInfo(std::string name, int startPositionX, int startPositionY, int width, int height, bool isReshapable) : name(name), positionX(startPositionX),
				positionY(startPositionY), width(width), height(height), isReshapable(isReshapable) {}

			WindowInfo(const WindowInfo& windowInfo)
			{
				name = windowInfo.name;
				positionX = windowInfo.positionX;
				positionY = windowInfo.positionY;
				width = windowInfo.width;
				height = windowInfo.height;
				isReshapable = windowInfo.isReshapable;
			}

			void operator=(const WindowInfo& windowInfo)
			{
				name = windowInfo.name;
				positionX = windowInfo.positionX;
				positionY = windowInfo.positionY;
				width = windowInfo.width;
				height = windowInfo.height;
				isReshapable = windowInfo.isReshapable;
			}

		};
	}
}