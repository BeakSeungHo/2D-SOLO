#include "stdafx.h"
#include "Breakable.h"

CBreakable::CBreakable()
{
}


CBreakable::~CBreakable()
{
}

int CBreakable::Update()
{
	CObjectMgr::GetInstance()->AddLayer(LAYER_BACK, this);

	return 0;
}

void CBreakable::LateUpdate()
{
}

void CBreakable::Render()
{
	D3DXMATRIX matScale, matTrans;

	const TEX_INFO* pTexInfo = nullptr;
	
	TCHAR szIndexNum[MIN_STR] = L"";

	if (0 == m_tInfo.byOption)
	{
		pTexInfo = m_pTextureMgr->GetTexInfo(L"Dungeon", L"Breakable", m_tInfo.byDrawID);
		NULL_CHECK(pTexInfo);

		D3DXMatrixScaling(&matScale,
			m_tInfo.vSize.x,
			m_tInfo.vSize.y,
			m_tInfo.vSize.z);
		D3DXMatrixTranslation(&matTrans,
			m_tInfo.vPos.x - CScrollMgr::GetScrollPos().x,
			m_tInfo.vPos.y - CScrollMgr::GetScrollPos().y,
			m_tInfo.vPos.z);

		m_tInfo.fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		m_tInfo.fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		m_pDeviceMgr->GetSprite()->SetTransform(&(matScale * matTrans));
		m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(m_tInfo.fCenterX, m_tInfo.fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else
	{
		pTexInfo = m_pTextureMgr->GetTexInfo(L"Dugeon", L"Breakable_Rest", m_tInfo.byDrawID);
		NULL_CHECK(pTexInfo);

		D3DXMatrixScaling(&matScale,
			m_tInfo.vSize.x,
			m_tInfo.vSize.y,
			m_tInfo.vSize.z);
		D3DXMatrixTranslation(&matTrans,
			m_tInfo.vPos.x - CScrollMgr::GetScrollPos().x,
			m_tInfo.vPos.y - CScrollMgr::GetScrollPos().y,
			m_tInfo.vPos.z);

		m_tInfo.fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		m_tInfo.fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		m_pDeviceMgr->GetSprite()->SetTransform(&(matScale * matTrans));
		m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(m_tInfo.fCenterX, m_tInfo.fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	
}


HRESULT CBreakable::Initialize()
{
	ZeroMemory(&m_tInfo, sizeof(TILE_INFO));
	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	return S_OK;
}

void CBreakable::Release()
{
}

CBreakable * CBreakable::Create(D3DXVECTOR3 vPos,BYTE byDrawID)
{
	CBreakable* pInstance = new CBreakable;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}
	pInstance->m_tInfo.vPos = vPos;
	pInstance->m_tInfo.byDrawID = byDrawID;

	return pInstance;
}

void CBreakable::SetOption(BYTE byOption)
{
}
