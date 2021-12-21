#pragma once

#include "GameObject.h"

class CPlayer : public CGameObject
{
private:
	CPlayer();

public:
	~CPlayer();

public:
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

private:
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	static CPlayer* Create();

private:
	void KeyInput();
	void ChangeState();

private:
	CKeyMgr*		m_pKeyMgr;
	FRAME			m_tFrame;
	PLAYER_STATE	m_ePreState;
	PLAYER_STATE	m_eCurState;
	wstring			m_wstrImageKey;
	wstring			m_wstrWeaponImageKey;

	float			m_fSpeed;
	float			m_fCheck;
	float			m_fAttackSpeed;

	bool			m_bIsRoll;
	bool			m_bIsAttack;

	DWORD			m_dwCurWay;
	DWORD			m_dwCurWeapon;

	const DWORD		m_dwUP;
	const DWORD		m_dwDOWN;
	const DWORD		m_dwLEFT;
	const DWORD		m_dwRIGHT;
	
	const DWORD		m_dwBIGSWORD;
	const DWORD		m_dwSHORTSWORD;
	const DWORD		m_dwBOW;
	const DWORD		m_dwGLOVE;
	const DWORD		m_dwSPEAR;
};

