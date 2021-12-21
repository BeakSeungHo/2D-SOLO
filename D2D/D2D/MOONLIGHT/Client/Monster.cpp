#include "stdafx.h"
#include "Monster.h"
#include "Item.h"

CMonster::CMonster() :
	m_dwUP(0x00000001),			// 0000	0000 0000 0000 0000 0000 0000 0001
	m_dwDOWN(0x00000002),		// 0000 0000 0000 0000 0000 0000 0000 0010
	m_dwLEFT(0x00000004),		// 0000 0000 0000 0000 0000 0000 0000 0100
	m_dwRIGHT(0x00000008)		// 0000 0000 0000 0000 0000 0000 0000 1000
{
	ZeroMemory(&m_tPInfo, sizeof(INFO));
	ZeroMemory(&m_tFrame, sizeof(FRAME));
	ZeroMemory(&m_tOInfo, sizeof(OBINFO));
}


CMonster::~CMonster()
{
}

int CMonster::Update()
{
	m_tFrame.fCurFrame += m_tFrame.fMaxFrame * m_pTimeMgr->GetDelta();/* * 20.f*/

	if (m_tFrame.fMaxFrame <= m_tFrame.fCurFrame)
	{
		m_tFrame.fCurFrame = 0.f;
	}
	if (ATTACK == m_eCurState && 7 == (int)m_tFrame.fCurFrame)
	{
		if (m_dwCurWay & m_dwUP)
			m_tPInfo.tAttackRange = { LONG(m_tPInfo.vPos.x - 10), LONG(m_tPInfo.vPos.y - 25),
			LONG(m_tPInfo.vPos.x + 10), LONG(m_tPInfo.vPos.y) };
		else if (m_dwCurWay & m_dwDOWN)
			m_tPInfo.tAttackRange = { LONG(m_tPInfo.vPos.x - 10), LONG(m_tPInfo.vPos.y),
			LONG(m_tPInfo.vPos.x + 10), LONG(m_tPInfo.vPos.y + 25) };
		else if (m_dwCurWay & m_dwLEFT)
			m_tPInfo.tAttackRange = { LONG(m_tPInfo.vPos.x - 25), LONG(m_tPInfo.vPos.y - 10),
			LONG(m_tPInfo.vPos.x), LONG(m_tPInfo.vPos.y + 10) };
		else if (m_dwCurWay & m_dwRIGHT)
			m_tPInfo.tAttackRange = { LONG(m_tPInfo.vPos.x), LONG(m_tPInfo.vPos.y - 10),
			LONG(m_tPInfo.vPos.x + 25), LONG(m_tPInfo.vPos.y + 10) };
	}
	if (ATTACK == m_eCurState && 10 == (int)m_tFrame.fCurFrame)
	{
		m_tPInfo.tAttackRange = {0,0,0,0};
	}
	ChangeState();
	Move();
	Invincibillity();

	if (m_tOInfo.iHp <= 0)
	{
		m_pObjectMgr->AddObject(OBJECT_ITEM, CItem::Create(m_tPInfo.vPos + D3DXVECTOR3(10.f, 0.f, 0.f), 0, 1));
		m_pObjectMgr->AddObject(OBJECT_ITEM, CItem::Create(m_tPInfo.vPos + D3DXVECTOR3(0.f,-10.f,0.f), 1,0));
		m_pObjectMgr->AddObject(OBJECT_ITEM, CItem::Create(m_tPInfo.vPos + D3DXVECTOR3(0.f, 10.f, 0.f), 2, 0));
		return DEAD_OBJ;
	}
	CObjectMgr::GetInstance()->AddLayer(LAYER_OBJECT, this);

	return NO_EVENT;
}

void CMonster::LateUpdate()
{
	D3DXMATRIX matScale, matTrans;

	D3DXMatrixScaling(&matScale,
		m_tPInfo.vSize.x,
		m_tPInfo.vSize.y,
		0.f); // 다이렉트 크기행렬 함수
	D3DXMatrixTranslation(&matTrans,
		m_tPInfo.vPos.x - CScrollMgr::GetScrollPos().x,
		m_tPInfo.vPos.y - CScrollMgr::GetScrollPos().y,
		0.f); // 다이렉트 이동행렬 함수

	m_tPInfo.matWorld = matScale * matTrans;

	D3DXVec3TransformNormal(&m_tPInfo.vDir, &m_tPInfo.vLook, &m_tPInfo.matWorld);
	D3DXVec3Normalize(&m_tPInfo.vDir, &m_tPInfo.vDir);

	m_tPInfo.vPos += m_tPInfo.vDir * m_tPInfo.fSpeed * m_pTimeMgr->GetDelta();

}

void CMonster::Render()
{
	const TEX_INFO* pTexInfo = m_pTextureMgr->GetTexInfo(L"KNIGHT", m_wstrImageKey, (int)m_tFrame.fCurFrame);
	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;
	
	if (ATTACK == m_eCurState && 7 <= (int)m_tFrame.fCurFrame)
	{
		if (m_dwCurWay == m_dwDOWN)
		{
			fCenterY -= pTexInfo->tImgInfo.Height * 0.25f;
		}
		else if (m_dwCurWay == m_dwLEFT)
		{
			fCenterX += pTexInfo->tImgInfo.Width * 0.25f;
		}
		else if (m_dwCurWay == m_dwRIGHT)
		{
			fCenterX -= pTexInfo->tImgInfo.Width * 0.25f;
		}
	}
	

	m_tPInfo.tRect = { LONG(m_tPInfo.vPos.x - fCenterX), LONG(m_tPInfo.vPos.y - fCenterY),LONG(m_tPInfo.vPos.x + fCenterX), LONG(m_tPInfo.vPos.y + fCenterY) };

	m_pDeviceMgr->GetSprite()->SetTransform(&m_tPInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB((255 - m_tOInfo.Alpha), 255, 255, 255));

}

HRESULT CMonster::Initialize()
{
	m_tPInfo.fSpeed = 50.f;
	m_tPInfo.vSize = { 1.f, 1.f, 0.f };

	m_tFrame.fCurFrame = 0.f;
	m_tFrame.fMaxFrame = 7.f;

	m_tOInfo.iAttack = 10;
	m_tOInfo.iDef = 5;
	m_tOInfo.iMaxHp = 50;
	m_tOInfo.iHp = m_tOInfo.iMaxHp;
	m_tOInfo.fMaxInvinTime = 0.3f;

	m_pTarget = m_pObjectMgr->GetList(OBJECT_PLAYER).front();
	m_wstrImageKey = L"IDLE_DOWN";
	m_eCurState = IDLE;
	return S_OK;
}

void CMonster::Release()
{
}

void CMonster::Move()
{
	if(nullptr == m_pTarget)
		return;

	if (sqrtf(powf(m_pTarget->GetPInfo().vPos.x - m_tPInfo.vPos.x, 2) + powf(m_pTarget->GetPInfo().vPos.y - m_tPInfo.vPos.y, 2)) < 100 && 
		sqrtf(powf(m_pTarget->GetPInfo().vPos.x - m_tPInfo.vPos.x, 2) + powf(m_pTarget->GetPInfo().vPos.y - m_tPInfo.vPos.y, 2)) > 30)
	{
		
		D3DXVec3Normalize(&m_tPInfo.vLook,&(m_pTarget->GetPInfo().vPos - m_tPInfo.vPos));
		if (abs(m_tPInfo.vLook.y) > abs(m_tPInfo.vLook.x))
		{
			if (m_tPInfo.vLook.y < 0)
			{
				m_wstrImageKey = L"IDLE_UP";
				m_dwCurWay = 0;
				m_dwCurWay |= m_dwUP;
				m_eCurState = IDLE;
			}
			else if (m_tPInfo.vLook.y > 0)
			{
				m_wstrImageKey = L"IDLE_DOWN";
				m_dwCurWay = 0;
				m_dwCurWay |= m_dwDOWN;
				m_eCurState = IDLE;
			}
		}
		else
		{
			if (m_tPInfo.vLook.x < 0)
			{
				m_wstrImageKey = L"IDLE_LEFT";
				m_dwCurWay = 0;
				m_dwCurWay |= m_dwLEFT;
				m_eCurState = IDLE;

			}
			else if (m_tPInfo.vLook.x > 0)
			{
				m_wstrImageKey = L"IDLE_RIGHT";
				m_dwCurWay = 0;
				m_dwCurWay |= m_dwRIGHT;
				m_eCurState = IDLE;
			}
		}
		
	}
	else if(sqrtf(powf(m_pTarget->GetPInfo().vPos.x - m_tPInfo.vPos.x, 2) + powf(m_pTarget->GetPInfo().vPos.y - m_tPInfo.vPos.y, 2)) < 30)
	{
		D3DXVec3Normalize(&m_tPInfo.vLook, &(m_pTarget->GetPInfo().vPos - m_tPInfo.vPos));
		if (abs(m_tPInfo.vLook.y) > abs(m_tPInfo.vLook.x))
		{
			if (m_tPInfo.vLook.y < 0)
			{
				m_wstrImageKey = L"ATTACK_UP";
				m_dwCurWay = 0;
				m_dwCurWay |= m_dwUP;
				m_eCurState = ATTACK;
			}
			else if (m_tPInfo.vLook.y > 0)
			{
				m_wstrImageKey = L"ATTACK_DOWN";
				m_dwCurWay = 0;
				m_dwCurWay |= m_dwDOWN;
				m_eCurState = ATTACK;
			}
		}
		else
		{
			if (m_tPInfo.vLook.x < 0)
			{
				m_wstrImageKey = L"ATTACK_LEFT";
				m_dwCurWay = 0;
				m_dwCurWay |= m_dwLEFT;
				m_eCurState = ATTACK;
			}
			else if (m_tPInfo.vLook.x > 0)
			{
				m_wstrImageKey = L"ATTACK_RIGHT";
				m_dwCurWay = 0;
				m_dwCurWay |= m_dwRIGHT;
				m_eCurState = ATTACK;
			}
		}
		m_tPInfo.vLook = { 0.f,0.f,0.f };
	}
	else
	{
		m_eCurState = IDLE;
		m_tPInfo.vLook = { 0.f,0.f,0.f };
	}
}

void CMonster::ChangeState()
{
	if (m_ePreState != m_eCurState)
	{
		m_tPInfo.tAttackRange = { 0,0,0,0 };
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.fCurFrame = 0.f;
			m_tFrame.fMaxFrame = 7.f;
			break;
		case ATTACK:
			m_tFrame.fCurFrame = 0.f;
			m_tFrame.fMaxFrame = 12.f;
			break;
		}

		m_ePreState = m_eCurState;
	}
}

CMonster * CMonster::Create(D3DXVECTOR3 vPos)
{
	CMonster* pInstance = new CMonster;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}
	
	pInstance->m_tPInfo.vPos = vPos;

	return pInstance;
}
