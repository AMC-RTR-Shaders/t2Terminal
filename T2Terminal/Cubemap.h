#pragma once
/*
* @author: Priyanka Bhasme
* @mailto: pribhasme@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/

#ifndef  _CUBEMAP_H_
#define _CUBEMAP_H_

#include"IScene.h"


namespace Priyanka
{

	#define IDBITMAP_POSX 102
	#define IDBITMAP_NEGX 103
	#define IDBITMAP_POSY 104
	#define IDBITMAP_NEGY 105
	#define IDBITMAP_POSZ 106
	#define IDBITMAP_NEGZ 107

	#define SIZE 8000

	class  Cubemap : virtual public T2Terminal::IScene
	{
	public:

		Cubemap();


		~Cubemap();

	private:

		GLuint _vertexShaderObject;
		GLuint _fragmentShaderObject;
		GLuint _shaderProgramObject;


		GLuint _modelMatrixUniform;
		GLuint _ViewMatrixUniform;
		GLuint _projectMatrixUniform;

		mat4 _perspectiveProjectionMatrix;

		GLuint _vaoCube;
		GLuint _vboCubePos;
				
		HBITMAP _hBitmap[6];
		GLuint _textureSamplerUniform;
		GLuint _textureCubemap;

	public:

		virtual BOOL SceneHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) override;

		virtual void Initialize() override;

		virtual void Update() override;

		virtual void ReSize(int width, int height, struct ResizeAttributes attributes) override;

		virtual void Render(HDC hdc, struct Attributes attributes) override;

		virtual void SceneTransition() override;

		virtual void UnInitialize() override;

		int LoadGLTexturesCubemap(GLuint *texture, int resArrayPtr);
	};
}


#endif // ! _CUBEMAP_H_
