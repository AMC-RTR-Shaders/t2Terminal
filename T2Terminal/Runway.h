/*
* @author: Praveen Suryawanshi
* @mailto: suryawanshi.praveen007@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/

#pragma once
#ifndef  _RUNWAY_H_
#define _RUNWAY_H_

#include"IScene.h"


namespace Rushabh
{

	class  Runway : virtual public T2Terminal::IScene
	{
	public:

		Runway();


		~Runway();

	public:

		GLuint _vertexShaderObject;
		GLuint _fragmentShaderObject;

		GLfloat angle;

		GLuint vbo_position;
		GLuint vbo_normal;

	protected:
		GLuint vao;
		
		GLuint _shaderProgramObject;

		mat4 _perspectiveProjectionMatrix;

		GLuint _modelMatrixUniform;
		GLuint _ViewMatrixUniform;
		GLuint _projectMatrixUniform;
		
		GLuint _LaUniform;
		GLuint _LdUniform;
		GLuint _LsUniform;
		GLuint _LightPositionUniform;
		GLuint _KaUniform;
		GLuint _KdUniform;
		GLuint _KsUniform;
		GLuint material_shininess_uniform;

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


#endif // ! _RUNWAY_H_
