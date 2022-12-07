#ifndef _ENEMY_H_
#define _ENEMY_H_

//�C���N���[�h�t�@�C��
#include "main.h"
#include "player.h"
#include "boss.h"
#include "water.h"
#include "score.h"
#include "bullet.h"
#include "scorechange.h"

//�}�N����`
#define MAX_ENEMY		(128)		//�G�̍ő吔

//�G�̏��
typedef enum
{
	ENEMYSTATE_NORMAL = 0,			//�ʏ���
	//ENEMYSTATE_DAMAGE,				//�_���[�W���
	ENEMYSTATE_APPEAR,				//�����������
	ENEMYSTATE_DEATH,				//���񂾏��
	/*ENEMYSTATE_CHARGE,
	ENEMYSTATE_EXPLODE,*/
	ENEMYSTATE_MAX
}ENEMYSTATE;

//�G�̎��
typedef enum
{
	ENEMYTYPE_BLUESLIME = 0,			//�X���C��
	ENEMYTYPE_GREENSLIME,				//�΃X���C��
	ENEMYTYPE_SLIMEBAT,					//��������X���C��
	ENEMYTYPE_MIMIC,
	ENEMYTYPE_CARD_HEART,
	ENEMYTYPE_CARD_DIAMOND,
	ENEMYTYPE_CARD_CLUB,
	ENEMYTYPE_CARD_SPADE,
	ENEMYTYPE_MAX
}ENEMYTYPE;

//�v���C���[���������ǂ����̏��
typedef enum
{
	ENEMYSTATE_ENCOUNTER_FALSE = 0,				//�v���C���[�������Ȃ����
	ENEMYSTATE_ENCOUNTER_TRUE,					//�v���C���[���������
	ENEMYSTATE_ENCOUNTER_LOST,					//�v���C���[�������Ȃ��Ȃ�����ԁ@(�܂��o���Ă��Ȃ�)
	ENEMYSTATE_ENCOUNTER_MAX
}ENEMYSTATE_ENCOUNTER;

//�G�̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;							//�ʒu
	D3DXVECTOR3 move;							//�ړ���
	D3DXVECTOR3 LastPos;						//�O��̈ʒu
	MOVESTATE MoveState;						//�ړ����
	ENEMYTYPE nType;							//���
	ENEMYSTATE_ENCOUNTER EncounterState;		
	ENEMYSTATE state;							//�G�̏��
	float fSight;								//����
	float fHeight;								//����
	float fWidth;								//��
	//ENEMYSTATE state;							//���
	int nCounterState;						//��ԊǗ��J�E���^�[
	//int nCounterShoot;						//�e�̔����̃J�E���^�[
	int nCountAnim;								//�A�j���[�V�����J�E���^�[
	int nPatternAnim;							//�A�j���[�V�����p�^�[��
	int nChaseCounter;							//�ǂ�������J�E���^�[
	int nCurrentPlatform;						//���݂̃v���b�g�t�H�[��
	int nDirection;								//����
	//int nLife;								//�̗�
	bool bUse;									//�g�p����Ă��邩�ǂ���
}Enemy;

//�v���g�^�C�v�錾
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, ENEMYTYPE nType);
void WarpEnemy(int nCntEnemy);
void SlimeAnimation(int nCntEnemy);
void MimicAnimation(int nCntEnemy);
void CardAnimation(int nCntEnemy);
void UpdateEnemyTex(int nCntEnemy, int nSheetLine, float nU, float nV);
void EnemyEncounter(int nCntEnemy, float Height);
Enemy*GetEnemy(void);
void SpawnEnemy(void)
/*
void HitEnemy(int nCntEnemy, int nDamage);
*/;

#endif _ENEMY_H_
