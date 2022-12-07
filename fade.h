#ifndef _FADET_H_
#define _FADET_H_

#include "main.h"
#include "sound.h"
#include "game.h"
#include "title.h"
#include "result.h"

//フェード
typedef enum
{
	FADE_NONE = 0,
	FADE_IN,				//フェードイン
	FADE_OUT,				//フェードアウト
	FADE_MAX
}FADE;

//プロトタイプ宣言
void InitFade(MODE modeNext);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);
void SetFade(MODE modeNext);
FADE GetFade(void);

#endif _FADE_H_