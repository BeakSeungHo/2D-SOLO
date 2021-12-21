#pragma once
class CCollisionMgr
{
private:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static void CollisionTile(OBJECT_LIST& srcList);
	static void CollisionTileEX(OBJECT_LIST& srcList);
	static void CollisionObject(OBJECT_LIST& dstList);
	static void CollisionAttack(OBJECT_LIST& dstList, OBJECT_LIST& srcList);
	static void CollisionItem();
};

