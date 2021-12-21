#pragma once

typedef struct tagInfo
{
	D3DXVECTOR3 vPos;	// 위치벡터 (수학에서는 위치벡터라는 개념이 없음)
	D3DXVECTOR3 vDir;	// 방향벡터
	D3DXVECTOR3 vLook;
	D3DXVECTOR3 vSize;
	D3DXMATRIX matWorld; // 월드행렬 = 스(케일) * 자(전) * 이(동) * 공(전) * 부(모행렬)
	RECT		tRect;
	RECT		tAttackRange;
	float		fSpeed;
}INFO;

typedef struct tagObjectInfo
{
	int		iHp;
	int		iMaxHp;
	int		iAttack;
	int		iDef;
	int		Alpha;
	bool	binvincibility;
	float	fInvinTime;
	float	fMaxInvinTime;
}OBINFO;

typedef struct tagTextureInfo
{
	LPDIRECT3DTEXTURE9 pTexture;
	D3DXIMAGE_INFO tImgInfo;
}TEX_INFO;

typedef struct tagTileInfo
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vSize;
	float fCenterX;
	float fCenterY;
	RECT tRect;
	BYTE byDrawID;
	BYTE byOption;
}TILE_INFO;

typedef struct tagIteminfo
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vSize;
	D3DXMATRIX	matWorld;
	RECT tRect;
	BYTE byDrawID;
	BYTE byOption;
	int iAbility;
	int iAmount;
}ITEM_INFO;

typedef struct tagFrame
{
	float fCurFrame;
	float fMaxFrame;
}FRAME;

typedef struct tagUnit
{
	wstring wstrName;
	int iAtt;
	int iDef;
	int iJobIndex;
	int iItem;
}UNIT_DATA;

typedef struct tagPathInfo
{
	wstring wstrObjectKey;
	wstring wstrStateKey;
	wstring wstrRelative;
	int iImgCount;
}PATH_INFO;