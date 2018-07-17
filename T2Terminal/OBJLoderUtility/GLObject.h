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
#define GL_SAFE_LOAD_TEXTURE(x,y,z){if(x!=NULL && y == true) {z;}}

enum
{
	VDG_ATTRIBUTE_POSITION = 0,
	VDG_ATTRIBUTE_COLOR,
	VDG_ATTRIBUTE_NORMAL,
	VDG_ATTRIBUTE_TEXTURE0,
};


#define GL_SAFE_DELETE_BUFFERS(buffer)if(buffer){glDeleteBuffers(1, &buffer);buffer=0;}
#define GL_SAFE_DELETE_ARRAYS(arrays)if(arrays){glDeleteVertexArrays(1, &arrays);arrays=0;}

#define GL_SAFE_GET_UNIFORM_LOCATION(isAvaiableMaterial,uniform_location,shaderProgramObject,materila_property){if(isAvaiableMaterial){uniform_location=glGetUniformLocation(shaderProgramObject,materila_property);}}


class GLObject
{
public:

	GLObject();

	void initialize_for_draw_array_from_cpu(GLuint shaderProgramObject,int vertices_size, GLfloat *vertices_data,int tex_cord_size , GLfloat *tex_cords_data, int normal_size, GLfloat *normals_data, std::vector<ThreeDModelLoader::MATERIAL*>* materialTable);
	void draw_using_draw_array(int count, std::vector<ThreeDModelLoader::MODEL_INDICES_MAP_TABLE*>  *modelIndicesMatrialMapTable, std::vector<ThreeDModelLoader::MATERIAL*>* materialTable);

	void initialize_for_draw_elements_from_cpu(GLuint shaderProgramObject,int vertices_size, GLfloat *vertices_data, int tex_cord_size, GLfloat *tex_cords_data, int normal_size, GLfloat *normals_data, int elements_size, unsigned short *elements_data, std::vector<ThreeDModelLoader::MATERIAL*>* materialTable);
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
	void clean_up();

private:

	GLuint _vao_object;
	
	GLuint _vbo_object_positions;
	
	GLuint _vbo_object_colors;

	GLuint _vbo_object_tex_cords;
	
	GLuint _vbo_object_normals;
	
	GLuint _vbo_object_elements_index;

};

#endif // !_GL_OBJECT_H_

