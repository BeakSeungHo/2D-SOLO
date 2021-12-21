#include "stdafx.h"
#include "HealingPool.h"
#include "ToolView.h"

CHealingPool::CHealingPool()
{
}


CHealingPool::~CHealingPool()
{
}

int CHealingPool::Update()
{
	return 0;
}

void CHealingPool::LateUpdate()
{
}

void CHealingPool::Render()
{
	D3DXMATRIX matScale, matTrans;

	const TEX_INFO* pTexInfo = nullptr;
	float fCenterX = 0.f, fCenterY = 0.f;

	TCHAR szIndexNum[MIN_STR] = L"";

	pTexInfo = m_pTextureMgr->GetTexInfo(L"Dungeon", L"HealingPool", m_tInfo.byDrawID);
	NULL_CHECK(pTexInfo);

	D3DXMatrixScaling(&matScale,
		m_tInfo.vSize.x,
		m_tInfo.vSize.y,
		m_tInfo.vSize.z);
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x - m_pView->GetScrollPos(0),
		m_tInfo.vPos.y - m_pView->GetScrollPos(1),
		m_tInfo.vPos.z);

	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	m_pDeviceMgr->GetSprite()->SetTransform(&(matScale * matTrans));
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	
}

void CHealingPool::MiniRender()
{
}

HRESULT CHealingPool::Initialize()
{
	ZeroMemory(&m_tInfo, sizeof(TILE_INFO));
	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	return S_OK;
}

void CHealingPool::Release()
{
}

CHealingPool * CHealingPool::Create(D3DXVECTOR3 vPos, CToolView * pView)
{
	CHealingPool* pInstance = new CHealingPool;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}
	pInstance->m_tInfo.vPos = vPos;

	if (pView)
		pInstance->m_pView = pView;

	return pInstance;
}
