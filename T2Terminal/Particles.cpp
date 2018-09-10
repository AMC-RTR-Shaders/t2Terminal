/*
* @author: Rushabh Parakh
* @mailto: rgparakh@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/

#include "Particles.h"

Rushabh::Particles::Particles()
{
	_particleTime = 0.01f;
}

Rushabh::Particles::~Particles()
{
	UnInitialize();
}

BOOL Rushabh::Particles::SceneHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	return 0;
}

void Rushabh::Particles::Initialize()
{

	//CREAT VERTEXT SHADER OBJECT
	_vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

	//CREATE SOURCE CODE FOR VERTEX SHADER OBJECT
	const GLchar *vertexShaderSourcecode =
		"#version 440 core"									\
		"\n"												\
		"uniform float u_time;"								\
		"uniform vec4 u_background;"						\
		"uniform mat4 u_mvp_matrix;"						\
		"in vec4 vPosition;"								\
		"in vec4 vColor;"									\
		"in vec3 vVelocity;"								\
		"in float fStartTime;"								\
		"in float fRadius;"									\
		"out vec4 out_color;"								\
		"void main(void)"									\
		"{"													\
		"vec4 vertice = vPosition;"							\
		"float t = u_time - fStartTime;"					\
		"if(t >= 0)"										\
		"{"													\
		"vertice = vPosition + vec4(vVelocity * t, 0.0);"	\
		"vertice.y -= 4.9 * t * t;"							\
		"out_color = vColor;"								\
		"}"													\
		"else"												\
		"{"													\
		"vertice = vPosition;"								\
		"out_color = vColor;"								\
		"}"													\
		"float distSqr = vertice.x*vertice.x;"\
		"if(distSqr >= fRadius)"					\
		"{"													\
		"out_color = vec4(0.0f, 0.0f, 0.0f, 1.0f);"			\
		"}"													\
		"else"												\
		"{"													\
		"out_color = vColor;"			\
		"}"													\

		"gl_Position = u_mvp_matrix * vertice;"				\
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

				SAFE_LOG("Particles Vertex Shader Compilation Log : %s\n", szInfoLog)
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
		"#version 440 core"		\
		"\n"					\
		"in vec4 out_color;"	\
		"out vec4 FragColor;"	\
		"void main(void)"		\
		"{"						\
		"FragColor = out_color;"\
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

				SAFE_LOG("Particles Fragment Shader Compilation Log : %s\n", szInfoLog)
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
	glBindAttribLocation(_shaderProgramObject, AMC_ATTRIBUTE_POSITION, "vPosition");	
	glBindAttribLocation(_shaderProgramObject, AMC_ATTRIBUTE_COLOR, "vColor");
	glBindAttribLocation(_shaderProgramObject, AMC_ATTRIBUTE_VELOCITY_ARRAY, "vVelocity");
	glBindAttribLocation(_shaderProgramObject, AMC_ATTRIBUTE_START_TIME_ARRAY, "fStartTime");
	glBindAttribLocation(_shaderProgramObject, AMC_ATTRIBUTE_RADIUS, "fRadius");

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

				SAFE_LOG("Particles Shader Program Link Log : %s \n", szInfoLog)
					SAFE_FREE(szInfoLog);
				UnInitialize();
				exit(0);
			}

		}
	}


	//GET MVP UNIFORM LOCATION
	_mVPUniform = glGetUniformLocation(_shaderProgramObject, "u_mvp_matrix");
	_locationUniform = glGetUniformLocation(_shaderProgramObject, "u_time");
	_backgroundUniform = glGetUniformLocation(_shaderProgramObject, "u_background");

	createPoints(PARTICLE_WIDTH, PARTICLE_HEIGHT);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo_position);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_position);
	glBufferData(GL_ARRAY_BUFFER, arrayWidth * arrayHeight * 3 * sizeof(GLfloat), _pVertex, GL_STATIC_DRAW);

	glVertexAttribPointer(AMC_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_POSITION);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &vbo_color);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_color);
	glBufferData(GL_ARRAY_BUFFER, arrayWidth * arrayHeight * 3 * sizeof(GLfloat), _pColor, GL_STATIC_DRAW);

	glVertexAttribPointer(AMC_ATTRIBUTE_COLOR, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_COLOR);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &vbo_color);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_color);
	glBufferData(GL_ARRAY_BUFFER, arrayWidth * arrayHeight * 3 * sizeof(GLfloat), _pVelocity, GL_STATIC_DRAW);

	glVertexAttribPointer(AMC_ATTRIBUTE_VELOCITY_ARRAY, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_VELOCITY_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &vbo_start_time);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_start_time);
	glBufferData(GL_ARRAY_BUFFER, arrayWidth * arrayHeight * sizeof(GLfloat), _pStartTime, GL_STATIC_DRAW);

	glVertexAttribPointer(AMC_ATTRIBUTE_START_TIME_ARRAY, 1, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_START_TIME_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &vbo_radius);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_radius);
	glBufferData(GL_ARRAY_BUFFER, arrayWidth * arrayHeight * sizeof(GLfloat), _pRadius, GL_STATIC_DRAW);

	glVertexAttribPointer(AMC_ATTRIBUTE_RADIUS, 1, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_RADIUS);

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

void Rushabh::Particles::createPoints(GLint w, GLint h)
{
	GLfloat *vptr = NULL, *cptr = NULL, *velptr = NULL, *stptr = NULL, *radptr = NULL;

	int i = 0;
	GLfloat x = 0.0f;
	GLfloat y = 0.0f;
	GLfloat z = 0.0f;
	GLfloat r = 0.0f;
	GLfloat theta = 0.0f;
	GLfloat zInc = 0.0001f / 5;
	_pVertex = (float *)malloc(w * h * 3 * sizeof(float));
	_pColor = (float *)malloc(w * h * 3 * sizeof(float));
	_pVelocity = (float *)malloc(w * h * 3 * sizeof(float));
	_pStartTime = (float *)malloc(w * h * sizeof(float));
	_pRadius = (float *)malloc(w * h * sizeof(float));

	vptr = _pVertex;
	cptr = _pColor;
	velptr = _pVelocity;
	stptr = _pStartTime;
	radptr = _pRadius;

	float xLength = 0.005f;
	float xCurrent = -xLength;
	float yCurrent = 0.0f;
	float XINC = xLength * 2 / 100;
	float YINC = 0.11f;
	float VELOCITY_INC = 1.0f;

	for (i = 0; i < PARTICLE_WIDTH * PARTICLE_HEIGHT; i++)
	{
		x = xCurrent;
		y = yCurrent;
		//z = ((float)i/(PARTICLE_WIDTH*PARTICLE_HEIGHT)) * ((float)i / (PARTICLE_WIDTH*PARTICLE_HEIGHT));
		//z += 0.0004f;
		z = 0.0000f;
		//z += zInc;

		*vptr = x;
		*(vptr + 1) = y;
		*(vptr + 2) = z * 0.0f;
		vptr += 3;

		*radptr = xLength*xLength;

		//theta += SPEED * 200;
		//r += SPEED*2;

		*cptr = 1.0f;
		*(cptr + 1) = 1.0f;
		*(cptr + 2) = 0.5f;
		cptr += 3;

		*velptr = ((float)rand() / RAND_MAX)*VELOCITY_INC;
		if (x > 0)
			*velptr *= -1.0f;

		*(velptr + 1) = ((float)rand() / RAND_MAX)*VELOCITY_INC*-1;
		//if (y > 0)
		//	*(velptr+1) *= -1.0f;

		//		*(velptr + 2) = ((float)rand() / RAND_MAX) + 3.0f * r * (rand()%2 ? 1 : -1);
		*(velptr + 2) = 0.0f;

		velptr += 3;

		//		*stptr = i * SPEED;
		*stptr = 0;

		radptr++;
		stptr++;
		//if (!((i + 1) % 200))
		//{
		//	zInc = zInc + 0.0001f / 5;
		//}

		xCurrent += XINC;
		if ((i + 1) % 100 == 0)
		{
			yCurrent -= YINC;
			xLength = xLength + 0.015f;
			xCurrent = -xLength;
			XINC = xLength * 2 / 100;
			VELOCITY_INC += 0.5f;
		}
	}

	arrayWidth = w;
	arrayHeight = h;
}

void Rushabh::Particles::Update()
{
	_particleTime = _particleTime + SPEED / 50;
}

void Rushabh::Particles::ReSize(int width, int height, struct ResizeAttributes attributes)
{
	if (height == 0)
		height = 1;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	_perspectiveProjectionMatrix = vmath::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 1000.0f);

}

void Rushabh::Particles::Render(HDC hdc, struct Attributes attributes)
{
	//START USING SHADER OBJECT	
	glUseProgram(_shaderProgramObject);

	glUniform1f(_locationUniform, _particleTime);
	glUniform4fv(_backgroundUniform, 1, _backgroundColor);
	glPointSize(1.0f);

	mat4 modelViewMatrix = mat4::identity();
	mat4 modelViewProjectionMatrix = mat4::identity();

	if (attributes.currentSequenceCounter > PARTICLE_LIGHT_1_ON)
	{
		modelViewMatrix = translate(
			attributes.translateCoords[SCENE_AIRPORT_MODEL][0],
			TRANS_Y_PARTICLES + attributes.translateCoords[SCENE_AIRPORT_MODEL][1],
			attributes.translateCoords[SCENE_AIRPORT_MODEL][2] - TRANS_X_PARTICLES);

		modelViewProjectionMatrix = _perspectiveProjectionMatrix * modelViewMatrix;

		modelViewMatrix = rotate(-ROTATE_Z_PARTICLES, 0.0f, 0.0f);

		modelViewProjectionMatrix = modelViewProjectionMatrix * modelViewMatrix;

		glUniformMatrix4fv(_mVPUniform, 1, GL_FALSE, modelViewProjectionMatrix);

		glBindVertexArray(vao);

		glDrawArrays(GL_POINTS, 0, PARTICLE_WIDTH * PARTICLE_HEIGHT);

		glBindVertexArray(0);
	}

	if (attributes.currentSequenceCounter > PARTICLE_LIGHT_2_ON)
	{
		modelViewMatrix = mat4::identity();
		modelViewProjectionMatrix = mat4::identity();

		modelViewMatrix = translate(
			-TRANS_X_PARTICLES + attributes.translateCoords[SCENE_AIRPORT_MODEL][0],
			TRANS_Y_PARTICLES + attributes.translateCoords[SCENE_AIRPORT_MODEL][1],
			attributes.translateCoords[SCENE_AIRPORT_MODEL][2]);

		modelViewProjectionMatrix = _perspectiveProjectionMatrix * modelViewMatrix;

		modelViewMatrix = rotate(0.0f, 0.0f, ROTATE_Z_PARTICLES);

		modelViewProjectionMatrix = modelViewProjectionMatrix * modelViewMatrix;

		glUniformMatrix4fv(_mVPUniform, 1, GL_FALSE, modelViewProjectionMatrix);

		glBindVertexArray(vao);

		glDrawArrays(GL_POINTS, 0, PARTICLE_WIDTH * PARTICLE_HEIGHT);

		glBindVertexArray(0);
	}

	if (attributes.currentSequenceCounter >= PARTICLE_LIGHT_3_ON)
	{

		modelViewMatrix = mat4::identity();
		modelViewProjectionMatrix = mat4::identity();

		modelViewMatrix = translate(
			TRANS_X_PARTICLES + attributes.translateCoords[SCENE_AIRPORT_MODEL][0],
			TRANS_Y_PARTICLES + attributes.translateCoords[SCENE_AIRPORT_MODEL][1],
			attributes.translateCoords[SCENE_AIRPORT_MODEL][2]);

		modelViewProjectionMatrix = _perspectiveProjectionMatrix * modelViewMatrix;

		modelViewMatrix = rotate(0.0f, 0.0f, -ROTATE_Z_PARTICLES);

		modelViewProjectionMatrix = modelViewProjectionMatrix * modelViewMatrix;

		glUniformMatrix4fv(_mVPUniform, 1, GL_FALSE, modelViewProjectionMatrix);

		glBindVertexArray(vao);

		glDrawArrays(GL_POINTS, 0, PARTICLE_WIDTH * PARTICLE_HEIGHT);

		glBindVertexArray(0);
	}


	//STOP USING SHADER
	glUseProgram(0);

}

void Rushabh::Particles::SceneTransition()
{
}

void Rushabh::Particles::UnInitialize()
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
