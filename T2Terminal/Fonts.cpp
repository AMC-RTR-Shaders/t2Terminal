
/*
* @author: Sanket Deshmukh
* @mailto: 1sanketdeshmukhgmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/

#include "Fonts.h"

Sanket::Fonts::Fonts()
{
	_angle = 0.0f;

	_modelParserShaders        = new ModelParser("3DModels\\Scene_3\\ShadersFont.obj");
	CHECK_NULL(_modelParserShaders);
	_modelParserPresent        = new ModelParser("3DModels\\Scene_3\\PresentsFont.obj");
	CHECK_NULL(_modelParserPresent);
	_modelParserT2Terminal     = new ModelParser("3DModels\\Scene_3\\T2TerminalFont.obj");
	CHECK_NULL(_modelParserT2Terminal);
	_modelParserPoweredBy      = new ModelParser("3DModels\\Scene_3\\PowerByFont.obj");
	CHECK_NULL(_modelParserPoweredBy);
	_modelParserAstromedicomp  = new ModelParser("3DModels\\Scene_3\\AstromedicompFont.obj");

	CHECK_NULL(_modelParserAstromedicomp);

	return;
CLEAN_LOCAL_ALLOCATION_BELOW:
	UnInitialize();
}

Sanket::Fonts::~Fonts()
{
	UnInitialize();
}

BOOL Sanket::Fonts::SceneHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	return 0;
}

void Sanket::Fonts::Initialize()
{
	SAFE_LOG("Fonts shading language supported verison is : %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION))

		//CREAT VERTEXT SHADER OBJECT
		_vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

	//CREATE SOURCE CODE FOR VERTEX SHADER OBJECT
	const GLchar *vertexShaderSourcecode =
		"#version 430" \
		"\n" \
		"in vec4 vPosition;" \
		"in vec3 vNormal;" \
		"in vec2 vTexture0_Coord;"\
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
		"out vec2 out_vTexture0_Coord;"\

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

		"gl_Position=u_projection_matrix * u_view_matrix * u_model_matrix * vPosition;" \
		"out_vTexture0_Coord = vTexture0_Coord;"\
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
				SAFE_LOG("Fonts Vertex Shader Compilation Log : %s\n", szInfoLog)
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
		"uniform sampler2D u_texture0_sampler;"
		"in vec3 phong_ads_color;" \
		"in vec2 out_vTexture0_Coord;"\
		"out vec4 FragColor;" \
		"void main(void)" \
		"{" \
		"FragColor = texture(u_texture0_sampler,out_vTexture0_Coord)* vec4(phong_ads_color,1.0);"\
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

				SAFE_LOG("Fonts Fragment Shader Compilation Log : %s\n", szInfoLog)
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
	//PRE-LINK BINDING OF SHADER PROGRAM OBJECT WITTH TEXTURE SHADER ATTRIBUTE
	glBindAttribLocation(_shaderProgramObject, AMC_ATTRIBUTE_TEXTURE0, "vTexture0_Coord");

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

				SAFE_LOG("Fonts Shader Program Link Log : %s \n", szInfoLog)
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

	//

	//LOAD THE MODEL HERE
	GLOBJECT_INSTANCEING instancing;
	instancing.instancingQuery = INSTANCING_QUERY::NO;
	CHECK_NULL(_modelParserShaders);

	_modelParserShaders->parse(_shaderProgramObject, ThreeDModelLoader::PROCESS_TYPE::CPU, ThreeDModelLoader::DRAW_TYPE::DRAW_USING_ARRAYS, &instancing,NULL);

	CHECK_NULL(_modelParserPresent);

	_modelParserPresent->parse(_shaderProgramObject, ThreeDModelLoader::PROCESS_TYPE::CPU, ThreeDModelLoader::DRAW_TYPE::DRAW_USING_ARRAYS, &instancing, NULL);

	CHECK_NULL(_modelParserT2Terminal);

	_modelParserT2Terminal->parse(_shaderProgramObject, ThreeDModelLoader::PROCESS_TYPE::CPU, ThreeDModelLoader::DRAW_TYPE::DRAW_USING_ARRAYS, &instancing, NULL);

	CHECK_NULL(_modelParserPoweredBy);

	_modelParserPoweredBy->parse(_shaderProgramObject, ThreeDModelLoader::PROCESS_TYPE::CPU, ThreeDModelLoader::DRAW_TYPE::DRAW_USING_ARRAYS, &instancing, NULL);

	CHECK_NULL(_modelParserAstromedicomp);

	_modelParserAstromedicomp->parse(_shaderProgramObject, ThreeDModelLoader::PROCESS_TYPE::CPU, ThreeDModelLoader::DRAW_TYPE::DRAW_USING_ARRAYS, &instancing, NULL);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);

	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LEQUAL);

	glShadeModel(GL_SMOOTH);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//glEnable(GL_CULL_FACE); /*Turning oFF cull , as we are doing animation , and so need to paint the back of object when rotating*/

	glDisable(GL_CULL_FACE);

	_perspectiveProjectionMatrix = mat4::identity();

	return;

CLEAN_LOCAL_ALLOCATION_BELOW:
	UnInitialize();

}

void Sanket::Fonts::Update()
{
	_angle = _angle + 0.3f;

	if (_angle >= 360.0f)
		_angle = _angle - 360.0f;

	_shadersDist += 0.05f;
	_presentDist += 0.08f;
	_T2TerminalDist += 0.08f;
	_PoweredByDist += 0.08f;
	_AstromedicompDist += 0.08f;
}

void Sanket::Fonts::ReSize(int width, int height, struct ResizeAttributes attributes)
{
	if (height == 0)
		height = 1;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	_perspectiveProjectionMatrix = vmath::perspective(45.0f, (GLfloat)width / (GLfloat)height, attributes.nearValue, attributes.farValue);

}

void Sanket::Fonts::Render(HDC hdc, struct Attributes attributes)
{
	mat4 modelMatrix = mat4::identity();
	mat4 viewMatrix = mat4::identity();
	mat4 rotateMatrix = mat4::identity();
	mat4 translateMatrix = mat4::identity();

	static GLfloat lightAmbient[] = { 1.0f,1.0f,1.0f,1.0f };
	static GLfloat lightDiffuse[] = { 0.0f,1.0f,0.0f,1.0f };
	static GLfloat lightSpecular[] = { 0.0f,1.0f,0.0f,1.0f };
	static GLfloat lightPosition[] = { 0.0f,0.0f,100.0f,1.0f };
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
	mat4 globalTMatrix = translate(0.0f, 0.0f, 0.0f);
	translateMatrix = translate(0.6f,0.0f, _shadersDist) * globalTMatrix;
	modelMatrix = modelMatrix * translateMatrix;

	rotateMatrix = rotate(0.0f, 280.0f, 0.0f);
	modelMatrix = modelMatrix * rotateMatrix;

	glUniformMatrix4fv(_modelMatrixUniform, 1, GL_FALSE, modelMatrix);
	glUniformMatrix4fv(_ViewMatrixUniform, 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(_projectMatrixUniform, 1, GL_FALSE, _perspectiveProjectionMatrix);

	CHECK_NULL(_modelParserShaders);
	_modelParserShaders->draw();

	 modelMatrix = mat4::identity();
	 viewMatrix = mat4::identity();
	 rotateMatrix = mat4::identity();
	 translateMatrix = mat4::identity();

	translateMatrix = translate(0.6f, 0.0f, _presentDist) * globalTMatrix;
	modelMatrix = modelMatrix * translateMatrix;

	rotateMatrix = rotate(0.0f, 280.0f, 0.0f);
	modelMatrix = modelMatrix * rotateMatrix;

	glUniformMatrix4fv(_modelMatrixUniform, 1, GL_FALSE, modelMatrix);
	glUniformMatrix4fv(_ViewMatrixUniform, 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(_projectMatrixUniform, 1, GL_FALSE, _perspectiveProjectionMatrix);

	CHECK_NULL(_modelParserPresent);
	_modelParserPresent->draw();

	 modelMatrix = mat4::identity();
	 viewMatrix = mat4::identity();
	 rotateMatrix = mat4::identity();
	 translateMatrix = mat4::identity();

	translateMatrix = translate(0.6f, 0.0f, _T2TerminalDist) * globalTMatrix;
	modelMatrix = modelMatrix * translateMatrix;

	rotateMatrix = rotate(0.0f, 280.0f, 0.0f);
	modelMatrix = modelMatrix * rotateMatrix;

	glUniformMatrix4fv(_modelMatrixUniform, 1, GL_FALSE, modelMatrix);
	glUniformMatrix4fv(_ViewMatrixUniform, 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(_projectMatrixUniform, 1, GL_FALSE, _perspectiveProjectionMatrix);

	CHECK_NULL(_modelParserT2Terminal);
	_modelParserT2Terminal->draw();

	 modelMatrix = mat4::identity();
	 viewMatrix = mat4::identity();
	 rotateMatrix = mat4::identity();
	 translateMatrix = mat4::identity();

	translateMatrix = translate(0.6f, 0.0f, _PoweredByDist) * globalTMatrix;
	modelMatrix = modelMatrix * translateMatrix;

	rotateMatrix = rotate(0.0f, 280.0f, 0.0f);
	modelMatrix = modelMatrix * rotateMatrix;

	glUniformMatrix4fv(_modelMatrixUniform, 1, GL_FALSE, modelMatrix);
	glUniformMatrix4fv(_ViewMatrixUniform, 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(_projectMatrixUniform, 1, GL_FALSE, _perspectiveProjectionMatrix);

	CHECK_NULL(_modelParserPoweredBy);
	_modelParserPoweredBy->draw();

	 modelMatrix = mat4::identity();
	 viewMatrix = mat4::identity();
	 rotateMatrix = mat4::identity();
	 translateMatrix = mat4::identity();

	translateMatrix = translate(0.6f, 0.0f, _AstromedicompDist) * globalTMatrix ;
	modelMatrix = modelMatrix * translateMatrix;

	rotateMatrix = rotate(0.0f, 280.0f, 0.0f);
	modelMatrix = modelMatrix * rotateMatrix;

	glUniformMatrix4fv(_modelMatrixUniform, 1, GL_FALSE, modelMatrix);
	glUniformMatrix4fv(_ViewMatrixUniform, 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(_projectMatrixUniform, 1, GL_FALSE, _perspectiveProjectionMatrix);

	CHECK_NULL(_modelParserAstromedicomp);
	_modelParserAstromedicomp->draw();

	//STOP USING SHADER
	glUseProgram(0);

	return;


CLEAN_LOCAL_ALLOCATION_BELOW:
	UnInitialize();
}

void Sanket::Fonts::SceneTransition()
{
}

void Sanket::Fonts::UnInitialize()
{
	//SAFE_DELETE(_modelParser);

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
