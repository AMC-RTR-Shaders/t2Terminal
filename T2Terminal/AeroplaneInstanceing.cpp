#include "AeroplaneInstanceing.h"

Harsh::AeroplaneInstanceing::AeroplaneInstanceing()
{
	_modelParser = new ModelParser("3DModels\\Chair\\chair.obj");
	CHECK_NULL(_modelParser);

	return;
CLEAN_LOCAL_ALLOCATION_BELOW:
	UnInitialize();

}

Harsh::AeroplaneInstanceing::~AeroplaneInstanceing()
{
	UnInitialize();
}



void Harsh::AeroplaneInstanceing::Initialize()
{
	SAFE_LOG("AeroplaneInstanceing shading language supported verison is : %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION))

	//CREAT VERTEXT SHADER OBJECT
	_vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

	//CREATE SOURCE CODE FOR VERTEX SHADER OBJECT
	const GLchar *vertexShaderSourcecode =
		"#version 430 core" \
		"\n" \
		"in vec4 vPosition;" \
		"in vec3 vNormal;" \
		"in vec4 instance_position;"\
		"in vec3 instance_rotation;"\
		"uniform mat4 u_model_matrix;" \
		"uniform mat4 u_view_matrix;" \
		"uniform mat4 u_projection_matrix;" \
		"uniform vec3 u_La;" \
		"uniform vec3 u_Ld;" \
		"uniform vec3 u_Ls;"\
		"uniform vec3 u_Ka;" \
		"uniform vec3 u_Kd;" \
		"uniform vec3 u_Ks;" \
		"uniform vec4 u_light_position;" \
		"uniform float u_material_shininess;" \
		"out vec3 out_color;"
		
		"mat4 construct_rotation_matrix(float angle_x,float angle_y,float angle_z)"\
		"{"\
			"angle_x = (angle_x * (3.1415 / 180.0));"\
			"angle_y = (angle_y * (3.1415 / 180.0));"\
			"angle_z = (angle_z * (3.1415 / 180.0));"\
			"float stx = sin(angle_x);"\
			"float ctx = cos(angle_x);"\
			"float sty = sin(angle_y);"\
			"float cty = cos(angle_y);"\
			"float stz = sin(angle_z);"\
			"float ctz = cos(angle_z);"\
			"return mat4(vec4(cty*ctz, -(cty*stz), sty, 0.0),"\
			"vec4(((ctx*stz)+(stx*sty*ctz)), ((ctx*ctz)-(stx*sty*stz)), -(stx*cty), 0.0),"\
			"vec4(((stx*stz)-(ctx*sty*ctz)), ((stx*ctz)+(ctx*sty*stz)), (ctx*cty), 0.0),"\
			"vec4(0.0, 0.0, 0.0, 1.0));"\
		"}"\

		"mat4 construct_translation_matrix(float tx,float ty,float tz)"\
		"{"\
			"return mat4(vec4(1.0, 0.0, 0.0, tx),"\
			"vec4(0.0, 1.0, 0.0, ty),"\
			"vec4(0.0, 0.0, 1.0, tz),"\
			"vec4(0.0, 0.0, 0.0, 1.0));"\
		"}"\

		"void main (void)" \
		"{" \
			"mat4 rot = construct_rotation_matrix(instance_rotation.x,instance_rotation.y,instance_rotation.z);"\
			"mat4 trans = construct_translation_matrix(instance_position.x,instance_position.y,instance_position.z);"\
			"gl_Position = u_projection_matrix * (u_view_matrix *  (u_model_matrix * ((vPosition) * rot) * trans));" \
			
			"vec4 eye_coordinates=u_view_matrix * u_model_matrix * vPosition;" \
			"vec3 transformed_normals=normalize(mat3(u_view_matrix * u_model_matrix) * vNormal);" \
			"vec3 light_direction = normalize(vec3(u_light_position) - eye_coordinates.xyz);" \
			"float tn_dot_ld = max(dot(transformed_normals, light_direction),0.0);" \
			"vec3 ambient = u_La * u_Ka;" \
			"vec3 diffuse = u_Ld * u_Kd * tn_dot_ld;" \
			"vec3 reflection_vector = reflect(-light_direction, transformed_normals);" \
			"vec3 viewer_vector = normalize(-eye_coordinates.xyz);" \
			"vec3 specular = u_Ls * u_Ks * pow(max(dot(reflection_vector, viewer_vector), 0.0), u_material_shininess);" \
			"out_color=ambient + diffuse + specular;" \
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

				SAFE_LOG("Aeroplane Instancing Vertex Shader Compilation Log : %s\n", szInfoLog)
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
		"#version 430 core" \
		"\n" \
		"in vec3 out_color;"\
		"out vec4 FragColor;" \
		"void main (void)" \
		"{" \
			"FragColor = vec4(out_color, 1.0);" \
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

				SAFE_LOG("Aeroplane Instancing Fragment Shader Compilation Log : %s\n", szInfoLog)
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
	glBindAttribLocation(_shaderProgramObject, AMC_ATTRIBUTE_POSITION, "instance_position");
	//PRE-LINK BINDING OF SHADER PROGRAM OBJECT WITTH TEXTURE SHADER ATTRIBUTE
	glBindAttribLocation(_shaderProgramObject, AMC_ATTRIBUTE_ROTATION, "instance_rotation");

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
				SAFE_LOG("Aeroplane Instancing Shader Program Link Log : %s \n", szInfoLog)
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
	material_shininess_uniform = glGetUniformLocation(_shaderProgramObject, "u_material_shininess");;

	//

	//LOAD THE MODEL HERE
	const GLfloat aeroplanePosition[] =
	{
		-7.0f, -1.0f, 0.0f,
		-4.0f, -1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		2.0f, -1.0f, 0.0f,
		6.0f, -1.0f, 0.0f,
	};

	const GLfloat aeroplaneRotation[] =
	{
		0.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f
	};

	CHECK_NULL(_modelParser);
	GLOBJECT_INSTANCEING *instancing = (GLOBJECT_INSTANCEING*)malloc(sizeof(GLOBJECT_INSTANCEING));
	instancing->instancingQuery = INSTANCING_QUERY::YES;

	instancing->isPostion = true;
	instancing->positionArray = aeroplanePosition;
	instancing->countOfPosition = sizeof(aeroplanePosition);
	instancing->position_attriDivisorCount = 1;

	instancing->isRotation = true;
	instancing->rotationArray = aeroplaneRotation;
	instancing->countOfRotation = sizeof(aeroplanePosition);
	instancing->rotation_attriDivisorCount = 1;

	instancing->numberOfInstance = 5;
	

	_modelParser->parse(_shaderProgramObject, ThreeDModelLoader::PROCESS_TYPE::CPU, ThreeDModelLoader::DRAW_TYPE::DRAW_USING_ARRAYS, instancing);


	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);

	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LEQUAL);

	glShadeModel(GL_SMOOTH);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_CULL_FACE); /*Turning oFF cull , as we are doing animation , and so need to paint the back of object when rotating*/

	_perspectiveProjectionMatrix = mat4::identity();

	return;

CLEAN_LOCAL_ALLOCATION_BELOW:
	UnInitialize();
}

BOOL Harsh::AeroplaneInstanceing::SceneHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	return 0;
}



void Harsh::AeroplaneInstanceing::Update()
{
}

void Harsh::AeroplaneInstanceing::ReSize(int width, int height)
{
	if (height == 0)
		height = 1;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	_perspectiveProjectionMatrix = vmath::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
}

void Harsh::AeroplaneInstanceing::Render(HDC hdc)
{
	mat4 modelMatrix = mat4::identity();
	mat4 viewMatrix = mat4::identity();
	mat4 rotateMatrix = mat4::identity();
	mat4 scaleMatrix = mat4::identity();

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

	modelMatrix = translate(0.0f, -5.0f, -30.0f);
	scaleMatrix = scale(0.5f, 0.5f, 0.5f);

	modelMatrix = modelMatrix * rotateMatrix;
	modelMatrix = modelMatrix * scaleMatrix;

	glUniformMatrix4fv(_modelMatrixUniform, 1, GL_FALSE, modelMatrix);
	glUniformMatrix4fv(_ViewMatrixUniform, 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(_projectMatrixUniform, 1, GL_FALSE, _perspectiveProjectionMatrix);

	CHECK_NULL(_modelParser);
	_modelParser->draw();

	//STOP USING SHADER
	glUseProgram(0);

	return;


CLEAN_LOCAL_ALLOCATION_BELOW:
	UnInitialize();
}

void Harsh::AeroplaneInstanceing::SceneTransition()
{
}

void Harsh::AeroplaneInstanceing::UnInitialize()
{
	SAFE_DELETE(_modelParser);

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
