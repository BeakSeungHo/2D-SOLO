#include "stdafx.h"
#include "UI.h"
#include "Player.h"

CUI::CUI() :
	m_bIsBoss(false)
{
}


CUI::~CUI()
{
}

int CUI::Update()
{
	CObjectMgr::GetInstance()->AddLayer(LAYER_UI, this);

	return NO_EVENT;
}

void CUI::LateUpdate()
{
}

void CUI::Render()
{
	const TEX_INFO* pTexInfo = m_pTextureMgr->GetTexInfo(L"GAME_UI", L"HealthBar", 0);
	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	D3DXMATRIX matScale, matTrans;

	D3DXMatrixScaling(&matScale,
		1.f,
		1.f,
		0.f); // 다이렉트 크기행렬 함수
	D3DXMatrixTranslation(&matTrans,
		128,
		16,
		0.f); // 다이렉트 이동행렬 함수

	m_tPInfo.matWorld = matScale * matTrans;

	m_pDeviceMgr->GetSprite()->SetTransform(&m_tPInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	pTexInfo = m_pTextureMgr->GetTexInfo(L"GAME_UI", L"HealthBar", 1);
	NULL_CHECK(pTexInfo);

	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	int iHp = m_pObjectMgr->GetList(OBJECT_PLAYER).front()->GetOInfo().iHp;
	int iMaxHp = m_pObjectMgr->GetList(OBJECT_PLAYER).front()->GetOInfo().iMaxHp;

	int iCount = ((float)iHp / iMaxHp) * 18;

	for (int i = 0; i < iCount; ++i)
	{
		D3DXMatrixScaling(&matScale,
			1.f,
			1.f,
			0.f); // 다이렉트 크기행렬 함수
		D3DXMatrixTranslation(&matTrans,
			102 + (i * fCenterX),
			16,
			0.f); // 다이렉트 이동행렬 함수

		m_tPInfo.matWorld = matScale * matTrans;

		m_pDeviceMgr->GetSprite()->SetTransform(&m_tPInfo.matWorld);
		m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
			nullptr, D3DCOLOR_ARGB(255, 255, 0, 0));
	}

	D3DXMatrixScaling(&matScale,
		0.5f,
		0.5f,
		0.f); // 다이렉트 크기행렬 함수
	D3DXMatrixTranslation(&matTrans,
		125,
		24,
		0.f); // 다이렉트 이동행렬 함수

	m_tPInfo.matWorld = matScale * matTrans;

	m_strText = to_wstring(iHp);
	m_pDeviceMgr->GetSprite()->SetTransform(&m_tPInfo.matWorld);

	m_pDeviceMgr->GetFont()->DrawText(
		m_pDeviceMgr->GetSprite(), /* 스프라이트 COM 객체 */
		m_strText.c_str(), /* 출력할 문자열 */
		lstrlen(m_strText.c_str()), /* 문자열 길이 */
		nullptr, /* 사각형 영역 */
		DT_CENTER,
		D3DCOLOR_ARGB(255, 255, 255, 255));

	D3DXMatrixScaling(&matScale,
		0.5f,
		0.5f,
		0.f); // 다이렉트 크기행렬 함수
	D3DXMatrixTranslation(&matTrans,
		145,
		24,
		0.f); // 다이렉트 이동행렬 함수

	m_tPInfo.matWorld = matScale * matTrans;

	m_strText = L"/";
	m_pDeviceMgr->GetSprite()->SetTransform(&m_tPInfo.matWorld);

	m_pDeviceMgr->GetFont()->DrawText(
		m_pDeviceMgr->GetSprite(), /* 스프라이트 COM 객체 */
		m_strText.c_str(), /* 출력할 문자열 */
		lstrlen(m_strText.c_str()), /* 문자열 길이 */
		nullptr, /* 사각형 영역 */
		DT_CENTER,
		D3DCOLOR_ARGB(255, 255, 255, 255));

	D3DXMatrixScaling(&matScale,
		0.5f,
		0.5f,
		0.f); // 다이렉트 크기행렬 함수
	D3DXMatrixTranslation(&matTrans,
		150,
		24,
		0.f); // 다이렉트 이동행렬 함수

	m_tPInfo.matWorld = matScale * matTrans;

	m_strText = to_wstring(iMaxHp);
	m_pDeviceMgr->GetSprite()->SetTransform(&m_tPInfo.matWorld);

	m_pDeviceMgr->GetFont()->DrawText(
		m_pDeviceMgr->GetSprite(), /* 스프라이트 COM 객체 */
		m_strText.c_str(), /* 출력할 문자열 */
		lstrlen(m_strText.c_str()), /* 문자열 길이 */
		nullptr, /* 사각형 영역 */
		DT_CENTER,
		D3DCOLOR_ARGB(255, 255, 255, 255));

	pTexInfo = m_pTextureMgr->GetTexInfo(L"GAME_UI", L"HealthBar", 2);
	NULL_CHECK(pTexInfo);

	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	D3DXMatrixScaling(&matScale,
		1.f,
		1.f,
		0.f); // 다이렉트 크기행렬 함수
	D3DXMatrixTranslation(&matTrans,
		85,
		16,
		0.f); // 다이렉트 이동행렬 함수

	m_tPInfo.matWorld = matScale * matTrans;

	m_pDeviceMgr->GetSprite()->SetTransform(&m_tPInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	pTexInfo = m_pTextureMgr->GetTexInfo(L"GAME_UI", L"HealthBar", 3);
	NULL_CHECK(pTexInfo);

	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	D3DXMatrixScaling(&matScale,
		0.8f,
		0.8f,
		0.f); // 다이렉트 크기행렬 함수
	D3DXMatrixTranslation(&matTrans,
		85,
		16,
		0.f); // 다이렉트 이동행렬 함수

	m_tPInfo.matWorld = matScale * matTrans;


	m_pDeviceMgr->GetSprite()->SetTransform(&m_tPInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 0, 0));

	pTexInfo = m_pTextureMgr->GetTexInfo(L"GAME_UI", L"Button", 7);
	NULL_CHECK(pTexInfo);

	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	D3DXMatrixScaling(&matScale,
		1.f,
		1.f,
		0.f); // 다이렉트 크기행렬 함수
	D3DXMatrixTranslation(&matTrans,
		585,
		11,
		0.f); // 다이렉트 이동행렬 함수

	m_tPInfo.matWorld = matScale * matTrans;


	m_pDeviceMgr->GetSprite()->SetTransform(&m_tPInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	pTexInfo = m_pTextureMgr->GetTexInfo(L"GAME_UI", L"ITEM", 6);
	NULL_CHECK(pTexInfo);

	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	D3DXMatrixScaling(&matScale,
		0.6f,
		0.6f,
		0.f); // 다이렉트 크기행렬 함수
	D3DXMatrixTranslation(&matTrans,
		570,
		20,
		0.f); // 다이렉트 이동행렬 함수

	m_tPInfo.matWorld = matScale * matTrans;


	m_pDeviceMgr->GetSprite()->SetTransform(&m_tPInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	pTexInfo = m_pTextureMgr->GetTexInfo(L"GAME_UI", L"Button", 1);
	NULL_CHECK(pTexInfo);

	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	D3DXMatrixScaling(&matScale,
		1.f,
		1.f,
		0.f); // 다이렉트 크기행렬 함수
	D3DXMatrixTranslation(&matTrans,
		615,
		11,
		0.f); // 다이렉트 이동행렬 함수

	m_tPInfo.matWorld = matScale * matTrans;


	m_pDeviceMgr->GetSprite()->SetTransform(&m_tPInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	pTexInfo = m_pTextureMgr->GetTexInfo(L"ITEM", L"ITEM", 0);
	NULL_CHECK(pTexInfo);

	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	D3DXMatrixScaling(&matScale,
		1.f,
		1.f,
		0.f); // 다이렉트 크기행렬 함수
	D3DXMatrixTranslation(&matTrans,
		625,
		18,
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
		615,
		18,
		0.f); // 다이렉트 이동행렬 함수

	m_tPInfo.matWorld = matScale * matTrans;

	m_strText = to_wstring(dynamic_cast<CPlayer*>(m_pObjectMgr->GetList(OBJECT_PLAYER).front())->GetPotionCount());
	m_pDeviceMgr->GetSprite()->SetTransform(&m_tPInfo.matWorld);

	m_pDeviceMgr->GetFont()->DrawText(
		m_pDeviceMgr->GetSprite(), /* 스프라이트 COM 객체 */
		m_strText.c_str(), /* 출력할 문자열 */
		lstrlen(m_strText.c_str()), /* 문자열 길이 */
		nullptr, /* 사각형 영역 */
		DT_CENTER,
		D3DCOLOR_ARGB(255, 255, 255, 255));

	pTexInfo = m_pTextureMgr->GetTexInfo(L"GAME_UI", L"BaseCircle", 0);
	NULL_CHECK(pTexInfo);

	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	D3DXMatrixScaling(&matScale,
		1.f,
		1.f,
		0.f); // 다이렉트 크기행렬 함수
	D3DXMatrixTranslation(&matTrans,
		600,
		48,
		0.f); // 다이렉트 이동행렬 함수

	m_tPInfo.matWorld = matScale * matTrans;


	m_pDeviceMgr->GetSprite()->SetTransform(&m_tPInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	pTexInfo = m_pTextureMgr->GetTexInfo(L"GAME_UI", L"ITEM", 2);
	NULL_CHECK(pTexInfo);

	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f;


	m_pDeviceMgr->GetSprite()->SetTransform(&m_tPInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	pTexInfo = m_pTextureMgr->GetTexInfo(L"GAME_UI", L"Button", 3);
	NULL_CHECK(pTexInfo);

	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	D3DXMatrixScaling(&matScale,
		1.f,
		1.f,
		0.f); // 다이렉트 크기행렬 함수
	D3DXMatrixTranslation(&matTrans,
		600,
		70,
		0.f); // 다이렉트 이동행렬 함수

	m_tPInfo.matWorld = matScale * matTrans;


	m_pDeviceMgr->GetSprite()->SetTransform(&m_tPInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	pTexInfo = m_pTextureMgr->GetTexInfo(L"GAME_UI", L"Button", 4);
	NULL_CHECK(pTexInfo);

	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	D3DXMatrixScaling(&matScale,
		1.f,
		1.f,
		0.f); // 다이렉트 크기행렬 함수
	D3DXMatrixTranslation(&matTrans,
		580,
		48,
		0.f); // 다이렉트 이동행렬 함수

	m_tPInfo.matWorld = matScale * matTrans;


	m_pDeviceMgr->GetSprite()->SetTransform(&m_tPInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	pTexInfo = m_pTextureMgr->GetTexInfo(L"GAME_UI", L"BaseCircle", 0);
	NULL_CHECK(pTexInfo);

	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	D3DXMatrixScaling(&matScale,
		1.f,
		1.f,
		0.f); // 다이렉트 크기행렬 함수
	D3DXMatrixTranslation(&matTrans,
		600,
		105,
		0.f); // 다이렉트 이동행렬 함수

	m_tPInfo.matWorld = matScale * matTrans;

	m_pDeviceMgr->GetSprite()->SetTransform(&m_tPInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	pTexInfo = m_pTextureMgr->GetTexInfo(L"GAME_UI", L"ITEM", 0);
	NULL_CHECK(pTexInfo);

	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	m_pDeviceMgr->GetSprite()->SetTransform(&m_tPInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	pTexInfo = m_pTextureMgr->GetTexInfo(L"GAME_UI", L"Button", 2);
	NULL_CHECK(pTexInfo);

	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	D3DXMatrixScaling(&matScale,
		1.f,
		1.f,
		0.f); // 다이렉트 크기행렬 함수
	D3DXMatrixTranslation(&matTrans,
		580,
		105,
		0.f); // 다이렉트 이동행렬 함수

	m_tPInfo.matWorld = matScale * matTrans;

	m_pDeviceMgr->GetSprite()->SetTransform(&m_tPInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	if (m_bIsBoss)
	{
		D3DXMatrixScaling(&matScale,
			1.f,
			1.f,
			0.f); // 다이렉트 크기행렬 함수
		D3DXMatrixTranslation(&matTrans,
			WINCX * 0.5f - 30.f,
			WINCY - 80.f,
			0.f); // 다이렉트 이동행렬 함수

		m_tPInfo.matWorld = matScale * matTrans;

		m_strText = L"골렘 왕";
		m_pDeviceMgr->GetSprite()->SetTransform(&m_tPInfo.matWorld);

		m_pDeviceMgr->GetFont()->DrawText(
			m_pDeviceMgr->GetSprite(), /* 스프라이트 COM 객체 */
			m_strText.c_str(), /* 출력할 문자열 */
			lstrlen(m_strText.c_str()), /* 문자열 길이 */
			nullptr, /* 사각형 영역 */
			DT_CENTER,
			D3DCOLOR_ARGB(255, 255, 255, 255));

		pTexInfo = m_pTextureMgr->GetTexInfo(L"GAME_UI", L"HealthBar", 5);
		NULL_CHECK(pTexInfo);

		fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		matScale, matTrans;

		float iBossHp = m_pObjectMgr->GetList(OBJECT_MONSTER).front()->GetOInfo().iHp;
		int iBossMaxHp = m_pObjectMgr->GetList(OBJECT_MONSTER).front()->GetOInfo().iMaxHp;

		D3DXMatrixScaling(&matScale,
			(iBossHp / iBossMaxHp),
			1.f,
			0.f); // 다이렉트 크기행렬 함수
		D3DXMatrixTranslation(&matTrans,
			WINCX * 0.5f - (1 - (iBossHp / iBossMaxHp)) * 215,
			WINCY -  50.f,
			0.f); // 다이렉트 이동행렬 함수

		m_tPInfo.matWorld = matScale * matTrans;

		m_pDeviceMgr->GetSprite()->SetTransform(&m_tPInfo.matWorld);
		m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
			nullptr, D3DCOLOR_ARGB(255, 255, 0, 0));

		pTexInfo = m_pTextureMgr->GetTexInfo(L"GAME_UI", L"HealthBar", 4);
		NULL_CHECK(pTexInfo);

		fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		D3DXMatrixScaling(&matScale,
			1.f,
			1.f,
			0.f); // 다이렉트 크기행렬 함수
		D3DXMatrixTranslation(&matTrans,
			WINCX * 0.5f,
			WINCY - 50.f,
			0.f); // 다이렉트 이동행렬 함수

		m_tPInfo.matWorld = matScale * matTrans;

		m_pDeviceMgr->GetSprite()->SetTransform(&m_tPInfo.matWorld);
		m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
			nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	
}

HRESULT CUI::Initialize()
{
	LPDIRECT3DDEVICE9 pGraphicDev = m_pDeviceMgr->GetDevice();
	NULL_CHECK_MSG_RETURN(pGraphicDev, L"pGraphicDev is null", E_FAIL);

	HRESULT hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../TEXTRUE/GAME_EFFECT/GAME_UI/HEAL_BAR/HealthBar_%d.png",
		L"GAME_UI",
		L"HealthBar",
		6);
	FAILED_CHECK_MSG_RETURN(hr, L"GAME_UI HealthBar LoadTexture Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../TEXTRUE/GAME_EFFECT/GAME_UI/BASECIRCLE/BaseCircle_%d.png",
		L"GAME_UI",
		L"BaseCircle",
		1);
	FAILED_CHECK_MSG_RETURN(hr, L"GAME_UI BaseCircle LoadTexture Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../TEXTRUE/GAME_EFFECT/GAME_UI/ITEM/ITEM_%d.png",
		L"GAME_UI",
		L"ITEM",
		7);
	FAILED_CHECK_MSG_RETURN(hr, L"GAME_UI BaseCircle LoadTexture Failed", E_FAIL);
	
	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../TEXTRUE/GAME_EFFECT/GAME_UI/KEY/Button_%d.png",
		L"GAME_UI",
		L"Button",
		8);
	FAILED_CHECK_MSG_RETURN(hr, L"GAME_UI Button LoadTexture Failed", E_FAIL);
	return S_OK;
}

void CUI::Release()
{
}

CUI * CUI::Create()
{
	CUI* pInstance = new CUI;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CUI::SetBoss(bool bIsBoss)
{
	m_bIsBoss = bIsBoss;
}
