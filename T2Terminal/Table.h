
/*
* @author: Sanket Deshmukh
* @mailto: 1sanketdeshmukh@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/

#pragma once
#ifndef  _TABLE_H_
#define _TABLE_H_


#include"IScene.h"

#define TRANS_Z_TABLE 4.0f
#define TRANS_X_TABLE 5.0f

namespace Sanket
{

	class  Table : virtual public T2Terminal::IScene
	{
	public:

		Table();


		~Table();

	private:

		GLuint _vertexShaderObject;
		GLuint _fragmentShaderObject;
		GLuint _shaderProgramObject;

		GLuint vao_Sphere;
		GLuint vbo_Sphere_Position;
		GLuint vbo_Sphere_Normal;
		GLuint vbo_Sphere_Elements;

		GLuint vao_Cube;
		GLuint vbo_Cube_Position;
		GLuint vbo_Cube_Normal;


		GLuint _ModelMatrixUniform;
		GLuint _ViewMatrixUniform;
		GLuint _ProjectionMatrixUniform;

		mat4 _perspectiveProjectionMatrix;

		GLuint _La0Uniform;
		GLuint	_Ld0Uniform;
		GLuint _Ls0Uniform;
		GLuint _Light0PositionUniform;
		GLuint	_La1Uniform ;
		GLuint	_Ld1Uniform	;
		GLuint	_Ls1Uniform	;
		GLuint _Light1PositionUniform;
		GLuint	_KaUniform;
		GLuint	_KdUniform;
		GLuint	_KsUniform;
		GLuint _MaterialShininessUniform;


		ModelParser *_modelParser;

		float gNumVertices=0; 
		float gNumElements=0; 

		float sphere_vertices[1146];
		float sphere_normals[1146];
		float sphere_textures[764];
		unsigned short sphere_elements[2280];

		GLfloat light0_ambient[4] = { 0.0f,0.0f,0.0f,1.0f };
		GLfloat light0_diffuse[4] = { 1.0f,1.0f,1.0f,1.0f };
		GLfloat light0_specular[4] = { 1.0f,1.0f,1.0f,1.0f };
		GLfloat light0_position[4] = { 000.0f,0.0f,100.0f,0.0f };

		GLfloat light1_ambient[4] = { 0.0f,0.0f,0.0f,1.0f };
		GLfloat light1_diffuse[4] = { 1.0f,1.0f,1.0f,1.0f };
		GLfloat light1_specular[4] = { 1.0f,1.0f,1.0f,0.0f };
		GLfloat light1_position[4] = { 2.0f,20.0f,-4.0f,0.0f };

		GLfloat materialAmbient[4] = { 0.8f,0.8f,0.8f,1.0f };
		GLfloat materialDiffuse[4] = { 0.8f,0.8f,0.8f,1.0f };
		GLfloat materialSpecular[4] = { 1.0f,1.0f,1.0f,1.0f };
		GLfloat materialShininess = 50.0f;

		/*GLfloat materialAmbientDark[4] = { 0.3f,0.3f,0.3f,1.0f };
		GLfloat materialDiffuseDark[4] = { 0.3f,0.3f,0.3f,1.0f };
		GLfloat materialSpecularDark[4] = { 0.3f,0.3f,0.3f,1.0f };
		GLfloat materialShininessDark = 50.0f;*/

		GLfloat materialAmbientWood[4] = { 0.80f,0.52f,0.25f,1.0f };
		GLfloat materialDiffuseWood[4] = { 0.80f,0.52f,0.25f,1.0f };
		GLfloat materialSpecularWood[4] = { 1.0f,1.0f,1.0f,1.0f };
		GLfloat materialShininessWood = 50.0f;


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


#endif // ! _TABLE_H_

