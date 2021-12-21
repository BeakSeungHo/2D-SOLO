#include "stdafx.h"
#include "Detail.h"
#include "ToolView.h"

CDetail::CDetail() :
	m_fAngle(0.f)
{
}


CDetail::~CDetail()
{
}

int CDetail::Update()
{
	return 0;
}

void CDetail::LateUpdate()
{
}

void CDetail::Render()
{
	D3DXMATRIX matScale, matTrans;

	const TEX_INFO* pTexInfo = nullptr;
	
	TCHAR szIndexNum[MIN_STR] = L"";

	pTexInfo = m_pTextureMgr->GetTexInfo(L"Dungeon", L"Detail", m_tInfo.byDrawID);
	NULL_CHECK(pTexInfo);

	D3DXMatrixScaling(&matScale,
		m_tInfo.vSize.x,
		m_tInfo.vSize.y,
		m_tInfo.vSize.z);
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x - m_pView->GetScrollPos(0),
		m_tInfo.vPos.y - m_pView->GetScrollPos(1),
		m_tInfo.vPos.z);

	m_tInfo.fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	m_tInfo.fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	m_pDeviceMgr->GetSprite()->SetTransform(&(matScale * matTrans));
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(m_tInfo.fCenterX, m_tInfo.fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	
}

void CDetail::MiniRender()
{
}

HRESULT CDetail::Initialize()
{
	ZeroMemory(&m_tInfo,sizeof(TILE_INFO));
	m_tInfo.vSize = {1.f, 1.f, 0.f};
	m_fAngle = 0.f;

	return S_OK;
}

void CDetail::Release()
{
}

CDetail * CDetail::Create(D3DXVECTOR3 vPos, BYTE byDrawID, CToolView * pView)
{
	CDetail* pInstance = new CDetail;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}
	pInstance->m_tInfo.vPos = vPos;
	pInstance->m_tInfo.byDrawID = byDrawID;

	if (pView)
		pInstance->m_pView = pView;

	return pInstance;
}
