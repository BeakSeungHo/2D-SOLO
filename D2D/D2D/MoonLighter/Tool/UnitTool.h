#pragma once
#include "afxwin.h"


// CUnitTool ��ȭ �����Դϴ�.

class CUnitTool : public CDialog
{
	DECLARE_DYNAMIC(CUnitTool)

public:
	CUnitTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CUnitTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UNITTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
	CString m_strInput; // ù��° EditControl�� �Էº���	
	CString m_strOutput; // �ι�° EditControl�� ��º���	
						
	CString m_strName;  // ĳ�����̸�	
	int m_iAtt; // ĳ���� ���ݷ�	
	int m_iDef; // ĳ���� ����

	CString m_strSearchName; // �̸� �˻�

public: // Control Variables
	CListBox m_ListBox;
	CButton m_Radio[3];
	CButton m_Check[3];

public: // User Variables
	map<wstring, UNIT_DATA*>	m_mapUnit;
};
