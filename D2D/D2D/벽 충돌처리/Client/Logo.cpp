#include "stdafx.h"
#include "Logo.h"
#include "MyButton.h"


CLogo::CLogo()
	: m_fMoveWall(0.f), m_bNext(false),
	m_pKeyMgr(CKeyMgr::GetInstance())
{
}


CLogo::~CLogo()
{
	Release();
}

int CLogo::Update()
{
	m_tFrame.fCurFrame += m_tFrame.fMaxFrame * m_pTimeMgr->GetDelta()/* * 20.f*/;

	if (m_tFrame.fMaxFrame <= m_tFrame.fCurFrame)
		m_tFrame.fCurFrame = 0.f;
	
	int iEVENT = m_pObjectMgr->Update();
	KeyInput();

	return iEVENT;
}

void CLogo::LateUpdate()
{
	m_pObjectMgr->LateUpdate();
}

void CLogo::Render()
{
	if (m_bNext)
		WallMove();

	// Logo_Back_1
	const TEX_INFO* pTexInfo = m_pTextureMgr->GetTexInfo(L"LOGO", L"BACK_1", (int)m_tFrame.fCurFrame);
	NULL_CHECK(pTexInfo);

	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);

	m_pDeviceMgr->GetSprite()->SetTransform(&matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, nullptr,
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	// Logo_Back_2
	pTexInfo = m_pTextureMgr->GetTexInfo(L"LOGO", L"BACK_2", (int)m_tFrame.fCurFrame);
	NULL_CHECK(pTexInfo);

	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, nullptr,
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	// LogoWall_Left
	pTexInfo = m_pTextureMgr->GetTexInfo(L"LogoWall_LEFT");
	NULL_CHECK(pTexInfo);

	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, nullptr,
		&D3DXVECTOR3(-m_fMoveWall, 0.f, 0.f), D3DCOLOR_ARGB(255, 255, 255, 255));
	
	// LogoWall_Right
	pTexInfo = m_pTextureMgr->GetTexInfo(L"LogoWall_RIGHT");
	NULL_CHECK(pTexInfo);

	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, nullptr,
		&D3DXVECTOR3(WINCX * 0.5f + m_fMoveWall, 0.f, 0.f), D3DCOLOR_ARGB(255, 255, 255, 255));
	
	// GameLogo
	pTexInfo = m_pTextureMgr->GetTexInfo(L"GameLogo");
	NULL_CHECK(pTexInfo);

	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(pTexInfo->tImgInfo.Width * 0.5f, pTexInfo->tImgInfo.Height * 0.5f, 0.f),
		&D3DXVECTOR3(WINCX * 0.5f, WINCY * 0.25f, 0.f), D3DCOLOR_ARGB(255, 255, 255, 255));

	if (m_fMoveWall < 50.f)
	{
		// LogoLight
		pTexInfo = m_pTextureMgr->GetTexInfo(L"LogoLight");
		NULL_CHECK(pTexInfo);

		m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, nullptr,
			nullptr, D3DCOLOR_ARGB(125, 255, 255, 255));

	}
	else
		m_pObjectMgr->Render();
	

}

HRESULT CLogo::Initialize()
{
	LPDIRECT3DDEVICE9 pGraphicDev = m_pDeviceMgr->GetDevice();
	NULL_CHECK_MSG_RETURN(pGraphicDev, L"pGraphicDev is null", E_FAIL);

	// LOGO BACK_1 TEXTURE
	HRESULT hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../TEXTRUE/LOGO/LogoBack_1_%d.png",
		L"LOGO",
		L"BACK_1",
		16);
	FAILED_CHECK_MSG_RETURN(hr, L"Logo Back_1 LoadTexture Failed", E_FAIL);

	// LOGO BACK_2 TEXTURE
	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../TEXTRUE/LOGO/LogoBack_2_%d.png",
		L"LOGO",
		L"BACK_2",
		16);
	FAILED_CHECK_MSG_RETURN(hr, L"Logo Back_2 LoadTexture Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_SINGLE,
		L"../TEXTRUE/LOGO/LogoWall_LEFT.png",
		L"LogoWall_LEFT");
	FAILED_CHECK_MSG_RETURN(hr, L"LogoWall_LEFT LoadTexture Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_SINGLE,
		L"../TEXTRUE/LOGO/LogoWall_RIGHT.png",
		L"LogoWall_RIGHT");
	FAILED_CHECK_MSG_RETURN(hr, L"LogoWall_RIGHT LoadTexture Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_SINGLE,
		L"../TEXTRUE/LOGO/GameLogo.png",
		L"GameLogo");
	FAILED_CHECK_MSG_RETURN(hr, L"GameLogo LoadTexture Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_SINGLE,
		L"../TEXTRUE/LOGO/LogoLight.png",
		L"LogoLight");
	FAILED_CHECK_MSG_RETURN(hr, L"LogoLight LoadTexture Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_SINGLE,
		L"../TEXTRUE/LOGO/Choice_left.png",
		L"Choice_left");
	FAILED_CHECK_MSG_RETURN(hr, L"Choice_left LoadTexture Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_SINGLE,
		L"../TEXTRUE/LOGO/Choice_Right.png",
		L"Choice_Right");
	FAILED_CHECK_MSG_RETURN(hr, L"Choice_left LoadTexture Failed", E_FAIL);

	CMyButton* temp = CMyButton::Create();
	temp->SetINFO(L"게임 시작", D3DXVECTOR3(WINCX * 0.5f, WINCY * 0.5f + 25,0.f), SCENE_STAGE);

	m_pObjectMgr->AddObject(OBJECT_BUTTON,temp);

	temp = CMyButton::Create();
	temp->SetINFO(L"종료", D3DXVECTOR3(WINCX * 0.5f, WINCY * 0.5f + 70, 0.f), SCENE_DESTORY);

	m_pObjectMgr->AddObject(OBJECT_BUTTON, temp);

	dynamic_cast<CMyButton*>(m_pObjectMgr->GetList(OBJECT_BUTTON).front())->SetTarget(TRUE);

	m_tFrame.fCurFrame = 0.f;
	m_tFrame.fMaxFrame = 16.f;
	m_fMoveWall = 0.f;

	return S_OK;
}

void CLogo::Release()
{
	for_each(m_pObjectMgr->GetList(OBJECT_BUTTON).begin(), m_pObjectMgr->GetList(OBJECT_BUTTON).end(), SafeDelete<CGameObject*>);
	m_pObjectMgr->GetList(OBJECT_BUTTON).clear();
}

int CLogo::KeyInput()
{
	if (m_pKeyMgr->KeyDown(KEY_RETURN))
		m_bNext = true;

	if (m_pKeyMgr->KeyDown(KEY_W))
	{
		auto iter_begin = m_pObjectMgr->GetList(OBJECT_BUTTON).begin();
		auto iter_end = m_pObjectMgr->GetList(OBJECT_BUTTON).end();

		for (; iter_begin != iter_end; ++iter_begin)
		{
			if (dynamic_cast<CMyButton*>(*iter_begin)->GetTarget())
			{
				if (*iter_begin == m_pObjectMgr->GetList(OBJECT_BUTTON).front())
					break;

				dynamic_cast<CMyButton*>(*iter_begin)->SetTarget(FALSE);
				dynamic_cast<CMyButton*>(*(--iter_begin))->SetTarget(TRUE);
				break;
			}
		}
	}

	if (m_pKeyMgr->KeyDown(KEY_S))
	{
		auto iter_begin = m_pObjectMgr->GetList(OBJECT_BUTTON).begin();
		auto iter_end = m_pObjectMgr->GetList(OBJECT_BUTTON).end();

		for (; iter_begin != iter_end; ++iter_begin)
		{
			if (dynamic_cast<CMyButton*>(*iter_begin)->GetTarget())
			{
				if(*iter_begin == m_pObjectMgr->GetList(OBJECT_BUTTON).back())
					break;

				dynamic_cast<CMyButton*>(*iter_begin)->SetTarget(FALSE);
				dynamic_cast<CMyButton*>(*(++iter_begin))->SetTarget(TRUE);
				break;
			}
		}
	}

	if (m_pKeyMgr->KeyDown(KEY_J))
	{
		auto iter_begin = m_pObjectMgr->GetList(OBJECT_BUTTON).begin();
		auto iter_end = m_pObjectMgr->GetList(OBJECT_BUTTON).end();

		for (; iter_begin != iter_end; ++iter_begin)
		{
			if (dynamic_cast<CMyButton*>(*iter_begin)->GetTarget())
			{
				m_pSceneMgr->SceneChange(SCENE_LOGO, dynamic_cast<CMyButton*>(*iter_begin)->GetScene());
				return CHANGE_SCENE;
			}
		}
	}

	return NO_EVENT;
}

bool CLogo::WallMove()
{
	if (m_fMoveWall < 50.f)
	{
		m_fMoveWall += 5.f;
	}
	else if(m_fMoveWall < 200.f)
		m_fMoveWall += 2.f;

	if(m_fMoveWall >= 200.f)
		return true;

	return false;
}

CLogo* CLogo::Create()
{
	CLogo* pInstance = new CLogo;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
