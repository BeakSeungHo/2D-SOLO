#include "stdafx.h"
#include "Monster2.h"
#include "Bullet.h"
#include "Item.h"

CMonster2::CMonster2() :
	m_dwUP(0x00000001),			// 0000	0000 0000 0000 0000 0000 0000 0001
	m_dwDOWN(0x00000002),		// 0000 0000 0000 0000 0000 0000 0000 0010
	m_dwLEFT(0x00000004),		// 0000 0000 0000 0000 0000 0000 0000 0100
	m_dwRIGHT(0x00000008)		// 0000 0000 0000 0000 0000 0000 0000 1000
{
	ZeroMemory(&m_tPInfo, sizeof(INFO));
	ZeroMemory(&m_tFrame, sizeof(FRAME));
	ZeroMemory(&m_tOInfo, sizeof(OBINFO));
}


CMonster2::~CMonster2()
{
}

int CMonster2::Update()
{
	m_tFrame.fCurFrame += m_tFrame.fMaxFrame * m_pTimeMgr->GetDelta();/* * 20.f*/

	if (m_tFrame.fMaxFrame <= m_tFrame.fCurFrame)
	{
		m_tFrame.fCurFrame = 0.f;
	}
	if (ATTACK == m_eCurState && 7 == (int)m_tFrame.fCurFrame)
	{
		CBullet* temp = CBullet::Create(m_tPInfo.vPos);
		if (m_dwCurWay == m_dwUP)
			temp->SetAngle(0.f);
		else if (m_dwCurWay == m_dwRIGHT)
			temp->SetAngle(90.f);
		else if (m_dwCurWay == m_dwDOWN)
			temp->SetAngle(180.f);
		else if (m_dwCurWay == m_dwLEFT)
			temp->SetAngle(270.f);
		m_pObjectMgr->AddObject(OBJECT_BULLET, temp);
		++m_tFrame.fCurFrame;
	}

	SetState();
	ChangeState();
	Invincibillity();

	if (m_tOInfo.iHp <= 0)
	{
		m_pObjectMgr->AddObject(OBJECT_ITEM, CItem::Create(m_tPInfo.vPos, 2, 0));
		m_pObjectMgr->AddObject(OBJECT_ITEM, CItem::Create(m_tPInfo.vPos, 3, 0));
		return DEAD_OBJ;
	}
	CObjectMgr::GetInstance()->AddLayer(LAYER_OBJECT, this);

	return NO_EVENT;
}

void CMonster2::LateUpdate()
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

void CMonster2::Render()
{
	const TEX_INFO* pTexInfo = m_pTextureMgr->GetTexInfo(L"TURRET", m_wstrImageKey, (int)m_tFrame.fCurFrame);
	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	m_tPInfo.tRect = { LONG(m_tPInfo.vPos.x - fCenterX), LONG(m_tPInfo.vPos.y - fCenterY),LONG(m_tPInfo.vPos.x + fCenterX), LONG(m_tPInfo.vPos.y + fCenterY) };

	m_pDeviceMgr->GetSprite()->SetTransform(&m_tPInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB((255 - m_tOInfo.Alpha), 255, 255, 255));
}

HRESULT CMonster2::Initialize()
{

	m_tPInfo.fSpeed = 50.f;
	m_tPInfo.vSize = { 1.f, 1.f, 0.f };

	m_tFrame.fCurFrame = 0.f;
	m_tFrame.fMaxFrame = 5.f;

	m_tOInfo.iAttack = 10;
	m_tOInfo.iDef = 5;
	m_tOInfo.iMaxHp = 50;
	m_tOInfo.iHp = m_tOInfo.iMaxHp;
	m_tOInfo.fMaxInvinTime = 0.3f;

	m_wstrImageKey = L"WALK_UP";

	m_pTarget = m_pObjectMgr->GetList(OBJECT_PLAYER).front();

	return S_OK;
}

void CMonster2::Release()
{
}

CMonster2 * CMonster2::Create(D3DXVECTOR3 vPos)
{
	CMonster2* pInstance = new CMonster2;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	pInstance->m_tPInfo.vPos = vPos;

	return pInstance;
}

void CMonster2::SetState()
{
	if (sqrtf(powf(m_pTarget->GetPInfo().vPos.x - m_tPInfo.vPos.x, 2) + powf(m_pTarget->GetPInfo().vPos.y - m_tPInfo.vPos.y, 2)) < 150)
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
		m_tPInfo.vLook = {0.f,0.f,0.f};
	}
	else if (sqrtf(powf(m_pTarget->GetPInfo().vPos.x - m_tPInfo.vPos.x, 2) + powf(m_pTarget->GetPInfo().vPos.y - m_tPInfo.vPos.y, 2)) < 200)
	{
		D3DXVec3Normalize(&m_tPInfo.vLook, &(m_pTarget->GetPInfo().vPos - m_tPInfo.vPos));
		if (abs(m_tPInfo.vLook.y) > abs(m_tPInfo.vLook.x))
		{
			if (m_tPInfo.vLook.y < 0)
			{
				m_wstrImageKey = L"WALK_UP";
				m_dwCurWay = 0;
				m_dwCurWay |= m_dwUP;
				m_eCurState = WALK;
			}
			else if (m_tPInfo.vLook.y > 0)
			{
				m_wstrImageKey = L"WALK_DOWN";
				m_dwCurWay = 0;
				m_dwCurWay |= m_dwDOWN;
				m_eCurState = WALK;
			}
		}
		else
		{
			if (m_tPInfo.vLook.x < 0)
			{
				m_wstrImageKey = L"WALK_LEFT";
				m_dwCurWay = 0;
				m_dwCurWay |= m_dwLEFT;
				m_eCurState = WALK;

			}
			else if (m_tPInfo.vLook.x > 0)
			{
				m_wstrImageKey = L"WALK_RIGHT";
				m_dwCurWay = 0;
				m_dwCurWay |= m_dwRIGHT;
				m_eCurState = WALK;
			}
		}
	}
}

void CMonster2::ChangeState()
{	
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case WALK:
			m_tFrame.fCurFrame = 0.f;
			m_tFrame.fMaxFrame = 5.f;
			break;
		case ATTACK:
			m_tFrame.fCurFrame = 0.f;
			m_tFrame.fMaxFrame = 10.f;
			break;
		}

		m_ePreState = m_eCurState;
	}
}
