#ifndef _PLATFORM_H_
#define _PLATFORM_H_

//�C���N���[�h�t�@�C��
#include "main.h"
#include "water.h"
#include "switch.h"
#include "player.h"
#include "switch.h"
#include "Item.h"
#include "arrow.h"

//�}�N����`
#define MAX_PLATFORM		(256)					//�v���b�g�t�H�[���̍ő吔

//�v���b�g�t�H�[���\���̂̐ݒ�
typedef struct
{
	D3DXVECTOR3 Pos;		//�v���b�g�t�H�[���̈ʒu
	D3DXVECTOR3 move;		//�ړ���
	D3DXVECTOR3 Memorymove;	//�ړ��ʂ�ۑ����邽�߂̕ϐ�
	float fwidth;			//�v���b�g�t�H�[���̕�
	float fHeight;			//�v���b�g�t�H�[���̍���
	float fMaxX;			
	float fMinX;			
	float fMaxY;				
	float fMinY;			
	int nType;				//�v���b�g�t�H�[���̎��
	int nMemory;			
	int nCntStatus;			
	bool bUse;				//�v���b�g�t�H�[�����g�p����Ă��邩�ǂ���
}PLATFORM;

//�v���g�^�C�v�錾
void InitPlatform(void);
void UninitPlatform(void);
void UpdatePlatform(void);
void DrawPlatform(void);
void SetPlatform(D3DXVECTOR3 pos, D3DXVECTOR3 move, float width, float height, int type,
				float fMaxX, float fMinX, float fMaxY, float fMinY);
PLATFORM*GetPlatform(void);
int BlockInteraction(D3DXVECTOR3*pPos,
	D3DXVECTOR3*pLastPos,
	D3DXVECTOR3*pMove,
	float fWidth,
	float fHeight);
int BlockInteractionBullet(D3DXVECTOR3*pPos,
	D3DXVECTOR3*pLastPos,
	D3DXVECTOR3*pMove,
	float fWidth,
	float fHeight);
void FirstStage(void);
void SecondStage(void);
void ThirdStage(void);
void BonusStage(void);
void FourthStage(void);
void FifthStage(void);

#endif // !_PLATFORM_H_
