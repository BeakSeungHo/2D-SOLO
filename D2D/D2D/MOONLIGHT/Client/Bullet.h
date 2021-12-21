#pragma once
#include "GameObject.h"
class CBullet :
	public CGameObject
{
private:
	CBullet();

public:
	virtual ~CBullet();

public:
	// CGameObject을(를) 통해 상속됨
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

private:
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	static CBullet* Create(D3DXVECTOR3 vPos);

public:
	void ChangeState();
	void SetAngle(float fAngle);
	void SetColli(bool bColli);
	void SetState();
	float GetAngle();

private:
	bool		m_bCollision;
	float		m_fAngle;
	
	FRAME			m_tFrame;
	PLAYER_STATE	m_ePreState;
	PLAYER_STATE	m_eCurState;
	wstring			m_wstrImageKey;
};

