#pragma once
#include "afxwin.h"


// CMapTool 대화 상자입니다.
class CGameObject;
class CToolView;
class CMapTool : public CDialog
{
	DECLARE_DYNAMIC(CMapTool)

public:
	CMapTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMapTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAPTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();


	DECLARE_MESSAGE_MAP()
public: // Message Functions
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnLbnSelchangeList();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedLoad();
	afx_msg void OnCbnSelchangeTileCombo();
	afx_msg void OnCbnSelchangeBackCombo();
	afx_msg void OnCbnSelchangeWallCombo();

public: // User Functions
	void SettingHorizontalScrollSize();

public:	// Control Variables
	CListBox m_ListBox;
	CComboBox m_TileCombo;
	CComboBox m_BackCombo;
	CComboBox m_WallCombo;
	CStatic m_Picture;
	CStatic m_Picture2;
	CButton m_Radio[4];

public: // User Variables
	int m_iDrawID;
	int m_iOptionID;
	BYTE m_byDrawID;
	BYTE m_byDrawBackID;
	BYTE m_byDrawWallID;

	CToolView*		m_pToolView;
	CGameObject*	m_pTarget;

	CDeviceMgr*		m_pDeviceMgr;
	CTextureMgr*	m_pTextureMgr;
	CObjectMgr*		m_pObjectMgr;

	
	afx_msg void OnBnClickedTileRadio();
	afx_msg void OnBnClickedDetailRadio();
	afx_msg void OnBnClickedBreakableRadio();
	afx_msg void OnBnClickedAdd();
};
