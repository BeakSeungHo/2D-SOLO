#include "stdafx.h"
#include "KeyMgr.h"

IMPLEMENT_SINGLETON(CKeyMgr)

CKeyMgr::CKeyMgr()
	: m_dwKeyDown(0), m_dwKeyUp(0), m_dwCurKey(0)
{

}
CKeyMgr::~CKeyMgr()
{

}

void CKeyMgr::Update()
{
	m_dwCurKey = 0;

	if (GetAsyncKeyState('W') & 0x8000)
		m_dwCurKey |= KEY_W;
	if (GetAsyncKeyState('S') & 0x8000)
		m_dwCurKey |= KEY_S;
	if (GetAsyncKeyState('A') & 0x8000)
		m_dwCurKey |= KEY_A;
	if (GetAsyncKeyState('D') & 0x8000)
		m_dwCurKey |= KEY_D;
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		m_dwCurKey |= KEY_SPACE;
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		m_dwCurKey |= KEY_RETURN;
	if (GetAsyncKeyState('J') & 0x8000)
		m_dwCurKey |= KEY_J;
	if (GetAsyncKeyState('E') & 0x8000)
		m_dwCurKey |= KEY_E;
	if (GetAsyncKeyState('I') & 0x8000)
		m_dwCurKey |= KEY_I;
	if (GetAsyncKeyState('Z') & 0x8000)
		m_dwCurKey |= KEY_Z;
	if (GetAsyncKeyState('K') & 0x8000)
		m_dwCurKey |= KEY_K;
	if (GetAsyncKeyState('C') & 0x8000)
		m_dwCurKey |= KEY_C;
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		m_dwCurKey |= KEY_LBUTTON;
	if (GetAsyncKeyState(VK_TAB) & 0x8000)
		m_dwCurKey |= KEY_TAB;
	if (GetAsyncKeyState('B') & 0x8000)
		m_dwCurKey |= KEY_B;
	if (GetAsyncKeyState('G') & 0x8000)
		m_dwCurKey |= KEY_G;
}

bool CKeyMgr::KeyDown(DWORD dwKey)
{
	// 전에 누른적 없고 현재 눌렸을 때 TRUE
	if (!(m_dwKeyDown & dwKey) && (m_dwCurKey & dwKey))
	{
		m_dwKeyDown |= dwKey;
		return true;
	}
	// 전에 누른적 있고 현재 누르지 않았을 때 FALSE
	if ((m_dwKeyDown & dwKey) && !(m_dwCurKey & dwKey))
	{
		m_dwKeyDown ^= dwKey;
		return false;
	}

	return false;
}

bool CKeyMgr::KeyUp(DWORD dwKey)
{
	// 전에 누른적 있고 현재 누르지 않았을 때 TRUE
	if ((m_dwKeyUp & dwKey) && !(m_dwCurKey & dwKey))
	{
		m_dwKeyUp ^= dwKey;
		return true;
	}
	// 전에 누른적 없고 현재 눌렸을 때 FALSE
	if (!(m_dwKeyUp & dwKey) && (m_dwCurKey & dwKey))
	{
		m_dwKeyUp |= dwKey;
		return false;
	}

	return false;
}

bool CKeyMgr::KeyPressing(DWORD dwKey)
{
	if (m_dwCurKey & dwKey)
		return true;

	return false;
}