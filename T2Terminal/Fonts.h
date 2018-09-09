#pragma once
/*
* @author: Sanket Deshmukh
* @mailto: 1Sanketdeshmukh@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/

#pragma once
#ifndef  _FONTS_H_
#define _FONTS_H_

#include"IScene.h"


namespace Sanket
{

	class  Fonts : virtual public T2Terminal::IScene
	{
	public:

		Fonts();


		~Fonts();

	private:

		GLuint _vertexShaderObject;
		GLuint _fragmentShaderObject;
		GLuint _shaderProgramObject;

		GLuint _modelMatrixUniform;
		GLuint _ViewMatrixUniform;
		GLuint _projectMatrixUniform;

		mat4 _perspectiveProjectionMatrix;

		GLuint _LaUniform;
		GLuint _LdUniform;
		GLuint _LsUniform;
		GLuint _LightPositionUniform;

		GLfloat _angle;
		GLfloat _shadersDist = -200.0f;
		GLfloat _presentDist = -500.0f;
		GLfloat _T2TerminalDist = -610.0f;
		GLfloat _PoweredByDist = -690.0f;
		GLfloat _AstromedicompDist = -800.0f;

		GLuint material_shininess_uniform;

		//ModelParser *_modelParser;
		ModelParser *_modelParserShaders;
		ModelParser	*_modelParserPresent;
		ModelParser	*_modelParserT2Terminal;
		ModelParser	*_modelParserPoweredBy;
		ModelParser	*_modelParserAstromedicomp;

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


#endif // ! _FONTS_H_
