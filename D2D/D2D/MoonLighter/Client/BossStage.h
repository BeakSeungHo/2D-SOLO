#pragma once
#include "Scene.h"
class CBossStage :
	public CScene
{
private:
	CBossStage();
public:
	virtual ~CBossStage();

public:
	// CScene��(��) ���� ��ӵ�
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

private:
	virtual HRESULT Initialize() override;
	virtual void Release() override;

private:
	void ScrollOffSet();
	
public:
	static CBossStage* Create();
private:
	bool	m_bCutSceen;
};

