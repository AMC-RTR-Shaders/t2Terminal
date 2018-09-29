#pragma once
/*
* @author: Sanket Deshmukh
* @mailto: 1Sanketdeshmukh@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/

#pragma once
#ifndef  _CREDIT_SCENE_H_
#define _CREDIT_SCENE_H_

#define QUAD_SIDE 21.0f

#define IDBITMAP_QUAD 910
#define IDBITMAP_GROWING_QUAD 911
#define IDBITMAP_GROWING_QUAD2 913
#define IDBITMAP_GROWING_STAR 912
#define TRANS_Y_SCENE_2_TILE -7.0f

#include"IScene.h"


namespace Sanket
{

	class  CreditScene : virtual public T2Terminal::IScene
	{
	public:

		CreditScene();


		~CreditScene();

	private:

		GLuint vao;
		GLuint vbo_position;
		GLuint vbo_texture;
		GLuint vao_growingStar;
		int completedQuads = 0;
		int numberOfTextures = 3;
		/*GLuint vbo_position_growingStar;
		GLuint vbo_texture_growingStar;*/
		/*GLuint vao_growingQuad;
		GLuint vbo_position_growingQuad;
		GLuint vbo_texture_growingQuad;*/
		GLuint _Texture_sampler_uniform;
		GLuint gTexture_Quad;
		GLuint gTexture_Full;
		GLuint gTexture_Growing;
		GLuint gTexture_GrowingStar;
		GLuint gTexture_GrowingQuad;
		GLuint gTexture_GrowingQuad2;
		GLuint _vertexShaderObject;
		GLuint _fragmentShaderObject;
		GLuint _shaderProgramObject;
		GLuint bindedTexture;
		float texCoordY  = 0.0f;
		float vertexY    = -21.0f;
		bool startScene = true;
		bool finishScene = false;
		float pauseTime = 1.0f;

		GLuint _modelMatrixUniform;
		GLuint _ViewMatrixUniform;
		GLuint _projectMatrixUniform;

		mat4 _perspectiveProjectionMatrix;

		GLuint _LaUniform;
		GLuint _LdUniform;
		GLuint _LsUniform;
		GLuint _LightPositionUniform;
		GLuint _BlackOutUniform;
		GLfloat _angle;
		GLfloat _blackOutValue;

		GLuint material_shininess_uniform;

		int LoadGLTextures(GLuint *, TCHAR[]);

		void drawQuad(float vertices[12], float textCoords[8],GLuint texture);

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


#endif // ! _CREDIT_SCENE_H_
