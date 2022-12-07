#ifndef _SCHANGE_H_
#define _SCHANGE_H_

#include "main.h"
#include "player.h"

#define MAX_SCHANGE		(4)

typedef enum
{
	CHANGEVALUE_PLUS250 = 0,
	CHANGEVALUE_PLUS500,
	CHANGEVALUE_MINUS250,
	CHANGEVALUE_MINUS500

}CHANGEVALUE;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	int nType;
	CHANGEVALUE value;
	bool bUse;
}ScoreChange;

//プロトタイプ宣言
void InitSChange(void);
void UninitSChange(void);
void UpdateSChange(void);
void DrawSChange(void);
void SetSChange(D3DXVECTOR3 pos, D3DXVECTOR3 move, int type, CHANGEVALUE Value);

#endif _SCHANGE_H_