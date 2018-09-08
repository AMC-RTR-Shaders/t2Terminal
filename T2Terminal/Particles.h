/*
* @author: Rushabh Parakh
* @mailto: rgparakh@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/

#pragma once
#ifndef  _PARTICLES_H_
#define _PARTICLES_H_

#include"IScene.h"

#define PARTICLE_WIDTH 100
#define PARTICLE_HEIGHT 100
#define SPEED 0.0001f
#define TRANS_Y_PARTICLES 3.8f
#define TRANS_X_PARTICLES 4.0f
#define ROTATE_Z_PARTICLES 30.0f

namespace Rushabh
{

	class  Particles : virtual public T2Terminal::IScene
	{
	public:

		Particles();


		~Particles();

	public:

		GLuint _vertexShaderObject;
		GLuint _fragmentShaderObject;

		GLfloat angle;

		GLuint vbo_position;
		GLuint vbo_color;
		GLuint vbo_velocity;
		GLuint vbo_start_time;
		GLuint vbo_radius;

	protected:
		GLuint vao;

		GLuint _shaderProgramObject;

		mat4 _perspectiveProjectionMatrix;

		GLuint _mVPUniform;
		GLuint _backgroundUniform;
		GLuint _locationUniform;

		GLint arrayWidth, arrayHeight;
		GLfloat *_pVertex = NULL;
		GLfloat *_pColor = NULL;
		GLfloat *_pVelocity = NULL;
		GLfloat *_pStartTime = NULL;
		GLfloat *_pRadius = NULL;

		GLfloat _particleTime;
		GLfloat _backgroundColor[4] = { 0.0f, 1.0f, 0.0f, 0.0f };


	public:

		virtual BOOL SceneHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) override;

		virtual void Initialize() override;

		virtual void Update() override;

		virtual void ReSize(int width, int height, struct ResizeAttributes attributes) override;

		virtual void Render(HDC hdc, struct Attributes attributes) override;

		virtual void SceneTransition() override;

		virtual void UnInitialize() override;

	private:

		void createPoints(GLint w, GLint h);

	};
}


#endif // ! _PARTICLES_H_
