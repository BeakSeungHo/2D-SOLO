#include "stdafx.h"
#include "Terrain.h"
#include "Door.h"


CDoor::CDoor() :
	m_bClose(false),
	m_fAngle(0.f)
{
	ZeroMemory(&m_tFrame, sizeof(FRAME));
	ZeroMemory(&m_tInfo, sizeof(TILE_INFO));
}


CDoor::~CDoor()
{
}

int CDoor::Update()
{
	if (m_bClose && m_tFrame.fCurFrame <= 7)
	{
		m_tFrame.fCurFrame += m_tFrame.fMaxFrame * m_pTimeMgr->GetDelta();
	}
	else if(!m_bClose && m_tFrame.fCurFrame >= 7)
	{
		m_tFrame.fCurFrame += m_tFrame.fMaxFrame * m_pTimeMgr->GetDelta();
		if(m_tFrame.fCurFrame >= m_tFrame.fMaxFrame)
			m_tFrame.fCurFrame = 0;
	}
	CObjectMgr::GetInstance()->AddLayer(LAYER_BACK, this);
	return NO_EVENT;
}

void CDoor::LateUpdate()
{
}

void CDoor::Render()
{
	D3DXMATRIX matScale, matTrans, matRotate;

	const TEX_INFO* pTexInfo = nullptr;
	float fCenterX = 0.f, fCenterY = 0.f;

	pTexInfo = m_pTextureMgr->GetTexInfo(L"Dungeon", L"Door", (int)m_tFrame.fCurFrame);
	NULL_CHECK(pTexInfo);

	D3DXMatrixScaling(&matScale,
		m_tInfo.vSize.x,
		m_tInfo.vSize.y,
		m_tInfo.vSize.z);
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x - CScrollMgr::GetScrollPos().x,
		m_tInfo.vPos.y - CScrollMgr::GetScrollPos().y,
		m_tInfo.vPos.z);
	D3DXMatrixRotationZ(&matRotate,D3DXToRadian(m_fAngle));

	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	m_pDeviceMgr->GetSprite()->SetTransform(&(matScale * matRotate * matTrans ));
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

}

HRESULT CDoor::Initialize()
{
	m_tInfo.vSize = {1.f, 1.f, 0.f};

	m_tFrame.fCurFrame = 0.f;
	m_tFrame.fMaxFrame = 10.f;
	return S_OK;
}

void CDoor::Release()
{
}

void CDoor::SetBool(bool bClose)
{
	m_bClose = bClose;
}

void CDoor::SetAngle(float fAngle)
{
	m_fAngle = fAngle;
}

float CDoor::GetAngle()
{
	return m_fAngle;
}

CDoor* CDoor::Create(D3DXVECTOR3 vPos)
{
	CDoor* pInstance = new CDoor;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}
	pInstance->m_tInfo.vPos = vPos;

	return pInstance;
}
