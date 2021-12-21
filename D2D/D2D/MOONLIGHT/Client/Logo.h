#pragma once
#include "Scene.h"
class CLogo : public CScene
{
private:
	CLogo();

public:
	virtual ~CLogo();


public:
	// CScene을(를) 통해 상속됨
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

private:
	virtual HRESULT Initialize() override;
	virtual void Release() override;

private:
	int KeyInput();
	bool WallMove();

public:
	static CLogo* Create();

private:
	FRAME		m_tFrame;
	CKeyMgr*	m_pKeyMgr;

	bool		m_bNext;
	float		m_fMoveWall;
	float		m_fLogoTime;
};

