#pragma once
#include "GameObject.h"
class CWall :
	public CGameObject
{
private:
	CWall();

public:
	virtual ~CWall();

public:
	// CGameObject을(를) 통해 상속됨
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

private:
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	static CWall* Create(D3DXVECTOR3 vPos, BYTE byDrawID);
};

