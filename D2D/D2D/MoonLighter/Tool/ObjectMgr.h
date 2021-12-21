#pragma once

class CGameObject;
class CObjectMgr
{
	DECLARE_SINGLETON(CObjectMgr)

private:
	CObjectMgr();
	~CObjectMgr();

public:
	HRESULT AddObject(OBJECT_TYPE eType, CGameObject* pObject);
	int Update();
	void LateUpdate();
	void Render();

public:
	void SetTerrainRender(bool bRedner);

public:
	CGameObject* GetTarget(OBJECT_TYPE eType , const D3DXVECTOR3& vPos);
	list<CGameObject*>& GetList(OBJECT_TYPE eType);
	void SaveObject(const TCHAR* pFilePath);
	void LoadObject(const TCHAR* pFilePath);

private:
	void Release();

private:
	list<CGameObject*>	m_ObjectList[OBJECT_END];
	bool				m_bTerrainRender;
};

