
/*
* @author: Sanket Deshmukh
* @mailto: 1sanketdeshmukh@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/

#include "Table.h"
#include "SphereMesh.h"
#include "Sphere.h"

#pragma comment(lib, "Sphere.lib")

Sanket::Table::Table()
{

}

Sanket::Table::~Table()
{
	UnInitialize();
}


BOOL Sanket::Table::SceneHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	return 0;
}

void Sanket::Table::Initialize()
{

	SAFE_LOG("Table shading language supported version is : %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION))

		//CREAT VERTEXT SHADER OBJECT
		_vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

	//CREATE SOURCE CODE FOR VERTEX SHADER OBJECT
	const GLchar *vertexShaderSourcecode =
		"#version 400 core" \
		"\n" \
		"in vec4 vPosition;" \
		"in vec3 vNormal;" \
		"uniform mat4 u_model_matrix ;" \
		"uniform mat4 u_view_matrix ;" \
		"uniform mat4 u_projection_matrix ;" \
		"uniform vec4 u_light0_position;"\
		"out vec3 transformed_normals;" \
		"out vec3 light_direction;" \
		"out vec3 viewer_vector;" \
		"void main(void)" \
		"{" \
		"vec4 eye_coordinates = u_view_matrix *u_model_matrix* vPosition;"\
		"transformed_normals = mat3 (u_view_matrix * u_model_matrix) * vNormal;"\
		"light_direction = vec3 (u_light0_position) - eye_coordinates.xyz;"\
		"viewer_vector = -eye_coordinates.xyz;"\
		"gl_Position = u_projection_matrix * u_view_matrix * u_model_matrix * vPosition ;" \
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
				SAFE_LOG("Table Vertex Shader Compilation Log : %s\n", szInfoLog)
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
		"in vec3 transformed_normals;" \
		"in vec3 light_direction;" \
		"in vec3 viewer_vector;" \
		"out vec4 FragColor;" \
		"uniform vec3 u_La0;"\
		"uniform vec3 u_Ld0;"\
		"uniform vec3 u_Ls0;"\
		"uniform vec3 u_Ka;"\
		"uniform vec3 u_Kd;"\
		"uniform vec3 u_Ks;"\
		"uniform float u_material_shininess;"\
		"uniform int u_lighting_enabled;"\
		"void main(void)" \
		"{" \
		"vec3 phong_ads_color;"\
		"vec3 normalized_transformed_normals=normalize(transformed_normals);"\
		"vec3 normalized_light_direction = normalize(light_direction);"\
		"vec3 normalized_viewer_vector = normalize(viewer_vector);"\
		"vec3 ambient = u_La0 * u_Ka ;"\
		"float tn_dot_ld = max(dot(normalized_transformed_normals,normalized_light_direction),0.0);"\
		"vec3 diffuse = u_Ld0 * u_Kd * tn_dot_ld; "\
		"vec3 reflection_vector = reflect(-normalized_light_direction,normalized_transformed_normals);"\
		"vec3 specular = u_Ls0 * u_Ks * pow(max(dot(reflection_vector,normalized_viewer_vector),0.0),u_material_shininess); "\
		"phong_ads_color = ambient + diffuse + specular;  "\
		"FragColor = vec4(phong_ads_color,1.0);"\
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

				SAFE_LOG("Table Fragment Shader Compilation Log : %s\n", szInfoLog)
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

				SAFE_LOG("Table Shader Program Link Log : %s \n", szInfoLog)
					SAFE_FREE(szInfoLog);
				UnInitialize();
				exit(0);
			}

		}
	}


	//GET MVP UNIFORM LOCATION
	

	_ModelMatrixUniform = glGetUniformLocation(_shaderProgramObject, "u_model_matrix");

	_ViewMatrixUniform = glGetUniformLocation(_shaderProgramObject, "u_view_matrix");

	_ProjectionMatrixUniform = glGetUniformLocation(_shaderProgramObject, "u_projection_matrix");

	_La0Uniform = glGetUniformLocation(_shaderProgramObject, "u_La0");
	_Ld0Uniform = glGetUniformLocation(_shaderProgramObject, "u_Ld0");
	_Ls0Uniform = glGetUniformLocation(_shaderProgramObject, "u_Ls0");
	_Light0PositionUniform = glGetUniformLocation(_shaderProgramObject, "u_light0_position");
	_La1Uniform = glGetUniformLocation(_shaderProgramObject, "u_La1");
	_Ld1Uniform = glGetUniformLocation(_shaderProgramObject, "u_Ld1");
	_Ls1Uniform = glGetUniformLocation(_shaderProgramObject, "u_Ls1");
	_Light1PositionUniform = glGetUniformLocation(_shaderProgramObject, "u_light1_position");
	_KaUniform = glGetUniformLocation(_shaderProgramObject, "u_Ka");
	_KdUniform = glGetUniformLocation(_shaderProgramObject, "u_Kd");
	_KsUniform = glGetUniformLocation(_shaderProgramObject, "u_Ks");
	_MaterialShininessUniform = glGetUniformLocation(_shaderProgramObject, "u_material_shininess");

	/// *** vertices , colors , shader attribs , vbo ,vao initializations *** ///


	const GLfloat cubeVertices[] =
	{
		// Top face

		1.0f, 1.0f, -1.0f,   // Right-top corner of top face 
		-1.0f,1.0f, -1.0f, // left-top corner of the top face
		-1.0f,1.0f, 1.0f,   //left bottom corner of front face
		1.0f, 1.0f, 1.0f, //right bottom corner of front face

						  //Bottom face

						  1.0f, -1.0f, -1.0f,   // Right-top corner of bottom face 
						  -1.0f, -1.0f, -1.0f, // left-top corner of the bottom face
						  -1.0f, -1.0f, 1.0f,   //left bottom corner of bottom face
						  1.0f, -1.0f, 1.0f, //right bottom corner of bottom face

											 //Front face

											 1.0f, 1.0f, 1.0f,   // Right-top corner of front face 
											 -1.0f,1.0f, 1.0f, // left-top corner of the front face
											 -1.0f, -1.0f, 1.0f,   //left bottom corner of front face
											 1.0f, -1.0f, 1.0f, //right bottom corner of front face


																//Back face

																1.0f, 1.0f, -1.0f,  // Right-top corner of back face 
																-1.0f,1.0f, -1.0f, // left-top corner of the back face
																-1.0f, -1.0f, -1.0f,   //left bottom corner of back face
																1.0f, -1.0f, -1.0f, //right bottom corner of back face

																					//Right face

																					1.0f, 1.0f, -1.0f,   // Right-top corner of right face 
																					1.0f, 1.0f, 1.0f, // left-top corner of the right face
																					1.0f, -1.0f, 1.0f,   //left bottom corner of right face
																					1.0f, -1.0f, -1.0f, //right bottom corner of right face

																										//Left face

																										-1.0f, 1.0f, 1.0f,   // Right-top corner of left face 
																										-1.0f, 1.0f, -1.0f, // left-top corner of the left face
																										-1.0f, -1.0f, -1.0f,   //left bottom corner of left face
																										-1.0f, -1.0f, 1.0f //right bottom corner of left face

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


	// Cylinder code

	makeSphere(0.15, 2.0, 10, 10);


	// Sphere 

	// Get Sphere Vertices

	getSphereVertexData(sphere_vertices, sphere_normals, sphere_textures, sphere_elements);

	gNumVertices = getNumberOfSphereVertices();

	gNumElements = getNumberOfSphereElements();


	glGenVertexArrays(1, &vao_Sphere);
	glBindVertexArray(vao_Sphere);

		glGenBuffers(1, &vbo_Sphere_Position);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_Sphere_Position);
		glBufferData(GL_ARRAY_BUFFER, sizeof(sphere_vertices), sphere_vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(AMC_ATTRIBUTE_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(AMC_ATTRIBUTE_VERTEX);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//// vbo for texture 

		glGenBuffers(1, &vbo_Sphere_Normal);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_Sphere_Normal);
		glBufferData(GL_ARRAY_BUFFER, sizeof(sphere_normals), sphere_normals, GL_STATIC_DRAW);

		glVertexAttribPointer(AMC_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(AMC_ATTRIBUTE_NORMAL);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// element vbo
		glGenBuffers(1, &vbo_Sphere_Elements);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_Sphere_Elements);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(sphere_elements), sphere_elements, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	// Cube Vao

	// Cube code 

	glGenVertexArrays(1, &vao_Cube);
	glBindVertexArray(vao_Cube);

		// Vbo for position 
		glGenBuffers(1, &vbo_Cube_Position);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_Cube_Position);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

		glVertexAttribPointer(AMC_ATTRIBUTE_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(AMC_ATTRIBUTE_VERTEX);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// vbo for normal 

		glGenBuffers(1, &vbo_Cube_Normal);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_Cube_Normal);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cubeNormals), cubeNormals, GL_STATIC_DRAW);

		glVertexAttribPointer(AMC_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(AMC_ATTRIBUTE_NORMAL);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);


	//
	
	
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


void Sanket::Table::Update()
{
	
}

void Sanket::Table::ReSize(int width, int height, struct ResizeAttributes attributes)
{
	if (height == 0)
		height = 1;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	_perspectiveProjectionMatrix = vmath::perspective(45.0f, (GLfloat)width / (GLfloat)height, attributes.nearValue, attributes.farValue);

}

void Sanket::Table::Render(HDC hdc, struct Attributes attributes)
{
	glDisable(GL_CULL_FACE);

	//START USING SHADER OBJECT	
	glUseProgram(_shaderProgramObject);
	GLfloat lightPosition[4] = { 100.0f,100.0f,100.0f,0.0f };

	glUniform3fv(_La0Uniform, 1, light0_ambient);
	glUniform3fv(_Ld0Uniform, 1, light0_diffuse);
	glUniform3fv(_Ls0Uniform, 1, light0_specular);
	glUniform4fv(_Light0PositionUniform, 1, lightPosition);

	glUniform3fv(_La1Uniform, 1, light1_ambient);
	glUniform3fv(_Ld1Uniform, 1, light1_diffuse);
	glUniform3fv(_Ls1Uniform, 1, light1_specular);
	glUniform4fv(_Light1PositionUniform, 1, light1_position);

	// Material's properties
	glUniform3fv(_KaUniform, 1, materialAmbientWood);
	glUniform3fv(_KdUniform, 1, materialDiffuseWood);
	glUniform3fv(_KsUniform, 1, materialSpecularWood);
	glUniform1f(_MaterialShininessUniform, materialShininessWood);

	mat4 modelMatrix = mat4::identity();
	mat4 viewMatrix = mat4::identity();
	mat4 rotationMatrix = mat4::identity();
	mat4 scaleMatrix = mat4::identity();
	mat4 translateGlobalMatrix = mat4::identity();
	mat4 rotateGlobalMatrix = mat4::identity();
	mat4 globalTRMatrix = mat4::identity();

	rotateGlobalMatrix = rotate(
		attributes.rotateCoords[SCENE_AIRPORT_MODEL][0],
		attributes.rotateCoords[SCENE_AIRPORT_MODEL][1],
		attributes.rotateCoords[SCENE_AIRPORT_MODEL][2]
	);

	translateGlobalMatrix = translate(
		attributes.translateCoords[SCENE_TABLE][0] + attributes.translateCoords[SCENE_AIRPORT_MODEL][0],
		attributes.translateCoords[SCENE_TABLE][1] + attributes.translateCoords[SCENE_AIRPORT_MODEL][1],
		attributes.translateCoords[SCENE_TABLE][2] + attributes.translateCoords[SCENE_AIRPORT_MODEL][2]);

	globalTRMatrix = translateGlobalMatrix * rotateGlobalMatrix;

	modelMatrix = translate(0.0f, -2.0f, -8.0f) * globalTRMatrix;
	scaleMatrix = scale(1.0f, 0.09f, 1.0f);
	modelMatrix = modelMatrix *scaleMatrix ;

	glUniformMatrix4fv(_ModelMatrixUniform, 1, GL_FALSE, modelMatrix);
	glUniformMatrix4fv(_ViewMatrixUniform, 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(_ProjectionMatrixUniform, 1, GL_FALSE, _perspectiveProjectionMatrix);

	glBindVertexArray(vao_Cube);
	// Draw Cube.

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 4, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 16, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 20, 4);

	// unbind Cube Vao
	glBindVertexArray(0);

	//modelMatrix = mat4::identity();
	//viewMatrix = mat4::identity();
	//rotationMatrix = mat4::identity();
	//scaleMatrix = mat4::identity();

	//// Translate model view matrix.

	//modelMatrix = translate(0.0f, 1.0f, -8.0f) * globalTRMatrix;
	//scaleMatrix = scale(6.5f, 0.09f, 3.6f);

	//modelMatrix = modelMatrix * scaleMatrix;

	//glUniformMatrix4fv(_ModelMatrixUniform, 1, GL_FALSE, modelMatrix);
	//glUniformMatrix4fv(_ViewMatrixUniform, 1, GL_FALSE, viewMatrix);
	//glUniformMatrix4fv(_ProjectionMatrixUniform, 1, GL_FALSE, _perspectiveProjectionMatrix);


	//glUniform3fv(_La0Uniform, 1, light0_ambient);
	//glUniform3fv(_Ld0Uniform, 1, light0_diffuse);
	//glUniform3fv(_Ls0Uniform, 1, light0_specular);
	//glUniform4fv(_Light0PositionUniform, 1, light0_position);

	//glUniform3fv(_La1Uniform, 1, light1_ambient);
	//glUniform3fv(_Ld1Uniform, 1, light1_diffuse);
	//glUniform3fv(_Ls1Uniform, 1, light1_specular);
	//glUniform4fv(_Light1PositionUniform, 1, light1_position);


	//glBindVertexArray(vao_Cube);

	//// Draw Cube.

	//glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	//glDrawArrays(GL_TRIANGLE_FAN, 4, 4);
	//glDrawArrays(GL_TRIANGLE_FAN, 8, 4);
	//glDrawArrays(GL_TRIANGLE_FAN, 12, 4);
	//glDrawArrays(GL_TRIANGLE_FAN, 16, 4);
	//glDrawArrays(GL_TRIANGLE_FAN, 20, 4);

	//// unbind Cube Vao
	//glBindVertexArray(0);

	glUniform3fv(_KaUniform, 1, materialAmbient);
	glUniform3fv(_KdUniform, 1, materialDiffuse);
	glUniform3fv(_KsUniform, 1, materialSpecular);
	glUniform1f(_MaterialShininessUniform, materialShininess);

	modelMatrix = mat4::identity();
	viewMatrix = mat4::identity();
	rotationMatrix = mat4::identity();
	scaleMatrix = mat4::identity();

	// draw cylinder between two cubes.

	modelMatrix = translate(0.0f, 1.0f, -8.0f) * globalTRMatrix;
	rotationMatrix = rotate(90.0f, 1.0f, 0.0f, 0.0f);
	scaleMatrix = scale(1.0f, 1.4f, 1.0f);

	// multiply the modelview and rotation matrix.

	modelMatrix = modelMatrix *  scaleMatrix;
	modelMatrix = modelMatrix * rotationMatrix;

	glUniformMatrix4fv(_ModelMatrixUniform, 1, GL_FALSE, modelMatrix);
	glUniformMatrix4fv(_ViewMatrixUniform, 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(_ProjectionMatrixUniform, 1, GL_FALSE, _perspectiveProjectionMatrix);

	draw();


	// top sphere

	modelMatrix = mat4::identity();
	viewMatrix = mat4::identity();
	rotationMatrix = mat4::identity();
	scaleMatrix = mat4::identity();

	modelMatrix = translate(-2.7f - TRANS_X_TABLE, 1.6f, -12.0f - TRANS_Z_TABLE) * globalTRMatrix;
	scaleMatrix = scale(0.4f, 0.4f, 0.4f);

	// multiply the modelview and rotation matrix.

	modelMatrix = modelMatrix *  scaleMatrix;

	glUniformMatrix4fv(_ModelMatrixUniform, 1, GL_FALSE, modelMatrix);
	glUniformMatrix4fv(_ViewMatrixUniform, 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(_ProjectionMatrixUniform, 1, GL_FALSE, _perspectiveProjectionMatrix);

	glUniform3fv(_La0Uniform, 1, light0_ambient);
	glUniform3fv(_Ld0Uniform, 1, light0_diffuse);
	glUniform3fv(_Ls0Uniform, 1, light0_specular);
	glUniform4fv(_Light0PositionUniform, 1, light0_position);


	glUniform3fv(_La1Uniform, 1, light1_ambient);
	glUniform3fv(_Ld1Uniform, 1, light1_diffuse);
	glUniform3fv(_Ls1Uniform, 1, light1_specular);
	glUniform4fv(_Light1PositionUniform, 1, light1_position);

	// Material's properties
	glUniform3fv(_KaUniform, 1, materialAmbient);
	glUniform3fv(_KdUniform, 1, materialDiffuse);
	glUniform3fv(_KsUniform, 1, materialSpecular);
	glUniform1f(_MaterialShininessUniform, materialShininess);

	// Sphere Code 

	// *** bind vao ***
	glBindVertexArray(vao_Sphere);

	// *** draw, either by glDrawTriangles() or glDrawArrays() or glDrawElements()
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vbo_Sphere_Elements);
	glDrawElements(GL_TRIANGLES, gNumElements, GL_UNSIGNED_SHORT, 0);

	// *** unbind vao ***
	glBindVertexArray(0);


	// top edge cylinder

	modelMatrix = mat4::identity();
	viewMatrix = mat4::identity();
	rotationMatrix = mat4::identity();
	scaleMatrix = mat4::identity();

	// draw cylinder

	modelMatrix = translate(-2.5f - TRANS_X_TABLE, 1.43f, -11.5f - TRANS_Z_TABLE) * globalTRMatrix;
	rotationMatrix = rotate(90.0f, 1.0f, 0.0f, 0.0f);
	scaleMatrix = scale(1.5f, 0.05f, 1.0f);

	// multiply the modelview and rotation matrix.

	modelMatrix = modelMatrix *  scaleMatrix;
	modelMatrix = modelMatrix * rotationMatrix;

	glUniform3fv(_La0Uniform, 1, light0_ambient);
	glUniform3fv(_Ld0Uniform, 1, light0_diffuse);
	glUniform3fv(_Ls0Uniform, 1, light0_specular);
	glUniform4fv(_Light0PositionUniform, 1, light0_position);


	glUniform3fv(_La1Uniform, 1, light1_ambient);
	glUniform3fv(_Ld1Uniform, 1, light1_diffuse);
	glUniform3fv(_Ls1Uniform, 1, light1_specular);
	glUniform4fv(_Light1PositionUniform, 1, light1_position);

	// Material's properties
	glUniform3fv(_KaUniform, 1, materialAmbientDark);
	glUniform3fv(_KdUniform, 1, materialDiffuseDark);
	glUniform3fv(_KsUniform, 1, materialSpecularDark);
	glUniform1f(_MaterialShininessUniform, materialShininessDark);

	glUniformMatrix4fv(_ModelMatrixUniform, 1, GL_FALSE, modelMatrix);
	glUniformMatrix4fv(_ViewMatrixUniform, 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(_ProjectionMatrixUniform, 1, GL_FALSE, _perspectiveProjectionMatrix);

	draw();

	// bottom edge cylinder

	modelMatrix = mat4::identity();
	viewMatrix = mat4::identity();
	rotationMatrix = mat4::identity();
	scaleMatrix = mat4::identity();

	// draw cylinder

	modelMatrix = translate(-2.5f - TRANS_X_TABLE, -2.3f, -11.5f - TRANS_Z_TABLE) * globalTRMatrix;

	rotationMatrix = rotate(90.0f, 1.0f, 0.0f, 0.0f);

	scaleMatrix = scale(3.5f, 0.05f, 1.2f);

	// multiply the modelview and rotation matrix.

	modelMatrix = modelMatrix *  scaleMatrix;

	modelMatrix = modelMatrix * rotationMatrix;

	glUniformMatrix4fv(_ModelMatrixUniform, 1, GL_FALSE, modelMatrix);

	glUniformMatrix4fv(_ViewMatrixUniform, 1, GL_FALSE, viewMatrix);

	glUniformMatrix4fv(_ProjectionMatrixUniform, 1, GL_FALSE, _perspectiveProjectionMatrix);

	draw();
	

	// bottom edge cylinder

	modelMatrix = mat4::identity();
	viewMatrix = mat4::identity();
	rotationMatrix = mat4::identity();
	scaleMatrix = mat4::identity();

	// draw cylinder

	modelMatrix = translate(-2.7f - TRANS_X_TABLE, -2.3f, -7.0f + TRANS_Z_TABLE) * globalTRMatrix;

	rotationMatrix = rotate(90.0f, 1.0f, 0.0f, 0.0f);

	scaleMatrix = scale(3.5f, 0.05f, 1.0f);

	// multiply the modelview and rotation matrix.

	modelMatrix = modelMatrix *  scaleMatrix;

	modelMatrix = modelMatrix * rotationMatrix;

	glUniformMatrix4fv(_ModelMatrixUniform, 1, GL_FALSE, modelMatrix);

	glUniformMatrix4fv(_ViewMatrixUniform, 1, GL_FALSE, viewMatrix);

	glUniformMatrix4fv(_ProjectionMatrixUniform, 1, GL_FALSE, _perspectiveProjectionMatrix);

	draw();



	// Top edge cylinder

	modelMatrix = mat4::identity();
	viewMatrix = mat4::identity();
	rotationMatrix = mat4::identity();
	scaleMatrix = mat4::identity();

	// draw cylinder

	modelMatrix = translate(-2.6f - TRANS_X_TABLE, 1.5f, -6.7f + TRANS_Z_TABLE) * globalTRMatrix;

	rotationMatrix = rotate(90.0f, 1.0f, 0.0f, 0.0f);

	scaleMatrix = scale(1.5f, 0.05f, 1.0f);

	// multiply the modelview and rotation matrix.

	modelMatrix = modelMatrix *  scaleMatrix;

	modelMatrix = modelMatrix * rotationMatrix;

	glUniformMatrix4fv(_ModelMatrixUniform, 1, GL_FALSE, modelMatrix);

	glUniformMatrix4fv(_ViewMatrixUniform, 1, GL_FALSE, viewMatrix);

	glUniformMatrix4fv(_ProjectionMatrixUniform, 1, GL_FALSE, _perspectiveProjectionMatrix);

	draw();

	// bottom edge cylinder

	modelMatrix = mat4::identity();
	viewMatrix = mat4::identity();
	rotationMatrix = mat4::identity();
	scaleMatrix = mat4::identity();

	// draw cylinder

	modelMatrix = translate(2.7f + TRANS_X_TABLE, -2.3f, -7.0f + TRANS_Z_TABLE) * globalTRMatrix;

	rotationMatrix = rotate(90.0f, 1.0f, 0.0f, 0.0f);

	scaleMatrix = scale(3.5f, 0.05f, 1.0f);

	// multiply the modelview and rotation matrix.

	modelMatrix = modelMatrix *  scaleMatrix;

	modelMatrix = modelMatrix * rotationMatrix;

	glUniformMatrix4fv(_ModelMatrixUniform, 1, GL_FALSE, modelMatrix);

	glUniformMatrix4fv(_ViewMatrixUniform, 1, GL_FALSE, viewMatrix);

	glUniformMatrix4fv(_ProjectionMatrixUniform, 1, GL_FALSE, _perspectiveProjectionMatrix);

	draw();

	// Top edge cylinder

	modelMatrix = mat4::identity();
	viewMatrix = mat4::identity();
	rotationMatrix = mat4::identity();
	scaleMatrix = mat4::identity();

	// draw cylinder

	modelMatrix = translate(2.6f + TRANS_X_TABLE, 1.5f, -6.7f + TRANS_Z_TABLE) * globalTRMatrix;

	rotationMatrix = rotate(90.0f, 1.0f, 0.0f, 0.0f);

	scaleMatrix = scale(1.5f, 0.05f, 1.0f);

	// multiply the modelview and rotation matrix.

	modelMatrix = modelMatrix *  scaleMatrix;

	modelMatrix = modelMatrix * rotationMatrix;

	glUniformMatrix4fv(_ModelMatrixUniform, 1, GL_FALSE, modelMatrix);

	glUniformMatrix4fv(_ViewMatrixUniform, 1, GL_FALSE, viewMatrix);

	glUniformMatrix4fv(_ProjectionMatrixUniform, 1, GL_FALSE, _perspectiveProjectionMatrix);

	draw();


	// bottom edge cylinder

	modelMatrix = mat4::identity();
	viewMatrix = mat4::identity();
	rotationMatrix = mat4::identity();
	scaleMatrix = mat4::identity();

	// draw cylinder

	modelMatrix = translate(2.7f + TRANS_X_TABLE, -2.3f, -12.0f - TRANS_Z_TABLE) * globalTRMatrix;

	rotationMatrix = rotate(90.0f, 1.0f, 0.0f, 0.0f);

	scaleMatrix = scale(3.5f, 0.05f, 1.0f);

	// multiply the modelview and rotation matrix.

	modelMatrix = modelMatrix *  scaleMatrix;

	modelMatrix = modelMatrix * rotationMatrix;

	glUniformMatrix4fv(_ModelMatrixUniform, 1, GL_FALSE, modelMatrix);

	glUniformMatrix4fv(_ViewMatrixUniform, 1, GL_FALSE, viewMatrix);

	glUniformMatrix4fv(_ProjectionMatrixUniform, 1, GL_FALSE, _perspectiveProjectionMatrix);

	draw();



	// Top edge cylinder

	modelMatrix = mat4::identity();
	viewMatrix = mat4::identity();
	rotationMatrix = mat4::identity();
	scaleMatrix = mat4::identity();

	// draw cylinder

	// Sanket

	modelMatrix = translate(2.6f + TRANS_X_TABLE, 1.5f, -11.50f - TRANS_Z_TABLE) * globalTRMatrix;

	rotationMatrix = rotate(90.0f, 1.0f, 0.0f, 0.0f);

	scaleMatrix = scale(1.5f, 0.05f, 1.0f);

	// multiply the modelview and rotation matrix.

	modelMatrix = modelMatrix *  scaleMatrix;

	modelMatrix = modelMatrix * rotationMatrix;

	glUniformMatrix4fv(_ModelMatrixUniform, 1, GL_FALSE, modelMatrix);

	glUniformMatrix4fv(_ViewMatrixUniform, 1, GL_FALSE, viewMatrix);

	glUniformMatrix4fv(_ProjectionMatrixUniform, 1, GL_FALSE, _perspectiveProjectionMatrix);

	draw();

	modelMatrix = mat4::identity();
	viewMatrix = mat4::identity();
	rotationMatrix = mat4::identity();
	scaleMatrix = mat4::identity();

	modelMatrix = translate(0.0f + TRANS_X_TABLE, 1.5f, -12.0f - TRANS_Z_TABLE) * globalTRMatrix;

	rotationMatrix = rotate(90.0f, 1.0f, 0.0f, 0.0f);

	scaleMatrix = scale(0.5f, 0.5f, 0.5f);

	// multiply the modelview and rotation matrix.

	modelMatrix = modelMatrix *  scaleMatrix;

	modelMatrix = modelMatrix * rotationMatrix;

	glUniformMatrix4fv(_ModelMatrixUniform, 1, GL_FALSE, modelMatrix);

	glUniformMatrix4fv(_ViewMatrixUniform, 1, GL_FALSE, viewMatrix);

	glUniformMatrix4fv(_ProjectionMatrixUniform, 1, GL_FALSE, _perspectiveProjectionMatrix);


	materialAmbient[0] = 1.0f;
	materialAmbient[1] = 1.0f;
	materialAmbient[2] = 1.0f;
	materialAmbient[3] = 1.0f;
	materialDiffuse[0] = 1.0f;
	materialDiffuse[1] = 1.0f;
	materialDiffuse[2] = 1.0f;
	materialDiffuse[3] = 1.0f;
	materialSpecular[0] =1.0f;
	materialSpecular[1] = 1.0f;
	materialSpecular[2] = 1.0f;
	materialSpecular[3] = 1.0f;
	materialShininess = 50.0f;

	glUniform3fv(_KaUniform, 1, materialAmbient);
	glUniform3fv(_KdUniform, 1, materialDiffuse);
	glUniform3fv(_KsUniform, 1, materialSpecular);
	glUniform1f(_MaterialShininessUniform, materialShininess);

	// top sphere

	modelMatrix = mat4::identity();
	viewMatrix = mat4::identity();
	rotationMatrix = mat4::identity();
	scaleMatrix = mat4::identity();

	modelMatrix = translate(2.7f + TRANS_X_TABLE, 1.7f, -12.0f - TRANS_Z_TABLE) * globalTRMatrix;

	scaleMatrix = scale(0.4f, 0.4f, 0.4f);

	// multiply the modelview and rotation matrix.

	modelMatrix = modelMatrix *  scaleMatrix;


	glUniformMatrix4fv(_ModelMatrixUniform, 1, GL_FALSE, modelMatrix);

	glUniformMatrix4fv(_ViewMatrixUniform, 1, GL_FALSE, viewMatrix);

	glUniformMatrix4fv(_ProjectionMatrixUniform, 1, GL_FALSE, _perspectiveProjectionMatrix);


	// Sphere Code 

	// *** bind vao ***
	glBindVertexArray(vao_Sphere);

	// *** draw, either by glDrawTriangles() or glDrawArrays() or glDrawElements()
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_Sphere_Elements);
	glDrawElements(GL_TRIANGLES, gNumElements, GL_UNSIGNED_SHORT, 0);

	// *** unbind vao ***
	glBindVertexArray(0);



	// top sphere

	modelMatrix = mat4::identity();
	viewMatrix = mat4::identity();
	rotationMatrix = mat4::identity();
	scaleMatrix = mat4::identity();

	modelMatrix = translate(2.7f + TRANS_X_TABLE, 1.7f, -7.0f + TRANS_Z_TABLE) * globalTRMatrix;

	scaleMatrix = scale(0.4f, 0.4f, 0.4f);

	// multiply the modelview and rotation matrix.

	modelMatrix = modelMatrix *  scaleMatrix;

	glUniformMatrix4fv(_ModelMatrixUniform, 1, GL_FALSE, modelMatrix);

	glUniformMatrix4fv(_ViewMatrixUniform, 1, GL_FALSE, viewMatrix);

	glUniformMatrix4fv(_ProjectionMatrixUniform, 1, GL_FALSE, _perspectiveProjectionMatrix);


	// Sphere Code 

	// *** bind vao ***
	glBindVertexArray(vao_Sphere);

	// *** draw, either by glDrawTriangles() or glDrawArrays() or glDrawElements()
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_Sphere_Elements);
	glDrawElements(GL_TRIANGLES, gNumElements, GL_UNSIGNED_SHORT, 0);

	// *** unbind vao ***
	glBindVertexArray(0);

	
	//  back left cylinder

	modelMatrix = mat4::identity();
	viewMatrix = mat4::identity();
	rotationMatrix = mat4::identity();
	scaleMatrix = mat4::identity();

	// draw cylinder

	modelMatrix = translate(-2.7f - TRANS_X_TABLE, 1.4f, -12.0f - TRANS_Z_TABLE) * globalTRMatrix;

	rotationMatrix = rotate(90.0f, 1.0f, 0.0f, 0.0f);

	scaleMatrix = scale(0.7f, 1.9f, 1.0f);

	// multiply the modelview and rotation matrix.

	modelMatrix = modelMatrix *  scaleMatrix;

	modelMatrix = modelMatrix * rotationMatrix;

	glUniformMatrix4fv(_ModelMatrixUniform, 1, GL_FALSE, modelMatrix);

	glUniformMatrix4fv(_ViewMatrixUniform, 1, GL_FALSE, viewMatrix);

	glUniformMatrix4fv(_ProjectionMatrixUniform, 1, GL_FALSE, _perspectiveProjectionMatrix);

	draw();

	modelMatrix = mat4::identity();
	viewMatrix = mat4::identity();
	rotationMatrix = mat4::identity();
	scaleMatrix = mat4::identity();

	modelMatrix = translate(-2.7f - TRANS_X_TABLE, 1.7f, -7.0f + TRANS_Z_TABLE) * globalTRMatrix;

	scaleMatrix = scale(0.4f, 0.4f, 0.4f);

	// multiply the modelview and rotation matrix.

	modelMatrix = modelMatrix *  scaleMatrix;

	glUniformMatrix4fv(_ModelMatrixUniform, 1, GL_FALSE, modelMatrix);

	glUniformMatrix4fv(_ViewMatrixUniform, 1, GL_FALSE, viewMatrix);

	glUniformMatrix4fv(_ProjectionMatrixUniform, 1, GL_FALSE, _perspectiveProjectionMatrix);


	// Sphere Code 

	// *** bind vao ***
	glBindVertexArray(vao_Sphere);

	// *** draw, either by glDrawTriangles() or glDrawArrays() or glDrawElements()
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_Sphere_Elements);
	glDrawElements(GL_TRIANGLES, gNumElements, GL_UNSIGNED_SHORT, 0);

	// *** unbind vao ***
	glBindVertexArray(0);


	modelMatrix = mat4::identity();
	viewMatrix = mat4::identity();
	rotationMatrix = mat4::identity();
	scaleMatrix = mat4::identity();

	// left front draw cylinder

	modelMatrix = translate(-2.7f - TRANS_X_TABLE, 1.4f, -7.0f + TRANS_Z_TABLE) * globalTRMatrix;

	rotationMatrix = rotate(90.0f, 1.0f, 0.0f, 0.0f);

	scaleMatrix = scale(0.7f, 1.9f, 1.0f);

	modelMatrix = modelMatrix *  scaleMatrix;

	modelMatrix = modelMatrix * rotationMatrix;

	glUniformMatrix4fv(_ModelMatrixUniform, 1, GL_FALSE, modelMatrix);

	glUniformMatrix4fv(_ViewMatrixUniform, 1, GL_FALSE, viewMatrix);

	glUniformMatrix4fv(_ProjectionMatrixUniform, 1, GL_FALSE, _perspectiveProjectionMatrix);

	draw();

	// front right

	modelMatrix = mat4::identity();
	viewMatrix = mat4::identity();
	rotationMatrix = mat4::identity();
	scaleMatrix = mat4::identity();

	// draw cylinder

	modelMatrix = translate(2.7f + TRANS_X_TABLE, 1.4f, -7.0f + TRANS_Z_TABLE) * globalTRMatrix;

	rotationMatrix = rotate(90.0f, 1.0f, 0.0f, 0.0f);

	scaleMatrix = scale(0.7f, 1.9f, 1.0f);

	// multiply the modelview and rotation matrix.

	modelMatrix = modelMatrix *  scaleMatrix;

	modelMatrix = modelMatrix * rotationMatrix;

	glUniformMatrix4fv(_ModelMatrixUniform, 1, GL_FALSE, modelMatrix);

	glUniformMatrix4fv(_ViewMatrixUniform, 1, GL_FALSE, viewMatrix);

	glUniformMatrix4fv(_ProjectionMatrixUniform, 1, GL_FALSE, _perspectiveProjectionMatrix);

	draw();

	// right - back cylinder

	modelMatrix = mat4::identity();
	viewMatrix = mat4::identity();
	rotationMatrix = mat4::identity();
	scaleMatrix = mat4::identity();

	// draw cylinder

	modelMatrix = translate(2.7f + TRANS_X_TABLE, 1.4f, -12.0f -TRANS_Z_TABLE) * globalTRMatrix;

	rotationMatrix = rotate(90.0f, 1.0f, 0.0f, 0.0f);

	scaleMatrix = scale(0.7f, 1.9f, 1.0f);

	// multiply the modelview and rotation matrix.

	modelMatrix = modelMatrix *  scaleMatrix;

	modelMatrix = modelMatrix * rotationMatrix;

	glUniformMatrix4fv(_ModelMatrixUniform, 1, GL_FALSE, modelMatrix);

	glUniformMatrix4fv(_ViewMatrixUniform, 1, GL_FALSE, viewMatrix);

	glUniformMatrix4fv(_ProjectionMatrixUniform, 1, GL_FALSE, _perspectiveProjectionMatrix);

	draw();
	
	//STOP USING SHADER
	glUseProgram(0);

	return;


CLEAN_LOCAL_ALLOCATION_BELOW:
	UnInitialize();
}

void Sanket::Table::SceneTransition()
{
}

void Sanket::Table::UnInitialize()
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

