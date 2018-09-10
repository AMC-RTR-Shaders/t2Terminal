/*
* @author: Rushabh Parakh
* @mailto: rgparakh@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/

#include "TerrainMap.h"

Rushabh::TerrainMap::TerrainMap()
{
	angle = 0.0f;
}

Rushabh::TerrainMap::~TerrainMap()
{
	UnInitialize();
}

BOOL Rushabh::TerrainMap::SceneHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	return 0;
}

void Rushabh::TerrainMap::Initialize()
{

	//CREAT VERTEXT SHADER OBJECT
	_vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

	//CREATE SOURCE CODE FOR VERTEX SHADER OBJECT
	const GLchar *vertexShaderSourceCode =
		"#version 440 core"							\
		"\n"										\
		"out VS_OUT"								\
		"{"											\
		"vec2 tc;"									\
		"}vs_out;"									\
		"void main(void)"							\
		"{"											\
		"float sideLength = 0.5;"					\
		"const vec4 vertices[] = vec4[](vec4(-sideLength, 0.0, -sideLength, 1.0),"  \
		"								vec4( sideLength, 0.0, -sideLength, 1.0),"  \
		"								vec4(-sideLength, 0.0,  sideLength, 1.0),"  \
		"								vec4( sideLength, 0.0,  sideLength, 1.0));" \
		"int x = gl_InstanceID & 63;"				\
		"int y = gl_InstanceID >> 6;"				\
		"vec2 offs = vec2(x,y);"					\
		"vs_out.tc = (vertices[gl_VertexID].xz + offs + vec2(0.5))/64.0;"					\
		"gl_Position = vertices[gl_VertexID] + vec4(float(x-32), 0.0, float(y-32), 0.0);"	\
		"}";

	//BIND vertexShaderSourcecode CODE TO gVertexShaderObject
	glShaderSource(_vertexShaderObject, 1, (const GLchar **)&vertexShaderSourceCode, NULL);

	//COMPILE VERTEX SHADER
	glCompileShader(_vertexShaderObject);

	/****************/


	GLint infoLogLength = 0;
	GLint iShaderCompilationStatus = 0;
	char *szInfoLog = NULL;
	GLsizei written = 0;

	glGetShaderiv(_vertexShaderObject, GL_COMPILE_STATUS, &iShaderCompilationStatus);

	if (iShaderCompilationStatus == GL_FALSE)
	{
		glGetShaderiv(_vertexShaderObject, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			szInfoLog = (char*)malloc(infoLogLength);

			if (szInfoLog != NULL)
			{

				glGetShaderInfoLog(_vertexShaderObject, infoLogLength, &written, szInfoLog);

				SAFE_LOG("TerrainMap Vertex Shader Compilation Log : %s\n", szInfoLog)
					SAFE_FREE(szInfoLog);
				UnInitialize();
				exit(0);
			}
		}
	}
	//CREAT VERTEXT SHADER OBJECT
	_tessControlShaderObject = glCreateShader(GL_TESS_CONTROL_SHADER);

	//CREATE SOURCE CODE FOR TESSELATION CONTROL SOURCE SHADER OBJECT
	const GLchar *tessControlShaderSourceCode =
		"#version 440 core"							\
		"\n"										\
		"layout (vertices = 4) out;"				\
		"in VS_OUT"									\
		"{"											\
		"vec2 tc;"									\
		"}tcs_in[];"								\
		"out TCS_OUT"								\
		"{"											\
		"vec2 tc;"									\
		"}tcs_out[];"								\
		"uniform mat4 u_mvp_matrix;"				\

		"void main(void)"							\
		"{"											\
		"if(gl_InvocationID == 0)"					\
		"{"											\
		"vec4 p0 = u_mvp_matrix * gl_in[0].gl_Position;"		\
		"vec4 p1 = u_mvp_matrix * gl_in[1].gl_Position;"		\
		"vec4 p2 = u_mvp_matrix * gl_in[2].gl_Position;"		\
		"vec4 p3 = u_mvp_matrix * gl_in[3].gl_Position;"		\
		"p0 /= p0.w;"								\
		"p1 /= p1.w;"								\
		"p2 /= p2.w;"								\
		"p3 /= p3.w;"								\
		"if(p0.z <= 0.0 || p1.z <= 0.0 || p2.z <= 0.0 || p3.z <= 0.0)"	\
		"{"											\
		"gl_TessLevelOuter[0] = 0.0;"				\
		"gl_TessLevelOuter[1] = 0.0;"				\
		"gl_TessLevelOuter[2] = 0.0;"				\
		"gl_TessLevelOuter[3] = 0.0;"				\
		"}"											\
		"else"										\
		"{"											\
		"float l0 = length(p2.xy - p0.xy) * 16.0 + 1.0;"	\
		"float l1 = length(p3.xy - p2.xy) * 16.0 + 1.0;"	\
		"float l2 = length(p3.xy - p1.xy) * 16.0 + 1.0;"	\
		"float l3 = length(p1.xy - p0.xy) * 16.0 + 1.0;"	\
		"gl_TessLevelOuter[0] = l0;"						\
		"gl_TessLevelOuter[1] = l1;"						\
		"gl_TessLevelOuter[2] = l2;"						\
		"gl_TessLevelOuter[3] = l3;"						\
		"gl_TessLevelInner[0] = min(l1, l3);"				\
		"gl_TessLevelInner[1] = min(l0, l2);"				\
		"}"													\
		"}"													\
		"gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;"	\
		"tcs_out[gl_InvocationID].tc = tcs_in[gl_InvocationID].tc;"					\
		"}";

	//BIND vertexShaderSourcecode CODE TO gVertexShaderObject
	glShaderSource(_tessControlShaderObject, 1, (const GLchar **)&tessControlShaderSourceCode, NULL);

	//COMPILE VERTEX SHADER
	glCompileShader(_tessControlShaderObject);

	/****************/


	infoLogLength = 0;
	iShaderCompilationStatus = 0;
	szInfoLog = NULL;
	written = 0;

	glGetShaderiv(_tessControlShaderObject, GL_COMPILE_STATUS, &iShaderCompilationStatus);

	if (iShaderCompilationStatus == GL_FALSE)
	{
		glGetShaderiv(_tessControlShaderObject, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			szInfoLog = (char*)malloc(infoLogLength);

			if (szInfoLog != NULL)
			{

				glGetShaderInfoLog(_tessControlShaderObject, infoLogLength, &written, szInfoLog);

				SAFE_LOG("TerrainMap Tesselation Control Shader Compilation Log : %s\n", szInfoLog)
					SAFE_FREE(szInfoLog);
				UnInitialize();
				exit(0);
			}
		}
	}

	//CREAT VERTEXT SHADER OBJECT
	_tessEvaluationShaderObject = glCreateShader(GL_TESS_EVALUATION_SHADER);

	//CREATE SOURCE CODE FOR TESSELATION CONTROL SOURCE SHADER OBJECT
	const GLchar *tessEvaluationShaderSourceCode =
		"#version 440 core"							\
		"\n"										\
		"layout (quads, fractional_odd_spacing) in;"\
		"uniform sampler2D u_tex_displacement;"		\
		"uniform mat4 u_mv_matrix;"				\
		"uniform mat4 u_p_matrix;"				\
		"uniform float u_dmap_depth;"				\
		"in TCS_OUT"								\
		"{"											\
		"vec2 tc;"									\
		"} tes_in[];"								\
		"out TES_OUT"								\
		"{"											\
		"vec2 tc;"									\
		"vec3 world_coord;"							\
		"vec3 eye_coord;"							\
		"} tes_out;"								\
		"void main(void)"							\
		"{"											\
		"vec2 tc1 = mix(tes_in[0].tc, tes_in[1].tc, gl_TessCoord.x);"\
		"vec2 tc2 = mix(tes_in[2].tc, tes_in[3].tc, gl_TessCoord.x);"\
		"vec2 tc = mix(tc2, tc1, gl_TessCoord.y);"	\
		"vec4 p1 = mix(gl_in[0].gl_Position, gl_in[1].gl_Position, gl_TessCoord.x);"	\
		"vec4 p2 = mix(gl_in[2].gl_Position, gl_in[3].gl_Position, gl_TessCoord.x);"	\
		"vec4 p = mix(p2, p1, gl_TessCoord.y);"		\
		"p.y += texture(u_tex_displacement, tc).r * u_dmap_depth;"\
		"vec4 P_eye = u_mv_matrix * p;"				\
		"tes_out.tc = tc;"							\
		"tes_out.world_coord = p.xyz;"				\
		"tes_out.eye_coord = P_eye.xyz;"			\
		"gl_Position = u_p_matrix * P_eye;"			\
		"}";


	//BIND vertexShaderSourcecode CODE TO gVertexShaderObject
	glShaderSource(_tessEvaluationShaderObject, 1, (const GLchar **)&tessEvaluationShaderSourceCode, NULL);

	//COMPILE VERTEX SHADER
	glCompileShader(_tessEvaluationShaderObject);

	/****************/


	infoLogLength = 0;
	iShaderCompilationStatus = 0;
	szInfoLog = NULL;
	written = 0;

	glGetShaderiv(_tessEvaluationShaderObject, GL_COMPILE_STATUS, &iShaderCompilationStatus);

	if (iShaderCompilationStatus == GL_FALSE)
	{
		glGetShaderiv(_tessEvaluationShaderObject, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			szInfoLog = (char*)malloc(infoLogLength);

			if (szInfoLog != NULL)
			{

				glGetShaderInfoLog(_tessEvaluationShaderObject, infoLogLength, &written, szInfoLog);

				SAFE_LOG("TerrainMap Tesselation Control Shader Compilation Log : %s\n", szInfoLog)
					SAFE_FREE(szInfoLog);
				UnInitialize();
				exit(0);
			}
		}
	}

	//Create FRAGMENT SHADER OBJECT
	_fragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);

	//CREATE SOURCE CODE FOR FRAGMENT SHADER
	const GLchar *fragmentShaderSourceCode =
		"#version 440 core"										\
		"\n"													\
		"out vec4 FragColor;"									\
		"layout (binding = 1) uniform sampler2D u_tex_color;"	\
		"uniform bool u_enable_fog;"								\
		"uniform vec4 fog_color = vec4(0.6, 0.7, 0.8, 0.0);"	\
		"in TES_OUT"											\
		"{"														\
		"vec2 tc;"												\
		"vec3 world_coord;"										\
		"vec3 eye_coord;"										\
		"} fs_in;"												\
		"vec4 fog(vec4 c)"															\
		"{"																			\
		"float z = length(fs_in.eye_coord);"										\
		"float de = 0.025 * smoothstep(0.0, 6.0, 10.0 - fs_in.world_coord.y);"		\
		"float di = 0.045 * (smoothstep(0.0, 40.0, 20.0 - fs_in.world_coord.y));"	\
		"float extinction = exp(-z * de);"											\
		"float inscattering = exp(-z * di);"										\
		"return c * extinction + fog_color * (1.0 - inscattering);"					\
		"}"																			\
		"void main(void)"										\
		"{"														\
		"vec4 landscape = texture(u_tex_color, fs_in.tc); "		\
		"if(u_enable_fog)"										\
		"{"														\
		"FragColor = fog(landscape);"							\
		"}"														\
		"else"													\
		"{"														\
		"FragColor = landscape;"								\
		"}"														\
		"}";

	//BIND fragmentShaderSourceCode to gFragmentShaderObject
	glShaderSource(_fragmentShaderObject, 1, (const GLchar **)&fragmentShaderSourceCode, NULL);

	//COMPILE FRAGMENT SHADER
	glCompileShader(_fragmentShaderObject);

	infoLogLength = 0;
	iShaderCompilationStatus = 0;
	szInfoLog = NULL;
	written = 0;

	glGetShaderiv(_fragmentShaderObject, GL_COMPILE_STATUS, &iShaderCompilationStatus);
	if (iShaderCompilationStatus == GL_FALSE)
	{
		glGetShaderiv(_fragmentShaderObject, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			szInfoLog = (char*)malloc(sizeof(infoLogLength));

			if (szInfoLog != NULL)
			{
				glGetShaderInfoLog(_fragmentShaderObject, infoLogLength, &written, szInfoLog);

				SAFE_LOG("TerrainMap Fragment Shader Compilation Log : %s\n", szInfoLog)
					SAFE_FREE(szInfoLog);
				UnInitialize();
				exit(0);
			}
		}
	}

	// *** SHADER PROGRAM ****//
	//CREATE SHADER PROGRAM OBJECT
	_shaderProgramObject = glCreateProgram();

	//ATTACH VERTEX SHADER PROGRAM TO SHADER PROGRAM
	glAttachShader(_shaderProgramObject, _vertexShaderObject);

	//ATTACH TESSELATION CONTROL SHADER PROGRAM TO SHADER PROGRAM
	glAttachShader(_shaderProgramObject, _tessControlShaderObject);

	//ATTACH TESSELATION EVALUTAION SHADER PROGRAM TO SHADER PROGRAM
	glAttachShader(_shaderProgramObject, _tessEvaluationShaderObject);

	//ATTACH FRAGMENT SHADER PROGRAM TO SHADER PROGRAM
	glAttachShader(_shaderProgramObject, _fragmentShaderObject);

	//LINK THE SHADER
	glLinkProgram(_shaderProgramObject);

	infoLogLength = 0;
	iShaderCompilationStatus = 0;
	szInfoLog = NULL;
	written = 0;

	GLint iShaderProgramLinkStatus = 0;
	glGetProgramiv(_shaderProgramObject, GL_LINK_STATUS, &iShaderProgramLinkStatus);
	if (iShaderProgramLinkStatus == GL_FALSE)
	{
		glGetProgramiv(_shaderProgramObject, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			szInfoLog = (char*)malloc(sizeof(infoLogLength));
			if (szInfoLog != NULL)
			{

				glGetProgramInfoLog(_shaderProgramObject, infoLogLength, &written, szInfoLog);

				SAFE_LOG("TerrainMap Shader Program Link Log : %s \n", szInfoLog)
					SAFE_FREE(szInfoLog);
				UnInitialize();
				exit(0);
			}

		}
	}


	//GET MVP UNIFORM LOCATION
	//_modelMatrixUniform = glGetUniformLocation(_shaderProgramObject, "u_model_matrix");
	//_ViewMatrixUniform = glGetUniformLocation(_shaderProgramObject, "u_view_matrix");
	//_projectMatrixUniform = glGetUniformLocation(_shaderProgramObject, "u_projection_matrix");

	_mVPUniform = glGetUniformLocation(_shaderProgramObject, "u_mvp_matrix");
	_modelViewMatrixUniform = glGetUniformLocation(_shaderProgramObject, "u_mv_matrix");
	_projectionMatrixUniform = glGetUniformLocation(_shaderProgramObject, "u_p_matrix");

	_enableFogUniform = glGetUniformLocation(_shaderProgramObject, "u_enable_fog");
	_dmapDepthUniform = glGetUniformLocation(_shaderProgramObject, "u_dmap_depth");
	_texture_displacement_uniform = glGetUniformLocation(_shaderProgramObject, "u_tex_displacement");
	_texture_color_uniform = glGetUniformLocation(_shaderProgramObject, "u_tex_color");

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);

	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LEQUAL);

	glShadeModel(GL_SMOOTH);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	_perspectiveProjectionMatrix = mat4::identity();

	LoadGLTextures(&_texture_Terrain_Map, MAKEINTRESOURCE(ID_BITMAP_TERRAIN_MAP));
}

int Rushabh::TerrainMap::LoadGLTextures(GLuint *texture, TCHAR imageResourceId[])
{
	//variable declarations
	HBITMAP hBitmap;
	BITMAP bmp;
	int iStatus = FALSE;

	//code 
	glGenTextures(1, texture); //1 image
	hBitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL), imageResourceId, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	if (hBitmap) //if bitmap exists ( means hBitmap is not null )
	{
		iStatus = TRUE;
		GetObject(hBitmap, sizeof(bmp), &bmp);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4); //pixel storage mode( word alignment/4 bytes ).
		glBindTexture(GL_TEXTURE_2D, *texture); //bind texture
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		//generate mipmapped texture ( 3 bytes, width, height & data from bmp)
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGB,
			bmp.bmWidth,
			bmp.bmHeight,
			0,
			GL_BGR_EXT,
			GL_UNSIGNED_BYTE,
			bmp.bmBits);

		glGenerateMipmap(GL_TEXTURE_2D);

		DeleteObject(hBitmap); //delete unwanted bitmap handle
	}
	return(iStatus);
}


void Rushabh::TerrainMap::Update()
{

}

void Rushabh::TerrainMap::ReSize(int width, int height, struct ResizeAttributes attributes)
{
	if (height == 0)
		height = 1;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	_perspectiveProjectionMatrix = vmath::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 1000.0f);

}

void Rushabh::TerrainMap::Render(HDC hdc, struct Attributes attributes)
{

	mat4 modelViewMatrix = mat4::identity();
	mat4 modelViewProjectionMatrix = mat4::identity();
	mat4 rotateMatrix = mat4::identity();

	modelViewMatrix = translate(
		attributes.translateCoords[SCENE_AIRPORT][0] + attributes.translateCoords[SCENE_TERRAIN_MAP][0],
		attributes.translateCoords[SCENE_AIRPORT][1] + attributes.translateCoords[SCENE_TERRAIN_MAP][1],
		attributes.translateCoords[SCENE_AIRPORT][2] + attributes.translateCoords[SCENE_TERRAIN_MAP][2]);

	rotateMatrix = rotate(
		attributes.rotateCoords[SCENE_TERRAIN_MAP][0], 
		attributes.rotateCoords[SCENE_TERRAIN_MAP][1],
		attributes.rotateCoords[SCENE_TERRAIN_MAP][2]);

	modelViewMatrix = modelViewMatrix * rotateMatrix;

	modelViewProjectionMatrix = _perspectiveProjectionMatrix * modelViewMatrix;

	//START USING SHADER OBJECT	
	glUseProgram(_shaderProgramObject);

	glUniformMatrix4fv(_mVPUniform, 1, GL_FALSE, modelViewProjectionMatrix);
	glUniformMatrix4fv(_modelViewMatrixUniform, 1, GL_FALSE, modelViewMatrix);
	glUniformMatrix4fv(_projectionMatrixUniform, 1, GL_FALSE, _perspectiveProjectionMatrix);

	glUniform1f(_dmapDepthUniform, 2.0f);
	glUniform1i(_enableFogUniform, false);

	glPatchParameteri(GL_PATCH_VERTICES, 4);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texture_Terrain_Map);
	glUniform1i(_texture_displacement_uniform, 0);
	glUniform1i(_texture_color_uniform, 0);

	//if (gbWireFrame)
	//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glDrawArraysInstanced(GL_PATCHES, 0, 4, 64 * 64);

	//STOP USING SHADER
	glUseProgram(0);

}

void Rushabh::TerrainMap::SceneTransition()
{
}

void Rushabh::TerrainMap::UnInitialize()
{
	//DETACH THE FRAGMENT SHADER OBJECT
	glDetachShader(_shaderProgramObject, _fragmentShaderObject);

	//DETACH THE VERTEX SHADER OBJECT
	glDetachShader(_shaderProgramObject, _vertexShaderObject);


	//DELETE VERTEX SHADER OBJECT
	glDeleteShader(_vertexShaderObject);
	_vertexShaderObject = 0;

	//DELETE FRAGMENT SHADER OBJECT
	glDeleteShader(_fragmentShaderObject);
	_fragmentShaderObject = 0;

	//DELETE SHADER PROGRAM OBJECT
	glDeleteProgram(_shaderProgramObject);
	_shaderProgramObject = 0;

	//UNLINK THE PROGRAM
	glUseProgram(0);
}
