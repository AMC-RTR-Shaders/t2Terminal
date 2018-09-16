/*
* @author: Sanket Deshmukh
* @mailto: 1sanketdeshmukh@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/

#include "Scene_4.h"

Scene_4::Scene_4::Scene_4()
{
	_CreditScene = NULL;
}

Scene_4::Scene_4::~Scene_4()
{
}

BOOL Scene_4::Scene_4::SceneHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	return 0;
}

void Scene_4::Scene_4::Initialize()
{
	_CreditScene = new Sanket::CreditScene();
	CHECK_NEW(_CreditScene);

	_CreditScene->Initialize();

	return;
CLEAN_LOCAL_ALLOCATION_BELOW:
	UnInitialize();

}

void Scene_4::Scene_4::Update()
{
	_CreditScene->Update();
}

void Scene_4::Scene_4::ReSize(int width, int height, struct ResizeAttributes attributes)
{
	_CreditScene->ReSize(width, height, attributes);
}

void Scene_4::Scene_4::Render(HDC hdc, struct Attributes attributes)
{
	_CreditScene->Render(hdc, attributes);
}

void Scene_4::Scene_4::SceneTransition()
{
	_CreditScene->SceneTransition();
}

void Scene_4::Scene_4::UnInitialize()
{
		SAFE_SCENE_DELETE(_CreditScene)
}
