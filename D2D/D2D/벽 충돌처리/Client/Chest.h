#pragma once
#include "GameObject.h"
class CChest :
	public CGameObject
{
public:
	CChest();
	virtual ~CChest();

public:
	// CGameObject을(를) 통해 상속됨
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

private:
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	static CChest* Create(D3DXVECTOR3 vPos);
};

