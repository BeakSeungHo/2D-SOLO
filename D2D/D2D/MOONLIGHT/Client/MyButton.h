#pragma once
#include "GameObject.h"
class CMyButton :
	public CGameObject
{
private:
	CMyButton();

public:
	virtual ~CMyButton();

public:
	// CGameObject을(를) 통해 상속됨
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	void SetINFO(wstring strText, D3DXVECTOR3 Pos, SCENE_TYPE eType = SCENE_END);
	void SetTarget(bool bTarget);
	bool GetTarget() const;
	SCENE_TYPE GetScene() const;

public:
	static CMyButton* Create();

private:
	SCENE_TYPE	m_eScene;
	wstring		m_strText;
	D3DXVECTOR3 m_vPos;
	CKeyMgr*	m_pKeyMgr;

	bool		m_bTarget;
};

