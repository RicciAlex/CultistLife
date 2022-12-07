#ifndef _PLAYER_H_
#define _PLAYER_H_

//�C���N���[�h�t�@�C��
#include "main.h"
#include "platform.h"

//�}�N����`
#define PLAYER_HEIGHT	(75.0f)					//�v���C���[�̍���
#define PLAYER_WIDTH	(50.0f)					//�v���C���[�̕�

//�v���C���[�̏��
typedef enum
{
	PLAYERSTATE_NORMAL = 0,						//���ʏ��
	PLAYERSTATE_DAMAGE,							//�_���[�W���
	PLAYERSTATE_WIN,
	PLAYERSTATE_DEATH,
	PLAYERSTATE_MAX
}PLAYERSTATE;

//�ړ����
typedef enum
{
	MOVESTATE_LANDED = 0,			//���n
	MOVESTATE_JUMP,				//�W�����v
	MOVESTATE_FALLING,			//����
	MOVESTATE_MAX
}MOVESTATE;

//�v���C���[�\���̂̐ݒ�
typedef struct
{
	D3DXVECTOR3 pos;								//�ʒu
	D3DXVECTOR3 move;								//�ړ���
	D3DXVECTOR3 LastPos;								//�v���C���[�̑O��̈ʒu
	//D3DXVECTOR3 rotPlayer;							//����
	PLAYERSTATE state;								//�v���C���[�̏��
	int nCounterState;								//��ԊǗ��̃J�E���^�[
	int nCounterAnim;								//�A�j���[�V�����̃J�E���^�[
	int nPatternAnim;								//�A�j���[�V�����p�^�[��
	int nDirectionMove;								//����
	MOVESTATE MoveState;						//�ړ����
	int nCurrentPlatform;						//���݂̃v���b�g�t�H�[��
	//int nCurrentPlatform;
	//float fLengthPlayer;							//�Ίp���̒���
	//float fAnglePlayer;								//�Ίp���̊p�x
	//int nLife;										//�̗�
	//int nItem;										//�A�C�e��
	//bool bDisp;										//�g�p����Ă��邩�ǂ���
}Player;


//�v���g�^�C�v�錾
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player*GetPlayer(void);
bool GetWin(void);

#endif // !_PLAYER_H_