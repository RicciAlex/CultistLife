#ifndef _PLAYER_H_
#define _PLAYER_H_

//インクルードファイル
#include "main.h"
#include "platform.h"

//マクロ定義
#define PLAYER_HEIGHT	(75.0f)					//プレイヤーの高さ
#define PLAYER_WIDTH	(50.0f)					//プレイヤーの幅

//プレイヤーの状態
typedef enum
{
	PLAYERSTATE_NORMAL = 0,						//普通状態
	PLAYERSTATE_DAMAGE,							//ダメージ状態
	PLAYERSTATE_WIN,
	PLAYERSTATE_DEATH,
	PLAYERSTATE_MAX
}PLAYERSTATE;

//移動状態
typedef enum
{
	MOVESTATE_LANDED = 0,			//着地
	MOVESTATE_JUMP,				//ジャンプ
	MOVESTATE_FALLING,			//落下
	MOVESTATE_MAX
}MOVESTATE;

//プレイヤー構造体の設定
typedef struct
{
	D3DXVECTOR3 pos;								//位置
	D3DXVECTOR3 move;								//移動量
	D3DXVECTOR3 LastPos;								//プレイヤーの前回の位置
	//D3DXVECTOR3 rotPlayer;							//向き
	PLAYERSTATE state;								//プレイヤーの状態
	int nCounterState;								//状態管理のカウンター
	int nCounterAnim;								//アニメーションのカウンター
	int nPatternAnim;								//アニメーションパターン
	int nDirectionMove;								//向き
	MOVESTATE MoveState;						//移動状態
	int nCurrentPlatform;						//現在のプラットフォーム
	//int nCurrentPlatform;
	//float fLengthPlayer;							//対角線の長さ
	//float fAnglePlayer;								//対角線の角度
	//int nLife;										//体力
	//int nItem;										//アイテム
	//bool bDisp;										//使用されているかどうか
}Player;


//プロトタイプ宣言
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player*GetPlayer(void);
bool GetWin(void);

#endif // !_PLAYER_H_