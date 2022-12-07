#ifndef _MINION_H_
#define _MINION_H_

//インクルードファイル
#include "main.h"
#include "boss.h"
#include "explosion.h"
#include "bullet.h"
#include "scorechange.h"

//マクロ定義
#define MAX_MINION		(16)		//敵の最大数

//敵の状態
typedef enum
{
	MINIONSTATE_NORMAL = 0,				//通常状態
	MINIONSTATE_ATTACK,
	MINIONSTATE_RETURN,
	MINIONSTATE_EXPLODE,				//爆発する状態
	MINIONSTATE_APPEAR,
	MINIONSTATE_MAX
}MINIONSTATE;

//敵の構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;							//位置
	D3DXVECTOR3 move;							//移動量
	D3DXVECTOR3 LastPos;						//前回の位置
	MINIONSTATE state;							//状態	
	float fHeight;								//高さ
	float fWidth;								//幅
	int nType;									//種類
	int nCounterState;						//状態管理カウンター
	int nCountAnim;								//アニメーションカウンター
	int nPatternAnim;							//アニメーションパターン
	int nDirection;								//向き
	bool bUse;									//使用されているかどうか
}Minion;

//プロトタイプ宣言
void InitMinion(void);
void UninitMinion(void);
void UpdateMinion(void);
void DrawMinion(void);
void SetMinion(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nType);
void UpdateBombBat(void);
void UpdateTarotSummon(void);
Minion*GetMinion(void);

#endif _MINION_H_
