/*
* @author: Rushabh Parakh
* @mailto: rgparakh@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/

#include "Runway.h"

Rushabh::Runway::Runway()
{
	angle = 0.0f;
}

Rushabh::Runway::~Runway()
{
	UnInitialize();
}

BOOL Rushabh::Runway::SceneHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	return 0;
}

void Rushabh::Runway::Initialize()
{

	//CREAT VERTEXT SHADER OBJECT
	_vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

	//CREATE SOURCE CODE FOR VERTEX SHADER OBJECT
	const GLchar *vertexShaderSourcecode =
		"#version 430" \
		"\n" \
		"in vec4 vPosition;" \
		"in vec3 vNormal;" \
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
		"if(1 == 1)" \
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
		"}" \
		"else" \
		"{" \
		"phong_ads_color = vec3(1.0, 1.0, 1.0);" \
		"}" \

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

				SAFE_LOG("Runway Vertex Shader Compilation Log : %s\n", szInfoLog)
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
		"FragColor = vec4(phong_ads_color, 1.0);" \
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

				SAFE_LOG("Runway Fragment Shader Compilation Log : %s\n", szInfoLog)
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

				SAFE_LOG("Runway Shader Program Link Log : %s \n", szInfoLog)
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

	_KaUniform = glGetUniformLocation(_shaderProgramObject, "u_Ka");
	_KdUniform = glGetUniformLocation(_shaderProgramObject, "u_Kd");
	_KsUniform = glGetUniformLocation(_shaderProgramObject, "u_Ks");

	// LIGHT POSITION TOKEN
	_LightPositionUniform = glGetUniformLocation(_shaderProgramObject, "u_light_position");


	//SHINYNESS COLOR TOKEN
	material_shininess_uniform = glGetUniformLocation(_shaderProgramObject, "u_material_shininess");;

	const GLfloat cubeVertices[] =
	{
		1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,

		1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,

		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,

		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,

		1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,
	};

	const GLfloat cubeNormals[] =
	{
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,

		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,

		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,

		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,

		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f
	};

	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);

	glGenBuffers(1, &vbo_position);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_position);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(AMC_ATTRIBUTE_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_VERTEX);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &vbo_normal);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_normal);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeNormals), cubeNormals, GL_STATIC_DRAW);
	glVertexAttribPointer(AMC_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);


	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
	glClearDepth(1.0f);

	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LEQUAL);

	glShadeModel(GL_SMOOTH);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_CULL_FACE); /*Turning oFF cull , as we are doing animation , and so need to paint the back of object when rotating*/

	_perspectiveProjectionMatrix = mat4::identity();

}

void Rushabh::Runway::Update()
{
	angle += 0.3f;
	if (angle > 360)
		angle = 0.0f;

}

void Rushabh::Runway::ReSize(int width, int height)
{
	if (height == 0)
		height = 1;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	_perspectiveProjectionMatrix = vmath::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

}

void Rushabh::Runway::Render(HDC hdc)
{
	mat4 modelMatrix = mat4::identity();
	mat4 viewMatrix = mat4::identity();
	mat4 rotateMatrix = mat4::identity();

	static GLfloat lightAmbient[] = { 0.0f,0.0f,0.0f,1.0f };
	static GLfloat lightDiffuse[] = { 1.0f,1.0f,1.0f,1.0f };
	static GLfloat lightSpecular[] = { 1.0f,1.0f,1.0f,1.0f };
	static GLfloat lightPosition[] = { 100.0f,100.0f,100.0f,1.0f };
	static GLfloat materialAmbient[] = { 1.0f,1.0f,1.0f,1.0f };
	static GLfloat materialDiffuse[] = { 1.0f,1.0f,1.0f,1.0f };
	static GLfloat materialSpecular[] = { 1.0f,1.0f,1.0f,1.0f };
	
	static GLfloat material_shininess = 50.0f;

	//START USING SHADER OBJECT	
	glUseProgram(_shaderProgramObject);

	// setting light's properties
	glUniform3fv(_LaUniform, 1, lightAmbient);
	glUniform3fv(_LdUniform, 1, lightDiffuse);
	glUniform3fv(_LsUniform, 1, lightSpecular);
	glUniform4fv(_LightPositionUniform, 1, lightPosition);
	glUniform3fv(_KaUniform, 1, materialAmbient);
	glUniform3fv(_KdUniform, 1, materialDiffuse);
	glUniform3fv(_KsUniform, 1, materialSpecular);

	//material shininess
	glUniform1f(material_shininess_uniform, material_shininess);
	//

	modelMatrix = translate(0.0f, 0.0f, -15.0f);
	rotateMatrix = rotate(angle, angle, angle);

	modelMatrix = modelMatrix * rotateMatrix;

	glUniformMatrix4fv(_modelMatrixUniform, 1, GL_FALSE, modelMatrix);
	glUniformMatrix4fv(_ViewMatrixUniform, 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(_projectMatrixUniform, 1, GL_FALSE, _perspectiveProjectionMatrix);

	glBindVertexArray(vao);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 4, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 16, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 20, 4);

	glBindVertexArray(0);


	//STOP USING SHADER
	glUseProgram(0);

}

void Rushabh::Runway::SceneTransition()
{
}

void Rushabh::Runway::UnInitialize()
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
