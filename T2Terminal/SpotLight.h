#pragma once
#ifndef _SPOTLIGHT_H_
#define _SPOTLIGHT_H_
#include"IScene.h"


namespace Harsh
{
	#define IDB_MARBLE 501
	#define IDB_STONE 502

	
	class SpotLight : virtual public T2Terminal::IScene
	{
	private:
		GLuint _vertexShaderObject;
		GLuint _fragmentShaderObject;
		GLuint _shaderProgramObject;

		GLuint _modelMatrixUniform;
		GLuint _ViewMatrixUniform;
		GLuint _projectMatrixUniform;

		GLuint Vao_cube;

		GLuint Vbo_cube_position;
		GLuint Vbo_cube_normal;
		GLuint Vbo_cube_texture;

		GLuint _Texture_smapler_uniform;
		GLuint Texture_Marble;
		GLuint Texture_Stone;

		GLuint _LightPositionUniform;
		GLuint _LKeyPressedUniform;

		GLuint _La_uniform;
		GLuint _Ld_Uniform;
		GLuint _Ls_Uniform;

		GLuint _Ka_Uniform;
		GLuint _Kd_Uniform;
		GLuint _Ks_Uniform;
		GLuint _Material_shininess_uniform;
		GLuint _viewrPositionUniform;
		GLuint _numSpotLightUniform;

		GLfloat lightAmbient[4] = {0.25f,0.25f,0.25f,1.0f};
		GLfloat lightDiffuse[4]= {1.0f,1.0f,1.0f,1.0f};
		GLfloat lightSpecular[4] = {1.0f,1.0f,1.0f,1.0f};
		GLfloat lightPosition[4] = {0.0f,100.0f,100.0f,1.0f};

		GLfloat material_Ambient[4] = {0.0f,0.0f,0.0f,1.0f};
		GLfloat material_Diffuse[4]= {1.0f,1.0f,1.0f,1.0f};
		GLfloat material_Specular[4] = {1.0f,1.0f,1.0f,1.0f};
		GLfloat material_shininess = 128.0f;

		GLfloat mAmbient[4] = { 0.0f,0.0f,0.0f,1.0f };
		GLfloat mDiffuse[4] = { 1.0f,1.0f,1.0f,1.0f };
		GLfloat mSpecular[4] = { 1.0f,1.0f,1.0f,1.0f };
		GLfloat lightAmbientS1[4] = { 0.1f,0.1f,0.1f,1.0f };
		GLfloat lightDiffuseS1[4] = { 1.0f,1.0f,1.0f,1.0f };
		GLfloat lightSpecularS1[4] = { 1.0f,1.0f,1.0f,1.0f };
		GLfloat lightPositionS1[4] = { 0.0f,3.0f,-11.0f,1.0f };
		GLfloat lightDirectionS1[4] = { 0.0f,-1.0f,0.0f,1.0f };

		GLfloat lightAmbientS2[4] ={ 0.1f,0.1f,0.1f,1.0f };
		GLfloat lightDiffuseS2[4] = { 1.0f,1.0f,0.0f,1.0f };
		GLfloat lightSpecularS2[4] = { 1.0f,1.0f,0.0f,1.0f };
		GLfloat lightPositionS2[4] = { 2.0f,3.0f,-11.0f,1.0f };
		GLfloat lightDirectionS2[4] = { -0.09f,-1.0f,0.0f,1.0f };

		GLfloat lightAmbientS3[4] = { 0.1f,0.1f,0.1f,1.0f };
		GLfloat lightDiffuseS3[4] = { 1.0f,1.0f,0.0f,1.0f };
		GLfloat lightSpecularS3[4] = { 1.0f,1.0f,0.0f,1.0f };
		GLfloat lightPositionS3[4] = { -2.0f,3.0f,-11.0f,1.0f };
		GLfloat lightDirectionS3[4] = { 0.09f,-1.0f,0.0f,1.0f };

		mat4 _perspectiveProjectionMatrix;

		bool gbAnimate;
		bool gbLight;

		GLuint _SpotLightLaUniform[3];
		GLuint _SpotLightLdUniform[3];
		GLuint _SpotLightLsUniform[3];
		GLuint _SpotLightLightPositionUniform[3];
		GLuint _SpotLightCutOffUniform[3];
		GLuint _SpotLightOuterCutOffUniform[3];
		GLuint _SpotLightConstantUniform[3];
		GLuint _SpotLightLinearUniform[3];
		GLuint _SpotLightQuadraticUniform[3];
		GLuint _SpotLightLightDirectionUniform[3];

		GLuint _material_Kd;
		GLuint _material_Ka;
		GLuint _material_Ks;
		GLuint _material_shininess_uniform;

		float angle_cube;

	public:
		SpotLight();
		~SpotLight();

		virtual BOOL SceneHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) override;

		virtual void Initialize() override;

		virtual void Update() override;

		virtual void ReSize(int width, int height, struct ResizeAttributes attributes) override;

		virtual void Render(HDC hdc, struct Attributes attributes) override;

		virtual void SceneTransition() override;

		virtual void UnInitialize() override;

		int LoadGLTextures(GLuint *,TCHAR[]);

	};
}

#endif
