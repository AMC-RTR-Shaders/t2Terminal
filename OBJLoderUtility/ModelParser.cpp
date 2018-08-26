/*
* @author: Praveen Suryawanshi
* @mailto: suryawanshi.praveen007@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/

#include "ModelParser.h"
#include"OBJLoader.h"
#include<math.h>

ThreeDModelLoader::ModelParser::ModelParser(char * filenfullpathname)
{
	_pfvertices = NULL;
	_vertices_cnt = 0;

	_pfnormals = NULL;
	_normals_cnt = 0;;

	_pftexturesCoords = NULL;
	_texcord_cnt = 0;

	_objLoader = NULL;

	_psPositionIndex = NULL;
	_position_index_cnt = 0;


	_objLoader = new OBJLoader(filenfullpathname);
	CHECK_NULL(_objLoader)

		_gl_object = new GLObject();
	CHECK_NULL(_gl_object)

		return;



CLEAN_LOCAL_ALLOCATION_BELOW:
	clean_up();
	return;
}

void ThreeDModelLoader::ModelParser::parse(GLuint shaderProgramObject, PROCESS_TYPE processtype, DRAW_TYPE drawtype, GLOBJECT_INSTANCEING *instancing)
{
	int i = 0;
	_process_type = processtype;
	_draw_type = drawtype;

	int vertices_element_cnt = 0;
	int vertices_cnt = 0;

	if (processtype == PROCESS_TYPE::GPU)
	{
		MessageBox(NULL, TEXT("GPU Implementation not available currently.\n Change to CPU implementation"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		goto CLEAN_LOCAL_ALLOCATION_BELOW;
	}

	CHECK_CALL(_objLoader, _objLoader->parse())

		if (_objLoader->getVertices()->size() > 0)
		{
			_pfvertices = (GLfloat*)malloc(sizeof(GLfloat)*(_objLoader->getFaces()->size()) * 3 * 3); // 9 because of  3 vertices with 3 points x,y,z i.e 3*3
			CHECK_NULL(_pfvertices)
				ZeroMemory(_pfvertices, (sizeof(GLfloat)*(_objLoader->getFaces()->size()) * 3 * 3));
		}

	if (_objLoader->getTextureCoordinates()->size()>0)
	{
		if (_objLoader->getTexCordArrayCount() == 2)
		{
			_pftexturesCoords = (GLfloat*)malloc(sizeof(GLfloat)*(_objLoader->getFaces()->size()) * 3/*vertices*/ * 2 /*cords*/);
			CHECK_NULL(_pftexturesCoords)
				ZeroMemory(_pftexturesCoords, (sizeof(GLfloat)*(_objLoader->getFaces()->size()) * 3/*vertices*/ * 2 /*cords*/));
		}
		if (_objLoader->getTexCordArrayCount() == 3)
		{
			_pftexturesCoords = (GLfloat*)malloc(sizeof(GLfloat)*(_objLoader->getFaces()->size()) * 3 * 3);
			CHECK_NULL(_pftexturesCoords)
				ZeroMemory(_pftexturesCoords, (sizeof(GLfloat)*(_objLoader->getFaces()->size()) * 3 * 3));
		}
		if (_objLoader->getTexCordArrayCount() == 4)
		{
			_pftexturesCoords = (GLfloat*)malloc(sizeof(GLfloat)*(_objLoader->getFaces()->size()) * 3 * 4);
			CHECK_NULL(_pftexturesCoords)
				ZeroMemory(_pftexturesCoords, (sizeof(GLfloat)*(_objLoader->getFaces()->size()) * 3 * 4));
		}

	}


	if (_objLoader->getNormals()->size() > 0)
	{
		_pfnormals = (GLfloat*)malloc(sizeof(GLfloat)*(_objLoader->getFaces()->size()) * 3 * 3);
		CHECK_NULL(_pfnormals)
			ZeroMemory(_pfnormals, (sizeof(GLfloat)*(_objLoader->getFaces()->size()) * 3 * 3));
	}


	if (_objLoader->getFaces()->size() > 0)
	{
		_psPositionIndex = (unsigned short*)malloc((_objLoader->getFaces()->size()) * 3 * sizeof(unsigned short));
		CHECK_NULL(_psPositionIndex)
	}



	if (_draw_type == DRAW_TYPE::DRAW_USING_ARRAYS)
	{
		for (i = 0; i < (int)(_objLoader->getFaces()->size()); i++)
		{
			OGLTRIANGLE triangle;

			getTriangle(i, &triangle);

			/*filling vertices*/
			if (_pfvertices != NULL && _objLoader->getVertices()->size() > 0)
			{
				_pfvertices[_vertices_cnt++] = triangle.first_point_vertices.X1;
				_pfvertices[_vertices_cnt++] = triangle.first_point_vertices.X2;
				_pfvertices[_vertices_cnt++] = triangle.first_point_vertices.X3;

				_pfvertices[_vertices_cnt++] = triangle.second_point_vertices.X1;
				_pfvertices[_vertices_cnt++] = triangle.second_point_vertices.X2;
				_pfvertices[_vertices_cnt++] = triangle.second_point_vertices.X3;

				_pfvertices[_vertices_cnt++] = triangle.third_point_vertices.X1;
				_pfvertices[_vertices_cnt++] = triangle.third_point_vertices.X2;
				_pfvertices[_vertices_cnt++] = triangle.third_point_vertices.X3;
			}
			/**/



			/*filling color*/
			if (_pftexturesCoords != NULL && _objLoader->getTextureCoordinates()->size() > 0)
			{
				if (_objLoader->getTexCordArrayCount() == 2)
				{
					_pftexturesCoords[_texcord_cnt++] = triangle.first_point_texture_coord.S;
					_pftexturesCoords[_texcord_cnt++] = triangle.first_point_texture_coord.T;

					_pftexturesCoords[_texcord_cnt++] = triangle.second_point_texture_coord.S;
					_pftexturesCoords[_texcord_cnt++] = triangle.second_point_texture_coord.T;

					_pftexturesCoords[_texcord_cnt++] = triangle.third_point_texture_coord.S;
					_pftexturesCoords[_texcord_cnt++] = triangle.third_point_texture_coord.T;
				}
				if (_objLoader->getTexCordArrayCount() == 3)
				{
					_pftexturesCoords[_texcord_cnt++] = triangle.first_point_texture_coord.S;
					_pftexturesCoords[_texcord_cnt++] = triangle.first_point_texture_coord.T;
					_pftexturesCoords[_texcord_cnt++] = triangle.first_point_texture_coord.R;

					_pftexturesCoords[_texcord_cnt++] = triangle.second_point_texture_coord.S;
					_pftexturesCoords[_texcord_cnt++] = triangle.second_point_texture_coord.T;
					_pftexturesCoords[_texcord_cnt++] = triangle.second_point_texture_coord.R;

					_pftexturesCoords[_texcord_cnt++] = triangle.third_point_texture_coord.S;
					_pftexturesCoords[_texcord_cnt++] = triangle.third_point_texture_coord.T;
					_pftexturesCoords[_texcord_cnt++] = triangle.third_point_texture_coord.R;
				}
				if (_objLoader->getTexCordArrayCount() == 4)
				{
					_pftexturesCoords[_texcord_cnt++] = triangle.first_point_texture_coord.S;
					_pftexturesCoords[_texcord_cnt++] = triangle.first_point_texture_coord.T;
					_pftexturesCoords[_texcord_cnt++] = triangle.first_point_texture_coord.R;
					_pftexturesCoords[_texcord_cnt++] = triangle.first_point_texture_coord.Q;

					_pftexturesCoords[_texcord_cnt++] = triangle.second_point_texture_coord.S;
					_pftexturesCoords[_texcord_cnt++] = triangle.second_point_texture_coord.T;
					_pftexturesCoords[_texcord_cnt++] = triangle.second_point_texture_coord.R;
					_pftexturesCoords[_texcord_cnt++] = triangle.first_point_texture_coord.Q;

					_pftexturesCoords[_texcord_cnt++] = triangle.third_point_texture_coord.S;
					_pftexturesCoords[_texcord_cnt++] = triangle.third_point_texture_coord.T;
					_pftexturesCoords[_texcord_cnt++] = triangle.third_point_texture_coord.R;
					_pftexturesCoords[_texcord_cnt++] = triangle.first_point_texture_coord.Q;
				}
			}
			/**/



			/*filling normals*/
			if (_pfnormals != NULL && _objLoader->getNormals()->size() > 0)
			{
				_pfnormals[_normals_cnt++] = triangle.first_point_normals.N1;
				_pfnormals[_normals_cnt++] = triangle.first_point_normals.N2;
				_pfnormals[_normals_cnt++] = triangle.first_point_normals.N3;

				_pfnormals[_normals_cnt++] = triangle.second_point_normals.N1;
				_pfnormals[_normals_cnt++] = triangle.second_point_normals.N2;
				_pfnormals[_normals_cnt++] = triangle.second_point_normals.N3;

				_pfnormals[_normals_cnt++] = triangle.third_point_normals.N1;
				_pfnormals[_normals_cnt++] = triangle.third_point_normals.N2;
				_pfnormals[_normals_cnt++] = triangle.third_point_normals.N3;
			}
			/**/

		}

		_gl_object->initialize_for_draw_array_from_cpu(shaderProgramObject, _vertices_cnt, _pfvertices, _texcord_cnt, _pftexturesCoords, _normals_cnt, _pfnormals, _objLoader->getMaterialTable(), instancing);
		goto CLEAN_UP_MEMORY_AFTER_PUSHING_TO_GPU;

	}
	else
	{
		int lenghtoffaces = (int)_objLoader->getFaces()->size();

		//start of copying.
		for (int i = 0; i < (int)lenghtoffaces; i++)
		{
			_psPositionIndex[_position_index_cnt++] = _objLoader->getFaces()->at(i).V1;
			_psPositionIndex[_position_index_cnt++] = _objLoader->getFaces()->at(i).V2;
			_psPositionIndex[_position_index_cnt++] = _objLoader->getFaces()->at(i).V3;
		
		
			//point 1
			int vindex = _objLoader->getFaces()->at(i).V1;
			int cnt = 0;
			
			if (_pfvertices!= NULL && _objLoader->getVertices()->size() > 0)
			{
				cnt = vindex * 3;
				_pfvertices[cnt++] = _objLoader->getVertices()->at(vindex).X1;
				_pfvertices[cnt++] = _objLoader->getVertices()->at(vindex).X2;
				_pfvertices[cnt++] = _objLoader->getVertices()->at(vindex).X3;
				_vertices_cnt += 3;
			}
			if (_pftexturesCoords!=NULL && _objLoader->getTextureCoordinates()->size() > 0)
			{
				cnt = vindex * 2;
				_pftexturesCoords[cnt++] = _objLoader->getTextureCoordinates()->at(_objLoader->getFaces()->at(i).T1).S;
				_pftexturesCoords[cnt++] = _objLoader->getTextureCoordinates()->at(_objLoader->getFaces()->at(i).T1).T;
				_texcord_cnt += 2;
			}
			
			if (_pfnormals!=NULL && _objLoader->getNormals()->size() > 0)
			{
				cnt = vindex * 3;
				_pfnormals[cnt++] = _objLoader->getNormals()->at(_objLoader->getFaces()->at(i).N1).N1;
				_pfnormals[cnt++] = _objLoader->getNormals()->at(_objLoader->getFaces()->at(i).N1).N2;
				_pfnormals[cnt++] = _objLoader->getNormals()->at(_objLoader->getFaces()->at(i).N1).N3;
				_normals_cnt += 3;
			}
			
			
			

			//point 2
			vindex = _objLoader->getFaces()->at(i).V2;
			
			if (_pfvertices!=NULL && _objLoader->getVertices()->size() > 0)
			{
				cnt = vindex * 3;
				_pfvertices[cnt++] = _objLoader->getVertices()->at(vindex).X1;
				_pfvertices[cnt++] = _objLoader->getVertices()->at(vindex).X2;
				_pfvertices[cnt++] = _objLoader->getVertices()->at(vindex).X3;
				_vertices_cnt += 3;
			}
			if (_pftexturesCoords!=NULL && _objLoader->getTextureCoordinates()->size() > 0)
			{
				cnt = vindex * 2;
				_pftexturesCoords[cnt++] = _objLoader->getTextureCoordinates()->at(_objLoader->getFaces()->at(i).T2).S;
				_pftexturesCoords[cnt++] = _objLoader->getTextureCoordinates()->at(_objLoader->getFaces()->at(i).T2).T;
				_texcord_cnt += 2;
			}
			if (_pfnormals!=NULL && _objLoader->getNormals()->size() > 0)
			{
				cnt = vindex * 3;
				_pfnormals[cnt++] = _objLoader->getNormals()->at(_objLoader->getFaces()->at(i).N2).N1;
				_pfnormals[cnt++] = _objLoader->getNormals()->at(_objLoader->getFaces()->at(i).N2).N2;
				_pfnormals[cnt++] = _objLoader->getNormals()->at(_objLoader->getFaces()->at(i).N2).N3;
				_normals_cnt += 3;
			}			
			
			//point 3
			vindex = _objLoader->getFaces()->at(i).V3;
			
			if (_pfvertices!=NULL && _objLoader->getVertices()->size() > 0)
			{
				cnt = vindex * 3;
				_pfvertices[cnt++] = _objLoader->getVertices()->at(vindex).X1;
				_pfvertices[cnt++] = _objLoader->getVertices()->at(vindex).X2;
				_pfvertices[cnt++] = _objLoader->getVertices()->at(vindex).X3;
				_vertices_cnt += 3;
			}
			if (_pftexturesCoords!=NULL && _objLoader->getTextureCoordinates()->size() > 0)
			{
				cnt = vindex * 2;
				_pftexturesCoords[cnt++] = _objLoader->getTextureCoordinates()->at(_objLoader->getFaces()->at(i).T3).S;
				_pftexturesCoords[cnt++] = _objLoader->getTextureCoordinates()->at(_objLoader->getFaces()->at(i).T3).T;
				_texcord_cnt += 2;
			}

			if (_pfnormals!=NULL && _objLoader->getNormals()->size() > 0)
			{
				cnt = vindex * 3;
				_pfnormals[cnt++] = _objLoader->getNormals()->at(_objLoader->getFaces()->at(i).N3).N1;
				_pfnormals[cnt++] = _objLoader->getNormals()->at(_objLoader->getFaces()->at(i).N3).N2;
				_pfnormals[cnt++] = _objLoader->getNormals()->at(_objLoader->getFaces()->at(i).N3).N3;
				_normals_cnt += 3;
			}			

		}
		//end of copying
		_gl_object->initialize_for_draw_elements_from_cpu(shaderProgramObject,_vertices_cnt, _pfvertices, _texcord_cnt, _pftexturesCoords, _normals_cnt, _pfnormals, _position_index_cnt, _psPositionIndex, _objLoader->getMaterialTable(), instancing);
		goto CLEAN_UP_MEMORY_AFTER_PUSHING_TO_GPU;
	}

CLEAN_UP_MEMORY_AFTER_PUSHING_TO_GPU:
		SAFE_FREE(_pfvertices)
		SAFE_FREE(_pftexturesCoords)
		SAFE_FREE(_pfnormals)
		SAFE_FREE(_psPositionIndex)
		CHECK_CALL(_objLoader, _objLoader->cleanUpMemory())
		return;


CLEAN_LOCAL_ALLOCATION_BELOW:
	clean_up();
	return;


}

void ThreeDModelLoader::ModelParser::draw()
{

	if (_draw_type == DRAW_TYPE::DRAW_USING_ARRAYS)
	{
		_gl_object->draw_using_draw_array((int)(_objLoader->getFaces()->size()) * 3 * 3, _objLoader->getModelIndicesMapTable(), _objLoader->getMaterialTable());

	}
	else
	{
		_gl_object->draw_using_draw_elements((int)(_objLoader->getFaces()->size() * 3), _objLoader->getModelIndicesMapTable(), _objLoader->getMaterialTable());
	}

	return;

}


void ThreeDModelLoader::ModelParser::clean_up()
{
	SAFE_DELETE(_objLoader)
		SAFE_FREE(_pfvertices)
		SAFE_FREE(_pftexturesCoords)
		SAFE_FREE(_pfnormals)
		SAFE_FREE(_psPositionIndex)
		SAFE_DELETE(_gl_object)
}

void ThreeDModelLoader::ModelParser::getTriangle(int positionArray, OGLTRIANGLE * triangle)
{

	//point 1
	if (_objLoader->getVertices()->size() > 0)
	{
		triangle->vertex_positions.v1 = _objLoader->getFaces()->at(positionArray).V1;

		triangle->first_point_vertices.X1 = _objLoader->getVertices()->at(triangle->vertex_positions.v1).X1;
		triangle->first_point_vertices.X2 = _objLoader->getVertices()->at(triangle->vertex_positions.v1).X2;
		triangle->first_point_vertices.X3 = _objLoader->getVertices()->at(triangle->vertex_positions.v1).X3;
	}
	if (_objLoader->getTextureCoordinates()->size() > 0 && _objLoader->getFaces()->at(positionArray).T1 >=0)
	{
		triangle->first_point_texture_coord.S = _objLoader->getTextureCoordinates()->at(_objLoader->getFaces()->at(positionArray).T1).S;
		triangle->first_point_texture_coord.T = _objLoader->getTextureCoordinates()->at(_objLoader->getFaces()->at(positionArray).T1).T;
		triangle->first_point_texture_coord.R = _objLoader->getTextureCoordinates()->at(_objLoader->getFaces()->at(positionArray).T1).R;
		triangle->first_point_texture_coord.Q = _objLoader->getTextureCoordinates()->at(_objLoader->getFaces()->at(positionArray).T1).Q;
	}
	if (_objLoader->getNormals()->size() > 0)
	{
		triangle->first_point_normals.N1 = _objLoader->getNormals()->at(_objLoader->getFaces()->at(positionArray).N1).N1;
		triangle->first_point_normals.N2 = _objLoader->getNormals()->at(_objLoader->getFaces()->at(positionArray).N1).N2;
		triangle->first_point_normals.N3 = _objLoader->getNormals()->at(_objLoader->getFaces()->at(positionArray).N1).N3;
	}
	//


	//point 2
	if (_objLoader->getVertices()->size()> 0)
	{
		triangle->vertex_positions.v2 = _objLoader->getFaces()->at(positionArray).V2;

		triangle->second_point_vertices.X1 = _objLoader->getVertices()->at(triangle->vertex_positions.v2).X1;
		triangle->second_point_vertices.X2 = _objLoader->getVertices()->at(triangle->vertex_positions.v2).X2;
		triangle->second_point_vertices.X3 = _objLoader->getVertices()->at(triangle->vertex_positions.v2).X3;
	}
	if (_objLoader->getTextureCoordinates()->size() > 0 && _objLoader->getFaces()->at(positionArray).T2 >= 0)
	{
		triangle->second_point_texture_coord.S = _objLoader->getTextureCoordinates()->at(_objLoader->getFaces()->at(positionArray).T2).S;
		triangle->second_point_texture_coord.T = _objLoader->getTextureCoordinates()->at(_objLoader->getFaces()->at(positionArray).T2).T;
		triangle->second_point_texture_coord.R = _objLoader->getTextureCoordinates()->at(_objLoader->getFaces()->at(positionArray).T2).R;
		triangle->second_point_texture_coord.Q = _objLoader->getTextureCoordinates()->at(_objLoader->getFaces()->at(positionArray).T2).Q;
	}
	if (_objLoader->getNormals()->size() > 0)
	{
		triangle->second_point_normals.N1 = _objLoader->getNormals()->at(_objLoader->getFaces()->at(positionArray).N2).N1;
		triangle->second_point_normals.N2 = _objLoader->getNormals()->at(_objLoader->getFaces()->at(positionArray).N2).N2;
		triangle->second_point_normals.N3 = _objLoader->getNormals()->at(_objLoader->getFaces()->at(positionArray).N2).N3;
	}
	//



	//point 3
	if (_objLoader->getVertices()->size() > 0)
	{
		triangle->vertex_positions.v3 = _objLoader->getFaces()->at(positionArray).V3;

		triangle->third_point_vertices.X1 = _objLoader->getVertices()->at(triangle->vertex_positions.v3).X1;
		triangle->third_point_vertices.X2 = _objLoader->getVertices()->at(triangle->vertex_positions.v3).X2;
		triangle->third_point_vertices.X3 = _objLoader->getVertices()->at(triangle->vertex_positions.v3).X3;
	}
	if (_objLoader->getTextureCoordinates()->size() > 0 && _objLoader->getFaces()->at(positionArray).T3 >= 0)
	{
		triangle->third_point_texture_coord.S = _objLoader->getTextureCoordinates()->at(_objLoader->getFaces()->at(positionArray).T3).S;
		triangle->third_point_texture_coord.T = _objLoader->getTextureCoordinates()->at(_objLoader->getFaces()->at(positionArray).T3).T;
		triangle->third_point_texture_coord.R = _objLoader->getTextureCoordinates()->at(_objLoader->getFaces()->at(positionArray).T3).R;
		triangle->third_point_texture_coord.Q = _objLoader->getTextureCoordinates()->at(_objLoader->getFaces()->at(positionArray).T3).Q;
	}

	if (_objLoader->getNormals()->size() > 0)
	{
		triangle->third_point_normals.N1 = _objLoader->getNormals()->at(_objLoader->getFaces()->at(positionArray).N3).N1;
		triangle->third_point_normals.N2 = _objLoader->getNormals()->at(_objLoader->getFaces()->at(positionArray).N3).N2;
		triangle->third_point_normals.N3 = _objLoader->getNormals()->at(_objLoader->getFaces()->at(positionArray).N3).N3;
	}
	//
}


ThreeDModelLoader::ModelParser::~ModelParser()
{
	clean_up();
}

