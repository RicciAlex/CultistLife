#ifndef _BULLET_H_
#define _BULLET_H_

//�C���N���[�h�t�@�C��
#include "main.h"
#include "platform.h"
#include "score.h"
#include "scorechange.h"

//�e�̎��
typedef enum
{
	BULLETTYPE_NORMALENEMY = 0,		//�v���C���[�̕��ʒe
	BULLETTYPE_BOSS,				//�G�̒e
	BULLETTYPE_MAX
}BULLETTYPE;

//�\���̂�ݒ�
typedef struct
{
	D3DXVECTOR3 pos;			//�e�̈ʒu
	D3DXVECTOR3 LastPos;		//�O��̈ʒu
	D3DXVECTOR3 move;			//�e�̈ړ���
	D3DXVECTOR3 Accel;			//����
	int nLife;					//�e�̗̑�
	int nType;					//���
	int nCntDelay;				//�����J�E���g����J�E���^�[
	int nCounterAnim;
	int nPatternAnim;
	bool bUse;					//�e���g���Ă��邩�ǂ���
}Bullet;

//�v���g�^�C�v�錾
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 acc, int type);

#endif _BULLET_H_