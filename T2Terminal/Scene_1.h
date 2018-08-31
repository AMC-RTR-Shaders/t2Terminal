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
#include "Cube.h"
#include "Quad.h"
#include "AeroplaneInstanceing.h"
#include "CubeTemplate.h"
#include "TerminalGlass.h"
#include "Airport.h"
#include "TerrainMap.h"


namespace Scene_1
{
	class Scene_1 : public virtual T2Terminal::IScene
	{

	public:
		Scene_1();

		~Scene_1();

	private:
		Rushabh::CubeTemplate *_cubeTemplate;
		Rushabh::TerminalGlass *_terminalGlass;
		Rushabh::Airport *_airport;
		Rushabh::TerrainMap *_terrainMap;
		Harsh::AeroplaneInstanceing *_aeroplaneInstancing;
		Utility::Cube *_cube;
		Utility::Quad *_quad;


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

#endif // ! _SCENE_1_H_

