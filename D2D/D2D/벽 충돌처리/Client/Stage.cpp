#include "stdafx.h"
#include "Stage.h"
#include "Terrain.h"
#include "Player.h"

CStage::CStage()
{
}


CStage::~CStage()
{
	Release();
}

int CStage::Update()
{
	m_pObjectMgr->Update();

	return NO_EVENT;
}

void CStage::LateUpdate()
{
	m_pObjectMgr->LateUpdate();
}

void CStage::Render()
{
	m_pObjectMgr->Render();
}

HRESULT CStage::Initialize()
{
	LPDIRECT3DDEVICE9 pGraphicDev = m_pDeviceMgr->GetDevice();
	NULL_CHECK_MSG_RETURN(pGraphicDev, L"pGraphicDev is null", E_FAIL);

	// Terrain Tile Texture
	HRESULT hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../TEXTRUE/TILE/TILE%d.png",
		L"Terrain",
		L"Tile",
		3);
	FAILED_CHECK_MSG_RETURN(hr, L"Terrain Tile LoadTexture Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
		L"../TEXTRUE/BACKGROUND/Back%d.png",
		L"BackGround", L"Back", 2);
	FAILED_CHECK_MSG_RETURN(hr, L"BACKGROUND Texture Load Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
		L"../TEXTRUE/DUNGEON/LowerDetail/LowerDetail_%d.png",
		L"Dungeon", L"Detail", 15);
	FAILED_CHECK_MSG_RETURN(hr, L"LowerDetail Texture Load Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
		L"../TEXTRUE/DUNGEON/Breakable/Breakable_%d.png",
		L"Dungeon", L"Breakable", 6);
	FAILED_CHECK_MSG_RETURN(hr, L"Breakable Texture Load Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
		L"../TEXTRUE/DUNGEON/Wall/Wall_%d.png",
		L"Dungeon", L"Wall", 1);
	FAILED_CHECK_MSG_RETURN(hr, L"Dungeon_Wall Texture Load Failed", E_FAIL);

	// Terrain Object
	hr = m_pObjectMgr->AddObject(OBJECT_TERRAIN, CTerrain::Create());
	FAILED_CHECK_MSG_RETURN(hr, L"Terrain Create Failed", E_FAIL);

	// Player Object
	hr = m_pObjectMgr->AddObject(OBJECT_PLAYER, CPlayer::Create());
	FAILED_CHECK_MSG_RETURN(hr, L"Player Create Failed", E_FAIL);

	m_pObjectMgr->LoadObject(L"../Data/Map_0.dat");

	return S_OK;
}

void CStage::Release()
{
}

CStage* CStage::Create()
{
	CStage* pInstance = new CStage;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}