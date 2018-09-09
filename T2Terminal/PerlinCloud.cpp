/*
* @author: Utility Abhijeet
* @mailto: aabhijeet95@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/

#include"PerlinCloud.h"

Abhijeet::PerlinCloud::PerlinCloud()
{
	 //skycolor[] = { 0.8f,0.8f,0.8f };
	 //cloudcolor[] = { 0.0f,0.0f,0.8f };

	_PerlinTime = 2.0f;
	_CloudDirection = 1;
	_gbChangeCloudDIrection = false;
	_gfUpdateCloudTime = 0.005f;
	_PerlinCloudAngle = 0.0f;
	_gfCloudAlpha = 1.0f;
}

Abhijeet::PerlinCloud::~PerlinCloud()
{
	UnInitialize();
}



BOOL Abhijeet::PerlinCloud::SceneHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	return 0;
}

void Abhijeet::PerlinCloud::Initialize()
{

	_gVertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

	const GLchar *vertexShaderSourceCode =
		"#version 400 core" \
		"\n" \
		"in vec4 vPosition;" \
		"uniform mat4 u_mvp_matrix;" \
		"void main(void)" \
		"{" \
		"gl_Position = u_mvp_matrix * vPosition;" \
		"}";
	glShaderSource(_gVertexShaderObject, 1, (const GLchar **)&vertexShaderSourceCode, NULL);

	glCompileShader(_gVertexShaderObject);

	GLint iInfoLength = 0;
	char *szInfoLog = NULL;

	GLint iShaderCompileStatus = 0;

	glGetShaderiv(_gVertexShaderObject, GL_COMPILE_STATUS, &iShaderCompileStatus);
	if (iShaderCompileStatus == GL_FALSE)
	{
		glGetShaderiv(_gVertexShaderObject, GL_INFO_LOG_LENGTH, &iInfoLength);
		if (iInfoLength > 0)
		{
			szInfoLog = (GLchar *)malloc(iInfoLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(_gVertexShaderObject, iInfoLength, &written, szInfoLog);
				SAFE_LOG( "\nVERTEX SHADER COMPILATION LOG:%s \n", szInfoLog);
				free(szInfoLog);
				UnInitialize();
				exit(0);
			}
		}
	}

	_gFragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar * fragmentShaderSourceCode =
		"#version 430 core" \
		"\n" \
		"uniform float iTime;" \
		"uniform vec3 iResolution;" \
		"uniform int iCloudDirection;"\
		"uniform float u_CloudAlpha;"\
		"out vec4 FragColor;" \
		"const float cloudscale = 1.5;"\
		"const float speed = 0.03;"\
		"const float clouddark = 0.5;"\
		"const float cloudlight = 0.3;"\
		"const float cloudcover = 0.5;"\
		//cloudcover FOR FRONT CLOUD DENSITY
		"const float cloudalpha = 3.0;"\
		//cloudalpha IS FOR VARIATION IN SHAPE OF CLOUD
		"const float skytint = 0.5;"\
		"const vec3 skycolour1 = vec3(0.2, 0.4, 0.6);"\
		"const vec3 skycolour2 = vec3(0.4, 0.7, 1.0);"\
		"const mat2 m = mat2(1.6, 1.2, -1.2, 1.6);"\

		"vec2 hash(vec2 p)"\
		"{"\
		"	p = vec2(dot(p, vec2(127.1, 311.7)), dot(p, vec2(269.5, 183.3)));"\
		"	return -1.0 + 2.0*fract(sin(p)*8758.5453123);"\
		"}"\

		"float noise(in vec2 p)"\
		"{"\
		"	 float K1 = 0.366025404;"\
		"	float K2 = 0.211324865;" \
		"	vec2 i = floor(p + (p.x + p.y)*K1);"\
		"	vec2 a = p - i + (i.x + i.y)*K2;"\
		"	vec2 o = (a.x>a.y) ? vec2(1.0, 0.0) : vec2(0.0, 1.0);"\
		"	vec2 b = a - o + K2;"\
		"	vec2 c = a - 1.0 + 2.0*K2;"\
		"	vec3 h = max(0.5 - vec3(dot(a, a), dot(b, b), dot(c, c)), 0.0);"\
		"	vec3 n = h*h*h*h*vec3(dot(a, hash(i + 0.0)), dot(b, hash(i + o)), dot(c, hash(i + 1.0)));"\
		"	return dot(n, vec3(70.0));"\
		"}"\

		"float fbm(vec2 n)"
		"{"\
		"	float total = 0.0, amplitude = 0.1;"\
		"	for (int i = 0; i < 7; i++) "\
		"	{"\
		"		total += noise(n) * amplitude;"\
		"		n = m * n;"\
		"		amplitude *= 0.4;"\
		"	}"\
		"	return total;"\
		"}"\

		"void main()"\
		"{"\
		"	vec2 p = gl_FragCoord.xy / iResolution.xy;"\
		"	vec2 uv = p*vec2(iResolution.x / iResolution.y, 1.0);"\
		"	float _PerlinTime = iTime * speed;"\
		"	float q = fbm(uv * cloudscale * 0.5);"\
		////ridged noise shape
		"	float r = 0.0;"\
		"	uv *= cloudscale;"\
		//THIS uv DECIDES THE DIRECTION OF AVOVE DENSE CLOUDS
		/*"	uv += q - _PerlinTime;"\*/
		"	if(iCloudDirection == 0)"\
		"	{"\
		"		uv += q - _PerlinTime;"\
		"	}"\
		"	else"\
		"	{"\
		"		uv -= q - _PerlinTime;"\
		"	}"\
		"	float weight = 0.8;"\
		"	for (int i = 0; i<8; i++)"\
		"	{"\
		"		r += abs(weight*noise(uv));"\
		"		uv = m*uv + _PerlinTime;"\
		"		weight *= 0.7;"\
		"	}"\
		////noise shape
		"	float f = 0.0;"\
		"	uv = p*vec2(iResolution.x / iResolution.y, 1.0);"\
		"	uv *= cloudscale;"\
		/*"	uv += q - _PerlinTime;"\*/
		"	if(iCloudDirection == 0)"\
		"	{"\
		"		uv += q - _PerlinTime;"\
		"	}"\
		"	else"\
		"	{"\
		"		uv -= q - _PerlinTime;"\
		"	}"\
		"	weight = 0.50;"\
		"	for (int i = 0; i<8; i++)"\
		"	{"\
		"		f += weight*noise(uv);"\
		"		uv = m*uv + _PerlinTime;"\
		"		weight *= 0.6;"\
		"	}"\
		"	f *= r + f;"\
		////noise colour
		"	float c = 0.0;"\
		"	_PerlinTime = iTime * speed * 2.0;"\
		"	uv = p*vec2(iResolution.x / iResolution.y, 1.0);"\
		"	uv *= cloudscale*2.0;"\
		/*"	uv += q - iTime;"\*/
		"	if(iCloudDirection == 0)"\
		"	{"\
		"		uv += q - iTime;"\
		"	}"\
		"	else"\
		"	{"\
		"		uv -= q - iTime;"\
		"	}"\
		"	weight = 0.4;"\
		"	for (int i = 0; i<7; i++)"\
		"	{"\
		"		c += weight*noise(uv);"\
		"		uv = m*uv + _PerlinTime;"\
		"		weight *= 0.6;"\
		"	}"\
		////noise ridge colour
		"	float c1 = 0.0;"\
		"	_PerlinTime = iTime * speed * 1.0;"\
		"	uv = p*vec2(iResolution.x / iResolution.y, 1.0);"\
		"	uv *= cloudscale*3.0;"\
		//THIS uv + or - decides BELOW CLOUDS DIRECTION OF FLOW
		/*"	uv += q - iTime;"\*/
		"	if(iCloudDirection == 0)"\
		"	{"\
		"		uv += q - iTime;"\
		"	}"\
		"	else"\
		"	{"\
		"		uv -= q - iTime;"\
		"	}"\
		"	weight = 0.4;"\
		"	for (int i = 0; i<7; i++)"\
		"	{"\
		"		c1 += abs(weight*noise(uv));"\
		"		uv = m*uv + iTime;"\
		"		weight *= 0.6;"\
		"	}"\
		"	c += c1;"\
		"	vec3 skycolour = mix(skycolour2, skycolour1, p.y);"\
		"	vec3 cloudcolour = vec3(1.1, 1.1, 0.9) * clamp((clouddark + cloudlight*c), 0.0, 1.0);"\
		"	f = cloudcover + cloudalpha*f*r;"\
		"	vec3 result = mix(skycolour, clamp(skytint * skycolour + cloudcolour, 0.0, 1.0), clamp(f + c, 0.0, 1.0));"\
		"	FragColor = vec4(result,u_CloudAlpha);"\
		"}";


	glShaderSource(_gFragmentShaderObject, 1, (const GLchar **)&fragmentShaderSourceCode, NULL);
	
	glCompileShader(_gFragmentShaderObject);

	glGetShaderiv(_gFragmentShaderObject, GL_COMPILE_STATUS, &iShaderCompileStatus);
	if (iShaderCompileStatus == GL_FALSE)
	{
		glGetShaderiv(_gFragmentShaderObject, GL_INFO_LOG_LENGTH, &iInfoLength);
		if (iInfoLength > 0)
		{
			szInfoLog = (GLchar *)malloc(iInfoLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(_gFragmentShaderObject, iInfoLength, &written, szInfoLog);
				SAFE_LOG("\n FRAGMENT SHADER COMPILATION LOG:%s \n", szInfoLog);
				free(szInfoLog);
				UnInitialize();
				exit(0);
			}
		}
	}
	
	_gShaderProgramObject = glCreateProgram();
	glAttachShader(_gShaderProgramObject, _gVertexShaderObject);
	glAttachShader(_gShaderProgramObject, _gFragmentShaderObject);

	glBindAttribLocation(_gShaderProgramObject, ABHI_ATTRIBUTE_POSITION, "vPosition");

	glLinkProgram(_gShaderProgramObject);

	GLint iShaderLinkStatus = 0;

	glGetShaderiv(_gVertexShaderObject, GL_LINK_STATUS, &iShaderLinkStatus);
	if (iShaderLinkStatus == GL_FALSE)
	{
		glGetShaderiv(_gShaderProgramObject, GL_INFO_LOG_LENGTH, &iInfoLength);
		if (iInfoLength > 0)
		{
			szInfoLog = (GLchar *)malloc(iInfoLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(_gShaderProgramObject, iInfoLength, &written, szInfoLog);
				SAFE_LOG("\n LINK TIME ERROR LOG: \n%s \n", szInfoLog);
				free(szInfoLog);
				UnInitialize();
				exit(0);
			}
		}
	}

	_gMVPUniform = glGetUniformLocation(_gShaderProgramObject, "u_mvp_matrix");
	iResolutionUniform = glGetUniformLocation(_gShaderProgramObject, "iResolution");
	_Perlin_PerlinTimeUniform = glGetUniformLocation(_gShaderProgramObject, "iTime");
	_CloudDirectionUniform = glGetUniformLocation(_gShaderProgramObject, "iCloudDirection");
	_gfCloudAlphaUniform = glGetUniformLocation(_gShaderProgramObject, "u_CloudAlpha");

	const GLfloat rectangleVertices[] =
	{   -1500.0f,150.0f,0.0f,
		-1500.0f,-1500.0f,0.0f,
		 1500.0f,-1500.0f,0.0f,
		 1500.0f,1500.0f,0.0f
	};

	glGenVertexArrays(1, &_gVao_Rectangle);
	glBindVertexArray(_gVao_Rectangle);

	glGenBuffers(1, &_gVbo_Position);
	glBindBuffer(GL_ARRAY_BUFFER, _gVbo_Position);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), rectangleVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(ABHI_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(ABHI_ATTRIBUTE_POSITION);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
		

	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	

	glClearColor(1.0f, 0.0f, 0.0f, 0.0);

	_gPerspectiveProjectionMatrix = mat4::identity();
}

void Abhijeet::PerlinCloud::Update()
{
	//THIS TIME WILL DECIDE THE SPEED OF CLOUD MOVEMENT
	/*if ((_gbChangeCloudDIrection == true) && (_gfUpdateCloudTime >= 0.001f))
	{
		_gfUpdateCloudTime -= 0.0001f;

	}
	else if (_gfUpdateCloudTime <= 0.01f)
	{
		_gfUpdateCloudTime -= 0.0001f;
	}*/
	//_gfUpdateCloudTime

	_PerlinTime = _PerlinTime + _gfUpdateCloudTime;

}

void Abhijeet::PerlinCloud::ReSize(int width, int height, struct ResizeAttributes attributes)
{
	if (height == 0)
		height = 1;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	_gPerspectiveProjectionMatrix = vmath::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 1000.0f);

}

void Abhijeet::PerlinCloud::Render(HDC hdc, struct Attributes attributes)
{
	//glDisable(GL_CULL_FACE);
	glUseProgram(_gShaderProgramObject);

	glUniform3f(iResolutionUniform, 800, 600.0, 0.0f);
	glUniform1f(_Perlin_PerlinTimeUniform, _PerlinTime);
	glUniform1i(_CloudDirectionUniform, attributes.PerlinCloudDirection);
	glUniform1f(_gfCloudAlphaUniform, attributes.PerlinCloudALpha);

	_gfUpdateCloudTime = attributes.PerlinCloudSpeed;
	//glUniform1f(updateXUniform, updateX);
	//glUniform1f(updateX2Uniform, updateX2);
	//glUniform1f(heightUniform, heightIncr);
	//glUniform1f(yPosUniform, yPos);

	vmath::mat4 modelViewMatrix = mat4::identity();
	mat4 modelViewProjectionMatrix = mat4::identity();

	//modelViewMatrix = vmath::translate(0.0f, 0.0f, -6.0f);
	modelViewMatrix = translate(
		attributes.translateCoords[SCENE_AIRPORT][0] + attributes.translateCoords[SCENE_SINGLE_AEROPLANE][0],
		attributes.translateCoords[SCENE_AIRPORT][1] + attributes.translateCoords[SCENE_SINGLE_AEROPLANE][1] - 100,
		attributes.translateCoords[SCENE_AIRPORT][2] + attributes.translateCoords[SCENE_SINGLE_AEROPLANE][2]);
		
	//_gRotationMatrix = vmath::rotate(attributes.PerlinCloudAngle, 1.0f, 0.0f, 0.0f);

	modelViewProjectionMatrix = _gPerspectiveProjectionMatrix * modelViewMatrix;
	//modelViewProjectionMatrix = modelViewProjectionMatrix * _gRotationMatrix;

	glUniformMatrix4fv(_gMVPUniform, 1, GL_FALSE, modelViewProjectionMatrix);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glBindVertexArray(_gVao_Rectangle);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glBindVertexArray(0);

	glDisable(GL_BLEND);


	//glUseProgram(0);

	/********************** UPDATE LOGIC ******************/
	//Update();

}

void Abhijeet::PerlinCloud::SceneTransition()
{
}

void Abhijeet::PerlinCloud::UnInitialize()
{
	if (_gVao_Rectangle)
	{
		glDeleteVertexArrays(1, &_gVao_Rectangle);
		_gVao_Rectangle = 0;
	}

	if (_gVbo_Position)
	{
		glDeleteBuffers(1, &_gVbo_Position);
		_gVbo_Position = 0;

	}
	glDetachShader(_gShaderProgramObject, _gVertexShaderObject);
	glDetachShader(_gShaderProgramObject, _gFragmentShaderObject);

	glDeleteShader(_gVertexShaderObject);
	glDeleteShader(_gFragmentShaderObject);
	glDeleteShader(_gShaderProgramObject);
	_gVertexShaderObject = _gFragmentShaderObject = _gShaderProgramObject = 0;

}
