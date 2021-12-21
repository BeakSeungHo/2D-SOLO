#include "stdafx.h"
#include "Boss.h"
#include "Punch.h"
#include "Rock.h"
#include "UI.h"
CBoss::CBoss()
{
	ZeroMemory(&m_tPInfo, sizeof(INFO));
	ZeroMemory(&m_tOInfo, sizeof(OBINFO));
}


CBoss::~CBoss()
{
}

int CBoss::Update()
{
	m_tFrame.fCurFrame += m_tFrame.fMaxFrame * m_pTimeMgr->GetDelta() * 0.25f;/* * 20.f*/

	if (m_eCurState == WAKEUP && 1 == (int)m_tFrame.fCurFrame)
	{
		CSoundMgr::GetInstance()->PlaySound(L"BOSS_A_WAKEUP.wav", CSoundMgr::MONSTER);
		dynamic_cast<CUI*>(m_pObjectMgr->GetList(OBJECT_UI).front())->SetBoss(true);
		++m_tFrame.fCurFrame;
	}
	else if (m_eCurState == DEATH && 1 == (int)m_tFrame.fCurFrame)
	{
		CSoundMgr::GetInstance()->PlaySound(L"BOSS_A_DEAD.wav", CSoundMgr::MONSTER);
		dynamic_cast<CUI*>(m_pObjectMgr->GetList(OBJECT_UI).front())->SetBoss(false);
		++m_tFrame.fCurFrame;
	}
	else if(m_eCurState == SPAWN && 15 == (int)m_tFrame.fCurFrame)
	{
		CSoundMgr::GetInstance()->PlaySound(L"BOSS_A_SPAWN.wav", CSoundMgr::MONSTER);
		++m_tFrame.fCurFrame;
	}
	if (m_tFrame.fMaxFrame <= m_tFrame.fCurFrame)
	{
		m_tFrame.fCurFrame = 0.f;
		if (m_eCurState == WAKEUP)
		{
			m_eCurState = BOSS_IDLE;
			m_wstrImageKey = L"IDLE";
		}
		if (m_eCurState == BOSS_IDLE && m_wstrImageKey == L"IDLE")
		{
			if (m_iCount == 0)
			{
				PunchPattern();
				m_iCount = 1;
			}
			else if (m_iCount == 1)
			{
				m_iCount = 0;
				RockPattern();
			}
				
		}		
		else if (m_eCurState == LAUNCH)
		{
			m_eCurState = BOSS_IDLE;
			m_wstrImageKey = L"NOARM_IDLE";
			m_pObjectMgr->AddObject(OBJECT_MONSTER, CPunch::Create());
		}
		else if (m_eCurState == RECOVER)
		{
			m_eCurState = BOSS_IDLE;
			m_wstrImageKey = L"IDLE";
		}
		else if (m_eCurState == SPAWN)
		{
			m_eCurState = BOSS_IDLE;
			m_wstrImageKey = L"IDLE";

			m_pObjectMgr->AddObject(OBJECT_ROCK, CRock::Create(D3DXVECTOR3(m_tPInfo.vPos.x, m_tPInfo.vPos.y + 190, 0.f)));
			m_pObjectMgr->AddObject(OBJECT_ROCK, CRock::Create(D3DXVECTOR3(m_tPInfo.vPos.x + 40 , m_tPInfo.vPos.y + 180, 0.f)));
			m_pObjectMgr->AddObject(OBJECT_ROCK, CRock::Create(D3DXVECTOR3(m_tPInfo.vPos.x - 40 , m_tPInfo.vPos.y + 180, 0.f)));
			m_pObjectMgr->AddObject(OBJECT_ROCK, CRock::Create(D3DXVECTOR3(m_tPInfo.vPos.x + 80, m_tPInfo.vPos.y + 170, 0.f)));
			m_pObjectMgr->AddObject(OBJECT_ROCK, CRock::Create(D3DXVECTOR3(m_tPInfo.vPos.x - 80, m_tPInfo.vPos.y + 170, 0.f)));
			m_pObjectMgr->AddObject(OBJECT_ROCK, CRock::Create(D3DXVECTOR3(m_tPInfo.vPos.x + 120, m_tPInfo.vPos.y + 150, 0.f)));
			m_pObjectMgr->AddObject(OBJECT_ROCK, CRock::Create(D3DXVECTOR3(m_tPInfo.vPos.x - 120, m_tPInfo.vPos.y + 150, 0.f)));
			m_pObjectMgr->AddObject(OBJECT_ROCK, CRock::Create(D3DXVECTOR3(m_tPInfo.vPos.x + 160, m_tPInfo.vPos.y + 130, 0.f)));
			m_pObjectMgr->AddObject(OBJECT_ROCK, CRock::Create(D3DXVECTOR3(m_tPInfo.vPos.x - 160, m_tPInfo.vPos.y + 130, 0.f)));
			m_pObjectMgr->AddObject(OBJECT_ROCK, CRock::Create(D3DXVECTOR3(m_tPInfo.vPos.x + 180, m_tPInfo.vPos.y + 90, 0.f)));
			m_pObjectMgr->AddObject(OBJECT_ROCK, CRock::Create(D3DXVECTOR3(m_tPInfo.vPos.x - 180, m_tPInfo.vPos.y + 90, 0.f)));
			m_pObjectMgr->AddObject(OBJECT_ROCK, CRock::Create(D3DXVECTOR3(m_tPInfo.vPos.x + 200, m_tPInfo.vPos.y + 50, 0.f)));
			m_pObjectMgr->AddObject(OBJECT_ROCK, CRock::Create(D3DXVECTOR3(m_tPInfo.vPos.x - 200, m_tPInfo.vPos.y + 50, 0.f)));
			m_pObjectMgr->AddObject(OBJECT_ROCK, CRock::Create(D3DXVECTOR3(m_tPInfo.vPos.x + 220, m_tPInfo.vPos.y, 0.f)));
			m_pObjectMgr->AddObject(OBJECT_ROCK, CRock::Create(D3DXVECTOR3(m_tPInfo.vPos.x - 220, m_tPInfo.vPos.y, 0.f)));

			m_pObjectMgr->AddObject(OBJECT_ROCK, CRock::Create(D3DXVECTOR3(m_tPInfo.vPos.x, m_tPInfo.vPos.y + 290, 0.f)));
			m_pObjectMgr->AddObject(OBJECT_ROCK, CRock::Create(D3DXVECTOR3(m_tPInfo.vPos.x + 50, m_tPInfo.vPos.y + 290, 0.f)));
			m_pObjectMgr->AddObject(OBJECT_ROCK, CRock::Create(D3DXVECTOR3(m_tPInfo.vPos.x - 50, m_tPInfo.vPos.y + 290, 0.f)));
			m_pObjectMgr->AddObject(OBJECT_ROCK, CRock::Create(D3DXVECTOR3(m_tPInfo.vPos.x + 100, m_tPInfo.vPos.y + 280, 0.f)));
			m_pObjectMgr->AddObject(OBJECT_ROCK, CRock::Create(D3DXVECTOR3(m_tPInfo.vPos.x - 100, m_tPInfo.vPos.y + 280, 0.f)));
			m_pObjectMgr->AddObject(OBJECT_ROCK, CRock::Create(D3DXVECTOR3(m_tPInfo.vPos.x + 140, m_tPInfo.vPos.y + 280, 0.f)));
			m_pObjectMgr->AddObject(OBJECT_ROCK, CRock::Create(D3DXVECTOR3(m_tPInfo.vPos.x - 140, m_tPInfo.vPos.y + 280, 0.f)));
			m_pObjectMgr->AddObject(OBJECT_ROCK, CRock::Create(D3DXVECTOR3(m_tPInfo.vPos.x + 180, m_tPInfo.vPos.y + 270, 0.f)));
			m_pObjectMgr->AddObject(OBJECT_ROCK, CRock::Create(D3DXVECTOR3(m_tPInfo.vPos.x - 180, m_tPInfo.vPos.y + 270, 0.f)));
			m_pObjectMgr->AddObject(OBJECT_ROCK, CRock::Create(D3DXVECTOR3(m_tPInfo.vPos.x + 220, m_tPInfo.vPos.y + 250, 0.f)));
			m_pObjectMgr->AddObject(OBJECT_ROCK, CRock::Create(D3DXVECTOR3(m_tPInfo.vPos.x - 220, m_tPInfo.vPos.y + 250, 0.f)));
			m_pObjectMgr->AddObject(OBJECT_ROCK, CRock::Create(D3DXVECTOR3(m_tPInfo.vPos.x + 260, m_tPInfo.vPos.y + 230, 0.f)));
			m_pObjectMgr->AddObject(OBJECT_ROCK, CRock::Create(D3DXVECTOR3(m_tPInfo.vPos.x - 260, m_tPInfo.vPos.y + 230, 0.f)));
			m_pObjectMgr->AddObject(OBJECT_ROCK, CRock::Create(D3DXVECTOR3(m_tPInfo.vPos.x + 280, m_tPInfo.vPos.y + 190, 0.f)));
			m_pObjectMgr->AddObject(OBJECT_ROCK, CRock::Create(D3DXVECTOR3(m_tPInfo.vPos.x - 280, m_tPInfo.vPos.y + 190, 0.f)));
			m_pObjectMgr->AddObject(OBJECT_ROCK, CRock::Create(D3DXVECTOR3(m_tPInfo.vPos.x + 300, m_tPInfo.vPos.y + 150, 0.f)));
			m_pObjectMgr->AddObject(OBJECT_ROCK, CRock::Create(D3DXVECTOR3(m_tPInfo.vPos.x - 300, m_tPInfo.vPos.y + 150, 0.f)));
			m_pObjectMgr->AddObject(OBJECT_ROCK, CRock::Create(D3DXVECTOR3(m_tPInfo.vPos.x + 320, m_tPInfo.vPos.y + 100, 0.f)));
			m_pObjectMgr->AddObject(OBJECT_ROCK, CRock::Create(D3DXVECTOR3(m_tPInfo.vPos.x - 320, m_tPInfo.vPos.y + 100, 0.f)));
			
		}

		else if (m_eCurState == DEATH)
			m_tFrame.fCurFrame = m_tFrame.fMaxFrame;
	}
	ChangeState();
	Invincibillity();

	if (m_tOInfo.iHp <= 0)
	{
		m_eCurState = DEATH;
		m_wstrImageKey = L"DEATH";
	}
	CObjectMgr::GetInstance()->AddLayer(LAYER_OBJECT, this);

	return NO_EVENT;
}

void CBoss::LateUpdate()
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

}

void CBoss::Render()
{
	const TEX_INFO* pTexInfo = m_pTextureMgr->GetTexInfo(L"Boss", m_wstrImageKey, (int)m_tFrame.fCurFrame);
	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	m_tPInfo.tRect = { LONG(m_tPInfo.vPos.x - fCenterX), LONG(m_tPInfo.vPos.y - fCenterY),LONG(m_tPInfo.vPos.x + fCenterX), LONG(m_tPInfo.vPos.y + fCenterY) };

	m_pDeviceMgr->GetSprite()->SetTransform(&m_tPInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255 - m_tOInfo.Alpha, 255, 255, 255));
}

HRESULT CBoss::Initialize()
{
	m_tPInfo.vSize = {1.f,1.f,0.f};
	m_tPInfo.vPos = {WINCX * 0.9f,WINCY * 0.75f,0.f};
	m_tFrame.fMaxFrame = 31.f;

	m_tOInfo.iHp = 100;
	m_tOInfo.iMaxHp = 100;
	m_tOInfo.fMaxInvinTime = 0.5f;

	LPDIRECT3DDEVICE9 pGraphicDev = m_pDeviceMgr->GetDevice();
	NULL_CHECK_MSG_RETURN(pGraphicDev, L"pGraphicDev is null", E_FAIL);

	HRESULT hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../TEXTRUE/BOSS/BOSS_A/IDLE/BOSS_A_IDLE_%d.png",
		L"Boss",
		L"IDLE",
		16);
	FAILED_CHECK_MSG_RETURN(hr, L"Boss IDLE LoadTexture Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../TEXTRUE/BOSS/BOSS_A/LAUNCH/BOSS_A_LAUNCH_%d.png",
		L"Boss",
		L"LAUNCH",
		39);
	FAILED_CHECK_MSG_RETURN(hr, L"Boss LAUNCH LoadTexture Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../TEXTRUE/BOSS/BOSS_A/RECOVER/BOSS_A_RECOVER_%d.png",
		L"Boss",
		L"RECOVER",
		24);
	FAILED_CHECK_MSG_RETURN(hr, L"Boss RECOVER LoadTexture Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../TEXTRUE/BOSS/BOSS_A/WAKEUP/BOSS_A_WAKEUP_%d.png",
		L"Boss",
		L"WAKEUP",
		32);
	FAILED_CHECK_MSG_RETURN(hr, L"Boss WAKEUP LoadTexture Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../TEXTRUE/BOSS/BOSS_A/DEATH/BOSS_A_DEATH_%d.png",
		L"Boss",
		L"DEATH",
		82);
	FAILED_CHECK_MSG_RETURN(hr, L"Boss DEATH LoadTexture Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../TEXTRUE/BOSS/BOSS_A/NOARM_IDLE/BOOS_A_NOARMIDLE_%d.png",
		L"Boss",
		L"NOARM_IDLE",
		16);
	FAILED_CHECK_MSG_RETURN(hr, L"Boss NOARM_IDLE LoadTexture Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../TEXTRUE/BOSS/BOSS_A/SPAWN/BOSS_A_SPAWN_%d.png",
		L"Boss",
		L"SPAWN",
		43);
	FAILED_CHECK_MSG_RETURN(hr, L"Boss SPAWN LoadTexture Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../TEXTRUE/BOSS/BOSS_A/PUNCH_DOWN/PUNCH_DOWN_%d.png",
		L"Boss",
		L"PUNCH_DOWN",
		9);
	FAILED_CHECK_MSG_RETURN(hr, L"Boss PUNCH_DOWN LoadTexture Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../TEXTRUE/BOSS/BOSS_A/PUNCH_UP/BOSS_A_PUNCHUP_%d.png",
		L"Boss",
		L"PUNCH_UP",
		9);
	FAILED_CHECK_MSG_RETURN(hr, L"Boss PUNCH_UP LoadTexture Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../TEXTRUE/BOSS/BOSS_A/PUNCH_SHADOW/BOSS_A_PUNCH_SHADOW_%d.png",
		L"Boss",
		L"PUNCH_SHADOW",
		1);
	FAILED_CHECK_MSG_RETURN(hr, L"Boss PUNCH_UP LoadTexture Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../TEXTRUE/BOSS/BOSS_A/ROCK/BOSS_A_ROCK_%d.png",
		L"Boss",
		L"ROCK",
		6);
	FAILED_CHECK_MSG_RETURN(hr, L"Boss ROCK LoadTexture Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../TEXTRUE/BOSS/BOSS_A/ROCK_SHADOW/BOSS_A_ROCK_SHADOW_%d.png",
		L"Boss",
		L"ROCK_SHADOW",
		1);
	FAILED_CHECK_MSG_RETURN(hr, L"Boss ROCK_SHADOW LoadTexture Failed", E_FAIL);

	return S_OK;
}

void CBoss::Release()
{
}

CBoss * CBoss::Create()
{
	CBoss* pInstance = new CBoss;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CBoss::ChangeState()
{
	
	if (m_ePreState != m_eCurState)
	{
		m_tPInfo.tAttackRange = { 0,0,0,0 };
		switch (m_eCurState)
		{
		case BOSS_IDLE:
			m_tFrame.fCurFrame = 0.f;
			m_tFrame.fMaxFrame = 15.f;
			break;
		case WAKEUP:
			m_tFrame.fCurFrame = 0.f;
			m_tFrame.fMaxFrame = 31.f;
			break;
		case SPAWN:
			m_tFrame.fCurFrame = 0.f;
			m_tFrame.fMaxFrame = 42.f;
			break;
		case LAUNCH:
			m_tFrame.fCurFrame = 0.f;
			m_tFrame.fMaxFrame = 38.f;
			break;
		case DEATH:
			m_tFrame.fCurFrame = 0.f;
			m_tFrame.fMaxFrame = 81.f;
			break;
		case RECOVER:
			m_tFrame.fCurFrame = 0.f;
			m_tFrame.fMaxFrame = 23.f;
			break;
		}

		m_ePreState = m_eCurState;
	}
}

void CBoss::PunchPattern()
{
	m_eCurState = LAUNCH;
	m_wstrImageKey = L"LAUNCH";

}

void CBoss::RockPattern()
{
	m_eCurState = SPAWN;
	m_wstrImageKey = L"SPAWN";
}

void CBoss::WavePattern()
{
	
}

void CBoss::SetState(BOSS_STATE eState, wstring wstrImageKey)
{
	m_eCurState = eState;
	m_wstrImageKey = wstrImageKey;
}

FRAME & CBoss::GetFrame() 
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_tFrame;
}
