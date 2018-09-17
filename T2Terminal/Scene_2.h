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
#include "SpotLightBox.h"
#include "Particles.h"
#include "RollingCylinder.h"
#include "BluePrint.h"
#include "Scene2Tile.h"
#include "WireFrameEffect.h"
#include "AirportTop.h"
#include "Table.h"
#include "Rope.h"
#include "Door.h"
#include "SpotLightNew.h"


namespace Scene_2
{
	class Scene_2 : public virtual  T2Terminal::IScene
	{
	public:
		Scene_2();
		~Scene_2();

	private:
		Harsh::SpotLight *_spotLight;
		Harsh::SpotLightNew *_spotLightNew;
		Harsh::SpotLightBox *_spotLightBox;

		Rushabh::Particles *_particles;
		Rushabh::RollingCylinder *_rollingCylinder;
		Rushabh::BluePrint *_bluePrint;
		Rushabh::Scene2Tile *_scene2Tile;
		Rushabh::AirportTop *_airportTop;

		Praveen::WireFrameEffect *_wireFrameEffect;

		Sanket::Table *_Table;
		Sanket::Rope *_Rope;

		Rahul::Door *_Door;

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
