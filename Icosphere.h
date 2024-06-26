#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include <array>
#include<cmath>
#include <map>
#include "CGLTexture.h"

class Icosphere
{
private:
	const float A = .525f;
	const float B = .850f;
	const float C = 0.0f;
	float radius;
	int level;


	std::vector<std::array<GLfloat, 3>> vertices;
	std::vector<std::array<GLuint, 3>> triangles;

	std::vector<std::array<GLfloat, 2>> textureCoordinates;
	std::vector<std::array<GLuint, 3>> textureFace;

	std::vector<std::array<GLfloat, 3>> FaceNormals;
	std::vector<std::array<GLfloat, 3>> vertexNormals;

	std::vector<CGLTexture*> high_resolution;
	std::vector<CGLTexture*> low_resolution;

	int textureColumns = 2;
	int textureRows = 2;

	bool seeWireframe = true;

	int getMidpoint(GLuint v1, GLuint v2, std::map<std::pair<int, int>, int>& isVisited, int& vertexCount);
	void tesellationRecursive(int depth, std::map<std::pair<int, int>, int>& isVisited, int triangleCount, int vertexCount);

	void calculateNormals();

	void textureCoord();//Calculate uv coordinates
	void fixTexture();//Changes u coordinates. To fix interpolation in texture.

	void findFaceNormal(GLfloat* vertex, GLfloat* vertex1, GLfloat* vertex2, GLfloat* normal);
	void vectorNormalize(GLfloat* normal);
	void vectorProduct(GLfloat* v1, GLfloat* v2, GLfloat* v3);
	//int getIndex(int i,double& xfix, double& yfix);

public:
	Icosphere(int level, std::vector<CGLTexture*>& high_resolution, int textureColumns, int textureRows, bool seeWireframe);
	void tesellation(int level);
	void drawSphere(float radius);
};



