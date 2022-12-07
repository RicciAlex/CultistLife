#ifndef _ARROW_H_
#define _ARROW_H_

#include "main.h"

#define MAX_ARROW		(8)

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	int nType;
	bool bUse;
}Arrow;

//プロトタイプ宣言
void InitArrow(void);
void UninitArrow(void);
void UpdateArrow(void);
void DrawArrow(void);
void SetArrow(D3DXVECTOR3 pos, D3DXVECTOR3 move, int type);

#endif _ARROW_H_