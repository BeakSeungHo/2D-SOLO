#pragma once
#include "GameObject.h"
class CBreakable :
	public CGameObject
{
private:
	CBreakable();

public:
	virtual ~CBreakable();

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
	static CBreakable* Create(D3DXVECTOR3 vPos,BYTE byDrawID, CToolView* pView = nullptr);

public:
	void SetOption(BYTE byOption);
};

