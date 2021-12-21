#pragma once

typedef struct tagInfo
{
	D3DXVECTOR3 vPos;	// ��ġ���� (���п����� ��ġ���Ͷ�� ������ ����)
	D3DXVECTOR3 vDir;	// ���⺤��
	D3DXVECTOR3 vLook;
	D3DXVECTOR3 vSize;
	D3DXMATRIX matWorld; // ������� = ��(����) * ��(��) * ��(��) * ��(��) * ��(�����)
	RECT		tRect;
}INFO;

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