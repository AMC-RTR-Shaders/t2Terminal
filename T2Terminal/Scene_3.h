#pragma once
/*
* @author: Praveen Suryawanshi
* @mailto: suryawanshi.praveen007@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/

#ifndef _SCENE_3_H_
#define _SCENE_3_H_

#include "IScene.h"
namespace Scene_3
{
	class Scene_3 : public virtual T2Terminal::IScene
	{
	public:
		Scene_3();
		~Scene_3();

	private:


	public :

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

#endif // !_SCENE_3_H_
