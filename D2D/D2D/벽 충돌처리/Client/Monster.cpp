#include "stdafx.h"
#include "Monster.h"


CMonster::CMonster()
{
}


CMonster::~CMonster()
{
}

int CMonster::Update()
{
	return 0;
}

void CMonster::LateUpdate()
{
}

void CMonster::Render()
{
}

HRESULT CMonster::Initialize()
{
	return E_NOTIMPL;
}

void CMonster::Release()
{
}

CMonster * CMonster::Create()
{
	CMonster* pInstance = new CMonster;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
