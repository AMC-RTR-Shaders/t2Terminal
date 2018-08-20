/*
* @author: Praveen Suryawanshi
* @mailto: suryawanshi.praveen007@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/

#pragma once
#pragma once
#ifndef  _MODEL_PARSER_H_
#define _MODEL_PARSER_H_

#include<Windows.h>
#include"GLObject.h"
#include"OBJLoader.h"
#include<gl/GL.h>


#pragma warning(disable:4996)
#pragma warning(disable:4005)

#define CHECK_NULL(obj){if(obj==NULL){ goto CLEAN_LOCAL_ALLOCATION_BELOW;}} 
#define SAFE_DELETE(obj){if(obj){delete obj;obj=NULL;}}
#define SAFE_FREE(mem){if(mem){free(mem);mem=NULL;}}


//#define CHECK_CALL(obj){if (obj){}else { CLEAN_LOCAL_ALLOCATION_BELOW;}}
#define CHECK_CALL(obj,call){if(obj==NULL){ goto CLEAN_LOCAL_ALLOCATION_BELOW;} else{call;}}


namespace ThreeDModelLoader
{

	typedef enum _process_type_
	{
		CPU,
		GPU

	}PROCESS_TYPE;


	typedef	enum _draw_type_
	{
		DRAW_USING_ARRAYS,
		DRAW_USING_ELEMENTS
	}DRAW_TYPE;

	class ModelParser
	{
	public:
		ModelParser(char *filenfullpathname);

		void parse(GLuint shaderProgramObject,PROCESS_TYPE processtype, DRAW_TYPE drawtype, GLOBJECT_INSTANCEING *instancing);

		void draw();

		~ModelParser();


	private :
		void clean_up();
		void getTriangle(int positionArray, OGLTRIANGLE * triangle);

	private:

		GLfloat *_pfvertices;
		int _vertices_cnt;

		GLfloat *_pfnormals;
		int _normals_cnt;

		GLfloat *_pftexturesCoords;
		int _texcord_cnt;


		unsigned short *_psPositionIndex;
		int _position_index_cnt;



		OBJLoader *_objLoader;
		
		PROCESS_TYPE _process_type;
		DRAW_TYPE _draw_type;


		GLObject *_gl_object;

		
	};

}

#endif