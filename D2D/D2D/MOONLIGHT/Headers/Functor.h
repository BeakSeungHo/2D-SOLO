#pragma once

#ifndef __FUNCTOR_H__

#include "GameObject.h"

class CSortObjectY
{
public:
	bool operator()(CGameObject* pDst, CGameObject* pSrc)
	{
		return pDst->GetPInfo().vPos.y < pSrc->GetPInfo().vPos.y;
	}
};

#define __FUNCTOR_H__
#endif
