#ifndef _WATER_H_
#define _WATER_H_

//インクルードファイル
#include "main.h"
#include "input.h"

//マクロ定義
#define MAX_WATER		(24)			//川や滝のの最大数

//水の状態
typedef enum
{
	WATERSTATE_READY = 0,				//開くことができる状態
	WATERSTATE_OPEN,					//流れている状態
	WATERSTATE_CLOSING,					//しまっている状態
	WATERSTATE_MAX

}WATERSTATE;

//水の構造体
typedef struct
{
	D3DXVECTOR3 pos;					//位置
	float fWidth;						//幅
	float fHeight;						//高さ
	int nType;							//種類
	int nNumSwitch;						//スイッチの番号
	WATERSTATE wState;					//状態
	bool bUse;							//使用されているかどうか
}WATER;

//プロトタイプ宣言
void InitWater(void);
void UninitWater(void);
void UpdateWater(void);
void DrawWater(void);
void SetWater(D3DXVECTOR3 pos, int type, float width, float height, int nSwitch, WATERSTATE state);
int WaterInteraction(D3DXVECTOR3*pPos,			//現在の位置
	D3DXVECTOR3*pMove,							//移動量
	float fWidth,								//幅
	float fHeight);								//高さ);
WATER*GetWater(void);

#endif // !_WATER_H_