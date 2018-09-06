#include "TerminalGlass.h"


Rushabh::TerminalGlass::TerminalGlass()
{
	angle = 0.0f;
	quadWidth[0] = 627.609253f;
	quadHeight[0] = 36.199402f;

	quadWidth[1] = 189.634139f;
	quadHeight[1] = 36.199421f;

	quadWidth[2] = 194.100614f;
	quadHeight[2] = 366.1994f;

	translateCoords[0][0] = 0.0f;
	translateCoords[0][1] = 0.0f;
	translateCoords[0][2] = 0.0f;

	translateCoords[1][0] = 0.0f;
	translateCoords[1][1] = 0.0f;
	translateCoords[1][2] = 0.0f;

	translateCoords[2][0] = 0.0f;
	translateCoords[2][1] = 0.0f;
	translateCoords[2][2] = 0.0f;


}

Rushabh::TerminalGlass::~TerminalGlass()
{
	UnInitialize();
}

BOOL Rushabh::TerminalGlass::SceneHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	return 0;
}

void Rushabh::TerminalGlass::Initialize()
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
		"void main(void)" \
		"{" \
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

				SAFE_LOG("TerminalGlass Vertex Shader Compilation Log : %s\n", szInfoLog)
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
		"uniform vec3 color;"
		"out vec4 FragColor;" \
		"void main(void)" \
		"{" \
		"FragColor = vec4(color,0.5);" \
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

				SAFE_LOG("TerminalGlass Fragment Shader Compilation Log : %s\n", szInfoLog)
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

				SAFE_LOG("TerminalGlass Shader Program Link Log : %s \n", szInfoLog)
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
	_ColorUniform = glGetUniformLocation(_shaderProgramObject, "color");

	// LIGHT POSITION TOKEN
	_LightPositionUniform = glGetUniformLocation(_shaderProgramObject, "u_light_position");


	//SHINYNESS COLOR TOKEN
	material_shininess_uniform = glGetUniformLocation(_shaderProgramObject, "u_material_shininess");;

	const GLfloat TerminalGlassNormals[] =
	{
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
	};

	
	const GLfloat TerminalGlassVertices[]
	{
		-306.350494f, 3.204212f, 104.097000f,
		321.258759f, 3.204212f, 104.097000f,
		321.258759f, 39.403614f, 104.097000f,
		-306.350494f, 39.403614f, 104.097000f,
		-315.846130f, 3.093319f, 70.996063f,
		-126.211891f, 3.093319f, -190.013062f,
		-126.211891f, 39.292740f, -190.013062f,
		-315.846130f, 39.292740f, 70.996063f,
		133.628693f, 3.271151f, -188.338379f,
		327.789307f, 3.271151f, 69.321381f,
		327.789307f, 39.470551f, 69.321381f,
		133.628693f, 39.470551f, -188.338379f,

	};

	glGenVertexArrays(1, &vao[0]);

	glBindVertexArray(vao[0]);

	glGenBuffers(1, &vbo_position);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_position);
	glBufferData(GL_ARRAY_BUFFER, sizeof(TerminalGlassVertices), TerminalGlassVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(AMC_ATTRIBUTE_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_VERTEX);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &vbo_normal);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_normal);
	glBufferData(GL_ARRAY_BUFFER, sizeof(TerminalGlassNormals), TerminalGlassNormals, GL_STATIC_DRAW);
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

void Rushabh::TerminalGlass::Update()
{
	angle += 0.3f;
	if (angle > 360)
		angle = 0.0f;

}

void Rushabh::TerminalGlass::ReSize(int width, int height, struct ResizeAttributes attributes)
{
	if (height == 0)
		height = 1;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	_perspectiveProjectionMatrix = vmath::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, attributes.farValue);
}

void Rushabh::TerminalGlass::Render(HDC hdc, struct Attributes attributes)
{
	mat4 modelMatrix = mat4::identity();
	mat4 viewMatrix = mat4::identity();
	mat4 rotateMatrix = mat4::identity();

	static GLfloat lightAmbient[] = { 0.0f,0.0f,0.0f,1.0f };
	static GLfloat lightDiffuse[] = { 1.0f,1.0f,1.0f,1.0f };
	static GLfloat lightSpecular[] = { 1.0f,1.0f,1.0f,1.0f };
	static GLfloat lightPosition[] = { 100.0f,100.0f,100.0f,1.0f };
	static GLfloat materialQuadAmbient[] = { 1.0f,0.0f,0.0f,1.0f };
	static GLfloat materialQuadDiffuse[] = { 1.0f,0.0f,0.0f,1.0f };
	static GLfloat materialQuadSpecular[] = { 1.0f,0.0f,0.0f,1.0f };

	static GLfloat materialFrameAmbient[] = { 0.0f,1.0f,0.0f,1.0f };
	static GLfloat materialFrameDiffuse[] = { 0.0f,1.0f,0.0f,1.0f };
	static GLfloat materialFrameSpecular[] = { 0.0f,1.0f,0.0f,1.0f };
	static GLfloat glassColor[] = { 0.8f,0.8f,0.0f,1.0f };
	static GLfloat lineColor[] = { 0.0f,0.0f,0.0f,1.0f };

	static GLfloat material_shininess = 50.0f;

	//START USING SHADER OBJECT	
	glUseProgram(_shaderProgramObject);

	// setting light's properties
	glUniform3fv(_LaUniform, 1, lightAmbient);
	glUniform3fv(_LdUniform, 1, lightDiffuse);
	glUniform3fv(_LsUniform, 1, lightSpecular);
	glUniform4fv(_LightPositionUniform, 1, lightPosition);
	glUniform3fv(_KaUniform, 1, materialQuadAmbient);
	glUniform3fv(_KdUniform, 1, materialQuadDiffuse);
	glUniform3fv(_KsUniform, 1, materialQuadSpecular);
	glUniform3fv(_ColorUniform, 1, glassColor);

	//material shininess
	glUniform1f(material_shininess_uniform, material_shininess);

	modelMatrix = translate(
		attributes.translateCoords[SCENE_AIRPORT][0] + translateCoords[0][0],
		attributes.translateCoords[SCENE_AIRPORT][1] + translateCoords[0][1],
		attributes.translateCoords[SCENE_AIRPORT][2] + translateCoords[0][2]);
	rotateMatrix = rotate(
		90.0f + attributes.rotateCoords[SCENE_AIRPORT][0],
		0.0f + attributes.rotateCoords[SCENE_AIRPORT][1],
		0.0f + attributes.rotateCoords[SCENE_AIRPORT][2]);
	modelMatrix = modelMatrix * rotateMatrix;

	glUniformMatrix4fv(_modelMatrixUniform, 1, GL_FALSE, modelMatrix);
	glUniformMatrix4fv(_ViewMatrixUniform, 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(_projectMatrixUniform, 1, GL_FALSE, _perspectiveProjectionMatrix);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindVertexArray(vao[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 4, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);
	glBindVertexArray(0);

	glDisable(GL_BLEND);

	glUniform3fv(_KaUniform, 1, materialFrameAmbient);
	glUniform3fv(_KdUniform, 1, materialFrameDiffuse);
	glUniform3fv(_KsUniform, 1, materialFrameSpecular);
	for(int i = 0 ;i<2 ;i++)
	{
		float increment = quadHeight[i] / 5;
		for (float y = quadHeight[i]; y > 0.0f; y -= increment)
		{
			modelMatrix = mat4::identity();
			viewMatrix = mat4::identity();
			
			modelMatrix = translate(
				attributes.translateCoords[SCENE_AIRPORT][0] + translateCoords[0][0],
				attributes.translateCoords[SCENE_AIRPORT][1] + translateCoords[0][1] + y,
				attributes.translateCoords[SCENE_AIRPORT][2] + translateCoords[0][2]);
			modelMatrix = modelMatrix * rotateMatrix;

			glUniformMatrix4fv(_modelMatrixUniform, 1, GL_FALSE, modelMatrix);
			glUniformMatrix4fv(_ViewMatrixUniform, 1, GL_FALSE, viewMatrix);
			glUniformMatrix4fv(_projectMatrixUniform, 1, GL_FALSE, _perspectiveProjectionMatrix);
			glUniform3fv(_ColorUniform, 1, lineColor);

			glBindVertexArray(vao[0]);
			glDrawArrays(GL_LINES, 0, 2);
			glBindVertexArray(0);
		}

		increment = quadWidth[i] / 20;
		for (float x = 0.0f; x < quadWidth[i]; x += increment)
		{
			modelMatrix = mat4::identity();
			viewMatrix = mat4::identity();

			modelMatrix = translate(
				attributes.translateCoords[SCENE_AIRPORT][0] + translateCoords[0][0] + x,
				attributes.translateCoords[SCENE_AIRPORT][1] + translateCoords[0][1],
				attributes.translateCoords[SCENE_AIRPORT][2] + translateCoords[0][2]);
				rotateMatrix = rotate(90.0f, 1.0f, 0.0f, 0.0f);
			modelMatrix = modelMatrix * rotateMatrix;

			glUniformMatrix4fv(_modelMatrixUniform, 1, GL_FALSE, modelMatrix);
			glUniformMatrix4fv(_ViewMatrixUniform, 1, GL_FALSE, viewMatrix);
			glUniformMatrix4fv(_projectMatrixUniform, 1, GL_FALSE, _perspectiveProjectionMatrix);
			glUniform3fv(_ColorUniform, 1, lineColor);


			glBindVertexArray(vao[0]);
			glDrawArrays(GL_LINES, 1, 2);
			glBindVertexArray(0);
		}


		//STOP USING SHADER
		glUseProgram(0);
	}
}

void Rushabh::TerminalGlass::SceneTransition()
{
}

void Rushabh::TerminalGlass::UnInitialize()
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
