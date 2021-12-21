#pragma once
#include "GameObject.h"

class CToolView;
class CTerrain : public CGameObject
{
private:
	CTerrain();

public:
	virtual ~CTerrain();

public:
	int GetTileIndex(const D3DXVECTOR3& vPos);

public:
	// CGameObject을(를) 통해 상속됨
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void MiniRender() override;

private:
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	void TileChange(const D3DXVECTOR3& vPos, const BYTE& byDrawID, const BYTE& byOption = 0);
	vector<TILE_INFO*>& GetVecTile();

private:
	bool IsPicking(const D3DXVECTOR3& vPos, int iIndex);

public:
	static CTerrain* Create(CToolView* pView = nullptr);

private:
	vector<TILE_INFO*>	m_vecTile;
};

