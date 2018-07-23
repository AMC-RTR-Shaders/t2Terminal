#include "Tset.h"

Rushabh::Tset::Tset()
{
}

Rushabh::Tset::~Tset()
{
}

void Rushabh::Tset::Render(HDC hdc)
{
	mat4 modelMatrix = mat4::identity();
	mat4 viewMatrix = mat4::identity();
	mat4 rotateMatrix = mat4::identity();

	static GLfloat lightAmbient[] = { 0.0f,0.0f,0.0f,1.0f };
	static GLfloat lightDiffuse[] = { 1.0f,1.0f,1.0f,1.0f };
	static GLfloat lightSpecular[] = { 1.0f,1.0f,1.0f,1.0f };
	static GLfloat lightPosition[] = { 100.0f,100.0f,100.0f,1.0f };
	static GLfloat materialAmbient[] = { 1.0f,1.0f,1.0f,1.0f };
	static GLfloat materialDiffuse[] = { 1.0f,1.0f,1.0f,1.0f };
	static GLfloat materialSpecular[] = { 1.0f,1.0f,1.0f,1.0f };

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

	//material shininess
	glUniform1f(material_shininess_uniform, material_shininess);
	//

	modelMatrix = translate(0.0f, 0.0f, -15.0f);
	rotateMatrix = rotate(angle, angle, angle);

	modelMatrix = modelMatrix * rotateMatrix;

	glUniformMatrix4fv(_modelMatrixUniform, 1, GL_FALSE, modelMatrix);
	glUniformMatrix4fv(_ViewMatrixUniform, 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(_projectMatrixUniform, 1, GL_FALSE, _perspectiveProjectionMatrix);

	glBindVertexArray(vao);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 4, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 16, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 20, 4);

	glBindVertexArray(0);


	//STOP USING SHADER
	glUseProgram(0);
}

