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

	case SCENE_4:
		scene = new Scene_4::Scene_4();
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
	_scene_1 = NULL;
	_scene_2 = NULL;
	_scene_3 = NULL;
	_scene_4 = NULL;

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
	  case 0x36: //key 6
		  _attributes.lightDirection[0] -= _cam_speed;
		  break;
	  case 0x37: //key 7
		  _attributes.lightDirection[0] += _cam_speed;
		  break;
	  case 0x38: //key 8
		  _attributes.lightDirection[1] += _cam_speed;
		  break;
	  case 0x39: //key 9
		  _attributes.lightDirection[1] -= _cam_speed;
		  break;
	  case Event::KeyBoard::KEYS::I:
		  _attributes.lightDirection[2] += _cam_speed;
		  break;
	case Event::KeyBoard::KEYS::O:
		_attributes.lightDirection[2] -= _cam_speed;
		break;
	  case Event::KeyBoard::KEYS::R:
		  _attributes.blendValue += _cam_speed;

	  case Event::KeyBoard::KEYS::T:
			_attributes.blendValue -= _cam_speed;
		break;
		case Event::KeyBoard::KEYS::A:
			++_attributes.currentScene;
			_attributes.currentScene = _attributes.currentScene % 4;
			_attributes.currentScene = SCENE_AIRPORT_MODEL;
			break;
		case Event::KeyBoard::KEYS::S:
			_attributes.currentScene = SCENE_BLUE_PRINT;
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
		case Event::KeyBoard::KEYS::H:
			_attributes.globalLight[0] -= 0.1f;
			_attributes.globalLight[1] -= 0.1f;
			_attributes.globalLight[2] -= 0.1f;
			break;

		case Event::KeyBoard::KEYS::J:
			_attributes.globalLight[0] += 0.05f;
			_attributes.globalLight[1] += 0.05f;
			_attributes.globalLight[2] += 0.05f;
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

	_scene_4 = T2Terminal::MainScene::GetInstance(SCENE_NUMBER::SCENE_4);
	if (_scene_4)
		_scene_4->Initialize();
  
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

	_width = width;
	_height = height;
}

void T2Terminal::MainScene::Render(HDC hdc, struct Attributes attributes)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_CULL_FACE);

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
	SAFE_SCENE_DELETE(_scene_4)
}

void T2Terminal::MainScene::UpdateTransformationAttributes()
{
	if (_attributes.globalScene == 1)
	{
//		_cam_speed *= 1.005f;

		if (_attributes.currentScene == SCENE_TERRAIN_MAP)//SCENE 1
		{
			if (_attributes.translateCoords[SCENE_AIRPORT][1] > Y_END_AIRPORT_0_5)
			{
				float offset = ((Y_START_SINGLE_PLANE - Y_SINGLE_PLANE_1) / (Y_AIRPORT_START - Y_END_AIRPORT_0_5));
				_attributes.translateCoords[SCENE_SINGLE_AEROPLANE][1] += _cam_speed*offset;
				offset = ((Z_START_SINGLE_PLANE - Z_SINGLE_PLANE_1) / (Y_AIRPORT_START - Y_END_AIRPORT_0_5));
				_attributes.translateCoords[SCENE_SINGLE_AEROPLANE][2] -= _cam_speed*offset;
			}

			if (_attributes.translateCoords[SCENE_AIRPORT][2] < Z_END_AIRPORT_1)
			{
				float offset = ((Z_AIRPORT_START - Z_END_AIRPORT_1) / (Y_AIRPORT_START - Y_END_AIRPORT_1));
				_attributes.translateCoords[SCENE_AIRPORT][1] -= _cam_speed;
				_attributes.translateCoords[SCENE_AIRPORT][2] -= _cam_speed * offset;

				offset = 1.0f / (float)(Y_AIRPORT_START - Y_END_AIRPORT_1);

				_attributes.PerlinCloudALpha += _cam_speed *offset;

				if (_attributes.PerlinCloudALpha > 1.0f)
					_attributes.PerlinCloudALpha = 1.0f;
			}
			else
			{
				_attributes.currentScene = SCENE_SINGLE_AEROPLANE;
				_attributes.currentTransformation = TRANSFORMATION_SINGLE_AEROPLANE_1;

				_attributes.translateCoords[SCENE_AIRPORT][0] = X_AIRPORT_POS_1;
				_attributes.translateCoords[SCENE_AIRPORT][1] = Y_AIRPORT_POS_1;
				_attributes.translateCoords[SCENE_AIRPORT][2] = Z_AIRPORT_POS_1;

				_attributes.rotateCoords[SCENE_AIRPORT][0] = X_AIRPORT_ROTATE_POS_1;
				_attributes.rotateCoords[SCENE_AIRPORT][1] = Y_AIRPORT_ROTATE_POS_1;
				_attributes.rotateCoords[SCENE_AIRPORT][2] = Z_AIRPORT_ROTATE_POS_1;

				_attributes.translateCoords[SCENE_SINGLE_AEROPLANE][0] = X_SINGLE_PLANE_POS_1_START;
				_attributes.translateCoords[SCENE_SINGLE_AEROPLANE][1] = Y_SINGLE_PLANE_POS_1_START;
				_attributes.translateCoords[SCENE_SINGLE_AEROPLANE][2] = Z_SINGLE_PLANE_POS_1_START;

				_attributes.rotateCoords[SCENE_SINGLE_AEROPLANE][0] = X_SINGLE_PLANE_ROTATE_POS_1;
				_attributes.rotateCoords[SCENE_SINGLE_AEROPLANE][1] = Y_SINGLE_PLANE_ROTATE_POS_1;
				_attributes.rotateCoords[SCENE_SINGLE_AEROPLANE][2] = Z_SINGLE_PLANE_ROTATE_POS_1;
			}
		}

		if (_attributes.currentScene == SCENE_SINGLE_AEROPLANE)
		{
			if (_attributes.currentTransformation == TRANSFORMATION_SINGLE_AEROPLANE_1)
			{
				if (_attributes.translateCoords[SCENE_SINGLE_AEROPLANE][0] < X_SINGLE_PLANE_POS_1_END)
				{
					_attributes.translateCoords[SCENE_SINGLE_AEROPLANE][0] += _cam_speed;
					float offset = (
							(Y_SINGLE_PLANE_POS_1_END - Y_SINGLE_PLANE_POS_1_START) /
							(X_SINGLE_PLANE_POS_1_END - X_SINGLE_PLANE_POS_1_START));
					_attributes.translateCoords[SCENE_SINGLE_AEROPLANE][1] += _cam_speed*offset;
					if(_attributes.PerlinCloudSpeed < 0.05f)
						_attributes.PerlinCloudSpeed += _cam_speed / 5000;
					if (_attributes.PerlinCloudALpha > 0.2f)
						_attributes.PerlinCloudALpha -= _cam_speed / 100;
				}
				else
				{
					if (_attributes.PerlinCloudALpha < 1.0f)
					{
						_attributes.PerlinCloudALpha += _cam_speed / 100;
					}
					else
					{
						_attributes.translateCoords[SCENE_AIRPORT][0] = X_AIRPORT_POS_2;
						_attributes.translateCoords[SCENE_AIRPORT][1] = Y_AIRPORT_POS_2;
						_attributes.translateCoords[SCENE_AIRPORT][2] = Z_AIRPORT_POS_2;

						_attributes.rotateCoords[SCENE_AIRPORT][0] = X_AIRPORT_ROTATE_POS_2;
						_attributes.rotateCoords[SCENE_AIRPORT][1] = Y_AIRPORT_ROTATE_POS_2;
						_attributes.rotateCoords[SCENE_AIRPORT][2] = Z_AIRPORT_ROTATE_POS_2;
						_attributes.currentTransformation = TRANSFORMATION_SINGLE_AEROPLANE_2;
						_attributes.currentSequenceCounter = 0.0f;
						_attributes.PerlinCloudSpeed = 0.005f;
					}
				}
			}
			else if (_attributes.currentTransformation == TRANSFORMATION_SINGLE_AEROPLANE_2)
			{
				if (_attributes.currentSequenceCounter < 500.0f)
				{
					if (_attributes.PerlinCloudALpha > 0.0f)
					{
						_attributes.PerlinCloudALpha -= _cam_speed / 100;
					}
					_attributes.translateCoords[SCENE_AIRPORT][2] += _cam_speed;
					_attributes.currentSequenceCounter += _cam_speed;
				}
				else
				{
					if (_attributes.PerlinCloudALpha < 1.0f)
					{
						_attributes.PerlinCloudALpha += _cam_speed / 100;
					}
					else
					{
						_attributes.currentTransformation = TRANSFORMATION_SINGLE_AEROPLANE_3;

						_attributes.translateCoords[SCENE_AIRPORT][0] = X_AIRPORT_POS_3_START;
						_attributes.translateCoords[SCENE_AIRPORT][1] = Y_AIRPORT_POS_3_START;
						_attributes.translateCoords[SCENE_AIRPORT][2] = Z_AIRPORT_POS_3_START;

						_attributes.rotateCoords[SCENE_AIRPORT][0] = X_AIRPORT_ROTATE_POS_3;
						_attributes.rotateCoords[SCENE_AIRPORT][1] = Y_AIRPORT_ROTATE_POS_3;
						_attributes.rotateCoords[SCENE_AIRPORT][2] = Z_AIRPORT_ROTATE_POS_3;

						_attributes.translateCoords[SCENE_SINGLE_AEROPLANE][0] = X_SINGLE_PLANE_POS_2_START;
						_attributes.translateCoords[SCENE_SINGLE_AEROPLANE][1] = Y_SINGLE_PLANE_POS_2_START;
						_attributes.translateCoords[SCENE_SINGLE_AEROPLANE][2] = Z_SINGLE_PLANE_POS_2_START;

						_attributes.rotateCoords[SCENE_SINGLE_AEROPLANE][0] = X_SINGLE_PLANE_ROTATE_POS_2_START;
						_attributes.rotateCoords[SCENE_SINGLE_AEROPLANE][1] = Y_SINGLE_PLANE_ROTATE_POS_2_START;
						_attributes.rotateCoords[SCENE_SINGLE_AEROPLANE][2] = Z_SINGLE_PLANE_ROTATE_POS_2_START;		
						_cam_speed = CAM_SPEED_LANDING;

						_attributes.scaleCoords[0] = 3.0f;
						_attributes.scaleCoords[1] = 3.0f;
						_attributes.scaleCoords[2] = 3.0f;
					}
				}
			}
			else if (_attributes.currentTransformation == TRANSFORMATION_SINGLE_AEROPLANE_3)
			{
				if (_attributes.translateCoords[SCENE_AIRPORT][1] < Y_AIRPORT_POS_3_END)
				{
					if (_attributes.PerlinCloudALpha > 0.0f)
					{
						_attributes.PerlinCloudALpha -= _cam_speed / 50;
					}

					_attributes.translateCoords[SCENE_AIRPORT][1] += _cam_speed;

					float offset = (
						(Z_AIRPORT_POS_3_START - Z_AIRPORT_POS_3_END) /
						(Y_AIRPORT_POS_3_END - Y_AIRPORT_POS_3_START));
					_attributes.translateCoords[SCENE_AIRPORT][2] -= _cam_speed*offset;

					offset = (
						(X_SINGLE_PLANE_POS_2_START - X_SINGLE_PLANE_POS_2_END) /
						(Y_AIRPORT_POS_3_END - Y_AIRPORT_POS_3_START));
					_attributes.translateCoords[SCENE_SINGLE_AEROPLANE][0] -= _cam_speed*offset;
					offset = (
						(Y_SINGLE_PLANE_POS_2_START - Y_SINGLE_PLANE_POS_2_END) /
						(Y_AIRPORT_POS_3_END - Y_AIRPORT_POS_3_START));
					_attributes.translateCoords[SCENE_SINGLE_AEROPLANE][1] -= _cam_speed*offset;
					offset = (
						(Z_SINGLE_PLANE_POS_2_START - Z_SINGLE_PLANE_POS_2_END) /
						(Y_AIRPORT_POS_3_END - Y_AIRPORT_POS_3_START));
					_attributes.translateCoords[SCENE_SINGLE_AEROPLANE][2] -= _cam_speed*offset;
					offset = (
						(Z_SINGLE_PLANE_ROTATE_POS_2_END - Z_SINGLE_PLANE_ROTATE_POS_2_START) /
						(Y_AIRPORT_POS_3_END - Y_AIRPORT_POS_3_START));
					_attributes.rotateCoords[SCENE_SINGLE_AEROPLANE][2] += _cam_speed*offset;

				}
				else
				{
					_attributes.currentTransformation = TRANSFORMATION_SINGLE_AEROPLANE_4;
				}
			}
			else if (_attributes.currentTransformation == TRANSFORMATION_SINGLE_AEROPLANE_4)
			{
				if (_attributes.translateCoords[SCENE_SINGLE_AEROPLANE][0] < X_SINGLE_PLANE_POS_3_END)
				{
					_attributes.translateCoords[SCENE_SINGLE_AEROPLANE][0] += 5*_cam_speed;
				}
				else
				{
					if (_attributes.PerlinCloudALpha < 0.5f)
					{
						_attributes.PerlinCloudALpha += _cam_speed / 50;
					}
					else
					{
						_attributes.currentScene = SCENE_TOP_VIEW;
						_attributes.currentTransformation = TRANSFORMATION_TOP_VIEW_2;

						_attributes.translateCoords[SCENE_AIRPORT][0] = X_END_AIRPORT_2;
						_attributes.translateCoords[SCENE_AIRPORT][1] = Y_END_AIRPORT_2;
						_attributes.translateCoords[SCENE_AIRPORT][2] = Z_END_AIRPORT_2;

						_attributes.rotateCoords[SCENE_AIRPORT][0] = X_END_ROTATE_2;
						_attributes.rotateCoords[SCENE_AIRPORT][1] = 0.0f;
						_attributes.rotateCoords[SCENE_AIRPORT][2] = 0.0f;

						_attributes.translateCoords[SCENE_AIRPORT_CUBEMAP][1] = 0.0f;
						_cam_speed = _cam_speed / 4;
					}
				}
			}

		}

		if (_attributes.currentScene == SCENE_TOP_VIEW)
		{
			if (_attributes.currentTransformation == TRANSFORMATION_TOP_VIEW_2)
			{
				if (_attributes.PerlinCloudALpha  > 0.0f)
				{
					_attributes.PerlinCloudALpha -= _cam_speed / 50;
				}

				if (_attributes.translateCoords[SCENE_AIRPORT][2] < Z_END_AIRPORT_3)
				{
					float offset = ((Y_END_AIRPORT_2 - Y_END_AIRPORT_3) / (Z_END_AIRPORT_2 - Z_END_AIRPORT_3));
					_attributes.translateCoords[SCENE_AIRPORT][1] += _cam_speed * offset;
					_attributes.translateCoords[SCENE_AIRPORT][2] += _cam_speed;
					offset = ((X_END_ROTATE_2 - X_END_ROTATE_3) / (Z_END_AIRPORT_2 - Z_END_AIRPORT_3));
					_attributes.rotateCoords[SCENE_AIRPORT][0] += _cam_speed * offset;

					offset = ((X_END_SINGLE_PLANE - X_END_SINGLE_PLANE_2) / (Z_END_AIRPORT_2 - Z_END_AIRPORT_3));
					_attributes.translateCoords[SCENE_SINGLE_AEROPLANE][0] += _cam_speed * offset;

					offset = ((Z_END_SINGLE_PLANE - Z_END_SINGLE_PLANE_2) / (Z_END_AIRPORT_2 - Z_END_AIRPORT_3));
					_attributes.translateCoords[SCENE_SINGLE_AEROPLANE][2] += _cam_speed * offset;

//					_cam_speed *= 1.0005f;
				}
				else
				{
					_attributes.currentTransformation = TRANSFORMATION_TOP_VIEW_3;
				}
			}
			else if (_attributes.currentTransformation == TRANSFORMATION_TOP_VIEW_3)
			{
				if (_attributes.blendValue > BLEND_VALUE_CUBE_MAP_MIN)
				{
					_attributes.blendValue -= _cam_speed / 600;
					_attributes.lightAmbient[0] -= _cam_speed / 600;
					_attributes.lightAmbient[1] -= _cam_speed / 600;
					_attributes.lightAmbient[2] -= _cam_speed / 600;

					if (_attributes.lightAmbient[0] < 0.0f)
					{
						_attributes.lightAmbient[0] = 0.0f;
						_attributes.lightAmbient[1] = 0.0f;
						_attributes.lightAmbient[2] = 0.0f;
					}
				}
				else if (_attributes.translateCoords[SCENE_AIRPORT][2] < Z_END_AIRPORT_4)
				{
					float offset = ((Y_END_AIRPORT_3 - Y_END_AIRPORT_4) / (Z_END_AIRPORT_3 - Z_END_AIRPORT_4));
					_attributes.translateCoords[SCENE_AIRPORT][1] += _cam_speed * offset;
					_attributes.translateCoords[SCENE_AIRPORT][2] += _cam_speed;
					offset = ((X_END_ROTATE_3 - X_END_ROTATE_4) / (Z_END_AIRPORT_3 - Z_END_AIRPORT_4));
					_attributes.rotateCoords[SCENE_AIRPORT][0] += _cam_speed * offset;
					offset = ((X_END_AIRPORT_4) / (Z_END_AIRPORT_3 - Z_END_AIRPORT_4));
					_attributes.translateCoords[SCENE_AIRPORT][0] -= _cam_speed * offset;
				}
				else
				{
					_attributes.translateCoords[SCENE_AIRPORT][1] = Y_END_AIRPORT_4;
					_attributes.translateCoords[SCENE_AIRPORT][2] = Z_END_AIRPORT_4;
					_attributes.currentTransformation = TRANSFORMATION_TOP_VIEW_4;
					_attributes.currentSequenceCounter = 0;
				}
			}
			else if (_attributes.currentTransformation == TRANSFORMATION_TOP_VIEW_4)
			{
				if (_attributes.currentSequenceCounter < 250.0f)
				{
					_attributes.currentSequenceCounter += _cam_speed / 2;
				}
				else if (_attributes.currentSequenceCounter < 500.0f)
				{
					_attributes.currentSequenceCounter += _cam_speed / 2;
					_attributes.numSpotLight = 1;
				}
				else if (_attributes.currentSequenceCounter < 750.0f)
				{
					_attributes.currentSequenceCounter += _cam_speed / 2;
					_attributes.numSpotLight = 2;
				}
				else if (_attributes.currentSequenceCounter < 1100.0f)
				{
					_attributes.numSpotLight = 3;
					_attributes.currentSequenceCounter += _cam_speed / 2;
				}
				else
				{
					_scene = _scene_2;

					_cam_speed = CAM_SPEED_AIRPORT_MODEL;

					_attributes.globalScene = 2;
					_attributes.currentScene = SCENE_AIRPORT_MODEL;
					_attributes.blendValue = BLEND_VALUE_BOX;
					_attributes.currentSequenceCounter = 0.0f;
					_attributes.numSpotLight = 0;

					_attributes.globalLight[0] = 1.0f;
					_attributes.globalLight[1] = 1.0f;
					_attributes.globalLight[2] = 1.0f;

					_scene->ReSize(_width, _height, _resizeAttributes);

				}
			}
		}
	}
/****************************************************SCENE 2 STARTS *******************************************************************/
	
	if (_attributes.globalScene == 2)
	{
		if (_attributes.currentScene == SCENE_AIRPORT_MODEL)
		{
			if (_attributes.currentSequenceCounter > PARTICLE_LIGHT_3_ON)
			{
				_attributes.numSpotLight = 3;
			}
			else if (_attributes.currentSequenceCounter > PARTICLE_LIGHT_2_ON)
			{
				_attributes.numSpotLight = 2;
			}
			else if (_attributes.currentSequenceCounter > PARTICLE_LIGHT_1_ON)
			{
				_attributes.numSpotLight = 1;
			}

			if (_attributes.currentSequenceCounter < PARTICLE_LIGHT_3_ON)
			{
				_attributes.currentSequenceCounter += _cam_speed;
			}
			else
			{
				_attributes.numSpotLight = 3;
				_attributes.currentScene = SCENE_BLUE_PRINT;
				_cam_speed /= 1.5;
			}
		}

		if (_attributes.currentScene == SCENE_BLUE_PRINT)
		{
			if (_attributes.translateCoords[SCENE_AIRPORT_MODEL][2] < Z_END_AIRPORT_MODEL_1)
			{
				float offset = ((Y_START_AIRPORT_MODEL - Y_END_AIRPORT_MODEL_1) / (Z_START_AIRPORT_MODEL - Z_END_AIRPORT_MODEL_1));
				_attributes.translateCoords[SCENE_AIRPORT_MODEL][1] += _cam_speed * offset;
				_attributes.translateCoords[SCENE_AIRPORT_MODEL][2] += _cam_speed;
			}
			if (_attributes.translateCoords[SCENE_CYLINDER_TRANS][0] < TRANS_X_BLUE_PRINT)
			{
				_attributes.translateCoords[SCENE_CYLINDER_TRANS][0] += 0.001f;
				_attributes.translateCoords[SCENE_CYLINDER_TEXCOORD][0] += 0.0005f / 4.5f;
			}
			else if (_attributes.translateCoords[SCENE_AIRPORT_MODEL][2] > Z_END_AIRPORT_MODEL_1)
			{
				_attributes.currentScene = SCENE_WIRE_FRAME;
			}
		}
		if (_attributes.currentScene == SCENE_WIRE_FRAME)
		{
			if (_attributes.currentTransformation == TRANSFORMATION_START_WIRE_FRAME)
			{
				if (_attributes.translateCoords[SCENE_AIRPORT_MODEL][2] > Z_END_AIRPORT_MODEL_3)
				{
					_attributes.translateCoords[SCENE_AIRPORT_MODEL][2] -= _cam_speed / 16;
					float offset = ((Y_END_AIRPORT_MODEL_2 - Y_END_AIRPORT_MODEL_3) / (Z_END_AIRPORT_MODEL_2 - Z_END_AIRPORT_MODEL_3));
					_attributes.translateCoords[SCENE_AIRPORT_MODEL][1] -= (_cam_speed / 16) * offset;
				}
				else
				{
					if (_attributes.currentSequenceCounter < START_SCENE_3)
					{
						_attributes.currentSequenceCounter += _cam_speed;
						if (_attributes.currentSequenceCounter > START_SCENE_3)
						{
							_scene = _scene_3;

							_cam_speed = CAM_SPEED_PHOTO_ROOM;
							
							_attributes.globalScene = 3;
							_attributes.currentScene = SCENE_PHOTO_ROOM;
							_attributes.currentSequenceCounter = 0.0f;
							_attributes.currentTransformation = TRANSFORMATION_INCREASE_SPOT_LIGHT;
							_zLimit = 2.0f;
							_attributes.globalLight[0] = 0.2f;
							_attributes.globalLight[1] = 0.2f;
							_attributes.globalLight[2] = 0.2f;

							_attributes.lightDirection[0] = 0.0f;
							_attributes.lightDirection[1] = -1.0f;
							_attributes.lightDirection[2] = 0.0f;

							_attributes.lightRadius = 15.0f;
							
							_scene->ReSize(_width, _height, _resizeAttributes);
						}
					}

				}

				if (_attributes.translateCoords[SCENE_AIRPORT_TOP][1] > Y_AIRPORT_TOP_END)
				{
					_attributes.translateCoords[SCENE_AIRPORT_TOP][1] -= (_cam_speed / 8);
				}
				_cam_speed *= 1.0001f;
			}
			else if (_attributes.translateCoords[SCENE_AIRPORT_MODEL][2] < Z_END_AIRPORT_MODEL_2)
			{
				float offset = ((Y_END_AIRPORT_MODEL_1 - Y_END_AIRPORT_MODEL_2) / (Z_END_AIRPORT_MODEL_1 - Z_END_AIRPORT_MODEL_2));
				_attributes.translateCoords[SCENE_AIRPORT_MODEL][1] += _cam_speed * offset;
				_attributes.translateCoords[SCENE_AIRPORT_MODEL][2] += _cam_speed;
				offset = ((0.0f - BLEND_VALUE_BOX) / (Z_END_AIRPORT_MODEL_1 - Z_END_AIRPORT_MODEL_2));
				_attributes.blendValue -= _cam_speed*offset;
				_cam_speed *= 1.0001f;
			}
			else
			{
				_attributes.currentTransformation = TRANSFORMATION_START_WIRE_FRAME;
			}
		}
	}

	/****************************************************SCENE 3 STARTS *******************************************************************/

	if (_attributes.globalScene == 3)
	{
		if (_attributes.currentTransformation == TRANSFORMATION_INCREASE_SPOT_LIGHT)
		{
			if (_attributes.currentSequenceCounter < _zLimit)
			{
				_attributes.currentSequenceCounter += _cam_speed;
			}
			else
			{
				_zLimit += 2.0f;
				_attributes.numSpotLight++;
				if (_attributes.numSpotLight == 25)
				{
					_attributes.currentTransformation = TRANSFORMATION_DECREASE_SPOT_LIGHT;
					_attributes.currentSequenceCounter = 0.0f;
					_zLimit = 2.0f;
				}
			}
		}

		if (_attributes.currentTransformation == TRANSFORMATION_DECREASE_SPOT_LIGHT)
		{
			if (_attributes.currentSequenceCounter < _zLimit)
			{
				_attributes.currentSequenceCounter += _cam_speed;
			}
			else
			{
				_zLimit += 2.0f;
				_attributes.numSpotLight--;
				if (_attributes.numSpotLight == 0)
				{
					_attributes.currentTransformation = TRANSFORMATION_INCREASE_AMBIENT;
					_attributes.numSpotLight = 25;
				}
			}
		}
		if (_attributes.currentTransformation == TRANSFORMATION_INCREASE_AMBIENT)
		{
			if (_attributes.globalLight[0] < 0.9f)
			{
				_attributes.globalLight[0] += _cam_speed/20;
				_attributes.globalLight[1] += _cam_speed/20;
				_attributes.globalLight[2] += _cam_speed/20;
			}
			else
			{
				_attributes.numSpotLight = 0;
				_attributes.currentTransformation = TRANSFORMATION_PHOTO_ROTATE;
				_cam_speed = _cam_speed / 5;
			}
		}
		if (_attributes.currentTransformation == TRANSFORMATION_PHOTO_ROTATE)
		{
			if (_attributes.translateCoords[SCENE_PHOTO_ROOM][2] < Z_END_PHOTO_ROOM_1)
			{
				_attributes.translateCoords[SCENE_PHOTO_ROOM][2] += _cam_speed;
				float offset = ((X_END_PHOTO_ROOM_1 - X_START_PHOTO_ROOM_1) / (Z_END_PHOTO_ROOM_1 - Z_START_PHOTO_ROOM_1));
				_attributes.translateCoords[SCENE_PHOTO_ROOM][0] += _cam_speed * offset;
				offset = ((Y_END_PHOTO_ROOM_1 - Y_START_PHOTO_ROOM_1) / (Z_END_PHOTO_ROOM_1 - Z_START_PHOTO_ROOM_1));
				_attributes.translateCoords[SCENE_PHOTO_ROOM][1] += _cam_speed * offset;
				offset = ((Y_ROTATE_END_PHOTO_ROOM_1 - Y_ROTATE_START_PHOTO_ROOM_1) / (Z_END_PHOTO_ROOM_1 - Z_START_PHOTO_ROOM_1));
				_attributes.rotateCoords[SCENE_PHOTO_ROOM][1] += _cam_speed * offset;
			}
			else
			{
				_attributes.currentTransformation = TRANSFORMATION_TRANSLATE_FWD;
			}
		}
		if (_attributes.currentTransformation == TRANSFORMATION_TRANSLATE_FWD)
		{
			if (_attributes.translateCoords[SCENE_PHOTO_ROOM][2] < Z_START_PHOTO_ROOM_2)
			{
				_attributes.translateCoords[SCENE_PHOTO_ROOM][2] += _cam_speed;
				float offset = ((X_END_PHOTO_ROOM_1 - X_START_PHOTO_ROOM_2) / (Z_END_PHOTO_ROOM_1 - Z_START_PHOTO_ROOM_2));
				_attributes.translateCoords[SCENE_PHOTO_ROOM][0] += _cam_speed * offset;
			}
			else
			{
				_attributes.currentTransformation = TRANSFORMATION_PHOTO_ROTATE_2;
				_cam_speed /= 2;
			}
		}
		if (_attributes.currentTransformation == TRANSFORMATION_PHOTO_ROTATE_2)
		{
			if (_attributes.translateCoords[SCENE_PHOTO_ROOM][2] < Z_END_PHOTO_ROOM_2)
			{
				_attributes.translateCoords[SCENE_PHOTO_ROOM][2] += _cam_speed;
				float offset = ((X_END_PHOTO_ROOM_2 - X_START_PHOTO_ROOM_2) / (Z_END_PHOTO_ROOM_2 - Z_START_PHOTO_ROOM_2));
				_attributes.translateCoords[SCENE_PHOTO_ROOM][0] += _cam_speed * offset;
				offset = ((Y_END_PHOTO_ROOM_2 - Y_END_PHOTO_ROOM_1) / (Z_END_PHOTO_ROOM_2 - Z_START_PHOTO_ROOM_2));
				_attributes.translateCoords[SCENE_PHOTO_ROOM][1] += _cam_speed * offset;
				offset = ((Y_ROTATE_END_PHOTO_ROOM_2 - Y_ROTATE_END_PHOTO_ROOM_1) / (Z_END_PHOTO_ROOM_2 - Z_START_PHOTO_ROOM_2));
				_attributes.rotateCoords[SCENE_PHOTO_ROOM][1] += _cam_speed * offset;
			}
			else
			{
				_attributes.currentScene = SCENE_STAR_FIELD;
			}
		}
		if (_attributes.currentScene == SCENE_STAR_FIELD)
		{
			if (_attributes.translateCoords[SCENE_STAR_FIELD][2] > 40.0f)
			{
				_scene = _scene_4;
				_attributes.globalScene = 4;
				_scene->ReSize(_width, _height, _resizeAttributes);
			}
			else
			{
				_attributes.translateCoords[SCENE_STAR_FIELD][2] += 0.08f;
			}
		}
	}
}

void T2Terminal::MainScene::InitializeTransformationAttributes()
{
	_attributes.scaleCoords[0] = 1.0f;
	_attributes.scaleCoords[1] = 1.0f;
	_attributes.scaleCoords[2] = 1.0f;

	_attributes.translateCoords[SCENE_BLUE_PRINT][0] = 0.0f;
	_attributes.translateCoords[SCENE_BLUE_PRINT][1] = 0.0f;
	_attributes.translateCoords[SCENE_BLUE_PRINT][2] = 0.0f;

	_attributes.translateCoords[SCENE_AIRPORT][0] = 0.0f;
	_attributes.translateCoords[SCENE_AIRPORT][1] = Y_AIRPORT_START;
	_attributes.translateCoords[SCENE_AIRPORT][2] = Z_AIRPORT_START;

	_attributes.translateCoords[SCENE_AIRPORT_CUBEMAP][1] = -15900.0f;

	_attributes.translateCoords[SCENE_TERRAIN_MAP][0] = 0.0f;
	_attributes.translateCoords[SCENE_TERRAIN_MAP][1] = 4495.0f;
	_attributes.translateCoords[SCENE_TERRAIN_MAP][2] = 6460.0f;

	_attributes.translateCoords[SCENE_SINGLE_AEROPLANE][0] = 0.0f;
	_attributes.translateCoords[SCENE_SINGLE_AEROPLANE][1] = 4580.0f;
	_attributes.translateCoords[SCENE_SINGLE_AEROPLANE][2] = 5400.0f;

	_attributes.translateCoords[SCENE_PERLIN_CLOUD][0] = 0.0f;
	_attributes.translateCoords[SCENE_PERLIN_CLOUD][1] = 0.0f;
	_attributes.translateCoords[SCENE_PERLIN_CLOUD][2] = -6.0f;


	_attributes.translateCoords[SCENE_AIRPORT_MODEL][0] = 0.0f;
	_attributes.translateCoords[SCENE_AIRPORT_MODEL][1] = 0.0f;
	_attributes.translateCoords[SCENE_AIRPORT_MODEL][2] = -20.0f;

	_attributes.translateCoords[SCENE_TABLE][0] = 0.0f;
	_attributes.translateCoords[SCENE_TABLE][1] = -2.1f;
	_attributes.translateCoords[SCENE_TABLE][2] = 6.0f;

	_attributes.rotateCoords[SCENE_AIRPORT][0] = -11.0f;
	_attributes.rotateCoords[SCENE_AIRPORT][1] = 0.0f;
	_attributes.rotateCoords[SCENE_AIRPORT][2] = 0.0f;

	_attributes.rotateCoords[SCENE_TERRAIN_MAP][0] = -10.0f;
	_attributes.rotateCoords[SCENE_TERRAIN_MAP][1] = 0.0f;
	_attributes.rotateCoords[SCENE_TERRAIN_MAP][2] = 0.0f;

	_attributes.rotateCoords[SCENE_SINGLE_AEROPLANE][0] = X_START_ROTATE_SINGLE_AEROPLANE;
	_attributes.rotateCoords[SCENE_SINGLE_AEROPLANE][1] = Y_START_ROTATE_SINGLE_AEROPLANE;
	_attributes.rotateCoords[SCENE_SINGLE_AEROPLANE][2] = 0.0f;
	
	_attributes.translateCoords[SCENE_CYLINDER_TRANS][0] = -TRANS_X_BLUE_PRINT;
	_attributes.translateCoords[SCENE_CYLINDER_TEXCOORD][0] = 0.0f;

	_attributes.translateCoords[SCENE_LIGHT_POS_1][0] = -61.0f;
	_attributes.translateCoords[SCENE_LIGHT_POS_1][1] = -120.50f;
	_attributes.translateCoords[SCENE_LIGHT_POS_1][2] = 352.4708f;

	_attributes.translateCoords[SCENE_LIGHT_POS_2][0] = 3.7741f;
	_attributes.translateCoords[SCENE_LIGHT_POS_2][1] = -120.50f;
	_attributes.translateCoords[SCENE_LIGHT_POS_2][2] = 352.4708f;

	_attributes.translateCoords[SCENE_LIGHT_POS_3][0] = 81.79f;
	_attributes.translateCoords[SCENE_LIGHT_POS_3][1] = -120.50f;
	_attributes.translateCoords[SCENE_LIGHT_POS_3][2] = 352.4708f;

	_attributes.translateCoords[SCENE_LIGHT_POS_4][0] = -8.54f;
	_attributes.translateCoords[SCENE_LIGHT_POS_4][1] = 5.73f,
	_attributes.translateCoords[SCENE_LIGHT_POS_4][2] = -85.032f;

	_attributes.lightRadius = 4.9582f;

	_attributes.translateCoords[SCENE_AIRPORT_TOP][0] = 0.0f;
	_attributes.translateCoords[SCENE_AIRPORT_TOP][1] = 10.0f;
	_attributes.translateCoords[SCENE_AIRPORT_TOP][2] = 0.0f;
  
	_attributes.rotateCoords[SCENE_AIRPORT_MODEL][0] = 10.0f;
	_attributes.rotateCoords[SCENE_AIRPORT_MODEL][1] = 0.0f;
	_attributes.rotateCoords[SCENE_AIRPORT_MODEL][2] = 0.0f;


	_attributes.translateCoords[SCENE_PHOTO_ROOM][0] = 0.0f;
	_attributes.translateCoords[SCENE_PHOTO_ROOM][1] = 0.0f;
	_attributes.translateCoords[SCENE_PHOTO_ROOM][2] = -51.0f;

	_attributes.rotateCoords[SCENE_PHOTO_ROOM][0] = 0.0f;
	_attributes.rotateCoords[SCENE_PHOTO_ROOM][1] = 0.0f;
	_attributes.rotateCoords[SCENE_PHOTO_ROOM][2] = 0.0f;

	_attributes.translateCoords[SCENE_STAR_FIELD][2] = -800.0f;

	//_attributes.translateCoords[SCENE_PHOTO_ROOM][0] = X_START_PHOTO_ROOM_2;
	//_attributes.translateCoords[SCENE_PHOTO_ROOM][1] = Y_END_PHOTO_ROOM_1;
	//_attributes.translateCoords[SCENE_PHOTO_ROOM][2] = Z_START_PHOTO_ROOM_2;

	//_attributes.rotateCoords[SCENE_PHOTO_ROOM][0] = 0.0f;
	//_attributes.rotateCoords[SCENE_PHOTO_ROOM][1] = Y_ROTATE_END_PHOTO_ROOM_1;
	//_attributes.rotateCoords[SCENE_PHOTO_ROOM][2] = 0.0f;


	_attributes.lightDirection[0] = -0.0147f;
	_attributes.lightDirection[1] = 0.7166f;
	_attributes.lightDirection[2] = -1.496f;


	_attributes.numSpotLight = 0;

	_attributes.currentSequenceCounter = 0.0f;
	_attributes.blendValue = BLEND_VALUE_CUBE_MAP;
	_attributes.currentScene = SCENE_TERRAIN_MAP;
	
	_attributes.lightAmbient[0] = 0.35f;
	_attributes.lightAmbient[1] = 0.35f;
	_attributes.lightAmbient[2] = 0.35f;
	_attributes.lightAmbient[3] = 1.0f;

	_attributes.globalLight[0] = 1.0f;
	_attributes.globalLight[1] = 1.0f;
	_attributes.globalLight[2] = 1.0f;

	_attributes.PerlinCloudALpha	 =  0.0f;
	_attributes.PerlinCloudDirection =  1 ;		//_CloudDirection i.e. TOP-TO-BOTTOM  OR BOTTOM-TO-TOP
	_attributes.PerlinCloudSpeed	 =  0.005f;		//SPEED OF THE CLOUD	


	_cam_speed = CAM_SPEED_TERRAIN;
	_attributes.globalScene = 1;

/****************SCENE 2  INITIALIAZATION *************/

	/*_cam_speed = CAM_SPEED_AIRPORT_MODEL;

	_attributes.globalScene = 2;
	_attributes.currentScene = SCENE_AIRPORT_MODEL;
	_attributes.blendValue = BLEND_VALUE_BOX;
	_attributes.currentSequenceCounter = 0.0f;
*/
/*****************************************************/




/****************SCENE 3  INITIALIAZATION *************/

//_cam_speed = CAM_SPEED_PHOTO_ROOM;
//
//_attributes.globalScene = 3;
//_attributes.currentScene = SCENE_PHOTO_ROOM;
//_attributes.currentSequenceCounter = 0.0f;
//_attributes.currentTransformation = TRANSFORMATION_INCREASE_SPOT_LIGHT;
//_zLimit = 2.0f;
//_attributes.globalLight[0] = 0.2f;
//_attributes.globalLight[1] = 0.2f;
//_attributes.globalLight[2] = 0.2f;

  
 /****************SCENE 4  INITIALIAZATION *************/

//_attributes.globalScene = 4;


/*****************************************************/

}

void T2Terminal::MainScene::InitializeResizeAttributes()
{
	_resizeAttributes.farValue = 32000.0f;
	_resizeAttributes.nearValue = 0.1f;
}
