#ifndef _PLATFORM_H_
#define _PLATFORM_H_

//インクルードファイル
#include "main.h"
#include "water.h"
#include "switch.h"
#include "player.h"
#include "switch.h"
#include "Item.h"
#include "arrow.h"

//マクロ定義
#define MAX_PLATFORM		(256)					//プラットフォームの最大数

//プラットフォーム構造体の設定
typedef struct
{
	D3DXVECTOR3 Pos;		//プラットフォームの位置
	D3DXVECTOR3 move;		//移動量
	D3DXVECTOR3 Memorymove;	//移動量を保存するための変数
	float fwidth;			//プラットフォームの幅
	float fHeight;			//プラットフォームの高さ
	float fMaxX;			
	float fMinX;			
	float fMaxY;				
	float fMinY;			
	int nType;				//プラットフォームの種類
	int nMemory;			
	int nCntStatus;			
	bool bUse;				//プラットフォームが使用されているかどうか
}PLATFORM;

//プロトタイプ宣言
void InitPlatform(void);
void UninitPlatform(void);
void UpdatePlatform(void);
void DrawPlatform(void);
void SetPlatform(D3DXVECTOR3 pos, D3DXVECTOR3 move, float width, float height, int type,
				float fMaxX, float fMinX, float fMaxY, float fMinY);
PLATFORM*GetPlatform(void);
int BlockInteraction(D3DXVECTOR3*pPos,
	D3DXVECTOR3*pLastPos,
	D3DXVECTOR3*pMove,
	float fWidth,
	float fHeight);
int BlockInteractionBullet(D3DXVECTOR3*pPos,
	D3DXVECTOR3*pLastPos,
	D3DXVECTOR3*pMove,
	float fWidth,
	float fHeight);
void FirstStage(void);
void SecondStage(void);
void ThirdStage(void);
void BonusStage(void);
void FourthStage(void);
void FifthStage(void);

#endif // !_PLATFORM_H_
