/*
* @author: Praveen Suryawanshi
* @mailto: suryawanshi.praveen007@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/

#include "WireFrameEffect.h"

float translateZ = -300.0f;


Praveen::WireFrameEffect::WireFrameEffect()
{
	_wireFrameEffect_angle = 0.0f;
	_particleTime = 0.0f;
	_wireFrameThreePillar = NULL;
	_wireFrameAllPillar = NULL;

	_modelParserThreePillar = NULL;
	_modelParserAllPillar = NULL;
	

	_modelParserThreePillar = new ModelParser("3DModels\\Scene_2\\ModelGrowingAirport\\scaledThreePiller.obj");
	_modelParserAllPillar = new ModelParser("3DModels\\Scene_2\\ModelGrowingAirport\\scaledPillerAll.obj");
	CHECK_NULL(_modelParserThreePillar);

	return;
CLEAN_LOCAL_ALLOCATION_BELOW:
	UnInitialize();
}

Praveen::WireFrameEffect::~WireFrameEffect()
{
	UnInitialize();
}

BOOL Praveen::WireFrameEffect::SceneHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	return 0;
}

void Praveen::WireFrameEffect::Initialize()
{	
	SAFE_LOG("Chair shading language supported verison is : %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION))

	//CREAT VERTEXT SHADER OBJECT
	_vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

	//CREATE SOURCE CODE FOR VERTEX SHADER OBJECT
	const GLchar *vertexShaderSourcecode =
		"#version 430" \
		"\n" \
		"in vec4 vPosition;" \
		"in vec3 vNormal;" \
		"in vec3 vColor;"\
		"uniform mat4 u_model_matrix;" \
		"uniform mat4 u_view_matrix;" \
		"uniform mat4 u_projection_matrix;" \
		"uniform vec3 u_La;" \
		"uniform vec3 u_Ld;" \
		"uniform vec3 u_Ls;" \
		"uniform vec4 u_light_position;" \
		"uniform vec3 u_Ka;" \
		"uniform vec3 u_Kd;" \
		"uniform vec3 u_Ks;" \
		"uniform float u_material_shininess;" \
		"out vec3 phong_ads_color;" \
		"void main(void)" \
		"{" \

			"vec4 eye_coordinates=u_view_matrix * u_model_matrix * vPosition;" \
			"vec3 transformed_normals=normalize(mat3(u_view_matrix * u_model_matrix) * vNormal);" \
			"vec3 light_direction = normalize(vec3(u_light_position) - eye_coordinates.xyz);" \
			"float tn_dot_ld = max(dot(transformed_normals, light_direction),0.0);" \
			"vec3 ambient = u_La * u_Ka;" \
			"vec3 diffuse = u_Ld * u_Kd * tn_dot_ld;" \
			"vec3 reflection_vector = reflect(-light_direction, transformed_normals);" \
			"vec3 viewer_vector = normalize(-eye_coordinates.xyz);" \
			"vec3 specular = u_Ls * u_Ks * pow(max(dot(reflection_vector, viewer_vector), 0.0), u_material_shininess);" \
			"phong_ads_color=ambient + diffuse + specular;" \
			"phong_ads_color = vColor;"\
			"gl_Position=u_projection_matrix * u_view_matrix * u_model_matrix * vPosition;" \
			
		"}";

	//BIND vertexShaderSourcecode CODE TO gVertexShaderObject
	glShaderSource(_vertexShaderObject, 1, (const GLchar **)&vertexShaderSourcecode, NULL);

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

				SAFE_LOG("WireFrameEffect Vertex Shader Compilation Log : %s\n", szInfoLog)
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
		"#version 430"\
		"\n" \
		"in vec3 phong_ads_color;" \
		"out vec4 FragColor;" \
		"void main(void)" \
		"{" \
			"FragColor = vec4(phong_ads_color,0.0f);"\
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

				SAFE_LOG("WireFrameEffect Fragment Shader Compilation Log : %s\n", szInfoLog)
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

	//ATTACH FRAGMENT SHADER PROGRAM TO SHADER PROGRAM
	glAttachShader(_shaderProgramObject, _fragmentShaderObject);

	//PRE-LINK BINDING OF SHADER PROGRAM OBJECT WITH VERTEX SHADER POSITION ATTRIBUTE
	glBindAttribLocation(_shaderProgramObject, AMC_ATTRIBUTE_VERTEX, "vPosition");
	//PRE-LINK BINDING OF SHADER PROGRAM OBJECT WITTH TEXTURE SHADER ATTRIBUTE
	glBindAttribLocation(_shaderProgramObject, AMC_ATTRIBUTE_NORMAL, "vNormal");
	//PRE-LINK BINDING OF SHADER PROGRAM OBJECT WITTH COLOR SHADER ATTRIBUTE
	glBindAttribLocation(_shaderProgramObject, AMC_ATTRIBUTE_COLOR, "vColor");

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

				char *szErrorfoLog = (char*)malloc(infoLogLength + 1024);
				sscanf(szInfoLog, "Aeroplane Shader Program Link Log : %s \n", szInfoLog);
				SAFE_LOG("chair Shader Program Link Log : %s \n", szInfoLog)
				SAFE_FREE(szInfoLog);
				UnInitialize();
				exit(0);
			}

		}
	}


	//GET MVP UNIFORM LOCATION
	_modelMatrixUniform = glGetUniformLocation(_shaderProgramObject, "u_model_matrix");
	_ViewMatrixUniform = glGetUniformLocation(_shaderProgramObject, "u_view_matrix");
	_projectMatrixUniform = glGetUniformLocation(_shaderProgramObject, "u_projection_matrix");


	//AMBIENT COLOR TOKEN
	_LaUniform = glGetUniformLocation(_shaderProgramObject, "u_La");

	// DIFUSE COLOR TOKEN
	_LdUniform = glGetUniformLocation(_shaderProgramObject, "u_Ld");

	// SPECULAR COLOR TOKEN
	_LsUniform = glGetUniformLocation(_shaderProgramObject, "u_Ls");

	// LIGHT POSITION TOKEN
	_LightPositionUniform = glGetUniformLocation(_shaderProgramObject, "u_light_position");


	//SHINYNESS COLOR TOKEN
	material_shininess_uniform = glGetUniformLocation(_shaderProgramObject, "u_material_shininess");



	_wireFrameThreePillar = (GLOBJECT_WIREFRAME_BUILDING*)malloc(sizeof(GLOBJECT_WIREFRAME_BUILDING));
	ZeroMemory(_wireFrameThreePillar, sizeof(GLOBJECT_WIREFRAME_BUILDING));
	_wireFrameThreePillar->wireFrameQuery = WIREFRAME_QUERY::WIREFRAME_YES;
	_wireFrameThreePillar->speedValueToIncrementSolidFaces = 0.6f;
	_wireFrameThreePillar->speedValueToIncrementWireFaces =  1.0f;
	
	_wireFrameThreePillar->triangle_poin1_color[0] = 240.0f / 255.0f;
	_wireFrameThreePillar->triangle_poin1_color[1] = 240.0f / 255.0f;
	_wireFrameThreePillar->triangle_poin1_color[2] = 240.0f / 255.0f;

	_wireFrameThreePillar->triangle_poin2_color[0] = 240.0f / 255.0f;
	_wireFrameThreePillar->triangle_poin2_color[1] = 240.0f / 255.0f;
	_wireFrameThreePillar->triangle_poin2_color[2] = 240.0f / 255.0f;

	_wireFrameThreePillar->triangle_poin3_color[0] = 240.0f / 255.0f;
	_wireFrameThreePillar->triangle_poin3_color[1] = 240.0f / 255.0f;
	_wireFrameThreePillar->triangle_poin3_color[2] = 240.0f / 255.0f;
	
	
	//LOAD THE MODEL HERE
	CHECK_NULL(_modelParserThreePillar);
	_modelParserThreePillar->parse(_shaderProgramObject, ThreeDModelLoader::PROCESS_TYPE::CPU, ThreeDModelLoader::DRAW_TYPE::DRAW_USING_ARRAYS,NULL, _wireFrameThreePillar);



	//ALL PILLAR
	_wireFrameAllPillar = (GLOBJECT_WIREFRAME_BUILDING*)malloc(sizeof(GLOBJECT_WIREFRAME_BUILDING));
	ZeroMemory(_wireFrameAllPillar, sizeof(GLOBJECT_WIREFRAME_BUILDING));
	_wireFrameAllPillar->wireFrameQuery = WIREFRAME_QUERY::WIREFRAME_YES;
	_wireFrameAllPillar->speedValueToIncrementSolidFaces = 3.0f;
	_wireFrameAllPillar->speedValueToIncrementWireFaces = 3.0f;

	_wireFrameAllPillar->triangle_poin1_color[0] = 240.0f / 255.0f;
	_wireFrameAllPillar->triangle_poin1_color[1] = 240.0f / 255.0f;
	_wireFrameAllPillar->triangle_poin1_color[2] = 240.0f / 255.0f;

	_wireFrameAllPillar->triangle_poin2_color[0] = 240.0f / 255.0f;
	_wireFrameAllPillar->triangle_poin2_color[1] = 240.0f / 255.0f;
	_wireFrameAllPillar->triangle_poin2_color[2] = 240.0f / 255.0f;

	_wireFrameAllPillar->triangle_poin3_color[0] = 240.0f / 255.0f;
	_wireFrameAllPillar->triangle_poin3_color[1] = 240.0f / 255.0f;
	_wireFrameAllPillar->triangle_poin3_color[2] = 240.0f / 255.0f;

	//LOAD THE MODEL HERE
	CHECK_NULL(_modelParserAllPillar);
	_modelParserAllPillar->parse(_shaderProgramObject, ThreeDModelLoader::PROCESS_TYPE::CPU, ThreeDModelLoader::DRAW_TYPE::DRAW_USING_ARRAYS,NULL, _wireFrameAllPillar);


	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);

	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LEQUAL);

	glShadeModel(GL_SMOOTH);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glDisable(GL_CULL_FACE);

	_perspectiveProjectionMatrix = mat4::identity();

	return;

CLEAN_LOCAL_ALLOCATION_BELOW:
	UnInitialize();

}

void Praveen::WireFrameEffect::Update()
{
	
	_wireFrameEffect_angle = _wireFrameEffect_angle + 0.3f;

	if (_wireFrameEffect_angle >= 360.0f)
		_wireFrameEffect_angle = _wireFrameEffect_angle - 360.0f;


	//update Code
	
	if (_wireFrameThreePillar->isModelWireFacesDone == true)
	{
		if (_wireFrameThreePillar->totalSolidFaces < _wireFrameThreePillar->lengthOfVertexMap)
		{
			_wireFrameThreePillar->incrementSolidFaces += _wireFrameThreePillar->speedValueToIncrementSolidFaces;
			if (_wireFrameThreePillar->incrementSolidFaces > 1.0f)
			{
				_wireFrameThreePillar->totalSolidFaces += (int)_wireFrameThreePillar->incrementSolidFaces;
				_wireFrameThreePillar->incrementSolidFaces = 0.0f;
			}
		}
		if ((int)_wireFrameThreePillar->totalSolidFaces == _wireFrameThreePillar->lengthOfVertexMap)
		{
			_wireFrameThreePillar->isModelSolidFacesDone = true;
		}
	}

	if (_wireFrameThreePillar->totalWireFaces <_wireFrameThreePillar->lengthOfVertexMap)
	{
		_wireFrameThreePillar->incrementWireFaces += _wireFrameThreePillar->speedValueToIncrementWireFaces;
		if (_wireFrameThreePillar->incrementWireFaces > 1.0f)
		{
			_wireFrameThreePillar->totalWireFaces += (int)_wireFrameThreePillar->incrementWireFaces;
			_wireFrameThreePillar->incrementWireFaces = 0.0f;
		}
	}
	if ((int)_wireFrameThreePillar->totalWireFaces == _wireFrameThreePillar->lengthOfVertexMap)
	{
		_wireFrameThreePillar->isModelWireFacesDone = true;
	}
	//


	


	//update Code
	if (_wireFrameThreePillar->isModelSolidFacesDone )
	{
		if (_wireFrameAllPillar->isModelWireFacesDone == true)
		{
			if (_wireFrameAllPillar->totalSolidFaces < _wireFrameAllPillar->lengthOfVertexMap)
			{
				_wireFrameAllPillar->incrementSolidFaces += _wireFrameAllPillar->speedValueToIncrementSolidFaces;
				if (_wireFrameAllPillar->incrementSolidFaces > 1.0f)
				{
					_wireFrameAllPillar->totalSolidFaces += (int)_wireFrameAllPillar->incrementSolidFaces;
					_wireFrameAllPillar->incrementSolidFaces = 0.0f;
				}
			}
			if ((int)_wireFrameAllPillar->totalSolidFaces == (int)_wireFrameAllPillar->lengthOfVertexMap)
			{
				_wireFrameAllPillar->isModelSolidFacesDone = true;
			}
		}

		if (_wireFrameAllPillar->totalWireFaces < _wireFrameAllPillar->lengthOfVertexMap)
		{
			_wireFrameAllPillar->incrementWireFaces += _wireFrameAllPillar->speedValueToIncrementWireFaces;
			if (_wireFrameAllPillar->incrementWireFaces > 1.0f)
			{
				_wireFrameAllPillar->totalWireFaces += (int)_wireFrameAllPillar->incrementWireFaces;
				_wireFrameAllPillar->incrementWireFaces = 0.0f;
			}
		}
		if ((int)_wireFrameAllPillar->totalWireFaces == _wireFrameAllPillar->lengthOfVertexMap)
		{
			_wireFrameAllPillar->isModelWireFacesDone = true;
		}
	}
	//
	
	// translateZ -= 0.1f;
}

void Praveen::WireFrameEffect::ReSize(int width, int height, struct ResizeAttributes attributes)
{
	if (height == 0)
		height = 1;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	_perspectiveProjectionMatrix = vmath::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 10000.0f);
}

void Praveen::WireFrameEffect::Render(HDC hdc, struct Attributes attributes)
{
	mat4 modelMatrix = mat4::identity();
	mat4 viewMatrix = mat4::identity();
	mat4 rotateMatrix = mat4::identity();

	static GLfloat lightAmbient[] = { 0.0f,0.0f,0.0f,1.0f };
	static GLfloat lightDiffuse[] = { 1.0f,1.0f,1.0f,1.0f };
	static GLfloat lightSpecular[] = { 1.0f,1.0f,1.0f,1.0f };
	static GLfloat lightPosition[] = { 100.0f,100.0f,100.0f,1.0f };
	static GLfloat material_shininess = 50.0f;

	//START USING SHADER OBJECT	
	glUseProgram(_shaderProgramObject);



	// setting light's properties
	glUniform3fv(_LaUniform, 1, lightAmbient);
	glUniform3fv(_LdUniform, 1, lightDiffuse);
	glUniform3fv(_LsUniform, 1, lightSpecular);
	glUniform4fv(_LightPositionUniform, 1, lightPosition);

	//material shininess
	glUniform1f(material_shininess_uniform, material_shininess);
	//

	//modelMatrix = translate(attributes.translateCoords[0] + 0.0f, attributes.translateCoords[1] + 0.0f, attributes.translateCoords[2] + 0.0f);
	///rotateMatrix = vmath::rotate<GLfloat>(90.0f, 1.0f, 0.0f, 0.0f);
	//modelMatrix = modelMatrix * rotateMatrix;
	//modelMatrix = translate(-400.0f, -5.0f, -1950.0f);
	modelMatrix =translate(
		attributes.translateCoords[SCENE_AIRPORT_MODEL][0] + TRANS_X_WIREFRAME, 
		attributes.translateCoords[SCENE_AIRPORT_MODEL][1]+ TRANS_Y_WIREFRAME,
		attributes.translateCoords[SCENE_AIRPORT_MODEL][2] + TRANS_Z_WIREFRAME);

	rotateMatrix = rotate(
		attributes.rotateCoords[SCENE_AIRPORT_MODEL][0],
		attributes.rotateCoords[SCENE_AIRPORT_MODEL][1],
		attributes.rotateCoords[SCENE_AIRPORT_MODEL][2]);

	modelMatrix = modelMatrix * scale(0.46f, 0.5f, 0.5f) * rotateMatrix;

	rotateMatrix = vmath::rotate<GLfloat>(_wireFrameEffect_angle, _wireFrameEffect_angle, _wireFrameEffect_angle);
	//rotateMatrix = vmath::rotate<GLfloat>(287.971619f, 287.971619f, 287.971619f);

	glUniformMatrix4fv(_modelMatrixUniform, 1, GL_FALSE, modelMatrix);
	glUniformMatrix4fv(_ViewMatrixUniform, 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(_projectMatrixUniform, 1, GL_FALSE, _perspectiveProjectionMatrix);

	CHECK_NULL(_modelParserThreePillar);
	
	if (_wireFrameThreePillar->isModelSolidFacesDone)
		_modelParserAllPillar->draw();

	_modelParserThreePillar->draw();

	//STOP USING SHADER
	glUseProgram(0);

	Update();
	return;


CLEAN_LOCAL_ALLOCATION_BELOW:
	UnInitialize();
}

void Praveen::WireFrameEffect::SceneTransition()
{
}

void Praveen::WireFrameEffect::UnInitialize()
{

	SAFE_DELETE(_modelParserThreePillar);
	SAFE_DELETE(_modelParserAllPillar);

	SAFE_DELETE(_wireFrameThreePillar);
	SAFE_DELETE(_wireFrameAllPillar);

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
