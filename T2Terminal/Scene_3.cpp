/*
* @author: Praveen Suryawanshi
* @mailto: suryawanshi.praveen007@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/

#include "Scene_3.h"

Scene_3::Scene_3::Scene_3()
{
	_Starfield = NULL;
	_Fonts = NULL;
}

Scene_3::Scene_3::~Scene_3()
{
}

BOOL Scene_3::Scene_3::SceneHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	return 0;
}

void Scene_3::Scene_3::Initialize()
{
	_Starfield = new Sanket::Starfield();
	CHECK_NEW(_Starfield);

	_Fonts = new Sanket::Fonts();
	CHECK_NEW(_Fonts);

	_Starfield->Initialize();
	_Fonts->Initialize();

	return;
CLEAN_LOCAL_ALLOCATION_BELOW:
	UnInitialize();

}

void Scene_3::Scene_3::Update()
{
	_Starfield->Update();
	_Fonts->Update();
}

void Scene_3::Scene_3::ReSize(int width, int height, struct ResizeAttributes attributes)
{
	_Starfield->ReSize(width, height, attributes);
	_Fonts->ReSize(width, height, attributes);
}

void Scene_3::Scene_3::Render(HDC hdc, struct Attributes attributes)
{
	_Starfield->Render(hdc, attributes);
	_Fonts->Render(hdc, attributes);
}

void Scene_3::Scene_3::SceneTransition()
{
	_Starfield->SceneTransition();
	_Fonts->SceneTransition();
}

void Scene_3::Scene_3::UnInitialize()
{
	SAFE_SCENE_DELETE(_Starfield)
	SAFE_SCENE_DELETE(_Fonts)
}
