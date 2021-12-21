
// ToolView.cpp : CToolView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Tool.h"
#endif

#include "MainFrm.h"
#include "ToolDoc.h"
#include "ToolView.h"
#include "Terrain.h"
#include "Back.h"
#include "Wall.h"
#include "MiniView.h"
#include "MyForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CToolView

IMPLEMENT_DYNCREATE(CToolView, CScrollView)

BEGIN_MESSAGE_MAP(CToolView, CScrollView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// ��������
HWND g_hWnd;

// CToolView ����/�Ҹ�

CToolView::CToolView()
	: m_pDeviceMgr(CDeviceMgr::GetInstance()),
	m_pTextureMgr(CTextureMgr::GetInstance()),
	m_pObjectMgr(CObjectMgr::GetInstance()),
	m_pMapTool(nullptr),
	m_pTarget(nullptr)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.	
}

CToolView::~CToolView()
{
	m_pObjectMgr->DestroyInstance();
	m_pTextureMgr->DestroyInstance();
	m_pDeviceMgr->DestroyInstance();
}

BOOL CToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CScrollView::PreCreateWindow(cs);
}

// CToolView �׸���

// WM_PAINT �޽����� ���� ������ ȣ��.
void CToolView::OnDraw(CDC* pDC)
{
	CToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	/*pDC->Rectangle(100, 100, 200, 200);
	pDC->Ellipse(100, 100, 200, 200);*/

	m_pDeviceMgr->Render_Begin();

	m_pObjectMgr->Render();

	m_pDeviceMgr->Render_End();

	CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	NULL_CHECK(pFrameWnd);

	CMiniView* pMiniView = dynamic_cast<CMiniView*>(pFrameWnd->m_SecondSplitter.GetPane(0, 0));
	NULL_CHECK(pMiniView);
	
	pMiniView->Invalidate(FALSE); // �̴Ϻ� ����
}


// CToolView �μ�

BOOL CToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CToolView ����

#ifdef _DEBUG
void CToolView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CToolDoc* CToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
	return (CToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CToolView �޽��� ó����


void CToolView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	g_hWnd = m_hWnd;

	// ��ũ�� ���� ����
	int iCX = 1176;
	int iCY = 792;

	CScrollView::SetScrollSizes(MM_TEXT, CSize(iCX, iCY));


	// View ũ�⸦ �����ϱ� ���ؼ��� ������ �������� ũ�⸦ �ǵ帰��.
	// ������ �������� ������ ������ ���.
	CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	NULL_CHECK_MSG(pFrameWnd, L"pFrameWnd is null");

	RECT rcFrame = {};

	// �������� ũ��(�׵θ� + Ŭ���̾�Ʈ ����) ������ �Լ�.(��ũ�� ��ǥ ����)
	pFrameWnd->GetWindowRect(&rcFrame); 
	::SetRect(&rcFrame, 0, 0, rcFrame.right - rcFrame.left, rcFrame.bottom - rcFrame.top);

	RECT rcView = {};

	// �������� Ŭ���̾�Ʈ ����(�׵θ��� �������� ����) ũ�� ������ �Լ�. (Ŭ���̾�Ʈ ��ǥ ����)
	GetClientRect(&rcView); 

	// ���� ������������� View ������ ������ ���Ѵ�.
	int iGapX = rcFrame.right - rcView.right;
	int iGapY = rcFrame.bottom - rcView.bottom;

	// �������������� ũ�⸦ ���� ����.
	pFrameWnd->SetWindowPos(nullptr, 0, 0, WINCX + iGapX, WINCY + iGapY, SWP_NOZORDER | SWP_NOMOVE);

	HRESULT hr = m_pDeviceMgr->InitDevice(MODE_WIN);
	FAILED_CHECK_MSG(hr, L"InitDevice Failed");

	LPDIRECT3DDEVICE9 pGraphicDev = m_pDeviceMgr->GetDevice();
	NULL_CHECK_MSG(pGraphicDev, L"pGraphicDev is null");

	hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
		L"../TEXTRUE/TILE/TILE%d.png",
		L"Terrain", L"Tile", 3);
	FAILED_CHECK_MSG(hr, L"Tile Texture Load Failed");

	hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
		L"../TEXTRUE/BACKGROUND/Back%d.png",
		L"BackGround", L"Back", 2);
	FAILED_CHECK_MSG(hr, L"BACKGROUND Texture Load Failed");

	hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
		L"../TEXTRUE/DUNGEON/LowerDetail/LowerDetail_%d.png",
		L"Dungeon", L"Detail", 15);
	FAILED_CHECK_MSG(hr, L"LowerDetail Texture Load Failed");

	hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
		L"../TEXTRUE/DUNGEON/Breakable/Breakable_%d.png",
		L"Dungeon", L"Breakable", 6);
	FAILED_CHECK_MSG(hr, L"Breakable Texture Load Failed");

	hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
		L"../TEXTRUE/DUNGEON/Wall/Wall_%d.png",
		L"Dungeon", L"Wall", 1);
	FAILED_CHECK_MSG(hr, L"Dungeon_Wall Texture Load Failed");

	m_pObjectMgr->AddObject(OBJECT_TERRAIN, CTerrain::Create(this));
	m_pObjectMgr->AddObject(OBJECT_BACK,CBack::Create(D3DXVECTOR3(WINCX * 0.5f, WINCY * 0.5f, 0.f),this));
	m_pObjectMgr->AddObject(OBJECT_WALL, CWall::Create(D3DXVECTOR3(WINCX * 0.5f, WINCY * 0.5f, 0.f), this));

	m_pMapTool = &dynamic_cast<CMyForm*>(pFrameWnd->m_SecondSplitter.GetPane(1,0))->m_MapTool;
	NULL_CHECK(m_pMapTool);

}

// WM_LBUTTONDOWN �޽��� �߻��� �� ȣ���.
void CToolView::OnLButtonDown(UINT nFlags, CPoint point)
{

	if (m_pMapTool->m_Radio[0].GetCheck())
	{
		// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
		D3DXVECTOR3 vPoint =
		{
			(float)point.x + CScrollView::GetScrollPos(0),
			(float)point.y + CScrollView::GetScrollPos(1),
			0.f
		};

		CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
		NULL_CHECK(pFrameWnd);

		CMyForm* pFormView = dynamic_cast<CMyForm*>(pFrameWnd->m_SecondSplitter.GetPane(1, 0));
		NULL_CHECK(pFormView);

		dynamic_cast<CTerrain*>(m_pObjectMgr->GetList(OBJECT_TERRAIN).front())->
		TileChange(vPoint, pFormView->m_MapTool.m_iDrawID, pFormView->m_MapTool.m_iOptionID);

		// ȭ�� ���� (WM_PAINT �߻�)
		Invalidate(FALSE);

		CScrollView::OnLButtonDown(nFlags, point);
	}
	else if (m_pMapTool->m_Radio[1].GetCheck())
	{
		m_pTarget = m_pObjectMgr->GetTarget(OBJECT_DETAIL, D3DXVECTOR3(point.x + CScrollView::GetScrollPos(0) ,point.y 
												+ CScrollView::GetScrollPos(1), 0.f));
	}
	else if (m_pMapTool->m_Radio[2].GetCheck())
	{
		m_pTarget = m_pObjectMgr->GetTarget(OBJECT_BREAKABLE , D3DXVECTOR3(point.x + CScrollView::GetScrollPos(0), point.y
												+ CScrollView::GetScrollPos(1), 0.f));
	}
	else if (m_pMapTool->m_Radio[3].GetCheck())
	{

	}
}

// WM_MOUSEMOVE �޽��� �߻� �� ȣ���.
void CToolView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_pMapTool->m_Radio[0].GetCheck())
	{
		// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			D3DXVECTOR3 vPoint =
			{
				(float)point.x + CScrollView::GetScrollPos(0),
				(float)point.y + CScrollView::GetScrollPos(1),
				0.f
			};

			CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
			NULL_CHECK(pFrameWnd);

			CMyForm* pFormView = dynamic_cast<CMyForm*>(pFrameWnd->m_SecondSplitter.GetPane(1, 0));
			NULL_CHECK(pFormView);

			dynamic_cast<CTerrain*>(m_pObjectMgr->GetList(OBJECT_TERRAIN).front())->
			TileChange(vPoint, pFormView->m_MapTool.m_iDrawID, pFormView->m_MapTool.m_iOptionID);

			// ȭ�� ���� (WM_PAINT �߻�)
			Invalidate(FALSE);
		}
	}
	else if (m_pMapTool->m_Radio[1].GetCheck() || m_pMapTool->m_Radio[2].GetCheck() )
	{
		if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
		{
			if (nullptr == m_pTarget)
				return;
			
			m_pTarget->SetPos(D3DXVECTOR3(point.x, point.y, 0.f));
			Invalidate(FALSE);
		}
	}
	CScrollView::OnMouseMove(nFlags, point);
}


void CToolView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	/*if (nullptr == m_pTarget)
		return;
	if (m_pMapTool->m_Radio[1].GetCheck() || m_pMapTool->m_Radio[2].GetCheck())
	{
		m_pTarget->SetPos(D3DXVECTOR3(point.x,point.y,0.f));
		Invalidate(FALSE);
	}*/

	CScrollView::OnRButtonDown(nFlags, point);
}


void CToolView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	switch (nChar)
	{
		case VK_TAB:
			m_pObjectMgr->SetTerrainRender(TRUE);
	}

	Invalidate(FALSE);


	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
}
