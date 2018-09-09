/*
* @author: Praveen Suryawanshi
* @mailto: suryawanshi.praveen007@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/

#pragma once
#ifndef  _AIRPORT_H_
#define _AIRPORT_H_

#include"IScene.h"


namespace Rushabh
{

	class  Airport : virtual public T2Terminal::IScene
	{
	public:

		Airport();


		~Airport();

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

		GLfloat _angle;

		GLuint material_shininess_uniform;

		ModelParser *_modelParser;

		GLuint _viewrPositionUniform;
		GLuint _numSpotLightUniform;

		GLuint _SpotLightLaUniform[3];
		GLuint _SpotLightLdUniform[3];
		GLuint _SpotLightLsUniform[3];
		GLuint _SpotLightLightPositionUniform[3];
		GLuint _SpotLightCutOffUniform[3];
		GLuint _SpotLightOuterCutOffUniform[3];
		GLuint _SpotLightConstantUniform[3];
		GLuint _SpotLightLinearUniform[3];
		GLuint _SpotLightQuadraticUniform[3];
		GLuint _SpotLightLightDirectionUniform[3];

		GLuint _material_Kd;
		GLuint _material_Ka;
		GLuint _material_Ks;
		GLuint _material_shininess_uniform;

		GLuint Vao_Cube;
		GLuint Vbo_Position;

		GLuint _LKeyPressedUniform;


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
