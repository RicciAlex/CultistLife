#ifndef _ENEMY_H_
#define _ENEMY_H_

//インクルードファイル
#include "main.h"
#include "player.h"
#include "boss.h"
#include "water.h"
#include "score.h"
#include "bullet.h"
#include "scorechange.h"

//マクロ定義
#define MAX_ENEMY		(128)		//敵の最大数

//敵の状態
typedef enum
{
	ENEMYSTATE_NORMAL = 0,			//通常状態
	//ENEMYSTATE_DAMAGE,				//ダメージ状態
	ENEMYSTATE_APPEAR,				//発生した状態
	ENEMYSTATE_DEATH,				//死んだ状態
	/*ENEMYSTATE_CHARGE,
	ENEMYSTATE_EXPLODE,*/
	ENEMYSTATE_MAX
}ENEMYSTATE;

//敵の種類
typedef enum
{
	ENEMYTYPE_BLUESLIME = 0,			//青スライム
	ENEMYTYPE_GREENSLIME,				//緑スライム
	ENEMYTYPE_SLIMEBAT,					//こうもりスライム
	ENEMYTYPE_MIMIC,
	ENEMYTYPE_CARD_HEART,
	ENEMYTYPE_CARD_DIAMOND,
	ENEMYTYPE_CARD_CLUB,
	ENEMYTYPE_CARD_SPADE,
	ENEMYTYPE_MAX
}ENEMYTYPE;

//プレイヤーを見たかどうかの状態
typedef enum
{
	ENEMYSTATE_ENCOUNTER_FALSE = 0,				//プレイヤーが見えない状態
	ENEMYSTATE_ENCOUNTER_TRUE,					//プレイヤーを見た状態
	ENEMYSTATE_ENCOUNTER_LOST,					//プレイヤーが見えなくなった状態　(まだ出来ていない)
	ENEMYSTATE_ENCOUNTER_MAX
}ENEMYSTATE_ENCOUNTER;

//敵の構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;							//位置
	D3DXVECTOR3 move;							//移動量
	D3DXVECTOR3 LastPos;						//前回の位置
	MOVESTATE MoveState;						//移動状態
	ENEMYTYPE nType;							//種類
	ENEMYSTATE_ENCOUNTER EncounterState;		
	ENEMYSTATE state;							//敵の状態
	float fSight;								//視力
	float fHeight;								//高さ
	float fWidth;								//幅
	//ENEMYSTATE state;							//状態
	int nCounterState;						//状態管理カウンター
	//int nCounterShoot;						//弾の発生のカウンター
	int nCountAnim;								//アニメーションカウンター
	int nPatternAnim;							//アニメーションパターン
	int nChaseCounter;							//追いかけるカウンター
	int nCurrentPlatform;						//現在のプラットフォーム
	int nDirection;								//向き
	//int nLife;								//体力
	bool bUse;									//使用されているかどうか
}Enemy;

//プロトタイプ宣言
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, ENEMYTYPE nType);
void WarpEnemy(int nCntEnemy);
void SlimeAnimation(int nCntEnemy);
void MimicAnimation(int nCntEnemy);
void CardAnimation(int nCntEnemy);
void UpdateEnemyTex(int nCntEnemy, int nSheetLine, float nU, float nV);
void EnemyEncounter(int nCntEnemy, float Height);
Enemy*GetEnemy(void);
void SpawnEnemy(void)
/*
void HitEnemy(int nCntEnemy, int nDamage);
*/;

#endif _ENEMY_H_
