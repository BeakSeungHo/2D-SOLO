#include "stdafx.h"
#include "ObjectMgr.h"
#include "Terrain.h"
#include "Detail.h"
#include "Breakable.h"
#include "HealingPool.h"
#include "Chest.h"
#include "Back.h"
#include "Wall.h"
#include "MainFrm.h"
#include "ToolView.h"
#include "GameObject.h"

IMPLEMENT_SINGLETON(CObjectMgr)

CObjectMgr::CObjectMgr() : m_bTerrainRender(false)
{
}


CObjectMgr::~CObjectMgr()
{
	Release();
}

HRESULT CObjectMgr::AddObject(OBJECT_TYPE eType, CGameObject* pObject)
{
	NULL_CHECK_RETURN(pObject, E_FAIL);
	m_ObjectList[eType].push_back(pObject);

	return S_OK;
}

int CObjectMgr::Update()
{
	list<CGameObject*>::iterator iter_begin, iter_end;

	for(int i = 0; i < OBJECT_END; ++i)
	{
		iter_begin = m_ObjectList[i].begin();
		iter_end = m_ObjectList[i].end();

		for (; iter_begin != iter_end; )
		{
			int iEvent = (*iter_begin)->Update();

			if (DEAD_OBJ == iEvent)
			{
				SafeDelete(*iter_begin);
				iter_begin = m_ObjectList[i].erase(iter_begin);
			}
			else
				++iter_begin;
		}
	}	

	return NO_EVENT;
}

void CObjectMgr::LateUpdate()
{
	for (int i = 0; i < OBJECT_END; ++i)
	{
		for (auto pObject : m_ObjectList[i])
			pObject->LateUpdate();
	}	
}

void CObjectMgr::Render()
{
	for (int i = 0; i < OBJECT_END; ++i)
	{
		if(m_bTerrainRender && OBJECT_TERRAIN == i)
			continue;

		for (auto pObject : m_ObjectList[i])
			pObject->Render();
	}
}

void CObjectMgr::SetTerrainRender(bool bRedner)
{
	m_bTerrainRender ^= bRedner;
}

CGameObject * CObjectMgr::GetTarget(OBJECT_TYPE eType,const D3DXVECTOR3& vPos)
{
	for (auto pObject : m_ObjectList[eType])
		if (pObject->PickTarget(vPos))
			return pObject;
	
	return nullptr;
}

list<CGameObject*>& CObjectMgr::GetList(OBJECT_TYPE eType)
{
	return m_ObjectList[eType];
}

void CObjectMgr::SaveObject(const TCHAR * pFilePath)
{
	HANDLE hFile = ::CreateFile(pFilePath, GENERIC_WRITE, 0, nullptr,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
		return;

	DWORD dwBytes = 0;
	DWORD size = 0;

	for (int i = OBJECT_BACK; i <= OBJECT_TERRAIN; ++i)
	{
		if (OBJECT_DOOR == i)
			continue;
		if (OBJECT_TERRAIN == i)
		{
			for (auto pObject : m_ObjectList[i])
			{
				size = dynamic_cast<CTerrain*>(pObject)->GetVecTile().size();
				WriteFile(hFile, &size, sizeof(DWORD), &dwBytes, nullptr);
				for (int j = 0; j < dynamic_cast<CTerrain*>(pObject)->GetVecTile().size(); ++j)
				{
					WriteFile(hFile, dynamic_cast<CTerrain*>(pObject)->GetVecTile()[j], sizeof(TILE_INFO), &dwBytes, nullptr);
				}
			}
			continue;
		}
		
		size = m_ObjectList[i].size();
		WriteFile(hFile, &size, sizeof(DWORD), &dwBytes, nullptr);
		
		for(auto pObject : m_ObjectList[i])
			WriteFile(hFile, &pObject->GetInfo(), sizeof(TILE_INFO), &dwBytes, nullptr);
	}
	CloseHandle(hFile);
}

void CObjectMgr::LoadObject(const TCHAR * pFilePath)
{
	HANDLE hFile = ::CreateFile(pFilePath, GENERIC_READ, 0, nullptr,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
		return;

	for (int i = OBJECT_BACK; i <= OBJECT_WALL; ++i)
	{
		if(!m_ObjectList[i].empty())
		{
			for_each(m_ObjectList[i].begin(), m_ObjectList[i].end(), SafeDelete<CGameObject*>);
			m_ObjectList[i].clear();
		}
	}

	if (!dynamic_cast<CTerrain*>(m_ObjectList[OBJECT_TERRAIN].front())->GetVecTile().empty())
	{
		for_each(dynamic_cast<CTerrain*>(m_ObjectList[OBJECT_TERRAIN].front())->GetVecTile().begin(), 
		dynamic_cast<CTerrain*>(m_ObjectList[OBJECT_TERRAIN].front())->GetVecTile().end(), SafeDelete<TILE_INFO*>);
		dynamic_cast<CTerrain*>(m_ObjectList[OBJECT_TERRAIN].front())->GetVecTile().clear();
	}

	CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());

	CToolView* pToolView = dynamic_cast<CToolView*>(pFrameWnd->m_MainSplitter.GetPane(0, 1));

	DWORD dwBytes = 0;
	DWORD size = 0;
	TILE_INFO tTile = {};


	while (true)
	{
		for (int i = OBJECT_BACK; i <= OBJECT_TERRAIN; ++i)
		{
			if (OBJECT_DOOR == i)
				continue;
			ReadFile(hFile, &size, sizeof(DWORD), &dwBytes, nullptr);
			if (0 == dwBytes)
				break;
			for (int j = 0; j < size; ++j)
			{
				ReadFile(hFile, &tTile, sizeof(TILE_INFO), &dwBytes, nullptr);
				if (0 == dwBytes)
					break;
				if (OBJECT_BACK == i)
				{
					m_ObjectList[i].push_back(CBack::Create(tTile.vPos, tTile.byDrawID, pToolView));
				}
				else if (OBJECT_DETAIL == i)
				{
					m_ObjectList[i].push_back(CDetail::Create(tTile.vPos, tTile.byDrawID, pToolView));
				}
				else if (OBJECT_BREAKABLE == i)
				{
					m_ObjectList[i].push_back(CBreakable::Create(tTile.vPos, tTile.byDrawID, pToolView));
				}
				else if (OBJECT_WALL == i)
				{
					m_ObjectList[i].push_back(CWall::Create(tTile.vPos, tTile.byDrawID, pToolView));
				}
				else if (OBJECT_TERRAIN == i)
				{
					dynamic_cast<CTerrain*>(m_ObjectList[OBJECT_TERRAIN].front())->GetVecTile().push_back(new TILE_INFO(tTile));
				}
			}
		}
		if (0 == dwBytes)
			break;
		
	}

	CloseHandle(hFile);
}

void CObjectMgr::Release()
{
	for (int i = 0; i < OBJECT_END; ++i)
	{
		for_each(m_ObjectList[i].begin(), m_ObjectList[i].end(), SafeDelete<CGameObject*>);
		m_ObjectList[i].clear();
	}
}
