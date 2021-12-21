#pragma once
#include "GameObject.h"
class CChest :
	public CGameObject
{
public:
	CChest();
	virtual ~CChest();

public:
	// CGameObject��(��) ���� ��ӵ�
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

private:
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	static CChest* Create(D3DXVECTOR3 vPos);
};

