#ifndef _BOSS_H_
#define _BOSS_H_

//インクルードファイル
#include "main.h"
#include "player.h"
#include "Enemy.h"
#include "bullet.h"
#include "minion.h"
#include "boss.h"
#include "sound.h"
#include "scorechange.h"

//ボスの状態
typedef enum
{
	BOSS_STATE_APPEAR = 0,			//発生状態
	BOSS_STATE_SLEEP,
	BOSS_STATE_NORMAL,				//普通
	BOSS_STATE_ATTACK,				//攻撃状態
	BOSS_STATE_DAMAGE,				//ダメージ状態
	BOSS_STATE_DEATH,				//死んだ状態
	BOSS_STATE_MAX
}BOSS_STATE;

//敵の構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;							//位置
	D3DXVECTOR3 move;							//移動量
	D3DXVECTOR3 LastPos;						//前回の位置
	MOVESTATE MoveState;						//移動状態
	int nType;									//種類
	//ENEMYSTATE_ENCOUNTER EncounterState;
	//float fSight;								//視力
	float fHeight;								//高さ
	BOSS_STATE BossState;							//状態
	int nCounterState;						//状態管理カウンター
	int nCounterShoot;						//弾の発生のカウンター
	int nCountAnim;								//アニメーションカウンター
	int nPatternAnim;							//アニメーションパターン
	int nChaseCounter;							//追いかけるカウンター
	bool bDamage;								//向き
	int nLife;								    //体力
	bool bUse;									//使用されているかどうか
}Boss;

//プロトタイプ宣言
void InitBoss(void);
void UninitBoss(void);
void UpdateBoss(void);
void DrawBoss(void);
void SetBoss(D3DXVECTOR3 pos, int type);
void UpdateSlimeSnake(void);
void UpdateTarotMaster(void);
void UpdateBossTex(int nSheetLine, float nU, float nV);
Boss*GetBoss(void);

#endif  _BOSS_H_