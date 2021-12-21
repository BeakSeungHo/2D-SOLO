#include "stdafx.h"
#include "MyButton.h"


CMyButton::CMyButton() :
	m_pKeyMgr(CKeyMgr::GetInstance())
{
}


CMyButton::~CMyButton()
{
}

int CMyButton::Update()
{
	CObjectMgr::GetInstance()->AddLayer(LAYER_UI, this);

	return NO_EVENT;
}

void CMyButton::LateUpdate()
{
}

void CMyButton::Render()
{
	D3DXMATRIX matTrans;

	if (m_bTarget)
	{
		const TEX_INFO* pTexInfo = m_pTextureMgr->GetTexInfo(L"Choice_left");
		NULL_CHECK(pTexInfo);

		float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		D3DXMatrixTranslation(&matTrans, m_vPos.x - (20 * lstrlen(m_strText.c_str()) * 0.5) - fCenterX, m_vPos.y, m_vPos.z);

		m_pDeviceMgr->GetSprite()->SetTransform(&matTrans);
		m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
			nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		pTexInfo = m_pTextureMgr->GetTexInfo(L"Choice_Right");
		NULL_CHECK(pTexInfo);

		fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		D3DXMatrixTranslation(&matTrans, m_vPos.x + (20 * lstrlen(m_strText.c_str()) * 0.5) + fCenterX, m_vPos.y, m_vPos.z);

		m_pDeviceMgr->GetSprite()->SetTransform(&matTrans);
		m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
			nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	


	D3DXMatrixTranslation(&matTrans,m_vPos.x, m_vPos.y, m_vPos.z);

	RECT rect = {- (20 * lstrlen(m_strText.c_str()) * 0.5),	- 10,
				(20 * lstrlen(m_strText.c_str()) * 0.5), 10};
	
	m_pDeviceMgr->GetSprite()->SetTransform(&matTrans);

	m_pDeviceMgr->GetFont()->DrawText(
		m_pDeviceMgr->GetSprite(), /* 스프라이트 COM 객체 */
		m_strText.c_str(), /* 출력할 문자열 */
		lstrlen(m_strText.c_str()), /* 문자열 길이 */
		&rect, /* 사각형 영역 */
		DT_CENTER,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

HRESULT CMyButton::Initialize()
{
	m_vPos = {0.f,0.f,0.f};
	m_strText = L"";
	return S_OK;
}

void CMyButton::Release()
{
}

void CMyButton::SetINFO(wstring strText, D3DXVECTOR3 Pos, SCENE_TYPE eType)
{
	m_eScene = eType;
	m_strText = strText;
	m_vPos = Pos;
}

void CMyButton::SetTarget(bool bTarget)
{
	m_bTarget = bTarget;
}

bool CMyButton::GetTarget() const
{
	return m_bTarget;
}

SCENE_TYPE CMyButton::GetScene() const
{
	return m_eScene;
}


CMyButton * CMyButton::Create()
{
	CMyButton* pInstance = new CMyButton;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
