#include "InitGLUT.h"

using namespace BasicEngine;
using namespace Core::Init;

Core::IListener* InitGLUT::listener = NULL;
Core::WindowInfo InitGLUT::windowInformation;

void InitGLUT::init(const Core::WindowInfo& windowInfo, const Core::ContextInfo& contextInfo, const Core::FramebufferInfo& framebufferInfo)
{
	int fakeargc = 1;
	char *fakeargv[] = { "fake" , nullptr };
	glutInit(&fakeargc, fakeargv);

	if (contextInfo.core)
	{
		glutInitContextVersion(contextInfo.majorVersion, contextInfo.minorVersion);
		glutInitContextProfile(GLUT_CORE_PROFILE);
	}
	else
	{
		glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	}

	glutInitDisplayMode(framebufferInfo.flags);
	glutInitWindowPosition(windowInfo.positionX, windowInfo.positionY);
	glutInitWindowSize(windowInfo.width, windowInfo.height);
	glutInitContextFlags(GLUT_DEBUG);													//Debuging
	glutCreateWindow(windowInfo.name.c_str());

	windowInformation = windowInfo;

	std::cout << "GLUT:initialized" << std::endl;
	glEnable(GL_DEBUG_OUTPUT);															//Debuging

	glutIdleFunc(idleCallback);
	glutCloseFunc(closeCallback);
	glutDisplayFunc(displayCallback);
	glutReshapeFunc(reshapeCallback);
	
	Init::InitGLEW::Init();
	glDebugMessageCallback(DebugOutput::myCallback, NULL);								//Debuging
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);	//Debuging

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	printOpenGLInfo(windowInfo, contextInfo);
}

void InitGLUT::run()
{
	std::cout << "GLUT: \t Start Running \n";
	glutMainLoop();
}

void InitGLUT::close()
{
	std::cout << "GLUT:\t Finished\n";
	glutLeaveMainLoop();
}

void InitGLUT::idleCallback()
{
	glutPostRedisplay();
}

void InitGLUT::displayCallback()
{
	if (listener)
	{
		listener->notifyBeginFrame();
		listener->notifyDisplayFrame();

		glutSwapBuffers();

		listener->notifyEndFrame();
	}
}

void InitGLUT::reshapeCallback(int width, int height)
{
	if (windowInformation.isReshapable)
	{
		if (listener)
		{
			listener->notifyReshape(width, height, windowInformation.width, windowInformation.height);
		}
		windowInformation.width = width;
		windowInformation.height = height;
	}
}

void InitGLUT::setListener(Core::IListener* iListener)
{
	listener = iListener;
}

void InitGLUT::closeCallback()
{
	close();
}

void InitGLUT::enterFullscreen()
{
	glutFullScreen();
}

void InitGLUT::exitFullscreen()
{
	glutLeaveFullScreen();
}

void InitGLUT::printOpenGLInfo(const Core::WindowInfo& windowInfo, const Core::ContextInfo& contextInfo)
{
	const unsigned char* renderer = glGetString(GL_RENDERER);
	const unsigned char* vendor = glGetString(GL_VENDOR);
	const unsigned char* version = glGetString(GL_VERSION);

	std::cout << "*************************************************************************" << std::endl;
	std::cout << "GLUT:Initialise" << std::endl;
	std::cout << "GLUT:\tVendor : " << vendor << std::endl;
	std::cout << "GLUT:\tRenderer : " << renderer << std::endl;
	std::cout << "GLUT:\tOpenGl version: " << version << std::endl;
}
