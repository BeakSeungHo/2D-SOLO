#include "stdafx.h"
#include "Wave.h"


CWave::CWave()
{
}


CWave::~CWave()
{
}

int CWave::Update()
{
	return 0;
}

void CWave::LateUpdate()
{
}

void CWave::Render()
{
}

HRESULT CWave::Initialize()
{
	return E_NOTIMPL;
}

void CWave::Release()
{
}

CWave * CWave::Create()
{
	CWave* pInstance = new CWave;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
