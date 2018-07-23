/*
* @author: Rushabh Parakh
* @mailto: rgparakh@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/

#pragma once
#ifndef  _AEROPLANCE_INSTANCING_H_
#define  _AEROPLANCE_INSTANCING_H_

#include"IScene.h"


namespace Harsh
{

	class  AeroplaneInstanceing : virtual public T2Terminal::IScene
	{
	public:

		AeroplaneInstanceing();


		~AeroplaneInstanceing();

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

		GLuint material_shininess_uniform;

		ModelParser *_modelParser;

		GLuint vao;
		GLuint vbo_position;
		GLuint vbo_normal;

	public:

		virtual BOOL SceneHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) override;

		virtual void Initialize() override;

		virtual void Update() override;

		virtual void ReSize(int width, int height) override;

		virtual void Render(HDC hdc) override;

		virtual void SceneTransition() override;

		virtual void UnInitialize() override;

	};
}


#endif // ! _AEROPLANCE_INSTANCING_H_
