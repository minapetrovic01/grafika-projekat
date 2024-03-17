#include "pch.h"
#include "CGLRenderer.h"
#include "Icosphere.h"

#define toRad PI/180
#define fullCircle 2*PI


CGLRenderer::CGLRenderer()
{
	this->m_hrc = NULL;

	viewR = 50;
	viewAngle[0] = 30*toRad;
	viewAngle[1] = 0;

	this->CalculateViewPosition();

	upVector[0]= upVector[2] = 0;
	upVector[1] = 1;

	this->texPlanet = new CGLTexture();

}

CGLRenderer::~CGLRenderer()
{
	if (this->texPlanet)
	{
		delete this->texPlanet;
		this->texPlanet = nullptr;
	}
}


bool CGLRenderer::CreateGLContext(CDC* pDC)
{
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int nPixelFormat = ChoosePixelFormat(pDC->m_hDC, &pfd);

	if (nPixelFormat == 0)
		return false;

	BOOL bResult = SetPixelFormat(pDC->m_hDC, nPixelFormat, &pfd);

	if (bResult == FALSE)
		return false;

	this->m_hrc = wglCreateContext(pDC->m_hDC);

	if (this->m_hrc == NULL)
		return false;

	return true;
}

void CGLRenderer::PrepareScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, this->m_hrc);
	// -------------------------------------------

	glClearColor(0.8, 0.8, 0.8, 1);

	glEnable(GL_DEPTH_TEST);
	/*this->platformMat->SetAmbient(.55, .55, .55, 1);
	this->platformMat->SetDiffuse(.85, .85, .85, 1);

	this->truckMat->SetAmbient(.65, .65, .45, 1);
	this->truckMat->SetDiffuse(.65, .65, .45, 1);

	this->cargoMat->SetAmbient(.85, .85, .85, 1);
	this->cargoMat->SetDiffuse(1, 1, 1, 1);*/

	CGLTexture::PrepareTexturing(true);
	/*this->texAtlas->LoadFromFile((CString)"lab-6-atlas.png");
	this->texGrass->LoadFromFile((CString)"lab-6-grass.jpeg", GL_REPEAT, GL_REPEAT);*/

	// Globalno ambientno svetlo
	GLfloat l_model_ambient[] = { .2, .2, .2, 1 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, l_model_ambient);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

	// Direkciono svetlo 
	float light_ambient_directional[] = { .35, .35, .35, 1 };
	float light_diffuse_directional[] = { 1, 1, 1, 1 };
	float light_specular_directional[] = { .2, .2, .2, 1 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient_directional);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse_directional);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular_directional);

	
	// -------------------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::Reshape(CDC* pDC, int w, int h)
{
	wglMakeCurrent(pDC->m_hDC, this->m_hrc);
	// -------------------------------------------

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30, (double)w / (double)h, 1, 100);
	glMatrixMode(GL_MODELVIEW);

	// -------------------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DrawScene(CDC* pDC)
{
	CalculateViewPosition();
	wglMakeCurrent(pDC->m_hDC, m_hrc);

	//glClearColor(0, 0, 0, .0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();

	gluLookAt(this->viewPosition[0], this->viewPosition[1], this->viewPosition[2], this->lookingAt[0], this->lookingAt[1], this->lookingAt[2], this->upVector[0], this->upVector[1], this->upVector[2]);


	this->Light();

	glPushMatrix();
	{
		
	}
	glPopMatrix();


	glEnable(GL_TEXTURE_2D);
	glEnable(GL_NORMALIZE);

	

	this->texPlanet->LoadFromFile((CString)"2k_mars.jpg");
	this->texPlanet->Select();


	Icosphere icosphere(4);
	icosphere.drawSphere(10);

	if (this->showAxis)
		this->DrawAxis(2);

	glFlush();


	SwapBuffers(pDC->m_hDC);
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DestroyScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);

	wglMakeCurrent(NULL, NULL);//ja sam izvukla iz if-a


	if (m_hrc) {
		wglDeleteContext(m_hrc);//ja sam dodala
		m_hrc = NULL;
	}
}

void CGLRenderer::CalculateViewPosition()
{
	viewPosition[0] = viewR * cos(viewAngle[0]) * cos(viewAngle[1]);
	viewPosition[1] = viewR * sin(viewAngle[0]);
	viewPosition[2] = viewR * cos(viewAngle[0]) * sin(viewAngle[1]);


	lookingAt[0] = lookingAt[2] = 0;
	lookingAt[1] = lookAtHeight;
}




void CGLRenderer::DrawAxis(double width)
{
	glLineWidth(width);

	glBegin(GL_LINES);
	//x
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(axisLineLenght, 0, 0);
	//y
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, axisLineLenght, 0);
	//z
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, axisLineLenght);
	glEnd();

}






void CGLRenderer::Light()
{
	glEnable(GL_LIGHTING);

	// Direkciono svetlo
	float light_position[] = { .5, 1, 1, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHT0);

	
}