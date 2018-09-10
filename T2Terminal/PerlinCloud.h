/*
* @author: Praveen Suryawanshi
* @mailto: suryawanshi.praveen007@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/

#pragma once
#ifndef  _PERLINCLOUD_H_
#define _PERLINCLOUD_H_

#include"IScene.h"

#define TRANS_Z_PERLIN_CLOUD -300.0f

namespace Abhijeet
{
	class  PerlinCloud : virtual public T2Terminal::IScene
	{
	public:

		PerlinCloud();


		~PerlinCloud();

	private:

		enum
		{
			ABHI_ATTRIBUTE_POSITION = 0,
			ABHI_ATTRIBUTE_COLOR,
			ABHI_ATTRIBUTE_NORMAL,
			ABHI_ATTRIBUTE_TEXTURE
		};


		GLuint _gVao_Rectangle;
		GLuint _gVbo_Position;
		GLuint _gMVPUniform;

		mat4 _gPerspectiveProjectionMatrix;

		GLuint _gVertexShaderObject;
		GLuint _gFragmentShaderObject;
		GLuint _gShaderProgramObject;

		GLuint _Perlin_PerlinTimeUniform;
		GLfloat _PerlinTime ;

		float _gfCloudAlpha ;
		GLuint _gfCloudAlphaUniform;

		GLuint gUniformSkycolor, gUniformcloudColor, gUniformScale;

		

		GLuint iResolutionUniform;

		GLuint _CloudDirection;
		GLuint _CloudDirectionUniform;
		bool _gbChangeCloudDIrection ;
		float _gfUpdateCloudTime;

		float _PerlinCloudAngle;
		mat4 _gRotationMatrix;

		GLfloat skycolor[3] ;
		GLfloat cloudcolor[3];


	public:
		

		virtual BOOL SceneHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) override;

		virtual void Initialize() override;

		virtual void Update() override;

		virtual void ReSize(int width, int height, struct ResizeAttributes attributes) override;

		virtual void Render(HDC hdc, struct Attributes attributes) override;

		virtual void SceneTransition() override;

		virtual void UnInitialize() override;

	};
}


#endif // ! _AIRPORT_H_
