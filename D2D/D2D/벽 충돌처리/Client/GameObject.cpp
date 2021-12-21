#include "stdafx.h"
#include "GameObject.h"

CGameObject::CGameObject()
	: m_pDeviceMgr(CDeviceMgr::GetInstance()),
	m_pTextureMgr(CTextureMgr::GetInstance()),
	m_pTimeMgr(CTimeMgr::GetInstance())
{
}


CGameObject::~CGameObject()
{
}

INFO & CGameObject::GetPInfo()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_tPInfo;
}

TILE_INFO& CGameObject::GetInfo()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_tInfo;
}

void CGameObject::Change(const BYTE & byDrawID, const BYTE & byOption)
{
	m_tInfo.byDrawID = byDrawID;
	m_tInfo.byOption = byOption;
}

void CGameObject::SetPos(D3DXVECTOR3 vPos)
{
	m_tPInfo.vPos = vPos;
	m_tInfo.vPos = vPos;
}

bool CGameObject::PickTarget(const D3DXVECTOR3 & vPos)
{

	D3DXVECTOR3 vPoint[4] =
	{
		D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y + TILECY * 0.5f, 0.f),
		D3DXVECTOR3(m_tInfo.vPos.x + TILECX * 0.5f, m_tInfo.vPos.y, 0.f),
		D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y - TILECY * 0.5f, 0.f),
		D3DXVECTOR3(m_tInfo.vPos.x - TILECX * 0.5f, m_tInfo.vPos.y, 0.f)
	};

	// 각 꼭지점으로부터 시계방향으로 방향벡터들을 구함.
	D3DXVECTOR3 vDir[4] =
	{
		vPoint[1] - vPoint[0],
		vPoint[2] - vPoint[1],
		vPoint[3] - vPoint[2],
		vPoint[0] - vPoint[3],
	};

	// 위에서 구한 방향벡터들의 각 법선벡터들을 구한다.
	D3DXVECTOR3 vNormal[4] = {};

	for (int i = 0; i < 4; ++i)
		D3DXVec3Cross(&vNormal[i], &D3DXVECTOR3(0.f, 0.f, 1.f), &vDir[i]);

	// 각 꼭지점에서부터 마우스위치로의 방향벡터를 구한다.
	D3DXVECTOR3 vMouseDir[4] =
	{
		vPos - vPoint[0],
		vPos - vPoint[1],
		vPos - vPoint[2],
		vPos - vPoint[3]
	};

	// vMouseDir과 vNormal을 각각 내적해서 모두 둔각(음수)이 나오면 TRUE!
	for (int i = 0; i < 4; ++i)
	{
		if (0 < D3DXVec3Dot(&vNormal[i], &vMouseDir[i]))
			return false;
	}

	return true;
}
