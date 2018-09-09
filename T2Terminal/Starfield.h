
/*
* @author: Sanket Deshmukh
* @mailto: 1sanketdeshmukh@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/

#pragma once
#ifndef  _Starfield_H_
#define _Starfield_H_

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

		/*GLuint _modelMatrixUniform;
		GLuint _ViewMatrixUniform;
		GLuint _projectMatrixUniform;*/

		GLuint vao;
		GLuint vbo_Position;
		GLuint vbo_Color;
		//GLuint gVao_Cube;
		//GLuint gVbo_Cube_position;
		//GLuint gVbo_Cube_color;

		GLuint _MVPUniform;
		GLuint _MVPUniform_Cube;
		GLuint _TimeUniform;

		mat4 _perspectiveProjectionMatrix;

		SYSTEMTIME _systemTime;
		//unsigned int noOfIterations = 0;
		//GLfloat cubeDistance = -35.0f;

		/*GLuint _LaUniform;
		GLuint _LdUniform;
		GLuint _LsUniform;
		GLuint _LightPositionUniform;*/

		//GLfloat _angle;

		//GLuint material_shininess_uniform;

		//ModelParser *_modelParser;

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


#endif // ! _Starfield_H_

