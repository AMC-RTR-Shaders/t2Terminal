/*
* @author: Rushabh Parakh
* @mailto: rgparakh@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/

#include "RollingCylinder.h"

Rushabh::RollingCylinder::RollingCylinder()
{
	_angle = 0.0f;
	gVertexX = -1.0f;
	gTexCoordX = 0.0f;
	_radius = 0.25f;
	_height = 2.0f;
}

Rushabh::RollingCylinder::~RollingCylinder()
{
	UnInitialize();
}

BOOL Rushabh::RollingCylinder::SceneHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	return 0;
}

void Rushabh::RollingCylinder::Initialize()
{

	//CREAT VERTEXT SHADER OBJECT
	_vertexShaderObject_cylinder = glCreateShader(GL_VERTEX_SHADER);

	//CREATE SOURCE CODE FOR VERTEX SHADER OBJECT
	const GLchar *vertexShaderSourcecode_cylinder =
		"#version 440 core"							\
		"\n"										\
		"in vec4 vPosition;"						\
		"in vec3 vNormal;"							\
		"uniform mat4 u_model_matrix;"				\
		"uniform mat4 u_view_matrix;"				\
		"uniform mat4 u_projection_matrix;"			\
		"uniform int u_lighting_enabled;"			\
		"uniform vec3 u_La;"						\
		"uniform vec3 u_Ld;"						\
		"uniform vec3 u_Ls;"						\
		"uniform vec4 u_light_position;"			\
		"uniform vec3 u_Ka;"						\
		"uniform vec3 u_Kd;"						\
		"uniform vec3 u_Ks;"						\
		"uniform float u_material_shininess;"		\
		"out vec3 phong_ads_color;"					\
		"void main(void)"							\
		"{"											\
		"if(u_lighting_enabled == 1)"				\
		"{"											\
		"vec4 eye_coordinates = u_view_matrix * u_model_matrix * vPosition;"					\
		"vec3 transformed_normals = normalize(mat3(u_view_matrix * u_model_matrix) * vNormal);"	\
		"vec3 light_direction = normalize(vec3(u_light_position) - eye_coordinates.xyz);"		\
		"float tn_dot_ld = max(dot(transformed_normals, light_direction), 0.0);"				\
		"vec3 ambient = u_La * u_Kd;"															\
		"vec3 diffuse = u_Ld * u_Kd * tn_dot_ld;"												\
		"vec3 reflection_vector = reflect(-light_direction, transformed_normals);"				\
		"vec3 viewer_vector = normalize(-eye_coordinates.xyz);"									\
		"vec3 specular = u_Ls * u_Ks * pow(max(dot(reflection_vector, viewer_vector), 0.0), u_material_shininess);"\
		"phong_ads_color = ambient + diffuse + specular;"										\
		"}"																						\
		"else"																					\
		"{"																						\
		"phong_ads_color = vec3(1.0, 1.0, 1.0);"												\
		"}"																						\
		"gl_Position = u_projection_matrix * u_view_matrix * u_model_matrix * vPosition;"		\
		"}";
	//BIND vertexShaderSourcecode CODE TO gVertexShaderObject
	glShaderSource(_vertexShaderObject_cylinder, 1, (const GLchar **)&vertexShaderSourcecode_cylinder, NULL);

	//COMPILE VERTEX SHADER
	glCompileShader(_vertexShaderObject_cylinder);

	/****************/


	GLint infoLogLength = 0;
	GLint iShaderCompilationStatus = 0;
	char *szInfoLog = NULL;
	GLsizei written = 0;

	glGetShaderiv(_vertexShaderObject_cylinder, GL_COMPILE_STATUS, &iShaderCompilationStatus);

	if (iShaderCompilationStatus == GL_FALSE)
	{
		glGetShaderiv(_vertexShaderObject_cylinder, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			szInfoLog = (char*)malloc(infoLogLength);

			if (szInfoLog != NULL)
			{

				glGetShaderInfoLog(_vertexShaderObject_cylinder, infoLogLength, &written, szInfoLog);

				SAFE_LOG("RollingCylinder Vertex Shader Compilation Log : %s\n", szInfoLog)
					SAFE_FREE(szInfoLog);
				UnInitialize();
				exit(0);
			}
		}
	}


	//Create FRAGMENT SHADER OBJECT
	_fragmentShaderObject_cylinder = glCreateShader(GL_FRAGMENT_SHADER);

	//CREATE SOURCE CODE FOR FRAGMENT SHADER
	const GLchar *fragmentShaderSourceCode_cylinder =
		"#version 440 core"												\
		"\n"															\
		"in vec3 phong_ads_color;"										\
		"out vec4 FragColor;"											\
		"void main(void)"												\
		"{"																\
		"FragColor = vec4(phong_ads_color, 1.0);"											\
		"}";

	//BIND fragmentShaderSourceCode to gFragmentShaderObject
	glShaderSource(_fragmentShaderObject_cylinder, 1, (const GLchar **)&fragmentShaderSourceCode_cylinder, NULL);

	//COMPILE FRAGMENT SHADER
	glCompileShader(_fragmentShaderObject_cylinder);

	infoLogLength = 0;
	iShaderCompilationStatus = 0;
	szInfoLog = NULL;
	written = 0;

	glGetShaderiv(_fragmentShaderObject_cylinder, GL_COMPILE_STATUS, &iShaderCompilationStatus);
	if (iShaderCompilationStatus == GL_FALSE)
	{
		glGetShaderiv(_fragmentShaderObject_cylinder, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			szInfoLog = (char*)malloc(sizeof(infoLogLength));

			if (szInfoLog != NULL)
			{
				glGetShaderInfoLog(_fragmentShaderObject_cylinder, infoLogLength, &written, szInfoLog);

				SAFE_LOG("RollingCylinder Fragment Shader Compilation Log : %s\n", szInfoLog)
					SAFE_FREE(szInfoLog);
				UnInitialize();
				exit(0);
			}
		}
	}

	// *** SHADER PROGRAM ****//
	//CREATE SHADER PROGRAM OBJECT
	_shaderProgramObject_cylinder = glCreateProgram();

	//ATTACH VERTEX SHADER PROGRAM TO SHADER PROGRAM
	glAttachShader(_shaderProgramObject_cylinder, _vertexShaderObject_cylinder);

	//ATTACH FRAGMENT SHADER PROGRAM TO SHADER PROGRAM
	glAttachShader(_shaderProgramObject_cylinder, _fragmentShaderObject_cylinder);

	//PRE-LINK BINDING OF SHADER PROGRAM OBJECT WITH VERTEX SHADER POSITION ATTRIBUTE
	glBindAttribLocation(_shaderProgramObject_cylinder, AMC_ATTRIBUTE_POSITION, "vPosition");
	glBindAttribLocation(_shaderProgramObject_cylinder, AMC_ATTRIBUTE_NORMAL, "vNormal");

	//LINK THE SHADER
	glLinkProgram(_shaderProgramObject_cylinder);

	infoLogLength = 0;
	iShaderCompilationStatus = 0;
	szInfoLog = NULL;
	written = 0;

	GLint iShaderProgramLinkStatus = 0;
	glGetProgramiv(_shaderProgramObject_cylinder, GL_LINK_STATUS, &iShaderProgramLinkStatus);
	if (iShaderProgramLinkStatus == GL_FALSE)
	{
		glGetProgramiv(_shaderProgramObject_cylinder, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			szInfoLog = (char*)malloc(sizeof(infoLogLength));
			if (szInfoLog != NULL)
			{

				glGetProgramInfoLog(_shaderProgramObject_cylinder, infoLogLength, &written, szInfoLog);

				SAFE_LOG("RollingCylinder Shader Program Link Log : %s \n", szInfoLog)
					SAFE_FREE(szInfoLog);
				UnInitialize();
				exit(0);
			}

		}
	}

	model_matrix_uniform = glGetUniformLocation(_shaderProgramObject_cylinder, "u_model_matrix");
	view_matrix_uniform = glGetUniformLocation(_shaderProgramObject_cylinder, "u_view_matrix");
	projection_matrix_uniform = glGetUniformLocation(_shaderProgramObject_cylinder, "u_projection_matrix");

	L_KeyPressed_uniform = glGetUniformLocation(_shaderProgramObject_cylinder, "u_lighting_enabled");

	La_uniform = glGetUniformLocation(_shaderProgramObject_cylinder, "u_La");
	Ld_uniform = glGetUniformLocation(_shaderProgramObject_cylinder, "u_Ld");
	Ls_uniform = glGetUniformLocation(_shaderProgramObject_cylinder, "u_Ls");

	light_position_uniform = glGetUniformLocation(_shaderProgramObject_cylinder, "u_light_position");

	Ka_uniform = glGetUniformLocation(_shaderProgramObject_cylinder, "u_Ka");
	Kd_uniform = glGetUniformLocation(_shaderProgramObject_cylinder, "u_Kd");
	Ks_uniform = glGetUniformLocation(_shaderProgramObject_cylinder, "u_Ks");
	material_shininess_uniform = glGetUniformLocation(_shaderProgramObject_cylinder, "u_material_shininess");

	makeSphere(_radius, _height, 10, 10);


	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
	glClearDepth(1.0f);

	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LEQUAL);

	glShadeModel(GL_SMOOTH);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_CULL_FACE); /*Turning oFF cull , as we are doing animation , and so need to paint the back of object when rotating*/

	_perspectiveProjectionMatrix = mat4::identity();

}


void Rushabh::RollingCylinder::Update()
{
	_angle += SPEED_ROLLING_CYLINDER;
	if (_angle > 360.0f)
		_angle = 0.0f;
}

void Rushabh::RollingCylinder::ReSize(int width, int height, struct ResizeAttributes attributes)
{
	if (height == 0)
		height = 1;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	_perspectiveProjectionMatrix = vmath::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 1000.0f);

}

void Rushabh::RollingCylinder::Render(HDC hdc, struct Attributes attributes)
{
	//START USING SHADER OBJECT	
	glDisable(GL_CULL_FACE); /*Turning oFF cull , as we are doing animation , and so need to paint the back of object when rotating*/

	glUseProgram(_shaderProgramObject_cylinder);


	if (true == true)
	{
		glUniform1i(L_KeyPressed_uniform, 1);

		glUniform3fv(La_uniform, 1, lightAmbient);
		glUniform3fv(Ld_uniform, 1, lightDiffuse);
		glUniform3fv(Ls_uniform, 1, lightSpecular);
		glUniform4fv(light_position_uniform, 1, lightPosition);

		glUniform3fv(Ka_uniform, 1, material_ambient);
		glUniform3fv(Kd_uniform, 1, material_diffuse);
		glUniform3fv(Ks_uniform, 1, material_specular);
		glUniform1f(material_shininess_uniform, material_shininess);
	}
	else
	{
		glUniform1i(L_KeyPressed_uniform, 0);
	}

	mat4 modelMatrix = mat4::identity();
	mat4 viewMatrix = mat4::identity();

	modelMatrix = translate(
		attributes.translateCoords[SCENE_CYLINDER_TRANS][0] + attributes.translateCoords[SCENE_AIRPORT_MODEL][0] + _radius, 
		attributes.translateCoords[SCENE_AIRPORT_MODEL][1] + TRANS_Y_ROLLINGCYLINDER + _radius + 0.1f,
		attributes.translateCoords[SCENE_AIRPORT_MODEL][2] - _height/2);
	//modelMatrix = modelMatrix * rotate(
	//	90.0f, 
	//	0.0f, 
	//	0.0f);

	modelMatrix = modelMatrix * rotate(
		attributes.rotateCoords[SCENE_AIRPORT_MODEL][0],
		attributes.rotateCoords[SCENE_AIRPORT_MODEL][1],
		attributes.rotateCoords[SCENE_AIRPORT_MODEL][2]);
	modelMatrix = modelMatrix * rotate(_angle, 0.0f, 0.0f, -1.0f);

	glUniformMatrix4fv(model_matrix_uniform, 1, GL_FALSE, modelMatrix);
	glUniformMatrix4fv(view_matrix_uniform, 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(projection_matrix_uniform, 1, GL_FALSE, _perspectiveProjectionMatrix);

	draw();

	//STOP USING SHADER
	glUseProgram(0);
}

void Rushabh::RollingCylinder::SceneTransition()
{
}

void Rushabh::RollingCylinder::UnInitialize()
{
	//DETACH THE FRAGMENT SHADER OBJECT
	glDetachShader(_shaderProgramObject_cylinder, _fragmentShaderObject_cylinder);

	//DETACH THE VERTEX SHADER OBJECT
	glDetachShader(_shaderProgramObject_cylinder, _vertexShaderObject_cylinder);


	//DELETE VERTEX SHADER OBJECT
	glDeleteShader(_vertexShaderObject_cylinder);
	_vertexShaderObject_cylinder = 0;

	//DELETE FRAGMENT SHADER OBJECT
	glDeleteShader(_fragmentShaderObject_cylinder);
	_fragmentShaderObject_cylinder = 0;

	//DELETE SHADER PROGRAM OBJECT
	glDeleteProgram(_shaderProgramObject_cylinder);
	_shaderProgramObject_cylinder = 0;

	//UNLINK THE PROGRAM
	glUseProgram(0);
}

void Rushabh::RollingCylinder::allocate(int numIndices)
{
	maxElements = numIndices;
	numElements = 0;
	numVertices = 0;

	iNumIndices = numIndices / 3;

	elements = (short *)malloc(iNumIndices * 3 * sizeof(unsigned short)); // 3 is x,y,z and 2 is sizeof short
	verts = (float *)malloc(iNumIndices * 3 * sizeof(float)); // 3 is x,y,z and 4 is sizeof float
	norms = (float *)malloc(iNumIndices * 3 * sizeof(float)); // 3 is x,y,z and 4 is sizeof float
	texCoords = (float *)malloc(iNumIndices * 2 * sizeof(float)); // 2 is s,t and 4 is sizeof float
}


bool Rushabh::RollingCylinder::isFoundIdentical(float val1, float val2, float diff)
{
	if (fabs(val1 - val2) < diff)
		return(true);
	else
		return(false);
}



void Rushabh::RollingCylinder::prepareToDraw()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// vbo for position
	glGenBuffers(1, &vbo_position);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_position);
	glBufferData(GL_ARRAY_BUFFER, iNumIndices * 3 * sizeof(float), verts, GL_STATIC_DRAW);
	glVertexAttribPointer(AMC_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// vbo for normals

	glGenBuffers(1, &vbo_normal);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_normal);
	glBufferData(GL_ARRAY_BUFFER, iNumIndices * 3 * sizeof(float), norms, GL_STATIC_DRAW);
	glVertexAttribPointer(AMC_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// vbo for texture
	glGenBuffers(1, &vbo_texture);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_texture);
	glBufferData(GL_ARRAY_BUFFER, iNumIndices * 2 * sizeof(float), texCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(AMC_ATTRIBUTE_TEXTURE0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_TEXTURE0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// vbo for index
	glGenBuffers(1, &vbo_index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, iNumIndices * 3 * sizeof(unsigned short), elements, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Rushabh::RollingCylinder::draw()
{
	glBindVertexArray(vao);

	// draw

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_index);
	glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_SHORT, 0);
	//glDrawElements(GL_LINES, numElements, GL_UNSIGNED_SHORT, 0);

	// unbind vao
	glBindVertexArray(0);
}

int Rushabh::RollingCylinder::getIndexCount()
{
	return(numElements);
}

int Rushabh::RollingCylinder::getVertexCount()
{
	// code
	return(numVertices);
}

void Rushabh::RollingCylinder::normalizeVector(float *v)
{
	// code

	// square the vector length

	float squaredVectorLength = (v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2]);

	// get square root of above 'squared vector length'
	float squareRootOfSquaredVectorLength = (float)sqrt(squaredVectorLength);

	// scale the vector with 1/squareRootOfSquaredVectorLength
	v[0] = v[0] * 1.0f / squareRootOfSquaredVectorLength;
	v[1] = v[1] * 1.0f / squareRootOfSquaredVectorLength;
	v[2] = v[2] * 1.0f / squareRootOfSquaredVectorLength;
}


void Rushabh::RollingCylinder::deallocate()
{
	// code
	if (vao)
	{
		glDeleteVertexArrays(1, &vao);
		vao = 0;
	}

	if (vbo_index)
	{
		glDeleteBuffers(1, &vbo_index);
		vbo_index = 0;
	}

	if (vbo_texture)
	{
		glDeleteBuffers(1, &vbo_texture);
		vbo_texture = 0;
	}

	if (vbo_normal)
	{
		glDeleteBuffers(1, &vbo_normal);
		vbo_normal = 0;
	}

	if (vbo_position)
	{
		glDeleteBuffers(1, &vbo_position);
		vbo_position = 0;
	}
}

void Rushabh::RollingCylinder::addTriangle(float single_vertex[4][3], float single_normal[4][3], float single_texture[4][2])
{
	const float diff = 0.00001f;
	int i, j;
	// code
	// normals should be of unit length
	normalizeVector(single_normal[0]);
	normalizeVector(single_normal[1]);
	normalizeVector(single_normal[2]);

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < numVertices; j++) //for the first ever iteration of 'j', numVertices will be 0 because of it's initialization in the parameterized constructor
		{
			if (isFoundIdentical(verts[j * 3], single_vertex[i][0], diff) &&
				isFoundIdentical(verts[(j * 3) + 1], single_vertex[i][1], diff) &&
				isFoundIdentical(verts[(j * 3) + 2], single_vertex[i][2], diff) &&

				isFoundIdentical(norms[j * 3], single_normal[i][0], diff) &&
				isFoundIdentical(norms[(j * 3) + 1], single_normal[i][1], diff) &&
				isFoundIdentical(norms[(j * 3) + 2], single_normal[i][2], diff) &&

				isFoundIdentical(texCoords[j * 2], single_texture[i][0], diff) &&
				isFoundIdentical(texCoords[(j * 2) + 1], single_texture[i][1], diff))
			{
				elements[numElements] = j;
				numElements++;
				break;
			}
		}

		//If the single vertex, normal and texture do not match with the given, then add the corressponding triangle to the end of the list
		if (j == numVertices && numVertices < maxElements && numElements < maxElements)
		{
			verts[numVertices * 3] = single_vertex[i][0];
			verts[(numVertices * 3) + 1] = single_vertex[i][1];
			verts[(numVertices * 3) + 2] = single_vertex[i][2];

			norms[numVertices * 3] = single_normal[i][0];
			norms[(numVertices * 3) + 1] = single_normal[i][1];
			norms[(numVertices * 3) + 2] = single_normal[i][2];

			texCoords[numVertices * 2] = single_texture[i][0];
			texCoords[(numVertices * 2) + 1] = single_texture[i][1];

			elements[numElements] = numVertices; //adding the index to the end of the list of elements/indices
			numElements++; //incrementing the 'end' of the list
			numVertices++; //incrementing coun of vertices
		}
	}
}

void Rushabh::RollingCylinder::makeSphere(float fRadius, float fHeight, int iSlices, int iStacks)
{
	// code
	float drho = VDG_PI / iStacks;
	float dtheta = 2.0f * (VDG_PI) / (iSlices);
	float ds = 1.0f / (iSlices);
	float dt = 1.0f / (iStacks);
	float t = 1.0f;
	float s = 0.0f;
	int i = 0;
	int j = 0;

	allocate(iSlices * iStacks * 6);

	for (i = 0; i < iStacks; i++)
	{
		float rho = (i * drho);
		float srho = (float)(sin(rho));
		float crho = (float)(cos(rho));
		float srhodrho = (float)(sin(rho + drho));
		float crhodrho = (float)(cos(rho + drho));
		float zCurrent = ((float)i / iStacks) * (fHeight);
		// Many sources of OpenGL sphere drawing code uses a triangle fan
		// for the caps of the sphere. This however introduces texturing
		// artifacts at the poles on some OpenGL implementations
		s = 0.0;

		float vertex[4][3] = { 0 };
		float normal[4][3] = { 0 };
		float texture[4][2] = { 0 };


		for (j = 0; j < iSlices; j++)
		{
			float theta = (j == iSlices) ? 0.0f : j * dtheta;
			float stheta = (float)(-sin(theta));
			float ctheta = (float)(cos(theta));

			float x = stheta * 1.0f;
			float y = ctheta * 1.0f;
			float z = zCurrent;
			float dist = (float)sqrt(x*x + y*y);

			texture[0][0] = s;
			texture[0][1] = t;
			normal[0][0] = x / dist;
			normal[0][1] = y / dist;
			normal[0][2] = 0.0f;
			vertex[0][0] = x * fRadius;
			vertex[0][1] = y * fRadius;
			vertex[0][2] = z;

			x = stheta * 1.0f;
			y = ctheta * 1.0f;
			z = zCurrent + (1.0f / iStacks)*fHeight;

			texture[1][0] = s;
			texture[1][1] = t - dt;
			normal[1][0] = x / dist;
			normal[1][1] = y / dist;
			normal[1][2] = 0.0f;
			vertex[1][0] = x * fRadius;
			vertex[1][1] = y * fRadius;
			vertex[1][2] = z;

			theta = ((j + 1) == iSlices) ? 0.0f : (j + 1) * dtheta;
			stheta = (float)(-sin(theta));
			ctheta = (float)(cos(theta));


			x = stheta * 1.0f;
			y = ctheta * 1.0f;
			z = zCurrent;

			s += ds;
			texture[2][0] = s;
			texture[2][1] = t;
			normal[2][0] = x / dist;
			normal[2][1] = y / dist;
			normal[2][2] = 0.0f;
			vertex[2][0] = x * fRadius;
			vertex[2][1] = y * fRadius;
			vertex[2][2] = z;

			x = stheta * 1.0f;
			y = ctheta * 1.0f;
			z = zCurrent + (1.0f / iStacks)*fHeight;

			texture[3][0] = s;
			texture[3][1] = t - dt;
			normal[3][0] = x / dist;
			normal[3][1] = y / dist;
			normal[3][2] = 0.0f;
			vertex[3][0] = x * fRadius;
			vertex[3][1] = y * fRadius;
			vertex[3][2] = z;

			addTriangle(vertex, normal, texture);

			// Rearrange for next triangle
			vertex[0][0] = vertex[1][0];
			vertex[0][1] = vertex[1][1];
			vertex[0][2] = vertex[1][2];
			normal[0][0] = normal[1][0];
			normal[0][1] = normal[1][1];
			normal[0][2] = normal[1][2];
			texture[0][0] = texture[1][0];
			texture[0][1] = texture[1][1];

			vertex[1][0] = vertex[3][0];
			vertex[1][1] = vertex[3][1];
			vertex[1][2] = vertex[3][2];
			normal[1][0] = normal[3][0];
			normal[1][1] = normal[3][1];
			normal[1][2] = normal[3][2];
			texture[1][0] = texture[3][0];
			texture[1][1] = texture[3][1];

			addTriangle(vertex, normal, texture);
		}
		t -= dt;
	}

	prepareToDraw();
}
