/*
* @author: Praveen Suryawanshi
* @mailto: suryawanshi.praveen007@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/


#pragma once

#ifndef  _WINDOWING_H_
#define _WINDOWING_H_



#include <Windows.h>
#include<stdio.h>
#include <gl\glew.h>
#include<gl/GL.h>
#include<Math.h>
#include "MainScene.h"
#include "vmath.h"


#pragma comment(lib,"glew32.lib")
#pragma comment(lib, "opengl32.lib")


using namespace T2Terminal;

namespace Windowing
{

	enum STYLE
	{
		HIDE,
		NORMAL,
		MINIMIZED,
		MAXIMIZED,
		NOACTIVATE,
		SHOW,
		MINIMIZE,
		MINNOACTIVE,
		SHOWNA,
		RESTORE,
	};

	
	class OGLSurface
	{
	public:
		
		OGLSurface(HINSTANCE hInstance,TCHAR *title);
		
		BOOL Register();

		BOOL Show(int width, int height,int style);

		BOOL IntializeGL();

		int StartLooper();

		void ReSize(int width, int height);

		void ToggleFullScreen();

		~OGLSurface();

	private:

		static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

		LRESULT CALLBACK OGLSurfaceProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
		
		HINSTANCE _hInstance;
		HWND _hwnd;
		TCHAR *_szAppName;
		WNDCLASSEX _wndclassex;
		int _width;
		int _height;


		bool _IsFullScreen;
		LONG _PreviousStyle;
		WINDOWPLACEMENT  _wndplacement;
		MONITORINFO _monitorInfo;

		HDC _hdc;
		HGLRC _hglrc;

		bool _isEscapeKeyPressed;

		bool _IsActiveWindow;
		bool _IsGameDone;

		IScene * _scene;

		
	};
}

#endif // ! _WINDOWING_H_
