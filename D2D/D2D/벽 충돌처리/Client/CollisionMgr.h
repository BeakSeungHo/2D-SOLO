#pragma once
class CCollisionMgr
{
private:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static void CollisionTile(OBJECT_LIST& dstList, OBJECT_LIST& srcList);
	static void CollisionAttack(OBJECT_LIST& dstList, OBJECT_LIST& srcList);


};

