
/*
* @author: Rushabh Parakh
* @mailto: rgparakh@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/

#include "Airport.h"

Rushabh::Airport::Airport()
{
	_angle = 0.0f;

	_modelParser = new ModelParser("3DModels\\Scene_1\\TopView\\T2TerminalWithTextureFinal.obj");
	CHECK_NULL(_modelParser);

	return;
CLEAN_LOCAL_ALLOCATION_BELOW:
	UnInitialize();
}

Rushabh::Airport::~Airport()
{
	UnInitialize();
}

BOOL Rushabh::Airport::SceneHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	return 0;
}

void Rushabh::Airport::Initialize()
{
	SAFE_LOG("Airport shading language supported verison is : %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION))

		//CREAT VERTEXT SHADER OBJECT
		_vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

	//CREATE SOURCE CODE FOR VERTEX SHADER OBJECT
	const GLchar *vertexShaderSourcecode =
		"#version 430 core" \
		"\n" \
		"in vec4 vPosition;" \
		"in vec3 vNormal;" \
		"in vec2 vTexture0_Coord;" \
		"uniform mat4 u_model_matrix;" \
		"uniform mat4 u_view_matrix;" \
		"uniform mat4 u_projection_matrix;" \
		"uniform int u_LKeyPressed;" \
		"uniform vec4 u_light_position;" \
		"out vec3 transformed_normals;" \
		"out vec3 light_direction;"\
		"out vec3 viewer_vector;"\
		"out vec2 out_texture0_coord;"\
		"out vec3 FragPos;"\
		"void main (void)" \
		"{" \
		"if(1 == 1)" \
		"{" \
		"vec4 eyeCoordinates =u_view_matrix * u_model_matrix * vPosition;" \
		"transformed_normals = mat3(u_view_matrix * u_model_matrix)*vNormal;" \
		"light_direction = vec3(u_light_position) - eyeCoordinates.xyz;" \
		"viewer_vector = -eyeCoordinates.xyz;" \
		"FragPos = vec3(u_model_matrix * vPosition);"
		"}" \
		"out_texture0_coord = vTexture0_Coord;" \
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
				SAFE_LOG("Airport Vertex Shader Compilation Log : %s\n", szInfoLog)
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
		"in vec3 light_direction;"\
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
		"uniform SpotLight spotLight[3];"\

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
		"ambient *= intensity;"\
		"diffuse *=  intensity;"\
		"specular *=  intensity;"\
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

				SAFE_LOG("Airport Fragment Shader Compilation Log : %s\n", szInfoLog)
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
	//PRE-LINK BINDING OF SHADER PROGRAM OBJECT WITTH TEXTURE SHADER ATTRIBUTE
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

				SAFE_LOG("Airport Shader Program Link Log : %s \n", szInfoLog)
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

	// LIGHT POSITION TOKEN
	_LightPositionUniform = glGetUniformLocation(_shaderProgramObject, "u_light_position");


	//SHINYNESS COLOR TOKEN
	material_shininess_uniform = glGetUniformLocation(_shaderProgramObject, "u_material_shininess");

	//spotlights
	_numSpotLightUniform = glGetUniformLocation(_shaderProgramObject, "u_numSpotLights");

	_LKeyPressedUniform = glGetUniformLocation(_shaderProgramObject, "u_LKeyPressed");


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


	//LOAD THE MODEL HERE
	GLOBJECT_INSTANCEING instancing;
	instancing.instancingQuery = INSTANCING_QUERY::NO;
	CHECK_NULL(_modelParser);
	_modelParser->parse(_shaderProgramObject, ThreeDModelLoader::PROCESS_TYPE::CPU, ThreeDModelLoader::DRAW_TYPE::DRAW_USING_ARRAYS, &instancing, NULL);

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

void Rushabh::Airport::Update()
{
	_angle = _angle + 0.3f;

	if (_angle >= 360.0f)
		_angle = _angle - 360.0f;
}

void Rushabh::Airport::ReSize(int width, int height, struct ResizeAttributes attributes)
{
	if (height == 0)
		height = 1;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	_perspectiveProjectionMatrix = vmath::perspective(45.0f, (GLfloat)width / (GLfloat)height, attributes.nearValue, attributes.farValue);

}

void Rushabh::Airport::Render(HDC hdc, struct Attributes attributes)
{
	glDisable(GL_CULL_FACE); /*Turning oFF cull , as we are doing animation , and so need to paint the back of object when rotating*/

	mat4 modelMatrix = mat4::identity();
	mat4 viewMatrix = mat4::identity();
	mat4 rotateMatrix = mat4::identity();
	mat4 translateMatrix = mat4::identity();

	static GLfloat lightAmbient[] = { 0.0f,0.0f,0.0f,1.0f };
	static GLfloat lightDiffuse[] = { 1.0f,1.0f,1.0f,1.0f };
	static GLfloat lightSpecular[] = { 1.0f,1.0f,1.0f,1.0f };
	static GLfloat lightPosition[] = { 100.0f,100.0f,100.0f,1.0f };
	//static GLfloat material_shininess = 50.0f;


	GLfloat material_Ambient[4] = { 0.0f,0.0f,0.0f,1.0f };
	GLfloat material_Diffuse[4] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat material_Specular[4] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat material_shininess = 128.0f;
	//white
	GLfloat mAmbient[4] = { 0.0f,0.0f,0.0f,1.0f };
	GLfloat mDiffuse[4] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat mSpecular[4] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat lightAmbientS1[4] = { 0.0f,0.0f,0.0f,1.0f };
	GLfloat lightDiffuseS1[4] = { 1.0f,0.6f,0.2f,1.0f };
	GLfloat lightSpecularS1[4] = { 1.0f,0.6f,0.2f,1.0f };
	GLfloat lightPositionS1[4] = { 0.0f,0.0f,0.0f,1.0f };
	GLfloat lightDirectionS1[4] = { 0.0f,0.0f,-1.0f,1.0f };
	//saffron
	GLfloat lightAmbientS2[4] = { 0.0f,0.0f,0.0f,1.0f };
	GLfloat lightDiffuseS2[4] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat lightSpecularS2[4] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat lightPositionS2[4] = { 0.0f,0.0f,0.0f,1.0f };
	GLfloat lightDirectionS2[4] = { 0.0f,0.0f,-1.0f,1.0f };
	//green
	GLfloat lightAmbientS3[4] = { 0.0f,0.0f,0.0f,1.0f };
	GLfloat lightDiffuseS3[4] = { 0.07f,0.53f,0.03f,1.0f };
	GLfloat lightSpecularS3[4] = { 0.07f,0.53f,0.03f,1.0f };
	GLfloat lightPositionS3[4] = { 0.0f,0.0f,0.0f,1.0f };
	GLfloat lightDirectionS3[4] = { 0.0f,0.0f,-1.0f,1.0f };
	//START USING SHADER OBJECT	
	glUseProgram(_shaderProgramObject);

	// setting light's properties
	glUniform3fv(_LaUniform, 1, attributes.lightAmbient);
	glUniform3fv(_LdUniform, 1, lightDiffuse);
	glUniform3fv(_LsUniform, 1, lightSpecular);
	glUniform4fv(_LightPositionUniform, 1, lightPosition);

	//material shininess
	glUniform1f(material_shininess_uniform, material_shininess);
	glUniform1i(_LKeyPressedUniform,1);


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
	glUniform1f(_SpotLightCutOffUniform[0], cos(radians(attributes.lightRadius)));
	glUniform1f(_SpotLightOuterCutOffUniform[0], cos(radians(attributes.lightRadius + 3.0f)));
	//lightPositionS1[0] = attributes.translateCoords[SCENE_LIGHT_POS_1][0];
	//lightPositionS1[1] = attributes.translateCoords[SCENE_LIGHT_POS_1][1];
	//lightPositionS1[2] = attributes.translateCoords[SCENE_LIGHT_POS_1][2];
	lightPositionS1[0] = attributes.translateCoords[SCENE_AIRPORT][0]  + attributes.translateCoords[SCENE_LIGHT_POS_1][0];
	lightPositionS1[1] = attributes.translateCoords[SCENE_AIRPORT][1]  + attributes.translateCoords[SCENE_LIGHT_POS_1][1];
	lightPositionS1[2] = attributes.translateCoords[SCENE_AIRPORT][2]  + attributes.translateCoords[SCENE_LIGHT_POS_1][2];

	glUniform3fv(_SpotLightLightPositionUniform[0], 1, lightPositionS1);
	lightDirectionS1[0] = attributes.lightDirection[0];
	lightDirectionS1[1] = attributes.lightDirection[1];
	lightDirectionS1[2] = attributes.lightDirection[2];

	glUniform3fv(_SpotLightLightDirectionUniform[0], 1, lightDirectionS1);

	glUniform3fv(_SpotLightLaUniform[1], 1, lightAmbientS2);
	glUniform3fv(_SpotLightLdUniform[1], 1, lightDiffuseS2);
	glUniform3fv(_SpotLightLsUniform[1], 1, lightSpecularS2);
	glUniform1f(_SpotLightConstantUniform[1], 1.0f);
	glUniform1f(_SpotLightLinearUniform[1], 0.09f);
	glUniform1f(_SpotLightQuadraticUniform[1], 0.032f);
	glUniform1f(_SpotLightCutOffUniform[1], cos(radians(attributes.lightRadius)));
	glUniform1f(_SpotLightOuterCutOffUniform[1], cos(radians(attributes.lightRadius + 3.0f)));
	//lightPositionS1[0] = attributes.translateCoords[SCENE_AIRPORT][0] + 0.0f + attributes.lTanslateX;
	//lightPositionS1[1] = attributes.translateCoords[SCENE_AIRPORT][1] + 3.0f + attributes.lTanslateY;
	//lightPositionS1[2] = attributes.translateCoords[SCENE_AIRPORT][2] + 0.0f + attributes.lTanslateZ;
	lightPositionS2[0] = attributes.translateCoords[SCENE_AIRPORT][0] + attributes.translateCoords[SCENE_LIGHT_POS_2][0];
	lightPositionS2[1] = attributes.translateCoords[SCENE_AIRPORT][1] + attributes.translateCoords[SCENE_LIGHT_POS_2][1];
	lightPositionS2[2] = attributes.translateCoords[SCENE_AIRPORT][2] + attributes.translateCoords[SCENE_LIGHT_POS_2][2];
	glUniform3fv(_SpotLightLightPositionUniform[1], 1, lightPositionS2);
	lightDirectionS2[0] = attributes.lightDirection[0];
	lightDirectionS2[1] = attributes.lightDirection[1];
	lightDirectionS2[2] = attributes.lightDirection[2];

	glUniform3fv(_SpotLightLightDirectionUniform[1], 1, lightDirectionS2);

	glUniform3fv(_SpotLightLaUniform[2], 1, lightAmbientS3);
	glUniform3fv(_SpotLightLdUniform[2], 1, lightDiffuseS3);
	glUniform3fv(_SpotLightLsUniform[2], 1, lightSpecularS3);
	glUniform1f(_SpotLightConstantUniform[2], 1.0f);
	glUniform1f(_SpotLightLinearUniform[2], 0.09f);
	glUniform1f(_SpotLightQuadraticUniform[2], 0.032f);
	glUniform1f(_SpotLightCutOffUniform[2], cos(radians(attributes.lightRadius)));
	glUniform1f(_SpotLightOuterCutOffUniform[2], cos(radians(attributes.lightRadius + 3.0f)));
	lightPositionS3[0] = attributes.translateCoords[SCENE_AIRPORT][0] + attributes.translateCoords[SCENE_LIGHT_POS_3][0];
	lightPositionS3[1] = attributes.translateCoords[SCENE_AIRPORT][1] + attributes.translateCoords[SCENE_LIGHT_POS_3][1];
	lightPositionS3[2] = attributes.translateCoords[SCENE_AIRPORT][2] + attributes.translateCoords[SCENE_LIGHT_POS_3][2];

	glUniform3fv(_SpotLightLightPositionUniform[2], 1, lightPositionS3);
	lightDirectionS3[0] = attributes.lightDirection[0];
	lightDirectionS3[1] = attributes.lightDirection[1];
	lightDirectionS3[2] = attributes.lightDirection[2];

	glUniform3fv(_SpotLightLightDirectionUniform[2], 1, lightDirectionS3);


//	if (attributes.currentScene == SCENE_AIRPORT || attributes.currentScene == SCENE_MASTER)
	{
		translateMatrix = translate(
			attributes.translateCoords[SCENE_AIRPORT][0],
			attributes.translateCoords[SCENE_AIRPORT][1] + attributes.translateCoords[SCENE_AIRPORT_CUBEMAP][1],
			attributes.translateCoords[SCENE_AIRPORT][2]);
		rotateMatrix = rotate(
			attributes.rotateCoords[SCENE_AIRPORT][0],
			attributes.rotateCoords[SCENE_AIRPORT][1],
			attributes.rotateCoords[SCENE_AIRPORT][2]);
	}
	modelMatrix = translateMatrix * rotateMatrix;

	glUniformMatrix4fv(_modelMatrixUniform, 1, GL_FALSE, modelMatrix);
	glUniformMatrix4fv(_ViewMatrixUniform, 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(_projectMatrixUniform, 1, GL_FALSE, _perspectiveProjectionMatrix);
	
	CHECK_NULL(_modelParser);
	_modelParser->draw();

	//STOP USING SHADER
	glUseProgram(0);

	return;


CLEAN_LOCAL_ALLOCATION_BELOW:
	UnInitialize();
}

void Rushabh::Airport::SceneTransition()
{
}

void Rushabh::Airport::UnInitialize()
{
	SAFE_DELETE(_modelParser);

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
