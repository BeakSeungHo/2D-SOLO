#include "stdafx.h"
#include "CollisionMgr.h"
#include "Terrain.h"
#include "GameObject.h"

CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::CollisionTile(OBJECT_LIST& dstList, OBJECT_LIST& srcList)
{
	RECT rc = {};

	if(dstList.empty() || srcList.empty())
		return;

	for (int i = 0; i < dynamic_cast<CTerrain*>(dstList.front())->GetVecTile().size(); ++i)
	{
		if (IntersectRect(&rc, &dynamic_cast<CTerrain*>(dstList.front())->GetVecTile()[i]->tRect, &srcList.front()->GetPInfo().tRect) && 1 == dynamic_cast<CTerrain*>(dstList.front())->GetVecTile()[i]->byOption)
		{
			float fMoveX = rc.left - rc.right;
			float fMoveY = rc.top - rc.bottom;

			float fX = srcList.front()->GetPInfo().vPos.x;
			float fY = srcList.front()->GetPInfo().vPos.y;

			if (fMoveX > fMoveY) // Y축으로 밀어냄
			{
				if (dynamic_cast<CTerrain*>(dstList.front())->GetVecTile()[i]->tRect.top < srcList.front()->GetPInfo().tRect.top &&
					dynamic_cast<CTerrain*>(dstList.front())->GetVecTile()[i]->tRect.bottom > srcList.front()->GetPInfo().tRect.top)
					srcList.front()->GetPInfo().vPos -= D3DXVECTOR3(0.f, -1.0f, 0.f);
				else if(dynamic_cast<CTerrain*>(dstList.front())->GetVecTile()[i]->tRect.top < srcList.front()->GetPInfo().tRect.bottom &&
					dynamic_cast<CTerrain*>(dstList.front())->GetVecTile()[i]->tRect.bottom > srcList.front()->GetPInfo().tRect.bottom)
					srcList.front()->GetPInfo().vPos -= D3DXVECTOR3(0.f, 1.0f, 0.f);
			}
			else // X축으로 밀어냄
			{
				if (dynamic_cast<CTerrain*>(dstList.front())->GetVecTile()[i]->tRect.left < srcList.front()->GetPInfo().tRect.left &&
					dynamic_cast<CTerrain*>(dstList.front())->GetVecTile()[i]->tRect.right > srcList.front()->GetPInfo().tRect.left )
					srcList.front()->GetPInfo().vPos -= D3DXVECTOR3(-1.f, 0.f, 0.f);
				else if (dynamic_cast<CTerrain*>(dstList.front())->GetVecTile()[i]->tRect.left < srcList.front()->GetPInfo().tRect.right &&
					dynamic_cast<CTerrain*>(dstList.front())->GetVecTile()[i]->tRect.right > srcList.front()->GetPInfo().tRect.right)
					srcList.front()->GetPInfo().vPos -= D3DXVECTOR3(1.f, 0.f, 0.f);
			}
		}
	}
}

void CCollisionMgr::CollisionAttack(OBJECT_LIST & dstList, OBJECT_LIST & srcList)
{
	
}

