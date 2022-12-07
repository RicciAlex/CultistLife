//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// BGM0
	SOUND_LABEL_BGM001,			// BGM1
	SOUND_LABEL_BGM002,			// BGM2
	SOUND_LABEL_BGM005,			// BGM5
	SOUND_LABEL_BGMTITLE,
	SOUND_LABEL_BGMNORMALSTAGE,
	SOUND_LABEL_BGMBOSS,
	SOUND_LABEL_BGMWIN,
	SOUND_LABEL_BGMGAMEOVER,
	SOUND_LABEL_SE_LEVELCHANGE,
	SOUND_LABEL_SE_SHOT,		// �e���ˉ�
	SOUND_LABEL_SE_HIT,			// �q�b�g��
	SOUND_LABEL_SE_EXPLOSION,	// ������
	SOUND_LABEL_SE_FIRE,		// ��
	SOUND_LABEL_SE_SLASH,		// 
	SOUND_LABEL_SE_DEATHSLASH,		// 
	SOUND_LABEL_SE_WATER,		// 
	SOUND_LABEL_SE_NORMALDAMAGE,		// 
	SOUND_LABEL_SE_NORMALBULLET,		// 
	SOUND_LABEL_SE_SELOPTION,		// 
	SOUND_LABEL_SE_CLICK,		// 
	SOUND_LABEL_SE_GETITEM,		//
	SOUND_LABEL_SE_CARDSWING,		//
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
