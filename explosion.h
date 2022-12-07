#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

//インクルードファイル
#include "main.h"
#include "sound.h"
#include "player.h"
#include "scorechange.h"

//マクロ定義
#define MAX_EXPLOSION		(128)			//爆発の最大数

//爆発の構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;		//爆発の位置
	D3DXCOLOR col;			//爆発の色
	int nCounterAnim;		//アニメーションカウンター
	int nPatternAnim;		//アニメーションカウンターNo.
	int nSize;				//爆発の大きさ
	bool bUse;				//爆発が使用されているかどうか
}Explosion;

//プロトタイプ宣言
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col, int size);

#endif _EXPLOSION_H_
