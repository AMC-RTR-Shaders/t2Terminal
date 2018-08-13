/*
* @author: Rushabh Parakh
* @mailto: rgparakh@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/

#pragma once
#ifndef  _QUAD_H_
#define _QUAD_H_

#include"IScene.h"


namespace Utility
{

	class  Quad : virtual public T2Terminal::IScene
	{
	public:

		Quad();


		~Quad();

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

		virtual void ReSize(int width, int height, struct ResizeAttributes attributes) override;

		virtual void Render(HDC hdc, struct Attributes attributes) override;

		virtual void SceneTransition() override;

		virtual void UnInitialize() override;

	};
}


#endif // ! _QUAD_H_
