#pragma once
#include "GameObject.h"
class CBoss :
	public CGameObject
{
private:
	CBoss();
public:
	virtual ~CBoss();

public:
	// CGameObject을(를) 통해 상속됨
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

private:
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	static CBoss* Create();

private:
	void ChangeState();
	void PunchPattern();
	void RockPattern();
	void WavePattern();

public:
	void SetState(BOSS_STATE eState, wstring wstrImageKey);
	FRAME& GetFrame();
private:
	FRAME			m_tFrame;
	BOSS_STATE		m_ePreState;
	BOSS_STATE		m_eCurState;
	wstring			m_wstrImageKey;
	int				m_iCount;
};

