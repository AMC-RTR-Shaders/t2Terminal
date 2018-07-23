#pragma once
/*
* @author: Praveen Suryawanshi
* @mailto: suryawanshi.praveen007@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/


#ifndef  _SCENE_1_H_
#define _SCENE_1_H_

#include "IScene.h"
#include"Aeroplane.h"
#include"Chair.h"
#include"Runway.h"
#include"AeroplaneInstanceing.h"
#include "Tset.h"

namespace Scene_1
{
	class Scene_1 : public virtual T2Terminal::IScene
	{

	public:
		Scene_1();

		~Scene_1();

	private:
		Praveen::Aeroplane *_aeroplane;
		Praveen::Chair *_chair;
		Rushabh::Runway *_runway;
		Rushabh::Tset *_test;
		Harsh::AeroplaneInstanceing *_aeroplaneInstancing;


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

#endif // ! _SCENE_1_H_

