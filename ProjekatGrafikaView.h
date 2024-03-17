
// ProjekatGrafikaView.h : interface of the CProjekatGrafikaView class
//

#pragma once
#include "CGLRenderer.h"


class CProjekatGrafikaView : public CView
{
protected: // create from serialization only
	CProjekatGrafikaView() noexcept;
	DECLARE_DYNCREATE(CProjekatGrafikaView)

// Attributes
public:
	CProjekatGrafikaDoc* GetDocument() const;
	CGLRenderer m_glRenderer;
	POINT mousePos = { 0,0 };
// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnInitialUpdate();


// Implementation
public:
	virtual ~CProjekatGrafikaView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};

#ifndef _DEBUG  // debug version in ProjekatGrafikaView.cpp
inline CProjekatGrafikaDoc* CProjekatGrafikaView::GetDocument() const
   { return reinterpret_cast<CProjekatGrafikaDoc*>(m_pDocument); }
#endif

