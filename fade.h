#ifndef _FADET_H_
#define _FADET_H_

#include "main.h"
#include "sound.h"
#include "game.h"
#include "title.h"
#include "result.h"

//�t�F�[�h
typedef enum
{
	FADE_NONE = 0,
	FADE_IN,				//�t�F�[�h�C��
	FADE_OUT,				//�t�F�[�h�A�E�g
	FADE_MAX
}FADE;

//�v���g�^�C�v�錾
void InitFade(MODE modeNext);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);
void SetFade(MODE modeNext);
FADE GetFade(void);

#endif _FADE_H_