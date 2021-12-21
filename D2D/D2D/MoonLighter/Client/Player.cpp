#include "stdafx.h"
#include "Player.h"
#include "Inventory.h"
#include "UI.h"

CPlayer::CPlayer()
	: m_pKeyMgr(CKeyMgr::GetInstance()),
	m_bIsRoll(false),
	m_bIsAttack(false),
	m_bIsSwing(false),
	m_bIsSystem(false),
	m_fSwingCheck(0.f),
	m_iPotionCount(0),
	m_dwUP(0x00000001),			// 0000	0000 0000 0000 0000 0000 0000 0001
	m_dwDOWN(0x00000002),		// 0000 0000 0000 0000 0000 0000 0000 0010
	m_dwLEFT(0x00000004),		// 0000 0000 0000 0000 0000 0000 0000 0100
	m_dwRIGHT(0x00000008),		// 0000 0000 0000 0000 0000 0000 0000 1000

	m_dwBIGSWORD(0x00000001),	// 0000 0000 0000 0000 0000 0000 0000 0001
	m_dwSHORTSWORD(0x00000002), // 0000 0000 0000 0000 0000 0000 0000 0010
	m_dwBOW(0x00000004),		// 0000 0000 0000 0000 0000 0000 0000 0100
	m_dwGLOVE(0x00000008),		// 0000 0000 0000 0000 0000 0000 0000 1000
	m_dwSPEAR(0x00000010)		// 0000 0000 0000 0000 0000 0000 0001 0000
{
	ZeroMemory(&m_tPInfo, sizeof(INFO));
	ZeroMemory(&m_tFrame, sizeof(FRAME));
	ZeroMemory(&m_tOInfo, sizeof(OBINFO));
}


CPlayer::~CPlayer()
{
	Release();
}

int CPlayer::Update()
{	
	m_tFrame.fCurFrame += m_tFrame.fMaxFrame * m_pTimeMgr->GetDelta() * m_fMotionSpeed/* * 20.f*/;

	if (m_tFrame.fMaxFrame <= m_tFrame.fCurFrame)
	{
		m_tFrame.fCurFrame = 0.f;
		m_fMotionSpeed = 1.f;
		m_fCheck = 12.f;
		m_fSwingCheck = 0.f;
		m_bIsRoll = false;
		m_bIsAttack = false;
		m_bIsSwing = false;
	}
	if (m_bIsRoll && 1 == (int)m_tFrame.fCurFrame)
	{
		CSoundMgr::GetInstance()->PlaySound(L"ROLL.wav", CSoundMgr::PLAYER);
		++m_tFrame.fCurFrame;
	}

	if (m_bIsSwing && 13 == (int)m_tFrame.fCurFrame)
	{
		CSoundMgr::GetInstance()->PlaySound(L"BIG_S.wav", CSoundMgr::PLAYER);
		++m_tFrame.fCurFrame;
	}

	if (m_bIsAttack && 1 == (int)m_tFrame.fCurFrame)
	{
		CSoundMgr::GetInstance()->PlaySound(L"BIG_1.wav", CSoundMgr::PLAYER);
		++m_tFrame.fCurFrame;
	}
	else if (m_bIsAttack && 15 == (int)m_tFrame.fCurFrame)
	{
		CSoundMgr::GetInstance()->PlaySound(L"BIG_2.wav", CSoundMgr::PLAYER);
		++m_tFrame.fCurFrame;
	}
	else if (m_bIsAttack && 28 == (int)m_tFrame.fCurFrame)
	{
		CSoundMgr::GetInstance()->PlaySound(L"BIG_3.wav", CSoundMgr::PLAYER);
		++m_tFrame.fCurFrame;
	}
	if (m_bIsAttack && (5 == (int)m_tFrame.fCurFrame || 16 == (int)m_tFrame.fCurFrame || 26 == (int)m_tFrame.fCurFrame))
	{
		if (m_dwCurWay & m_dwUP)
			m_tPInfo.tAttackRange = {LONG(m_tPInfo.vPos.x - 25), LONG(m_tPInfo.vPos.y - 75), 
									LONG(m_tPInfo.vPos.x + 25), LONG(m_tPInfo.vPos.y -25)};
		else if (m_dwCurWay & m_dwDOWN)
			m_tPInfo.tAttackRange = { LONG(m_tPInfo.vPos.x - 25), LONG(m_tPInfo.vPos.y + 25), 
									LONG(m_tPInfo.vPos.x + 25), LONG(m_tPInfo.vPos.y + 75) };
		else if (m_dwCurWay & m_dwLEFT)
			m_tPInfo.tAttackRange = { LONG(m_tPInfo.vPos.x - 75), LONG(m_tPInfo.vPos.y - 25), 
									LONG(m_tPInfo.vPos.x - 25), LONG(m_tPInfo.vPos.y + 25) };
		else if (m_dwCurWay & m_dwRIGHT)
			m_tPInfo.tAttackRange = { LONG(m_tPInfo.vPos.x + 25), LONG(m_tPInfo.vPos.y - 25), 
									LONG(m_tPInfo.vPos.x + 75), LONG(m_tPInfo.vPos.y + 25) };
	}
	if (m_bIsAttack && (8 == (int)m_tFrame.fCurFrame || 19 == (int)m_tFrame.fCurFrame || 29 == (int)m_tFrame.fCurFrame))
	{
		m_tPInfo.tAttackRange = {0,0,0,0};
	}

	if (m_bIsSwing && (18 == (int)m_tFrame.fCurFrame || 22 == (int)m_tFrame.fCurFrame))
	{
		m_tPInfo.tAttackRange = { LONG(m_tPInfo.vPos.x + 25), LONG(m_tPInfo.vPos.y - 25),
							LONG(m_tPInfo.vPos.x + 75), LONG(m_tPInfo.vPos.y + 25) };
	}
	else if (m_bIsSwing && (19 == (int)m_tFrame.fCurFrame || 24 == (int)m_tFrame.fCurFrame))
	{
		m_tPInfo.tAttackRange = { LONG(m_tPInfo.vPos.x - 25), LONG(m_tPInfo.vPos.y + 25),
			LONG(m_tPInfo.vPos.x + 25), LONG(m_tPInfo.vPos.y + 75) };
	}
	else if (m_bIsSwing && 20 == (int)m_tFrame.fCurFrame)
	{
		m_tPInfo.tAttackRange = { LONG(m_tPInfo.vPos.x - 75), LONG(m_tPInfo.vPos.y - 25),
			LONG(m_tPInfo.vPos.x - 25), LONG(m_tPInfo.vPos.y + 25) };
	}
	else if (m_bIsSwing && 21 == (int)m_tFrame.fCurFrame)
	{
		m_tPInfo.tAttackRange = { LONG(m_tPInfo.vPos.x - 25), LONG(m_tPInfo.vPos.y - 75),
			LONG(m_tPInfo.vPos.x + 25), LONG(m_tPInfo.vPos.y - 25) };
	}
	if (m_bIsSwing && 25 == (int)m_tFrame.fCurFrame)
	{
		m_tPInfo.tAttackRange = { 0,0,0,0 };
	}
	if (!m_bIsSystem)
	{
		KeyInput();
	}
	ChangeState();
	Invincibillity();
	CObjectMgr::GetInstance()->AddLayer(LAYER_OBJECT, this);

	return NO_EVENT;
}

void CPlayer::LateUpdate()
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

void CPlayer::Render()
{
	const TEX_INFO* pTexInfo = m_pTextureMgr->GetTexInfo(L"Player", m_wstrImageKey, (int)m_tFrame.fCurFrame);
	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	m_tPInfo.tRect = { LONG(m_tPInfo.vPos.x - fCenterX), LONG(m_tPInfo.vPos.y - fCenterY),LONG(m_tPInfo.vPos.x + fCenterX), LONG(m_tPInfo.vPos.y + fCenterY) };

	m_pDeviceMgr->GetSprite()->SetTransform(&m_tPInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255 - m_tOInfo.Alpha, 255, 255 , 255));

	if (m_bIsAttack || m_bIsSwing)
	{
		pTexInfo = m_pTextureMgr->GetTexInfo(L"Weapon", m_wstrWeaponImageKey, (int)m_tFrame.fCurFrame);
		NULL_CHECK(pTexInfo);

		float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		m_pDeviceMgr->GetSprite()->SetTransform(&m_tPInfo.matWorld);
		m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
			nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

HRESULT CPlayer::Initialize()
{
	// 행렬 초기화 -> 항등행렬(I)
	//CMathMgr::MyMatrixIdentity(&m_tPInfo.matWorld);
	D3DXMatrixIdentity(&m_tPInfo.matWorld); // 다이렉트 항등행렬 함수

	m_tPInfo.vPos = { WINCX * 0.5f, WINCY * 0.5f, 0.f }; // x, y, z
	m_tPInfo.vDir = { 0.f, 0.f, 0.f };
	m_tPInfo.vLook = { 0.f, -1.f, 0.f };
	m_tPInfo.vSize = { 1.f, 1.f, 0.f };

	m_tFrame.fCurFrame = 0.f;
	m_tFrame.fMaxFrame = 10.f;

	m_tOInfo.iAttack = 10;
	m_tOInfo.iDef = 5;
	m_tOInfo.iMaxHp = 100;
	m_tOInfo.iHp = m_tOInfo.iMaxHp;

	m_iPotionCount = 1;
	m_tOInfo.fMaxInvinTime = 2.f;

	m_tPInfo.fSpeed = 150.f;
	m_fMotionSpeed = 1.f;

	m_wstrImageKey = L"IDLE_RIGHT";
	m_wstrWeaponImageKey = L"";
	m_eCurState = IDLE;
	m_bIsRoll = false;
	m_bIsAttack = false;
	m_vecItem.reserve(20);
	m_vecItem.resize(20);
	LPDIRECT3DDEVICE9 pGraphicDev = m_pDeviceMgr->GetDevice();
	NULL_CHECK_MSG_RETURN(pGraphicDev, L"pGraphicDev is null", E_FAIL);

	m_pObjectMgr->AddObject(OBJECT_UI, CUI::Create());

	//IDLE_DOWN
	HRESULT hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../TEXTRUE/PLAYER/FLEID/IDLE/DOWN/IDLE_DOWN%d.png",
		L"Player",
		L"IDLE_DOWN",
		10);
	FAILED_CHECK_MSG_RETURN(hr, L"Player IDLE_DOWN LoadTexture Failed", E_FAIL);
	//IDLE_UP
	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../TEXTRUE/PLAYER/FLEID/IDLE/UP/IDLE_UP%d.png",
		L"Player",
		L"IDLE_UP",
		10);
	FAILED_CHECK_MSG_RETURN(hr, L"Player IDLE_UP LoadTexture Failed", E_FAIL);
	//IDLE_LEFT
	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../TEXTRUE/PLAYER/FLEID/IDLE/LEFT/IDLE_LEFT%d.png",
		L"Player",
		L"IDLE_LEFT",
		10);
	FAILED_CHECK_MSG_RETURN(hr, L"Player IDLE_LEFT LoadTexture Failed", E_FAIL);
	//IDLE_RIGHT
	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../TEXTRUE/PLAYER/FLEID/IDLE/RIGHT/IDLE_RIGHT%d.png",
		L"Player",
		L"IDLE_RIGHT",
		10);
	FAILED_CHECK_MSG_RETURN(hr, L"Player IDLE_RIGHT LoadTexture Failed", E_FAIL);

	//WALK_UP
	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../TEXTRUE/PLAYER/FLEID/WALK/UP/WALK_UP%d.png",
		L"Player",
		L"WALK_UP",
		8);
	FAILED_CHECK_MSG_RETURN(hr, L"Player WALK_UP LoadTexture Failed", E_FAIL);
	//WALK_DOWN
	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../TEXTRUE/PLAYER/FLEID/WALK/DOWN/WALK_DOWN%d.png",
		L"Player",
		L"WALK_DOWN",
		8);
	FAILED_CHECK_MSG_RETURN(hr, L"Player WALK_DOWN LoadTexture Failed", E_FAIL);
	//WALK_LEFT
	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../TEXTRUE/PLAYER/FLEID/WALK/LEFT/WALK_LEFT%d.png",
		L"Player",
		L"WALK_LEFT",
		8);
	FAILED_CHECK_MSG_RETURN(hr, L"Player WALK_LEFT LoadTexture Failed", E_FAIL);
	//WALK_RIGHT
	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../TEXTRUE/PLAYER/FLEID/WALK/RIGHT/WALK_RIGHT%d.png",
		L"Player",
		L"WALK_RIGHT",
		8);
	FAILED_CHECK_MSG_RETURN(hr, L"Player WALK_RIGHT LoadTexture Failed", E_FAIL);

	//ROLL_UP
	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../TEXTRUE/PLAYER/FLEID/ROLL/UP/ROLL_UP%d.png",
		L"Player",
		L"ROLL_UP",
		8);
	FAILED_CHECK_MSG_RETURN(hr, L"Player ROLL_UP LoadTexture Failed", E_FAIL);
	//ROLL_DOWN
	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../TEXTRUE/PLAYER/FLEID/ROLL/DOWN/ROLL_DOWN%d.png",
		L"Player",
		L"ROLL_DOWN",
		8);
	FAILED_CHECK_MSG_RETURN(hr, L"Player ROLL_DOWN LoadTexture Failed", E_FAIL);
	//ROLL_LEFT
	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../TEXTRUE/PLAYER/FLEID/ROLL/LEFT/ROLL_LEFT%d.png",
		L"Player",
		L"ROLL_LEFT",
		8);
	FAILED_CHECK_MSG_RETURN(hr, L"Player ROLL_LEFT LoadTexture Failed", E_FAIL);
	//ROLL_RIGHT
	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../TEXTRUE/PLAYER/FLEID/ROLL/RIGHT/ROLL_RIGHT%d.png",
		L"Player",
		L"ROLL_RIGHT",
		8);
	FAILED_CHECK_MSG_RETURN(hr, L"Player ROLL_RIGHT LoadTexture Failed", E_FAIL);
	//BIG_DOWN
	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../TEXTRUE/PLAYER/ATTACK/BIGSWORD/DOWN/BIG_DOWN_%d.png",
		L"Player",
		L"BIG_DOWN",
		39);
	FAILED_CHECK_MSG_RETURN(hr, L"Player BIG_DOWN LoadTexture Failed", E_FAIL);
	//BIG_LEFT
	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../TEXTRUE/PLAYER/ATTACK/BIGSWORD/LEFT/BIG_LEFT_%d.png",
		L"Player",
		L"BIG_LEFT",
		39);
	FAILED_CHECK_MSG_RETURN(hr, L"Player BIG_LEFT LoadTexture Failed", E_FAIL);
	//BIG_RIGHT
	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../TEXTRUE/PLAYER/ATTACK/BIGSWORD/RIGHT/BIG_RIGHT_%d.png",
		L"Player",
		L"BIG_RIGHT",
		39);
	FAILED_CHECK_MSG_RETURN(hr, L"Player BIG_RIGHT LoadTexture Failed", E_FAIL);
	//BIG_UP
	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../TEXTRUE/PLAYER/ATTACK/BIGSWORD/UP/BIG_UP_%d.png",
		L"Player",
		L"BIG_UP",
		39);
	FAILED_CHECK_MSG_RETURN(hr, L"Player BIG_UP LoadTexture Failed", E_FAIL);
	//W_BIG_DOWN
	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../TEXTRUE/WAPON/W_BIG/DOWN/W_BIG_DOWN_%d.png",
		L"Weapon",
		L"W_BIG_DOWN",
		39);
	FAILED_CHECK_MSG_RETURN(hr, L"W_BIG_DOWN LoadTexture Failed", E_FAIL);
	//W_BIG_LEFT
	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../TEXTRUE/WAPON/W_BIG/LEFT/W_BIG_LEFT_%d.png",
		L"Weapon",
		L"W_BIG_LEFT",
		39);
	FAILED_CHECK_MSG_RETURN(hr, L"W_BIG_LEFT LoadTexture Failed", E_FAIL);
	//W_BIG_RIGHT
	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../TEXTRUE/WAPON/W_BIG/RIGHT/W_BIG_RIGHT_%d.png",
		L"Weapon",
		L"W_BIG_RIGHT",
		39);
	FAILED_CHECK_MSG_RETURN(hr, L"W_BIG_RIGHT LoadTexture Failed", E_FAIL);
	//W_BIG_UP
	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../TEXTRUE/WAPON/W_BIG/UP/W_BIG_UP_%d.png",
		L"Weapon",
		L"W_BIG_UP",
		39);
	FAILED_CHECK_MSG_RETURN(hr, L"W_BIG_UP LoadTexture Failed", E_FAIL);


	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../TEXTRUE/PLAYER/ATTACK/BIGSWORD/BIG_SECOND/DOWN/BIG_S_DOWN%d.png",
		L"Player",
		L"BIG_S_DOWN",
		34);
	FAILED_CHECK_MSG_RETURN(hr, L"Player BIG_S_DOWN LoadTexture Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../TEXTRUE/WAPON/W_BIG/W_BIG_SECOND/DOWN/W_BIG_S_%d.png",
		L"Weapon",
		L"W_BIG_S_",
		34);
	FAILED_CHECK_MSG_RETURN(hr, L"WAPON W_BIG_S_ LoadTexture Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
		L"../TEXTRUE/ITEM/ITEM_%d.png",
		L"ITEM", L"ITEM", 4);
	FAILED_CHECK_MSG_RETURN(hr, L"ITEM Texture Load Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
		L"../TEXTRUE/INVEN/Inventory_%d.png",
		L"INVEN", L"INVEN", 3);
	FAILED_CHECK_MSG_RETURN(hr, L"ITEM Texture Load Failed", E_FAIL);

	return S_OK;
}

void CPlayer::Release()
{
}

CPlayer* CPlayer::Create()
{
	CPlayer* pInstance = new CPlayer;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CPlayer::SetSystem(bool bSystem)
{
	m_bIsSystem = bSystem;
}

bool CPlayer::GetIsRoll()
{
	return m_bIsRoll;
}

int CPlayer::GetPotionCount()
{
	return m_iPotionCount;
}

void CPlayer::KeyInput()
{
	if (!m_bIsRoll && !m_bIsAttack && !m_bIsInven && !m_bIsSwing)
	{
		if (m_pKeyMgr->KeyPressing(KEY_A))
		{
			m_tPInfo.vLook = { -1.0f,0.f,0.f };
			m_dwCurWay = 0;
			m_dwCurWay |= m_dwLEFT;
			m_wstrImageKey = L"WALK_LEFT";
			m_eCurState = WALK;
		}
		else if (m_pKeyMgr->KeyPressing(KEY_D))
		{
			m_tPInfo.vLook = { 1.0f,0.f,0.f };
			m_dwCurWay = 0;
			m_dwCurWay |= m_dwRIGHT;
			m_wstrImageKey = L"WALK_RIGHT";
			m_eCurState = WALK;
		}
		else if (m_pKeyMgr->KeyPressing(KEY_W))
		{
			m_tPInfo.vLook = { 0.f,-1.f,0.f };
			m_dwCurWay = 0;
			m_dwCurWay |= m_dwUP;
			m_wstrImageKey = L"WALK_UP";
			m_eCurState = WALK;
		}
		else if (m_pKeyMgr->KeyPressing(KEY_S))
		{
			m_tPInfo.vLook = { 0.f,1.f,0.f };
			m_dwCurWay = 0;
			m_dwCurWay |= m_dwDOWN;
			m_wstrImageKey = L"WALK_DOWN";
			m_eCurState = WALK;
		}
		else
		{
			m_tPInfo.vLook = {0.f,0.f,0.f};
			if(m_dwCurWay & m_dwUP)
				m_wstrImageKey = L"IDLE_UP";
			else if (m_dwCurWay & m_dwDOWN)
				m_wstrImageKey = L"IDLE_DOWN";
			else if (m_dwCurWay & m_dwLEFT)
				m_wstrImageKey = L"IDLE_LEFT";
			else if (m_dwCurWay & m_dwRIGHT)
				m_wstrImageKey = L"IDLE_RIGHT";
			m_eCurState = IDLE;
		}
		
	}

	if (m_pKeyMgr->KeyDown(KEY_I))
	{
		if (m_bIsInven == false)
		{
			m_pObjectMgr->AddObject(OBJECT_UI, CInventory::Create());
			m_bIsInven = true;
		}
		else
		{
			dynamic_cast<CInventory*>(m_pObjectMgr->GetList(OBJECT_UI).back())->SetDelete();
			m_bIsInven = false;
		}
	}
	
	if (m_pKeyMgr->KeyDown(KEY_SPACE) && !m_bIsAttack && !m_bIsSwing)
	{
		if (m_dwCurWay & m_dwUP)
			m_wstrImageKey = L"ROLL_UP";
		else if (m_dwCurWay & m_dwDOWN)
			m_wstrImageKey = L"ROLL_DOWN";
		else if (m_dwCurWay & m_dwLEFT)
			m_wstrImageKey = L"ROLL_LEFT";
		else if (m_dwCurWay & m_dwRIGHT)
			m_wstrImageKey = L"ROLL_RIGHT";
		m_eCurState = ROLL;
		m_fMotionSpeed = 2.f;
		m_bIsRoll = true;
		
	}

	if (m_bIsAttack && m_tFrame.fCurFrame - m_fCheck > 0)
	{
		if (m_pKeyMgr->KeyDown(KEY_J))
		{
			m_bIsAttack = true;
			m_fCheck += 13.f ;
	
		}
		else if (m_tFrame.fCurFrame - m_fCheck > 3)
		{
			m_bIsAttack = false;
			m_fCheck = 12.f;
			m_fMotionSpeed = 1.f;
		}
	}
	else if (m_pKeyMgr->KeyDown(KEY_J) && !m_bIsRoll && !m_bIsSwing && !m_bIsInven)
	{
		m_tPInfo.vLook = { 0.f,0.f,0.f };
		if (m_dwCurWay & m_dwUP)
		{
			m_wstrImageKey = L"BIG_UP";
			m_wstrWeaponImageKey = L"W_BIG_UP";
		}	
		else if (m_dwCurWay & m_dwDOWN)
		{
			m_wstrImageKey = L"BIG_DOWN";
			m_wstrWeaponImageKey = L"W_BIG_DOWN";
		}
		else if (m_dwCurWay & m_dwLEFT)
		{
			m_wstrImageKey = L"BIG_LEFT";
			m_wstrWeaponImageKey = L"W_BIG_LEFT";
		}
		else if (m_dwCurWay & m_dwRIGHT)
		{
			m_wstrImageKey = L"BIG_RIGHT";
			m_wstrWeaponImageKey = L"W_BIG_RIGHT";
		}
		
		m_fMotionSpeed = 0.5f;
		m_eCurState = ATTACK;
		m_bIsAttack = true;
	}

	if (m_pKeyMgr->KeyPressing(KEY_E) && !m_bIsInven)
	{
		if (m_iPotionCount > 0)
		{
			m_tOInfo.iHp += 20;
			if(m_tOInfo.iHp >= m_tOInfo.iMaxHp)
				m_tOInfo.iHp = m_tOInfo.iMaxHp;
			--m_iPotionCount;
		}
		if(m_iPotionCount < 0)
			m_iPotionCount = 0;

	}

	if (m_pKeyMgr->KeyPressing(KEY_K) && !m_bIsRoll && !m_bIsInven)
	{
		m_tPInfo.vLook = { 0.f,0.f,0.f };
		
		m_wstrImageKey = L"BIG_S_DOWN";
		m_wstrWeaponImageKey = L"W_BIG_S_";

		m_fSwingCheck += m_tFrame.fMaxFrame * m_pTimeMgr->GetDelta() * m_fMotionSpeed;

		m_fMotionSpeed = 0.5f;
		m_eCurState = SECOND_ATTACK;
		m_bIsSwing = true;
	}
	else if (m_bIsSwing && m_fSwingCheck < 10.f)
	{
		m_tPInfo.vLook = { 0.f,0.f,0.f };
		if (m_dwCurWay & m_dwUP)
			m_wstrImageKey = L"IDLE_UP";
		else if (m_dwCurWay & m_dwDOWN)
			m_wstrImageKey = L"IDLE_DOWN";
		else if (m_dwCurWay & m_dwLEFT)
			m_wstrImageKey = L"IDLE_LEFT";
		else if (m_dwCurWay & m_dwRIGHT)
			m_wstrImageKey = L"IDLE_RIGHT";
		m_eCurState = IDLE;

		m_bIsSwing = false;
	}
	
}

void CPlayer::ChangeState()
{
	if (m_ePreState != m_eCurState)
	{
		m_tPInfo.tAttackRange = { 0,0,0,0 };
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.fCurFrame = 0.f;
			m_tFrame.fMaxFrame = 10.f;
			break;
		case WALK:
			m_tFrame.fCurFrame = 0.f;
			m_tFrame.fMaxFrame = 8.f;
			break;
		case ROLL:
			m_tFrame.fCurFrame = 0.f;
			m_tFrame.fMaxFrame = 8.f;
			break;
		case ATTACK:
			m_tFrame.fCurFrame = 0.f;
			m_tFrame.fMaxFrame = 39.f;
			break;
		case SECOND_ATTACK:
			m_tFrame.fCurFrame = 0.f;
			m_tFrame.fMaxFrame = 33.f;
			break;
		}

		m_ePreState = m_eCurState;
	}
}

vector<CGameObject*>& CPlayer::GetItemVec()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_vecItem;
}

void CPlayer::PushItem(CGameObject* Item)
{
	if (Item->GetITinfo().byOption == 1)
	{
		++m_iPotionCount;
		return;
	}
		

	for (int i = 0; i < m_vecItem.capacity(); ++i)
	{
		if (m_vecItem[i] == NULL)
		{
			m_vecItem[i] = (Item);
			return;
		}
		if (m_vecItem[i]->GetITinfo().byOption == 0)
		{
			if (m_vecItem[i]->GetITinfo().byDrawID == Item->GetITinfo().byDrawID)
			{
				++m_vecItem[i]->GetITinfo().iAmount;
				return;
				
			}
		}
	}

}

void CPlayer::PopItem(int i)
{
	if(m_vecItem[i] == nullptr)
		return;
	else 
		--m_vecItem[i]->GetITinfo().iAmount;

	if(m_vecItem[i]->GetITinfo().iAmount == 0)
		;//m_vecItem[i] = nullptr;
}

void CPlayer::SwapItem(int i, int j)
{
	
}
