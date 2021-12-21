// MapTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "MapTool.h"
#include "MainFrm.h"
#include "ToolView.h"
#include "Terrain.h"
#include "Detail.h"
#include "Breakable.h"
#include "GameObject.h"
#include "afxdialogex.h"

#include "DirectoryMgr.h"


// CMapTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMapTool, CDialog)

CMapTool::CMapTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MAPTOOL, pParent),
	m_iDrawID(0),
	m_iOptionID(0),
	m_pDeviceMgr(CDeviceMgr::GetInstance()),
	m_pTextureMgr(CTextureMgr::GetInstance()),
	m_pObjectMgr(CObjectMgr::GetInstance())
{

}

CMapTool::~CMapTool()
{
}

void CMapTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_PICTURE, m_Picture);
	DDX_Control(pDX, IDC_RADIO1, m_Radio[0]);
	DDX_Control(pDX, IDC_RADIO2, m_Radio[1]);
	DDX_Control(pDX, IDC_RADIO3, m_Radio[2]);
	DDX_Control(pDX, IDC_RADIO4, m_Radio[3]);
	DDX_Control(pDX, IDC_COMBO1, m_TileCombo);
	DDX_Control(pDX, IDC_COMBO2, m_BackCombo);
	DDX_Control(pDX, IDC_COMBO3, m_WallCombo);
	DDX_Control(pDX, IDC_PICTURE2, m_Picture2);
}


BEGIN_MESSAGE_MAP(CMapTool, CDialog)
	ON_WM_DROPFILES()
	ON_LBN_SELCHANGE(IDC_LIST1, &CMapTool::OnLbnSelchangeList)
	ON_BN_CLICKED(IDC_BUTTON7, &CMapTool::OnBnClickedSave)
	ON_BN_CLICKED(IDC_BUTTON6, &CMapTool::OnBnClickedLoad)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMapTool::OnCbnSelchangeTileCombo)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CMapTool::OnCbnSelchangeBackCombo)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CMapTool::OnCbnSelchangeWallCombo)
	ON_BN_CLICKED(IDC_RADIO1, &CMapTool::OnBnClickedTileRadio)
	ON_BN_CLICKED(IDC_RADIO2, &CMapTool::OnBnClickedDetailRadio)
	ON_BN_CLICKED(IDC_RADIO3, &CMapTool::OnBnClickedBreakableRadio)
	ON_BN_CLICKED(IDC_BUTTON1, &CMapTool::OnBnClickedAdd)
END_MESSAGE_MAP()


// CMapTool 메시지 처리기입니다.

// WM_DROPFILES 메시지 발생 시 호출됨.
void CMapTool::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	TCHAR szFileName[MAX_STR] = L"";

	// 드래그 앤 드롭된 대상들 중 인덱스에 해당하는 파일의 이름을 얻어온다.
	//::DragQueryFile(hDropInfo, 1, szFileName, MAX_STR);
	//::AfxMessageBox(szFileName);

	// 두번째인자가 -1일 때 드래그 앤 드롭된 대상들의 전체 개수를 얻어온다.
	int iCount = ::DragQueryFile(hDropInfo, -1, nullptr, 0);

	CString strRelative = L"";
	CString strFileName = L"";

	for (int i = 0; i < iCount; ++i)
	{
		::DragQueryFile(hDropInfo, i, szFileName, MAX_STR);

		//strRelative = CDirectoryMgr::ConvertRelativePath(szFileName);
		strFileName = ::PathFindFileName(szFileName); // 파일명 얻어내는 함수.

		lstrcpy(szFileName, strFileName);
		::PathRemoveExtension(szFileName); // 확장자 제거.

		m_ListBox.AddString(szFileName);
	}

	SettingHorizontalScrollSize();

	CDialog::OnDropFiles(hDropInfo);
}

void CMapTool::SettingHorizontalScrollSize()
{
	// 리스트박스에 수평 스크롤 확장하기.

	CString strName = L"";

	int iSrcCX = 0, iDstCX = 0;

	CDC* pDC = m_ListBox.GetDC();

	for (int i = 0; i < m_ListBox.GetCount(); ++i)
	{
		m_ListBox.GetText(i, strName);

		// 현재 문자열의 길이를 픽셀 단위로 환산.
		iSrcCX = pDC->GetTextExtent(strName).cx;

		if (iDstCX < iSrcCX)
			iDstCX = iSrcCX;
	}

	m_ListBox.ReleaseDC(pDC);

	// 현재 리스트박스가 가지고 있는 수평 스크롤 범위보다 클 때
	if (iDstCX > m_ListBox.GetHorizontalExtent())
		m_ListBox.SetHorizontalExtent(iDstCX); // 수평 스크롤 크기 갱신.
}


void CMapTool::OnLbnSelchangeList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int iIndex = m_ListBox.GetCurSel();

	if (-1 == iIndex)
		return;

	m_byDrawID = iIndex;

	const TEX_INFO* pTexInfo = nullptr;

	if (m_Radio[1].GetCheck())
	{
		pTexInfo = m_pTextureMgr->GetTexInfo(L"Dungeon", L"Detail", m_byDrawID);
		NULL_CHECK(pTexInfo);
	}
	else if (m_Radio[2].GetCheck())
	{
		pTexInfo = m_pTextureMgr->GetTexInfo(L"Dungeon", L"Breakable",m_byDrawID);
		NULL_CHECK(pTexInfo);
	}
	

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	D3DXMATRIX matScale, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, WINCX / pTexInfo->tImgInfo.Width, WINCY / pTexInfo->tImgInfo.Height, 0.f);
	D3DXMatrixTranslation(&matTrans, WINCX * 0.5f, WINCY * 0.5f, 0.f);

	matWorld = matScale * matTrans;

	m_pDeviceMgr->GetSprite()->SetTransform(&matWorld);

	m_pDeviceMgr->Render_Begin();

	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	m_pDeviceMgr->Render_End(m_Picture.m_hWnd);
}


void CMapTool::OnBnClickedSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog Dlg(FALSE, L".dat", L"제목 없음.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data Files(*.dat)|*.dat|Text Files(*.txt)|*.txt||", this);

	TCHAR szCurrentDir[MAX_STR] = L"";

	::GetCurrentDirectory(MAX_STR, szCurrentDir);
	::PathRemoveFileSpec(szCurrentDir);
	::PathCombine(szCurrentDir, szCurrentDir, L"Data");

	Dlg.m_ofn.lpstrInitialDir = szCurrentDir;

	if (IDOK == Dlg.DoModal())
	{		
		NULL_CHECK(m_pToolView)

		m_pToolView->m_pObjectMgr->SaveObject(Dlg.GetPathName());
	}
}


void CMapTool::OnBnClickedLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog Dlg(TRUE, L".dat", L"제목 없음.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data Files(*.dat)|*.dat|Text Files(*.txt)|*.txt||", this);

	TCHAR szCurrentDir[MAX_STR] = L"";

	::GetCurrentDirectory(MAX_STR, szCurrentDir);
	::PathRemoveFileSpec(szCurrentDir);
	::PathCombine(szCurrentDir, szCurrentDir, L"Data");

	Dlg.m_ofn.lpstrInitialDir = szCurrentDir;

	if (IDOK == Dlg.DoModal())
	{

		m_pToolView->m_pObjectMgr->LoadObject(Dlg.GetPathName());
		
		m_pToolView->Invalidate(FALSE);
	}
}


void CMapTool::OnCbnSelchangeTileCombo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int iIndex = m_TileCombo.GetCurSel();

	if (-1 == iIndex)
		return;

	//CString strName = L"";
	//m_TileCombo.GetText(iIndex, strName);

	//int i = 0;

	//for (; i < strName.GetLength(); ++i)
	//{
	//	// 현재 문자가 글자인지 숫자인지 판별. 숫자라면 true
	//	if (isdigit(strName[i]))
	//		break;
	//}

	//// Delete(index, count): 현재 문자열의 index자리부터 count만큼 제거.
	//strName.Delete(0, i);

	//// 문자 -> 정수로 변환.
	//m_iDrawID = _ttoi(strName);

	m_iDrawID = iIndex;
	m_iOptionID = iIndex;

	// 픽처 컨트롤에 타일 미리보기 출력.
	const TEX_INFO* pTexInfo = m_pTextureMgr->GetTexInfo(L"Terrain", L"Tile", m_iDrawID);
	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	D3DXMATRIX matScale, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, (float)WINCX / TILECX, (float)WINCY / TILECY, 0.f);
	D3DXMatrixTranslation(&matTrans, WINCX * 0.5f, WINCY * 0.5f, 0.f);

	matWorld = matScale * matTrans;

	m_pDeviceMgr->GetSprite()->SetTransform(&matWorld);

	m_pDeviceMgr->Render_Begin();

	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	m_pDeviceMgr->Render_End(m_Picture2.m_hWnd);
}


void CMapTool::OnCbnSelchangeBackCombo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int iIndex = m_BackCombo.GetCurSel();

	if (-1 == iIndex)
		return;

	m_byDrawBackID = iIndex;

	m_pObjectMgr->GetList(OBJECT_BACK).front()->Change(m_byDrawBackID);

	m_pToolView->Invalidate(FALSE);
}


void CMapTool::OnCbnSelchangeWallCombo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int iIndex = m_WallCombo.GetCurSel();

	if (-1 == iIndex)
		return;

	m_byDrawWallID = iIndex;

	m_pObjectMgr->GetList(OBJECT_WALL).front()->Change(m_byDrawWallID);

	m_pToolView->Invalidate(FALSE);
}


BOOL CMapTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_TileCombo.AddString(L"TILE0");
	m_TileCombo.AddString(L"TILE1");
	m_TileCombo.AddString(L"TILE2");

	m_BackCombo.AddString(L"Normal");
	m_BackCombo.AddString(L"Bossroom");
	
	m_WallCombo.AddString(L"Normal");
	m_WallCombo.AddString(L"Null");

	CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	
	m_pToolView = dynamic_cast<CToolView*>(pFrameWnd->m_MainSplitter.GetPane(0, 1));
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CMapTool::OnBnClickedTileRadio()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_ListBox.ResetContent();
}


void CMapTool::OnBnClickedDetailRadio()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_ListBox.ResetContent();

	wstring szFileName = L"";
	TCHAR iCount[MIN_STR] = L"";

	for (int i = 0; i < 15; ++i)
	{
		szFileName = L"Detail_";

		_itow_s(i,iCount,10);

		szFileName += iCount;

		m_ListBox.AddString(szFileName.c_str());
	}

}


void CMapTool::OnBnClickedBreakableRadio()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_ListBox.ResetContent();

	wstring szFileName = L"";
	TCHAR iCount[MIN_STR] = L"";

	for (int i = 0; i < 6; ++i)
	{
		szFileName = L"Breakable_";

		_itow_s(i, iCount, 10);

		szFileName += iCount;

		m_ListBox.AddString(szFileName.c_str());
	}
}


void CMapTool::OnBnClickedAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_Radio[1].GetCheck())
	{
		m_pObjectMgr->AddObject(OBJECT_DETAIL, CDetail::Create(D3DXVECTOR3(WINCX * 0.5f, WINCY * 0.5f, 0.f),m_byDrawID, m_pToolView));
		m_pToolView->Invalidate(FALSE);
	}
	else if (m_Radio[2].GetCheck())
	{
		m_pObjectMgr->AddObject(OBJECT_BREAKABLE, CBreakable::Create(D3DXVECTOR3(WINCX * 0.5f, WINCY * 0.5f, 0.f), m_byDrawID, m_pToolView));
		m_pToolView->Invalidate(FALSE);
	}
}
