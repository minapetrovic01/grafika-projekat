#pragma once
#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "glu32.lib")

#include <GL\gl.h>
#include <GL\glu.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <string>
#include <cmath>
#include <afxwin.h>
#include "CGLMaterial.h"
#include "CGLTexture.h"

#define PI 3.14159


struct COLOR3F {
	float R;
	float G;
	float B;
};

class CGLRenderer
{
private:
	HGLRC m_hrc;

	void CalculateViewPosition();


public:
	CGLRenderer();
	~CGLRenderer();

	bool showAxis = true;
	bool showGrid = true;

	bool showNormals;

	double lookingAt[3];
	double viewPosition[3];
	double upVector[3];

	double viewAngle[2];
	double viewR;
	double pieceAngle;


	double lookAtHeight = 2;

	double axisLineLenght = 100;

	CGLTexture* texPlanet;

	std::vector<CGLTexture*> high_resolution;
	std::vector<CGLTexture*> low_resolution;

	int textureColumns = 2;
	int textureRows = 2;

	double alpha = 0;

	int nSeg;

	bool CreateGLContext(CDC* pDC);
	void PrepareScene(CDC* pDC);
	void DestroyScene(CDC* pDC);
	void Reshape(CDC* pDC, int w, int h);
	void DrawScene(CDC* pDC);

	void DrawAxis(double width);

	void Light();


};

