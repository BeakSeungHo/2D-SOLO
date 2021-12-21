#pragma once
#include "GameObject.h"
class CUI :
	public CGameObject
{
private:
	CUI();
public:
	virtual ~CUI();

public:
	// CGameObject을(를) 통해 상속됨
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
private:
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	static CUI* Create();
	void SetBoss(bool bIsBoss);

private:
	bool		m_bIsBoss;
	wstring		m_strText;
};

