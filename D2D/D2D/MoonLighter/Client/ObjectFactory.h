#pragma once

#ifndef __OBJECT_FACTORY_H__

class CGameObject;

/* 추상 팩토리 패턴 */
// 객체 생성 통일 및 캡슐화에 초점을 둔 디자인 패턴

template <typename T>
class CObjectFactory 
{
public:
	static CGameObject* CreateObject()
	{
		CGameObject* pInstance = T::Create();

		return pInstance;
	}

	static CGameObject* CreateObject(D3DXVECTOR3 Pos)
	{
		CGameObject* pInstance = T::Create();
		pInstance->SetPos(Pos);

		return pInstance;
	}

	static CGameObject* CreateObject(D3DXVECTOR3 Pos, D3DXVECTOR3 Center, BYTE DrawID)
	{
		CGameObject* pInstance = T::Create();
		pInstance->SetPos(Pos);
		pInstance->SetCenter(Center);
		pInstance->SetDrawID(DrawID);

		return pInstance;
	}
};

#define __OBJECT_FACTORY_H__
#endif
