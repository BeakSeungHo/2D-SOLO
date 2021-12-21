#include "stdafx.h"
#include "GameObject.h"

CGameObject::CGameObject()
	: m_pDeviceMgr(CDeviceMgr::GetInstance()),
	m_pTextureMgr(CTextureMgr::GetInstance()),
	m_pTimeMgr(CTimeMgr::GetInstance()),
	m_pObjectMgr(CObjectMgr::GetInstance())
{
}


CGameObject::~CGameObject()
{
}

INFO & CGameObject::GetPInfo()
{
	// TODO: ���⿡ ��ȯ ������ �����մϴ�.
	return m_tPInfo;
}

TILE_INFO& CGameObject::GetInfo()
{
	// TODO: ���⿡ ��ȯ ������ �����մϴ�.
	return m_tInfo;
}

void CGameObject::Change(const BYTE & byDrawID, const BYTE & byOption)
{
	m_tInfo.byDrawID = byDrawID;
	m_tInfo.byOption = byOption;
}

OBINFO& CGameObject::GetOInfo()
{
	return m_tOInfo;
}

ITEM_INFO& CGameObject::GetITinfo()
{
	return m_tITinfo;
}

void CGameObject::Invincibillity()
{
	if (m_tOInfo.fInvinTime >= m_tOInfo.fMaxInvinTime)
	{
		m_tOInfo.Alpha = 0;
		m_tOInfo.fInvinTime = 0;
		m_tOInfo.binvincibility = false;
	}
	else if (m_tOInfo.binvincibility)
	{
		m_tOInfo.fInvinTime += m_pTimeMgr->GetDelta();
		m_tOInfo.Alpha = 255 * ((m_tOInfo.Alpha/255) ^ 1);
	}
}

void CGameObject::SetAttack(RECT Range)
{
	m_tPInfo.tAttackRange = Range;
}

void CGameObject::SetPos(D3DXVECTOR3 vPos)
{
	m_tPInfo.vPos = vPos;
	m_tInfo.vPos = vPos;
	m_tITinfo.vPos = vPos;
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

	// �� ���������κ��� �ð�������� ���⺤�͵��� ����.
	D3DXVECTOR3 vDir[4] =
	{
		vPoint[1] - vPoint[0],
		vPoint[2] - vPoint[1],
		vPoint[3] - vPoint[2],
		vPoint[0] - vPoint[3],
	};

	// ������ ���� ���⺤�͵��� �� �������͵��� ���Ѵ�.
	D3DXVECTOR3 vNormal[4] = {};

	for (int i = 0; i < 4; ++i)
		D3DXVec3Cross(&vNormal[i], &D3DXVECTOR3(0.f, 0.f, 1.f), &vDir[i]);

	// �� �������������� ���콺��ġ���� ���⺤�͸� ���Ѵ�.
	D3DXVECTOR3 vMouseDir[4] =
	{
		vPos - vPoint[0],
		vPos - vPoint[1],
		vPos - vPoint[2],
		vPos - vPoint[3]
	};

	// vMouseDir�� vNormal�� ���� �����ؼ� ��� �а�(����)�� ������ TRUE!
	for (int i = 0; i < 4; ++i)
	{
		if (0 < D3DXVec3Dot(&vNormal[i], &vMouseDir[i]))
			return false;
	}

	return true;
}
