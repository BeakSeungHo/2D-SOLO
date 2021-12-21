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
	// CGameObject을(를) 통해 상속됨
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void MiniRender() override;

private:
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	static CBack* Create(D3DXVECTOR3 vPos, CToolView* pView = nullptr);
};

