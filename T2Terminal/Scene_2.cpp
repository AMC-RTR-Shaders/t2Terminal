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
	_spotLightBox = NULL;
	_particles = NULL;
	_rollingCylinder = NULL;
	_bluePrint = NULL;
	_scene2Tile = NULL;
	_wireFrameEffect = NULL;
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

	_spotLightBox = new Harsh::SpotLightBox;
	CHECK_NEW(_spotLightBox);

	  _particles = new Rushabh::Particles();
	CHECK_NEW(_particles);

	_rollingCylinder = new Rushabh::RollingCylinder();
	CHECK_NEW(_rollingCylinder);

	_bluePrint = new Rushabh::BluePrint();
	CHECK_NEW(_bluePrint);

	_scene2Tile = new Rushabh::Scene2Tile();
	CHECK_NEW(_scene2Tile);
	
	_wireFrameEffect = new Praveen::WireFrameEffect();
	CHECK_NEW(_wireFrameEffect);


	_spotLight->Initialize();
	_spotLightBox->Initialize();

	_particles->Initialize();
	_rollingCylinder->Initialize();
	_bluePrint->Initialize();
	_scene2Tile->Initialize();
	_wireFrameEffect->Initialize();

	return;
CLEAN_LOCAL_ALLOCATION_BELOW:
	UnInitialize();
}

void Scene_2::Scene_2::Update()
{

	_spotLight->Update();
	_spotLightBox->Update();
    _particles->Update();
	_rollingCylinder->Update();
	_bluePrint->Update();
	//_wireFrameEffect->Update();
}

void Scene_2::Scene_2::ReSize(int width, int height, struct ResizeAttributes attributes)
{
	_spotLight->ReSize(width, height, attributes);
	_spotLightBox->ReSize(width, height,attributes);
	_particles->ReSize(width, height, attributes);
	_rollingCylinder->ReSize(width, height, attributes);
	_bluePrint->ReSize(width, height, attributes);
	_scene2Tile->ReSize(width, height, attributes);
	_wireFrameEffect->ReSize(width, height, attributes);

}

void Scene_2::Scene_2::Render(HDC hdc, struct Attributes attributes)
{
	_spotLight->Render(hdc, attributes);
	_scene2Tile->Render(hdc, attributes);
	_rollingCylinder->Render(hdc, attributes);
	_bluePrint->Render(hdc, attributes);
	if (attributes.currentTransformation == TRANSFORMATION_START_WIRE_FRAME)
	{
		_wireFrameEffect->Render(hdc, attributes);
	}
	else
	{
		_particles->Render(hdc, attributes);
		_spotLightBox->Render(hdc, attributes);
  }
}

void Scene_2::Scene_2::SceneTransition()
{
	_spotLight->SceneTransition();
	_spotLightBox->SceneTransition();
	_rollingCylinder->SceneTransition();
	_particles->SceneTransition();
	_bluePrint->SceneTransition();
	_wireFrameEffect->SceneTransition();
}

void Scene_2::Scene_2::UnInitialize()
{
	SAFE_SCENE_DELETE(_spotLight)
	SAFE_SCENE_DELETE(_spotLightBox)

	SAFE_SCENE_DELETE(_particles)
	SAFE_SCENE_DELETE(_rollingCylinder)
	SAFE_SCENE_DELETE(_bluePrint)

	SAFE_SCENE_DELETE(_scene2Tile)
	SAFE_SCENE_DELETE(_wireFrameEffect)
}
