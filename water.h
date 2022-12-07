#ifndef _WATER_H_
#define _WATER_H_

//�C���N���[�h�t�@�C��
#include "main.h"
#include "input.h"

//�}�N����`
#define MAX_WATER		(24)			//����̂̍ő吔

//���̏��
typedef enum
{
	WATERSTATE_READY = 0,				//�J�����Ƃ��ł�����
	WATERSTATE_OPEN,					//����Ă�����
	WATERSTATE_CLOSING,					//���܂��Ă�����
	WATERSTATE_MAX

}WATERSTATE;

//���̍\����
typedef struct
{
	D3DXVECTOR3 pos;					//�ʒu
	float fWidth;						//��
	float fHeight;						//����
	int nType;							//���
	int nNumSwitch;						//�X�C�b�`�̔ԍ�
	WATERSTATE wState;					//���
	bool bUse;							//�g�p����Ă��邩�ǂ���
}WATER;

//�v���g�^�C�v�錾
void InitWater(void);
void UninitWater(void);
void UpdateWater(void);
void DrawWater(void);
void SetWater(D3DXVECTOR3 pos, int type, float width, float height, int nSwitch, WATERSTATE state);
int WaterInteraction(D3DXVECTOR3*pPos,			//���݂̈ʒu
	D3DXVECTOR3*pMove,							//�ړ���
	float fWidth,								//��
	float fHeight);								//����);
WATER*GetWater(void);

#endif // !_WATER_H_