#pragma once

#ifndef __GAMEOBJECT_H__

class CGameObject
{
protected:
	CGameObject();

public:
	virtual ~CGameObject();

public:
	virtual int Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Render() PURE;

protected:
	virtual HRESULT Initialize() PURE;
	virtual void Release() PURE;

public:
	INFO& GetPInfo();
	TILE_INFO& GetInfo();
	void Change(const BYTE& byDrawID, const BYTE& byOption = 0);
	OBINFO& GetOInfo();
	ITEM_INFO& GetITinfo();
	void Invincibillity();
	void SetAttack(RECT Range);
	void SetPos(D3DXVECTOR3 vPos);
	bool PickTarget(const D3DXVECTOR3& vPos);

protected:
	CDeviceMgr*		m_pDeviceMgr;
	CTextureMgr*	m_pTextureMgr;
	CTimeMgr*		m_pTimeMgr;
	CObjectMgr*		m_pObjectMgr;
	TILE_INFO		m_tInfo;
	INFO			m_tPInfo;
	OBINFO			m_tOInfo;
	ITEM_INFO		m_tITinfo;
};

#define __GAMEOBJECT_H__
#endif
