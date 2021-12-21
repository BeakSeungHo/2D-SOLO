#pragma once
#include "GameObject.h"
class CRock :
	public CGameObject
{
public:
	CRock();
	virtual ~CRock();

public:
	// CGameObject을(를) 통해 상속됨
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

private:
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	static CRock* Create(D3DXVECTOR3 vPos);

private:
	FRAME			m_tFrame;
	float			m_fDeleteTime;
};

