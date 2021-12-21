#pragma once
#include "GameObject.h"
class CInventory :
	public CGameObject
{
private:
	CInventory();
public:
	virtual ~CInventory();

public:
	// CGameObject을(를) 통해 상속됨
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

private:
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	static CInventory*	Create();
	void KeyInput();
	void SetDelete();

private:
	vector<CGameObject*>	m_vecInven;
	CKeyMgr*				m_pKeyMgr;
	wstring					m_strText;
	CGameObject*			m_Temp;
	bool					m_bDelete;
	int						m_iPreCount;
	int						m_iCount;
};

