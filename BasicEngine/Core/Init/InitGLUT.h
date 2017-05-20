#pragma once
#include "../../PCH.h"

namespace BasicEngine
{
	namespace Core
	{
		namespace Init
		{
			class InitGLUT
			{
			public:
				static void init(const Core::WindowInfo& window, const Core::ContextInfo& context, const Core::FramebufferInfo& framebufferInfo);

				static void run();
				static void close();

				void enterFullscreen();
				void exitFullscreen();

				static void printOpenGLInfo(const Core::WindowInfo& windowInfo, const Core::ContextInfo& context);

				static Core::WindowInfo getWindowInfo();

			private:
				static void idleCallback();
				static void displayCallback();
				static void reshapeCallback(int width, int height);
				static void closeCallback();

				static Core::IListener* listener;
				static Core::WindowInfo windowInformation;

			public:
				static void setListener(Core::IListener* ilistener);
			};
		}
	}
}