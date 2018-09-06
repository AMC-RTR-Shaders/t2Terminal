/*
* @author: Praveen Suryawanshi
* @mailto: suryawanshi.praveen007@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/

#include "Scene_2.h"

Scene_2::Scene_2::Scene_2()
{
	_spotLight = NULL;
}

Scene_2::Scene_2::~Scene_2()
{
	UnInitialize();
}

BOOL Scene_2::Scene_2::SceneHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	return 0;
}

void Scene_2::Scene_2::Initialize()
{
	_spotLight = new Harsh::SpotLight;
	CHECK_NEW(_spotLight);

	_spotLight->Initialize();

	return;
CLEAN_LOCAL_ALLOCATION_BELOW:
	UnInitialize();
}

void Scene_2::Scene_2::Update()
{
	_spotLight->Update();
}

void Scene_2::Scene_2::ReSize(int width, int height, struct ResizeAttributes attributes)
{
	_spotLight->ReSize(width, height,attributes);
}

void Scene_2::Scene_2::Render(HDC hdc, struct Attributes attributes)
{
	_spotLight->Render(hdc, attributes);
}

void Scene_2::Scene_2::SceneTransition()
{
	_spotLight->SceneTransition();
}

void Scene_2::Scene_2::UnInitialize()
{
	_spotLight->UnInitialize();
}
