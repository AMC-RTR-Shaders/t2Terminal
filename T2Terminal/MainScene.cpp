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
      case 0x31: //KEY 1
			_attributes.numSpotLight = 1;
			_attributes.currentScene = SCENE_LIGHT_POS_1;
			break;
	case 0x32: //KEY 2
			_attributes.numSpotLight = 2;
			_attributes.currentScene = SCENE_LIGHT_POS_2;
			break;
      case 0x33: //KEY 3
			_attributes.numSpotLight = 3;
			_attributes.currentScene = SCENE_LIGHT_POS_3;
			break;
	  case 0x34: //KEY 4
		  _attributes.lightRadius += _cam_speed;
		  break;
	  case 0x35: //KEY 5
		  _attributes.lightRadius -= _cam_speed;
		  break;
		case Event::KeyBoard::KEYS::T:
      break;
		case Event::KeyBoard::KEYS::A:
			++_attributes.currentScene;
			_attributes.currentScene = _attributes.currentScene % 3;
			_attributes.currentScene = 0;
			break;

		case VK_UP:
			_attributes.translateCoords[_attributes.currentScene][2] += _cam_speed;
			break;
		case VK_DOWN:
			_attributes.translateCoords[_attributes.currentScene][2] -= _cam_speed;
			break;
		case VK_LEFT:
			_attributes.translateCoords[_attributes.currentScene][0] -= _cam_speed;
			break;
		case VK_RIGHT:
			_attributes.translateCoords[_attributes.currentScene][0] += _cam_speed;
			break;
		case Event::KeyBoard::KEYS::P:
			_attributes.translateCoords[_attributes.currentScene][1] -= _cam_speed;
			break;
		case Event::KeyBoard::KEYS::L:
			_attributes.translateCoords[_attributes.currentScene][1] += _cam_speed;
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
		case Event::KeyBoard::KEYS::M:
			_cam_speed *= 1.5f;
			break;
		case Event::KeyBoard::KEYS::N:
			_cam_speed /= 1.5f;
			break;
		case Event::KeyBoard::KEYS::Q:
			_attributes.rotateCoords[_attributes.currentScene][_axis] += _cam_speed / 10;
			break;
		case Event::KeyBoard::KEYS::W:
			_attributes.rotateCoords[_attributes.currentScene][_axis] -= _cam_speed / 10;
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
		UpdateTransformationAttributes();
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
	if (_attributes.currentScene == SCENE_TERRAIN_MAP)//SCENE 1
	{
		if (_attributes.translateCoords[SCENE_AIRPORT][2] < Z_END_AIRPORT_1)
		{
			float offset = ((Z_AIRPORT_START - Z_END_AIRPORT_1) / (Y_AIRPORT_START - Y_END_AIRPORT_1));
			_attributes.translateCoords[SCENE_AIRPORT][1] -= _cam_speed;
			_attributes.translateCoords[SCENE_AIRPORT][2] -= _cam_speed * offset;
			_cam_speed *= 1.001f;
		}
		else
		{
			_attributes.currentScene = SCENE_SINGLE_AEROPLANE;
			_attributes.currentTransformation = TRANSFORMATION_SINGLE_AEROPLANE_1;
		}
	}

	if (_attributes.currentScene == SCENE_SINGLE_AEROPLANE)
	{
		if (_attributes.currentTransformation == TRANSFORMATION_SINGLE_AEROPLANE_1)
		{
			if (_attributes.rotateCoords[SCENE_SINGLE_AEROPLANE][2] > Z_END_ROTATE_SINGLE_AEROPLANE_1)
			{
				_attributes.rotateCoords[SCENE_SINGLE_AEROPLANE][2] -= _cam_speed;
				//_cam_speed *= 1.005f;
			}
			else
			{
				_attributes.currentTransformation = TRANSFORMATION_SINGLE_AEROPLANE_2;
			}
		}
		else if (_attributes.currentTransformation == TRANSFORMATION_SINGLE_AEROPLANE_2)
		{
			if (_attributes.rotateCoords[SCENE_SINGLE_AEROPLANE][2] < Z_END_ROTATE_SINGLE_AEROPLANE_2)
			{
				_attributes.rotateCoords[SCENE_SINGLE_AEROPLANE][2] += _cam_speed;
				//_cam_speed *= 1.005f;
			}
			else
			{
				_attributes.currentTransformation = TRANSFORMATION_SINGLE_AEROPLANE_3;
			}
		}
		else if (_attributes.currentTransformation == TRANSFORMATION_SINGLE_AEROPLANE_3)
		{
			if (_attributes.rotateCoords[SCENE_SINGLE_AEROPLANE][2] > Z_END_ROTATE_SINGLE_AEROPLANE_3)
			{
				float offset = (
					(Y_START_ROTATE_SINGLE_AEROPLANE - Y_END_ROTATE_SINGLE_AEROPLANE_3) /
					(Z_END_ROTATE_SINGLE_AEROPLANE_2 - Z_END_ROTATE_SINGLE_AEROPLANE_3));
				_attributes.rotateCoords[SCENE_SINGLE_AEROPLANE][2] -= _cam_speed;
				_attributes.rotateCoords[SCENE_SINGLE_AEROPLANE][1] -= _cam_speed*offset;
				offset = (
					(0.0f - X_END_ROTATE_SINGLE_AEROPLANE_3) /
					(Z_END_ROTATE_SINGLE_AEROPLANE_2 - Z_END_ROTATE_SINGLE_AEROPLANE_3));
				_attributes.rotateCoords[SCENE_SINGLE_AEROPLANE][0] -= _cam_speed*offset;
			}
			else
			{
				_attributes.currentScene = SCENE_TOP_VIEW;
				_attributes.currentTransformation = TRANSFORMATION_TOP_VIEW_1;

			}
		}
	}

	if (_attributes.currentScene == SCENE_TOP_VIEW)
	{
		if (_attributes.currentTransformation == TRANSFORMATION_TOP_VIEW_1)
		{
			if (_attributes.translateCoords[SCENE_AIRPORT][2] < Z_END_AIRPORT_2)
			{
				float offset = ((Y_END_AIRPORT_1 - Y_END_AIRPORT_2) / (Z_END_AIRPORT_1 - Z_END_AIRPORT_2));
				_attributes.translateCoords[SCENE_AIRPORT][1] += _cam_speed * offset;
				_attributes.translateCoords[SCENE_AIRPORT][2] += _cam_speed;
				offset = ((X_END_ROTATE_1 - X_END_ROTATE_2) / (Z_END_AIRPORT_1 - Z_END_AIRPORT_2));
				_attributes.rotateCoords[SCENE_AIRPORT][0] += _cam_speed * offset;

				//AEROPLANE TRANSLATION
				offset = ((-Y_START_SINGLE_PLANE + Y_END_SINGLE_PLANE) / (Z_END_AIRPORT_1 - Z_END_AIRPORT_2));
				_attributes.translateCoords[SCENE_SINGLE_AEROPLANE][1] -= (_cam_speed * offset);

				offset = ((-Z_START_SINGLE_PLANE + Z_END_SINGLE_PLANE) / (Z_END_AIRPORT_1 - Z_END_AIRPORT_2));
				_attributes.translateCoords[SCENE_SINGLE_AEROPLANE][2] -= (_cam_speed * offset);

				_cam_speed *= 1.0005f;
			}
			else
			{
				_attributes.currentTransformation = TRANSFORMATION_TOP_VIEW_2;
			}
		}
		else if (_attributes.currentTransformation == TRANSFORMATION_TOP_VIEW_2)
		{
			if (_attributes.translateCoords[SCENE_AIRPORT][2] < Z_END_AIRPORT_3)
			{
				float offset = ((Y_END_AIRPORT_2 - Y_END_AIRPORT_3) / (Z_END_AIRPORT_2 - Z_END_AIRPORT_3));
				_attributes.translateCoords[SCENE_AIRPORT][1] += _cam_speed * offset;
				_attributes.translateCoords[SCENE_AIRPORT][2] += _cam_speed;
				offset = ((X_END_ROTATE_2 - X_END_ROTATE_3) / (Z_END_AIRPORT_2 - Z_END_AIRPORT_3));
				_attributes.rotateCoords[SCENE_AIRPORT][0] += _cam_speed * offset;

				_cam_speed *= 1.0005f;
			}
			else
			{
				_attributes.currentTransformation = TRANSFORMATION_TOP_VIEW_3;
			}
		}
		else if (_attributes.currentTransformation == TRANSFORMATION_TOP_VIEW_3)
		{
			if (_attributes.translateCoords[SCENE_AIRPORT][2] < Z_END_AIRPORT_4)
			{
				float offset = ((Y_END_AIRPORT_3 - Y_END_AIRPORT_4) / (Z_END_AIRPORT_3 - Z_END_AIRPORT_4));
				_attributes.translateCoords[SCENE_AIRPORT][1] += _cam_speed * offset;
				_attributes.translateCoords[SCENE_AIRPORT][2] += _cam_speed;
				offset = ((X_END_ROTATE_3 - X_END_ROTATE_4) / (Z_END_AIRPORT_3 - Z_END_AIRPORT_4));
				_attributes.rotateCoords[SCENE_AIRPORT][0] += _cam_speed * offset;

				//				_cam_speed *= 1.005f;
			}
			else
			{
				_attributes.currentTransformation = TRANSFORMATION_TOP_VIEW_2;
			}
		}
	}

	if (_attributes.currentScene == SCENE_AIRPORT_MODEL)
	{
		if (_attributes.translateCoords[SCENE_CYLINDER_TRANS][0] < 1.0f)
		{
			_attributes.translateCoords[SCENE_CYLINDER_TRANS][0] += 0.0005f;
			_attributes.translateCoords[SCENE_CYLINDER_TEXCOORD][0] += 0.00025f;
		}
	}
}

void T2Terminal::MainScene::InitializeTransformationAttributes()
{

	_attributes.translateCoords[SCENE_AIRPORT][0] = 0.0f;
	_attributes.translateCoords[SCENE_AIRPORT][1] = Y_AIRPORT_START;
	_attributes.translateCoords[SCENE_AIRPORT][2] = Z_AIRPORT_START;

	_attributes.translateCoords[SCENE_TERRAIN_MAP][0] = 0.0f;
	_attributes.translateCoords[SCENE_TERRAIN_MAP][1] = 4495.0f;
	_attributes.translateCoords[SCENE_TERRAIN_MAP][2] = 6460.0f;

	_attributes.translateCoords[SCENE_SINGLE_AEROPLANE][0] = 0.0f;
	_attributes.translateCoords[SCENE_SINGLE_AEROPLANE][1] = 4580.0f;
	_attributes.translateCoords[SCENE_SINGLE_AEROPLANE][2] = 5400.0f;

	_attributes.rotateCoords[SCENE_AIRPORT][0] = -11.0f;
	_attributes.rotateCoords[SCENE_AIRPORT][1] = 0.0f;
	_attributes.rotateCoords[SCENE_AIRPORT][2] = 0.0f;

	_attributes.rotateCoords[SCENE_SINGLE_AEROPLANE][0] = 0.0f;
	_attributes.rotateCoords[SCENE_SINGLE_AEROPLANE][1] = 180.0f;
	_attributes.rotateCoords[SCENE_SINGLE_AEROPLANE][2] = 0.0f;
	
	_attributes.translateCoords[SCENE_CYLINDER_TRANS][0] = -1.0f;
	_attributes.translateCoords[SCENE_CYLINDER_TEXCOORD][0] = 0.0f;

	_attributes.translateCoords[SCENE_LIGHT_POS_1][0] = -61.0f;
	_attributes.translateCoords[SCENE_LIGHT_POS_1][1] = 64.0f;
	_attributes.translateCoords[SCENE_LIGHT_POS_1][2] = 190.0f;

	_attributes.translateCoords[SCENE_LIGHT_POS_2][0] = 7.0f;
	_attributes.translateCoords[SCENE_LIGHT_POS_2][1] = 64.0f;
	_attributes.translateCoords[SCENE_LIGHT_POS_2][2] = 190.0f;

	_attributes.translateCoords[SCENE_LIGHT_POS_3][0] = 70.0f;
	_attributes.translateCoords[SCENE_LIGHT_POS_3][1] = 64.0f;
	_attributes.translateCoords[SCENE_LIGHT_POS_3][2] = 190.0f;

	_attributes.lightRadius = 1.25f;

	//_attributes.translateCoords[SCENE_AIRPORT][0] = 0.0f;
	//_attributes.translateCoords[SCENE_AIRPORT][1] = Y_END_AIRPORT_3;
	//_attributes.translateCoords[SCENE_AIRPORT][2] = Z_END_AIRPORT_3;

	//_attributes.translateCoords[SCENE_TERRAIN_MAP][0] = 0.0f;
	//_attributes.translateCoords[SCENE_TERRAIN_MAP][1] = 4495.0f;
	//_attributes.translateCoords[SCENE_TERRAIN_MAP][2] = 6460.0f;

	//_attributes.translateCoords[SCENE_SINGLE_AEROPLANE][0] = 0.0f;
	//_attributes.translateCoords[SCENE_SINGLE_AEROPLANE][1] = Y_END_SINGLE_PLANE;
	//_attributes.translateCoords[SCENE_SINGLE_AEROPLANE][2] = Z_END_SINGLE_PLANE;

	//_attributes.rotateCoords[SCENE_AIRPORT][0] = X_END_ROTATE_3;
	//_attributes.rotateCoords[SCENE_AIRPORT][1] = 0.0f;
	//_attributes.rotateCoords[SCENE_AIRPORT][2] = 0.0f;

	//_attributes.rotateCoords[SCENE_SINGLE_AEROPLANE][0] = X_END_ROTATE_SINGLE_AEROPLANE_3;
	//_attributes.rotateCoords[SCENE_SINGLE_AEROPLANE][1] = Y_END_ROTATE_SINGLE_AEROPLANE_3;
	//_attributes.rotateCoords[SCENE_SINGLE_AEROPLANE][2] = Z_END_ROTATE_SINGLE_AEROPLANE_3;

	_attributes.currentScene = SCENE_AIRPORT_MODEL;

	_cam_speed = CAM_SPEED_TERRAIN * 2;

}

void T2Terminal::MainScene::InitializeResizeAttributes()
{
	_resizeAttributes.farValue = 16000.0f;
	_resizeAttributes.nearValue = 0.1f;
}
