#include "stdafx.h"
#include "Back.h"

CBack::CBack()
{
}


CBack::~CBack()
{
}

int CBack::Update()
{
	return 0;
}

void CBack::LateUpdate()
{
}

void CBack::Render()
{
	D3DXMATRIX matScale, matTrans;

	const TEX_INFO* pTexInfo = nullptr;
	float fCenterX = 0.f, fCenterY = 0.f;

	TCHAR szIndexNum[MIN_STR] = L"";

	pTexInfo = m_pTextureMgr->GetTexInfo(L"BackGround", L"Back", m_tInfo.byDrawID);
	NULL_CHECK(pTexInfo);

	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	D3DXMatrixScaling(&matScale,
		m_tInfo.vSize.x,
		m_tInfo.vSize.y,
		m_tInfo.vSize.z);
	D3DXMatrixTranslation(&matTrans,
		fCenterX - CScrollMgr::GetScrollPos().x,
		fCenterY - CScrollMgr::GetScrollPos().y,
		m_tInfo.vPos.z);

	m_pDeviceMgr->GetSprite()->SetTransform(&(matScale * matTrans));
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

HRESULT CBack::Initialize()
{
	ZeroMemory(&m_tInfo, sizeof(TILE_INFO));
	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	return S_OK;
}

void CBack::Release()
{
}

CBack * CBack::Create(D3DXVECTOR3 vPos)
{
	CBack* pInstance = new CBack;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}
	pInstance->m_tInfo.vPos = vPos;

	return pInstance;
}
