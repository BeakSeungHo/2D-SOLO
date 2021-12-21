#pragma once
#include "GameObject.h"
class CBack :
	public CGameObject
{
private:
	CBack();

public:
	virtual ~CBack();

public:
	// CGameObject��(��) ���� ��ӵ�
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

private:
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	static CBack* Create(D3DXVECTOR3 vPos);
};

