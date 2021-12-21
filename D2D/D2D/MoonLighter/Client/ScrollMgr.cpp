#include "stdafx.h"
#include "ScrollMgr.h"

D3DXVECTOR3 CScrollMgr::m_vScrollPos = { 0.f, 0.f, 0.f };

CScrollMgr::CScrollMgr()
{
}


CScrollMgr::~CScrollMgr()
{
}

const D3DXVECTOR3& CScrollMgr::GetScrollPos()
{
	// TODO: ���⿡ ��ȯ ������ �����մϴ�.
	return m_vScrollPos;
}

void CScrollMgr::MoveScrollPos(const D3DXVECTOR3& vMove)
{
	m_vScrollPos += vMove;
}

void CScrollMgr::SetScrollPos(const D3DXVECTOR3 & vMove)
{
	m_vScrollPos = vMove;
}