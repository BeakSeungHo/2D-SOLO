#include "stdafx.h"
#include "Inventory.h"
#include "Player.h"

CInventory::CInventory() :
	m_bDelete(false),
	m_pKeyMgr(CKeyMgr::GetInstance()),
	m_iCount(0),
	m_iPreCount(-1),
	m_Temp(nullptr)
{
	ZeroMemory(&m_tPInfo,sizeof(INFO));
	ZeroMemory(&m_tITinfo,sizeof(ITEM_INFO));
}


CInventory::~CInventory()
{
}

int CInventory::Update()
{
	KeyInput();
	if(m_bDelete)
		return DEAD_OBJ;
	CObjectMgr::GetInstance()->AddLayer(LAYER_UI, this);
	return NO_EVENT;
}

void CInventory::LateUpdate()
{
	D3DXMATRIX matScale, matTrans;

	D3DXMatrixScaling(&matScale,
		m_tPInfo.vSize.x,
		m_tPInfo.vSize.y,
		0.f); // 다이렉트 크기행렬 함수
	D3DXMatrixTranslation(&matTrans,
		m_tPInfo.vPos.x,
		m_tPInfo.vPos.y,
		0.f); // 다이렉트 이동행렬 함수

	m_tPInfo.matWorld = matScale * matTrans;
}

void CInventory::Render()
{
	const TEX_INFO* pTexInfo = m_pTextureMgr->GetTexInfo(L"INVEN", L"INVEN", 0);
	NULL_CHECK(pTexInfo);

	D3DXMATRIX matScale, matTrans;

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	m_pDeviceMgr->GetSprite()->SetTransform(&m_tPInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	for (int i = 0; i < m_vecInven.size(); ++i)
	{
		if(m_vecInven[i] == NULL)
			continue;
		pTexInfo = m_pTextureMgr->GetTexInfo(L"ITEM", L"ITEM", m_vecInven[i]->GetITinfo().byDrawID );
		NULL_CHECK(pTexInfo);

		fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		D3DXMatrixScaling(&matScale,
			m_tPInfo.vSize.x,
			m_tPInfo.vSize.y,
			0.f); // 다이렉트 크기행렬 함수
		D3DXMatrixTranslation(&matTrans,
			122 + ((i % 5) * 36),
			32 * 3 + ((i/5) * 36),
			0.f); // 다이렉트 이동행렬 함수

		m_tPInfo.matWorld = matScale * matTrans;

		m_pDeviceMgr->GetSprite()->SetTransform(&m_tPInfo.matWorld);
		m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
			nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		D3DXMatrixScaling(&matScale,
			0.5f,
			0.5f,
			0.f); // 다이렉트 크기행렬 함수
		D3DXMatrixTranslation(&matTrans,
			122 + ((i % 5) * 36) + 5,
			32 * 3 + ((i / 5) * 36) + 5,
			0.f); // 다이렉트 이동행렬 함수

		m_tPInfo.matWorld = matScale * matTrans;

		m_strText = to_wstring(m_vecInven[i]->GetITinfo().iAmount + 1);
		m_pDeviceMgr->GetSprite()->SetTransform(&m_tPInfo.matWorld);

		m_pDeviceMgr->GetFont()->DrawText(
			m_pDeviceMgr->GetSprite(), /* 스프라이트 COM 객체 */
			m_strText.c_str(), /* 출력할 문자열 */
			lstrlen(m_strText.c_str()), /* 문자열 길이 */
			nullptr, /* 사각형 영역 */
			DT_CENTER,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	pTexInfo = m_pTextureMgr->GetTexInfo(L"INVEN", L"INVEN", 1);
	NULL_CHECK(pTexInfo);

	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	D3DXMatrixScaling(&matScale,
		m_tPInfo.vSize.x,
		m_tPInfo.vSize.y,
		0.f); // 다이렉트 크기행렬 함수
	D3DXMatrixTranslation(&matTrans,
		122 + (m_iCount%5) * 36,
		98 + (m_iCount/5) * 38,
		0.f); // 다이렉트 이동행렬 함수

	m_tPInfo.matWorld = matScale * matTrans;


	m_pDeviceMgr->GetSprite()->SetTransform(&m_tPInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	if (m_Temp)
	{
		pTexInfo = m_pTextureMgr->GetTexInfo(L"INVEN", L"INVEN", 2);
		NULL_CHECK(pTexInfo);

		fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		D3DXMatrixScaling(&matScale,
			m_tPInfo.vSize.x,
			m_tPInfo.vSize.y,
			0.f); // 다이렉트 크기행렬 함수
		D3DXMatrixTranslation(&matTrans,
			122 + (m_iCount % 5) * 36,
			98 + (m_iCount / 5) * 38 - 38,
			0.f); // 다이렉트 이동행렬 함수

		m_tPInfo.matWorld = matScale * matTrans;


		m_pDeviceMgr->GetSprite()->SetTransform(&m_tPInfo.matWorld);
		m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
			nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		pTexInfo = m_pTextureMgr->GetTexInfo(L"ITEM", L"ITEM",  m_Temp->GetITinfo().byDrawID);
		NULL_CHECK(pTexInfo);

		fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		m_pDeviceMgr->GetSprite()->SetTransform(&m_tPInfo.matWorld);
		m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
			nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		D3DXMatrixScaling(&matScale,
			0.5f,
			0.5f,
			0.f); // 다이렉트 크기행렬 함수
		D3DXMatrixTranslation(&matTrans,
			122 + (m_iCount % 5) * 36,
			98 + (m_iCount / 5) * 38 - 38,
			0.f); // 다이렉트 이동행렬 함수

		m_tPInfo.matWorld = matScale * matTrans;

		m_strText = to_wstring(m_Temp->GetITinfo().iAmount + 1);
		m_pDeviceMgr->GetSprite()->SetTransform(&m_tPInfo.matWorld);

		m_pDeviceMgr->GetFont()->DrawText(
			m_pDeviceMgr->GetSprite(), /* 스프라이트 COM 객체 */
			m_strText.c_str(), /* 출력할 문자열 */
			lstrlen(m_strText.c_str()), /* 문자열 길이 */
			nullptr, /* 사각형 영역 */
			DT_CENTER,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

HRESULT CInventory::Initialize()
{
	m_vecInven = dynamic_cast<CPlayer*>(m_pObjectMgr->GetList(OBJECT_PLAYER).front())->GetItemVec();

	m_tPInfo.vSize = {1.f,1.f,0.f};
	m_tPInfo.vPos = {WINCX * 0.5f, WINCY * 0.5f, 0.f};

	return S_OK;
}

void CInventory::Release()
{
}

CInventory * CInventory::Create()
{
	CInventory* pInstance = new CInventory;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CInventory::KeyInput()
{
	if (m_pKeyMgr->KeyDown(KEY_A))
	{
		--m_iCount;
		if(m_iCount < 0)
			m_iCount = 0;
	}
	else if (m_pKeyMgr->KeyDown(KEY_D))
	{
		m_iCount++;
		if(m_iCount > 19)
			m_iCount = 19;
	}
	else if (m_pKeyMgr->KeyDown(KEY_W))
	{
		m_iCount -= 5;
		if(m_iCount < 0)
			m_iCount += 5;
	}
	else if (m_pKeyMgr->KeyDown(KEY_S))
	{
		m_iCount += 5;
		if (m_iCount > 19)
			m_iCount -= 5;
	}
	
	if (m_pKeyMgr->KeyDown(KEY_C))
	{
		if (nullptr == m_Temp && m_vecInven[m_iCount] != nullptr)
		{
			m_Temp = m_vecInven[m_iCount];
			m_vecInven[m_iCount] = nullptr;
			m_iPreCount = m_iCount;
		}
		else
		{
			if (m_vecInven[m_iCount] == nullptr)
			{
				m_vecInven[m_iCount] = m_Temp;
				m_Temp = nullptr;
				m_iPreCount = -1;
			}
			else if (m_vecInven[m_iCount] == m_Temp && m_iCount == m_iPreCount)
			{
				--m_vecInven[m_iCount]->GetITinfo().iAmount;
				if (m_vecInven[m_iCount]->GetITinfo().iAmount <= 0)
					m_vecInven[m_iCount] = nullptr;
				++m_Temp->GetITinfo().iAmount;
			}
			else
			{
				m_vecInven[m_iPreCount] = m_vecInven[m_iCount];
				m_vecInven[m_iCount] = m_Temp;
				m_iPreCount = -1;
				m_Temp = nullptr;
			}
		}	
	}
}

void CInventory::SetDelete()
{
	dynamic_cast<CPlayer*>(m_pObjectMgr->GetList(OBJECT_PLAYER).front())->GetItemVec() = m_vecInven;
	
	m_bDelete = true;
}
