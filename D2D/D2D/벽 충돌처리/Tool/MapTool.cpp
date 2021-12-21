// MapTool.cpp : ���� �����Դϴ�.
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


// CMapTool ��ȭ �����Դϴ�.

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


// CMapTool �޽��� ó�����Դϴ�.

// WM_DROPFILES �޽��� �߻� �� ȣ���.
void CMapTool::OnDropFiles(HDROP hDropInfo)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	TCHAR szFileName[MAX_STR] = L"";

	// �巡�� �� ��ӵ� ���� �� �ε����� �ش��ϴ� ������ �̸��� ���´�.
	//::DragQueryFile(hDropInfo, 1, szFileName, MAX_STR);
	//::AfxMessageBox(szFileName);

	// �ι�°���ڰ� -1�� �� �巡�� �� ��ӵ� ������ ��ü ������ ���´�.
	int iCount = ::DragQueryFile(hDropInfo, -1, nullptr, 0);

	CString strRelative = L"";
	CString strFileName = L"";

	for (int i = 0; i < iCount; ++i)
	{
		::DragQueryFile(hDropInfo, i, szFileName, MAX_STR);

		//strRelative = CDirectoryMgr::ConvertRelativePath(szFileName);
		strFileName = ::PathFindFileName(szFileName); // ���ϸ� ���� �Լ�.

		lstrcpy(szFileName, strFileName);
		::PathRemoveExtension(szFileName); // Ȯ���� ����.

		m_ListBox.AddString(szFileName);
	}

	SettingHorizontalScrollSize();

	CDialog::OnDropFiles(hDropInfo);
}

void CMapTool::SettingHorizontalScrollSize()
{
	// ����Ʈ�ڽ��� ���� ��ũ�� Ȯ���ϱ�.

	CString strName = L"";

	int iSrcCX = 0, iDstCX = 0;

	CDC* pDC = m_ListBox.GetDC();

	for (int i = 0; i < m_ListBox.GetCount(); ++i)
	{
		m_ListBox.GetText(i, strName);

		// ���� ���ڿ��� ���̸� �ȼ� ������ ȯ��.
		iSrcCX = pDC->GetTextExtent(strName).cx;

		if (iDstCX < iSrcCX)
			iDstCX = iSrcCX;
	}

	m_ListBox.ReleaseDC(pDC);

	// ���� ����Ʈ�ڽ��� ������ �ִ� ���� ��ũ�� �������� Ŭ ��
	if (iDstCX > m_ListBox.GetHorizontalExtent())
		m_ListBox.SetHorizontalExtent(iDstCX); // ���� ��ũ�� ũ�� ����.
}


void CMapTool::OnLbnSelchangeList()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CFileDialog Dlg(FALSE, L".dat", L"���� ����.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CFileDialog Dlg(TRUE, L".dat", L"���� ����.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int iIndex = m_TileCombo.GetCurSel();

	if (-1 == iIndex)
		return;

	//CString strName = L"";
	//m_TileCombo.GetText(iIndex, strName);

	//int i = 0;

	//for (; i < strName.GetLength(); ++i)
	//{
	//	// ���� ���ڰ� �������� �������� �Ǻ�. ���ڶ�� true
	//	if (isdigit(strName[i]))
	//		break;
	//}

	//// Delete(index, count): ���� ���ڿ��� index�ڸ����� count��ŭ ����.
	//strName.Delete(0, i);

	//// ���� -> ������ ��ȯ.
	//m_iDrawID = _ttoi(strName);

	m_iDrawID = iIndex;
	m_iOptionID = iIndex;

	// ��ó ��Ʈ�ѿ� Ÿ�� �̸����� ���.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int iIndex = m_BackCombo.GetCurSel();

	if (-1 == iIndex)
		return;

	m_byDrawBackID = iIndex;

	m_pObjectMgr->GetList(OBJECT_BACK).front()->Change(m_byDrawBackID);

	m_pToolView->Invalidate(FALSE);
}


void CMapTool::OnCbnSelchangeWallCombo()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
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
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CMapTool::OnBnClickedTileRadio()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_ListBox.ResetContent();
}


void CMapTool::OnBnClickedDetailRadio()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
