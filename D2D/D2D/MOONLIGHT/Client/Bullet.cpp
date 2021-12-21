#include "stdafx.h"
#include "Bullet.h"


CBullet::CBullet() :
	m_bCollision(false),
	m_fAngle(0.f)
{
	ZeroMemory(&m_tFrame, sizeof(FRAME));
	ZeroMemory(&m_tPInfo, sizeof(INFO));
	ZeroMemory(&m_tOInfo,sizeof(OBINFO));
}


CBullet::~CBullet()
{
}

int CBullet::Update()
{
	m_tFrame.fCurFrame += m_tFrame.fMaxFrame * m_pTimeMgr->GetDelta();/* * 20.f*/

	if (m_tFrame.fMaxFrame <= m_tFrame.fCurFrame)
	{
		m_tFrame.fCurFrame = 0.f;
		if(m_bCollision)
			return DEAD_OBJ;
	}

	SetState();
	ChangeState();
	CObjectMgr::GetInstance()->AddLayer(LAYER_EFFECT, this);
	return NO_EVENT;
}

void CBullet::LateUpdate()
{

	D3DXMATRIX matScale, matTrans, matRotate;

	D3DXMatrixScaling(&matScale,
		m_tPInfo.vSize.x,
		m_tPInfo.vSize.y,
		0.f); // 다이렉트 크기행렬 함수
	D3DXMatrixTranslation(&matTrans,
		m_tPInfo.vPos.x - CScrollMgr::GetScrollPos().x,
		m_tPInfo.vPos.y - CScrollMgr::GetScrollPos().y,
		0.f); // 다이렉트 이동행렬 함수
	D3DXMatrixRotationZ(&matRotate,D3DXToRadian(m_fAngle));

	m_tPInfo.matWorld = matScale * matRotate * matTrans;

	D3DXVec3TransformNormal(&m_tPInfo.vDir, &m_tPInfo.vLook, &m_tPInfo.matWorld);
	D3DXVec3Normalize(&m_tPInfo.vDir, &m_tPInfo.vDir);

	m_tPInfo.vPos += m_tPInfo.vLook * m_tPInfo.fSpeed * m_pTimeMgr->GetDelta();
	m_tPInfo.tRect = { LONG(m_tPInfo.vPos.x - 5), LONG(m_tPInfo.vPos.y - 5), LONG(m_tPInfo.vPos.x + 5), LONG(m_tPInfo.vPos.y + 5) };
	m_tPInfo.tAttackRange = m_tPInfo.tRect;
}

void CBullet::Render()
{
	const TEX_INFO* pTexInfo = m_pTextureMgr->GetTexInfo(L"TURRET", m_wstrImageKey, (int)m_tFrame.fCurFrame);
	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	m_pDeviceMgr->GetSprite()->SetTransform(&m_tPInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

HRESULT CBullet::Initialize()
{
	m_tPInfo.fSpeed = 100.f;
	m_tPInfo.vSize = { 1.f, 1.f, 0.f };

	m_tFrame.fCurFrame = 0.f;
	m_tFrame.fMaxFrame = 5.f;

	m_tOInfo.iAttack = 5;
	m_wstrImageKey = L"BULLET";
	return S_OK;
}

void CBullet::Release()
{
}

CBullet * CBullet::Create(D3DXVECTOR3 vPos)
{
	CBullet* pInstance = new CBullet;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}
	pInstance->m_tPInfo.vPos = vPos;

	return pInstance;
}

void CBullet::ChangeState()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ATTACK:
			m_tFrame.fCurFrame = 0.f;
			m_tFrame.fMaxFrame = 5.f;
			break;
		case BEATTACK:
			m_tFrame.fCurFrame = 0.f;
			m_tFrame.fMaxFrame = 4.f;
			break;
		}

		m_ePreState = m_eCurState;
	}
}

void CBullet::SetAngle(float fAngle)
{
	m_fAngle = fAngle;
}

void CBullet::SetColli(bool bColli)
{
	m_bCollision = bColli;
}

void CBullet::SetState()
{
	if (m_bCollision)
	{
		m_wstrImageKey = L"BULLET_COLLSION";
		m_eCurState = BEATTACK;
		m_tPInfo.vLook = { 0.f,0.f,0.f };
	}
	else
	{
		m_wstrImageKey = L"BULLET";
		m_eCurState = ATTACK;
		if (0 == (m_fAngle / 90))
		{
			m_tPInfo.vLook = { 0.f,-1.f,0.f };
		}
		else if (1 == (m_fAngle / 90))
		{
			m_tPInfo.vLook = { 1.f,0.f,0.f };
		}
		else if (2 == (m_fAngle / 90))
		{
			m_tPInfo.vLook = { 0.f,1.f,0.f };
		}
		else if (3 == (m_fAngle / 90))
		{
			m_tPInfo.vLook = { -1.f,0.f,0.f };
		}
	}
	

}

float CBullet::GetAngle()
{
	return m_fAngle;
}
