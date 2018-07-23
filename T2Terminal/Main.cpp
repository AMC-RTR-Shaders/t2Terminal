/*
* @author: Praveen Suryawanshi
* @mailto: suryawanshi.praveen007@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/

#include "Windowing.h"

using namespace Windowing;

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

TCHAR szAppName[] = TEXT("T2Terminal");

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow)
{
	OGLSurface surface(hInstance, szAppName);
	surface.Register();
	surface.Show(WIN_WIDTH,WIN_HEIGHT, Windowing::STYLE::NORMAL);
	surface.IntializeGL();
	return surface.StartLooper();	
}
