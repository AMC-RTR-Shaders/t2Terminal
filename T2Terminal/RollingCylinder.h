/*
* @author: Rushabh Parakh
* @mailto: rgparakh@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/

#pragma once
#ifndef  _ROLLING_CYLINDER_H_
#define _ROLLING_CYLINDER_H_

#include"IScene.h"

#define VDG_PI  3.14159265358979323846f
#define ID_BITMAP_SMILEY 100
#define TRANS_Y_ROLLINGCYLINDER -0.55f
#define SPEED_ROLLING_CYLINDER 0.3f
#define TRANS_Z_CYLINDER -0.75f

namespace Rushabh
{

	class  RollingCylinder : virtual public T2Terminal::IScene
	{
	public:

		RollingCylinder();


		~RollingCylinder();

	public:

		GLuint _vertexShaderObject_cylinder;
		GLuint _fragmentShaderObject_cylinder;

		GLuint _vertexShaderObject_quad;
		GLuint _fragmentShaderObject_quad;

		GLfloat angle;
		
	protected:
		GLuint vao;

		GLuint gVao_quad;
		GLuint gVbo_quad_position;
		GLuint gVbo_quad_texture;

		GLuint _shaderProgramObject_cylinder;
		GLuint _shaderProgramObject_quad;

		mat4 _perspectiveProjectionMatrix;

	private:

		GLuint model_matrix_uniform, view_matrix_uniform, projection_matrix_uniform;

		GLuint gMVPUniform_quad, gTexture_sampler_uniform_quad;

		GLuint L_KeyPressed_uniform;

		GLuint La_uniform;
		GLuint Ld_uniform;
		GLuint Ls_uniform;
		GLuint light_position_uniform;

		GLuint Ka_uniform;
		GLuint Kd_uniform;
		GLuint Ks_uniform;
		GLuint material_shininess_uniform;

		GLfloat lightAmbient[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat lightDiffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat lightSpecular[4] = { 1.0f, 1.0f, 1.0f ,1.0f };
		GLfloat lightPosition[4] = { 100.0f, 100.0f, 100.0f, 1.0f };

		GLfloat material_ambient[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat material_diffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat material_specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat material_shininess = 50.0f;

		GLfloat gAngle = 0.0f;
		GLfloat gVertexX = -1.0f;
		GLfloat gTexCoordX = 0.0f;

		short *elements;
		float *verts;
		float *norms;
		float *texCoords;

		int numElements = 0;
		int maxElements = 0;
		int numVertices = 0;
		int numIndices;
		int iNumIndices;

		float _radius;
		float _height; 
		float _angle;

		GLuint vbo_position = 0;
		GLuint vbo_normal = 0;
		GLuint vbo_texture = 0;
		GLuint vbo_index = 0;

		GLuint gTexture_Smiley;

	public:

		virtual BOOL SceneHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) override;

		virtual void Initialize() override;

		virtual void Update() override;

		virtual void ReSize(int width, int height, struct ResizeAttributes attributes) override;

		virtual void Render(HDC hdc, struct Attributes attributes) override;

		virtual void SceneTransition() override;

		virtual void UnInitialize() override;

	private:

		void allocate(int numIndices);
		bool isFoundIdentical(float val1, float val2, float diff);
		void prepareToDraw();
		void draw();
		int getIndexCount();
		int getVertexCount();
		void normalizeVector(float *v);
		void deallocate();
		void addTriangle(float single_vertex[4][3], float single_normal[4][3], float single_texture[4][2]);
		void makeSphere(float fRadius, float fHeight, int iSlices, int iStacks);
		int LoadGLTextures(GLuint *texture, TCHAR imageResourceId[]);
	};
}


#endif // ! _ROLLING_CYLINDER_H_
