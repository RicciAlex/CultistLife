#ifndef _BOSS_H_
#define _BOSS_H_

//�C���N���[�h�t�@�C��
#include "main.h"
#include "player.h"
#include "Enemy.h"
#include "bullet.h"
#include "minion.h"
#include "boss.h"
#include "sound.h"
#include "scorechange.h"

//�{�X�̏��
typedef enum
{
	BOSS_STATE_APPEAR = 0,			//�������
	BOSS_STATE_SLEEP,
	BOSS_STATE_NORMAL,				//����
	BOSS_STATE_ATTACK,				//�U�����
	BOSS_STATE_DAMAGE,				//�_���[�W���
	BOSS_STATE_DEATH,				//���񂾏��
	BOSS_STATE_MAX
}BOSS_STATE;

//�G�̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;							//�ʒu
	D3DXVECTOR3 move;							//�ړ���
	D3DXVECTOR3 LastPos;						//�O��̈ʒu
	MOVESTATE MoveState;						//�ړ����
	int nType;									//���
	//ENEMYSTATE_ENCOUNTER EncounterState;
	//float fSight;								//����
	float fHeight;								//����
	BOSS_STATE BossState;							//���
	int nCounterState;						//��ԊǗ��J�E���^�[
	int nCounterShoot;						//�e�̔����̃J�E���^�[
	int nCountAnim;								//�A�j���[�V�����J�E���^�[
	int nPatternAnim;							//�A�j���[�V�����p�^�[��
	int nChaseCounter;							//�ǂ�������J�E���^�[
	bool bDamage;								//����
	int nLife;								    //�̗�
	bool bUse;									//�g�p����Ă��邩�ǂ���
}Boss;

//�v���g�^�C�v�錾
void InitBoss(void);
void UninitBoss(void);
void UpdateBoss(void);
void DrawBoss(void);
void SetBoss(D3DXVECTOR3 pos, int type);
void UpdateSlimeSnake(void);
void UpdateTarotMaster(void);
void UpdateBossTex(int nSheetLine, float nU, float nV);
Boss*GetBoss(void);

#endif  _BOSS_H_