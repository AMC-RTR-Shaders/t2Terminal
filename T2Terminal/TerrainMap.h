/*
* @author: Rushabh Parakh
* @mailto: rgparakh@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/

#pragma once
#ifndef  _TERRAINMAP_H_
#define _TERRAINMAP_H_

#include"IScene.h"

#define ID_BITMAP_TERRAIN_MAP 101

namespace Rushabh
{

	class  TerrainMap : virtual public T2Terminal::IScene
	{
	public:

		TerrainMap();


		~TerrainMap();

	public:

		GLuint _vertexShaderObject;
		GLuint _tessControlShaderObject;
		GLuint _tessEvaluationShaderObject;
		GLuint _fragmentShaderObject;

		GLfloat angle;

		GLuint vbo_position;
		GLuint vbo_normal;

	private:
		int LoadGLTextures(GLuint *texture, TCHAR imageResourceId[]);

	protected:
		GLuint vao;

		GLuint _shaderProgramObject;

		mat4 _perspectiveProjectionMatrix;

		GLuint _mVPUniform;
		GLuint 	_modelViewMatrixUniform;
		GLuint _projectionMatrixUniform;

		GLuint _enableFogUniform;
		GLuint _dmapDepthUniform;
		GLuint _texture_displacement_uniform;
		GLuint _texture_color_uniform;
		GLuint _texture_Terrain_Map;

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


#endif // ! _TERRAINMAP_H_
