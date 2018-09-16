/*
* @author: Rushabh Parakh
* @mailto: rgparakh@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/

#include "PhotoRoom.h"

Rushabh::PhotoRoom::PhotoRoom()
{
	
}

Rushabh::PhotoRoom::~PhotoRoom()
{
	UnInitialize();
}	

BOOL Rushabh::PhotoRoom::SceneHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	return 0;
}

void Rushabh::PhotoRoom::Initialize()
{
	//code
	transX = 0.0f;
	transY = 0.0f;
	transZ = 0.0f;

	//CREAT VERTEXT SHADER OBJECT
	_vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

	//CREATE SOURCE CODE FOR VERTEX SHADER OBJECT
	const GLchar *vertexShaderSourceCode =
		"#version 430 core" \
		"\n" \
		"in vec4 vPosition;" \
		"in vec3 vNormal;" \
		"in vec2 vTexture0_Coord;" \
		"uniform mat4 u_model_matrix;" \
		"uniform mat4 u_view_matrix;" \
		"uniform mat4 u_projection_matrix;" \
		"uniform int u_LKeyPressed;" \
		"uniform vec4 u_light_position1;" \
		"uniform vec4 u_light_position2;" \
		"out vec3 transformed_normals;" \
		"out vec3 light_direction1;"\
		"out vec3 light_direction2;"\
		"out vec3 viewer_vector;"\
		"out vec2 out_texture0_coord;"\
		"out vec3 FragPos;"\
		"void main (void)" \
		"{" \
		"if(u_LKeyPressed == 1)" \
		"{" \
		"vec4 eyeCoordinates =u_view_matrix * u_model_matrix * vPosition;" \
		"transformed_normals = mat3(u_view_matrix * u_model_matrix)*vNormal;" \
		"light_direction1 = vec3(u_light_position1) - eyeCoordinates.xyz;" \
		"light_direction2 = vec3(u_light_position2) - eyeCoordinates.xyz;" \
		"viewer_vector = -eyeCoordinates.xyz;" \
		"FragPos = vec3(u_model_matrix * vPosition);"
		"}" \
		"out_texture0_coord = vTexture0_Coord;" \
		"gl_Position = u_projection_matrix * u_view_matrix * u_model_matrix *vPosition;" \
		"}";

	//BIND vertexShaderSourcecode CODE TO gVertexShaderObject
	glShaderSource(_vertexShaderObject, 1, (const GLchar **)&vertexShaderSourceCode, NULL);

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

				SAFE_LOG("PhotoRoom Vertex Shader Compilation Log : %s\n", szInfoLog)
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
		"in vec3 diffuse_light;"
		"in vec2 out_texture0_coord;"
		"in vec3 transformed_normals;"\
		"in vec3 light_direction1;"\
		"in vec3 light_direction2;"\
		"in vec3 viewer_vector;"\
		"in vec3 FragPos;"\

		"uniform sampler2D u_texture0_sampler;" \
		"uniform vec3 u_La;" \
		"uniform vec3 u_Ld;" \
		"uniform vec3 u_Ls;" \
		"uniform vec3 u_Ka;" \
		"uniform vec3 u_Kd;" \
		"uniform vec3 u_Ks;" \
		"uniform float u_material_shininess;" \
		"uniform int u_LKeyPressed;"
		"uniform int u_numSpotLights;"\
		"uniform vec3 u_viewPos;" \
		
		"struct Material {"\
		"vec3 u_Ka;"\
		"vec3 u_Kd;"\
		"vec3 u_Ks;"\
		"float u_material_shininess;"\
		"};"\
		"uniform Material material;"

		"struct SpotLight {"\
		"vec3 u_light_position;"\
		"vec3 u_light_direction;"\
		"float cutOff;"\
		"float outerCutOff;"\
		"float constant;"\
		"float linear;"\
		"float quadratic;"\
		"vec3 u_La;"\
		"vec3 u_Ld;"\
		"vec3 u_Ls;"\
		"};"\
		"uniform SpotLight spotLight[25];"\

		"out vec4 FragColor;" \

		"vec3 CalcSpotLight(SpotLight light, vec3 normal)"\
		"{"\
		"vec3 lightDir = normalize(light.u_light_position - FragPos);"\
		"float tn_dot_ld = max(dot(normal, lightDir), 0.0);"\
		"vec3 diffuse = light.u_Ld * tn_dot_ld * texture(u_texture0_sampler,out_texture0_coord).rgb;" \
		"vec3 view_direction = normalize(u_viewPos - FragPos);" \

		// material_Specularr shading
		"vec3 reflectDir = reflect(-lightDir, normal);"\
		"float spec = pow(max(dot(view_direction, reflectDir), 0.0), material.u_material_shininess);"\
		"vec3 specular = light.u_Ls * spec * texture(u_texture0_sampler,out_texture0_coord).rgb;"\

		// attenuation
		"float distance = length(light.u_light_position - FragPos);"\
		"float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));"\
		// spotlight intensity
		"float theta = dot(lightDir, normalize(-light.u_light_direction)); "\
		"float epsilon = light.cutOff - light.outerCutOff;"\
		"float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);"\
		// combine results
		"vec3 ambient = light.u_La * texture(u_texture0_sampler,out_texture0_coord).rgb;"\
		"ambient *=  intensity;"\
		"diffuse *= intensity;"\
		"specular *= intensity;"\
		"return (ambient + diffuse + specular);"\
		"}"\

		"void main (void)" \
		"{" \
		"vec3 result = vec3(0.0,0.0,0.0);"
		"vec3 phong_ads_color;" \
		"if(u_LKeyPressed == 1)"\
		"{" \
		"vec3 normalized_transformed_normals = normalize(transformed_normals);"\

		"vec3 normalized_light_direction1 = normalize(light_direction1);"\
		"vec3 normalized_light_direction2 = normalize(light_direction2);"\
		
		"vec3 normalized_viewer_vector = normalize(viewer_vector);"\
		
		"vec3 ambient1 = u_La * u_Ka;"\
		"float tn_dot_ld1 = max(dot(normalized_transformed_normals , normalized_light_direction1),0.0);"\
		"vec3 diffuse1 = u_Ld * u_Kd * tn_dot_ld1;"\
		"vec3 reflection_vector1 = reflect(-normalized_light_direction1,normalized_transformed_normals);"\
		"vec3 specular1 = u_Ls * u_Ks *pow(max(dot(reflection_vector1,normalized_viewer_vector),0.0),u_material_shininess);"\

		"vec3 ambient2 = u_La * u_Ka;"\
		"float tn_dot_ld2 = max(dot(normalized_transformed_normals , normalized_light_direction2),0.0);"\
		"vec3 diffuse2 = u_Ld * u_Kd * tn_dot_ld2;"\
		"vec3 reflection_vector2 = reflect(-normalized_light_direction2,normalized_transformed_normals);"\
		"vec3 specular2 = u_Ls * u_Ks *pow(max(dot(reflection_vector2,normalized_viewer_vector),0.0),u_material_shininess);"\

		"vec3 ambient = ambient1 + ambient2 ;" \
		"vec3 diffuse = diffuse1 + diffuse2 ;" \
		"vec3 specular = specular1 + specular2 ;" \

		"phong_ads_color = ambient + diffuse + specular;"\
		"for(int i=0;i<u_numSpotLights;i++){"
		"result += CalcSpotLight(spotLight[i], normalized_transformed_normals);"
		"}"\
		"}"\
		"else"\
		"{"\
		"phong_ads_color = vec3(1.0,1.0,1.0);"\
		"}"\
		"FragColor = vec4(result + phong_ads_color,1.0) * texture(u_texture0_sampler,out_texture0_coord);" \
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

				SAFE_LOG("PhotoRoom Fragment Shader Compilation Log : %s\n", szInfoLog)
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

				SAFE_LOG("PhotoRoom Shader Program Link Log : %s \n", szInfoLog)
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

	_Ka_Uniform = glGetUniformLocation(_shaderProgramObject, "u_Ka");
	_Kd_Uniform = glGetUniformLocation(_shaderProgramObject, "u_Kd");
	_Ks_Uniform = glGetUniformLocation(_shaderProgramObject, "u_Ks");
	_Material_shininess_uniform = glGetUniformLocation(_shaderProgramObject, "u_material_shininess");

	_LightPositionUniform1 = glGetUniformLocation(_shaderProgramObject, "u_light_position1");
	_LightPositionUniform2 = glGetUniformLocation(_shaderProgramObject, "u_light_position2");

	_Ld_Uniform = glGetUniformLocation(_shaderProgramObject, "u_Ld");
	_La_uniform = glGetUniformLocation(_shaderProgramObject, "u_La");
	_La_uniform = glGetUniformLocation(_shaderProgramObject, "u_Ls");
	_LKeyPressedUniform = glGetUniformLocation(_shaderProgramObject, "u_LKeyPressed");
	_numSpotLightUniform = glGetUniformLocation(_shaderProgramObject, "u_numSpotLights");

	_Texture_smapler_uniform = glGetUniformLocation(_shaderProgramObject, "u_texture0_sampler");
	_viewrPositionUniform = glGetUniformLocation(_shaderProgramObject, "u_viewPos");

	_material_Kd = glGetUniformLocation(_shaderProgramObject, "material.u_Kd");
	_material_Ka = glGetUniformLocation(_shaderProgramObject, "material.u_Ka");
	_material_Ks = glGetUniformLocation(_shaderProgramObject, "material.u_Ks");
	_material_shininess_uniform = glGetUniformLocation(_shaderProgramObject, "material.u_material_shininess");

	char uniformText[50];
	for (int j = 0; j < 25; j++)
	{
		sprintf_s(uniformText, 50, "spotLight[%d].u_La", j);
		_SpotLightLaUniform[j] = glGetUniformLocation(_shaderProgramObject, uniformText);
		
		sprintf_s(uniformText, 50, "spotLight[%d].u_Ld", j);
		_SpotLightLdUniform[j] = glGetUniformLocation(_shaderProgramObject, uniformText);
		
		sprintf_s(uniformText, 50, "spotLight[%d].u_Ls", j);
		_SpotLightLsUniform[j] = glGetUniformLocation(_shaderProgramObject, uniformText);

		sprintf_s(uniformText, 50, "spotLight[%d].constant", j);
		_SpotLightConstantUniform[j] = glGetUniformLocation(_shaderProgramObject, uniformText);

		sprintf_s(uniformText, 50, "spotLight[%d].linear", j);
		_SpotLightLinearUniform[j] = glGetUniformLocation(_shaderProgramObject, uniformText);
		
		sprintf_s(uniformText, 50, "spotLight[%d].quadratic", j);
		_SpotLightQuadraticUniform[j] = glGetUniformLocation(_shaderProgramObject, uniformText);

		sprintf_s(uniformText, 50, "spotLight[%d].cutOff", j);
		_SpotLightCutOffUniform[j] = glGetUniformLocation(_shaderProgramObject, uniformText);
		
		sprintf_s(uniformText, 50, "spotLight[%d].outerCutOff", j);
		_SpotLightOuterCutOffUniform[j] = glGetUniformLocation(_shaderProgramObject, uniformText);
		
		sprintf_s(uniformText, 50, "spotLight[%d].u_light_position", j);
		_SpotLightLightPositionUniform[j] = glGetUniformLocation(_shaderProgramObject, uniformText);
		
		sprintf_s(uniformText, 50, "spotLight[%d].u_light_direction", j);
		_SpotLightLightDirectionUniform[j] = glGetUniformLocation(_shaderProgramObject, uniformText);

	}
	
	float w = ROOM_WIDTH; // X 
	float h = ROOM_HEIGHT; // Y
	float l = ROOM_LENGTH; // Z

	const GLfloat cubeVertices[] =
	{
		w, h, l, //front
		w, -h, l,
		-w, -h, l,
		-w, h, l,

		w, h, -l, //back
		w, -h, -l,
		-w, -h, -l,
		-w, h, -l,

		w, h, l, //right
		w, h, -l,
		w, -h, -l,
		w, -h, l,

		-w, h, l, //left
		-w, h, -l,
		-w, -h, -l,
		-w, -h, l,

		w, h, l, //top
		-w, h, l,
		-w, h, -l,
		w, h, -l,

		w, -h, l, //bottom
		-w, -h, l,
		-w, -h, -l,
		w, -h, -l
	};

	w = ROOM_WIDTH; // X 
	h = ROOM_HEIGHT / 3; // Y
	l = ROOM_LENGTH; // Z


	const GLfloat horizontalQuadVertices[] =
	{
		-w, h, l, //left
		-w, h, -l,
		-w, -h, -l,
		-w, -h, l,
	};

	w = ROOM_WIDTH; // X 
	h = ROOM_HEIGHT / 2; // Y
	l = ROOM_LENGTH / NUM_VERTICAL_CUBE - 2 * VERTICAL_CUBE_LENGTH; // Z

	const GLfloat photoQuadVertices[] =
	{
		-w, h, l, //left
		-w, h, -l,
		-w, -h, -l,
		-w, -h, l,
	};

	w = HORIZONTAL_CUBE_WIDTH; // X 
	h = HORIZONTAL_CUBE_HEIGHT; // Y
	l = HORIZONTAL_CUBE_LENGTH; // Z

	const GLfloat horizontalCubeVertices[] =
	{
		w, h, l, //front
		w, -h, l,
		-w, -h, l,
		-w, h, l,

		w, h, -l, //back
		w, -h, -l,
		-w, -h, -l,
		-w, h, -l,

		w, h, l, //right
		w, h, -l,
		w, -h, -l,
		w, -h, l,

		-w, h, l, //left
		-w, h, -l,
		-w, -h, -l,
		-w, -h, l,

		w, h, l, //top
		-w, h, l,
		-w, h, -l,
		w, h, -l,

		w, -h, l, //bottom
		-w, -h, l,
		-w, -h, -l,
		w, -h, -l
	};

	w = VERTICAL_CUBE_WIDTH; // X 
	h = VERTICAL_CUBE_HEIGHT; // Y
	l = VERTICAL_CUBE_LENGTH; // Z

	const GLfloat verticalCubeVertices[] =
	{
		w, h, l, //front
		w, -h, l,
		-w, -h, l,
		-w, h, l,

		w, h, -l, //back
		w, -h, -l,
		-w, -h, -l,
		-w, h, -l,

		w, h, l, //right
		w, h, -l,
		w, -h, -l,
		w, -h, l,

		-w, h, l, //left
		-w, h, -l,
		-w, -h, -l,
		-w, -h, l,

		w, h, l, //top
		-w, h, l,
		-w, h, -l,
		w, h, -l,

		w, -h, l, //bottom
		-w, -h, l,
		-w, -h, -l,
		w, -h, -l
	};
	const GLfloat cubeTexCoords[] =
	{
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,

		0.0f, 0.0f,
		0.0f, 20.0f,
		5.0f, 20.0f,
		5.0f, 0.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,

		0.0f, 0.0f,
		0.0f, 10.0f,
		10.0f, 10.0f,
		10.0f, 0.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 4.0f,
		0.0f, 4.0f,
	};

	const GLfloat cubeNormals[] =
	{
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
		1.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};


	const GLfloat horizontalQuadTexCoords[] =
	{
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
	};

	const GLfloat horizontalQuadNormals[] =
	{
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
	};

	glGenVertexArrays(1, &gVao_cube);
	glBindVertexArray(gVao_cube);

	glGenBuffers(1, &gVbo_cube_position);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_cube_position);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(AMC_ATTRIBUTE_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_VERTEX);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &gVbo_cube_normal);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_cube_normal);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeNormals), cubeNormals, GL_STATIC_DRAW);

	glVertexAttribPointer(AMC_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_NORMAL);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &gVbo_cube_texture);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_cube_texture);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeTexCoords), cubeTexCoords, GL_STATIC_DRAW);

	glVertexAttribPointer(AMC_ATTRIBUTE_TEXTURE0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_TEXTURE0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glGenVertexArrays(1, &gVao_horizontal_Quad);
	glBindVertexArray(gVao_horizontal_Quad);

	glGenBuffers(1, &gVbo_cube_position);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_cube_position);
	glBufferData(GL_ARRAY_BUFFER, sizeof(horizontalQuadVertices), horizontalQuadVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(AMC_ATTRIBUTE_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_VERTEX);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &gVbo_cube_normal);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_cube_normal);
	glBufferData(GL_ARRAY_BUFFER, sizeof(horizontalQuadNormals), horizontalQuadNormals, GL_STATIC_DRAW);

	glVertexAttribPointer(AMC_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_NORMAL);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &gVbo_cube_texture);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_cube_texture);
	glBufferData(GL_ARRAY_BUFFER, sizeof(horizontalQuadTexCoords), horizontalQuadTexCoords, GL_STATIC_DRAW);

	glVertexAttribPointer(AMC_ATTRIBUTE_TEXTURE0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_TEXTURE0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glGenVertexArrays(1, &gVao_photo_Quad);
	glBindVertexArray(gVao_photo_Quad);

	glGenBuffers(1, &gVbo_cube_position);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_cube_position);
	glBufferData(GL_ARRAY_BUFFER, sizeof(photoQuadVertices), photoQuadVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(AMC_ATTRIBUTE_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_VERTEX);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &gVbo_cube_texture);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_cube_texture);
	glBufferData(GL_ARRAY_BUFFER, sizeof(horizontalQuadTexCoords), horizontalQuadTexCoords, GL_STATIC_DRAW);

	glVertexAttribPointer(AMC_ATTRIBUTE_TEXTURE0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_TEXTURE0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &gVbo_cube_normal);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_cube_normal);
	glBufferData(GL_ARRAY_BUFFER, sizeof(horizontalQuadNormals), horizontalQuadNormals, GL_STATIC_DRAW);

	glVertexAttribPointer(AMC_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_NORMAL);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0);


	glGenVertexArrays(1, &gVao_horizontal_cube);
	glBindVertexArray(gVao_horizontal_cube);

	glGenBuffers(1, &gVbo_cube_position);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_cube_position);
	glBufferData(GL_ARRAY_BUFFER, sizeof(horizontalCubeVertices), horizontalCubeVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(AMC_ATTRIBUTE_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_VERTEX);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &gVbo_cube_normal);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_cube_normal);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeNormals), cubeNormals, GL_STATIC_DRAW);

	glVertexAttribPointer(AMC_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_NORMAL);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glGenBuffers(1, &gVbo_cube_texture);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_cube_texture);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeTexCoords), cubeTexCoords, GL_STATIC_DRAW);

	glVertexAttribPointer(AMC_ATTRIBUTE_TEXTURE0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_TEXTURE0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glGenVertexArrays(1, &gVao_vertical_cube);
	glBindVertexArray(gVao_vertical_cube);

	glGenBuffers(1, &gVbo_cube_position);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_cube_position);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticalCubeVertices), verticalCubeVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(AMC_ATTRIBUTE_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_VERTEX);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &gVbo_cube_normal);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_cube_normal);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeNormals), cubeNormals, GL_STATIC_DRAW);
	
	glVertexAttribPointer(AMC_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_NORMAL);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glGenBuffers(1, &gVbo_cube_texture);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_cube_texture);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeTexCoords), cubeTexCoords, GL_STATIC_DRAW);

	glVertexAttribPointer(AMC_ATTRIBUTE_TEXTURE0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_TEXTURE0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	//clear color
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//shade model
	glShadeModel(GL_SMOOTH);
	//depth
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	LoadGLTextures(&gTexture_Carpet, MAKEINTRESOURCE(ID_BITMAP_CARPET));
	LoadGLTextures(&gTexture_Wood, MAKEINTRESOURCE(ID_BITMAP_WOOD));
	LoadGLTextures(&gTexture_Sides, MAKEINTRESOURCE(ID_BITMAP_SIDES));
	LoadGLTextures(&gTexture_Cieling, MAKEINTRESOURCE(ID_BITMAP_CIELING));
	LoadGLTextures(&gTexture_Star, MAKEINTRESOURCE(ID_BITMAP_STAR));
	int photoId = ID_BITMAP_PHOTO_1;
	for (int i = 0; i < 25; i++)
	{
		LoadGLTextures(&gTexture_Photo[i], MAKEINTRESOURCE(photoId));
		photoId++;
	}
	_perspectiveProjectionMatrix = mat4::identity();


}

void Rushabh::PhotoRoom::Update()
{

}

void Rushabh::PhotoRoom::ReSize(int width, int height, struct ResizeAttributes attributes)
{
	if (height == 0)
		height = 1;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	_perspectiveProjectionMatrix = vmath::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 1000.0f);

}

int  Rushabh::PhotoRoom::LoadGLTextures(GLuint *texture, TCHAR imageResourceId[])
{
	//variable declarations
	HBITMAP hBitmap;
	BITMAP bmp;
	int iStatus = FALSE;

	//code 
	glGenTextures(1, texture); //1 image
	hBitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL), imageResourceId, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	if (hBitmap) //if bitmap exists ( means hBitmap is not null )
	{
		iStatus = TRUE;
		GetObject(hBitmap, sizeof(bmp), &bmp);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4); //pixel storage mode( word alignment/4 bytes ).
		glBindTexture(GL_TEXTURE_2D, *texture); //bind texture
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		//generate mipmapped texture ( 3 bytes, width, height & data from bmp)
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGB,
			bmp.bmWidth,
			bmp.bmHeight,
			0,
			GL_BGR_EXT,
			GL_UNSIGNED_BYTE,
			bmp.bmBits);

		glGenerateMipmap(GL_TEXTURE_2D);

		DeleteObject(hBitmap); //delete unwanted bitmap handle
	}
	return(iStatus);
}

void Rushabh::PhotoRoom::Render(HDC hdc, struct Attributes attributes)
{
	glDisable(GL_CULL_FACE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//start using opengl program object

	static GLfloat lightAmbientS1[4] = { 0.0f,0.0f,0.0f,1.0f };
	static GLfloat lightDiffuseS1[4] = { 1.0f,1.0f,1.0f,1.0f };
	static GLfloat lightSpecularS1[4] = { 1.0f,1.0f,1.0f,1.0f };
	static GLfloat lightPositionS1[4] = { 0.0f,6.0f,0.0f,1.0f };
	static GLfloat lightDirectionS1[4] = { 0.0f,-1.0f,0.0f,1.0f };


	
	glUseProgram(_shaderProgramObject);
	vec4 pos;
	gbLight = true;
	if (gbLight == true)
	{
		glUniform1i(_LKeyPressedUniform, 1);

		//light properties
		glUniform3fv(_La_uniform, 1, attributes.globalLight);
		glUniform3fv(_Ld_Uniform, 1, attributes.globalLight);
		glUniform3fv(_Ls_Uniform, 1, lightSpecular);
		glUniform4fv(_LightPositionUniform1, 1, lightPosition);
		glUniform4fv(_LightPositionUniform2, 1, lightPosition1);

		glUniform3fv(_Ka_Uniform, 1, material_Ambient);
		glUniform3fv(_Kd_Uniform, 1, material_Diffuse);
		glUniform3fv(_Ks_Uniform, 1, material_Specular);
		glUniform1f(_Material_shininess_uniform, material_shininess);

		glUniform3fv(_material_Kd, 1, mAmbient);
		glUniform3fv(_material_Ka, 1, mDiffuse);
		glUniform3fv(_material_Ks, 1, mSpecular);
		glUniform1f(_material_shininess_uniform, 50.0f);
		glUniform3fv(_viewrPositionUniform, 1, vec3(0.0f, 0.0f, 0.0f));

		glUniform1i(_numSpotLightUniform, attributes.numSpotLight);

		for (int k = 0; k < 25; k++)
		{

			glUniform3fv(_SpotLightLaUniform[k], 1, lightAmbientS1);
			glUniform3fv(_SpotLightLdUniform[k], 1, lightDiffuseS1);
			glUniform3fv(_SpotLightLsUniform[k], 1, lightSpecularS1);
			glUniform1f(_SpotLightConstantUniform[k], 1.0f);
			glUniform1f(_SpotLightLinearUniform[k], 0.09f);
			glUniform1f(_SpotLightQuadraticUniform[k], 0.032f);
			glUniform1f(_SpotLightCutOffUniform[k], cos(radians(attributes.lightRadius)));
			glUniform1f(_SpotLightOuterCutOffUniform[k], cos(radians(attributes.lightRadius + 3.0f)));
			lightPositionS1[0] = attributes.translateCoords[SCENE_PHOTO_ROOM][0] + attributes.translateCoords[SCENE_LIGHT_POS_4][0];
			lightPositionS1[1] = attributes.translateCoords[SCENE_PHOTO_ROOM][1] + attributes.translateCoords[SCENE_LIGHT_POS_4][1];
			lightPositionS1[2] = attributes.translateCoords[SCENE_PHOTO_ROOM][2] + attributes.translateCoords[SCENE_LIGHT_POS_4][2] + (k*(5.0f));

			glUniform3fv(_SpotLightLightPositionUniform[k], 1, lightPositionS1);

			lightDirectionS1[0] = -2.73f;
			lightDirectionS1[1] = -10.0f;
			lightDirectionS1[2] = 0.0f;
			glUniform3fv(_SpotLightLightDirectionUniform[k], 1, lightDirectionS1);

		}
	}
	else
	{
		glUniform1i(_LKeyPressedUniform, 0);
	}


	mat4 modelMatrix = mat4::identity();
	mat4 viewMatrix = mat4::identity();
	//mat4 modelViewProjectionMatrix = mat4::identity();
	mat4 scaleMatrix = mat4::identity();
	mat4 rotationMatrix = mat4::identity();
	mat4 globalTRMatrix = mat4::identity();


	/****** CUBE BLOCK STARTS ******/
	
	rotationMatrix = rotate(
		attributes.rotateCoords[SCENE_PHOTO_ROOM][0],
		attributes.rotateCoords[SCENE_PHOTO_ROOM][1],
		attributes.rotateCoords[SCENE_PHOTO_ROOM][2]
		);
	globalTRMatrix = translate(
		attributes.translateCoords[SCENE_PHOTO_ROOM][0], 
		attributes.translateCoords[SCENE_PHOTO_ROOM][1], 
		attributes.translateCoords[SCENE_PHOTO_ROOM][2]) * rotationMatrix;

	//	scaleMatrix = scale(0.75f, 0.75f, 0.75f);

	modelMatrix = globalTRMatrix;

	//modelViewProjectionMatrix = gPerspectiveProjectionMatrix * modelViewMatrix;

	glUniformMatrix4fv(_modelMatrixUniform, 1, GL_FALSE, modelMatrix);
	glUniformMatrix4fv(_ViewMatrixUniform, 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(_projectMatrixUniform, 1, GL_FALSE, _perspectiveProjectionMatrix);

	glBindVertexArray(gVao_cube);

	glActiveTexture(GL_TEXTURE0);

	
	glBindTexture(GL_TEXTURE_2D, gTexture_Sides);
	glUniform1i(_Texture_smapler_uniform, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glBindTexture(GL_TEXTURE_2D, gTexture_Star);
	glUniform1i(_Texture_smapler_uniform, 0);
	//glDrawArrays(GL_TRIANGLE_FAN, 4, 4);

	glBindTexture(GL_TEXTURE_2D, gTexture_Sides);
	glUniform1i(_Texture_smapler_uniform, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 4);

	glBindTexture(GL_TEXTURE_2D, gTexture_Cieling);
	glUniform1i(_Texture_smapler_uniform, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 16, 4);

	glBindTexture(GL_TEXTURE_2D, gTexture_Carpet);
	glUniform1i(_Texture_smapler_uniform, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 20, 4);

	glBindVertexArray(0);

	/****** CUBE BLOCK ENDS ******/


	/****** QUAD BLOCK STARTS ******/
	modelMatrix = mat4::identity();
	rotationMatrix = mat4::identity();
	viewMatrix = mat4::identity();
	//rotationMatrix = rotate(angleCube, 0.0f, 1.0f, 0.0f);
	modelMatrix = globalTRMatrix;

	modelMatrix = modelMatrix * translate(0.01f, -2 * ROOM_HEIGHT / 3, 0.0f);


	glUniformMatrix4fv(_modelMatrixUniform, 1, GL_FALSE, modelMatrix);
	glUniformMatrix4fv(_ViewMatrixUniform, 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(_projectMatrixUniform, 1, GL_FALSE, _perspectiveProjectionMatrix);

	glBindVertexArray(gVao_horizontal_Quad);

	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, gTexture_Wood);
	glUniform1i(_Texture_smapler_uniform, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glBindVertexArray(0);

	/****** QUAD BLOCK ENDS ******/


	float zPhotoQuad = -ROOM_LENGTH + (ROOM_LENGTH / NUM_VERTICAL_CUBE);
	float zPhotoGap = 2 * (ROOM_LENGTH / NUM_VERTICAL_CUBE);
	/****** PHOTO QUAD BLOCK STARTS ******/
	for (int i = 0; i < NUM_VERTICAL_CUBE; i++)
	{
		modelMatrix = mat4::identity();
		rotationMatrix = mat4::identity();
		viewMatrix = mat4::identity();

		//rotationMatrix = rotate(angleCube, 0.0f, 1.0f, 0.0f);
		modelMatrix = globalTRMatrix;

		modelMatrix = modelMatrix * translate(0.01f, ROOM_HEIGHT / 3, 0.0f + zPhotoQuad);

	
		glUniformMatrix4fv(_modelMatrixUniform, 1, GL_FALSE, modelMatrix);
		glUniformMatrix4fv(_ViewMatrixUniform, 1, GL_FALSE, viewMatrix);
		glUniformMatrix4fv(_projectMatrixUniform, 1, GL_FALSE, _perspectiveProjectionMatrix);

		glBindVertexArray(gVao_photo_Quad);

		glActiveTexture(GL_TEXTURE0);

		glBindTexture(GL_TEXTURE_2D, gTexture_Photo[NUM_VERTICAL_CUBE - 1 -i]);
		glUniform1i(_Texture_smapler_uniform, 0);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

		glBindVertexArray(0);
		zPhotoQuad += zPhotoGap;
	}
	/****** QUAD BLOCK ENDS ******/



	float verticalGap = ROOM_LENGTH * 2 / NUM_VERTICAL_CUBE;
	/****** CUBE BLOCK STARTS ******/
	float translateCoords[][3] =
	{
		-ROOM_WIDTH + HORIZONTAL_CUBE_WIDTH, -ROOM_HEIGHT / 3, 0.0f,
		-ROOM_WIDTH + HORIZONTAL_CUBE_WIDTH, ROOM_HEIGHT - HORIZONTAL_CUBE_HEIGHT, 0.0f,
	};
	for (int i = 0; i < 2; i++)
	{
		modelMatrix = mat4::identity();
		viewMatrix = mat4::identity();
		
		modelMatrix = globalTRMatrix * translate(translateCoords[i][0], translateCoords[i][1], translateCoords[i][2]);

		
		glUniformMatrix4fv(_modelMatrixUniform, 1, GL_FALSE, modelMatrix);
		glUniformMatrix4fv(_ViewMatrixUniform, 1, GL_FALSE, viewMatrix);
		glUniformMatrix4fv(_projectMatrixUniform, 1, GL_FALSE, _perspectiveProjectionMatrix);

		glBindVertexArray(gVao_horizontal_cube);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, gTexture_Wood);
		glUniform1i(_Texture_smapler_uniform, 0);

		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		glDrawArrays(GL_TRIANGLE_FAN, 4, 4);
		glDrawArrays(GL_TRIANGLE_FAN, 8, 4);
		glDrawArrays(GL_TRIANGLE_FAN, 12, 4);
		glDrawArrays(GL_TRIANGLE_FAN, 16, 4);
		glBindTexture(GL_TEXTURE_2D, gTexture_Carpet);
		glUniform1i(_Texture_smapler_uniform, 0);
		glDrawArrays(GL_TRIANGLE_FAN, 20, 4);

		glBindVertexArray(0);
	}
	/****** CUBE BLOCK ENDS ******/

	/****** CUBE BLOCK STARTS ******/
	float zVerticalCube = -ROOM_LENGTH;
	for (int i = 0; i < NUM_VERTICAL_CUBE; i++)
	{
		modelMatrix = mat4::identity();
		viewMatrix = mat4::identity();

		modelMatrix = globalTRMatrix * translate(-ROOM_WIDTH + HORIZONTAL_CUBE_WIDTH, -2 * VERTICAL_CUBE_HEIGHT - HORIZONTAL_CUBE_HEIGHT, zVerticalCube);
		
		glUniformMatrix4fv(_modelMatrixUniform, 1, GL_FALSE, modelMatrix);
		glUniformMatrix4fv(_ViewMatrixUniform, 1, GL_FALSE, viewMatrix);
		glUniformMatrix4fv(_projectMatrixUniform, 1, GL_FALSE, _perspectiveProjectionMatrix);

		glBindVertexArray(gVao_vertical_cube);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, gTexture_Wood);
		glUniform1i(_Texture_smapler_uniform, 0);

		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		glDrawArrays(GL_TRIANGLE_FAN, 4, 4);
		glDrawArrays(GL_TRIANGLE_FAN, 8, 4);
		glDrawArrays(GL_TRIANGLE_FAN, 12, 4);
		glDrawArrays(GL_TRIANGLE_FAN, 16, 4);
		glBindTexture(GL_TEXTURE_2D, gTexture_Carpet);
		glUniform1i(_Texture_smapler_uniform, 0);
		glDrawArrays(GL_TRIANGLE_FAN, 20, 4);

		glBindVertexArray(0);

		zVerticalCube += verticalGap;
	}
	/****** CUBE BLOCK ENDS ******/


	modelMatrix = mat4::identity();
	viewMatrix = mat4::identity();
	scaleMatrix = mat4::identity();
	scaleMatrix = scale(0.1f, 0.1f, 0.02f);
	modelMatrix = translate(pos[0], pos[1], pos[2]);
	modelMatrix *= scaleMatrix;
	
	glUniformMatrix4fv(_modelMatrixUniform, 1, GL_FALSE, modelMatrix);
	glUniformMatrix4fv(_ViewMatrixUniform, 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(_projectMatrixUniform, 1, GL_FALSE, _perspectiveProjectionMatrix);

	glBindVertexArray(gVao_horizontal_cube);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 4, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 16, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 20, 4);

	glBindVertexArray(0);
	//stop using opengl program object
	glUseProgram(0);



}

void Rushabh::PhotoRoom::SceneTransition()
{
}

void Rushabh::PhotoRoom::UnInitialize()
{
	if (gVao_cube)
	{
		glDeleteVertexArrays(1, &gVao_cube);
		gVao_cube = 0;
	}

	if (gVao_horizontal_cube)
	{
		glDeleteVertexArrays(1, &gVao_horizontal_cube);
		gVao_horizontal_cube = 0;
	}

	if (gVao_horizontal_Quad)
	{
		glDeleteVertexArrays(1, &gVao_horizontal_cube);
		gVao_horizontal_cube = 0;
	}

	if (gVao_photo_Quad)
	{
		glDeleteVertexArrays(1, &gVao_photo_Quad);
		gVao_photo_Quad = 0;
	}

	if (gVao_vertical_cube)
	{
		glDeleteVertexArrays(1, &gVao_vertical_cube);
		gVao_vertical_cube = 0;
	}

	if (gVbo_cube_position)
	{
		glDeleteBuffers(1, &gVbo_cube_position);
		gVbo_cube_position = 0;
	}

	if (gVbo_cube_texture)
	{
		glDeleteBuffers(1, &gVbo_cube_texture);
		gVbo_cube_texture = 0;
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
