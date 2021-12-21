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
	// CGameObject��(��) ���� ��ӵ�
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

