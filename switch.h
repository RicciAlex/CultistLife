#ifndef _SWITCH_H_
#define _SWITCH_H_

//�C���N���[�h�t�@�C��
#include "main.h"
#include "player.h"
#include "input.h"
#include "water.h"

//�}�N����`
#define MAX_SWITCH		(48)					//�v���b�g�t�H�[���̍ő吔
#define SWITCH_HEIGHT	(15.0f)
#define SWITCH_WIDTH	(15.0f)

//�X�C�b�`�\���̂̐ݒ�
typedef struct
{
	D3DXVECTOR3 Pos;		//�X�C�b�`�̈ʒu
	int nCountSwitch;		//�X�C�b�`�̔ԍ�
	bool bActive;			//�X�C�b�`�̏��
	bool bUse;				//�X�C�b�`���g�p����Ă��邩�ǂ���
}SWITCH;

//�v���g�^�C�v�錾
void InitSwitch(void);
void UninitSwitch(void);
void UpdateSwitch(void);
void DrawSwitch(void);
void SetSwitch(D3DXVECTOR3 pos, int nNumberSwitch, bool Active);
int*GetActiveSwitch(void);

#endif