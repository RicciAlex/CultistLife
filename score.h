#ifndef _SCORE_H_
#define _SCORE_H_

#include "player.h"
#include "Ranking.h"

//プロトタイプ宣言
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void SetScore(int nScore);
void AddScore(int nValue);

#endif _SCORE_H_