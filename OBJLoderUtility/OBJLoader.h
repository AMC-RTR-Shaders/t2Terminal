/*
* @author: Praveen Suryawanshi
* @mailto: suryawanshi.praveen007@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/
#pragma once
#ifndef  _OBJ_LOADER_
#define _OBJ_LOADER_
#include<Windows.h>
#include<gl/GL.h>
#include <vector>
#include "MTLLoader.h"

#pragma warning(disable:4996)
#pragma warning(disable:4005)

#define CHECK_MALLOC(mem){ if(mem == NULL) {goto CLEAN_LOCAL_ALLOCATION_BELOW;}}
#define SAFE_FREE(mem) { if (mem) { free(mem); mem = NULL; } }
#define SAFE_CLOSE(fp) { if(fp){fclose(fp); fp=NULL;}}

#define CHECK_NEW(obj){if(obj == NULL){ goto CLEAN_LOCAL_ALLOCATION_BELOW;}}
#define SAFE_CLEAR_VECTOR_AND_FREE(obj){if(obj){obj->clear();delete obj;obj=NULL;}}
#define SAFE_DELETE(obj) { if (obj) { delete obj; obj = NULL; } }



namespace ThreeDModelLoader
{
	typedef struct _vertex_
	{
		GLfloat X1;
		GLfloat X2;
		GLfloat X3;

	}VERTEX;

	typedef struct _vertex_position_
	{
		int v1;
		int v2;
		int v3;

	}VERTEX_POSITON;


	typedef struct _texture_coord_
	{
		GLfloat S;
		GLfloat T;
		GLfloat R;
		GLfloat Q;

	}TEXTURE_CORD;


	typedef struct _normal_
	{
		GLfloat N1;
		GLfloat N2;
		GLfloat N3;

	}NORMAL;
	
	
	typedef struct _oglTriangle_
	{
		VERTEX first_point_vertices;
		TEXTURE_CORD first_point_texture_coord;
		NORMAL first_point_normals;

		VERTEX second_point_vertices;
		TEXTURE_CORD second_point_texture_coord;
		NORMAL second_point_normals;

		VERTEX third_point_vertices;
		TEXTURE_CORD third_point_texture_coord;
		NORMAL third_point_normals;

		VERTEX_POSITON vertex_positions;


	}OGLTRIANGLE;



	typedef struct  _trianglefaceindices_
	{
		/*NOTE:
		* V:Vertex
		* T:TEXTURE
		* N:NORMALS
		*/

		int V1;
		int T1;
		int N1;

		int V2;
		int T2;
		int N2;

		int V3;
		int T3;
		int N3;
	}TRIANGLE_FACE_INDICES;



	typedef struct _model_indices_material_map_table_
	{
		char materialName[256];
		int material_index;
		int start_index;
		int end_index;

	}MODEL_INDICES_MAP_TABLE;

	class OBJLoader
	{
		const char *separater_space = " ";
		const char *separater_slash = "/";

	private:

		int getTokenCountFromLine(char *line);

		bool isVertex(char* token);
		void onVertex();
		
		bool isTextureCoords(char* token);
		void onTextureCoords(int token_count);
		

		bool isNormal(char* token);
		void onNormal();
		

		bool isFaces(char* token);
		void onFaces();

		bool isMtlLib(char* token);
		void onMtlLib();

		bool isStartUseMtl(char * token);
		void onStartUseMtl();

		bool isEndUseMtl(char * token);
		void onEndUseMtl();

		void MapMaterialsTObject();

		int equals(char *src, char *dest);

	public:
		OBJLoader(char *szfileFullPath);

		void parse();


		int getTexCordArrayCount();

		std::vector<VERTEX>  * getVertices();

		std::vector<TEXTURE_CORD> *getTextureCoordinates();

		std::vector<NORMAL>  *getNormals();

		std::vector<TRIANGLE_FACE_INDICES>  *getFaces();

		std::vector<MODEL_INDICES_MAP_TABLE*>  * getModelIndicesMapTable();

		std::vector<MATERIAL*> * getMaterialTable();

		void cleanUpMemory();

		~OBJLoader();

	private:
		


		std::vector<VERTEX>  *_pvVertices;

		std::vector<TEXTURE_CORD> *_pvTexturesCoords;
		
		std::vector<NORMAL>  *_pvNormals;
		
		std::vector<TRIANGLE_FACE_INDICES>  *_pvFaces;

		std::vector<MODEL_INDICES_MAP_TABLE*>  *_pvModelIndicesMapTable;
	

		int _nTexCordCount;


		char *_szfileFullPath;

		MTLLoader *_pMtlLoader;

		MODEL_INDICES_MAP_TABLE *_model;


	};

#endif // ! 

}
