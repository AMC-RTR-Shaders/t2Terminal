#include "AeroplaneInstanceing.h"

Harsh::AeroplaneInstanceing::AeroplaneInstanceing()
{
	_modelParser = new ModelParser("3DModels\\Scene_1\\Aeroplane\\airpl.obj");
	CHECK_NULL(_modelParser);

	return;
CLEAN_LOCAL_ALLOCATION_BELOW:
	UnInitialize();

}

Harsh::AeroplaneInstanceing::~AeroplaneInstanceing()
{
	UnInitialize();
}



void Harsh::AeroplaneInstanceing::Initialize()
{
	SAFE_LOG("AeroplaneInstanceing shading language supported verison is : %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION))

	//CREAT VERTEXT SHADER OBJECT
	_vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

	//CREATE SOURCE CODE FOR VERTEX SHADER OBJECT
	const GLchar *vertexShaderSourcecode =
		"#version 430 core" \
		"\n" \
		"in vec4 vPosition;" \
		"in vec3 vNormal;" \
		"in vec4 instance_position;"\
		"in vec3 instance_rotation;"\
		"uniform mat4 u_model_matrix;" \
		"uniform mat4 u_view_matrix;" \
		"uniform mat4 u_projection_matrix;" \
		"uniform vec3 u_La;" \
		"uniform vec3 u_Ld;" \
		"uniform vec3 u_Ls;"\
		"uniform vec3 u_Ka;" \
		"uniform vec3 u_Kd;" \
		"uniform vec3 u_Ks;" \
		"uniform vec4 u_light_position;" \
		"uniform float u_material_shininess;" \
		"out vec3 out_color;"
		
		"mat4 construct_rotation_matrix(float angle_x,float angle_y,float angle_z)"\
		"{"\
			"angle_x = (angle_x * (3.1415 / 180.0));"\
			"angle_y = (angle_y * (3.1415 / 180.0));"\
			"angle_z = (angle_z * (3.1415 / 180.0));"\
			"float stx = sin(angle_x);"\
			"float ctx = cos(angle_x);"\
			"float sty = sin(angle_y);"\
			"float cty = cos(angle_y);"\
			"float stz = sin(angle_z);"\
			"float ctz = cos(angle_z);"\
			"return mat4(vec4(cty*ctz, -(cty*stz), sty, 0.0),"\
			"vec4(((ctx*stz)+(stx*sty*ctz)), ((ctx*ctz)-(stx*sty*stz)), -(stx*cty), 0.0),"\
			"vec4(((stx*stz)-(ctx*sty*ctz)), ((stx*ctz)+(ctx*sty*stz)), (ctx*cty), 0.0),"\
			"vec4(0.0, 0.0, 0.0, 1.0));"\
		"}"\

		"mat4 construct_translation_matrix(float tx,float ty,float tz)"\
		"{"\
			"return mat4(vec4(1.0, 0.0, 0.0, tx),"\
			"vec4(0.0, 1.0, 0.0, ty),"\
			"vec4(0.0, 0.0, 1.0, tz),"\
			"vec4(0.0, 0.0, 0.0, 1.0));"\
		"}"\

		"void main (void)" \
		"{" \
			"mat4 rot = construct_rotation_matrix(instance_rotation.x,instance_rotation.y,instance_rotation.z);"\
			"mat4 trans = construct_translation_matrix(instance_position.x,instance_position.y,instance_position.z);"\
			"gl_Position = u_projection_matrix * (u_view_matrix *  (u_model_matrix * ((vPosition) * rot) * trans));" \
			
			"vec4 eye_coordinates=u_view_matrix * u_model_matrix * vPosition;" \
			"vec3 transformed_normals=normalize(mat3(u_view_matrix * u_model_matrix) * vNormal);" \
			"vec3 light_direction = normalize(vec3(u_light_position) - eye_coordinates.xyz);" \
			"float tn_dot_ld = max(dot(transformed_normals, light_direction),0.0);" \
			"vec3 ambient = u_La * u_Ka;" \
			"vec3 diffuse = u_Ld * u_Kd * tn_dot_ld;" \
			"vec3 reflection_vector = reflect(-light_direction, transformed_normals);" \
			"vec3 viewer_vector = normalize(-eye_coordinates.xyz);" \
			"vec3 specular = u_Ls * u_Ks * pow(max(dot(reflection_vector, viewer_vector), 0.0), u_material_shininess);" \
			"out_color=ambient + diffuse + specular;" \
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

				SAFE_LOG("Aeroplane Instancing Vertex Shader Compilation Log : %s\n", szInfoLog)
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
		"in vec3 out_color;"\
		"out vec4 FragColor;" \
		"void main (void)" \
		"{" \
			"FragColor = vec4(out_color, 1.0);" \
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

				SAFE_LOG("Aeroplane Instancing Fragment Shader Compilation Log : %s\n", szInfoLog)
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
	glBindAttribLocation(_shaderProgramObject, AMC_ATTRIBUTE_POSITION, "instance_position");
	//PRE-LINK BINDING OF SHADER PROGRAM OBJECT WITTH TEXTURE SHADER ATTRIBUTE
	glBindAttribLocation(_shaderProgramObject, AMC_ATTRIBUTE_ROTATION, "instance_rotation");

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
				sscanf(szInfoLog, "Aeroplane Shader Program Link Log : %s \n", szInfoLog);
				SAFE_LOG("Aeroplane Instancing Shader Program Link Log : %s \n", szInfoLog)
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
	material_shininess_uniform = glGetUniformLocation(_shaderProgramObject, "u_material_shininess");;

	//

	//LOAD THE MODEL HERE
	const GLfloat aeroplanePosition[] =
	{
		-442.38006591796875f,597.3568725585938f, -1.1920928955078125e-07f,
		-235.2344512939453f, 278.9481506347656f, -1.7881393432617188e-06f,
		-743.2999877929688f,  819.7822265625f,-1.1920928955078125e-07f,
		-444.4163513183594f, -9.498588562011719f, -1.7881393432617188e-06f,
		-530.5835571289062f, -122.79051208496094f, -3.6954879760742188e-06f,
		-596.292236328125f,  -271.97576904296875f,-3.6954879760742188e-06f,
		-820.8156127929688f,  949.6500854492188f,7.510185241699219e-06f,
		-685.8102416992188f,  1118.2052001953125f, 11.995464324951172f,
		-532.0331420898438f, 1117.9698486328125f, 6.318092346191406e-06f,
		-281.33740234375f,  848.8373413085938f, 2.5033950805664062e-06f,
		-159.4169921875f,  737.2481079101562f,2.5033950805664062e-06f,
		80.270751953125f,  706.0451049804688f, 3.4570693969726562e-06f,
		240.75062561035156f,  813.7158203125f, 3.4570693969726562e-06f,
		367.567626953125f,  1035.059326171875f, 3.4570693969726562e-06f,
		613.4510498046875f,  1120.7261962890625f, 1.5497207641601562e-06f,
		801.5818481445312f,  1046.99072265625f, 1.5497207641601562e-06f,
		759.7669677734375f,  861.5180053710938f, 1.5497207641601562e-06f,
		521.7274780273438f,  709.3599243164062f, -6.079673767089844e-06f,
		420.3172302246094f,  596.7721557617188f, -6.139278411865234e-06f,
		274.1110534667969f,  400.63153076171875f, -6.616115570068359e-06f,
		317.5008850097656f, 188.65992736816406f, -8.52346420288086e-06f,
		401.7718505859375f, 53.963531494140625f, -8.52346420288086e-06f,
		401.7718505859375f, 53.963531494140625f, -8.52346420288086e-06f,
		488.0202331542969f, -72.20281982421875f, -8.52346420288086e-06f,
		601.9674072265625f, -172.35833740234375f, -1.043081283569336e-05f,
	};

	const GLfloat aeroplaneRotation[] =
	{
		1.5708f, 148.0f, -0.0000f,
		1.5708f, 120.0000f, 2.0909f,
		1.5708f, 148.0000f, 2.5746f,
		1.5708f, 58.9000f, 1.0283f,
		1.5708f, 58.9000f, 1.0283f,
		1.5708f, 89.6f, 1.5631f,
		1.5708f, 110.0f, 1.9204f,
		1.5708f, 35.1f, 0.6127f,
		1.5708f, 7.41f, 0.1294f,
		1.5708f, -24.7f, -0.4319f,
		1.5708f, -24.7f, -0.4319f,
		1.5708f, 37.0f, 0.6466f,
		1.5708f, 49.9f, 0.8702f,
		1.5708f, 46.5f, 0.8109f,
		1.5708f, 337.0f, 5.8777f,
		1.5708f, 305.0f, 5.3272f,
		1.5708f,256.0f, 4.4715f,
		1.5708f, 256.0f, 4.4715f,
		1.5708f, 247.0f, 4.3145f,
		1.5708f, 260.0f, 4.5297f,
		1.5708f, 317.0f, 5.5355f,
		1.5708f, 317.0f, 5.5355f,
		1.5708f, 317.0f, 5.5355f,
		1.5708f, 317.0f, 5.5355f,
		1.5010f, 281.0f, 4.9043f,
	};

	CHECK_NULL(_modelParser);
	GLOBJECT_INSTANCEING *instancing = (GLOBJECT_INSTANCEING*)malloc(sizeof(GLOBJECT_INSTANCEING));
	instancing->instancingQuery = INSTANCING_QUERY::YES;

	instancing->isPostion = true;
	instancing->positionArray = aeroplanePosition;
	instancing->countOfPosition = sizeof(aeroplanePosition);
	instancing->position_attriDivisorCount = 1;

	instancing->isRotation = true;
	instancing->rotationArray = aeroplaneRotation;
	instancing->countOfRotation = sizeof(aeroplanePosition);
	instancing->rotation_attriDivisorCount = 1;

	instancing->numberOfInstance = 26;
	

	_modelParser->parse(_shaderProgramObject, ThreeDModelLoader::PROCESS_TYPE::CPU, ThreeDModelLoader::DRAW_TYPE::DRAW_USING_ARRAYS, instancing);


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

BOOL Harsh::AeroplaneInstanceing::SceneHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	return 0;
}



void Harsh::AeroplaneInstanceing::Update()
{
}

void Harsh::AeroplaneInstanceing::ReSize(int width, int height, struct ResizeAttributes attributes)
{
	if (height == 0)
		height = 1;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	_perspectiveProjectionMatrix = vmath::perspective(45.0f, (GLfloat)width / (GLfloat)height, attributes.nearValue, attributes.farValue);
}

void Harsh::AeroplaneInstanceing::Render(HDC hdc, struct Attributes attributes)
{
	mat4 modelMatrix = mat4::identity();
	mat4 viewMatrix = mat4::identity();
	mat4 rotateMatrix = mat4::identity();
	mat4 scaleMatrix = mat4::identity();

	static GLfloat lightAmbient[] = { 0.0f,0.0f,0.0f,1.0f };
	static GLfloat lightDiffuse[] = { 1.0f,1.0f,1.0f,1.0f };
	static GLfloat lightSpecular[] = { 1.0f,1.0f,1.0f,1.0f };
	static GLfloat lightPosition[] = { 100.0f,100.0f,100.0f,1.0f };
	static GLfloat material_shininess = 50.0f;

	//START USING SHADER OBJECT	
	glUseProgram(_shaderProgramObject);

	// setting light's properties
	glUniform3fv(_LaUniform, 1, lightAmbient);
	glUniform3fv(_LdUniform, 1, lightDiffuse);
	glUniform3fv(_LsUniform, 1, lightSpecular);
	glUniform4fv(_LightPositionUniform, 1, lightPosition);

	//material shininess
	glUniform1f(material_shininess_uniform, material_shininess);
	//

	modelMatrix = translate(attributes.translateCoords[0] -0.0f, attributes.translateCoords[0] -0.0f, attributes.translateCoords[0] -2500.0f);
	modelMatrix = modelMatrix * rotate(90.0f, 1.0f, 0.0f, 0.0f);
	
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

void Harsh::AeroplaneInstanceing::SceneTransition()
{
}

void Harsh::AeroplaneInstanceing::UnInitialize()
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
