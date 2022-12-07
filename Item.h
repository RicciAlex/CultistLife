#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"
#include "main.h"
#include "player.h"
#include "score.h"

#define MAX_ITEM		(12)

//アイテムの種類
typedef enum
{
	ITEMTYPE_NULL = 0,		//アイテムがない
	ITEMTYPE_CARD,			//爆弾
	ITEMTYPE_MAX
}ITEMTYPE;

//アイテム構造体の設定
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;
	D3DXVECTOR3 EqPoint;
	int nCntAnim;
	int nType;				//種類
	bool bUse;				//使用されているかどうか
}ITEM;

//プロトタイプ宣言
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 move, int type);

#endif _ITEM_H_