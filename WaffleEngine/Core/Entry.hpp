#pragma once
#include "App.hpp"

extern Waffle::App* Waffle::CreateApp(int argc, char** argv);
bool g_ApplicationRunning = true;

namespace Waffle {

	int Main(int argc, char** argv)
	{
		while (g_ApplicationRunning)
		{
			Waffle::App* app = Waffle::CreateApp(argc, argv);
			app->Run();
			delete app;
		}

		return 0;
	}

}

#ifdef RELEASE_MODE

#ifdef __WIN32
#include <Windows.h>

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	return Waffle::Main(__argc, __argv);
}

#endif // __WIN32
#else

int main(int argc, char** argv)
{
	return Waffle::Main(argc, argv);
}

#endif // RELEASE_MODE
