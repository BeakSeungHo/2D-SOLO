// MiniView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "MiniView.h"
#include "ToolView.h"
#include "Terrain.h"
#include "MainFrm.h"


// CMiniView

IMPLEMENT_DYNCREATE(CMiniView, CView)

CMiniView::CMiniView()
	: m_pDeviceMgr(CDeviceMgr::GetInstance()),
	m_pTerrain(nullptr)
{

}

CMiniView::~CMiniView()
{
}

BEGIN_MESSAGE_MAP(CMiniView, CView)
END_MESSAGE_MAP()


// CMiniView 그리기입니다.

void CMiniView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
	//pDC->Rectangle(100, 100, 200, 200);

	m_pDeviceMgr->Render_Begin();

	m_pTerrain->MiniRender();

	m_pDeviceMgr->Render_End(m_hWnd);
}


// CMiniView 진단입니다.

#ifdef _DEBUG
void CMiniView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CMiniView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMiniView 메시지 처리기입니다.


void CMiniView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	NULL_CHECK(pFrameWnd);

	CToolView* pView = dynamic_cast<CToolView*>(pFrameWnd->m_MainSplitter.GetPane(0, 1));
	NULL_CHECK(pView);

	m_pTerrain = dynamic_cast<CTerrain*>(pView->m_pObjectMgr->GetList(OBJECT_TERRAIN).front());
	NULL_CHECK(m_pTerrain);
}
