/*
* @author: Praveen Suryawanshi
* @mailto: suryawanshi.praveen007@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/

#pragma once
#ifndef  _WIRE_FRAME_EFFECT_H_
#define _WIRE_FRAME_EFFECT_H_

#include"IScene.h"

#define TRANS_Y_WIREFRAME -0.75f - 0.35f 
#define TRANS_Z_WIREFRAME -1.5f + 0.27f
#define TRANS_X_WIREFRAME -0.50f

namespace Praveen
{

	class  WireFrameEffect : virtual public T2Terminal::IScene
	{
	public:

		WireFrameEffect();


		~WireFrameEffect();

	private:

		GLuint _vertexShaderObject;
		GLuint _fragmentShaderObject;
		GLuint _shaderProgramObject;

		GLuint _modelMatrixUniform;
		GLuint _ViewMatrixUniform;
		GLuint _projectMatrixUniform;

		mat4 _perspectiveProjectionMatrix;

		GLuint _LaUniform;
		GLuint _LdUniform;
		GLuint _LsUniform;
		GLuint _LightPositionUniform;

		GLfloat _wireFrameEffect_angle;

		GLuint material_shininess_uniform;


		ModelParser *_modelParserThreePillar;
		ModelParser *_modelParserAllPillar;

		GLfloat _particleTime;


		GLOBJECT_WIREFRAME_BUILDING *_wireFrameThreePillar;
		GLOBJECT_WIREFRAME_BUILDING *_wireFrameAllPillar;
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


#endif // ! _CHAIR_H_
