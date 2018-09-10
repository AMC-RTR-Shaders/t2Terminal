// functions use without 'this' prefix are private to class.
// functions with 'this' prefix are 'public' and hence when they use

#pragma once
#ifndef  _SPHEREMESH_H_
#define _SPHEREMESH_H_

#include <math.h>


short *elements;
float *verts;
float *norms;
float *texCoords;

int numElements = 0;
int maxElements = 0;
int numVertices = 0;
int numIndices;
int iNumIndices;

GLuint vbo_position = 0;
GLuint vbo_normal = 0;
GLuint vbo_texture = 0;
GLuint vbo_index = 0;
GLuint vao = 0;

const float VDG_PI = 3.14159265358979323846f;

enum
{
	VDG_ATTRIBUTE_POSITION = 0,
	VDG_ATTRIBUTE_COLOR,
	VDG_ATTRIBUTE_NORMAL,
	VDG_ATTRIBUTE_TEXTURE0,
};

void allocate(int numIndices)
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


bool isFoundIdentical(float val1, float val2, float diff)
{
	if (fabs(val1 - val2) < diff)
		return(true);
	else
		return(false);
}



void prepareToDraw()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// vbo for position
	glGenBuffers(1, &vbo_position);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_position);
	glBufferData(GL_ARRAY_BUFFER, iNumIndices * 3 * sizeof(float), verts, GL_STATIC_DRAW);
	glVertexAttribPointer(VDG_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(VDG_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// vbo for normals

	glGenBuffers(1, &vbo_normal);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_normal);
	glBufferData(GL_ARRAY_BUFFER, iNumIndices * 3 * sizeof(float), norms, GL_STATIC_DRAW);
	glVertexAttribPointer(VDG_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(VDG_ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// vbo for texture
	glGenBuffers(1, &vbo_texture);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_texture);
	glBufferData(GL_ARRAY_BUFFER, iNumIndices * 2 * sizeof(float), texCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(VDG_ATTRIBUTE_TEXTURE0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(VDG_ATTRIBUTE_TEXTURE0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// vbo for index
	glGenBuffers(1, &vbo_index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, iNumIndices * 3 * sizeof(unsigned short), elements, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void draw()
{
	glBindVertexArray(vao);

	// draw

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_index);
	glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_SHORT, 0);
	//glDrawElements(GL_LINES, numElements, GL_UNSIGNED_SHORT, 0);

	// unbind vao
	glBindVertexArray(0);
}

int getIndexCount()
{
	return(numElements);
}

int getVertexCount()
{
	// code
	return(numVertices);
}

void normalizeVector(float *v)
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


void deallocate()
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

void addTriangle(float single_vertex[4][3], float single_normal[4][3], float single_texture[4][2])
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

void makeSphere(float fRadius, float fHeight, int iSlices, int iStacks)
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


		for (j = 0; j < iSlices ; j++)
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

#endif