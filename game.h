#ifndef _GAME_H_
#define _GAME_H_

//�C���N���[�h�t�@�C��
#include "player.h"
#include "input.h"
#include "platform.h"
#include "bg.h"
#include "Enemy.h"
#include "water.h"
#include "boss.h"
#include "switch.h"
#include "bullet.h"
#include "minion.h"
#include "explosion.h"
#include "score.h"
#include "arrow.h"
#include "scorechange.h"
#include "PauseMenu.h"
#include "Tutorial.h"

//�v���g�^�C�v�錾
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetStage(void);

#endif _GAME_H_