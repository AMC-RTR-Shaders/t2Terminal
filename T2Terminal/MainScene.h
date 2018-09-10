/*
* @author: Praveen Suryawanshi
* @mailto: suryawanshi.praveen007@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/

#pragma once
#ifndef _MAIN_SCENE_H_
#define  _MAIN_SCENE_H_


#include "IScene.h"
#include "Scene_1.h"
#include "Scene_2.h"
#include "Scene_3.h"


#define CAM_SPEED_AIRPORT 5.0f
#define CAM_SPEED_TERRAIN 0.001f
#define CAM_SPEED_AIRPORT_MODEL 0.002f

#define Y_AIRPORT_START				-4500.0f
#define Z_AIRPORT_START				-6475.0f

#define Y_END_AIRPORT_1				-4600.0f
#define Z_END_AIRPORT_1				-5600.0f
#define X_END_ROTATE_1				-10.0f

#define Y_END_AIRPORT_2				-850.0f
#define Z_END_AIRPORT_2				-3400.0f
#define X_END_ROTATE_2				27.0f

#define Y_END_AIRPORT_3				-153.0f
#define Z_END_AIRPORT_3				-2110.0f
#define X_END_ROTATE_3				51.0f

#define X_END_AIRPORT_4				-9.565f
#define Y_END_AIRPORT_4				57.84f
#define Z_END_AIRPORT_4				-279.6f
#define X_END_ROTATE_4				18.36f

#define X_END_SINGLE_PLANE			0.0f;

#define Y_START_SINGLE_PLANE		4580.0f
#define Z_START_SINGLE_PLANE		5400.0f
#define X_END_SINGLE_PLANE			500.0f
#define Y_END_SINGLE_PLANE			1000.0f
#define Z_END_SINGLE_PLANE			1500.0f
#define X_END_SINGLE_PLANE_2		1000.0f
#define Z_END_SINGLE_PLANE_2		600.0f

#define Y_START_ROTATE_SINGLE_AEROPLANE	180.0f
#define Z_END_ROTATE_SINGLE_AEROPLANE_1	-25.0f
#define Z_END_ROTATE_SINGLE_AEROPLANE_2	25.0f
#define X_END_ROTATE_SINGLE_AEROPLANE_3	7.5f
#define Y_END_ROTATE_SINGLE_AEROPLANE_3	150.0f
#define Z_END_ROTATE_SINGLE_AEROPLANE_3	-12.5f
#define X_END_ROTATE_SINGLE_AEROPLANE_4	0.0f
#define Y_END_ROTATE_SINGLE_AEROPLANE_4	120.0f
#define Z_END_ROTATE_SINGLE_AEROPLANE_4	0.0f

#define START_CLOUD_SPEED 0.005f
#define END_CLOUD_SPEED_1 0.03f
#define END_CLOUD_SPEED_2 -0.03f
#define END_CLOUD_SPEED_3 0.03f
#define CLOUD_ALPHA_OFFSET 0.05f

#define Z_BLEND_AIRPORT_START_1 -6284.0
#define Z_BLEND_AIRPORT_START_2 -5900.0
#define Z_BLEND_AIRPORT_END_1   -5508.0
#define Z_BLEND_AIRPORT_END_2   -5300.0

#define Y_START_AIRPORT_MODEL 0.0f
#define Z_START_AIRPORT_MODEL -20.0f
#define Y_END_AIRPORT_MODEL_1 -1.28f
#define Z_END_AIRPORT_MODEL_1 -10.2f
#define Y_END_AIRPORT_MODEL_2 0.432f
#define Z_END_AIRPORT_MODEL_2 -3.0f
#define Y_END_AIRPORT_MODEL_3 1.76f
#define Z_END_AIRPORT_MODEL_3 -14.4f

#define Y_AIRPORT_TOP_START		10.0f
#define Y_AIRPORT_TOP_END		-0.93f

#define BLEND_VALUE_BOX 0.3f
#define BLEND_VALUE_CUBE_MAP 1.0f
#define BLEND_VALUE_CUBE_MAP_MIN 0.4f

using namespace T2Terminal;

namespace T2Terminal
{

	class MainScene : virtual public IScene
	{

	private:

		IScene *_scene;

		IScene *_scene_1;
		IScene *_scene_2;
		IScene *_scene_3;

		bool _switch;
		int _axis= 0;
		float _cam_speed;

		int _width;
		int _height;
		
		vmath::mat4 _perspectiveProjectionMatrix;

		IScene::ResizeAttributes _resizeAttributes;
		IScene::Attributes _attributes;

	public:
		MainScene();

		~MainScene();



		// Inherited via IScene
		virtual BOOL SceneHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) override;

		virtual void Initialize() override;

		virtual void Update() override;

		virtual void ReSize(int width, int height, struct ResizeAttributes attributes) override;

		virtual void Render(HDC hdc, struct Attributes attributes) override;

		virtual void SceneTransition() override;

		virtual void UnInitialize() override;

		void UpdateTransformationAttributes();
		void InitializeTransformationAttributes();
		void InitializeResizeAttributes();
	};
}

#endif