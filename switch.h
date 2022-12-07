#ifndef _SWITCH_H_
#define _SWITCH_H_

//インクルードファイル
#include "main.h"
#include "player.h"
#include "input.h"
#include "water.h"

//マクロ定義
#define MAX_SWITCH		(48)					//プラットフォームの最大数
#define SWITCH_HEIGHT	(15.0f)
#define SWITCH_WIDTH	(15.0f)

//スイッチ構造体の設定
typedef struct
{
	D3DXVECTOR3 Pos;		//スイッチの位置
	int nCountSwitch;		//スイッチの番号
	bool bActive;			//スイッチの状態
	bool bUse;				//スイッチが使用されているかどうか
}SWITCH;

//プロトタイプ宣言
void InitSwitch(void);
void UninitSwitch(void);
void UpdateSwitch(void);
void DrawSwitch(void);
void SetSwitch(D3DXVECTOR3 pos, int nNumberSwitch, bool Active);
int*GetActiveSwitch(void);

#endif