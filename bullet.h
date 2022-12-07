#ifndef _BULLET_H_
#define _BULLET_H_

//インクルードファイル
#include "main.h"
#include "platform.h"
#include "score.h"
#include "scorechange.h"

//弾の種類
typedef enum
{
	BULLETTYPE_NORMALENEMY = 0,		//プレイヤーの普通弾
	BULLETTYPE_BOSS,				//敵の弾
	BULLETTYPE_MAX
}BULLETTYPE;

//構造体を設定
typedef struct
{
	D3DXVECTOR3 pos;			//弾の位置
	D3DXVECTOR3 LastPos;		//前回の位置
	D3DXVECTOR3 move;			//弾の移動量
	D3DXVECTOR3 Accel;			//加速
	int nLife;					//弾の体力
	int nType;					//種類
	int nCntDelay;				//数をカウントするカウンター
	int nCounterAnim;
	int nPatternAnim;
	bool bUse;					//弾が使われているかどうか
}Bullet;

//プロトタイプ宣言
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 acc, int type);

#endif _BULLET_H_