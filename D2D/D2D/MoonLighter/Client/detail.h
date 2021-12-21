#pragma once
#include "GameObject.h"
class CDetail :
	public CGameObject
{
private:
	CDetail();

public:
	virtual ~CDetail();

public:
	// CGameObject��(��) ���� ��ӵ�
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

private:	
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	static CDetail* Create(D3DXVECTOR3 vPos, BYTE byDrawID );

private:
	float		m_fAngle;
};

