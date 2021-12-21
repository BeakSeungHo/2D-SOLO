#include "stdafx.h"
#include "BossStage.h"
#include "Boss.h"

CBossStage::CBossStage() :
	m_bCutSceen(false)
{
}


CBossStage::~CBossStage()
{
	Release();
}

int CBossStage::Update()
{
	m_pObjectMgr->Update();

	if (m_bCutSceen == false && CScrollMgr::GetScrollPos().y < WINCY)
	{
		D3DXVECTOR3 temp = D3DXVECTOR3(WINCX * 0.4f, WINCY * 0.4f, 0.f) - CScrollMgr::GetScrollPos();
		D3DXVec3Normalize(&temp, &temp);
		CScrollMgr::MoveScrollPos(temp);
		dynamic_cast<CBoss*>(m_pObjectMgr->GetList(OBJECT_MONSTER).front())->SetState(WAKEUP, L"WAKEUP");
		if (dynamic_cast<CBoss*>(m_pObjectMgr->GetList(OBJECT_MONSTER).front())->GetFrame().fCurFrame >= 30)
		{
			m_bCutSceen = true;
		}
	}
	else
	{
		CScrollMgr::SetScrollPos(m_pObjectMgr->GetList(OBJECT_PLAYER).front()->GetPInfo().vPos - D3DXVECTOR3(WINCX * 0.5f, WINCY * 0.5f, 0.f));
	}
	
	ScrollOffSet();
	return NO_EVENT;
}

void CBossStage::LateUpdate()
{
	m_pObjectMgr->LateUpdate();
}

void CBossStage::Render()
{
	m_pObjectMgr->Render();
}

HRESULT CBossStage::Initialize()
{
	m_pObjectMgr->LoadObject(L"../Data/Boss_Map.dat", D3DXVECTOR3(0.f, 0.f, 0.f));	
	m_pObjectMgr->AddObject(OBJECT_MONSTER,CBoss::Create());
	m_pObjectMgr->GetList(OBJECT_PLAYER).front()->SetPos(D3DXVECTOR3(WINCX * 0.9f ,WINCY * 2.f,0.f));
	CScrollMgr::SetScrollPos(m_pObjectMgr->GetList(OBJECT_PLAYER).front()->GetPInfo().vPos);

	CSoundMgr::GetInstance()->PlayBGM(L"BOSS_A_BGM.wav");
	return S_OK;
}

void CBossStage::Release()
{
	CSoundMgr::GetInstance()->StopSound(CSoundMgr::BGM);
}

void CBossStage::ScrollOffSet()
{
	if(CScrollMgr::GetScrollPos().x < 0)
		CScrollMgr::SetScrollPos(D3DXVECTOR3(0,CScrollMgr::GetScrollPos().y,0));
	if (CScrollMgr::GetScrollPos().x > 1152 - WINCX)
		CScrollMgr::SetScrollPos(D3DXVECTOR3(1152 - WINCX, CScrollMgr::GetScrollPos().y, 0));
	if (CScrollMgr::GetScrollPos().y < 0)
		CScrollMgr::SetScrollPos(D3DXVECTOR3(CScrollMgr::GetScrollPos().x, 0, 0));
	if (CScrollMgr::GetScrollPos().y > 779 - WINCY)
		CScrollMgr::SetScrollPos(D3DXVECTOR3(CScrollMgr::GetScrollPos().x, 779 - WINCY, 0));

}

CBossStage * CBossStage::Create()
{
	CBossStage* pInstance = new CBossStage;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
