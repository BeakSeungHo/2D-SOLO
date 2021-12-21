#pragma once
#include "afxwin.h"


// CUnitTool 대화 상자입니다.

class CUnitTool : public CDialog
{
	DECLARE_DYNAMIC(CUnitTool)

public:
	CUnitTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CUnitTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UNITTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public: // Message Functions
	afx_msg void OnBnClickedPush();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnLbnSelchangeList();
	afx_msg void OnEnChangeSearchName();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedLoad();

public:
	virtual BOOL OnInitDialog();

public:	// Value Variables
	CString m_strInput; // 첫번째 EditControl의 입력변수	
	CString m_strOutput; // 두번째 EditControl의 출력변수	
						
	CString m_strName;  // 캐릭터이름	
	int m_iAtt; // 캐릭터 공격력	
	int m_iDef; // 캐릭터 방어력

	CString m_strSearchName; // 이름 검색

public: // Control Variables
	CListBox m_ListBox;
	CButton m_Radio[3];
	CButton m_Check[3];

public: // User Variables
	map<wstring, UNIT_DATA*>	m_mapUnit;
};
