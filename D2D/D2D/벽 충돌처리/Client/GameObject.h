#pragma once
class CToolView;
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
	void SetPos(D3DXVECTOR3 vPos);
	bool PickTarget(const D3DXVECTOR3& vPos);

protected:
	CDeviceMgr*		m_pDeviceMgr;
	CTextureMgr*	m_pTextureMgr;
	CTimeMgr*		m_pTimeMgr;
	TILE_INFO		m_tInfo;
	INFO			m_tPInfo;
};

