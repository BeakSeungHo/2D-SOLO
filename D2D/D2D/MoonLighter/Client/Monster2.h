#pragma once
#include "GameObject.h"
class CMonster2 :
	public CGameObject
{
private:
	CMonster2();

public:
	virtual ~CMonster2();

public:
	// CGameObject을(를) 통해 상속됨
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

private:
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	static CMonster2* Create(D3DXVECTOR3 vPos);
	
private:
	void SetState();
	void ChangeState();
private:
	FRAME			m_tFrame;
	PLAYER_STATE	m_ePreState;
	PLAYER_STATE	m_eCurState;
	wstring			m_wstrImageKey;

	CGameObject*	m_pTarget;

	DWORD			m_dwCurWay;

	const DWORD		m_dwUP;
	const DWORD		m_dwDOWN;
	const DWORD		m_dwLEFT;
	const DWORD		m_dwRIGHT;
};

