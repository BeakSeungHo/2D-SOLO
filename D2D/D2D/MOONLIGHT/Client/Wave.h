#pragma once
#include "GameObject.h"
class CWave :
	public CGameObject
{
private:
	CWave();
public:
	virtual ~CWave();

public:
	// CGameObject��(��) ���� ��ӵ�
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

private:
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	static CWave* Create();
};

