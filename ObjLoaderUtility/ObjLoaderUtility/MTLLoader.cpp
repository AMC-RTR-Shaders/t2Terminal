/*
* @author: Praveen Suryawanshi
* @mailto: suryawanshi.praveen007@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/
#include "MTLLoader.h"


ThreeDModelLoader::MTLLoader::MTLLoader(char * filename)
{
	if (filename == NULL)
		return;

	_szMtlLib = NULL;

	_szMtlLib = filename;

	_szNextLine = NULL;

	_pvMaterial = NULL;


	_pvMaterial = new std::vector<MATERIAL*>();
	CHECK_NEW(_pvMaterial)
	
	return;



CLEAN_LOCAL_ALLOCATION_BELOW:
	SAFE_DELETE(_pvMaterial);
	return;
}

void ThreeDModelLoader::MTLLoader::parse()
{
	char *line_clone = NULL;

	const int line_size = 256;
	char line[line_size];
	
	char *token = NULL;

	if (_szMtlLib == NULL)
		return;

	FILE * mtlFileFp= NULL;

	fopen_s(&mtlFileFp, _szMtlLib, "r");
	CHECK_MALLOC(mtlFileFp)

	
	while (true)
	{
		memset((void*)line, (int)'\0', line_size);
		token = NULL;

		if (_szNextLine == NULL)
		{
			if (fgets(line, line_size, mtlFileFp) == NULL)
				break;
		}
		else
		{
			strcpy(line, _szNextLine);
		}

		int number_of_tokens_in_line = getTokenCountFromLine(line);
		
		line_clone = _strdup(line);
		token = strtok(line, separater_space);
		
		if (isNewMaterial(token))
		{
			char temp[100];
			char materialname[100];

			sscanf(line_clone,"%s %s",&temp,&materialname);

			if (onNewMaterial(mtlFileFp, materialname) == false)
				break;
		}

		SAFE_FREE(line_clone);
	}

	SAFE_CLOSE(mtlFileFp)
	SAFE_FREE(line_clone)
	return;



CLEAN_LOCAL_ALLOCATION_BELOW:
	SAFE_CLOSE(mtlFileFp)
	SAFE_FREE(line_clone)
	return;
}

int ThreeDModelLoader::MTLLoader::getTokenCountFromLine(char * line)
{
	int count = 0, i;

	for (i = 0;line[i] != '\0';i++)
	{
		if (line[i] == ' ')
			count++;
	}

	return count;
}

bool ThreeDModelLoader::MTLLoader::isNewMaterial(char * token)
{
	return  token != NULL ? (strcmp(token, "newmtl") == 0) : false;
}

bool ThreeDModelLoader::MTLLoader::onNewMaterial(FILE *mtlFileFp, char *materialName)
{
	const int line_size = 256;
	char line[line_size];
	char *token = NULL;
	bool eof = false;
	char * line_clone = NULL;


	_material = NULL;

	_material = (MATERIAL*)malloc(sizeof(MATERIAL));
	CHECK_MALLOC(_material)
	ZeroMemory(_material, sizeof(MATERIAL));

	strcpy(_material->name, materialName);

	while (true)
	{
		
		
		memset((void*)line, (int)'\0', line_size);
		token = NULL;

		
		if (fgets(line, line_size, mtlFileFp) == NULL)
		{
			eof = true;
			break;
		}

		line_clone = _strdup(line);

		token = strtok(line, separater_space);

		if (isNewMaterial(token))
		{
			_szNextLine = line_clone;
			break;
			
		}
		
		if (isMaterialAmbient(token))
			onMaterialAmbient(line_clone);

		if (isMaterialDiffuse(token))
			onMaterialDiffuse(line_clone);

		if (isMaterialSpecular(token))
			onMaterialSpecular(line_clone);

		if (isMaterialTransmittance(token))
			onMaterialTransmittance(line_clone);

		if (isMaterialEmission(token))
			onMaterialEmission(line_clone);

		if (isMaterialDissolve(token))
			onMaterialDissolve(line_clone);

		if (isMaterialDissolveInvert(token))
			onMaterialDissolveInvert(line_clone);

		if (isMaterialIllum(token))
			onMaterialIllum(line_clone);

		if (isMaterialTextureMapAmbient(token))
			onMaterialTextureMapAmbient(line_clone);


		if (isMaterialTextureMapDiffuse(token))
			onMaterialTextureMapDiffuse(line_clone);

		if (isMaterialTextureMapSpecular(token))
			onMaterialTextureMapSpecular(line_clone);

		if (isMaterialTextureMapSpecularHightLight(token))
			onMaterialTextureMapSpecularHightLight(line_clone);

		if (isMaterialTextureMapBump(token))
			onMaterialTextureMapBump(line_clone);

		if (isMaterialTextureMapDisplacement(token))
			onMaterialTextureMapDisplacement(line_clone);

		if (isMaterialTextureMapAlpha(token))
			onMaterialTextureMapAlpha(line_clone);

		if (isMaterialSpecularExponentShininess(token))
			onMaterialSpecularExponentOrShininess(line_clone);

		if (isMaterialOpticalDensityOrIndexOfRefraction(token))
			onMaterialOpticalDensityOrIndexOfRefraction(line_clone);

		SAFE_FREE(line_clone);
	}

	_pvMaterial->push_back(_material);
	return (eof == true)?false:true;



CLEAN_LOCAL_ALLOCATION_BELOW:
	SAFE_FREE(line_clone);
	return false;

}

bool ThreeDModelLoader::MTLLoader::isMaterialAmbient(char * token)
{
	return  token != NULL ? (strcmp(token, "Ka") == 0) : false;
}

void ThreeDModelLoader::MTLLoader::onMaterialAmbient(char *line)
{
	GLfloat r = NULL, g = NULL, b = NULL;
	char token_name[25];
	
	sscanf(line,"%s %f %f %f",token_name,&r,&g,&b);
	
	_material->Ka[0] = r;
	_material->Ka[1] = g;
	_material->Ka[2] = b;

	_material->isKaAvailable = true;
}

bool ThreeDModelLoader::MTLLoader::isMaterialDiffuse(char * token)
{
	return  token != NULL ? (strcmp(token, "Kd") == 0) : false;
}

void ThreeDModelLoader::MTLLoader::onMaterialDiffuse( char *line)
{
	GLfloat r = NULL, g = NULL, b = NULL;
	char token_name[25];
	
	sscanf(line, "%s %f %f %f", token_name, &r, &g, &b);
	
	_material->Kd[0] = r;
	_material->Kd[1] = g;
	_material->Kd[2] = b;

	_material->isKdAvailable = true;
}

bool ThreeDModelLoader::MTLLoader::isMaterialSpecular(char * token)
{
	return   token != NULL ? (strcmp(token, "Ks") == 0) : false;
}

void ThreeDModelLoader::MTLLoader::onMaterialSpecular(char *line)
{
	GLfloat r = NULL, g = NULL, b = NULL;
	char token_name[25];
	
	sscanf(line, "%s %f %f %f", token_name, &r, &g, &b);
	
	_material->Ks[0] = r;
	_material->Ks[1] = g;
	_material->Ks[2] = b;

	_material->isKsAvailable = true;
}

bool ThreeDModelLoader::MTLLoader::isMaterialTransmittance(char * token)
{
	return   token != NULL ? (strcmp(token, "Kt") == 0) : false;
}

void ThreeDModelLoader::MTLLoader::onMaterialTransmittance(char * line)
{
	GLfloat r = NULL, g = NULL, b = NULL;
	char token_name[25];

	sscanf(line, "%s %f %f %f", token_name, &r, &g, &b);

	_material->Kt[0] = r;
	_material->Kt[1] = g;
	_material->Kt[2] = b;

	_material->isKtAvailable = true;
}

bool ThreeDModelLoader::MTLLoader::isMaterialEmission(char * token)
{
	return   token != NULL ? (strcmp(token, "Ke") == 0) : false;
}

void ThreeDModelLoader::MTLLoader::onMaterialEmission(char *line)
{
	GLfloat r = NULL, g = NULL, b = NULL;
	char token_name[25];
	
	sscanf(line, "%s %f %f %f", token_name, &r, &g, &b);
	
	_material->Ke[0] = r;
	_material->Ke[1] = g;
	_material->Ke[2] = b;

	_material->isKeAvailable = true;
}

bool ThreeDModelLoader::MTLLoader::isMaterialDissolve(char * token)
{
	return token != NULL ? (strcmp(token, "d") == 0) : false;
}

void ThreeDModelLoader::MTLLoader::onMaterialDissolve(char *line)
{
	GLfloat val = NULL;
	
	char token_name[25];
	
	sscanf(line, "%s %f", token_name, &val);
	_material->d = val;

	_material->isdAvailable = true;

}

bool ThreeDModelLoader::MTLLoader::isMaterialDissolveInvert(char * token)
{
	return token != NULL ? (strcmp(token, "Tr") == 0) : false;
}

void ThreeDModelLoader::MTLLoader::onMaterialDissolveInvert(char * line)
{
	GLfloat val = NULL;

	char token_name[25];

	sscanf(line, "%s %f", token_name, &val);
	_material->d = 1.0f - val;

	_material->isTrAvailable = true;
}

bool ThreeDModelLoader::MTLLoader::isMaterialIllum(char * token)
{
	return token != NULL ? (strcmp(token, "illum") == 0) : false;
}

void ThreeDModelLoader::MTLLoader::onMaterialIllum( char *line)
{
	GLfloat val = NULL;
	
	char token_name[25];
	
	sscanf(line, "%s %f", token_name, &val);
	_material->illum = val;

	_material->isillumAvailable = true;
}

bool ThreeDModelLoader::MTLLoader::isMaterialTextureMapAmbient(char * token)
{
	return token != NULL ? (strcmp(token, "map_Ka") == 0) : false;
}

void ThreeDModelLoader::MTLLoader::onMaterialTextureMapAmbient( char * line)
{
	char token_name[25], texture_name[256];
	
	sscanf(line, "%s %s", token_name, texture_name);
	
	_material->map_Ka.texturename =  texture_name;

	_material->ismap_KaAvailable = true;
}

bool ThreeDModelLoader::MTLLoader::isMaterialTextureMapDiffuse(char * token)
{
	return token != NULL ? (strcmp(token, "map_Kd") == 0) : false;
}

void ThreeDModelLoader::MTLLoader::onMaterialTextureMapDiffuse( char *line)
{
	char token_name[25], texture_name[256];
	
	sscanf(line, "%s %s", token_name,texture_name);
	
	_material->map_Kd.texturename = texture_name;

	_material->ismap_KdAvailable = true;
}

bool ThreeDModelLoader::MTLLoader::isMaterialTextureMapSpecular(char * token)
{
	return token != NULL ? (strcmp(token, "map_Kd") == 0) : false;
}

void ThreeDModelLoader::MTLLoader::onMaterialTextureMapSpecular(char * line)
{
	char token_name[25], texture_name[256];
	
	sscanf(line, "%s %s", token_name, texture_name);
	
	_material->map_Ks.texturename = texture_name;

	_material->ismap_KdAvailable = true;
}

bool ThreeDModelLoader::MTLLoader::isMaterialTextureMapSpecularHightLight(char * token)
{
	return token != NULL ? (strcmp(token, "map_Ns") == 0) : false;
}

void ThreeDModelLoader::MTLLoader::onMaterialTextureMapSpecularHightLight(char * line)
{
	char token_name[25], texture_name[256];

	sscanf(line, "%s %s", token_name, texture_name);

	_material->map_Ns.texturename = texture_name;

	_material->ismap_NsAvailable = true;
}

bool ThreeDModelLoader::MTLLoader::isMaterialTextureMapBump(char * token)
{
	return token != NULL ? (strcmp(token, "map_bump") == 0 || strcmp(token, "bump") == 0) : false;
}

void ThreeDModelLoader::MTLLoader::onMaterialTextureMapBump(char * line)
{
	char token_name[25], texture_name[256];

	sscanf(line, "%s %s", token_name, texture_name);

	_material->map_bump.texturename = texture_name;

	_material->ismap_bumpAvailable = true;
}

bool ThreeDModelLoader::MTLLoader::isMaterialTextureMapDisplacement(char * token)
{
	return token != NULL ? (strcmp(token, "disp") == 0): false;
}

void ThreeDModelLoader::MTLLoader::onMaterialTextureMapDisplacement(char * line)
{
	char token_name[25], texture_name[256];

	sscanf(line, "%s %s", token_name, texture_name);

	_material->map_disp.texturename = texture_name;

	_material->ismap_dispAvailable = true;
}

bool ThreeDModelLoader::MTLLoader::isMaterialTextureMapAlpha(char * token)
{
	return token != NULL ? (strcmp(token, "map_d") == 0) : false;
}

void ThreeDModelLoader::MTLLoader::onMaterialTextureMapAlpha(char * line)
{
	char token_name[25],texture_name[256];

	sscanf(line, "%s %s", token_name, texture_name);

	_material->map_d.texturename = texture_name;

	_material->ismap_dAvailable = true;
}

bool ThreeDModelLoader::MTLLoader::isMaterialSpecularExponentShininess(char * token)
{
	return token != NULL ? (strcmp(token, "Ns") == 0) : false;
}

void ThreeDModelLoader::MTLLoader::onMaterialSpecularExponentOrShininess( char * line)
{
	char token_name[25];
	GLfloat  val = 0;
	
	sscanf(line, "%s %f", token_name,&val);
	_material->Ns = val;

	_material->isNsAvailable = true;
}

bool ThreeDModelLoader::MTLLoader::isMaterialOpticalDensityOrIndexOfRefraction(char * token)
{
	return token != NULL ? (strcmp(token, "Ni") == 0) : false;
}

void ThreeDModelLoader::MTLLoader::onMaterialOpticalDensityOrIndexOfRefraction( char * line)
{
	char token_name[25];
	GLfloat  val = NULL;
	sscanf(line, "%s %f", token_name, &val);
	_material->Ni = val;

	_material->isNiAvailiable = true;
}

char * ThreeDModelLoader::MTLLoader::getMtlLibFileName()
{
	return _szMtlLib;
}

std::vector<ThreeDModelLoader::MATERIAL*>* ThreeDModelLoader::MTLLoader::getMaterials()
{
	return _pvMaterial;
}

ThreeDModelLoader::MTLLoader::~MTLLoader()
{
	//SAFE_FREE(_szMtlLib)
	SAFE_FREE(_material)
	SAFE_FREE(_szNextLine)
	SAFE_CLEAR_VECTOR_AND_FREE(_pvMaterial)
}
