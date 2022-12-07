#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"
#include "main.h"
#include "player.h"
#include "score.h"

#define MAX_ITEM		(12)

//�A�C�e���̎��
typedef enum
{
	ITEMTYPE_NULL = 0,		//�A�C�e�����Ȃ�
	ITEMTYPE_CARD,			//���e
	ITEMTYPE_MAX
}ITEMTYPE;

//�A�C�e���\���̂̐ݒ�
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;
	D3DXVECTOR3 EqPoint;
	int nCntAnim;
	int nType;				//���
	bool bUse;				//�g�p����Ă��邩�ǂ���
}ITEM;

//�v���g�^�C�v�錾
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 move, int type);

#endif _ITEM_H_