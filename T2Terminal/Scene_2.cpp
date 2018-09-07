/*
* @author: Praveen Suryawanshi
* @mailto: suryawanshi.praveen007@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/

#include "Scene_2.h"

Scene_2::Scene_2::Scene_2()
{
	_particles = NULL;
	_rollingCylinder = NULL;
	_bluePrint = NULL;
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
	_particles = new Rushabh::Particles();
	CHECK_NEW(_particles);

	_rollingCylinder = new Rushabh::RollingCylinder();
	CHECK_NEW(_rollingCylinder);

	_bluePrint = new Rushabh::BluePrint();
	CHECK_NEW(_bluePrint);

	_particles->Initialize();

	_rollingCylinder->Initialize();

	_bluePrint->Initialize();

	return;
CLEAN_LOCAL_ALLOCATION_BELOW:
	UnInitialize();
}

void Scene_2::Scene_2::Update()
{
	_particles->Update();
	_rollingCylinder->Update();
	_bluePrint->Update();
}

void Scene_2::Scene_2::ReSize(int width, int height, struct ResizeAttributes attributes)
{
	_particles->ReSize(width, height, attributes);
	_rollingCylinder->ReSize(width, height, attributes);
	_bluePrint->ReSize(width, height, attributes);
}

void Scene_2::Scene_2::Render(HDC hdc, struct Attributes attributes)
{
	_particles->Render(hdc, attributes);
//	_rollingCylinder->Render(hdc, attributes);
//	_bluePrint->Render(hdc, attributes);
}

void Scene_2::Scene_2::SceneTransition()
{
	_rollingCylinder->SceneTransition();
	_particles->SceneTransition();
	_bluePrint->SceneTransition();
}

void Scene_2::Scene_2::UnInitialize()
{
	SAFE_SCENE_DELETE(_particles)
	SAFE_SCENE_DELETE(_rollingCylinder)
	SAFE_SCENE_DELETE(_bluePrint)
}
