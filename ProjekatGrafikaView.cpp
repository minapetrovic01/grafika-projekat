
// ProjekatGrafikaView.cpp : implementation of the CProjekatGrafikaView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ProjekatGrafika.h"
#endif

#include "ProjekatGrafikaDoc.h"
#include "ProjekatGrafikaView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define PI 3.14159265358979323846
#define toRad PI / 180


// CProjekatGrafikaView

IMPLEMENT_DYNCREATE(CProjekatGrafikaView, CView)

BEGIN_MESSAGE_MAP(CProjekatGrafikaView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEHWHEEL()
	ON_WM_MOVE()
	ON_WM_DESTROY()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

// CProjekatGrafikaView construction/destruction

CProjekatGrafikaView::CProjekatGrafikaView() noexcept
{
	// TODO: add construction code here

}

CProjekatGrafikaView::~CProjekatGrafikaView()
{
}

BOOL CProjekatGrafikaView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CProjekatGrafikaView drawing

void CProjekatGrafikaView::OnDraw(CDC* pDC)
{
	CProjekatGrafikaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	this->m_glRenderer.DrawScene(pDC);

	// TODO: add draw code for native data here
}


// CProjekatGrafikaView printing

BOOL CProjekatGrafikaView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CProjekatGrafikaView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CProjekatGrafikaView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CProjekatGrafikaView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CDC* pDC = GetDC();
	this->m_glRenderer.PrepareScene(pDC);
	ReleaseDC(pDC);
}


// CProjekatGrafikaView diagnostics

#ifdef _DEBUG
void CProjekatGrafikaView::AssertValid() const
{
	CView::AssertValid();
}

void CProjekatGrafikaView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CProjekatGrafikaDoc* CProjekatGrafikaView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CProjekatGrafikaDoc)));
	return (CProjekatGrafikaDoc*)m_pDocument;
}
#endif //_DEBUG


// CProjekatGrafikaView message handlers


void CProjekatGrafikaView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == 'Q') {
		this->m_glRenderer.alpha -= 2;
		Invalidate();
	}
	if (nChar == 'E') {
		this->m_glRenderer.alpha += 2;
		Invalidate();
	}
	if (nChar == 'A') {
		this->m_glRenderer.viewAngle[1] += 4 * PI / 180;
		Invalidate();
	}
	if (nChar == 'D') {
		this->m_glRenderer.viewAngle[1] -= 4 * PI / 180;
		Invalidate();
	}
	if (nChar == 'W') {
		this->m_glRenderer.viewAngle[0] += 2 * PI / 180;
		Invalidate();
	}
	if (nChar == 'S') {
		this->m_glRenderer.viewAngle[0] -= 2 * PI / 180;
		Invalidate();
	}
	if (nChar == VK_UP) {
		this->m_glRenderer.lookAtHeight += 0.5;
		Invalidate();
	}
	if (nChar == VK_DOWN) {
		this->m_glRenderer.lookAtHeight -= 0.5;
		Invalidate();
	}
	if (nChar == 'N') {
		this->m_glRenderer.showNormals = !this->m_glRenderer.showNormals;
		Invalidate();
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CProjekatGrafikaView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (nFlags & MK_LBUTTON) {
		double moveX = point.x > mousePos.x ? 1 : -1;
		double moveY = point.y > mousePos.y ? 1 : -1;
		if (abs(point.x - mousePos.x) > abs(point.y - mousePos.y))
			moveY /= 10;
		else
			moveX /= 10;
		this->m_glRenderer.viewAngle[1] += moveX * toRad;
		this->m_glRenderer.viewAngle[0] += moveY * toRad;
		mousePos = point;
		Invalidate();
	}

	CView::OnMouseMove(nFlags, point);
}


void CProjekatGrafikaView::OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt)
{
	double r = this->m_glRenderer.viewR + zDelta * (-0.01);

	if (r > 5 && r < 50) {
		this->m_glRenderer.viewR = r;
		Invalidate();
	}

	CView::OnMouseHWheel(nFlags, zDelta, pt);
}


void CProjekatGrafikaView::OnMove(int x, int y)
{
	CView::OnMove(x, y);

	// TODO: Add your message handler code here
}


void CProjekatGrafikaView::OnDestroy()
{
	CView::OnDestroy();

	CDC* pDC = GetDC();
	this->m_glRenderer.DestroyScene(pDC);
	ReleaseDC(pDC);
}


int CProjekatGrafikaView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CDC* pDC = GetDC();
	this->m_glRenderer.CreateGLContext(pDC);
	ReleaseDC(pDC);


	// TODO:  Add your specialized creation code here

	return 0;
}


BOOL CProjekatGrafikaView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return TRUE;
}


void CProjekatGrafikaView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	CDC* pDC = GetDC();
	this->m_glRenderer.Reshape(pDC, cx, cy);
	ReleaseDC(pDC);

}


BOOL CProjekatGrafikaView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default

	double r = this->m_glRenderer.viewR + zDelta * (-0.01);

	if (r > 5 && r < 100) {
		this->m_glRenderer.viewR = r;
		Invalidate();
	}

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}
