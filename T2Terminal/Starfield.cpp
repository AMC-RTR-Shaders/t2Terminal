
/*
* @author: Sanket Deshmukh
* @mailto: 1sanketdeshmukh@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/

#include "Starfield.h"

Sanket::Starfield::Starfield()
{
	
}

Sanket::Starfield::~Starfield()
{
	UnInitialize();
}

float Sanket::Starfield::random_float(void)
{
	float res;
	unsigned int tmp;

	_seed *= 16807;

	tmp = _seed ^ (_seed >> 4) ^ (_seed << 15);

	*((unsigned int *)&res) = (tmp >> 9) | 0x3F800000;

	return (res - 1.0f);
}

BOOL Sanket::Starfield::SceneHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	return 0;
}

void Sanket::Starfield::Initialize()
{
	
	SAFE_LOG("Starfield shading language supported version is : %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION))

		//CREAT VERTEXT SHADER OBJECT
		_vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

	//CREATE SOURCE CODE FOR VERTEX SHADER OBJECT
	const GLchar *vertexShaderSourcecode =

		"#version 400 core" \
		"\n" \
		"in vec4 vPosition;" \
		"in vec4 color;" \
		"out vec4 starColor ;" \
		"uniform mat4 u_mvp_matrix;" \
		"uniform float time;" \
		"void main(void)" \
		"{" \
		"vec4 newVertex = vPosition;" \
		" newVertex.z += time ;" \
		" newVertex.z = fract(newVertex.z);" \
		" float size = (7.0 * newVertex.z * newVertex.z);" \
		" starColor = smoothstep(1.0,7.0,size) * color;"\
		" newVertex.z = (99.9 * newVertex.z) - 100.0 ;" \
		"gl_Position = u_mvp_matrix * newVertex;" \
		"gl_PointSize = size ; " \
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
				SAFE_LOG("Starfield Vertex Shader Compilation Log : %s\n", szInfoLog)
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

		"#version 400 core" \
		"\n" \
		"in vec4 starColor;" \
		"out vec4 FragColor;" \
		"void main(void)" \
		"{" \
		"FragColor = starColor;"\
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

				SAFE_LOG("Starfield Fragment Shader Compilation Log : %s\n", szInfoLog)
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

	glBindAttribLocation(_shaderProgramObject, AMC_ATTRIBUTE_COLOR, "color");



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

				SAFE_LOG("Starfield Shader Program Link Log : %s \n", szInfoLog)
					SAFE_FREE(szInfoLog);
				UnInitialize();
				exit(0);
			}

		}
	}


	_MVPUniform = glGetUniformLocation(_shaderProgramObject, "u_mvp_matrix");

	_TimeUniform = glGetUniformLocation(_shaderProgramObject, "time");

	/// *** vertices , colors , shader attribs , vbo ,vao initializations *** ///


	// For particle system

	float starPositions[6000];

	for (int i = 0; i < 6000; i++)
	{
		starPositions[i] = (random_float() * 2.0f - 1.0f) * 10.0f;
		starPositions[i + 1] = (random_float() * 2.0f - 1.0f) * 10.0f;
		starPositions[i + 2] = random_float();
		i = i + 3;
	}


	float starColors[6000];

	for (int i = 0; i < 6000; i++)
	{

		starColors[i] = 0.0f;
		starColors[i + 1] = 1.0f;
		starColors[i + 2] = 0.0f;

		i = i + 3;

	}


	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo_Position);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_Position);
	glBufferData(GL_ARRAY_BUFFER, sizeof(starPositions), starPositions, GL_STATIC_DRAW);

	glVertexAttribPointer(AMC_ATTRIBUTE_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_VERTEX);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//// vbo for texture 

	glGenBuffers(1, &vbo_Color);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_Color);
	glBufferData(GL_ARRAY_BUFFER, sizeof(starColors), starColors, GL_STATIC_DRAW);

	glVertexAttribPointer(AMC_ATTRIBUTE_COLOR, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_COLOR);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);


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

void Sanket::Starfield::Update()
{

}

void Sanket::Starfield::ReSize(int width, int height, struct ResizeAttributes attributes)
{
	if (height == 0)
		height = 1;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	_perspectiveProjectionMatrix = vmath::perspective(45.0f, (GLfloat)width / (GLfloat)height, attributes.nearValue, attributes.farValue);

}

void Sanket::Starfield::Render(HDC hdc, struct Attributes attributes)
{
	GetSystemTime(&_systemTime);


	float t = (float)_systemTime.wMilliseconds;


	mat4 modelViewMatrix;
	mat4 modelViewProjectionMatrix;

	modelViewMatrix = mat4::identity();

	modelViewProjectionMatrix = _perspectiveProjectionMatrix * modelViewMatrix;


	//START USING SHADER OBJECT	
	glUseProgram(_shaderProgramObject);

	glUniformMatrix4fv(_MVPUniform, 1, GL_FALSE, modelViewProjectionMatrix);

	t *= 0.001f;
	t -= floor(t);

	glUniform1f(_TimeUniform, t);

	glBindVertexArray(vao);

	glEnable(GL_PROGRAM_POINT_SIZE);

	glDrawArrays(GL_POINTS, 0, NUM_STARS);

	glBindVertexArray(0);

	
	//STOP USING SHADER
	glUseProgram(0);

	return;


CLEAN_LOCAL_ALLOCATION_BELOW:
	UnInitialize();
}

void Sanket::Starfield::SceneTransition()
{
}

void Sanket::Starfield::UnInitialize()
{
	
	if (vao)
	{
		glDeleteVertexArrays(1, &vao);
		vao = 0;
	}

	if (vbo_Position)
	{
		glDeleteBuffers(1, &vbo_Position);
		vbo_Position = 0;
	}

	if (vbo_Color)
	{
		glDeleteBuffers(1, &vbo_Color);
		vbo_Color = 0;
	}


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




