/*
* @author: Praveen Suryawanshi
* @mailto: suryawanshi.praveen007@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/
#pragma once

#ifndef _GL_OBJECT_H_
#define _GL_OBJECT_H_

#include<stdio.h>
#include <gl\glew.h>
#include<iostream>
#include<vector>
#include<tchar.h>
#include"OBJLoader.h"
//#include<gl/GL.h>

#pragma comment(lib,"glew32.lib")
#pragma comment(lib, "opengl32.lib")

using namespace ThreeDModelLoader;


#define GL_SAFE_LOAD_MATERIAL(x,y,z){if(x!=NULL && y==true){z;}}
#define GL_SAFE_LOAD_TEXTURE(x,y,step1,step2,step3){if(x!=NULL && y == true) {step1;step2;step3;}}

enum
{
	AMC_ATTRIBUTE_VERTEX = 0,
	AMC_ATTRIBUTE_COLOR,
	AMC_ATTRIBUTE_NORMAL,

	AMC_ATTRIBUTE_TEXTURE0,
	AMC_ATTRIBUTE_TEXTURE1,
	AMC_ATTRIBUTE_TEXTURE2,
	AMC_ATTRIBUTE_TEXTURE3,
	AMC_ATTRIBUTE_TEXTURE4,
	AMC_ATTRIBUTE_TEXTURE5,
	AMC_ATTRIBUTE_TEXTURE6,

	AMC_ATTRIBUTE_POSITION,
	AMC_ATTRIBUTE_ROTATION,
};




typedef enum _instanceing_query_
{
	NO,
	YES
}INSTANCING_QUERY;

typedef struct _instance_
{
	INSTANCING_QUERY instancingQuery;
	
	int numberOfInstance;

	const GLfloat *positionArray;
	int countOfPosition;
	bool isPostion;
	GLint position_attriDivisorCount;

	const GLfloat *rotationArray;
	int countOfRotation;
	bool isRotation;
	GLint rotation_attriDivisorCount;

}GLOBJECT_INSTANCEING;


#define GL_SAFE_DELETE_BUFFERS(buffer)if(buffer){glDeleteBuffers(1, &buffer);buffer=0;}
#define GL_SAFE_DELETE_ARRAYS(arrays)if(arrays){glDeleteVertexArrays(1, &arrays);arrays=0;}

#define GL_SAFE_GET_UNIFORM_LOCATION(isAvaiableMaterial,uniform_location,shaderProgramObject,materila_property){if(isAvaiableMaterial){uniform_location=glGetUniformLocation(shaderProgramObject,materila_property);}}


class GLObject
{
public:

	GLObject();

	void initialize_for_draw_array_from_cpu(GLuint shaderProgramObject,int vertices_size, GLfloat *vertices_data,int tex_cord_size , GLfloat *tex_cords_data, int normal_size, GLfloat *normals_data, std::vector<ThreeDModelLoader::MATERIAL*>* materialTable, GLOBJECT_INSTANCEING *instancing);
	void draw_using_draw_array(int count, std::vector<ThreeDModelLoader::MODEL_INDICES_MAP_TABLE*>  *modelIndicesMatrialMapTable, std::vector<ThreeDModelLoader::MATERIAL*>* materialTable);

	void initialize_for_draw_elements_from_cpu(GLuint shaderProgramObject,int vertices_size, GLfloat *vertices_data, int tex_cord_size, GLfloat *tex_cords_data, int normal_size, GLfloat *normals_data, int elements_size, unsigned short *elements_data, std::vector<ThreeDModelLoader::MATERIAL*>* materialTable, GLOBJECT_INSTANCEING *instancing);
	void draw_using_draw_elements(int count,std::vector<ThreeDModelLoader::MODEL_INDICES_MAP_TABLE*>  *modelIndicesMatrialMapTable, std::vector<ThreeDModelLoader::MATERIAL*>* materialTable);

	GLuint get_vao_object();

	GLuint get_vbo_object_positions();

	GLuint get_vbo_object_colors();

	GLuint get_vbo_object_tex_cords();

	GLuint get_vbo_object_normals();

	GLuint get_vbo_object_elements();

	~GLObject();

private:

	void applyMaterial(MATERIAL *material);
	void applyTexture(MATERIAL *material);
	void LoadGLTexture(GLuint *texture, char *path);
	void initializeMaterials(std::vector<ThreeDModelLoader::MATERIAL*>* materialTable,GLuint shaderProgramObject);
	void initializeTextures(std::vector<ThreeDModelLoader::MATERIAL*>* materialTable, GLuint shaderProgramObject);
	void clean_up();

private:

	GLOBJECT_INSTANCEING *_instancing;

	GLuint _vao_object;
	
	GLuint _vbo_object_positions;
	
	GLuint _vbo_object_colors;

	GLuint _vbo_object_tex_cords;
	
	GLuint _vbo_object_normals;
	
	GLuint _vbo_object_elements_index;

	GLuint _vbo_instancing_position;

	GLuint _vao_instancing_rotation;

};

#endif // !_GL_OBJECT_H_

