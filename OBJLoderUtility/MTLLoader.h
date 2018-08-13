/*
* @author: Praveen Suryawanshi
* @mailto: suryawanshi.praveen007@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/

#pragma once
#ifndef  _MTL_LOADER_
#define _MTL_LOADER_
#include<Windows.h>
#include<gl/GL.h>
#include <vector>

//http://people.sc.fsu.edu/~jburkardt/data/mtl/mtl.html
//https://www.youtube.com/watch?v=XIVUxywOyjE
//https://xiangchen.wordpress.com/2010/05/04/loading-a-obj-file-in-opengl/
//http://people.sc.fsu.edu/~jburkardt/data/mtl/mtl.html
//https://www.mathworks.com/matlabcentral/mlc-downloads/downloads/submissions/27982/versions/5/previews/help%20file%20format/MTL_format.html
//https://en.wikipedia.org/wiki/Wavefront_.obj_file

#pragma warning(disable:4996)
#pragma warning(disable:4005)

#define CHECK_NEW(obj){if(obj == NULL){ goto CLEAN_LOCAL_ALLOCATION_BELOW;}} 
#define SAFE_DELETE(obj){if(obj){ delete (obj); obj=NULL;}}

#define CHECK_MALLOC(mem){if(mem == NULL){ goto CLEAN_LOCAL_ALLOCATION_BELOW;}} 
#define SAFE_FREE(mem){if(mem){ free(mem);mem=NULL;}}
#define SAFE_CLOSE(fp) { if(fp){fclose(fp); fp=NULL;}}

#define SAFE_CLEAR_VECTOR_AND_FREE(obj){if(obj){obj->clear();delete obj;obj=NULL;}}

namespace ThreeDModelLoader
{
	typedef struct _texture_
	{
		char * texturename;

	}TEXTURE;

	typedef struct _material_ {
	
		char  name[256];
		GLfloat Ns;
		bool isNsAvailable;
		GLuint Ns_Uniform;


		GLfloat Ni;
		bool isNiAvailiable;
		GLuint Ni_Uniform;

		GLfloat Ka[3];
		bool isKaAvailable;
		GLuint Ka_Uniform;

		GLfloat Kd[3];
		bool isKdAvailable;
		GLuint Kd_Uniform;

		GLfloat Ks[3];
		bool isKsAvailable;
		GLuint Ks_Uniform;

		GLfloat Ke[3];
		bool isKeAvailable;
		GLuint Ke_Uniform;

		GLfloat Kt[3];
		bool isKtAvailable;
		GLuint Kt_Uniform;
		
		GLfloat d; //alpha >> d instead of Tr
		bool isdAvailable;
		GLuint d_Uniform;

		GLfloat Tr; //aloha >> Tr instred of d
		bool isTrAvailable;
		GLuint Tr_Uniform;
		
		GLfloat Tf; //need to add prototype
		bool isTfAvailable;
		GLuint Tf_Uniform;

		GLfloat illum;
		bool isillumAvailable;
		GLuint illum_Uniform;

		TEXTURE map_Ka;
		bool ismap_KaAvailable;
		GLuint map_Ka_Uniform;
		GLuint map_Ka_Texture_smapler_uniform;

		TEXTURE map_Kd;
		bool ismap_KdAvailable;
		GLuint map_Kd_Uniform;
		GLuint map_Kd_Texture_smapler_uniform;

		TEXTURE map_Ks;
		bool ismap_KsAvailable;
		GLuint map_Ks_Uniform;
		GLuint map_Ks_Texture_smapler_uniform;

		TEXTURE map_Ns;
		bool ismap_NsAvailable;
		GLuint map_Ns_Uniform;
		GLuint map_Ns_Texture_smapler_uniform;

		TEXTURE map_bump;
		bool ismap_bumpAvailable;
		GLuint map_bump_Uniform;
		GLuint map_bump_Texture_smapler_uniform;

		TEXTURE map_disp;
		bool ismap_dispAvailable;
		GLuint map_disp_Uniform;
		GLuint map_disp_Texture_smapler_uniform;
		
		TEXTURE map_d;
		bool ismap_dAvailable;
		GLuint map_d_Uniform;
		GLuint map_d_Texture_smapler_uniform;
		
	}MATERIAL;

	class MTLLoader
	{

		const char *separater_space = " ";

	private:

		int getTokenCountFromLine(char *line);

		bool isNewMaterial(char *token);
		bool onNewMaterial(FILE *mtlFileFp, char *materialName);

		bool isMaterialAmbient(char *token);
		void onMaterialAmbient(char *line);

		bool isMaterialDiffuse(char *token);
		void onMaterialDiffuse(char *line);


		bool isMaterialSpecular(char *token);
		void onMaterialSpecular(char *line);

		bool isMaterialTransmittance(char *token);
		void onMaterialTransmittance(char *line);

		bool isMaterialEmission(char *token);
		void onMaterialEmission(char *line);


		bool isMaterialDissolve(char *token);
		void onMaterialDissolve(char *line);

		bool isMaterialDissolveInvert(char *token);
		void onMaterialDissolveInvert(char *line);

		bool isMaterialIllum(char *token);
		void onMaterialIllum( char *line);

		bool isMaterialTextureMapAmbient(char *token);
		void onMaterialTextureMapAmbient(char *line);


		bool isMaterialTextureMapDiffuse(char *token);
		void onMaterialTextureMapDiffuse( char *line);

		bool isMaterialTextureMapSpecular(char *token);
		void onMaterialTextureMapSpecular(char *line);
		
		bool isMaterialTextureMapSpecularHightLight(char *token);
		void onMaterialTextureMapSpecularHightLight(char *line);

		bool isMaterialTextureMapBump(char *token);
		void onMaterialTextureMapBump(char *line);

		bool isMaterialTextureMapDisplacement(char *token);
		void onMaterialTextureMapDisplacement(char *line);

		bool isMaterialTextureMapAlpha(char *token);
		void onMaterialTextureMapAlpha(char *line);
		
		bool isMaterialSpecularExponentShininess(char *token);
		void onMaterialSpecularExponentOrShininess(char *line);

		bool isMaterialOpticalDensityOrIndexOfRefraction(char *token);
		void onMaterialOpticalDensityOrIndexOfRefraction( char *line);



	public:
		
		MTLLoader(char *filename);


		void parse();


		char * getMtlLibFileName();

		std::vector<MATERIAL*> *getMaterials();

		~MTLLoader();

	private:

		char *_szMtlLib;
		std::vector<MATERIAL*> *_pvMaterial;
		MATERIAL *_material;
		char *_szNextLine;

	};
}
#endif