/*
* @author: Rushabh Parakh
* @mailto: rgparakh@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/

#include "Door.h"

Rahul::Door::Door()
{
	// Left Sliding Door's Front Face X axis
	LSD_X_1 = 0.0f;
	LSD_X_4 = 0.0f;
	// Left Sliding Door's Front Face Y axis
	LSD_Z_1 = -29.0f;
	LSD_Z_4 = -29.0f;

	// Right Sliding Door's Front Face X axis
	RSD_X_2 = 0.0f;
	RSD_X_3 = 0.0f;
	// Right Sliding Door's Front Face Y axis
	RSD_Z_2 = -29.0f;
	RSD_Z_3 = -29.0f;
}

Rahul::Door::~Door()
{
	UnInitialize();
}

BOOL Rahul::Door::SceneHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	return 0;
}

void Rahul::Door::Initialize()
{

	//CREAT VERTEXT SHADER OBJECT
	_vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

	//CREATE SOURCE CODE FOR VERTEX SHADER OBJECT
	const GLchar *vertexShaderSourcecode =
		"#version 430" \
		"\n" \
		"in vec4 vPosition;" \
		"in vec3 vNormal;" \
		"in vec2 vTexture0_Coord;" \
		"uniform int light_enabled;" \
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
		"out vec2 out_texture0_coord;" \

		"void main(void)" \
		"{" \
		"if(light_enabled == 1)" \
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
		"out_texture0_coord = vTexture0_Coord;" \
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

				SAFE_LOG("Door Vertex Shader Compilation Log : %s\n", szInfoLog)
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
		"in vec2 out_texture0_coord;" \
		"uniform float u_blend_value;" \
		"out vec4 FragColor;" \
		"uniform sampler2D u_texture0_sampler;" \
		"void main(void)" \
		"{" \
		"FragColor = vec4(phong_ads_color, u_blend_value) * texture(u_texture0_sampler,out_texture0_coord);" \
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

				SAFE_LOG("Door Fragment Shader Compilation Log : %s\n", szInfoLog)
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

				SAFE_LOG("Door Shader Program Link Log : %s \n", szInfoLog)
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

	gTexture_sampler_uniform = glGetUniformLocation(_shaderProgramObject, "u_texture0_sampler");

	// LIGHT enabled
	_LightEnabled = glGetUniformLocation(_shaderProgramObject, "light_enabled");

	_Blend_Value_uniform = glGetUniformLocation(_shaderProgramObject, "u_blend_value");

	InitTED();
	InitLED();
	InitRED();
	InitLD();
	InitRD();

	LoadGLTextures(&gTexture_Door, MAKEINTRESOURCE(ID_BITMAP_ENTRANCE_DOOR));

	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
	glClearDepth(1.0f);

	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LEQUAL);

	glShadeModel(GL_SMOOTH);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_CULL_FACE); /*Turning oFF cull , as we are doing animation , and so need to paint the back of object when rotating*/

	_perspectiveProjectionMatrix = mat4::identity();

}

// generate cube coordinates
void Rahul::Door::GenerateCubeCoordinates(float cubeMiddleX, float cubeMiddleY, float cubeMiddleZ, float width, float height, float depth, float CubeCoordinates[])
{
	// TOP FACE
	CubeCoordinates[0] = cubeMiddleX + (width / 2.0f);
	CubeCoordinates[1] = cubeMiddleY + (height / 2.0f);
	CubeCoordinates[2] = cubeMiddleZ - (depth / 2.0f);

	CubeCoordinates[3] = cubeMiddleX - (width / 2.0f);
	CubeCoordinates[4] = cubeMiddleY + (height / 2.0f);
	CubeCoordinates[5] = cubeMiddleZ - (depth / 2.0f) ;

	CubeCoordinates[6] = cubeMiddleX - (width / 2.0f);
	CubeCoordinates[7] = cubeMiddleY + (height / 2.0f);
	CubeCoordinates[8] = cubeMiddleZ + (depth / 2.0f);

	CubeCoordinates[9] = cubeMiddleX + (width / 2.0f);
	CubeCoordinates[10] = cubeMiddleY + (height / 2.0f);
	CubeCoordinates[11] = cubeMiddleZ + (depth / 2.0f);

	// BOTTOM FACE
	CubeCoordinates[12] = cubeMiddleX + (width / 2.0f);
	CubeCoordinates[13] = cubeMiddleY - (height / 2.0f);
	CubeCoordinates[14] = cubeMiddleZ - (depth / 2.0f);

	CubeCoordinates[15] = cubeMiddleX - (width / 2.0f);
	CubeCoordinates[16] = cubeMiddleY - (height / 2.0f);
	CubeCoordinates[17] = cubeMiddleZ - (depth / 2.0f);

	CubeCoordinates[18] = cubeMiddleX - (width / 2.0f);
	CubeCoordinates[19] = cubeMiddleY - (height / 2.0f);
	CubeCoordinates[20] = cubeMiddleZ + (depth / 2.0f);

	CubeCoordinates[21] = cubeMiddleX + (width / 2.0f);
	CubeCoordinates[22] = cubeMiddleY - (height / 2.0f);
	CubeCoordinates[23] = cubeMiddleZ + (depth / 2.0f);

	// FRONT FACE
	CubeCoordinates[24] = cubeMiddleX + (width / 2.0f);
	CubeCoordinates[25] = cubeMiddleY + (height / 2.0f);
	CubeCoordinates[26] = cubeMiddleZ + (depth / 2.0f);

	CubeCoordinates[27] = cubeMiddleX - (width / 2.0f);
	CubeCoordinates[28] = cubeMiddleY + (height / 2.0f);
	CubeCoordinates[29] = cubeMiddleZ + (depth / 2.0f);

	CubeCoordinates[30] = cubeMiddleX - (width / 2.0f);
	CubeCoordinates[31] = cubeMiddleY - (height / 2.0f);
	CubeCoordinates[32] = cubeMiddleZ + (depth / 2.0f);

	CubeCoordinates[33] = cubeMiddleX + (width / 2.0f);
	CubeCoordinates[34] = cubeMiddleY - (height / 2.0f);
	CubeCoordinates[35] = cubeMiddleZ + (depth / 2.0f);

	// BACK FACE
	CubeCoordinates[36] = cubeMiddleX + (width / 2.0f);
	CubeCoordinates[37] = cubeMiddleY + (height / 2.0f);
	CubeCoordinates[38] = cubeMiddleZ - (depth / 2.0f);

	CubeCoordinates[39] = cubeMiddleX - (width / 2.0f);
	CubeCoordinates[40] = cubeMiddleY + (height / 2.0f);
	CubeCoordinates[41] = cubeMiddleZ - (depth / 2.0f);

	CubeCoordinates[42] = cubeMiddleX - (width / 2.0f);
	CubeCoordinates[43] = cubeMiddleY - (height / 2.0f);
	CubeCoordinates[44] = cubeMiddleZ - (depth / 2.0f);

	CubeCoordinates[45] = cubeMiddleX + (width / 2.0f);
	CubeCoordinates[46] = cubeMiddleY - (height / 2.0f);
	CubeCoordinates[47] = cubeMiddleZ - (depth / 2.0f);

	// LEFT FACE
	CubeCoordinates[48] = cubeMiddleX - (width / 2.0f);
	CubeCoordinates[49] = cubeMiddleY + (height / 2.0f);
	CubeCoordinates[50] = cubeMiddleZ - (depth / 2.0f);

	CubeCoordinates[51] = cubeMiddleX - (width / 2.0f);
	CubeCoordinates[52] = cubeMiddleY + (height / 2.0f);
	CubeCoordinates[53] = cubeMiddleZ + (depth / 2.0f);

	CubeCoordinates[54] = cubeMiddleX - (width / 2.0f);
	CubeCoordinates[55] = cubeMiddleY - (height / 2.0f);
	CubeCoordinates[56] = cubeMiddleZ + (depth / 2.0f);

	CubeCoordinates[57] = cubeMiddleX - (width / 2.0f);
	CubeCoordinates[58] = cubeMiddleY - (height / 2.0f);
	CubeCoordinates[59] = cubeMiddleZ - (depth / 2.0f);

	// RIGHT FACE
	CubeCoordinates[60] = cubeMiddleX + (width / 2.0f);
	CubeCoordinates[61] = cubeMiddleY + (height / 2.0f);
	CubeCoordinates[62] = cubeMiddleZ - (depth / 2.0f);

	CubeCoordinates[63] = cubeMiddleX + (width / 2.0f);
	CubeCoordinates[64] = cubeMiddleY + (height / 2.0f);
	CubeCoordinates[65] = cubeMiddleZ + (depth / 2.0f);

	CubeCoordinates[66] = cubeMiddleX + (width / 2.0f);
	CubeCoordinates[67] = cubeMiddleY - (height / 2.0f);
	CubeCoordinates[68] = cubeMiddleZ + (depth / 2.0f);

	CubeCoordinates[69] = cubeMiddleX + (width / 2.0f);
	CubeCoordinates[70] = cubeMiddleY - (height / 2.0f);
	CubeCoordinates[71] = cubeMiddleZ - (depth / 2.0f);
}

// initialize texture and normal
void Rahul::Door::InitTextureNormal()
{
	glGenBuffers(1, &vbo_texture);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_texture);
	glBufferData(GL_ARRAY_BUFFER, sizeof(DoorTexCoords), DoorTexCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(AMC_ATTRIBUTE_TEXTURE0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_TEXTURE0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &vbo_normal);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_normal);
	glBufferData(GL_ARRAY_BUFFER, sizeof(DoorNormals), DoorNormals, GL_STATIC_DRAW);
	glVertexAttribPointer(AMC_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// initialize top entrance door
void Rahul::Door::InitTED()
{
	float* TopDoorFrameVertices = (float*)malloc(sizeof(float) * 24 * 3);
	GenerateCubeCoordinates(TED_CubeMiddleX, TED_CubeMiddleY, TED_CubeMiddleZ, TED_Width, TED_Height, TED_Depth, TopDoorFrameVertices);

	// VAO FOR TOP CUBE
	glGenVertexArrays(1, &vao_top_entrance_door);
	glBindVertexArray(vao_top_entrance_door);

	glGenBuffers(1, &vbo_position_ted);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_position_ted);
	glBufferData(GL_ARRAY_BUFFER, 24 * 3 * sizeof(float), TopDoorFrameVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(AMC_ATTRIBUTE_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_VERTEX);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	InitTextureNormal();

	glBindVertexArray(0);
}

// initialize left entrance door
void Rahul::Door::InitLED()
{
	float* LeftDoorFrameVertices = (float*)malloc(sizeof(float) * 24 * 3);
	GenerateCubeCoordinates(LED_CubeMiddleX, LED_CubeMiddleY, LED_CubeMiddleZ, LED_Width, LED_Height, LED_Depth, LeftDoorFrameVertices);

	// VAO FOR LEFT CUBE
	glGenVertexArrays(1, &vao_left_entrance_door);
	glBindVertexArray(vao_left_entrance_door);

	glGenBuffers(1, &vbo_position_led);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_position_led);
	glBufferData(GL_ARRAY_BUFFER, 24 * 3 * sizeof(float), LeftDoorFrameVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(AMC_ATTRIBUTE_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_VERTEX);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	InitTextureNormal();

	glBindVertexArray(0);
}

// initialize right entrance door
void Rahul::Door::InitRED()
{
	float* RightDoorFrameVertices = (float*)malloc(sizeof(float) * 24 * 3);
	GenerateCubeCoordinates(RED_CubeMiddleX, RED_CubeMiddleY, RED_CubeMiddleZ, RED_Width, RED_Height, RED_Depth, RightDoorFrameVertices);

	// VAO FOR RIGHT CUBE
	glGenVertexArrays(1, &vao_right_entrance_door);
	glBindVertexArray(vao_right_entrance_door);

	glGenBuffers(1, &vbo_position_red);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_position_red);
	glBufferData(GL_ARRAY_BUFFER, 24 * 3 * sizeof(float), RightDoorFrameVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(AMC_ATTRIBUTE_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_VERTEX);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	InitTextureNormal();

	glBindVertexArray(0);
}

// initialize left rotating door
void Rahul::Door::InitLD()
{
	// VAO FOR LEFT SLIDING DOOR
	glGenVertexArrays(1, &vao_left_sliding_door);
	glBindVertexArray(vao_left_sliding_door);

	glGenBuffers(1, &vbo_position_lsd);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_position_lsd);
	glBufferData(GL_ARRAY_BUFFER, 4 * 3 * sizeof(GL_FLOAT), NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(AMC_ATTRIBUTE_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_VERTEX);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	InitTextureNormal();

	glBindVertexArray(0);
}

// initialize right rotating door
void Rahul::Door::InitRD()
{
	// VAO FOR RIGHT SLIDING DOOR
	glGenVertexArrays(1, &vao_right_sliding_door);
	glBindVertexArray(vao_right_sliding_door);

	glGenBuffers(1, &vbo_position_rsd);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_position_rsd);
	glBufferData(GL_ARRAY_BUFFER, 4 * 3 * sizeof(GL_FLOAT), NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(AMC_ATTRIBUTE_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_VERTEX);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	InitTextureNormal();

	glBindVertexArray(0);
}

void Rahul::Door::Update()
{
	doorRotateAngle = doorRotateAngle + 0.001f;
	if (StartDoorRotation == 1)
	{
		if (doorRotateAngle < (3.14f / 2.0f))
		{
			// udpate coordinates for left sliding door
			LSD_X_Rotating = LSD_X_3_Point + (radius * cos(doorRotateAngle));
			LSD_X_4 = LSD_X_Rotating;
			LSD_X_1 = LSD_X_Rotating;

			LSD_Z_Rotating = LSD_Z_3_Point + (radius * -sin(doorRotateAngle));
			LSD_Z_4 = LSD_Z_Rotating;
			LSD_Z_1 = LSD_Z_Rotating;

			// udpate coordinates for right sliding door

			RSD_X_Rotating = RSD_X_4_Point + (radius * -cos(doorRotateAngle));
			RSD_X_2 = RSD_X_Rotating;
			RSD_X_3 = RSD_X_Rotating;

			RSD_Z_Rotating = RSD_Z_4_Point + (radius * -sin(doorRotateAngle));
			RSD_Z_2 = RSD_Z_Rotating;
			RSD_Z_3 = RSD_Z_Rotating;
		}
	}
}

void Rahul::Door::ReSize(int width, int height, struct ResizeAttributes attributes)
{
	if (height == 0)
		height = 1;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	_perspectiveProjectionMatrix = vmath::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 1000.0f);

}

int  Rahul::Door::LoadGLTextures(GLuint *texture, TCHAR imageResourceId[])
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

void Rahul::Door::Render(HDC hdc, struct Attributes attributes)
{
	// TOP CUBE
	mat4 modelMatrix = mat4::identity();
	mat4 viewMatrix = mat4::identity();
	mat4 rotateMatrix = mat4::identity();

	static GLfloat lightAmbient[] = { 1.0f,1.0f,1.0f,1.0f };
	static GLfloat lightDiffuse[] = { 1.0f,1.0f,1.0f,1.0f };
	static GLfloat lightSpecular[] = { 1.0f,1.0f,1.0f,1.0f };
	static GLfloat lightPosition[] = { 100.0f,100.0f,100.0f,1.0f };
	static GLfloat materialAmbient[] = { 1.0f,1.0f,1.0f,1.0f };
	static GLfloat materialDiffuse[] = { 1.0f,1.0f,1.0f,1.0f };
	static GLfloat materialSpecular[] = { 1.0f,1.0f,1.0f,1.0f };
	static GLfloat zero[] = { 0.0f,0.0f,0.0f,0.0f };
	static GLfloat material_shininess = 50.0f;

	//START USING SHADER OBJECT	
	glUseProgram(_shaderProgramObject);

	// setting light's properties
	glUniform3fv(_LaUniform, 1, lightAmbient);
	glUniform3fv(_LdUniform, 1, lightDiffuse);
	glUniform3fv(_LsUniform, 1, lightSpecular);
	glUniform4fv(_LightPositionUniform, 1, lightPosition);
	glUniform3fv(_KaUniform, 1, materialAmbient);
	glUniform3fv(_KdUniform, 1, materialDiffuse);
	glUniform3fv(_KsUniform, 1, materialSpecular);
	glUniform1i(_LightEnabled, 1);
	glUniform1f(_Blend_Value_uniform, BlendValue);

	//material shininess
	glUniform1f(material_shininess_uniform, material_shininess);

	modelMatrix = translate(
		attributes.translateCoords[SCENE_AIRPORT_MODEL][0],
		attributes.translateCoords[SCENE_AIRPORT_MODEL][1] - 7.0f,
		attributes.translateCoords[SCENE_AIRPORT_MODEL][2]);
	rotateMatrix = rotate(
		attributes.rotateCoords[SCENE_AIRPORT_MODEL][0],
		attributes.rotateCoords[SCENE_AIRPORT_MODEL][1],
		attributes.rotateCoords[SCENE_AIRPORT_MODEL][2]);

	modelMatrix = modelMatrix * rotateMatrix;

	glUniformMatrix4fv(_modelMatrixUniform, 1, GL_FALSE, modelMatrix);
	glUniformMatrix4fv(_ViewMatrixUniform, 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(_projectMatrixUniform, 1, GL_FALSE, _perspectiveProjectionMatrix);

	DrawTED();
	DrawLED();
	DrawRED();
	DrawLD();
	DrawRD();

	//STOP USING SHADER
	glUseProgram(0);

}

// draw top entrance door
void Rahul::Door::DrawTED()
{
	glBindVertexArray(vao_top_entrance_door);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gTexture_Door);
	glUniform1i(gTexture_sampler_uniform, 0);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);	// 4(each with its x,y,z) vertices in squareVertices array
	glDrawArrays(GL_TRIANGLE_FAN, 4, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 16, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 20, 4);

	glBindVertexArray(0);
}

// draw left entrance door
void Rahul::Door::DrawLED()
{
	glBindVertexArray(vao_left_entrance_door);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gTexture_Door);
	glUniform1i(gTexture_sampler_uniform, 0);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);	// 4(each with its x,y,z) vertices in squareVertices array
	glDrawArrays(GL_TRIANGLE_FAN, 4, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 16, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 20, 4);

	glBindVertexArray(0);
}

// draw right entrance door
void Rahul::Door::DrawRED()
{
	glBindVertexArray(vao_right_entrance_door);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gTexture_Door);
	glUniform1i(gTexture_sampler_uniform, 0);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);	// 4(each with its x,y,z) vertices in squareVertices array
	glDrawArrays(GL_TRIANGLE_FAN, 4, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 16, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 20, 4);

	glBindVertexArray(0);
}

// draw left rotating door
void Rahul::Door::DrawLD()
{
	GLfloat LeftSlidingDoorVertices[] =
	{
		LSD_X_1,18.0f,LSD_Z_1,
		-15.0f,18.0f,-29.0f,
		-15.0f,0.0f,-29.0f,
		LSD_X_4,0.0f,LSD_Z_4
	};

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindVertexArray(vao_left_sliding_door);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_position_lsd);
	glBufferData(GL_ARRAY_BUFFER, sizeof(LeftSlidingDoorVertices), LeftSlidingDoorVertices, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gTexture_Door);
	glUniform1i(gTexture_sampler_uniform, 0);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);	// 4(each with its x,y,z) vertices in squareVertices array

	glBindVertexArray(0);

	glDisable(GL_BLEND);
}

// draw right rotating door
void Rahul::Door::DrawRD()
{
	GLfloat RightSlidingDoorVertices[] =
	{
		15.0f,18.0f,-29.0f,
		RSD_X_2,18.0f,RSD_Z_2,
		RSD_X_3,0.0f,RSD_Z_3,
		15.0f,0.0f,-29.0f,
	};

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindVertexArray(vao_right_sliding_door);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_position_rsd);
	glBufferData(GL_ARRAY_BUFFER, sizeof(RightSlidingDoorVertices), RightSlidingDoorVertices, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gTexture_Door);
	glUniform1i(gTexture_sampler_uniform, 0);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);	// 4(each with its x,y,z) vertices in squareVertices array

	glBindVertexArray(0);

	glDisable(GL_BLEND);
}

void Rahul::Door::SceneTransition()
{
}

void Rahul::Door::UnInitialize()
{
	if (vao_top_entrance_door)
	{
		glDeleteBuffers(1, &vao_top_entrance_door);
		vao_top_entrance_door = 0;
	}
	if (vbo_position_ted)
	{
		glDeleteBuffers(1, &vbo_position_ted);
		vbo_position_ted = 0;
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
	if (vao_left_entrance_door)
	{
		glDeleteBuffers(1, &vao_left_entrance_door);
		vao_left_entrance_door = 0;
	}
	if (vao_right_entrance_door)
	{
		glDeleteBuffers(1, &vao_right_entrance_door);
		vao_right_entrance_door = 0;
	}
	if (vao_left_sliding_door)
	{
		glDeleteBuffers(1, &vao_left_sliding_door);
		vao_left_sliding_door = 0;
	}
	if (vao_right_sliding_door)
	{
		glDeleteBuffers(1, &vao_right_sliding_door);
		vao_right_sliding_door = 0;
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
