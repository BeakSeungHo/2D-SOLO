// UnitTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "UnitTool.h"
#include "afxdialogex.h"


// CUnitTool ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CUnitTool, CDialog)

CUnitTool::CUnitTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_UNITTOOL, pParent)
	, m_strInput(_T(""))
	, m_strOutput(_T(""))
	, m_strName(_T(""))
	, m_iAtt(0)
	, m_iDef(0)
	, m_strSearchName(_T(""))
{

}

CUnitTool::~CUnitTool()
{
	for (auto& MyPair : m_mapUnit)
		SafeDelete(MyPair.second);

	m_mapUnit.clear();
}

void CUnitTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strInput);
	DDX_Text(pDX, IDC_EDIT2, m_strOutput);
	DDX_Text(pDX, IDC_EDIT3, m_strName);
	DDX_Text(pDX, IDC_EDIT4, m_iAtt);
	DDX_Text(pDX, IDC_EDIT5, m_iDef);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_RADIO1, m_Radio[0]);
	DDX_Control(pDX, IDC_RADIO2, m_Radio[1]);
	DDX_Control(pDX, IDC_RADIO3, m_Radio[2]);
	DDX_Control(pDX, IDC_CHECK1, m_Check[0]);
	DDX_Control(pDX, IDC_CHECK2, m_Check[1]);
	DDX_Control(pDX, IDC_CHECK3, m_Check[2]);
	DDX_Text(pDX, IDC_EDIT6, m_strSearchName);
}


BEGIN_MESSAGE_MAP(CUnitTool, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CUnitTool::OnBnClickedPush)
	ON_BN_CLICKED(IDC_BUTTON2, &CUnitTool::OnBnClickedAdd)
	ON_LBN_SELCHANGE(IDC_LIST1, &CUnitTool::OnLbnSelchangeList)
	ON_EN_CHANGE(IDC_EDIT6, &CUnitTool::OnEnChangeSearchName)
	ON_BN_CLICKED(IDC_BUTTON3, &CUnitTool::OnBnClickedDelete)
	ON_BN_CLICKED(IDC_BUTTON4, &CUnitTool::OnBnClickedSave)
	ON_BN_CLICKED(IDC_BUTTON5, &CUnitTool::OnBnClickedLoad)
END_MESSAGE_MAP()


// CUnitTool �޽��� ó�����Դϴ�.


void CUnitTool::OnBnClickedPush()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
	// UpdateData�Լ�: DoDataExchange�Լ��� ����.
	// TRUE: ������ ��ȯ ������ "��Ʈ�� -> ����"�� ����.
	UpdateData(TRUE);

	m_strOutput = m_strInput;

	// FALSE: ������ ��ȯ ������ "���� -> ��Ʈ��"�� ����.
	UpdateData(FALSE);
}


void CUnitTool::OnBnClickedAdd()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);	

	// CString::GetString()�Լ��� wstring::c_str()�� ���� ����� �Ѵ�.
	auto iter_find = m_mapUnit.find(m_strName.GetString());

	if (m_mapUnit.end() != iter_find)
		return;

	UNIT_DATA* pUnit = new UNIT_DATA;
	pUnit->wstrName = m_strName.GetString();
	pUnit->iAtt = m_iAtt;
	pUnit->iDef = m_iDef;
	pUnit->iItem = 0;

	for (int i = 0; i < 3; ++i)
	{
		if (m_Radio[i].GetCheck()) // ���� ��ư�� üũ�Ǿ� ������ TRUE ��ȯ.
		{
			pUnit->iJobIndex = i;
			break;
		}
	}	

	if (m_Check[0].GetCheck())
		pUnit->iItem |= RUBY;
	if (m_Check[1].GetCheck())
		pUnit->iItem |= SAPPHIRE;
	if (m_Check[2].GetCheck())
		pUnit->iItem |= DIAMOND;

	m_mapUnit.insert(make_pair(pUnit->wstrName, pUnit));

	// ����Ʈ�ڽ� ��Ͽ� ���ڿ��� �߰��Ѵ�.
	m_ListBox.AddString(m_strName);
}


void CUnitTool::OnLbnSelchangeList()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	int iIndex = m_ListBox.GetCurSel(); // ������ ����� �ε����� ����.

	if (-1 == iIndex) // ���� ����� �������� ��
		return;

	CString strName = L"";
	m_ListBox.GetText(iIndex, strName); // �ε����� �ش��ϴ� �̸��� ����.

	auto iter_find = m_mapUnit.find(strName.GetString());

	if (m_mapUnit.end() == iter_find)
		return;

	m_strName = iter_find->second->wstrName.c_str();
	m_iAtt = iter_find->second->iAtt;
	m_iDef = iter_find->second->iDef;

	for (int i = 0; i < 3; ++i)
	{
		m_Radio[i].SetCheck(FALSE); // ��� ��ư üũ ����
		m_Check[i].SetCheck(FALSE);
	}

	// ���� ������ �����ִ� ������ üũ.
	m_Radio[iter_find->second->iJobIndex].SetCheck(TRUE); 

	if (RUBY & iter_find->second->iItem)
		m_Check[0].SetCheck(TRUE);
	if (SAPPHIRE & iter_find->second->iItem)
		m_Check[1].SetCheck(TRUE);
	if (DIAMOND & iter_find->second->iItem)
		m_Check[2].SetCheck(TRUE);

	UpdateData(FALSE);
}


BOOL CUnitTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_Radio[0].SetCheck(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CUnitTool::OnEnChangeSearchName()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	auto iter_find = m_mapUnit.find(m_strSearchName.GetString());

	if (m_mapUnit.end() == iter_find)
		return;

	// ã�� ����� �ε����� ��ȯ.
	int iIndex = m_ListBox.FindString(-1, m_strSearchName);

	if (-1 == iIndex)
		return;

	// �ε����� �ش��ϴ� ����� �����ϰ� ����.
	m_ListBox.SetCurSel(iIndex);
	OnLbnSelchangeList(); // ������ ����� ������ ���.
}


void CUnitTool::OnBnClickedDelete()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	int iIndex = m_ListBox.GetCurSel();

	if (-1 == iIndex)
		return;

	CString strFindName = L"";
	m_ListBox.GetText(iIndex, strFindName);

	auto iter_find = m_mapUnit.find(strFindName.GetString());

	if (m_mapUnit.end() == iter_find)
		return;

	SafeDelete(iter_find->second);
	m_mapUnit.erase(iter_find);

	// �ε����� �ش��ϴ� ����� ����Ʈ�ڽ����� �����Ѵ�.
	m_ListBox.DeleteString(iIndex);

	m_strName = L"";
	m_iAtt = 0;
	m_iDef = 0;

	for (int i = 0; i < 3; ++i)
	{
		m_Radio[i].SetCheck(FALSE);
		m_Check[i].SetCheck(FALSE);
	}

	m_Radio[0].SetCheck(TRUE);

	m_strSearchName = L""; // �˻��� ���.

	UpdateData(FALSE);
}


void CUnitTool::OnBnClickedSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	// ���� �Ǵ� �ҷ����⿡ ���̴� ��ȭ���� MFC Ŭ����.
	CFileDialog Dlg(FALSE, L".dat", L"���� ����.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data Files(*.dat)|*.dat|Text Files(*.txt)|*.txt||", this);

	TCHAR szCurrentDir[MAX_STR] = L"";

	// ���� �۾���θ� ������ �Լ�.
	::GetCurrentDirectory(MAX_STR, szCurrentDir);

	// ��ο��� ���ϸ� ���� �Լ�. ������ ���ϸ��� ������ ���� ������ ����.
	::PathRemoveFileSpec(szCurrentDir);
	//::AfxMessageBox(szCurrentDir);	

	// PathCombine(A, B, C) -> A�� B�� C�� ���յ� ��ΰ� ����. �� �� B�� C���̿� \\ �ڵ�����.
	::PathCombine(szCurrentDir, szCurrentDir, L"Data");
	//::AfxMessageBox(szCurrentDir);

	//// ���̾�α� ���� �� �ʱ� ��� ����. (�����X)
	Dlg.m_ofn.lpstrInitialDir = szCurrentDir;

	if (IDOK == Dlg.DoModal())
	{
		//::AfxMessageBox(Dlg.GetPathName());

		HANDLE hFile = CreateFile(Dlg.GetPathName(), GENERIC_WRITE, 0, nullptr,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (INVALID_HANDLE_VALUE == hFile)
			return;

		size_t iLen = 0;
		DWORD dwBytes = 0;

		for (auto& MyPair : m_mapUnit)
		{
			iLen = MyPair.second->wstrName.length() + 1;

			WriteFile(hFile, &iLen, sizeof(size_t), &dwBytes, nullptr);
			WriteFile(hFile, MyPair.second->wstrName.c_str(), sizeof(wchar_t) * iLen, &dwBytes, nullptr);
			WriteFile(hFile, &MyPair.second->iAtt, sizeof(int), &dwBytes, nullptr);
			WriteFile(hFile, &MyPair.second->iDef, sizeof(int), &dwBytes, nullptr);
			WriteFile(hFile, &MyPair.second->iJobIndex, sizeof(int), &dwBytes, nullptr);
			WriteFile(hFile, &MyPair.second->iItem, sizeof(int), &dwBytes, nullptr);
		}

		CloseHandle(hFile);
	}
}


void CUnitTool::OnBnClickedLoad()
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
		HANDLE hFile = CreateFile(Dlg.GetPathName(), GENERIC_READ, 0, nullptr,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (INVALID_HANDLE_VALUE == hFile)
			return;

		if (!m_mapUnit.empty())
		{
			for (auto& MyPair : m_mapUnit)
				SafeDelete(MyPair.second);

			m_mapUnit.clear();
			m_ListBox.ResetContent(); // ����Ʈ�ڽ� ����.
		}
		
		DWORD dwBytes = 0;

		size_t iLen = 0;
		wchar_t* pString = nullptr;
		int iAtt = 0, iDef = 0, iJobIndex = 0, iItem = 0;	

		UNIT_DATA* pUnit = nullptr;

		while(true)
		{
			ReadFile(hFile, &iLen, sizeof(size_t), &dwBytes, nullptr);

			pString = new wchar_t[iLen];
			ReadFile(hFile, pString, sizeof(wchar_t) * iLen, &dwBytes, nullptr);

			ReadFile(hFile, &iAtt, sizeof(int), &dwBytes, nullptr);
			ReadFile(hFile, &iDef, sizeof(int), &dwBytes, nullptr);
			ReadFile(hFile, &iJobIndex, sizeof(int), &dwBytes, nullptr);
			ReadFile(hFile, &iItem, sizeof(int), &dwBytes, nullptr);

			if (0 == dwBytes)
			{
				SafeDelete_Array(pString);
				break;
			}

			pUnit = new UNIT_DATA;
			pUnit->wstrName = pString;
			SafeDelete_Array(pString);

			pUnit->iAtt = iAtt;
			pUnit->iDef = iDef;
			pUnit->iJobIndex = iJobIndex;
			pUnit->iItem = iItem;

			m_mapUnit.insert(make_pair(pUnit->wstrName, pUnit));
			m_ListBox.AddString(pUnit->wstrName.c_str());
		}

		CloseHandle(hFile);
	}
}
