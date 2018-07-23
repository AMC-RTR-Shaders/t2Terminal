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
	_chair = NULL;
	_runway = NULL;
	_aeroplaneInstancing = NULL;
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
	//create objects.
	_aeroplane = new Praveen::Aeroplane();
	CHECK_NEW(_aeroplane);

	_chair = new Praveen::Chair();
	CHECK_NEW(_chair);

	_runway = new Rushabh::Runway();
	CHECK_NEW(_runway);
	
	_aeroplaneInstancing = new Harsh::AeroplaneInstanceing();
	CHECK_NEW(_aeroplaneInstancing);

	_test = new Rushabh::Tset();
	CHECK_NEW(_test);
	
	

	//Initializ.
	//_aeroplane->Initialize();
	//_chair->Initialize();
	//_runway->Initialize();
	_aeroplaneInstancing->Initialize();
	//_test->Initialize();

	return;
CLEAN_LOCAL_ALLOCATION_BELOW:
	UnInitialize();
}

void Scene_1::Scene_1::Update()
{
	_aeroplaneInstancing->Update();
}

void Scene_1::Scene_1::ReSize(int width, int height)
{
	_aeroplaneInstancing->ReSize(width, height);
}

void Scene_1::Scene_1::Render(HDC hdc)
{
	_aeroplaneInstancing->Render(hdc);
}

void Scene_1::Scene_1::SceneTransition()
{
	_aeroplaneInstancing->SceneTransition();
}

void Scene_1::Scene_1::UnInitialize()
{
	SAFE_SCENE_DELETE(_aeroplane)
	SAFE_SCENE_DELETE(_chair)
	SAFE_SCENE_DELETE(_runway)
	SAFE_SCENE_DELETE(_aeroplaneInstancing)
	SAFE_SCENE_DELETE(_test)
}
