#include "TerminalGlass.h"


Rushabh::TerminalGlass::TerminalGlass()
{
	angle = 0.0f;
	quadWidth[0] = 300.0f;
	quadHeight[0] = 30.0f;

	quadWidth[1] = 150.0f;
	quadHeight[1] = 30.0f;

	quadWidth[2] = quadWidth[1];
	quadHeight[2] = quadHeight[1];

	translateCoords[0][0] = 0.0f;
	translateCoords[0][1] = 0.0f;
	translateCoords[0][2] = 0.0f;

	translateCoords[1][0] = 0.0f;
	translateCoords[1][1] = 70.0f;
	translateCoords[1][2] = 0.0f;

	translateCoords[2][0] = 0.0f;
	translateCoords[2][1] = 140.0f;
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

	// LIGHT POSITION TOKEN
	_LightPositionUniform = glGetUniformLocation(_shaderProgramObject, "u_light_position");


	//SHINYNESS COLOR TOKEN
	material_shininess_uniform = glGetUniformLocation(_shaderProgramObject, "u_material_shininess");;

	const GLfloat TerminalGlassVertices[] =
	{
		quadWidth[0], quadHeight[0], 0.0f,
		-quadWidth[0], quadHeight[0], 0.0f,
		-quadWidth[0], -quadHeight[0], 0.0f,
		quadWidth[0], -quadHeight[0], 0.0f,
	};

	const GLfloat TerminalGlassNormals[] =
	{
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
	};

	const GLfloat TerminalSideVertices[] =
	{
		quadWidth[1], quadHeight[1], 0.0f,
		-quadWidth[1], quadHeight[1], 0.0f,
		-quadWidth[1], -quadHeight[1], 0.0f,
		quadWidth[1], -quadHeight[1], 0.0f,
	};

	const GLfloat TerminalSideNormals[] =
	{
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
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

	glGenVertexArrays(1, &vao[1]);

	glBindVertexArray(vao[1]);

		glGenBuffers(1, &vbo_position);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_position);
			glBufferData(GL_ARRAY_BUFFER, sizeof(TerminalSideVertices), TerminalSideVertices, GL_STATIC_DRAW);
			glVertexAttribPointer(AMC_ATTRIBUTE_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, NULL);
			glEnableVertexAttribArray(AMC_ATTRIBUTE_VERTEX);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, &vbo_normal);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_normal);
			glBufferData(GL_ARRAY_BUFFER, sizeof(TerminalSideNormals), TerminalSideNormals, GL_STATIC_DRAW);
			glVertexAttribPointer(AMC_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
			glEnableVertexAttribArray(AMC_ATTRIBUTE_NORMAL);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	vao[2] = vao[1];

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
	int i = 0;

	for (i = 0; i < 3; i++)
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

		//material shininess
		glUniform1f(material_shininess_uniform, material_shininess);

		modelMatrix = translate(attributes.translateCoords[0] + translateCoords[i][0], 
								attributes.translateCoords[1] + translateCoords[i][1], 
								attributes.translateCoords[2] + translateCoords[i][2]);

		glUniformMatrix4fv(_modelMatrixUniform, 1, GL_FALSE, modelMatrix);
		glUniformMatrix4fv(_ViewMatrixUniform, 1, GL_FALSE, viewMatrix);
		glUniformMatrix4fv(_projectMatrixUniform, 1, GL_FALSE, _perspectiveProjectionMatrix);

		glBindVertexArray(vao[i]);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		glBindVertexArray(0);


		glUniform3fv(_KaUniform, 1, materialFrameAmbient);
		glUniform3fv(_KdUniform, 1, materialFrameDiffuse);
		glUniform3fv(_KsUniform, 1, materialFrameSpecular);

		float increment = quadHeight[i] / 5;
		for (float y = -2 * quadHeight[i]; y < 0.0f; y += increment)
		{
			modelMatrix = mat4::identity();
			viewMatrix = mat4::identity();

			modelMatrix = translate(attributes.translateCoords[0] + translateCoords[i][0],
									attributes.translateCoords[1] + translateCoords[i][1]+y,
									attributes.translateCoords[2] + translateCoords[i][2]);			
			//rotateMatrix = rotate(-30.0f, 1.0f, 0.0f, 0.0f);
			//modelMatrix = modelMatrix * rotateMatrix;

			glUniformMatrix4fv(_modelMatrixUniform, 1, GL_FALSE, modelMatrix);
			glUniformMatrix4fv(_ViewMatrixUniform, 1, GL_FALSE, viewMatrix);
			glUniformMatrix4fv(_projectMatrixUniform, 1, GL_FALSE, _perspectiveProjectionMatrix);

			glBindVertexArray(vao[i]);
			glDrawArrays(GL_LINES, 0, 2);
			glBindVertexArray(0);
		}

		increment = quadWidth[i] / 20;
		for (float x = 0.0; x < 2 * quadWidth[i]; x += increment)
		{
			modelMatrix = mat4::identity();
			viewMatrix = mat4::identity();

			modelMatrix = translate(attributes.translateCoords[0] + translateCoords[i][0]+x,
									attributes.translateCoords[1] + translateCoords[i][1],
									attributes.translateCoords[2] + translateCoords[i][2]);			
			//rotateMatrix = rotate(-30.0f, 1.0f, 0.0f, 0.0f);
			//modelMatrix = modelMatrix * rotateMatrix;

			glUniformMatrix4fv(_modelMatrixUniform, 1, GL_FALSE, modelMatrix);
			glUniformMatrix4fv(_ViewMatrixUniform, 1, GL_FALSE, viewMatrix);
			glUniformMatrix4fv(_projectMatrixUniform, 1, GL_FALSE, _perspectiveProjectionMatrix);

			glBindVertexArray(vao[i]);
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
