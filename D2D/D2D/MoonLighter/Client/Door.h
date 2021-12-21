#pragma once
#include "GameObject.h"
class CDoor :
	public CGameObject
{
private:
	CDoor();

public:
	virtual ~CDoor();

public:
	// CGameObject을(를) 통해 상속됨
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

private:
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	void SetBool(bool bClose);
	void SetAngle(float fAngle);
	float GetAngle();

public:
	static CDoor* Create(D3DXVECTOR3 vPos);

private:
	bool	m_bClose;
	float	m_fAngle;
	FRAME	m_tFrame;
};

