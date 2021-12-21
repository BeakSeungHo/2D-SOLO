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
	// CGameObject을(를) 통해 상속됨
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

private:
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	static CMonster* Create();


};

