// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// PatternGeneratorView.cpp : implementation of the CPatternGeneratorView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PatternGenerator.h"
#endif

#include "PatternGeneratorDoc.h"
#include "PatternGeneratorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPatternGeneratorView

IMPLEMENT_DYNCREATE(CPatternGeneratorView, CView)

BEGIN_MESSAGE_MAP(CPatternGeneratorView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPatternGeneratorView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_BUTTON_Start, &CPatternGeneratorView::OnButtonStart)
	ON_COMMAND(ID_BUTTON_Stop, &CPatternGeneratorView::OnButtonStop)
	ON_COMMAND(ID_BUTTON_Resume, &CPatternGeneratorView::OnButtonResume)
END_MESSAGE_MAP()

// CPatternGeneratorView construction/destruction

CPatternGeneratorView::CPatternGeneratorView()
{
	// TODO: add construction code here
	m_iCounter = 0;
	incY = 1;
	incX = 1;
	circleX1 = 0;
	circleY1 = 0;
	circleX2 = 100;
	circleY2 = 100;

}

CPatternGeneratorView::~CPatternGeneratorView()
{
}

BOOL CPatternGeneratorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CPatternGeneratorView drawing

void CPatternGeneratorView::OnDraw(CDC* pDC)
{
	CPatternGeneratorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CString strData;
	if (m_iCounter >= 0)
	{
		strData.Format(_T("The Count=%d"), m_iCounter);
	}
	pDC->TextOut(100, 100, strData);
	//pDC->Rectangle(rect);
	pDC->Ellipse(circleX1, circleY1, circleX2, circleY2);

	pDC->Rectangle(pDoc->m_iLeftTop, pDoc->m_iRightTop, pDoc->m_iLeftBottom, pDoc->m_iRightBottom);



	for (int iIndex = 0; iIndex <= 1; iIndex++)
	{

		pDC->Ellipse(circleX1, circleY1, circleX2, circleY2);

		if (circleX1 >= pDoc->m_iLeftBottom - 100)
		{
			incX = -1;
		}
		if (circleX1 <= pDoc->m_iLeftTop)
		{
			incX = 2;
		}
		if (circleY1 >= pDoc->m_iRightBottom - 100)
		{
			incY = -1.5;
		}
		if (circleY1 <= pDoc->m_iRightTop)
		{
			incY = 1;
		}
		circleX1 = circleX1 + incX;
		circleY1 = circleY1 + incY;
		circleX2 = circleX2 + incX;
		circleY2 = circleY2 + incY;



	}

	// TODO: add draw code for native data here
}


// CPatternGeneratorView printing


void CPatternGeneratorView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPatternGeneratorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPatternGeneratorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPatternGeneratorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CPatternGeneratorView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPatternGeneratorView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CPatternGeneratorView diagnostics

#ifdef _DEBUG
void CPatternGeneratorView::AssertValid() const
{
	CView::AssertValid();
}

void CPatternGeneratorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPatternGeneratorDoc* CPatternGeneratorView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPatternGeneratorDoc)));
	return (CPatternGeneratorDoc*)m_pDocument;
}
#endif //_DEBUG


// CPatternGeneratorView message handlers


void CPatternGeneratorView::OnButtonStart()
{
	// TODO: Add your command handler code here
	m_pCurrentThread = AfxBeginThread(CPatternGeneratorView::StartThread, this);
}


void CPatternGeneratorView::OnButtonStop()
{
	// TODO: Add your command handler code here
	m_pCurrentThread->SuspendThread();
	Invalidate();
}


void CPatternGeneratorView::OnButtonResume()
{
	// TODO: Add your command handler code here
	m_pCurrentThread->ResumeThread();
	Invalidate();
}


UINT CPatternGeneratorView::StartThread(LPVOID Param)
{
	CPatternGeneratorView *pView = (CPatternGeneratorView *)Param;
	while (true)
	{
		pView->m_iCounter++;
		pView->Invalidate();
		Sleep(100);
	}
	return 0;
	
}
