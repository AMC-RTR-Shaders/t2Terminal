/*
* @author: Praveen Suryawanshi
* @mailto: suryawanshi.praveen007@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/
#include "GLObject.h"

GLObject::GLObject()
{
}

void GLObject::initialize_for_draw_array_from_cpu(GLuint shaderProgramObject,int vertices_size, GLfloat * vertices_data, int tex_cord_size, GLfloat * tex_cords_data, int normal_size, GLfloat * normals_data, std::vector<ThreeDModelLoader::MATERIAL*>* materialTable, GLOBJECT_INSTANCEING *instancing)
{
	_instancing = instancing;

	initializeMaterials(materialTable, shaderProgramObject);
	initializeTextures(materialTable, shaderProgramObject);
	
	/*Rectangle*/
	glGenVertexArrays(1, &_vao_object);
	glBindVertexArray(_vao_object);

	
	/*position*/
	if (vertices_size > 0)
	{
		glGenBuffers(1, &_vbo_object_positions);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo_object_positions);

		glBufferData(GL_ARRAY_BUFFER,   /**/vertices_size/**/ * sizeof(GL_FLOAT), vertices_data, GL_STATIC_DRAW);
		glVertexAttribPointer(AMC_ATTRIBUTE_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(AMC_ATTRIBUTE_VERTEX);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	/**/


	/*texture*/
	if (tex_cord_size > 0)
	{
		glGenBuffers(1, &_vbo_object_tex_cords);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo_object_tex_cords);

		glBufferData(GL_ARRAY_BUFFER,  /**/tex_cord_size/**/ * sizeof(GL_FLOAT), tex_cords_data, GL_STATIC_DRAW);
		glVertexAttribPointer(AMC_ATTRIBUTE_TEXTURE0, 2/*s,t*/, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(AMC_ATTRIBUTE_TEXTURE0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	/**/


	/*normals*/
	if (normal_size >0)
	{
		glGenBuffers(1, &_vbo_object_normals);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo_object_normals);

		glBufferData(GL_ARRAY_BUFFER,  /**/normal_size/**/ * sizeof(GL_FLOAT), normals_data, GL_STATIC_DRAW);
		glVertexAttribPointer(AMC_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(AMC_ATTRIBUTE_NORMAL);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	/**/

	/*INSTANCING*/
	if (instancing != NULL && instancing->instancingQuery == INSTANCING_QUERY::YES)
	{
		if (instancing->isPostion)
		{
			glGenBuffers(1, &_vbo_instancing_position);
			glBindBuffer(GL_ARRAY_BUFFER, _vbo_instancing_position);
			glBufferData(GL_ARRAY_BUFFER, /**/instancing->countOfPosition/**/, instancing->positionArray, GL_STATIC_DRAW);

			glVertexAttribPointer(AMC_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);

			glEnableVertexAttribArray(AMC_ATTRIBUTE_POSITION);
			glVertexAttribDivisor(AMC_ATTRIBUTE_POSITION, instancing->position_attriDivisorCount);

			glBindBuffer(GL_ARRAY_BUFFER, 0);




		}

		if (instancing != NULL && instancing->isRotation)
		{
			glGenBuffers(1, &_vao_instancing_rotation);
			glBindBuffer(GL_ARRAY_BUFFER, _vao_instancing_rotation);
			glBufferData(GL_ARRAY_BUFFER, /**/instancing->countOfRotation/**/, instancing->rotationArray, GL_STATIC_DRAW);

			glVertexAttribPointer(AMC_ATTRIBUTE_ROTATION, 3, GL_FLOAT, GL_FALSE, 0, NULL);

			glEnableVertexAttribArray(AMC_ATTRIBUTE_ROTATION);

			glVertexAttribDivisor(AMC_ATTRIBUTE_ROTATION, instancing->rotation_attriDivisorCount);

			glBindBuffer(GL_ARRAY_BUFFER, 0);

		}
	}
	/**/

	glBindVertexArray(0);
	/**/
}

void GLObject::draw_using_draw_array(int count,std::vector<ThreeDModelLoader::MODEL_INDICES_MAP_TABLE*>  *modelIndicesMatrialMapTable, std::vector<ThreeDModelLoader::MATERIAL*>* materialTable)
{
	int start_offset = 0;
	int end_offset = 0;

	glBindVertexArray(_vao_object);

	if (modelIndicesMatrialMapTable->size() > 0)
	{
		for (size_t i = 0; i < modelIndicesMatrialMapTable->size(); i++)
		{
			int materialIndex = modelIndicesMatrialMapTable->at(i)->material_index;
			MATERIAL *material = materialTable->at(materialIndex);
			char *name = material->name;

			applyMaterial(material);
			applyTexture(material);

			start_offset = modelIndicesMatrialMapTable->at(i)->start_index;
			end_offset = modelIndicesMatrialMapTable->at(i)->end_index;


			if (_instancing->instancingQuery == INSTANCING_QUERY::YES)
			{
				glDrawArraysInstanced(GL_TRIANGLES, start_offset * 3, end_offset * 3, _instancing->numberOfInstance);
			}
			else
			{
				glDrawArrays(GL_TRIANGLES, start_offset * 3, end_offset * 3);
			}
		}
	}
	else
	{
		if (_instancing->instancingQuery == INSTANCING_QUERY::YES)
		{
			glDrawArraysInstanced(GL_TRIANGLES, 0, count / 3, _instancing->numberOfInstance);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, count / 3);
		}
		
	}
	
	glBindVertexArray(0);
	glActiveTexture(0);
}

void GLObject::initialize_for_draw_elements_from_cpu(GLuint shaderProgramObject,int vertices_size, GLfloat * vertices_data, int tex_cord_size, GLfloat * tex_cords_data, int normal_size, GLfloat * normals_data, int elements_size, unsigned short * elements_data, std::vector<ThreeDModelLoader::MATERIAL*>* materialTable, GLOBJECT_INSTANCEING *instancing)
{
	_instancing = instancing;
	
	initializeMaterials(materialTable, shaderProgramObject);
	initializeTextures(materialTable, shaderProgramObject);

	/*Rectangle*/
	glGenVertexArrays(1, &_vao_object);
	glBindVertexArray(_vao_object);

	/*position*/
	if (vertices_size >  0)
	{
		glGenBuffers(1, &_vbo_object_positions);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo_object_positions);

		glBufferData(GL_ARRAY_BUFFER,   /**/vertices_size/**/ * sizeof(GL_FLOAT), vertices_data, GL_STATIC_DRAW);
		glVertexAttribPointer(AMC_ATTRIBUTE_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(AMC_ATTRIBUTE_VERTEX);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	/**/


	
	/*texture*/
	if (tex_cord_size > 0)
	{
		glGenBuffers(1, &_vbo_object_tex_cords);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo_object_tex_cords);

		glBufferData(GL_ARRAY_BUFFER,  /**/tex_cord_size/**/ * sizeof(GL_FLOAT), tex_cords_data, GL_STATIC_DRAW);
		glVertexAttribPointer(AMC_ATTRIBUTE_TEXTURE0, 2/*s,t*/, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(AMC_ATTRIBUTE_TEXTURE0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	/**/


	/*normals*/
	if (normal_size > 0)
	{
		glGenBuffers(1, &_vbo_object_normals);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo_object_normals);

		glBufferData(GL_ARRAY_BUFFER,  /**/normal_size/**/ * sizeof(GL_FLOAT), normals_data, GL_STATIC_DRAW);
		glVertexAttribPointer(AMC_ATTRIBUTE_NORMAL, 3/*s,t*/, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(AMC_ATTRIBUTE_NORMAL);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	/**/


	/*ELEMENT VBO*/
	if (elements_size >  0)
	{
		glGenBuffers(1, &_vbo_object_elements_index);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo_object_elements_index);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, (/**/elements_size/**/ * sizeof(unsigned short)), elements_data, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	/**/

	/*INSTANCING*/
	if (instancing != NULL && instancing->instancingQuery == INSTANCING_QUERY::YES)
	{
		if (instancing->isPostion)
		{
			glGenBuffers(1, &_vbo_instancing_position);
			glBindBuffer(GL_ARRAY_BUFFER, _vbo_instancing_position);
			glBufferData(GL_ARRAY_BUFFER, /**/instancing->countOfPosition/**/, instancing->positionArray, GL_STATIC_DRAW);

			glVertexAttribPointer(AMC_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);

			glEnableVertexAttribArray(AMC_ATTRIBUTE_POSITION);
			glVertexAttribDivisor(AMC_ATTRIBUTE_POSITION, instancing->position_attriDivisorCount);

			glBindBuffer(GL_ARRAY_BUFFER, 0);

			
			

		}

		if (instancing != NULL && instancing->isRotation)
		{
			glGenBuffers(1, &_vao_instancing_rotation);
			glBindBuffer(GL_ARRAY_BUFFER, _vao_instancing_rotation);
			glBufferData(GL_ARRAY_BUFFER, /**/instancing->countOfRotation/**/, instancing->rotationArray, GL_STATIC_DRAW);

			glVertexAttribPointer(AMC_ATTRIBUTE_ROTATION, 3, GL_FLOAT, GL_FALSE, 0, NULL);

			glEnableVertexAttribArray(AMC_ATTRIBUTE_ROTATION);
			
			glVertexAttribDivisor(AMC_ATTRIBUTE_ROTATION, instancing->rotation_attriDivisorCount);

			glBindBuffer(GL_ARRAY_BUFFER, 0);

		}
	}
	/**/

	glBindVertexArray(0);
	/**/
}


void GLObject::draw_using_draw_elements( int count,std::vector<ThreeDModelLoader::MODEL_INDICES_MAP_TABLE*>  *modelIndicesMatrialMapTable, std::vector<ThreeDModelLoader::MATERIAL*>* materialTable)
{
	//https://www.reddit.com/r/opengl/comments/4jwj9n/single_mesh_multiple_materials/
	int start_offset = 0;
	int buffer_count = 0;

	glBindVertexArray(_vao_object);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo_object_elements_index);
	
	if (modelIndicesMatrialMapTable->size() > 0)
	{
		for (size_t i = 0; i < modelIndicesMatrialMapTable->size(); i++)
		{

			int materialIndex = modelIndicesMatrialMapTable->at(i)->material_index;
			MATERIAL *material = materialTable->at(materialIndex);
			char *name = material->name;

			applyMaterial(material);
			applyTexture(material);


			if (i < modelIndicesMatrialMapTable->size() - 1)
			{	

				start_offset = modelIndicesMatrialMapTable->at(i)->start_index;
				buffer_count = modelIndicesMatrialMapTable->at(i + 1)->start_index - modelIndicesMatrialMapTable->at(i)->start_index;

			}
			else
			{
				start_offset = modelIndicesMatrialMapTable->at(i)->start_index;
				buffer_count = (count-1) - start_offset + 1;
				
			}

			if (_instancing !=NULL &&  _instancing->instancingQuery == INSTANCING_QUERY::YES)
			{
				glDrawArraysInstanced(GL_TRIANGLES, sizeof(GLuint) * start_offset, buffer_count, _instancing->numberOfInstance);
			}
			else
			{
				glDrawElements(GL_TRIANGLES, buffer_count, GL_UNSIGNED_SHORT, (void*)(sizeof(GLuint) * start_offset));
			}
		}
	}
	else
	{
		if (_instancing!=NULL && _instancing->instancingQuery == INSTANCING_QUERY::YES)
		{
			glDrawArraysInstanced(GL_TRIANGLES, count, 0, _instancing->numberOfInstance);
		}
		else
		{
			glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_SHORT, 0);
		}
	}

	
	glBindVertexArray(0);
	glActiveTexture(0);
}

GLuint GLObject::get_vao_object()
{
	return _vao_object;
}

GLuint GLObject::get_vbo_object_positions()
{
	return _vbo_object_positions;
}

GLuint GLObject::get_vbo_object_colors()
{
	return _vbo_object_colors;
}

GLuint GLObject::get_vbo_object_tex_cords()
{
	return _vbo_object_tex_cords;
}

GLuint GLObject::get_vbo_object_normals()
{
	return _vbo_object_normals;
}

GLuint GLObject::get_vbo_object_elements()
{
	return _vbo_object_elements_index;
}

GLObject::~GLObject()
{
	clean_up();
}


void GLObject::LoadGLTexture(GLuint *texture, char *path)
{
	HBITMAP hBitmap;
	BITMAP bmp;

	WCHAR  tpath[1024];
	swprintf(tpath,L"%S", path);

	hBitmap = (HBITMAP)LoadImage(NULL, tpath, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE );

	if (hBitmap)
	{
		GetObject(hBitmap, sizeof(bmp), &bmp);
		glGenTextures(1, texture);
		
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glBindTexture(GL_TEXTURE_2D, *texture);
	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		
		glTexImage2D(GL_TEXTURE_2D, 0/*LOD*/, GL_RGB, bmp.bmWidth, bmp.bmHeight, 0/*border width*/, GL_BGR, GL_UNSIGNED_BYTE, bmp.bmBits);
		glGenerateMipmap(GL_TEXTURE_2D);
		
		DeleteObject(hBitmap);
	}
}

void GLObject::initializeMaterials(std::vector<ThreeDModelLoader::MATERIAL*>* materialTable, GLuint shaderProgramObject)
{
	//Get uniform locations for material
	for (size_t i = 0; i < materialTable->size(); i++)
	{
		MATERIAL *material = materialTable->at(i);

	
		GL_SAFE_GET_UNIFORM_LOCATION(material->isNsAvailable, material->Ns_Uniform, shaderProgramObject, "u_Ns")
		GL_SAFE_GET_UNIFORM_LOCATION(material->isNiAvailiable, material->Ni_Uniform, shaderProgramObject, "u_Ni")
		GL_SAFE_GET_UNIFORM_LOCATION(material->isKaAvailable, material->Ka_Uniform, shaderProgramObject, "u_Ka")
		GL_SAFE_GET_UNIFORM_LOCATION(material->isKdAvailable, material->Kd_Uniform, shaderProgramObject, "u_Kd")
		GL_SAFE_GET_UNIFORM_LOCATION(material->isKsAvailable, material->Ks_Uniform, shaderProgramObject, "u_Ks")
		GL_SAFE_GET_UNIFORM_LOCATION(material->isKeAvailable, material->Ke_Uniform, shaderProgramObject, "u_Ke")
		GL_SAFE_GET_UNIFORM_LOCATION(material->isKtAvailable, material->Kt_Uniform, shaderProgramObject, "u_Kt")
		GL_SAFE_GET_UNIFORM_LOCATION(material->isdAvailable, material->d_Uniform, shaderProgramObject, "u_d")
		GL_SAFE_GET_UNIFORM_LOCATION(material->isTrAvailable, material->Tr_Uniform, shaderProgramObject, "u_Tr")
		GL_SAFE_GET_UNIFORM_LOCATION(material->isTfAvailable, material->Tf_Uniform, shaderProgramObject, "u_Tf")
		GL_SAFE_GET_UNIFORM_LOCATION(material->isillumAvailable, material->illum_Uniform, shaderProgramObject, "u_illum")

		GL_SAFE_GET_UNIFORM_LOCATION(material->ismap_KaAvailable, material->map_Ka_Uniform, shaderProgramObject, "u_map_Ka")
		GL_SAFE_GET_UNIFORM_LOCATION(material->ismap_KaAvailable, material->map_Ka_Texture_smapler_uniform, shaderProgramObject, "u_texture0_sampler")

		GL_SAFE_GET_UNIFORM_LOCATION(material->ismap_KdAvailable, material->map_Kd_Uniform, shaderProgramObject, "u_map_Kd")
		GL_SAFE_GET_UNIFORM_LOCATION(material->ismap_KdAvailable, material->map_Kd_Texture_smapler_uniform, shaderProgramObject, "u_texture1_sampler")

		GL_SAFE_GET_UNIFORM_LOCATION(material->ismap_KsAvailable, material->map_Ks_Uniform, shaderProgramObject, "u_map_Ks")
		GL_SAFE_GET_UNIFORM_LOCATION(material->ismap_KsAvailable, material->map_Ks_Texture_smapler_uniform, shaderProgramObject, "u_texture2_sampler")

		GL_SAFE_GET_UNIFORM_LOCATION(material->ismap_NsAvailable, material->map_Ns_Uniform, shaderProgramObject, "u_map_Ns")
		GL_SAFE_GET_UNIFORM_LOCATION(material->ismap_NsAvailable, material->map_Ns_Texture_smapler_uniform, shaderProgramObject, "u_texture3_sampler")

		GL_SAFE_GET_UNIFORM_LOCATION(material->ismap_bumpAvailable, material->map_bump_Uniform, shaderProgramObject, "u_map_bump")
		GL_SAFE_GET_UNIFORM_LOCATION(material->ismap_bumpAvailable, material->map_bump_Texture_smapler_uniform, shaderProgramObject, "u_texture4_sampler")

		GL_SAFE_GET_UNIFORM_LOCATION(material->ismap_dispAvailable, material->map_disp_Uniform, shaderProgramObject, "u_map_disp")
		GL_SAFE_GET_UNIFORM_LOCATION(material->ismap_dispAvailable, material->map_disp_Texture_smapler_uniform, shaderProgramObject, "u_texture5_sampler")

		GL_SAFE_GET_UNIFORM_LOCATION(material->ismap_dAvailable, material->map_d_Uniform, shaderProgramObject, "u_map_d")
		GL_SAFE_GET_UNIFORM_LOCATION(material->ismap_dAvailable, material->map_d_Texture_smapler_uniform, shaderProgramObject, "u_texture6_sampler")
	}
	//


	
}

void GLObject::initializeTextures(std::vector<ThreeDModelLoader::MATERIAL*>* materialTable, GLuint shaderProgramObject)
{
	
	/*laod textures*/
	for (int i = 0; i < (int)materialTable->size(); i++)
	{

		GL_SAFE_LOAD_TEXTURE(materialTable, materialTable->at(i)->ismap_KaAvailable,NULL,LoadGLTexture(&materialTable->at(i)->map_Ka_Uniform, materialTable->at(i)->map_Ka.texturename), NULL)
		GL_SAFE_LOAD_TEXTURE(materialTable, materialTable->at(i)->ismap_KdAvailable, NULL, LoadGLTexture(&materialTable->at(i)->map_Kd_Uniform, materialTable->at(i)->map_Kd.texturename), NULL)
		GL_SAFE_LOAD_TEXTURE(materialTable, materialTable->at(i)->ismap_KsAvailable, NULL, LoadGLTexture(&materialTable->at(i)->map_Ks_Uniform, materialTable->at(i)->map_Ks.texturename), NULL)
		GL_SAFE_LOAD_TEXTURE(materialTable, materialTable->at(i)->ismap_NsAvailable, NULL, LoadGLTexture(&materialTable->at(i)->map_Ns_Uniform, materialTable->at(i)->map_Ns.texturename), NULL)
		GL_SAFE_LOAD_TEXTURE(materialTable, materialTable->at(i)->ismap_bumpAvailable, NULL, LoadGLTexture(&materialTable->at(i)->map_bump_Uniform, materialTable->at(i)->map_bump.texturename), NULL)
		GL_SAFE_LOAD_TEXTURE(materialTable, materialTable->at(i)->ismap_dispAvailable, NULL, LoadGLTexture(&materialTable->at(i)->map_disp_Uniform, materialTable->at(i)->map_disp.texturename), NULL)
		GL_SAFE_LOAD_TEXTURE(materialTable, materialTable->at(i)->ismap_dAvailable,NULL,LoadGLTexture(&materialTable->at(i)->map_d_Uniform, materialTable->at(i)->map_d.texturename), NULL)

	}
	/**/
}

void GLObject::applyMaterial(MATERIAL * material)
{	
	GL_SAFE_LOAD_MATERIAL(material, material->isNsAvailable,	glUniform1f(material->Ns_Uniform, material->Ns))
	GL_SAFE_LOAD_MATERIAL(material, material->isNiAvailiable,	glUniform1f(material->Ni_Uniform, material->Ni))
	GL_SAFE_LOAD_MATERIAL(material, material->isKaAvailable,	glUniform3fv(material->Ka_Uniform,1, material->Ka))
    GL_SAFE_LOAD_MATERIAL(material, material->isKdAvailable,	glUniform3fv(material->Kd_Uniform, 1, material->Kd))
	GL_SAFE_LOAD_MATERIAL(material, material->isKsAvailable,	glUniform3fv(material->Ks_Uniform, 1, material->Ks))
	GL_SAFE_LOAD_MATERIAL(material, material->isKeAvailable,	glUniform3fv(material->Ke_Uniform, 1, material->Ke))
	GL_SAFE_LOAD_MATERIAL(material, material->isKtAvailable,	glUniform3fv(material->Kt_Uniform, 1, material->Kt))
	GL_SAFE_LOAD_MATERIAL(material, material->isdAvailable,		glUniform1f(material->d_Uniform,  material->d))
	GL_SAFE_LOAD_MATERIAL(material, material->isTrAvailable,	glUniform1f(material->Tr_Uniform,  material->Tr))
	GL_SAFE_LOAD_MATERIAL(material, material->isTfAvailable,	glUniform1f(material->Tf_Uniform,  material->Tf))
	GL_SAFE_LOAD_MATERIAL(material, material->isillumAvailable,glUniform1f(material->illum_Uniform,  material->illum))

}

void GLObject::applyTexture(MATERIAL * material)
{
	

	GL_SAFE_LOAD_TEXTURE(material, material->ismap_KaAvailable, glActiveTexture(GL_TEXTURE0),glBindTexture(GL_TEXTURE_2D, material->map_Ka_Uniform), glUniform1i(material->map_Ka_Texture_smapler_uniform, 0))
	GL_SAFE_LOAD_TEXTURE(material, material->ismap_KdAvailable, glActiveTexture(GL_TEXTURE1),glBindTexture(GL_TEXTURE_2D, material->map_Kd_Uniform), glUniform1i(material->map_Kd_Texture_smapler_uniform, 0))
	GL_SAFE_LOAD_TEXTURE(material, material->ismap_KsAvailable, glActiveTexture(GL_TEXTURE2),glBindTexture(GL_TEXTURE_2D, material->map_Ks_Uniform), glUniform1i(material->map_Ks_Texture_smapler_uniform, 0))
	GL_SAFE_LOAD_TEXTURE(material, material->ismap_NsAvailable, glActiveTexture(GL_TEXTURE3),glBindTexture(GL_TEXTURE_2D, material->map_Ns_Uniform), glUniform1i(material->map_Ns_Texture_smapler_uniform, 0))
	GL_SAFE_LOAD_TEXTURE(material, material->ismap_bumpAvailable, glActiveTexture(GL_TEXTURE4),glBindTexture(GL_TEXTURE_2D, material->map_bump_Uniform), glUniform1i(material->map_bump_Texture_smapler_uniform, 0))
	GL_SAFE_LOAD_TEXTURE(material, material->ismap_dispAvailable, glActiveTexture(GL_TEXTURE5),glBindTexture(GL_TEXTURE_2D, material->map_disp_Uniform), glUniform1i(material->map_disp_Texture_smapler_uniform, 0))
	GL_SAFE_LOAD_TEXTURE(material, material->ismap_dAvailable, glActiveTexture(GL_TEXTURE6),glBindTexture(GL_TEXTURE_2D, material->map_d_Uniform), glUniform1i(material->map_d_Texture_smapler_uniform, 0))

}

void GLObject::clean_up()
{
	GL_SAFE_DELETE_ARRAYS(_vao_object)
	GL_SAFE_DELETE_BUFFERS(_vbo_object_positions)
	GL_SAFE_DELETE_BUFFERS(_vbo_object_colors)
	GL_SAFE_DELETE_BUFFERS(_vbo_object_tex_cords)
	GL_SAFE_DELETE_BUFFERS(_vbo_object_normals)
	GL_SAFE_DELETE_BUFFERS(_vbo_object_elements_index)
	//SAFE_FREE(_instancing);
}
