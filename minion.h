#ifndef _MINION_H_
#define _MINION_H_

//�C���N���[�h�t�@�C��
#include "main.h"
#include "boss.h"
#include "explosion.h"
#include "bullet.h"
#include "scorechange.h"

//�}�N����`
#define MAX_MINION		(16)		//�G�̍ő吔

//�G�̏��
typedef enum
{
	MINIONSTATE_NORMAL = 0,				//�ʏ���
	MINIONSTATE_ATTACK,
	MINIONSTATE_RETURN,
	MINIONSTATE_EXPLODE,				//����������
	MINIONSTATE_APPEAR,
	MINIONSTATE_MAX
}MINIONSTATE;

//�G�̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;							//�ʒu
	D3DXVECTOR3 move;							//�ړ���
	D3DXVECTOR3 LastPos;						//�O��̈ʒu
	MINIONSTATE state;							//���	
	float fHeight;								//����
	float fWidth;								//��
	int nType;									//���
	int nCounterState;						//��ԊǗ��J�E���^�[
	int nCountAnim;								//�A�j���[�V�����J�E���^�[
	int nPatternAnim;							//�A�j���[�V�����p�^�[��
	int nDirection;								//����
	bool bUse;									//�g�p����Ă��邩�ǂ���
}Minion;

//�v���g�^�C�v�錾
void InitMinion(void);
void UninitMinion(void);
void UpdateMinion(void);
void DrawMinion(void);
void SetMinion(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nType);
void UpdateBombBat(void);
void UpdateTarotSummon(void);
Minion*GetMinion(void);

#endif _MINION_H_
