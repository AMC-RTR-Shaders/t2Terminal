/*
* @author: Praveen Suryawanshi
* @mailto: suryawanshi.praveen007@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/

#include "Windowing.h"
#include "KeyBoard.h"

using namespace Event;

LRESULT Windowing::OGLSurface::WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{

	OGLSurface* psurface = (OGLSurface*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

	if (psurface == NULL)
	{
		
		return DefWindowProc(hwnd, message, wparam, lparam);
	}
	else 
	{
		return psurface->OGLSurfaceProc(hwnd, message, wparam, lparam);
	}
}

LRESULT Windowing::OGLSurface::OGLSurfaceProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	if (_scene != NULL)
	{
		_scene->SceneHandler(hwnd, message, wparam, lparam);
	}
	

	switch (message)
	{

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case   WM_ACTIVATE:
		
		if (HIWORD(wparam) == 0)
			_IsActiveWindow = true;
			else
			_IsActiveWindow = false;
			break;

	case WM_SIZE:
		ReSize(LOWORD(lparam), HIWORD(lparam));
		break;
		
	case WM_KEYDOWN:
		switch (wparam)
		{

		case VK_ESCAPE: _isEscapeKeyPressed = true;
			break;

		case Event::KeyBoard::KEYS::F:
			ToggleFullScreen();
			break;

		default: break;
		}
		
	default: break;
	}

	return DefWindowProc(hwnd, message, wparam, lparam);
}


Windowing::OGLSurface::OGLSurface(HINSTANCE hInstance,TCHAR *title)
{
	_hInstance = NULL;
	_hwnd = NULL;
	_szAppName = NULL;	
	_width = 0;
	_height =0;
	_IsFullScreen = false;
	_PreviousStyle = false;
	_hdc = NULL;
	_isEscapeKeyPressed = false;
	_IsActiveWindow = false;
	_IsGameDone = false;
	ZeroMemory(&_wndclassex, sizeof(WNDCLASSEX));
	
	_szAppName = title;
	_hInstance = hInstance;

	_scene = T2Terminal::MainScene::GetInstance(SCENE_NUMBER::MAIN);

	if (_scene == NULL)
		throw std::exception("EXCEPTION :INSTANCE NOT SET");
	
}

BOOL Windowing::OGLSurface::Register()
{
	_wndclassex.cbSize = sizeof(WNDCLASSEX);
	_wndclassex.cbClsExtra = 0;
	_wndclassex.cbWndExtra = 0;
	_wndclassex.hCursor = LoadCursor(NULL, IDC_ARROW);
	_wndclassex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	_wndclassex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	_wndclassex.hInstance = _hInstance;
	_wndclassex.lpfnWndProc = OGLSurface::WndProc;
	_wndclassex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	_wndclassex.lpszClassName = _szAppName;
	_wndclassex.lpszMenuName = NULL;
	_wndclassex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

	if (!RegisterClassEx(&_wndclassex))
		return false;

	return true;
}

BOOL Windowing::OGLSurface::Show(int width, int height , int style)
{
	_width = width;
	_height = height;
	
	_hwnd = CreateWindowEx(WS_EX_APPWINDOW,
		_szAppName,
		_szAppName,
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width,
		height,
		NULL,
		NULL,
		 _hInstance,
		 this
	);
	

	 if (_hwnd == NULL)
		 return false;

	 SetWindowLongPtr(_hwnd, GWLP_USERDATA, (LONG_PTR)this);

	 ShowWindow(_hwnd, style);

	 SetForegroundWindow(_hwnd);

	 SetFocus(_hwnd);

	 return true;
}

BOOL Windowing::OGLSurface::IntializeGL()
{
	PIXELFORMATDESCRIPTOR pfd;

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cRedBits = 8;
	pfd.cBlueBits = 8;
	pfd.cBlueBits = 8;
	pfd.cAlphaBits = 8;
	pfd.cDepthBits = 32;
	
	_hdc = GetDC(_hwnd);

	if (_hdc == NULL)
		return false;

	int iIndexPixelFormatDescriptor = ChoosePixelFormat(_hdc, &pfd);

	if (iIndexPixelFormatDescriptor == 0)
		return false;
	
	if (SetPixelFormat(_hdc, iIndexPixelFormatDescriptor, &pfd) == FALSE)
		return false;
	
	_hglrc = wglCreateContext(_hdc);

	if (_hglrc == NULL)
		return false;
	
	if (wglMakeCurrent(_hdc, _hglrc) == FALSE)
		return false;

	GLenum error = glewInit();
	if (error != GLEW_OK)
		return false;

	
	_scene->Initialize();

	//WARM UP CALL
	_scene->ReSize(_width,_height);
	
	return true;
}

int Windowing::OGLSurface::StartLooper()
{
	MSG msg{ 0 };

	
	while (_IsGameDone == false)
	{

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				_IsGameDone = true;
			}
			else
			{	
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

		}
		else
		{
			if (_IsActiveWindow == true)
			{
				if (_isEscapeKeyPressed == true)
					_IsGameDone = true;

				if (_scene == NULL)
					throw std::exception("EXCEPTION : SCENE INSTANCE NOT SET");

				_scene->Update();

				if (_scene == NULL)
					throw std::exception("EXCEPTION : SCENE INSTANCE NOT SET");

				_scene->Render(_hdc);

			}
		}
	}

	if (_scene == NULL)
		throw std::exception("EXCEPTION : SCENE INSTANCE NOT SET");

	_scene->UnInitialize();
	_scene = NULL;

	return msg.wParam;
}

void Windowing::OGLSurface::ReSize(int width, int height)
{
	_width = width;
	_height = height;

	if (_scene == NULL)
		throw std::exception("EXCEPTION :INSTANCE NOT SET");

	_scene->ReSize(_width, _height);
}

void Windowing::OGLSurface::ToggleFullScreen()
{
	if (_IsFullScreen)
	{
		SetWindowLong(_hwnd, GWL_STYLE, _PreviousStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(_hwnd, &_wndplacement);
		SetWindowPos(_hwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);
		ShowCursor(TRUE);
		_IsFullScreen = false;
		return;
	}

	_PreviousStyle = GetWindowLong(_hwnd, GWL_STYLE);

	if (_PreviousStyle & WS_OVERLAPPEDWINDOW)
	{
		_monitorInfo = { sizeof(MONITORINFO) };

		if (GetWindowPlacement(_hwnd, &_wndplacement) && GetMonitorInfo(MonitorFromWindow(_hwnd, MONITORINFOF_PRIMARY), &_monitorInfo))
		{
			SetWindowLong(_hwnd, GWL_STYLE, _PreviousStyle & ~WS_OVERLAPPEDWINDOW);
			SetWindowPos(_hwnd, HWND_TOP, _monitorInfo.rcMonitor.left, _monitorInfo.rcMonitor.top, _monitorInfo.rcMonitor.right - _monitorInfo.rcMonitor.left, _monitorInfo.rcMonitor.bottom - _monitorInfo.rcMonitor.top, SWP_NOZORDER | SWP_FRAMECHANGED);
		}

	}

	ShowCursor(FALSE);
	_IsFullScreen = true;
}


Windowing::OGLSurface::~OGLSurface()
{
	if (_hglrc != NULL)
	{
		wglDeleteContext(_hglrc);
		_hglrc = NULL;
	}

	if(_hwnd != NULL)
	{

		ReleaseDC(_hwnd, _hdc);
		_hdc = NULL;

		DestroyWindow(_hwnd);
		_hwnd = NULL;
	}
	
	PostQuitMessage(0);
}
