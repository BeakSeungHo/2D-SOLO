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

public:
	void SetSystem(bool bSystem);
	bool GetIsRoll();
	int	 GetPotionCount();
	vector<CGameObject*>& GetItemVec();
	void PushItem(CGameObject* Item);
	void PopItem(int i);
	void SwapItem(int i, int j);

private:
	void KeyInput();
	void ChangeState();
	

private:
	CKeyMgr*				m_pKeyMgr;
	FRAME					m_tFrame;
	PLAYER_STATE			m_ePreState;
	PLAYER_STATE			m_eCurState;
	wstring					m_wstrImageKey;
	wstring					m_wstrWeaponImageKey;
	vector<CGameObject*>	m_vecItem;
	
	int				m_iPotionCount;
	float			m_fCheck;
	float			m_fSwingCheck;
	float			m_fMotionSpeed;

	bool			m_bIsRoll;
	bool			m_bIsAttack;
	bool			m_bIsSwing;
	bool			m_bIsSystem;
	bool			m_bIsInven;

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

