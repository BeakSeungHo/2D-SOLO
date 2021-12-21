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
	// CGameObject��(��) ���� ��ӵ�
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

private:
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	static CBreakable* Create(D3DXVECTOR3 vPos,BYTE byDrawID);

public:
	void SetOption(BYTE byOption);
};

