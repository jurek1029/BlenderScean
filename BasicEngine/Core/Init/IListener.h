#pragma once
namespace BasicEngine
{
	namespace Core
	{
		class IListener
		{
		public:
			virtual ~IListener() = 0;

			virtual void notifyBeginFrame() = 0;
			virtual void notifyDisplayFrame() = 0;
			virtual void notifyEndFrame() = 0;
			virtual void notifyReshape(int widht, int height, int previousWidth, int previousHeight) = 0;
		};

		inline IListener::~IListener()
		{

		}
	}
}