
/*
* @author: Sanket Deshmukh
* @mailto: 1sanketdeshmukh@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/

#pragma once
#ifndef  _STARFIELD_H_
#define _STARFIELD_H_

#include"IScene.h"


namespace Sanket
{

	class  Starfield : virtual public T2Terminal::IScene
	{
	public:

		Starfield();


		~Starfield();

	private:

		GLuint _vertexShaderObject;
		GLuint _fragmentShaderObject;
		GLuint _shaderProgramObject;

		GLuint vao;
		GLuint vbo_Position;
		GLuint vbo_Color;

		GLuint _MVPUniform;
		GLuint _MVPUniform_Cube;
		GLuint _TimeUniform;

		mat4 _perspectiveProjectionMatrix;

		SYSTEMTIME _systemTime;

		 unsigned int _seed ;

	private:

		float random_float(void);

	private :
		enum
		{
			NUM_STARS = 2000
		};


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


#endif // ! _STARFIELD_H_

