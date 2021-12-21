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
	virtual void MiniRender() PURE;

protected:
	virtual HRESULT Initialize() PURE;
	virtual void Release() PURE;

public:
	TILE_INFO GetInfo() const;
	void Change(const BYTE& byDrawID, const BYTE& byOption = 0);
	void SetPos(D3DXVECTOR3 vPos);
	bool PickTarget(const D3DXVECTOR3& vPos);

protected:
	CDeviceMgr*		m_pDeviceMgr;
	CTextureMgr*	m_pTextureMgr;
	TILE_INFO		m_tInfo;
	CToolView*		m_pView;
};

