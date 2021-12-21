#include "stdafx.h"
#include "Stage.h"
#include "Terrain.h"
#include "Door.h"
#include "Player.h"
#include "Monster.h"
#include "Monster2.h"


CStage::CStage() :
	m_pTerrain(nullptr)
{
	ZeroMemory(m_iMap, sizeof(m_iMap));
}


CStage::~CStage()
{
	Release();
}

int CStage::Update()
{
	m_pObjectMgr->Update();
	m_pTerrain = dynamic_cast<CTerrain*>(m_pObjectMgr->GetMap());
	OpenCloseDoor();

	if (m_pKeyMgr->KeyDown(KEY_B))
	{
		m_pSceneMgr->SceneChange(SCENE_STAGE, SCENE_BOSS);
		return CHANGE_SCENE;
	}

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
		4);
	FAILED_CHECK_MSG_RETURN(hr, L"Terrain Tile LoadTexture Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
		L"../TEXTRUE/BACKGROUND/Back%d.png",
		L"BackGround", L"Back", 2);
	FAILED_CHECK_MSG_RETURN(hr, L"BACKGROUND Texture Load Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
		L"../TEXTRUE/DUNGEON/LowerDetail/LowerDetail_%d.png",
		L"Dungeon", L"Detail", 17);
	FAILED_CHECK_MSG_RETURN(hr, L"LowerDetail Texture Load Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
		L"../TEXTRUE/DUNGEON/Breakable/Breakable_%d.png",
		L"Dungeon", L"Breakable", 6);
	FAILED_CHECK_MSG_RETURN(hr, L"Breakable Texture Load Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
		L"../TEXTRUE/DUNGEON/Wall/Wall_%d.png",
		L"Dungeon", L"Wall", 1);
	FAILED_CHECK_MSG_RETURN(hr, L"Dungeon_Wall Texture Load Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
		L"../TEXTRUE/DUNGEON/Door/Door_%d.png",
		L"Dungeon", L"Door", 11);
	FAILED_CHECK_MSG_RETURN(hr, L"Dungeon_Door Texture Load Failed", E_FAIL);
	//
	hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
		L"../TEXTRUE/MONSTER/KNIGHT/ATTACK/DOWN/ATTACK_DOWN_%d.png",
		L"KNIGHT", L"ATTACK_DOWN", 13);
	FAILED_CHECK_MSG_RETURN(hr, L"KNIGHT ATTACK_DOWN Texture Load Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
		L"../TEXTRUE/MONSTER/KNIGHT/ATTACK/UP/ATTACK_UP_%d.png",
		L"KNIGHT", L"ATTACK_UP", 13);
	FAILED_CHECK_MSG_RETURN(hr, L"KNIGHT ATTACK_UP Texture Load Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
		L"../TEXTRUE/MONSTER/KNIGHT/ATTACK/LEFT/ATTACK_LEFT_%d.png",
		L"KNIGHT", L"ATTACK_LEFT", 13);
	FAILED_CHECK_MSG_RETURN(hr, L"KNIGHT ATTACK_LEFT Texture Load Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
		L"../TEXTRUE/MONSTER/KNIGHT/ATTACK/RIGHT/ATTACK_RIGHT_%d.png",
		L"KNIGHT", L"ATTACK_RIGHT", 13);
	FAILED_CHECK_MSG_RETURN(hr, L"KNIGHT ATTACK_RIGHT Texture Load Failed", E_FAIL);
	//
	hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
		L"../TEXTRUE/MONSTER/KNIGHT/IDLE/DOWN/IDLE_DOWN_%d.png",
		L"KNIGHT", L"IDLE_DOWN", 8);
	FAILED_CHECK_MSG_RETURN(hr, L"KNIGHT IDLE_DOWN Texture Load Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
		L"../TEXTRUE/MONSTER/KNIGHT/IDLE/UP/IDLE_UP_%d.png",
		L"KNIGHT", L"IDLE_UP", 8);
	FAILED_CHECK_MSG_RETURN(hr, L"KNIGHT IDLE_UP Texture Load Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
		L"../TEXTRUE/MONSTER/KNIGHT/IDLE/LEFT/IDLE_LEFT_%d.png",
		L"KNIGHT", L"IDLE_LEFT", 8);
	FAILED_CHECK_MSG_RETURN(hr, L"KNIGHT IDLE_LEFT Texture Load Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
		L"../TEXTRUE/MONSTER/KNIGHT/IDLE/RIGHT/IDLE_RIGHT_%d.png",
		L"KNIGHT", L"IDLE_RIGHT", 8);
	FAILED_CHECK_MSG_RETURN(hr, L"KNIGHT IDLE_RIGHT Texture Load Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
		L"../TEXTRUE/MONSTER/TURRET/ATTACK/UP/ATTACK_UP_%d.png",
		L"TURRET", L"ATTACK_UP", 11);
	FAILED_CHECK_MSG_RETURN(hr, L"TURRET ATTACK_UP Texture Load Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
		L"../TEXTRUE/MONSTER/TURRET/ATTACK/DOWN/ATTACK_DOWN_%d.png",
		L"TURRET", L"ATTACK_DOWN", 11);
	FAILED_CHECK_MSG_RETURN(hr, L"TURRET ATTACK_DOWN Texture Load Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
		L"../TEXTRUE/MONSTER/TURRET/ATTACK/LEFT/ATTACK_LEFT_%d.png",
		L"TURRET", L"ATTACK_LEFT", 11);
	FAILED_CHECK_MSG_RETURN(hr, L"TURRET ATTACK_LEFT Texture Load Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
		L"../TEXTRUE/MONSTER/TURRET/ATTACK/RIGHT/ATTACK_RIGHT_%d.png",
		L"TURRET", L"ATTACK_RIGHT", 11);
	FAILED_CHECK_MSG_RETURN(hr, L"TURRET ATTACK_RIGHT Texture Load Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
		L"../TEXTRUE/MONSTER/TURRET/WALK/UP/WALK_UP_%d.png",
		L"TURRET", L"WALK_UP", 6);
	FAILED_CHECK_MSG_RETURN(hr, L"TURRET WALK_UP Texture Load Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
		L"../TEXTRUE/MONSTER/TURRET/WALK/DOWN/WALK_DOWN_%d.png",
		L"TURRET", L"WALK_DOWN", 6);
	FAILED_CHECK_MSG_RETURN(hr, L"TURRET WALK_DOWN Texture Load Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
		L"../TEXTRUE/MONSTER/TURRET/WALK/LEFT/WALK_LEFT_%d.png",
		L"TURRET", L"WALK_LEFT", 6);
	FAILED_CHECK_MSG_RETURN(hr, L"TURRET WALK_LEFT Texture Load Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
		L"../TEXTRUE/MONSTER/TURRET/WALK/RIGHT/WALK_RIGHT_%d.png",
		L"TURRET", L"WALK_RIGHT", 6);
	FAILED_CHECK_MSG_RETURN(hr, L"TURRET WALK_RIGHT Texture Load Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
		L"../TEXTRUE/MONSTER/TURRET/BULLET/TURRET_BULLET_%d.png",
		L"TURRET", L"BULLET", 6);
	FAILED_CHECK_MSG_RETURN(hr, L"TURRET BULLET Texture Load Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
		L"../TEXTRUE/MONSTER/TURRET/BULLET/Collision/BULLET_COLLSION_%d.png",
		L"TURRET", L"BULLET_COLLSION", 5);
	FAILED_CHECK_MSG_RETURN(hr, L"TURRET BULLET_COLLSION Texture Load Failed", E_FAIL);

	

	srand(time(nullptr));

	int Count = 0;

	while (true)
	{
		m_iMap[4][2] = 1;
		Count = 0;
		for (int i = 4; i >= 0; --i)
		{
			for (int j = 2; j < 5; ++j)
			{
				if (1 == m_iMap[i][j])
				{
					if (1 != m_iMap[i][j - 1] && (j - 1 >= 0))
						m_iMap[i][j - 1] = rand() % 2;
					if (1 != m_iMap[i][j + 1] && (j + 1 < 5))
						m_iMap[i][j + 1] = rand() % 2;
					if (1 != m_iMap[i - 1][j] && (i - 1 >= 0))
						m_iMap[i - 1][j] = rand() % 2;
				}
			}
			for (int j = 2; j >= 0; --j)
			{
				if (1 == m_iMap[i][j])
				{
					if (1 != m_iMap[i][j - 1] && (j - 1 >= 0))
						m_iMap[i][j - 1] = rand() % 2;
					if (1 != m_iMap[i][j + 1] && (j + 1 < 5))
						m_iMap[i][j + 1] = rand() % 2;
					if (1 != m_iMap[i - 1][j] && (i - 1 >= 0))
						m_iMap[i - 1][j] = rand() % 2;
				}
			}
		}

		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				if (1 == m_iMap[i][j])
					++Count;
			}
		}

		if (Count > 3 && Count < 6)
			break;

		ZeroMemory(m_iMap, sizeof(m_iMap));
	}

	
	
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if(1 == m_iMap[i][j])
				m_pObjectMgr->LoadObject(L"../Data/Map_0.dat",D3DXVECTOR3(j * WINCX, i * WINCY, 0.f));
		}
	}

	CDoor* temp = nullptr;
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (1 == m_iMap[i][j])
			{
				if (1 == m_iMap[i][j - 1] && (j - 1 >= 0))	//LEFT
				{
					temp = CDoor::Create(D3DXVECTOR3(j * WINCX + 64 , i * WINCY + WINCY * 0.5f, 0.f));
					temp->SetAngle(270.f);
					m_pObjectMgr->AddObject(OBJECT_DOOR, temp);
				}
				if (1 == m_iMap[i][j + 1] && (j + 1 < 5))	//RIGHT
				{
					temp = CDoor::Create(D3DXVECTOR3(j * WINCX + WINCX - 64, i * WINCY + WINCY * 0.5f, 0.f));
					temp->SetAngle(90.f);
					m_pObjectMgr->AddObject(OBJECT_DOOR, temp);
				}
				if (1 == m_iMap[i - 1][j] && (i - 1 >= 0))	//UP
				{
					temp = CDoor::Create(D3DXVECTOR3(j * WINCX + WINCX * 0.5f, i * WINCY + 32, 0.f));
					temp->SetAngle(0.f);
					m_pObjectMgr->AddObject(OBJECT_DOOR, temp);
				}
				if (1 == m_iMap[i + 1][j] && (i + 1 < 5))	//DWON
				{
					temp = CDoor::Create(D3DXVECTOR3(j * WINCX + WINCX * 0.5f, i * WINCY + WINCY - 32, 0.f));
					temp->SetAngle(180.f);
					m_pObjectMgr->AddObject(OBJECT_DOOR, temp);
				}
			}
		}
	}

	// Player Object
	hr = m_pObjectMgr->AddObject(OBJECT_PLAYER, CPlayer::Create());
	FAILED_CHECK_MSG_RETURN(hr, L"Player Create Failed", E_FAIL);

	m_pObjectMgr->GetList(OBJECT_PLAYER).front()->SetPos(D3DXVECTOR3(2 * WINCX + WINCX * 0.5f, 4 * WINCY + WINCY * 0.5f, 0.f));
	CScrollMgr::MoveScrollPos(D3DXVECTOR3(2 * WINCX , 4 * WINCY , 0.f));
	m_pTerrain = dynamic_cast<CTerrain*>(m_pObjectMgr->GetMap());


	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (1 == m_iMap[i][j])
			{
				m_pObjectMgr->AddObject(OBJECT_MONSTER, CMonster::Create(D3DXVECTOR3(j * WINCX + WINCX * 0.75f, i * WINCY + WINCY * 0.25f, 0.f)));
				m_pObjectMgr->AddObject(OBJECT_MONSTER, CMonster2::Create(D3DXVECTOR3(j * WINCX + WINCX * 0.25f, i * WINCY + WINCY * 0.75f, 0.f)));
			}
		}
	}

	//m_pObjectMgr->AddObject(OBJECT_MONSTER, CMonster::Create(D3DXVECTOR3(2 * WINCX + WINCX * 0.75f, 4 * WINCY + WINCY * 0.25f, 0.f)));
	//m_pObjectMgr->AddObject(OBJECT_MONSTER, CMonster2::Create(D3DXVECTOR3(2 * WINCX + WINCX * 0.25f, 4 * WINCY + WINCY * 0.75f, 0.f)));

	CSoundMgr::GetInstance()->PlayBGM(L"BOSS_A_BGM.wav");

	return S_OK;
}

void CStage::Release()
{

	for_each(m_pObjectMgr->GetList(OBJECT_BACK).begin(), m_pObjectMgr->GetList(OBJECT_BACK).end(), SafeDelete<CGameObject*>);
	m_pObjectMgr->GetList(OBJECT_BACK).clear();

	for_each(m_pObjectMgr->GetList(OBJECT_TERRAIN).begin(), m_pObjectMgr->GetList(OBJECT_TERRAIN).end(), SafeDelete<CGameObject*>);
	m_pObjectMgr->GetList(OBJECT_TERRAIN).clear();

	for_each(m_pObjectMgr->GetList(OBJECT_MONSTER).begin(), m_pObjectMgr->GetList(OBJECT_MONSTER).end(), SafeDelete<CGameObject*>);
	m_pObjectMgr->GetList(OBJECT_MONSTER).clear();

	for_each(m_pObjectMgr->GetList(OBJECT_DETAIL).begin(), m_pObjectMgr->GetList(OBJECT_DETAIL).end(), SafeDelete<CGameObject*>);
	m_pObjectMgr->GetList(OBJECT_DETAIL).clear();

	for_each(m_pObjectMgr->GetList(OBJECT_CHEST).begin(), m_pObjectMgr->GetList(OBJECT_CHEST).end(), SafeDelete<CGameObject*>);
	m_pObjectMgr->GetList(OBJECT_CHEST).clear();

	for_each(m_pObjectMgr->GetList(OBJECT_DOOR).begin(), m_pObjectMgr->GetList(OBJECT_DOOR).end(), SafeDelete<CGameObject*>);
	m_pObjectMgr->GetList(OBJECT_DOOR).clear();

	m_pObjectMgr->GetRenderList(LAYER_BACK).clear();
	m_pObjectMgr->GetRenderList(LAYER_TERRAIN).clear();
	m_pObjectMgr->GetRenderList(LAYER_OBJECT).clear();
	m_pObjectMgr->GetRenderList(LAYER_EFFECT).clear();
	m_pObjectMgr->GetRenderList(LAYER_UI).clear();

	CSoundMgr::GetInstance()->StopSound(CSoundMgr::BGM);

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

void CStage::OpenCloseDoor()
{
	

	size_t size = m_pTerrain->GetVecTile().size();

	RECT rc = {};
	POINT pt = {0,0};
	POINT pt2 = {0,0};
	float Angle = 0.f;
	rc = { m_pTerrain->GetVecTile()[0]->tRect.left, m_pTerrain->GetVecTile()[0]->tRect.top,
		m_pTerrain->GetVecTile()[size - 1]->tRect.right, m_pTerrain->GetVecTile()[size - 1]->tRect.bottom };
	
	if (m_pObjectMgr->GetList(OBJECT_MONSTER).empty())
	{
		return;
	}
	auto iter_begin = m_pObjectMgr->GetList(OBJECT_MONSTER).begin();
	auto iter_end = m_pObjectMgr->GetList(OBJECT_MONSTER).end();
	int iCount = 0;
	for (; iter_begin != iter_end; ++iter_begin)
	{
		pt = { LONG((*iter_begin)->GetPInfo().vPos.x),LONG((*iter_begin)->GetPInfo().vPos.y) };

		auto iter_begin2 = m_pObjectMgr->GetList(OBJECT_DOOR).begin();
		auto iter_end2 = m_pObjectMgr->GetList(OBJECT_DOOR).end();
		
		for (; iter_begin2 != iter_end2; ++iter_begin2)
		{
			pt2 = { LONG((*iter_begin2)->GetInfo().vPos.x),LONG((*iter_begin2)->GetInfo().vPos.y) };
			
			if (PtInRect(&rc, pt) && PtInRect(&rc, pt2))
			{
				iCount++;
			}
		}
	}

	auto iter_begin2 = m_pObjectMgr->GetList(OBJECT_DOOR).begin();
	auto iter_end2 = m_pObjectMgr->GetList(OBJECT_DOOR).end();

	for (; iter_begin2 != iter_end2; ++iter_begin2)
	{
		pt2 = { LONG((*iter_begin2)->GetInfo().vPos.x),LONG((*iter_begin2)->GetInfo().vPos.y) };

		if (PtInRect(&rc, pt2))
		{
			if (iCount > 0)
			{
				m_pTerrain->TileChange((*iter_begin2)->GetInfo().vPos, 0, 0);
				dynamic_cast<CDoor*>((*iter_begin2))->SetBool(true);
			}
			else
			{
				Angle = dynamic_cast<CDoor*>((*iter_begin2))->GetAngle();
				dynamic_cast<CDoor*>((*iter_begin2))->SetBool(false);
				m_pTerrain->TileChange((*iter_begin2)->GetInfo().vPos, 3, (Angle / 90 + 3));
			}
		}
	}
	
}
