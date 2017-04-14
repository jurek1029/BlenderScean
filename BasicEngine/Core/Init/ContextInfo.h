#pragma once
namespace BasicEngine
{
	namespace Core
	{
		struct ContextInfo
		{
			int majorVersion, minorVersion;
			bool core;

			ContextInfo()
			{
				majorVersion = 3;
				minorVersion = 3;
				core = true;
			}

			ContextInfo(int majorVersion, int minorVersion, bool core) : majorVersion(majorVersion), minorVersion(minorVersion), core(core) {}

			ContextInfo(const ContextInfo& contextInfo)
			{
				majorVersion = contextInfo.majorVersion;
				minorVersion = contextInfo.minorVersion;
				core = contextInfo.core;
			}

			void operator=(const ContextInfo& contextInfo)
			{
				majorVersion = contextInfo.majorVersion;
				minorVersion = contextInfo.minorVersion;
				core = contextInfo.core;
			}
		};
	}
}