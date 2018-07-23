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

		vmath::mat4 _perspectiveProjectionMatrix;


	public:
		MainScene();

		~MainScene();



		// Inherited via IScene
		virtual BOOL SceneHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) override;

		virtual void Initialize() override;

		virtual void Update() override;

		virtual void ReSize(int width, int height) override;

		virtual void Render(HDC hdc) override;

		virtual void SceneTransition() override;

		virtual void UnInitialize() override;

	};
}

#endif