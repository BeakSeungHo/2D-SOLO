#pragma once
class CScrollMgr
{
private:
	CScrollMgr();
	~CScrollMgr();

public:
	static const D3DXVECTOR3& GetScrollPos();

public:
	static void MoveScrollPos(const D3DXVECTOR3& vMove);
	static void SetScrollPos(const D3DXVECTOR3& vMove);
	

private:
	static D3DXVECTOR3 m_vScrollPos;	
};

