#pragma once
/*
* @author: Praveen Suryawanshi
* @mailto: suryawanshi.praveen007@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/

#ifndef _SCENE_2_H
#define _SCENE_2_H

#include "IScene.h"
#include "SpotLight.h"

namespace Scene_2
{
	class Scene_2 : public virtual  T2Terminal::IScene
	{
	public:
		Scene_2();
		~Scene_2();

	private:
		Harsh::SpotLight *_spotLight;

	public:

		// Inherited via IScene
		virtual BOOL SceneHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) override;

		virtual void Initialize() override;

		virtual void Update() override;

		virtual void ReSize(int width, int height, struct ResizeAttributes attributes) override;

		virtual void Render(HDC hdc, struct Attributes attributes) override;

		virtual void SceneTransition() override;

		virtual void UnInitialize() override;

	};
}
#endif // !_SCENE_2_H
