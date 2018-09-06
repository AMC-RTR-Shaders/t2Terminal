
/*
* @author: Priyanka Bhasme
* @mailto: pribhasme@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/

#include "Cubemap.h"

Priyanka::Cubemap::Cubemap()
{
	//
}

Priyanka::Cubemap::~Cubemap()
{
	UnInitialize();
}

BOOL Priyanka::Cubemap::SceneHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	return 0;
}

void Priyanka::Cubemap::Initialize()
{
	SAFE_LOG("Cubemap shading language supported verison is : %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION))

	//CREAT VERTEXT SHADER OBJECT
	_vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

	//CREATE SOURCE CODE FOR VERTEX SHADER OBJECT
	const GLchar *vertexShaderSourcecode =
		"#version 330" \
		"\n" \
		"in vec3 vPosition;" \
		"out vec3 out_texture0_coord;" \
		"uniform mat4 u_model_matrix;" \
		"uniform mat4 u_projection_matrix;" \
		"uniform mat4 u_view_matrix;" \
		"void main(void)" \
		"{" \
		"gl_Position = u_projection_matrix * u_view_matrix * u_model_matrix * vec4(vPosition, 1.0);" \
		"out_texture0_coord = vPosition;" \
		"}";

	//BIND vertexShaderSourcecode CODE TO gVertexShaderObject
	glShaderSource(_vertexShaderObject, 1, (const GLchar **)&vertexShaderSourcecode, NULL);

	//COMPILE VERTEX SHADER
	glCompileShader(_vertexShaderObject);


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
				SAFE_LOG("Cubemap Vertex Shader Compilation Log : %s\n", szInfoLog)
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
		"#version 330" \
		"\n" \
		"out vec4 FragColor;" \
		"in vec3 out_texture0_coord;" \
		"uniform samplerCube u_texture0_sampler;" \
		"void main(void)" \
		"{" \
		"FragColor = texture(u_texture0_sampler, out_texture0_coord);" \
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

				SAFE_LOG("Cubemap Fragment Shader Compilation Log : %s\n", szInfoLog)
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

				SAFE_LOG("Cubemap Shader Program Link Log : %s \n", szInfoLog)
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
	_textureSamplerUniform = glGetUniformLocation(_shaderProgramObject, "u_texture0_sampler");

	const GLfloat cubeVertices[] =
	{
		-SIZE,  SIZE, -SIZE, // back
		-SIZE, -0, -SIZE,
		SIZE, -0, -SIZE,
		SIZE, -0, -SIZE,
		SIZE,  SIZE, -SIZE,
		-SIZE,  SIZE, -SIZE,

		-SIZE, -0,  SIZE,  // left
		-SIZE, -0, -SIZE,
		-SIZE,  SIZE, -SIZE,
		-SIZE,  SIZE, -SIZE,
		-SIZE,  SIZE,  SIZE,
		-SIZE, -0,  SIZE,

		SIZE, -0, -SIZE, // right
		SIZE, -0,  SIZE,
		SIZE,  SIZE,  SIZE,
		SIZE,  SIZE,  SIZE,
		SIZE,  SIZE, -SIZE,
		SIZE, -SIZE, -SIZE,

		-SIZE, -0,  SIZE, // front
		-SIZE,  SIZE,  SIZE,
		SIZE,  SIZE,  SIZE,
		SIZE,  SIZE,  SIZE,
		SIZE, -0,  SIZE,
		-SIZE, -0,  SIZE,

		-SIZE,  SIZE, -SIZE,  //top
		SIZE,  SIZE, -SIZE,
		SIZE,  SIZE,  SIZE,
		SIZE,  SIZE,  SIZE,
		-SIZE,  SIZE,  SIZE,
		-SIZE,  SIZE, -SIZE,

		-SIZE, -0, -SIZE, // bottom
		-SIZE, -0,  SIZE,
		SIZE, -0, -SIZE,
		SIZE, -0, -SIZE,
		-SIZE, -0,  SIZE,
		SIZE, -0, SIZE
	};

	// FOR CUBE
	glGenVertexArrays(1, &_vaoCube);
	glBindVertexArray(_vaoCube);

	// FOR CUBE POSITION
	glGenBuffers(1, &_vboCubePos);
	glBindBuffer(GL_ARRAY_BUFFER, _vboCubePos);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(AMC_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(AMC_ATTRIBUTE_POSITION);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glEnable(GL_TEXTURE_2D);
	// LOAD CUBEMAP TEXTURE
	LoadGLTexturesCubemap(&_textureCubemap, IDBITMAP_POSX);

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

void Priyanka::Cubemap::Update()
{
	//
}

void Priyanka::Cubemap::ReSize(int width, int height, struct ResizeAttributes attributes)
{
	if (height == 0)
		height = 1;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	_perspectiveProjectionMatrix = vmath::perspective(45.0f, (GLfloat)width / (GLfloat)height, attributes.nearValue, attributes.farValue);

}

void Priyanka::Cubemap::Render(HDC hdc, struct Attributes attributes)
{
	mat4 modelMatrix = mat4::identity();
	mat4 viewMatrix = mat4::identity();
	mat4 rotateMatrix = mat4::identity();
	mat4 translateMatrix = mat4::identity();
//	if (attributes.currentScene == SCENE_AIRPORT || attributes.currentScene == SCENE_MASTER)
	{
		translateMatrix = translate(
			attributes.translateCoords[SCENE_AIRPORT][0], 
			attributes.translateCoords[SCENE_AIRPORT][1], 
			attributes.translateCoords[SCENE_AIRPORT][2]);
		rotateMatrix = rotate(
			attributes.rotateCoords[SCENE_AIRPORT][0], 
			attributes.rotateCoords[SCENE_AIRPORT][1], 
			attributes.rotateCoords[SCENE_AIRPORT][2]);
	}
	modelMatrix = translateMatrix * rotateMatrix;

	// NO NEED TO TRANSLATE CUBEMAP
	// WE NULLIFY TRANSLATE CO-ORDINATES AND MAKE ZERO HERE
	// THIS WAY, CAMERA MOVEMENT WONT AFFECT THE CUBEMAP. IT WILL NEVER REACH THE EDGES OF CUBEMAP
	viewMatrix[3][0] = 0.0f;
	viewMatrix[3][1] = 0.0f;
	viewMatrix[3][2] = 0.0f;

	glUseProgram(_shaderProgramObject);

	glUniformMatrix4fv(_modelMatrixUniform, 1, GL_FALSE, modelMatrix);
	glUniformMatrix4fv(_ViewMatrixUniform, 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(_projectMatrixUniform, 1, GL_FALSE, _perspectiveProjectionMatrix);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _textureCubemap);
	glUniform1i(_textureSamplerUniform, 0);

	//draw cube
	glBindVertexArray(_vaoCube);
	glDrawArrays(GL_TRIANGLES, 0, 36); // 3 (each with its x,y,z )

	glBindVertexArray(0);

	glUseProgram(0);

	return;


CLEAN_LOCAL_ALLOCATION_BELOW:
	UnInitialize();
}

void Priyanka::Cubemap::SceneTransition()
{
}

void Priyanka::Cubemap::UnInitialize()
{
	
	_vaoCube = 0;
	_vboCubePos = 0;

	_textureSamplerUniform = 0;
	_textureCubemap = 0;

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

int Priyanka::Cubemap::LoadGLTexturesCubemap(GLuint *texture, int resArrayPtr)
{
	// variable declarations

	BITMAP bmp;
	int iStatus = FALSE;
	// code
	glGenTextures(1, texture);// 1 image
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, *texture);// bind texture

	for (int i = 0; i < 6; i++)
	{
		_hBitmap[i] = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(resArrayPtr + i), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
		if (_hBitmap[i])// if bitmap exists ( means hBitmap is not null )
		{
			iStatus = TRUE;
			GetObject(_hBitmap[i], sizeof(bmp), &bmp);

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0,
				GL_RGB,
				bmp.bmWidth,
				bmp.bmHeight,
				0,
				GL_BGR,
				GL_UNSIGNED_BYTE,
				bmp.bmBits);

		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	return(iStatus);
}
