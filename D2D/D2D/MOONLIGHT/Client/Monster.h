#pragma once
#include "GameObject.h"
class CMonster :
	public CGameObject
{
private:
	CMonster();

public:
	virtual ~CMonster();

public:
	// CGameObject을(를) 통해 상속됨
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

private:
	virtual HRESULT Initialize() override;
	virtual void Release() override;

private:
	void Move();
	void ChangeState();
	

public:
	static CMonster* Create(D3DXVECTOR3 vPos);

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

