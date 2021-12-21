// MyForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "MyForm.h"


// CMyForm

IMPLEMENT_DYNCREATE(CMyForm, CFormView)

CMyForm::CMyForm()
	: CFormView(IDD_MYFORM),
	m_MySheet(L"MySheet")
{

}

CMyForm::~CMyForm()
{
}

void CMyForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyForm, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CMyForm::OnBnClickedUnitTool)
	ON_BN_CLICKED(IDC_BUTTON6, &CMyForm::OnBnClickedMapTool)
	ON_BN_CLICKED(IDC_BUTTON7, &CMyForm::OnBnClickedPathTool)
	ON_BN_CLICKED(IDC_BUTTON8, &CMyForm::OnBnClickedSheet)
END_MESSAGE_MAP()


// CMyForm 진단입니다.

#ifdef _DEBUG
void CMyForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMyForm 메시지 처리기입니다.


void CMyForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	// MFC 폰트 오브젝트 생성.
	m_Font.CreatePointFont(200, L"consolas");

	// ID값을 통해서 현재 다이얼로그에 배치된 대상을 얻어올 수 있다.
	GetDlgItem(IDC_BUTTON1)->SetFont(&m_Font); // 버튼에 폰트 적용하기
	GetDlgItem(IDC_BUTTON6)->SetFont(&m_Font); // 버튼에 폰트 적용하기
	GetDlgItem(IDC_BUTTON7)->SetFont(&m_Font); // 버튼에 폰트 적용하기
	GetDlgItem(IDC_BUTTON8)->SetFont(&m_Font); // 버튼에 폰트 적용하기

	// 다이얼로그 생성
	m_UnitTool.Create(IDD_UNITTOOL);
	m_MapTool.Create(IDD_MAPTOOL);
	m_PathTool.Create(IDD_PATHTOOL);

	// Sheet 생성
	m_MySheet.Create(this, WS_SYSMENU | WS_POPUP | WS_CAPTION | DS_MODALFRAME | DS_CONTEXTHELP);
}

void CMyForm::OnBnClickedUnitTool()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//::AfxMessageBox(L"Unit Tool"); // MFC 메시지박스 함수.

	// 아직 생성되지 않았다면 GetSafeHwnd함수는 nullptr을 반환.
	NULL_CHECK_MSG(m_UnitTool.GetSafeHwnd(), L"UnitTool is null");
	m_UnitTool.ShowWindow(SW_SHOW); // SW_SHOW: 창모양으로 출력.
}


void CMyForm::OnBnClickedMapTool()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	NULL_CHECK_MSG(m_MapTool.GetSafeHwnd(), L"MapTool is null");
	m_MapTool.ShowWindow(SW_SHOW); // SW_SHOW: 창모양으로 출력.
}


void CMyForm::OnBnClickedPathTool()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	NULL_CHECK_MSG(m_PathTool.GetSafeHwnd(), L"PathTool is null");
	m_PathTool.ShowWindow(SW_SHOW); // SW_SHOW: 창모양으로 출력.
}


void CMyForm::OnBnClickedSheet()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	NULL_CHECK_MSG(m_MySheet.GetSafeHwnd(), L"MySheet is null");
	m_MySheet.ShowWindow(SW_SHOW); // SW_SHOW: 창모양으로 출력.
}
