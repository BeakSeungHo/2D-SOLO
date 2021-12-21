#include "stdafx.h"
#include "Item.h"


CItem::CItem()
{	
	ZeroMemory(&m_tITinfo, sizeof(ITEM_INFO));
}


CItem::~CItem()
{
}

int CItem::Update()
{
	CObjectMgr::GetInstance()->AddLayer(LAYER_EFFECT, this);
	return NO_EVENT;
}

void CItem::LateUpdate()
{
	D3DXMATRIX matScale, matTrans;

	D3DXMatrixScaling(&matScale,
		m_tITinfo.vSize.x,
		m_tITinfo.vSize.y,
		0.f); // 다이렉트 크기행렬 함수
	D3DXMatrixTranslation(&matTrans,
		m_tITinfo.vPos.x - CScrollMgr::GetScrollPos().x,
		m_tITinfo.vPos.y - CScrollMgr::GetScrollPos().y,
		0.f); // 다이렉트 이동행렬 함수

	m_tITinfo.matWorld = matScale * matTrans;

}

void CItem::Render()
{
	const TEX_INFO* pTexInfo = m_pTextureMgr->GetTexInfo(L"ITEM", L"ITEM", m_tITinfo.byDrawID);
	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	m_tPInfo.tRect = { LONG(m_tITinfo.vPos.x - fCenterX), LONG(m_tITinfo.vPos.y - fCenterY),LONG(m_tITinfo.vPos.x + fCenterX), LONG(m_tITinfo.vPos.y + fCenterY) };

	m_pDeviceMgr->GetSprite()->SetTransform(&m_tITinfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

HRESULT CItem::Initialize()
{
	m_tITinfo.vSize = {1.f,1.f,0.f};

	return S_OK;
}

void CItem::Release()
{
}

CItem * CItem::Create(D3DXVECTOR3 vPos, BYTE byDrawID, BYTE byOptionID)
{
	CItem* pInstance = new CItem;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}
	pInstance->m_tITinfo.vPos = vPos;
	pInstance->m_tITinfo.byDrawID = byDrawID;
	pInstance->m_tITinfo.byOption = byOptionID;
	return pInstance;
}
