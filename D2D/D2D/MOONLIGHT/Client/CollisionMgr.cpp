#include "stdafx.h"
#include "CollisionMgr.h"
#include "Player.h"
#include "Terrain.h"
#include "Bullet.h"
#include "GameObject.h"

CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::CollisionTile(OBJECT_LIST & srcList)
{
	RECT rc = {};

	if (srcList.empty())
		return;

	CTerrain* m_pTerrain = dynamic_cast<CTerrain*>(CObjectMgr::GetInstance()->GetMap());
	NULL_CHECK(m_pTerrain);

	for (int i = 0; i < m_pTerrain->GetVecTile().size(); ++i)
	{
		auto iter_begin = srcList.begin();
		auto iter_end = srcList.end();

		if (IntersectRect(&rc, &m_pTerrain->GetVecTile()[i]->tRect, &srcList.front()->GetPInfo().tRect) && 1 == m_pTerrain->GetVecTile()[i]->byOption)
		{
			float fMoveX = rc.left - rc.right;
			float fMoveY = rc.top - rc.bottom;

			float fX = srcList.front()->GetPInfo().vPos.x;
			float fY = srcList.front()->GetPInfo().vPos.y;

			if (fMoveX > fMoveY) // Y축으로 밀어냄
			{
				if (m_pTerrain->GetVecTile()[i]->tRect.top < srcList.front()->GetPInfo().tRect.top &&
					m_pTerrain->GetVecTile()[i]->tRect.bottom > srcList.front()->GetPInfo().tRect.top)
					srcList.front()->GetPInfo().vPos -= D3DXVECTOR3(0.f, -1.0f, 0.f) * srcList.front()->GetPInfo().fSpeed * CTimeMgr::GetInstance()->GetDelta();
				else if (m_pTerrain->GetVecTile()[i]->tRect.top < srcList.front()->GetPInfo().tRect.bottom &&
					m_pTerrain->GetVecTile()[i]->tRect.bottom > srcList.front()->GetPInfo().tRect.bottom)
					srcList.front()->GetPInfo().vPos -= D3DXVECTOR3(0.f, 1.0f, 0.f) * srcList.front()->GetPInfo().fSpeed * CTimeMgr::GetInstance()->GetDelta();
			}
			else // X축으로 밀어냄
			{
				if (m_pTerrain->GetVecTile()[i]->tRect.left < srcList.front()->GetPInfo().tRect.left &&
					m_pTerrain->GetVecTile()[i]->tRect.right > srcList.front()->GetPInfo().tRect.left)
					srcList.front()->GetPInfo().vPos -= D3DXVECTOR3(-1.f, 0.f, 0.f) * srcList.front()->GetPInfo().fSpeed * CTimeMgr::GetInstance()->GetDelta();
				else if (m_pTerrain->GetVecTile()[i]->tRect.left < srcList.front()->GetPInfo().tRect.right &&
					m_pTerrain->GetVecTile()[i]->tRect.right > srcList.front()->GetPInfo().tRect.right)
					srcList.front()->GetPInfo().vPos -= D3DXVECTOR3(1.f, 0.f, 0.f) * srcList.front()->GetPInfo().fSpeed * CTimeMgr::GetInstance()->GetDelta();
			}
		}
		else if (IntersectRect(&rc, &m_pTerrain->GetVecTile()[i]->tRect, &srcList.front()->GetPInfo().tRect) && 2 == m_pTerrain->GetVecTile()[i]->byOption)
		{
			float fMoveX = rc.left - rc.right;
			float fMoveY = rc.top - rc.bottom;

			float fX = srcList.front()->GetPInfo().vPos.x;
			float fY = srcList.front()->GetPInfo().vPos.y;
			if (!dynamic_cast<CPlayer*>(srcList.front())->GetIsRoll())
			{
				if (fMoveX > fMoveY) // Y축으로 밀어냄
				{
					if (m_pTerrain->GetVecTile()[i]->tRect.top < srcList.front()->GetPInfo().tRect.top &&
						m_pTerrain->GetVecTile()[i]->tRect.bottom > srcList.front()->GetPInfo().tRect.top)
						srcList.front()->GetPInfo().vPos -= D3DXVECTOR3(0.f, -1.0f, 0.f) * srcList.front()->GetPInfo().fSpeed * CTimeMgr::GetInstance()->GetDelta();
					else if (m_pTerrain->GetVecTile()[i]->tRect.top < srcList.front()->GetPInfo().tRect.bottom &&
						m_pTerrain->GetVecTile()[i]->tRect.bottom > srcList.front()->GetPInfo().tRect.bottom)
						srcList.front()->GetPInfo().vPos -= D3DXVECTOR3(0.f, 1.0f, 0.f) * srcList.front()->GetPInfo().fSpeed * CTimeMgr::GetInstance()->GetDelta();
				}
				else // X축으로 밀어냄
				{
					if (m_pTerrain->GetVecTile()[i]->tRect.left < srcList.front()->GetPInfo().tRect.left &&
						m_pTerrain->GetVecTile()[i]->tRect.right > srcList.front()->GetPInfo().tRect.left)
						srcList.front()->GetPInfo().vPos -= D3DXVECTOR3(-1.f, 0.f, 0.f) * srcList.front()->GetPInfo().fSpeed * CTimeMgr::GetInstance()->GetDelta();
					else if (m_pTerrain->GetVecTile()[i]->tRect.left < srcList.front()->GetPInfo().tRect.right &&
						m_pTerrain->GetVecTile()[i]->tRect.right > srcList.front()->GetPInfo().tRect.right)
						srcList.front()->GetPInfo().vPos -= D3DXVECTOR3(1.f, 0.f, 0.f) * srcList.front()->GetPInfo().fSpeed * CTimeMgr::GetInstance()->GetDelta();
				}
			}
		}
		else if (IntersectRect(&rc, &m_pTerrain->GetVecTile()[i]->tRect, &srcList.front()->GetPInfo().tRect) && 3 == m_pTerrain->GetVecTile()[i]->byOption)
		{
			srcList.front()->SetPos(srcList.front()->GetPInfo().vPos + D3DXVECTOR3(0.f, -TILECY * 6, 0.f));
			CScrollMgr::MoveScrollPos(D3DXVECTOR3(0.f, -WINCY, 0.f));

		}
		else if (IntersectRect(&rc, &m_pTerrain->GetVecTile()[i]->tRect, &srcList.front()->GetPInfo().tRect) && 4 == m_pTerrain->GetVecTile()[i]->byOption)
		{
			srcList.front()->SetPos(srcList.front()->GetPInfo().vPos + D3DXVECTOR3(TILECX * 8, 0.f, 0.f));
			CScrollMgr::MoveScrollPos(D3DXVECTOR3(WINCX, 0.f, 0.f));
		}
		else if (IntersectRect(&rc, &m_pTerrain->GetVecTile()[i]->tRect, &srcList.front()->GetPInfo().tRect) && 5 == m_pTerrain->GetVecTile()[i]->byOption)
		{
			srcList.front()->SetPos(srcList.front()->GetPInfo().vPos + D3DXVECTOR3(0.f, TILECY * 6, 0.f));
			CScrollMgr::MoveScrollPos(D3DXVECTOR3(0.f, WINCY, 0.f));
		}
		else if (IntersectRect(&rc, &m_pTerrain->GetVecTile()[i]->tRect, &srcList.front()->GetPInfo().tRect) && 6 == m_pTerrain->GetVecTile()[i]->byOption)
		{
			srcList.front()->SetPos(srcList.front()->GetPInfo().vPos + D3DXVECTOR3(-TILECX * 8, 0.f, 0.f));
			CScrollMgr::MoveScrollPos(D3DXVECTOR3(-WINCX, 0.f, 0.f));
		}
	}
}

void CCollisionMgr::CollisionTileEX(OBJECT_LIST& srcList)
{
	RECT rc = {};
	if (srcList.empty())
		return;

	CTerrain* m_pTerrain = dynamic_cast<CTerrain*>(CObjectMgr::GetInstance()->GetMap());
	NULL_CHECK(m_pTerrain);

	for (int i = 0; i < m_pTerrain->GetVecTile().size(); ++i)
	{
		if (1 == m_pTerrain->GetVecTile()[i]->byOption)
		{
			auto iter_begin = srcList.begin();
			auto iter_end = srcList.end();

			for (; iter_begin != iter_end; ++iter_begin)
			{
				if (IntersectRect(&rc, &m_pTerrain->GetVecTile()[i]->tRect, &(*iter_begin)->GetPInfo().tRect))
					dynamic_cast<CBullet*>(*iter_begin)->SetColli(true);
			}
		}
	}

}

void CCollisionMgr::CollisionObject(OBJECT_LIST & dstList)
{
	if (dstList.empty())
		return;

	RECT rc = {};

	auto iter_front = CObjectMgr::GetInstance()->GetList(OBJECT_PLAYER).front();
	auto iter_begin = dstList.begin();
	auto iter_end	= dstList.end();

	for (; iter_begin != iter_end; ++iter_begin)
	{
		if(IntersectRect(&rc, &(*iter_begin)->GetPInfo().tRect, &iter_front->GetPInfo().tRect))
		{
			float fMoveX = rc.left - rc.right;
			float fMoveY = rc.top - rc.bottom;

			float fX = iter_front->GetPInfo().vPos.x;
			float fY = iter_front->GetPInfo().vPos.y;

			if (fMoveX > fMoveY) // Y축으로 밀어냄
			{
				if ((*iter_begin)->GetPInfo().tRect.top < iter_front->GetPInfo().tRect.top &&
					(*iter_begin)->GetPInfo().tRect.bottom > iter_front->GetPInfo().tRect.top)
					iter_front->GetPInfo().vPos -= D3DXVECTOR3(0.f, -1.0f, 0.f) * iter_front->GetPInfo().fSpeed * CTimeMgr::GetInstance()->GetDelta();
				else if ((*iter_begin)->GetPInfo().tRect.top < iter_front->GetPInfo().tRect.bottom &&
					(*iter_begin)->GetPInfo().tRect.bottom > iter_front->GetPInfo().tRect.bottom)
					iter_front->GetPInfo().vPos -= D3DXVECTOR3(0.f, 1.0f, 0.f) * iter_front->GetPInfo().fSpeed * CTimeMgr::GetInstance()->GetDelta();
			}
			else // X축으로 밀어냄
			{
				if ((*iter_begin)->GetPInfo().tRect.left < iter_front->GetPInfo().tRect.left &&
					(*iter_begin)->GetPInfo().tRect.right > iter_front->GetPInfo().tRect.left)
					iter_front->GetPInfo().vPos -= D3DXVECTOR3(-1.f, 0.f, 0.f) * iter_front->GetPInfo().fSpeed * CTimeMgr::GetInstance()->GetDelta();
				else if ((*iter_begin)->GetPInfo().tRect.left < iter_front->GetPInfo().tRect.right &&
					(*iter_begin)->GetPInfo().tRect.right > iter_front->GetPInfo().tRect.right)
					iter_front->GetPInfo().vPos -= D3DXVECTOR3(1.f, 0.f, 0.f) * iter_front->GetPInfo().fSpeed * CTimeMgr::GetInstance()->GetDelta();
			}
		}
	}
}

void CCollisionMgr::CollisionAttack(OBJECT_LIST & dstList, OBJECT_LIST & srcList)
{
	if(dstList.empty() || srcList.empty())
		return;

	RECT rc = {};
	RECT rc2 = {0,0,0,0};
	

	auto src_begin = srcList.begin();
	auto src_end = srcList.end();

	bool bAttack = false;

	for (; src_begin != src_end; ++src_begin)
	{
		auto dst_begin = dstList.begin();
		auto dst_end = dstList.end();
		
		for (; dst_begin != dst_end; ++dst_begin)
		{
			if((dstList == CObjectMgr::GetInstance()->GetList(OBJECT_PLAYER) && dynamic_cast<CPlayer*>(*dst_begin)->GetIsRoll()))
				return;
			
			if (IntersectRect(&rc, &(*dst_begin)->GetPInfo().tRect, &(*src_begin)->GetPInfo().tAttackRange) && !(*dst_begin)->GetOInfo().binvincibility)
			{	
				(*dst_begin)->GetOInfo().iHp -= (*src_begin)->GetOInfo().iAttack;
				(*dst_begin)->GetOInfo().binvincibility = true; 
				bAttack = true;
				if (srcList == CObjectMgr::GetInstance()->GetList(OBJECT_BULLET))
				{
					dynamic_cast<CBullet*>(*src_begin)->SetColli(true);
				}
			}
		}
		if(bAttack)
			(*src_begin)->SetAttack(rc2);	
	}
}

void CCollisionMgr::CollisionItem()
{	
	if(CObjectMgr::GetInstance()->GetList(OBJECT_PLAYER).empty() || CObjectMgr::GetInstance()->GetList(OBJECT_ITEM).empty())
		return;

	auto iter_front = CObjectMgr::GetInstance()->GetList(OBJECT_PLAYER).front();
	auto iter_begin = CObjectMgr::GetInstance()->GetList(OBJECT_ITEM).begin();
	auto iter_end = CObjectMgr::GetInstance()->GetList(OBJECT_ITEM).end();

	RECT rc = {};
	for (; iter_begin != iter_end; ++iter_begin)
	{
		if (IntersectRect(&rc, &(*iter_begin)->GetPInfo().tRect, &(iter_front)->GetPInfo().tRect))
		{
			dynamic_cast<CPlayer*>(iter_front)->PushItem(*iter_begin);
			(*iter_begin)->SetPos(D3DXVECTOR3(-1000.f,-1000.f,1.f));
		}
	}
}

