#include "stdafx.h"
#include "Rock.h"
#include "Terrain.h"

CRock::CRock() :
	m_fDeleteTime(0.f)
{
}


CRock::~CRock()
{
}

int CRock::Update()
{
	m_tFrame.fCurFrame += m_tFrame.fMaxFrame * m_pTimeMgr->GetDelta();/* * 20.f*/

	if (m_tFrame.fMaxFrame <= m_tFrame.fCurFrame)
	{
		m_tFrame.fCurFrame = m_tFrame.fMaxFrame;
		m_fDeleteTime += m_tFrame.fMaxFrame * m_pTimeMgr->GetDelta();
		m_tPInfo.tRect = { LONG(m_tPInfo.vPos.x - 16), LONG(m_tPInfo.vPos.y - 18),LONG(m_tPInfo.vPos.x + 16), LONG(m_tPInfo.vPos.y + 18) };
	}
	if (m_fDeleteTime > 50)
	{
		return DEAD_OBJ;
	}
	CObjectMgr::GetInstance()->AddLayer(LAYER_OBJECT, this);

	return NO_EVENT;
}

void CRock::LateUpdate()
{
	
}

void CRock::Render()
{
	const TEX_INFO* pTexInfo = m_pTextureMgr->GetTexInfo(L"Boss", L"ROCK_SHADOW", 0);
	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	D3DXMATRIX matScale, matTrans, matRotate;

	D3DXMatrixScaling(&matScale,
		(m_tFrame.fCurFrame + 1) / 9,
		(m_tFrame.fCurFrame + 1) / 9,
		0.f); // 다이렉트 크기행렬 함수
	D3DXMatrixTranslation(&matTrans,
		m_tPInfo.vPos.x - CScrollMgr::GetScrollPos().x,
		m_tPInfo.vPos.y - CScrollMgr::GetScrollPos().y,
		0.f); // 다이렉트 이동행렬 함수

	m_tPInfo.matWorld = matScale * matTrans;

	m_pDeviceMgr->GetSprite()->SetTransform(&m_tPInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	pTexInfo = m_pTextureMgr->GetTexInfo(L"Boss", L"ROCK", 1);
	NULL_CHECK(pTexInfo);

	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	D3DXMatrixScaling(&matScale,
		m_tPInfo.vSize.x,
		m_tPInfo.vSize.y,
		0.f); // 다이렉트 크기행렬 함수
	D3DXMatrixTranslation(&matTrans,
		m_tPInfo.vPos.x - CScrollMgr::GetScrollPos().x,
		m_tPInfo.vPos.y - CScrollMgr::GetScrollPos().y - 400 + m_tFrame.fCurFrame * 50,
		0.f); // 다이렉트 이동행렬 함수

	m_tPInfo.matWorld = matScale * matTrans;

	m_pDeviceMgr->GetSprite()->SetTransform(&m_tPInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	
}

HRESULT CRock::Initialize()
{
	m_tFrame.fCurFrame = 0.f;
	m_tFrame.fMaxFrame = 8.f;
	m_tPInfo.vSize = {1.f,1.f,0.f};
	return S_OK;
}

void CRock::Release()
{
	
}

CRock * CRock::Create(D3DXVECTOR3 vPos)
{
	CRock* pInstance = new CRock;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}
	pInstance->m_tPInfo.vPos = vPos;

	return pInstance;
}
