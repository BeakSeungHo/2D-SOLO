#include "stdafx.h"
#include "Chest.h"

CChest::CChest()
{
}


CChest::~CChest()
{
}

int CChest::Update()
{
	return 0;
}

void CChest::LateUpdate()
{
}

void CChest::Render()
{
	D3DXMATRIX matScale, matTrans;

	const TEX_INFO* pTexInfo = nullptr;
	float fCenterX = 0.f, fCenterY = 0.f;

	TCHAR szIndexNum[MIN_STR] = L"";

	pTexInfo = m_pTextureMgr->GetTexInfo(L"Dungeon", L"Chest", m_tInfo.byDrawID);
	NULL_CHECK(pTexInfo);

	D3DXMatrixScaling(&matScale,
		m_tInfo.vSize.x,
		m_tInfo.vSize.y,
		m_tInfo.vSize.z);
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x - CScrollMgr::GetScrollPos().x,
		m_tInfo.vPos.y - CScrollMgr::GetScrollPos().y,
		m_tInfo.vPos.z);

	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	m_pDeviceMgr->GetSprite()->SetTransform(&(matScale * matTrans));
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

HRESULT CChest::Initialize()
{
	ZeroMemory(&m_tInfo, sizeof(TILE_INFO));
	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	return S_OK;
}

void CChest::Release()
{
}

CChest * CChest::Create(D3DXVECTOR3 vPos)
{
	CChest* pInstance = new CChest;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}
	pInstance->m_tInfo.vPos = vPos;

	return pInstance;
}
