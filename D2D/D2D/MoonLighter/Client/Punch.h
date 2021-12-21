#pragma once
#include "GameObject.h"
class CPunch :
	public CGameObject
{
private:
	CPunch();

public:
	virtual ~CPunch();

public:
	// CGameObject을(를) 통해 상속됨
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

private:
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	static CPunch* Create();

private:
	FRAME			m_tFrame;
	wstring			m_wstrImageKey;
	CGameObject*	m_pTarget;
	float			m_fWaitTime;
	int				m_iCount;
};

