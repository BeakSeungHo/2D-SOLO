// MyForm.cpp : ���� �����Դϴ�.
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


// CMyForm �����Դϴ�.

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


// CMyForm �޽��� ó�����Դϴ�.


void CMyForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	// MFC ��Ʈ ������Ʈ ����.
	m_Font.CreatePointFont(200, L"consolas");

	// ID���� ���ؼ� ���� ���̾�α׿� ��ġ�� ����� ���� �� �ִ�.
	GetDlgItem(IDC_BUTTON1)->SetFont(&m_Font); // ��ư�� ��Ʈ �����ϱ�
	GetDlgItem(IDC_BUTTON6)->SetFont(&m_Font); // ��ư�� ��Ʈ �����ϱ�
	GetDlgItem(IDC_BUTTON7)->SetFont(&m_Font); // ��ư�� ��Ʈ �����ϱ�
	GetDlgItem(IDC_BUTTON8)->SetFont(&m_Font); // ��ư�� ��Ʈ �����ϱ�

	// ���̾�α� ����
	m_UnitTool.Create(IDD_UNITTOOL);
	m_MapTool.Create(IDD_MAPTOOL);
	m_PathTool.Create(IDD_PATHTOOL);

	// Sheet ����
	m_MySheet.Create(this, WS_SYSMENU | WS_POPUP | WS_CAPTION | DS_MODALFRAME | DS_CONTEXTHELP);
}

void CMyForm::OnBnClickedUnitTool()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//::AfxMessageBox(L"Unit Tool"); // MFC �޽����ڽ� �Լ�.

	// ���� �������� �ʾҴٸ� GetSafeHwnd�Լ��� nullptr�� ��ȯ.
	NULL_CHECK_MSG(m_UnitTool.GetSafeHwnd(), L"UnitTool is null");
	m_UnitTool.ShowWindow(SW_SHOW); // SW_SHOW: â������� ���.
}


void CMyForm::OnBnClickedMapTool()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	NULL_CHECK_MSG(m_MapTool.GetSafeHwnd(), L"MapTool is null");
	m_MapTool.ShowWindow(SW_SHOW); // SW_SHOW: â������� ���.
}


void CMyForm::OnBnClickedPathTool()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	NULL_CHECK_MSG(m_PathTool.GetSafeHwnd(), L"PathTool is null");
	m_PathTool.ShowWindow(SW_SHOW); // SW_SHOW: â������� ���.
}


void CMyForm::OnBnClickedSheet()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	NULL_CHECK_MSG(m_MySheet.GetSafeHwnd(), L"MySheet is null");
	m_MySheet.ShowWindow(SW_SHOW); // SW_SHOW: â������� ���.
}
