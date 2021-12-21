#include "stdafx.h"
#include "Punch.h"
#include "Boss.h"

CPunch::CPunch() :
	m_fWaitTime(0.f),
	m_iCount(0)
{
	ZeroMemory(&m_tPInfo, sizeof(INFO));
}


CPunch::~CPunch()
{
}

int CPunch::Update()
{
	m_tFrame.fCurFrame += m_tFrame.fMaxFrame * m_pTimeMgr->GetDelta();/* * 20.f*/

	if (m_wstrImageKey == L"PUNCH_DOWN" && 1 == (int)m_tFrame.fCurFrame)
	{
		CSoundMgr::GetInstance()->PlaySound(L"BOSS_A_ROKETDOWN.wav", CSoundMgr::MONSTER);
		++m_tFrame.fCurFrame;
	}
	if (m_wstrImageKey == L"PUNCH_DOWN" && 2 == (int)m_tFrame.fCurFrame)
	{
		CSoundMgr::GetInstance()->PlaySound(L"BOSS_A_ROKET.wav", CSoundMgr::MONSTER);
		++m_tFrame.fCurFrame;
	}

	if (m_tFrame.fMaxFrame <= m_tFrame.fCurFrame)
	{
		if (L"PUNCH_DOWN" == m_wstrImageKey)
		{
			m_fWaitTime += m_tFrame.fMaxFrame * m_pTimeMgr->GetDelta();
			m_tFrame.fCurFrame = m_tFrame.fMaxFrame;
			m_tPInfo.tAttackRange = { LONG(m_tPInfo.vPos.x - 32), LONG(m_tPInfo.vPos.y),
									LONG(m_tPInfo.vPos.x + 32), LONG(m_tPInfo.vPos.y + 64) };
			if (m_fWaitTime >= 3)
			{	
				m_tFrame.fCurFrame = 0.f;
				m_wstrImageKey = L"PUNCH_UP";
				m_fWaitTime = 0;
				m_tPInfo.tAttackRange = {0,0,0};
			}
		}
		else if (L"PUNCH_UP" == m_wstrImageKey)
		{
			m_fWaitTime += m_tFrame.fMaxFrame * m_pTimeMgr->GetDelta();
			m_tFrame.fCurFrame = m_tFrame.fMaxFrame;
			if (m_fWaitTime >= 3)
			{
				m_tFrame.fCurFrame = 0.f;
				m_wstrImageKey = L"PUNCH_DOWN";
				++m_iCount;
				m_fWaitTime = 0;
			}
		}
		
	}
	if (m_iCount >= 2)
	{
		dynamic_cast<CBoss*>(m_pObjectMgr->GetList(OBJECT_MONSTER).front())->SetState(RECOVER,L"RECOVER");
		return DEAD_OBJ;
	}
		
	CObjectMgr::GetInstance()->AddLayer(LAYER_OBJECT, this);
	return NO_EVENT;
}

void CPunch::LateUpdate()
{
	if (L"PUNCH_DOWN" == m_wstrImageKey)
		m_tPInfo.vDir = { 0.f,m_tFrame.fCurFrame,0.f };
	else if (L"PUNCH_UP" == m_wstrImageKey)
		m_tPInfo.vDir = { 0.f,(m_tFrame.fMaxFrame - m_tFrame.fCurFrame),0.f };

	if (L"PUNCH_DOWN" == m_wstrImageKey && m_tFrame.fCurFrame < 4)
	{
		m_tPInfo.vPos = m_pTarget->GetPInfo().vPos;
	}
}

void CPunch::Render()
{
	const TEX_INFO* pTexInfo = m_pTextureMgr->GetTexInfo(L"Boss", L"PUNCH_SHADOW", 0);
	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	m_tPInfo.tRect = { LONG(m_tPInfo.vPos.x - fCenterX), LONG(m_tPInfo.vPos.y - fCenterY),LONG(m_tPInfo.vPos.x + fCenterX), LONG(m_tPInfo.vPos.y + fCenterY) };
	D3DXMATRIX matScale, matTrans;

	if (L"PUNCH_DOWN" == m_wstrImageKey)
	{
		D3DXMatrixScaling(&matScale,
			(m_tFrame.fCurFrame + 1) / 9,
			(m_tFrame.fCurFrame + 1) / 9,
			0.f); // 다이렉트 크기행렬 함수
		D3DXMatrixTranslation(&matTrans,
			m_tPInfo.vPos.x - CScrollMgr::GetScrollPos().x,
			m_tPInfo.vPos.y - CScrollMgr::GetScrollPos().y,
			0.f); // 다이렉트 이동행렬 함수
	}
	else if (L"PUNCH_UP" == m_wstrImageKey)
	{
		D3DXMatrixScaling(&matScale,
			(m_tFrame.fMaxFrame - m_tFrame.fCurFrame + 1) / 9,
			(m_tFrame.fMaxFrame - m_tFrame.fCurFrame + 1) / 9,
			0.f); // 다이렉트 크기행렬 함수
		D3DXMatrixTranslation(&matTrans,
			m_tPInfo.vPos.x - CScrollMgr::GetScrollPos().x,
			m_tPInfo.vPos.y - CScrollMgr::GetScrollPos().y,
			0.f); // 다이렉트 이동행렬 함수
	}
	

	m_tPInfo.matWorld = matScale * matTrans;

	m_pDeviceMgr->GetSprite()->SetTransform(&m_tPInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	pTexInfo = m_pTextureMgr->GetTexInfo(L"Boss", m_wstrImageKey, (int)m_tFrame.fCurFrame);
	NULL_CHECK(pTexInfo);

	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	matScale, matTrans;

	D3DXMatrixScaling(&matScale,
		m_tPInfo.vSize.x,
		m_tPInfo.vSize.y,
		0.f); // 다이렉트 크기행렬 함수
	D3DXMatrixTranslation(&matTrans,
		m_tPInfo.vPos.x - CScrollMgr::GetScrollPos().x,
		m_tPInfo.vPos.y - 320 + (m_tPInfo.vDir.y * 40) - CScrollMgr::GetScrollPos().y,
		0.f); // 다이렉트 이동행렬 함수

	m_tPInfo.matWorld = matScale * matTrans;

	m_tPInfo.tRect = { LONG(m_tPInfo.vPos.x - fCenterX), LONG(m_tPInfo.vPos.y - fCenterY),LONG(m_tPInfo.vPos.x + fCenterX), LONG(m_tPInfo.vPos.y + fCenterY) };

	m_pDeviceMgr->GetSprite()->SetTransform(&m_tPInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
	nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	
}

HRESULT CPunch::Initialize()
{
	m_pTarget = m_pObjectMgr->GetList(OBJECT_PLAYER).front();
	m_tPInfo.vSize = {1.f,1.f,0.f};
	m_wstrImageKey = L"PUNCH_DOWN";
	m_iCount = 0;
	m_tOInfo.iAttack = 10;
	m_tFrame.fMaxFrame = 8.f;
	m_tPInfo.vPos = D3DXVECTOR3(m_pTarget->GetPInfo().vPos.x, m_pTarget->GetPInfo().vPos.y - 320, 0.f);

	return S_OK;
}

void CPunch::Release()
{
}

CPunch * CPunch::Create()
{
	CPunch* pInstance = new CPunch;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
