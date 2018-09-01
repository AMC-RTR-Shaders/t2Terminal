/*
* @author: Praveen Suryawanshi
* @mailto: suryawanshi.praveen007@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/


#include"MainScene.h"

using namespace T2Terminal;

IScene * T2Terminal::IScene::GetInstance(SCENE_NUMBER scene_number)
{
	IScene *scene = NULL;

	switch (scene_number)
	{
	case MAIN:
		scene = new MainScene();
		break;

	case SCENE_1:
		scene = new Scene_1::Scene_1();
		break;

	case SCENE_2:
		scene = new Scene_2::Scene_2();
		break;

	case SCENE_3:
		scene = new Scene_3::Scene_3();
		break;

	default:
		throw std::exception("EXCEPTION : INVALID SCENE NUMBER");
		break;	
	}

	if (scene == NULL)
		std::exception("EXCEPTION : SCENE OBJECT NOT SET");
	
	return scene;
}

T2Terminal::MainScene::MainScene()
{
	_scene = NULL;
	_switch = false;
}

T2Terminal::MainScene::~MainScene()
{
	if (_scene != NULL)
	{
		delete _scene;
		_scene = NULL;
	}

}

BOOL T2Terminal::MainScene::SceneHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	if (_scene != NULL)
	{
		_scene->SceneHandler(hwnd, message, wparam, lparam);
	}

	switch (message)
	{

	case WM_KEYDOWN:
		switch (wparam)
		{


		case Event::KeyBoard::KEYS::T:
			break;
		case VK_UP:
			_attributes.translateCoords[2] += _cam_speed;
			break;
		case VK_DOWN:
			_attributes.translateCoords[2] -= _cam_speed;
			break;
		case VK_LEFT:
			_attributes.translateCoords[0] -= _cam_speed;
			break;
		case VK_RIGHT:
			_attributes.translateCoords[0] += _cam_speed;
			break;
		case Event::KeyBoard::KEYS::P:
			_attributes.translateCoords[1] -= _cam_speed;
			break;
		case Event::KeyBoard::KEYS::L:
			_attributes.translateCoords[1] += _cam_speed;
			break;
		case Event::KeyBoard::KEYS::X:
			_axis = 0;
			break;
		case Event::KeyBoard::KEYS::Y:
			_axis = 1;
			break;
		case Event::KeyBoard::KEYS::Z:
			_axis = 2;
			break;
		case Event::KeyBoard::KEYS::Q:
			if (_axis == 0 || _axis == 1 || _axis == 2)
				_attributes.rotateCoords[_axis] += _cam_speed / 10;
			break;
		case Event::KeyBoard::KEYS::W:
			if (_axis == 0 || _axis == 1 || _axis == 2)
				_attributes.rotateCoords[_axis] -= _cam_speed / 10;
			break;
		}

	default: 
		break;
	
	}

	return false;
}

void T2Terminal::MainScene::Initialize()
{
	InitializeTransformationAttributes();
	InitializeResizeAttributes();

	_scene_1 = T2Terminal::MainScene::GetInstance(SCENE_NUMBER::SCENE_1);
	if(_scene_1)
		_scene_1->Initialize();

	_scene_2 = T2Terminal::MainScene::GetInstance(SCENE_NUMBER::SCENE_2);
	if (_scene_2)
		_scene_2->Initialize();

	_scene_3 = T2Terminal::MainScene::GetInstance(SCENE_NUMBER::SCENE_3);
	if (_scene_3)
		_scene_3->Initialize();

	_scene = _scene_1;

}

void T2Terminal::MainScene::Update()
{
	if (_scene)
	{
		_scene->Update();
	//	UpdateTransformationAttributes();
	}
}

void T2Terminal::MainScene::ReSize(int width, int height, struct ResizeAttributes attributes)
{
	if(_scene)
		_scene->ReSize(width, height, _resizeAttributes);
}

void T2Terminal::MainScene::Render(HDC hdc, struct Attributes attributes)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (_scene)
	{
		_scene->Render(hdc, _attributes);
	}
	SwapBuffers(hdc);
}

void T2Terminal::MainScene::SceneTransition()
{
	if(_scene)
		_scene->SceneTransition();
}

void T2Terminal::MainScene::UnInitialize()
{	
	SAFE_SCENE_DELETE(_scene_1)
	SAFE_SCENE_DELETE(_scene_2)
	SAFE_SCENE_DELETE(_scene_3)
}

void T2Terminal::MainScene::UpdateTransformationAttributes()
{
	if (_attributes.currentScene == SCENE_TERRAIN_MAP)
	{
		if (_attributes.translateCoords[2] < TRANSLATE_Z_TERRAIN_LIMIT)
		{
			_attributes.translateCoords[2] += _cam_speed;
			_attributes.translateCoords[1] -= _cam_speed / 2;
		}
		else
		{
			_attributes.rotateCoords[0] = 0.0f;
			_attributes.rotateCoords[1] = 0.0f;
			_attributes.rotateCoords[2] = 0.0f;

			_attributes.currentScene = SCENE_SINGLE_AEROPLANE;

			_cam_speed = CAM_SPEED_AIRPORT;
		}
	}

	if (_attributes.currentScene == SCENE_SINGLE_AEROPLANE)
	{
		if (_attributes.translateCoords[2] < TRANSLATE_Z_SINGLE_AEROPLANE_LIMIT)
		{
			_attributes.translateCoords[2] -= _cam_speed;
			_attributes.translateCoords[1] -= _cam_speed / 2;
		}
		else
		{
			_attributes.translateCoords[0] = 0.0f;
			_attributes.translateCoords[1] = 0.0f;
			_attributes.translateCoords[2] = TRANSLATE_Z_AIRPORT;

			_attributes.rotateCoords[0] = 0.0f;
			_attributes.rotateCoords[1] = 0.0f;
			_attributes.rotateCoords[2] = 0.0f;

			_attributes.currentScene = SCENE_AIRPORT;

			_cam_speed = CAM_SPEED_AIRPORT;
		}
	}
}

void T2Terminal::MainScene::InitializeTransformationAttributes()
{
	_attributes.translateCoords[0] = 0.0f;
	_attributes.translateCoords[1] = 0.0f;
	_attributes.translateCoords[2] = TRANSLATE_Z_TERRAIN;

	_attributes.rotateCoords[0] = 0.0f;
	_attributes.rotateCoords[1] = 0.0f;
	_attributes.rotateCoords[2] = 0.0f;

	_attributes.currentScene = SCENE_TERRAIN_MAP;

	_cam_speed = CAM_SPEED_TERRAIN;
}

void T2Terminal::MainScene::InitializeResizeAttributes()
{
	_resizeAttributes.farValue = 5000.0f;
	_resizeAttributes.nearValue = 0.1f;
}
