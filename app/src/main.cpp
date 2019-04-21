/*
	Program entry point
*/

#include <tsconfig.h>
#include <tsengine.h>
#include "application.h"

#ifdef TS_PLATFORM_WIN32
#include <windows.h>
#endif

int main(int argc, char** argv)
{
	//Set startup parameters
	ts::SEngineStartupParams startup;
	startup.argc = argc;
	startup.argv = argv;

#ifdef TS_PLATFORM_WIN32

	SetProcessDPIAware();
	
	startup.showWindow = SW_SHOWDEFAULT;

	char path[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, path);
	startup.appPath = path;

#endif
	
	//Run engine
	ts::CEngineEnv engine(startup);
	ts::Application app(engine);
	return engine.start(app);
};
