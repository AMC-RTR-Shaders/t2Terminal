#include "Scene_1.h"
/*
* @author: Praveen Suryawanshi
* @mailto: suryawanshi.praveen007@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/


Scene_1::Scene_1::Scene_1()
{
	_cube = NULL;
	_aeroplaneInstancing = NULL;
	_quad = NULL;
	_terminalGlass = NULL;
	_airport = NULL;
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
	_cube = new Utility::Cube();
	CHECK_NEW(_cube);
	
	_aeroplaneInstancing = new Harsh::AeroplaneInstanceing();
	CHECK_NEW(_aeroplaneInstancing);

	_cubeTemplate = new Rushabh::CubeTemplate();
	CHECK_NEW(_cubeTemplate);
	
	_quad = new Utility::Quad();
	CHECK_NEW(_quad);

	_terminalGlass = new Rushabh::TerminalGlass();
	CHECK_NEW(_terminalGlass);

	_airport = new Rushabh::Airport();
	CHECK_NEW(_airport);

	//Initializ.
	//_aeroplane->Initialize();
	//_cubeTemplate->Initialize();
	//_quad->Initialize();
	//_terminalGlass->Initialize();
	_aeroplaneInstancing->Initialize();
	_airport->Initialize();

	return;
CLEAN_LOCAL_ALLOCATION_BELOW:
	UnInitialize();
}

void Scene_1::Scene_1::Update()
{
	_terminalGlass->Update();
	_aeroplaneInstancing->Update();
	_airport->Update();
}

void Scene_1::Scene_1::ReSize(int width, int height, struct ResizeAttributes attributes)
{
	_terminalGlass->ReSize(width, height, attributes);
	_aeroplaneInstancing->ReSize(width, height, attributes);
	_airport->ReSize(width, height, attributes);
}

void Scene_1::Scene_1::Render(HDC hdc, struct Attributes attributes)
{
	//_terminalGlass->Render(hdc, attributes);
	_aeroplaneInstancing->Render(hdc, attributes);
	_airport->Render(hdc, attributes);
}

void Scene_1::Scene_1::SceneTransition()
{
	_terminalGlass->SceneTransition();
	_aeroplaneInstancing->SceneTransition();
	_airport->SceneTransition();
}

void Scene_1::Scene_1::UnInitialize()
{
	SAFE_SCENE_DELETE(_cube)
	SAFE_SCENE_DELETE(_aeroplaneInstancing)
	SAFE_SCENE_DELETE(_cubeTemplate)
	SAFE_SCENE_DELETE(_quad)
	SAFE_SCENE_DELETE(_terminalGlass)
	SAFE_SCENE_DELETE(_airport)

}
