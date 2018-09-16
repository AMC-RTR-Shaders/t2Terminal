#pragma once
/*
* @author: Rushabh Parakh
* @mailto: rgparakh@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/

#pragma once
#ifndef  _PHOTOROOM_H_
#define _PHOTOROOM_H_

#include"IScene.h"

#define ID_BITMAP_CARPET   600
#define ID_BITMAP_WOOD     601
#define ID_BITMAP_CIELING  602
#define ID_BITMAP_SIDES    603
#define ID_BITMAP_STAR    604
#define ID_BITMAP_PHOTO_1	  605
#define ID_BITMAP_PHOTO_2	  606
#define ID_BITMAP_PHOTO_3	  607
#define ID_BITMAP_PHOTO_4	  608
#define ID_BITMAP_PHOTO_5	  609
#define ID_BITMAP_PHOTO_6	  610
#define ID_BITMAP_PHOTO_7	  611
#define ID_BITMAP_PHOTO_8	  612
#define ID_BITMAP_PHOTO_9	  613
#define ID_BITMAP_PHOTO_10	  614
#define ID_BITMAP_PHOTO_11	  615
#define ID_BITMAP_PHOTO_12	  616
#define ID_BITMAP_PHOTO_13	  617
#define ID_BITMAP_PHOTO_14	  618
#define ID_BITMAP_PHOTO_15	  619
#define ID_BITMAP_PHOTO_16	  620
#define ID_BITMAP_PHOTO_17	  621
#define ID_BITMAP_PHOTO_18	  622
#define ID_BITMAP_PHOTO_19	  623
#define ID_BITMAP_PHOTO_20	  624
#define ID_BITMAP_PHOTO_21	  625
#define ID_BITMAP_PHOTO_22	  626
#define ID_BITMAP_PHOTO_23	  627
#define ID_BITMAP_PHOTO_24	  628
#define ID_BITMAP_PHOTO_25	  629


#define ROOM_WIDTH 10.0f
#define ROOM_HEIGHT 4.0f
#define ROOM_LENGTH 62.5f
#define HORIZONTAL_CUBE_WIDTH 0.25f
#define HORIZONTAL_CUBE_HEIGHT 0.25f
#define HORIZONTAL_CUBE_LENGTH ROOM_LENGTH
#define VERTICAL_CUBE_WIDTH HORIZONTAL_CUBE_WIDTH
#define VERTICAL_CUBE_HEIGHT ROOM_HEIGHT/3
#define VERTICAL_CUBE_LENGTH HORIZONTAL_CUBE_HEIGHT
#define NUM_VERTICAL_CUBE 25


namespace Rushabh
{

	class  PhotoRoom : virtual public T2Terminal::IScene
	{
	public:

		PhotoRoom();


		~PhotoRoom();

	public:

		GLuint _vertexShaderObject;
		GLuint _fragmentShaderObject;


		GLuint gVertexShaderObject;
		GLuint gFragmentShaderObject;
		GLuint gShaderProgramObject;

		GLuint gVao_cube;
		GLuint gVao_horizontal_cube;
		GLuint gVao_vertical_cube;
		GLuint gVbo_cube_position;
		GLuint gVbo_cube_texture;
		GLuint gVbo_cube_normal;

		GLuint gVao_photo_Quad;
		GLuint gVao_horizontal_Quad;

	protected:
		GLuint vao;

		GLuint _shaderProgramObject;

		mat4 _perspectiveProjectionMatrix;

		GLuint _modelMatrixUniform;
		GLuint _ViewMatrixUniform;
		GLuint _projectMatrixUniform;

		GLuint gMVPUniform;
		
		GLuint gTexture_Smiley;
		GLuint _Texture_smapler_uniform;
		GLuint gTexture_Carpet;
		GLuint gTexture_Wood;
		GLuint gTexture_Sides;
		GLuint gTexture_Cieling;
		GLuint gTexture_Star;
		GLuint gTexture_Photo[25];
	

		GLuint _LightPositionUniform1;
		GLuint _LightPositionUniform2;
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

		GLfloat lightAmbient[4] = { 0.0f,0.0f,0.0f,1.0f };
		GLfloat lightDiffuse[4] = { 0.4f,0.4f,0.4f,1.0f };
		GLfloat lightSpecular[4] = { 1.0f,1.0f,1.0f,1.0f };
		GLfloat lightPosition[4] = { 100.0f,100.0f,100.0f,1.0f };
		GLfloat lightPosition1[4] = { -100.0f,100.0f,100.0f,1.0f };

		GLfloat material_Ambient[4] = { 0.0f,0.0f,0.0f,1.0f };
		GLfloat material_Diffuse[4] = { 1.0f,1.0f,1.0f,1.0f };
		GLfloat material_Specular[4] = { 1.0f,1.0f,1.0f,1.0f };
		GLfloat material_shininess = 128.0f;

		GLfloat mAmbient[4] = { 0.0f,0.0f,0.0f,1.0f };
		GLfloat mDiffuse[4] = { 1.0f,1.0f,1.0f,1.0f };
		GLfloat mSpecular[4] = { 1.0f,1.0f,1.0f,1.0f };

		GLuint _SpotLightLaUniform[25];
		GLuint _SpotLightLdUniform[25];
		GLuint _SpotLightLsUniform[25];
		GLuint _SpotLightLightPositionUniform[25];
		GLuint _SpotLightCutOffUniform[25];
		GLuint _SpotLightOuterCutOffUniform[25];
		GLuint _SpotLightConstantUniform[25];
		GLuint _SpotLightLinearUniform[25];
		GLuint _SpotLightQuadraticUniform[25];
		GLuint _SpotLightLightDirectionUniform[25];
		GLuint _material_Kd;
		GLuint _material_Ka;
		GLuint _material_Ks;
		GLuint _material_shininess_uniform;


		float angleCube = 0.0f;
		float transX, transY, transZ;
		bool gbLight;
	public:

		virtual BOOL SceneHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) override;

		virtual void Initialize() override;

		virtual void Update() override;

		virtual void ReSize(int width, int height, struct ResizeAttributes attributes) override;

		virtual void Render(HDC hdc, struct Attributes attributes) override;

		virtual void SceneTransition() override;

		virtual void UnInitialize() override;

	private:
		int LoadGLTextures(GLuint *texture, TCHAR imageResourceId[]);

	};
}


#endif // ! _PHOTOROOM_H_
