/*
* @author: Rahul Parakh
* @mailto: rgparakh@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/

#pragma once
#ifndef  _DOOR_H_
#define _DOOR_H_

#include"IScene.h"
#define ID_BITMAP_ENTRANCE_DOOR 201

namespace Rahul
{

	class  Door : virtual public T2Terminal::IScene
	{
	public:

		Door();
		~Door();

	public:

		GLuint _vertexShaderObject;
		GLuint _fragmentShaderObject;

		// angle of rotating door
		GLfloat doorRotateAngle = 0.0f;
		// radius of door rotation
		GLfloat radius = 15.0f;

		// Left Sliding Door's X axis
		GLfloat LSD_X_1;
		GLfloat LSD_X_4;
		// Left Sliding Door's Z axis
		GLfloat LSD_Z_1;
		GLfloat LSD_Z_4;

		// Right Sliding Door's X axis
		GLfloat RSD_X_2;
		GLfloat RSD_X_3;
		// Right Sliding Door's Z axis
		GLfloat RSD_Z_2;
		GLfloat RSD_Z_3;

		// x position of rotating left sliding door
		GLfloat LSD_X_Rotating;
		// z position of rotating left sliding door
		GLfloat LSD_Z_Rotating;

		// x position of rotating right sliding door
		GLfloat RSD_X_Rotating;
		// z position of rotating right sliding door
		GLfloat RSD_Z_Rotating;

		// x position of 3rd vertex of left sliding door
		GLfloat LSD_X_3_Point = -15.0f;
		// z position of 3rd vertex of left sliding door
		GLfloat LSD_Z_3_Point = -29.0f;

		// x position of 4th vertex of right sliding door
		GLfloat RSD_X_4_Point = 15.0f;
		// z position of 3rd vertex of right sliding door
		GLfloat RSD_Z_4_Point = -29.0f;

		GLint startDoorSliding = 0;

	protected:
		GLuint vao_top_entrance_door;
		GLuint vao_left_entrance_door;
		GLuint vao_right_entrance_door;
		GLuint vao_left_sliding_door;
		GLuint vao_right_sliding_door;
		GLuint _shaderProgramObject;

		GLuint vbo_position_ted;
		GLuint vbo_position_led;
		GLuint vbo_position_red;
		GLuint vbo_position_lsd;
		GLuint vbo_position_rsd;
		GLuint vbo_texture;
		GLuint vbo_normal;

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

		GLuint gTexture_Door;
		GLuint gTexture_sampler_uniform;

		GLuint _LightEnabled;

		const GLfloat DoorTexCoords[48] =
		{
			// TOP FACE
			0.0f,0.0f,
			1.0f,0.0f,
			1.0f,1.0f,
			0.0f,1.0f,

			// BOTTOM FACE
			0.0f,0.0f,
			1.0f,0.0f,
			1.0f,1.0f,
			0.0f,1.0f,

			// FRONT FACE
			0.0f,0.0f,
			1.0f,0.0f,
			1.0f,1.0f,
			0.0f,1.0f,

			// BACK FACE
			0.0f,0.0f,
			1.0f,0.0f,
			1.0f,1.0f,
			0.0f,1.0f,

			// LEFT FACE
			0.0f,0.0f,
			1.0f,0.0f,
			1.0f,1.0f,
			0.0f,1.0f,

			// RIGHT FACE
			0.0f,0.0f,
			1.0f,0.0f,
			1.0f,1.0f,
			0.0f,1.0f,
		};

		const GLfloat DoorNormals[72] =
		{
			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,

			0.0f,-1.0f,0.0f,
			0.0f,-1.0f,0.0f,
			0.0f,-1.0f,0.0f,
			0.0f,-1.0f,0.0f,

			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,

			0.0f,0.0f,-1.0f,
			0.0f,0.0f,-1.0f,
			0.0f,0.0f,-1.0f,
			0.0f,0.0f,-1.0f,

			-1.0f,0.0f,0.0f,
			-1.0f,0.0f,0.0f,
			-1.0f,0.0f,0.0f,
			-1.0f,0.0f,0.0f,

			1.0f,0.0f,0.0f,
			1.0f,0.0f,0.0f,
			1.0f,0.0f,0.0f,
			1.0f,0.0f,0.0f
		};

	public:

		virtual BOOL SceneHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) override;

		virtual void Initialize() override;

		virtual void Update() override;

		virtual void ReSize(int width, int height, struct ResizeAttributes attributes) override;

		virtual void Render(HDC hdc, struct Attributes attributes) override;

		virtual void SceneTransition() override;

		virtual void UnInitialize() override;

		void InitTED();
		void InitLED();
		void InitRED();
		void InitLD();
		void InitRD();
		void DrawTED();
		void DrawLED();
		void DrawRED();
		void DrawLD();
		void DrawRD();

	private:
		int LoadGLTextures(GLuint *texture, TCHAR imageResourceId[]);

	};
}


#endif // ! _DOOR_H_
