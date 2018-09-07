#include "SpotLightBox.h"

Harsh::SpotLightBox::SpotLightBox()
{
	return;

CLEAN_LOCAL_ALLOCATION_BELOW:
	UnInitialize();

}

Harsh::SpotLightBox::~SpotLightBox()
{
	UnInitialize();
}



void Harsh::SpotLightBox::Initialize()
{
	SAFE_LOG("SpotLight Box shading language supported verison is : %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION))

		//CREAT VERTEXT SHADER OBJECT
		_vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

	//CREATE SOURCE CODE FOR VERTEX SHADER OBJECT
	const GLchar *vertexShaderSourcecode =
		"#version 430 core" \
		"\n" \
		"in vec4 vPosition;" \
		"in vec3 vNormal;" \
		"uniform mat4 u_model_matrix;" \
		"uniform mat4 u_view_matrix;" \
		"uniform mat4 u_projection_matrix;" \
		"uniform int u_LKeyPressed;" \
		"uniform vec4 u_light_position;" \
		"out vec3 transformed_normals;" \
		"out vec3 light_direction;"\
		"out vec3 viewer_vector;"\
		"out vec3 FragPos;"\
		"void main (void)" \
		"{" \
		"if(u_LKeyPressed == 1)" \
		"{" \
		"vec4 eyeCoordinates =u_view_matrix * u_model_matrix * vPosition;" \
		"transformed_normals = mat3(u_view_matrix * u_model_matrix)*vNormal;" \
		"light_direction = vec3(u_light_position) - eyeCoordinates.xyz;" \
		"viewer_vector = -eyeCoordinates.xyz;" \
		"FragPos = vec3(u_model_matrix * vPosition);"
		"}" \
		"gl_Position = u_projection_matrix * u_view_matrix * u_model_matrix *vPosition;" \
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

				SAFE_LOG("SpotLight Vertex Shader Compilation Log : %s\n", szInfoLog)
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
		"in vec3 transformed_normals;"\
		"in vec3 light_direction;"\
		"in vec3 viewer_vector;"\
		"in vec3 FragPos;"\
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
		"uniform SpotLight spotLight[3];"\

		"out vec4 FragColor;" \

		"vec3 CalcSpotLight(SpotLight light, vec3 normal)"\
		"{"\
		"vec3 lightDir = normalize(light.u_light_position - FragPos);"\
		"float tn_dot_ld = max(dot(normal, lightDir), 0.0);"\
		"vec3 diffuse = light.u_Ld * tn_dot_ld * u_Kd;" \
		"vec3 view_direction = normalize(u_viewPos - FragPos);" \

		// material_Specularr shading
		"vec3 reflectDir = reflect(-lightDir, normal);"\
		"float spec = pow(max(dot(view_direction, reflectDir), 0.0), material.u_material_shininess);"\
		"vec3 specular = light.u_Ls * spec * u_Ks;"\

		// attenuation
		"float distance = length(light.u_light_position - FragPos);"\
		"float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));"\
		// spotlight intensity
		"float theta = dot(lightDir, normalize(-light.u_light_direction)); "\
		"float epsilon = light.cutOff - light.outerCutOff;"\
		"float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);"\
		// combine results
		"vec3 ambient = light.u_La * u_Ka;"\
		"ambient *= attenuation * intensity;"\
		"diffuse *= attenuation * intensity;"\
		"specular *= attenuation * intensity;"\
		"return (ambient + diffuse + specular);"\
		"}"\

		"void main (void)" \
		"{" \
		"vec3 result = vec3(0.0,0.0,0.0);"
		"vec3 phong_ads_color;" \
		"if(u_LKeyPressed == 1)"\
		"{" \
		"vec3 normalized_transformed_normals = normalize(transformed_normals);"\
		"vec3 normalized_light_direction = normalize(light_direction);"\
		"vec3 normalized_viewer_vector = normalize(viewer_vector);"\
		"vec3 ambient = u_La * u_Ka;"\
		"float tn_dot_ld = max(dot(normalized_transformed_normals , normalized_light_direction),0.0);"\
		"vec3 diffuse = u_Ld * u_Kd * tn_dot_ld;"\
		"vec3 reflection_vector = reflect(-normalized_light_direction,normalized_transformed_normals);"\
		"vec3 specular = u_Ls * u_Ks *pow(max(dot(reflection_vector,normalized_viewer_vector),0.0),u_material_shininess);"\
		"phong_ads_color = ambient + diffuse + specular;"\
		"for(int i=0;i<u_numSpotLights;i++){"
		"result += CalcSpotLight(spotLight[i], normalized_transformed_normals);"
		"}"\
		"}"\
		"else"\
		"{"\
		"phong_ads_color = vec3(1.0,1.0,1.0);"\
		"}"\
		"FragColor = vec4(result + phong_ads_color,0.5);" \
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

				SAFE_LOG("SpotLight Box Fragment Shader Compilation Log : %s\n", szInfoLog)
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

				char *szErrorfoLog = (char*)malloc(infoLogLength + 1024);
				sscanf(szInfoLog, "SpotLight Shader Program Link Log : %s \n", szInfoLog);
				SAFE_LOG("SpotLight Shader Program Link Log : %s \n", szInfoLog)
					SAFE_FREE(szInfoLog);
				UnInitialize();
				exit(0);
			}

		}
	}


	_modelMatrixUniform = glGetUniformLocation(_shaderProgramObject, "u_model_matrix");
	_ViewMatrixUniform = glGetUniformLocation(_shaderProgramObject, "u_view_matrix");
	_projectMatrixUniform = glGetUniformLocation(_shaderProgramObject, "u_projection_matrix");

	_Ka_Uniform = glGetUniformLocation(_shaderProgramObject, "u_Ka");
	_Kd_Uniform = glGetUniformLocation(_shaderProgramObject, "u_Kd");
	_Ks_Uniform = glGetUniformLocation(_shaderProgramObject, "u_Ks");
	_Material_shininess_uniform = glGetUniformLocation(_shaderProgramObject, "u_material_shininess");

	_LightPositionUniform = glGetUniformLocation(_shaderProgramObject, "u_light_position");
	_Ld_Uniform = glGetUniformLocation(_shaderProgramObject, "u_Ld");
	_La_uniform = glGetUniformLocation(_shaderProgramObject, "u_La");
	_La_uniform = glGetUniformLocation(_shaderProgramObject, "u_Ls");
	_LKeyPressedUniform = glGetUniformLocation(_shaderProgramObject, "u_LKeyPressed");
	_numSpotLightUniform = glGetUniformLocation(_shaderProgramObject, "u_numSpotLights");

	_viewrPositionUniform = glGetUniformLocation(_shaderProgramObject, "u_viewPos");

	_material_Kd = glGetUniformLocation(_shaderProgramObject, "material.u_Kd");
	_material_Ka = glGetUniformLocation(_shaderProgramObject, "material.u_Ka");
	_material_Ks = glGetUniformLocation(_shaderProgramObject, "material.u_Ks");
	_material_shininess_uniform = glGetUniformLocation(_shaderProgramObject, "material.u_material_shininess");

	_SpotLightLaUniform[0] = glGetUniformLocation(_shaderProgramObject, "spotLight[0].u_La");
	_SpotLightLdUniform[0] = glGetUniformLocation(_shaderProgramObject, "spotLight[0].u_Ld");
	_SpotLightLsUniform[0] = glGetUniformLocation(_shaderProgramObject, "spotLight[0].u_Ls");
	_SpotLightConstantUniform[0] = glGetUniformLocation(_shaderProgramObject, "spotLight[0].constant");
	_SpotLightLinearUniform[0] = glGetUniformLocation(_shaderProgramObject, "spotLight[0].linear");
	_SpotLightQuadraticUniform[0] = glGetUniformLocation(_shaderProgramObject, "spotLight[0].quadratic");
	_SpotLightCutOffUniform[0] = glGetUniformLocation(_shaderProgramObject, "spotLight[0].cutOff");
	_SpotLightOuterCutOffUniform[0] = glGetUniformLocation(_shaderProgramObject, "spotLight[0].outerCutOff");
	_SpotLightLightPositionUniform[0] = glGetUniformLocation(_shaderProgramObject, "spotLight[0].u_light_position");
	_SpotLightLightDirectionUniform[0] = glGetUniformLocation(_shaderProgramObject, "spotLight[0].u_light_direction");

	_SpotLightLaUniform[1] = glGetUniformLocation(_shaderProgramObject, "spotLight[1].u_La");
	_SpotLightLdUniform[1] = glGetUniformLocation(_shaderProgramObject, "spotLight[1].u_Ld");
	_SpotLightLsUniform[1] = glGetUniformLocation(_shaderProgramObject, "spotLight[1].u_Ls");
	_SpotLightConstantUniform[1] = glGetUniformLocation(_shaderProgramObject, "spotLight[1].constant");
	_SpotLightLinearUniform[1] = glGetUniformLocation(_shaderProgramObject, "spotLight[1].linear");
	_SpotLightQuadraticUniform[1] = glGetUniformLocation(_shaderProgramObject, "spotLight[1].quadratic");
	_SpotLightCutOffUniform[1] = glGetUniformLocation(_shaderProgramObject, "spotLight[1].cutOff");
	_SpotLightOuterCutOffUniform[1] = glGetUniformLocation(_shaderProgramObject, "spotLight[1].outerCutOff");
	_SpotLightLightPositionUniform[1] = glGetUniformLocation(_shaderProgramObject, "spotLight[1].u_light_position");
	_SpotLightLightDirectionUniform[1] = glGetUniformLocation(_shaderProgramObject, "spotLight[1].u_light_direction");

	_SpotLightLaUniform[2] = glGetUniformLocation(_shaderProgramObject, "spotLight[2].u_La");
	_SpotLightLdUniform[2] = glGetUniformLocation(_shaderProgramObject, "spotLight[2].u_Ld");
	_SpotLightLsUniform[2] = glGetUniformLocation(_shaderProgramObject, "spotLight[2].u_Ls");
	_SpotLightConstantUniform[2] = glGetUniformLocation(_shaderProgramObject, "spotLight[2].constant");
	_SpotLightLinearUniform[2] = glGetUniformLocation(_shaderProgramObject, "spotLight[2].linear");
	_SpotLightQuadraticUniform[2] = glGetUniformLocation(_shaderProgramObject, "spotLight[2].quadratic");
	_SpotLightCutOffUniform[2] = glGetUniformLocation(_shaderProgramObject, "spotLight[2].cutOff");
	_SpotLightOuterCutOffUniform[2] = glGetUniformLocation(_shaderProgramObject, "spotLight[2].outerCutOff");
	_SpotLightLightPositionUniform[2] = glGetUniformLocation(_shaderProgramObject, "spotLight[2].u_light_position");
	_SpotLightLightDirectionUniform[2] = glGetUniformLocation(_shaderProgramObject, "spotLight[2].u_light_direction");

	//

	//cube
	const GLfloat cubeVertices[] =
	{
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,

		1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,

		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,

		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,

		1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
	};

	glGenVertexArrays(1, &Vao_cube);
	glBindVertexArray(Vao_cube);

	glGenBuffers(1, &Vbo_cube_position);
	glBindBuffer(GL_ARRAY_BUFFER, Vbo_cube_position);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(AMC_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(AMC_ATTRIBUTE_POSITION);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	const GLfloat CubeNormals[] =

		//cube normals
	{
		0.0f,0.0f,1.0f,
		0.0f,0.0f,1.0f,
		0.0f,0.0f,1.0f,
		0.0f,0.0f,1.0f,

		1.0f,0.0f,0.0f,
		1.0f,0.0f,0.0f,
		1.0f,0.0f,0.0f,
		1.0f,0.0f,0.0f,

		0.0f,0.0f,-1.0f,
		0.0f,0.0f,-1.0f,
		0.0f,0.0f,-1.0f,
		0.0f,0.0f,-1.0f,

		-1.0f,0.0f,0.0f,
		-1.0f,0.0f,0.0f,
		-1.0f,0.0f,0.0f,
		-1.0f,0.0f,0.0f,

		0.0f,1.0f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,1.0f,0.0f,

		0.0f,-1.0f,0.0f,
		0.0f,-1.0f,0.0f,
		0.0f,-1.0f,0.0f,
		0.0f,-1.0f,0.0f,

	};
	glGenBuffers(1, &Vbo_cube_normal);
	glBindBuffer(GL_ARRAY_BUFFER, Vbo_cube_normal);
	glBufferData(GL_ARRAY_BUFFER, sizeof(CubeNormals), CubeNormals, GL_STATIC_DRAW);

	glVertexAttribPointer(AMC_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(AMC_ATTRIBUTE_NORMAL);

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

	gbAnimate = false;
	gbLight = false;

	angle_cube = 0.0f;

	return;

CLEAN_LOCAL_ALLOCATION_BELOW:
	UnInitialize();
}


BOOL Harsh::SpotLightBox::SceneHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	return 0;
}



void Harsh::SpotLightBox::Update()
{
	angle_cube = angle_cube + 0.01f;
	if (angle_cube >= 360.0f)
		angle_cube -= 360.0f;
}

void Harsh::SpotLightBox::ReSize(int width, int height, struct ResizeAttributes attributes)
{
	if (height == 0)
		height = 1;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	_perspectiveProjectionMatrix = vmath::perspective(45.0f, (GLfloat)width / (GLfloat)height, attributes.nearValue, attributes.farValue);
}

void Harsh::SpotLightBox::Render(HDC hdc, struct Attributes attributes)
{

	glUseProgram(_shaderProgramObject);
	gbLight = true;
	if (gbLight == true)
	{
		glUniform1i(_LKeyPressedUniform, 1);

		//light properties
		glUniform3fv(_La_uniform, 1, lightAmbient);
		glUniform3fv(_Ld_Uniform, 1, lightDiffuse);
		glUniform3fv(_Ls_Uniform, 1, lightSpecular);
		glUniform4fv(_LightPositionUniform, 1, lightPosition);

		glUniform3fv(_Ka_Uniform, 1, material_Ambient);
		glUniform3fv(_Kd_Uniform, 1, material_Diffuse);
		glUniform3fv(_Ks_Uniform, 1, material_Specular);
		glUniform1f(_Material_shininess_uniform, material_shininess);

		glUniform3fv(_material_Kd, 1, mAmbient);
		glUniform3fv(_material_Ka, 1, mDiffuse);
		glUniform3fv(_material_Ks, 1, mSpecular);
		glUniform1f(_material_shininess_uniform, 50.0f);
		glUniform3fv(_viewrPositionUniform, 1, vec3(0.0f, 0.0f, 3.0f));

		glUniform1i(_numSpotLightUniform, attributes.numSpotLight);

		glUniform3fv(_SpotLightLaUniform[0], 1, lightAmbientS1);
		glUniform3fv(_SpotLightLdUniform[0], 1, lightDiffuseS1);
		glUniform3fv(_SpotLightLsUniform[0], 1, lightSpecularS1);
		glUniform1f(_SpotLightConstantUniform[0], 1.0f);
		glUniform1f(_SpotLightLinearUniform[0], 0.09f);
		glUniform1f(_SpotLightQuadraticUniform[0], 0.032f);
		glUniform1f(_SpotLightCutOffUniform[0], cos(radians(12.5f)));
		glUniform1f(_SpotLightOuterCutOffUniform[0], cos(radians(17.0f)));
		lightPositionS1[0] = attributes.translateCoords[SCENE_AIRPORT][0] + 0.0f;
		lightPositionS1[1] = attributes.translateCoords[SCENE_AIRPORT][1] + 3.0f;
		lightPositionS1[2] = attributes.translateCoords[SCENE_AIRPORT][2] + 0.0f;
		glUniform3fv(_SpotLightLightPositionUniform[0], 1, lightPositionS1);
		glUniform3fv(_SpotLightLightDirectionUniform[0], 1, lightDirectionS1);

		glUniform3fv(_SpotLightLaUniform[1], 1, lightAmbientS2);
		glUniform3fv(_SpotLightLdUniform[1], 1, lightDiffuseS2);
		glUniform3fv(_SpotLightLsUniform[1], 1, lightSpecularS2);
		glUniform1f(_SpotLightConstantUniform[1], 1.0f);
		glUniform1f(_SpotLightLinearUniform[1], 0.09f);
		glUniform1f(_SpotLightQuadraticUniform[1], 0.032f);
		glUniform1f(_SpotLightCutOffUniform[1], cos(radians(12.5f)));
		glUniform1f(_SpotLightOuterCutOffUniform[1], cos(radians(17.0f)));
		lightPositionS2[0] = attributes.translateCoords[SCENE_AIRPORT][0] + 0.0f;
		lightPositionS2[1] = attributes.translateCoords[SCENE_AIRPORT][1] + 3.0f;
		lightPositionS2[2] = attributes.translateCoords[SCENE_AIRPORT][2] + 0.0f;
		glUniform3fv(_SpotLightLightPositionUniform[1], 1, lightPositionS2);
		glUniform3fv(_SpotLightLightDirectionUniform[1], 1, lightDirectionS2);

		glUniform3fv(_SpotLightLaUniform[2], 1, lightAmbientS3);
		glUniform3fv(_SpotLightLdUniform[2], 1, lightDiffuseS3);
		glUniform3fv(_SpotLightLsUniform[2], 1, lightSpecularS3);
		glUniform1f(_SpotLightConstantUniform[2], 1.0f);
		glUniform1f(_SpotLightLinearUniform[2], 0.09f);
		glUniform1f(_SpotLightQuadraticUniform[2], 0.032f);
		glUniform1f(_SpotLightCutOffUniform[2], cos(radians(12.5f)));
		glUniform1f(_SpotLightOuterCutOffUniform[2], cos(radians(17.0f)));
		lightPositionS3[0] = attributes.translateCoords[SCENE_AIRPORT][0] + 0.0f;
		lightPositionS3[1] = attributes.translateCoords[SCENE_AIRPORT][1] + 3.0f;
		lightPositionS3[2] = attributes.translateCoords[SCENE_AIRPORT][2] + 0.0f;
		glUniform3fv(_SpotLightLightPositionUniform[2], 1, lightPositionS3);
		glUniform3fv(_SpotLightLightDirectionUniform[2], 1, lightDirectionS3);

	}
	else
	{
		glUniform1i(_LKeyPressedUniform, 0);
	}

	mat4 modelMatrix = mat4::identity();
	mat4 viewMatrix = mat4::identity();
	mat4 rotationMatrix = mat4::identity();
	mat4 scaleMatrix = mat4::identity();
	mat4 translateMatrix = mat4::identity();

	//square block
	scaleMatrix = scale(1.5f, 0.35f, 1.5f);
	translateMatrix = translate(attributes.translateCoords[SCENE_AIRPORT][0] + 0.0f, attributes.translateCoords[SCENE_AIRPORT][1] + -1.5f, attributes.translateCoords[SCENE_AIRPORT][2] + 0.0f);
	modelMatrix = translateMatrix*scaleMatrix;


	glUniformMatrix4fv(_modelMatrixUniform, 1, GL_FALSE, modelMatrix);
	glUniformMatrix4fv(_ViewMatrixUniform, 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(_projectMatrixUniform, 1, GL_FALSE, _perspectiveProjectionMatrix);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindVertexArray(Vao_cube);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 4, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 16, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 20, 4);
	glBindVertexArray(0);
	glDisable(GL_BLEND);
	glUseProgram(0);

	return;


CLEAN_LOCAL_ALLOCATION_BELOW:
	UnInitialize();
}

void Harsh::SpotLightBox::SceneTransition()
{
}

void Harsh::SpotLightBox::UnInitialize()
{
	if (Vao_cube)
	{
		glDeleteVertexArrays(1, &Vao_cube);
		Vao_cube = 0;
	}

	if (Vbo_cube_position)
	{
		glDeleteBuffers(1, &Vbo_cube_position);
		Vbo_cube_position = 0;
	}

	if (Vbo_cube_normal)
	{
		glDeleteBuffers(1, &Vbo_cube_normal);
		Vbo_cube_normal = 0;
	}

	if (Vbo_cube_texture)
	{
		glDeleteBuffers(1, &Vbo_cube_texture);
		Vbo_cube_texture = 0;
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
