/*
* @author: Rushabh Parakh
* @mailto: rgparakh@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/

#pragma once
#ifndef  _BLUEPRINT_H_
#define _BLUEPRINT_H_

#include"IScene.h"

#define ID_BITMAP_SMILEY 100
#define TRANS_Y_BLUE_PRINT -1.0f
#define TRANS_Z_BLUE_PRINT -0.75f

namespace Rushabh
{

	class  BluePrint : virtual public T2Terminal::IScene
	{
	public:

		BluePrint();


		~BluePrint();

	public:

		GLuint _vertexShaderObject;
		GLuint _fragmentShaderObject;

		GLfloat angle;

		GLuint vbo_position;
		GLuint vbo_normal;
		GLuint vbo_texture;
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

		GLuint gTexture_Smiley;

	public:

		virtual BOOL SceneHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) override;

		virtual void Initialize() override;

		virtual void Update() override;

		virtual void ReSize(int width, int height, struct ResizeAttributes attributes) override;

		virtual void Render(HDC hdc, struct Attributes attributes) override;

		virtual void SceneTransition() override;

		virtual void UnInitialize() override;

	private:
		int LoadGLTextures(GLuint *texture, TCHAR imageResourceId[]);

	};
}


#endif // ! _BLUEPRINT_H_
