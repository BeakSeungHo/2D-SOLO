#pragma once
#include "GameObject.h"
class CMonster :
	public CGameObject
{
private:
	CMonster();

public:
	virtual ~CMonster();

public:
	// CGameObject��(��) ���� ��ӵ�
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

private:
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	static CMonster* Create();


};

