#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

//�C���N���[�h�t�@�C��
#include "main.h"
#include "sound.h"
#include "player.h"
#include "scorechange.h"

//�}�N����`
#define MAX_EXPLOSION		(128)			//�����̍ő吔

//�����̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;		//�����̈ʒu
	D3DXCOLOR col;			//�����̐F
	int nCounterAnim;		//�A�j���[�V�����J�E���^�[
	int nPatternAnim;		//�A�j���[�V�����J�E���^�[No.
	int nSize;				//�����̑傫��
	bool bUse;				//�������g�p����Ă��邩�ǂ���
}Explosion;

//�v���g�^�C�v�錾
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col, int size);

#endif _EXPLOSION_H_
