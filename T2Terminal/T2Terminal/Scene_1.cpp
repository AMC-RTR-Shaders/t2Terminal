#include "Scene_1.h"
/*
* @author: Praveen Suryawanshi
* @mailto: suryawanshi.praveen007@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/


Scene_1::Scene_1::Scene_1()
{
	_aeroplane = NULL;
}

Scene_1::Scene_1::~Scene_1()
{
	UnInitialize();
}

BOOL Scene_1::Scene_1::SceneHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	return 0;
}

void Scene_1::Scene_1::Initialize()
{
	_aeroplane = new Praveen::Aeroplane();
	CHECK_NEW(_aeroplane);

	_aeroplane->Initialize();

	return;
CLEAN_LOCAL_ALLOCATION_BELOW:
	UnInitialize();
}

void Scene_1::Scene_1::Update()
{
	_aeroplane->Update();
}

void Scene_1::Scene_1::ReSize(int width, int height)
{
	_aeroplane->ReSize(width, height);
}

void Scene_1::Scene_1::Render(HDC hdc)
{
	_aeroplane->Render(hdc);
}

void Scene_1::Scene_1::SceneTransition()
{
	_aeroplane->SceneTransition();
}

void Scene_1::Scene_1::UnInitialize()
{
	SAFE_SCENE_DELETE(_aeroplane)
}
