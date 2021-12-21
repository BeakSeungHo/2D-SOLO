// UnitTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "UnitTool.h"
#include "afxdialogex.h"


// CUnitTool 대화 상자입니다.

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


// CUnitTool 메시지 처리기입니다.


void CUnitTool::OnBnClickedPush()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	// UpdateData함수: DoDataExchange함수를 실행.
	// TRUE: 데이터 교환 방향이 "컨트롤 -> 변수"로 진행.
	UpdateData(TRUE);

	m_strOutput = m_strInput;

	// FALSE: 데이터 교환 방향이 "변수 -> 컨트롤"로 진행.
	UpdateData(FALSE);
}


void CUnitTool::OnBnClickedAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);	

	// CString::GetString()함수는 wstring::c_str()과 같은 기능을 한다.
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
		if (m_Radio[i].GetCheck()) // 현재 버튼이 체크되어 있으면 TRUE 반환.
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

	// 리스트박스 목록에 문자열을 추가한다.
	m_ListBox.AddString(m_strName);
}


void CUnitTool::OnLbnSelchangeList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int iIndex = m_ListBox.GetCurSel(); // 선택한 대상의 인덱스를 얻어옴.

	if (-1 == iIndex) // 없는 대상을 선택했을 때
		return;

	CString strName = L"";
	m_ListBox.GetText(iIndex, strName); // 인덱스에 해당하는 이름을 얻어옴.

	auto iter_find = m_mapUnit.find(strName.GetString());

	if (m_mapUnit.end() == iter_find)
		return;

	m_strName = iter_find->second->wstrName.c_str();
	m_iAtt = iter_find->second->iAtt;
	m_iDef = iter_find->second->iDef;

	for (int i = 0; i < 3; ++i)
	{
		m_Radio[i].SetCheck(FALSE); // 모든 버튼 체크 해제
		m_Check[i].SetCheck(FALSE);
	}

	// 현재 유닛이 갖고있는 직업에 체크.
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

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_Radio[0].SetCheck(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CUnitTool::OnEnChangeSearchName()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	auto iter_find = m_mapUnit.find(m_strSearchName.GetString());

	if (m_mapUnit.end() == iter_find)
		return;

	// 찾은 대상의 인덱스를 반환.
	int iIndex = m_ListBox.FindString(-1, m_strSearchName);

	if (-1 == iIndex)
		return;

	// 인덱스에 해당하는 대상을 선택하게 만듦.
	m_ListBox.SetCurSel(iIndex);
	OnLbnSelchangeList(); // 선택한 대상의 정보를 출력.
}


void CUnitTool::OnBnClickedDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

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

	// 인덱스에 해당하는 대상을 리스트박스에서 제거한다.
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

	m_strSearchName = L""; // 검색란 비움.

	UpdateData(FALSE);
}


void CUnitTool::OnBnClickedSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 저장 또는 불러오기에 쓰이는 대화상자 MFC 클래스.
	CFileDialog Dlg(FALSE, L".dat", L"제목 없음.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data Files(*.dat)|*.dat|Text Files(*.txt)|*.txt||", this);

	TCHAR szCurrentDir[MAX_STR] = L"";

	// 현재 작업경로를 얻어오는 함수.
	::GetCurrentDirectory(MAX_STR, szCurrentDir);

	// 경로에서 파일명 제거 함수. 제거할 파일명이 없으면 말단 폴더명 제거.
	::PathRemoveFileSpec(szCurrentDir);
	//::AfxMessageBox(szCurrentDir);	

	// PathCombine(A, B, C) -> A에 B와 C가 결합된 경로가 저장. 이 때 B와 C사이에 \\ 자동삽입.
	::PathCombine(szCurrentDir, szCurrentDir, L"Data");
	//::AfxMessageBox(szCurrentDir);

	//// 다이얼로그 생성 시 초기 경로 설정. (상대경로X)
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
		HANDLE hFile = CreateFile(Dlg.GetPathName(), GENERIC_READ, 0, nullptr,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (INVALID_HANDLE_VALUE == hFile)
			return;

		if (!m_mapUnit.empty())
		{
			for (auto& MyPair : m_mapUnit)
				SafeDelete(MyPair.second);

			m_mapUnit.clear();
			m_ListBox.ResetContent(); // 리스트박스 비우기.
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
