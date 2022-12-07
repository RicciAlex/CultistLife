//==========================================//
//                                          //
//             �{�X�̃t�@�C��               //
//�@�@�@�@�@�@ Author: Ricci Alex           //
//                                          //
//==========================================//

//�C���N���[�h�t�@�C��
#include "boss.h"
#include <time.h>

//�O���[�o���ϐ���錾
LPDIRECT3DTEXTURE9 g_apTextureBoss;						//�{�X�̃e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_apTextureSnakeSlime;				//�X���C���{�X�̃e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_apTextureTarotMaster;				//�^���b�g�{�X�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBoss = NULL;			//���_�o�b�t�@�ւ̃|�C���^
Boss g_Boss;											//�{�X�^�̔z���錾����

//�{�X�̏���������
void InitBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̏��ւ̃|�C���^
	VERTEX_2D*pVtx;					//���_���ւ̃|�C���^

	pDevice = GetDevice();			//�f�o�C�X�̏��̎擾

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\SlimeBlue_SpriteSheet2.png",
		&g_apTextureBoss);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\GigantSnakeSlimeSprite.png",
		&g_apTextureSnakeSlime);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\TarotMaster_Sprite.png",
		&g_apTextureTarotMaster);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBoss,
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);

	//�{�X�^�̕ϐ��̊e�p�����[�^�̏�����
	g_Boss.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//���݂̈ʒu
	g_Boss.LastPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�O��̈ʒu
	g_Boss.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�ړ���
	g_Boss.MoveState = MOVESTATE_FALLING;						//�ړ����
	g_Boss.BossState = BOSS_STATE_APPEAR;						//�{�X�̏��
	g_Boss.fHeight = 50.0f;										//����
	g_Boss.nCountAnim = 0;										//�A�j���[�V�����J�E���^�[
	g_Boss.nPatternAnim = 0;									//�A�j���[�V�����p�^�[��
	g_Boss.nChaseCounter = 0;									//�ǂ�������J�E���^�[
	g_Boss.bDamage = false;										//����
	g_Boss.nCounterShoot = 0;									//�{�X�̒e���˂̃J�E���^�[
	g_Boss.nCounterState = 0;									//�{�X�̏�ԃJ�E���^�[
	g_Boss.nLife = 3;											//�̗�
	g_Boss.nType = 0;											//���
	g_Boss.bUse = false;										//�g�p����Ă��邩�ǂ���

	//���_�ݒ�
	pVtx[1].pos = D3DXVECTOR3(g_Boss.pos.x + 50.0f, g_Boss.pos.y - 100.0f, 0.0f);
	pVtx[0].pos = D3DXVECTOR3(g_Boss.pos.x - 50.0f, g_Boss.pos.y - 100.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Boss.pos.x + 50.0f, g_Boss.pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Boss.pos.x - 50.0f, g_Boss.pos.y, 0.0f);

	//rhw�ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[3].tex = D3DXVECTOR2(0.0f, 0.125f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.125f, 0.125f);
	pVtx[0].tex = D3DXVECTOR2(0.125f, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBoss->Unlock();
}

//�{�X�̏I������
void UninitBoss(void)
{
	//�e�N�X�`���̔j��
	if (g_apTextureBoss != NULL)
	{
		g_apTextureBoss->Release();
		g_apTextureBoss = NULL;
	}
	if (g_apTextureSnakeSlime != NULL)
	{			   
		g_apTextureSnakeSlime->Release();
		g_apTextureSnakeSlime = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBoss != NULL)
	{
		g_pVtxBuffBoss->Release();
		g_pVtxBuffBoss = NULL;
	}
}

//�{�X�̍X�V����
void UpdateBoss(void)
{
	if (g_Boss.bUse == true)
	{//�g�p����Ă���ꍇ

		if (g_Boss.nType == 1)
		{//�X���C���{�X�̏ꍇ
			UpdateSlimeSnake();
		}
		else if (g_Boss.nType == 2)
		{//�^���b�g�{�X�̏ꍇ
			UpdateTarotMaster();
		}
	}
}

//�{�X�̕`�揈��
void DrawBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̏��ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBoss, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_Boss.bUse == true)
	{
		if (g_Boss.nType == 0)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureBoss);
		}
		else if (g_Boss.nType == 1)
		{//�X���C���{�X�̏ꍇ
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureSnakeSlime);
		}
		else if (g_Boss.nType == 2)
		{//�^���b�g�{�X�̏ꍇ
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureTarotMaster);
		}

		//�l�p�`��`�悷��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//�{�X�̐ݒ�
void SetBoss(D3DXVECTOR3 pos, int type)
{

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);

	if (g_Boss.bUse == false)
	{
		g_Boss.pos = pos;			//���݂̈ʒu�̐ݒ�
		g_Boss.LastPos = pos;		//�O��̈ʒu�̈ʒu
		g_Boss.nType = type;		//��ނ̐ݒ�
		g_Boss.bUse = true;			//�g�p����Ă����Ԃɂ���

		if (type == 0)
		{
			//���_�ݒ�
			pVtx[1].pos = D3DXVECTOR3(g_Boss.pos.x + 50.0f, g_Boss.pos.y - 100.0f, 0.0f);
			pVtx[0].pos = D3DXVECTOR3(g_Boss.pos.x - 50.0f, g_Boss.pos.y - 100.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Boss.pos.x + 50.0f, g_Boss.pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Boss.pos.x - 50.0f, g_Boss.pos.y, 0.0f);

			//�e�N�X�`�����W�̐ݒ�
			pVtx[3].tex = D3DXVECTOR2(0.0f, 0.125f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.125f, 0.125f);
			pVtx[0].tex = D3DXVECTOR2(0.125f, 0.0f);
		}
		else if (type == 1)
		{//�X���C���{�X�̏ꍇ
			g_Boss.nCountAnim = 30;

			//���_�ݒ�
			pVtx[1].pos = D3DXVECTOR3(g_Boss.pos.x + 150.0f, g_Boss.pos.y, 0.0f);
			pVtx[0].pos = D3DXVECTOR3(g_Boss.pos.x - 150.0f, g_Boss.pos.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Boss.pos.x + 150.0f, g_Boss.pos.y + 400.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Boss.pos.x - 150.0f, g_Boss.pos.y + 400.0f, 0.0f);

			//�e�N�X�`�����W�̐ݒ�
			pVtx[3].tex = D3DXVECTOR2(0.5, 0.25);
			pVtx[1].tex = D3DXVECTOR2(0.5, 0.0);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 0.25);
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
		}
		else if (type == 2)
		{//�^���b�g�{�X�̏ꍇ
			g_Boss.BossState = BOSS_STATE_SLEEP;				//�{�X�̏��

			g_Boss.nLife = 5;									//�{�X�̗̑�

			//���_�ݒ�
			pVtx[1].pos = D3DXVECTOR3(g_Boss.pos.x + 50.0f, g_Boss.pos.y - 100, 0.0f);
			pVtx[0].pos = D3DXVECTOR3(g_Boss.pos.x - 50.0f, g_Boss.pos.y - 100, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Boss.pos.x + 50.0f, g_Boss.pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Boss.pos.x - 50.0f, g_Boss.pos.y, 0.0f);

			//�e�N�X�`�����W�̐ݒ�
			pVtx[3].tex = D3DXVECTOR2(0.125, 0.125);
			pVtx[1].tex = D3DXVECTOR2(0.125, 0.0);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 0.125);
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBoss->Unlock();
}

//�X���C���{�X�̍X�V����
void UpdateSlimeSnake(void)
{
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^
	Player*pPlayer;		//�v���C���[�̏��ւ̃|�C���^
	bool bEnd = false;	
	int*pSwitch;		//�X�C�b�`���ւ̃|�C���^

	pSwitch = GetActiveSwitch();	//�X�C�b�`���̎擾
	pPlayer = GetPlayer();			//�v���C���[�̏��̎擾

	int nInteraction = 0;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);

	if (g_Boss.BossState == BOSS_STATE_APPEAR)
	{//��������ꍇ

		//�A�j���[�V��������
		if (g_Boss.nCountAnim > 0)
		{
			g_Boss.nCountAnim--;
		}
		if (g_Boss.nCountAnim <= 0)
		{
			g_Boss.move.y = -1.0f;
		}

		if (g_Boss.pos.y <= 500.0f)
		{
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			g_Boss.nCountAnim = 0;								//�A�j���[�V�����J�E���^�[���O�ɂ���
			g_Boss.move.y = 0.0f;								//Y���W�̈ړ��ʂ��O�ɂ���
			g_Boss.BossState = BOSS_STATE_NORMAL;				//���ʏ�Ԃɂ���
			PlaySound(SOUND_LABEL_BGMBOSS);						//�{�XBGM���Đ�����
		}

		//�e�N�X�`�����W�̐ݒ�
		pVtx[3].tex = D3DXVECTOR2(0.5, 0.25);
		pVtx[1].tex = D3DXVECTOR2(0.5, 0.0);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.25);
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	}
	if (g_Boss.BossState == BOSS_STATE_NORMAL)
	{//���ʂ̏�Ԃ̏ꍇ
		//�A�j���V��������
		g_Boss.nCountAnim++;

		if (g_Boss.nCounterShoot > 0)
		{//�e�̔����J�E���^�[
			g_Boss.nCounterShoot--;
		}

		if (*pSwitch == 4)
		{
			//�G�̐ݒ�
			SetMinion(D3DXVECTOR3(0.0f, 370.0f, 0.0f), D3DXVECTOR3(2.0f, 0.0f, 0.0f), 0);
			SetMinion(D3DXVECTOR3(1280.0f, 370.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 0);
			*pSwitch = 0;
		}

		if (g_Boss.nCounterShoot <= 0 && pPlayer->pos.y <= 250.0f)
		{//�v���C���[�����ڂɍU���ł���͈͈ȊO��������A�e����
			PlaySound(SOUND_LABEL_SE_NORMALBULLET);
			SetBullet(D3DXVECTOR3(g_Boss.pos.x, g_Boss.pos.y + 5.0f, 0.0f), D3DXVECTOR3(0.0f, -8.0f, 0.0f), D3DXVECTOR3(0.0f, 0.08f, 0.0f), 0);
			SetBullet(D3DXVECTOR3(g_Boss.pos.x, g_Boss.pos.y + 5.0f, 0.0f), D3DXVECTOR3(2.07f, -8.0f, 0.0f), D3DXVECTOR3(0.0f, 0.08f, 0.0f), 0);
			SetBullet(D3DXVECTOR3(g_Boss.pos.x, g_Boss.pos.y + 5.0f, 0.0f), D3DXVECTOR3(-2.07f, -8.0f, 0.0f), D3DXVECTOR3(0.0f, 0.08f, 0.0f), 0);

			g_Boss.nCounterShoot = 120;						//�e�̔����J�E���^�[�̐ݒ�
		}

		//=====================================================================================================================================================
		//													�A�j���V��������
		if (g_Boss.nCountAnim % 30 == 29)
		{
			g_Boss.nPatternAnim++;

			if (g_Boss.nPatternAnim == 4)
			{
				g_Boss.nPatternAnim = 0;
			}

			if (g_Boss.nPatternAnim == 0 || g_Boss.nPatternAnim == 2)
			{
				g_Boss.move.y = -0.25f;
			}
			else if (g_Boss.nPatternAnim == 1 || g_Boss.nPatternAnim == 3)
			{
				g_Boss.move.y = 0.25f;
			}

			if (g_Boss.pos.x + 75.0f <= pPlayer->pos.x)
			{
				g_Boss.move.x = 1.0f;
			}
			else if (g_Boss.pos.x - 75.0f >= pPlayer->pos.x)
			{
				g_Boss.move.x = -1.0f;
			}
			//=====================================================================================================================================================
			//=====================================================================================================================================================
			//									�v���C���[�͍U���ł���͈͂ŁA�{�X�̏�ɂ���ꍇ�A�U����Ԃɂ���
			if (g_Boss.pos.x + 75.0f >= pPlayer->pos.x && g_Boss.pos.x - 75.0f <= pPlayer->pos.x)
			{
				if (pPlayer->pos.y >= 250.0f)
				{
					g_Boss.BossState = BOSS_STATE_ATTACK;				//�U����Ԃɂ���
					g_Boss.nChaseCounter = 100.0f;						//�ǂ�������J�E���^�[�̐ݒ�
					g_Boss.nCountAnim = 0;								//�A�j���[�V�����J�E���^�[�̐ݒ�
					g_Boss.nPatternAnim = 0;							//�A�j���[�V�����p�^�[���̐ݒ�
					g_Boss.move.x = 0.0f;								//�ړ��ʂ��O�ɂ���
					g_Boss.move.y = 0.0f;								//�ړ��ʂ��O�ɂ���
				}

			}
		}

		//�e�N�X�`�����W�̐ݒ�
		pVtx[3].tex = D3DXVECTOR2(0.5, 0.25 + (0.25f * g_Boss.nPatternAnim));
		pVtx[1].tex = D3DXVECTOR2(0.5, 0.0 + (0.25f * g_Boss.nPatternAnim));
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.25 + (0.25f * g_Boss.nPatternAnim));
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f + (0.25f * g_Boss.nPatternAnim));
	}
	//===========================================================================================================================================================================================
	//===========================================================================================================================================================================================
	//																				�U����Ԃ̏ꍇ
	else if (g_Boss.BossState == BOSS_STATE_ATTACK)
	{
		g_Boss.nChaseCounter--;

		if (g_Boss.nChaseCounter >= 70)
		{//��Ɉړ�
			g_Boss.move.y = -8.0f;
		}
		else if (g_Boss.nChaseCounter >= 30 && g_Boss.nChaseCounter < 70)
		{//�����Ȃ�
			g_Boss.move.y = 0.0f;
		}
		else if (g_Boss.nChaseCounter < 30 && g_Boss.nChaseCounter >= 0)
		{//���ɖ߂�
			g_Boss.move.y = 8.0f;
		}
		else if (g_Boss.nChaseCounter < 0)
		{//���ʏ�Ԃɖ߂�
			g_Boss.move.y = 0.0f;								//�ړ��ʂ��O�ɂ���
			g_Boss.move.x = 0.0f;								//�ړ��ʂ��O�ɂ���
			g_Boss.pos.y = 500.0f;								//Y���W�̈ʒu�̐ݒ�
			g_Boss.nChaseCounter = 0;							//�U���J�E���^�[���O�ɂ���
			g_Boss.BossState = BOSS_STATE_NORMAL;				//���ʏ�Ԃɂ���

			if (g_Boss.bDamage == true)
			{//��������G�ɓ��������ꍇ
				g_Boss.nCounterState = 10;						//��ԃJ�E���^�[�̐ݒ�
				g_Boss.BossState = BOSS_STATE_DAMAGE;			//�_���[�W��Ԃɂ���
			}
		}

		//===========================================================================================================================================================================================
		//																					�v���C���[�ɓ��������ꍇ
		if (pPlayer->pos.y > g_Boss.pos.y && pPlayer->pos.x >= g_Boss.pos.x - 100.0f && pPlayer->pos.x <= g_Boss.pos.x + 100.0f && pPlayer->state != PLAYERSTATE_DAMAGE &&pPlayer->state != PLAYERSTATE_DEATH)
		{
			pPlayer->state = PLAYERSTATE_DAMAGE;					//�v���C���[���_���[�W��Ԃɂ���
			pPlayer->nCounterState = 180;							//��ԃJ�E���^�[�̐ݒ�
			AddScore(-500);											//�X�R�A��������
			PlaySound(SOUND_LABEL_SE_NORMALDAMAGE);					//�_���[�W�T�E���h���Đ�����
			SetSChange(D3DXVECTOR3(pPlayer->pos.x - (50.0f * pPlayer->nDirectionMove), pPlayer->pos.y - PLAYER_HEIGHT, 0.0f), D3DXVECTOR3(pPlayer->move.x, pPlayer->move.y, 0.0f), 0, CHANGEVALUE_MINUS500);
		}

		//�e�N�X�`�����W�̐ݒ�
		pVtx[3].tex = D3DXVECTOR2(0.5f, 0.25f);
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.25f);
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);

	}
	//===========================================================================================================================================================================================
	//																						�_���[�W��Ԃ̏ꍇ
	else if (g_Boss.BossState == BOSS_STATE_DAMAGE)
	{
		g_Boss.nCounterState--;										//�F�A�j���[�V�����J�E���^�[�̍X�V

		if (g_Boss.nCounterState == 1)
		{
			PlaySound(SOUND_LABEL_SE_EXPLOSION);					//�����T�E���h���Đ�
		}
		else if (g_Boss.nCounterState <= 0)
		{//�A�j���[�V��������
			g_Boss.nCountAnim++;

			if (g_Boss.nCountAnim % 8 == 7)
			{
				//���_�J���[�̍X�V
				if (g_Boss.nPatternAnim == 0)
				{
					g_Boss.nPatternAnim = 1;

					pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				}
				else
				{
					g_Boss.nPatternAnim = 0;

					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				}
				if (g_Boss.nCountAnim >= 120)
				{//�_���[�W��^���āA�̗͂̔���
					g_Boss.nLife--;						//�̗͂�������
					g_Boss.nPatternAnim = 0;			//�A�j���[�V�����p�^�[�����O�ɂ���
					g_Boss.nCountAnim = 0;				//�A�j���[�V�����J�E���^�[���O�ɂ���
					g_Boss.bDamage = false;				

					if (g_Boss.nLife <= 0)
					{//�̗͂�0�ɂȂ����ꍇ
						g_Boss.BossState = BOSS_STATE_DEATH;		//���񂾏�Ԃɂ���
						g_Boss.nCounterState = 150;					//�A�j���[�V�����J�E���^�[�̐ݒ�
					}
					else
					{//�̗͂͂O�łȂ��ꍇ
						g_Boss.BossState = BOSS_STATE_NORMAL;		//���ʏ�Ԃɖ߂�
					}
					//���_�J���[�̍X�V
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				}
			}
			//�e�N�X�`�����W�̐ݒ�
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0.25 + (0.25f * g_Boss.nPatternAnim));
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0 + (0.25f * g_Boss.nPatternAnim));
			pVtx[2].tex = D3DXVECTOR2(0.5f, 0.25 + (0.25f * g_Boss.nPatternAnim));
			pVtx[0].tex = D3DXVECTOR2(0.5f, 0.0f + (0.25f * g_Boss.nPatternAnim));
		}
		else
		{
			//�e�N�X�`�����W�̐ݒ�
			pVtx[3].tex = D3DXVECTOR2(0.5f, 0.25f);
			pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 0.25f);
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		}
	}
	//===========================================================================================================================================================================================
	//===========================================================================================================================================================================================
	//																							���񂾂�
	else if (g_Boss.BossState == BOSS_STATE_DEATH)
	{
		g_Boss.nCounterState--;								//�X�e�[�^�X�J�E���^�[�̍X�V
		g_Boss.move = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		//�ړ��ʂ̍X�V

		//�A�j���[�V��������
		g_Boss.nCountAnim++;

		if (g_Boss.nCountAnim % 8 == 7)
		{
			if (g_Boss.nPatternAnim == 0)
			{
				g_Boss.nPatternAnim = 1;

				//���_�J���[�̍X�V
				pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			}
			else
			{
				g_Boss.nPatternAnim = 0;

				//���_�J���[�̍X�V
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}

			//�e�N�X�`�����W�̐ݒ�
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0.25 + (0.25f * g_Boss.nPatternAnim));
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0 + (0.25f * g_Boss.nPatternAnim));
			pVtx[2].tex = D3DXVECTOR2(0.5f, 0.25 + (0.25f * g_Boss.nPatternAnim));
			pVtx[0].tex = D3DXVECTOR2(0.5f, 0.0f + (0.25f * g_Boss.nPatternAnim));
		}
		if (g_Boss.nCounterState <= 0)
		{
			g_Boss.nCountAnim = 0;
			g_Boss.nPatternAnim = 0;
			g_Boss.nCounterState = 0;

			//���_�J���[�̍X�V
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			bEnd = true;
			AddScore(10000);
			g_Boss.bUse = false;					//�g�p����Ă��Ȃ���Ԃɂ���
		}
	}

	//�{�X�̈ʒu�̍X�V
	g_Boss.pos += g_Boss.move;


	//���_�ݒ�
	pVtx[1].pos = D3DXVECTOR3(g_Boss.pos.x + 150.0f, g_Boss.pos.y, 0.0f);
	pVtx[0].pos = D3DXVECTOR3(g_Boss.pos.x - 150.0f, g_Boss.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Boss.pos.x + 150.0f, g_Boss.pos.y + 400.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Boss.pos.x - 150.0f, g_Boss.pos.y + 400.0f, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBoss->Unlock();

	if (bEnd == true)
	{//�{�X�����񂾂�A�v���C���[����������Ԃɂ���
		pPlayer->state = PLAYERSTATE_WIN;
	}
}

//�^���b�g�{�X�̍X�V����
void UpdateTarotMaster(void)
{
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^
	Player*pPlayer;		//�v���X���ւ̃|�C���^
	bool bEnd = false;	
	int*pSwitch;		//�X�C�b�`���ւ̃|�C���^
	Minion*pMinion;		//�G���ւ̃|�C���^

	pMinion = GetMinion();			//�G�̏����擾
	pPlayer = GetPlayer();			//�v���C���[�̏��̎擾
	pSwitch = GetActiveSwitch();	//�X�C�b�`���̎擾

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);

	//===========================================================================================================================================================================================
	//																						�Q�Ă����Ԃ̏ꍇ
	if (g_Boss.BossState == BOSS_STATE_SLEEP)
	{
		if (/*pPlayer->pos.x > 500.0f && pPlayer->pos.x < 780.0f && pPlayer->pos.y > 530.0f*/
			(pPlayer->pos.x - g_Boss.pos.x) * (pPlayer->pos.x - g_Boss.pos.x) + (pPlayer->pos.y - g_Boss.pos.y) * (pPlayer->pos.y - g_Boss.pos.y) < 160000)
		{
			g_Boss.BossState = BOSS_STATE_APPEAR;						//������Ԃɂ���
			g_Boss.nPatternAnim++;										//�A�j���[�V�����p�^�[���̍X�V
		}
	}
	//===========================================================================================================================================================================================
	//===========================================================================================================================================================================================
	//																						������Ԃ̏ꍇ
	if (g_Boss.BossState == BOSS_STATE_APPEAR)
	{
		//�A�j���[�V��������
		g_Boss.nCountAnim++;

		switch (g_Boss.nPatternAnim)
		{
		case 1:
			if (g_Boss.nCountAnim % 15 == 14)
			{
				g_Boss.nPatternAnim++;
				g_Boss.nCountAnim = 0;
				PlaySound(SOUND_LABEL_BGMBOSS);						//�{�X�T�E���h���Đ�����
			}
			break;

		case 2:
			if (g_Boss.nCountAnim % 60 == 59)
			{
				g_Boss.nPatternAnim++;
				g_Boss.nCountAnim = 0;
			}
			break;

		case 3:
			if (g_Boss.nCountAnim % 10 == 9)
			{
				g_Boss.nPatternAnim++;
				g_Boss.nCountAnim = 0;
			}
			break;

		case 4:
			if (g_Boss.nCountAnim % 60 == 59)
			{
				g_Boss.nPatternAnim++;
				g_Boss.nCountAnim = 0;
			}
			break;

		case 5:
			if (g_Boss.nCountAnim % 30 == 29)
			{//�A�j���[�V�������I�������
				g_Boss.BossState = BOSS_STATE_ATTACK;					//�U����Ԃɂ���
				g_Boss.nPatternAnim = 0;								//�A�j���[�V�����p�^�[�����O�ɂ���
				g_Boss.nCountAnim = 0;									//�A�j���[�V�����J�E���^�[���O�ɂ���
				*pSwitch = 0;											//�X�C�b�`���g���Ă��Ȃ���Ԃɂ���
			}
			break;
		}
		//�e�N�X�`�����W�̍X�V
		if (g_Boss.BossState == BOSS_STATE_APPEAR)
		{
			UpdateBossTex(0, 0.125f, 0.125f);
		}
	}
	//===========================================================================================================================================================================================
	//===========================================================================================================================================================================================
	//																				�U����Ԃ̏ꍇ
	else if (g_Boss.BossState == BOSS_STATE_ATTACK)
	{//�U����Ԃ̏ꍇ

		//�A�j���V��������
		g_Boss.nCountAnim++;

		if (g_Boss.nCountAnim % 30 == 29)
		{
			if (g_Boss.nLife == 5 && g_Boss.nPatternAnim < 4 || g_Boss.nLife < 5 && g_Boss.nPatternAnim < 6)
			{
				g_Boss.nPatternAnim++;

				if (g_Boss.nPatternAnim == 5)
				{
					*pSwitch = 0;
				}

				if (g_Boss.nLife == 5 && g_Boss.nPatternAnim == 4 || g_Boss.nLife < 5 && g_Boss.nPatternAnim == 6)
				{
					switch (g_Boss.nLife)
					{
					case 5:
						SetMinion(D3DXVECTOR3(810.0f, 0.0f, 0.0f), D3DXVECTOR3(-10.0f, 0.0f, 0.0f), 1);							//���
						break;
					case 4:
						SetMinion(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);								//���_
						break;
					case 3:
						SetMinion(D3DXVECTOR3(600.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2);							//�݂��ꂽ�j
						break;
					case 2:
						SetMinion(D3DXVECTOR3(200.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 5);						//���z
						break;
					case 1:
						SetMinion(D3DXVECTOR3(640.0f, SCREEN_HEIGHT + 180.0f, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), 4);		//����
						break;
					}
				}
			}
			g_Boss.nCountAnim = 0;
		}
		//�e�N�X�`�����W�̍X�V
		switch (g_Boss.nLife)
		{
		case 5:
			UpdateBossTex(1, 0.125f, 0.125f);
			break;
		case 4:
			UpdateBossTex(2, 0.125f, 0.125f);
			break;
		case 3:
			UpdateBossTex(3, 0.125f, 0.125f);
			break;
		case 2:
			UpdateBossTex(4, 0.125f, 0.125f);
			break;
		case 1:
			UpdateBossTex(5, 0.125f, 0.125f);
			break;
		}
		//===========================================================================================================================================================================================
		//																						�X�C�b�`�S���g������										
		if (*pSwitch == 8)
		{
			g_Boss.BossState = BOSS_STATE_DAMAGE;				//�_���[�W��Ԃɂ���
			g_Boss.nCounterState = 120;							//��ԃJ�E���^�[�̐ݒ�
			g_Boss.nPatternAnim = 7;							//�A�j���[�V�����p�^�[���̐ݒ�

			//���_�J���[�̍X�V
			pVtx[0].col = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f);
		}
	}
	//===========================================================================================================================================================================================
	//																							�_���[�W��Ԃ̏ꍇ
	else if (g_Boss.BossState == BOSS_STATE_DAMAGE)
	{
		g_Boss.nCounterState--;

		if (g_Boss.nCounterState % 10 == 0)
		{
			PlaySound(SOUND_LABEL_SE_FIRE);						//���̃T�E���h���Đ�

			//�e�̐ݒ�
			SetBullet(D3DXVECTOR3(g_Boss.pos.x + 25.0f, 700.0f, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 5);
			SetBullet(D3DXVECTOR3(g_Boss.pos.x - 35.0f, 700.0f, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 5);
			SetBullet(D3DXVECTOR3(g_Boss.pos.x - 5.0f, 700.0f, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 5);
		}

		if (g_Boss.nCounterState % 8 == 7)
		{
			//���_�J���[�̍X�V
			if (g_Boss.nPatternAnim == 7)
			{//����
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				g_Boss.nPatternAnim = 5;
			}
			else
			{//�Ԃ�
				pVtx[0].col = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f);

				g_Boss.nPatternAnim = 7;
			}
			//�e�N�X�`�����W�̍X�V
			if (g_Boss.nPatternAnim == 5)
			{
				UpdateBossTex(1, 0.125f, 0.125f);
			}
			else
			{
				UpdateBossTex(2, 0.125f, 0.125f);
			}
		}

		if (g_Boss.nCounterState <= 0)
		{//��ԃJ�E���^�[��0�ɂȂ�����A�̗͔��肷��
			g_Boss.nCounterState = 0;

			if (g_Boss.nLife > 1)
			{//�̗͂��O�łȂ��ꍇ
				g_Boss.nLife--;									//�̗͂̍X�V
				g_Boss.nCountAnim = 0;							//�A�j���[�V�����J�E���^�[���O�ɂ���
				g_Boss.nPatternAnim = 0;						//�A�j���[�V�����p�^�[�����O�ɂ���
				g_Boss.BossState = BOSS_STATE_ATTACK;			//�U����Ԃɂ���
				*pSwitch = 0;									//�X�C�b�`���g���Ă��Ȃ���Ԃɂ���

				//���_�J���[�𕁒ʂ̃J���[�ɖ߂�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
			else
			{//�̗͂��O�ɂȂ����ꍇ
				g_Boss.BossState = BOSS_STATE_DEATH;			//���񂾏�Ԃɂ���
				g_Boss.nCountAnim = 0;							//�A�j���[�V�����J�E���^�[���O�ɂ���
				g_Boss.nPatternAnim = 0;						//�A�j���[�V�����J�E���^�[���O�ɂ���
				g_Boss.nCounterState = 300;						//��ԃJ�E���^�[�̐ݒ�
				*pSwitch = 0;									//�X�C�b�`���g���Ă��Ȃ���Ԃɂ���

				//���_�J���[�𕁒ʂ̃J���[�ɖ߂�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
		}
	}
	//===========================================================================================================================================================================================
	//===========================================================================================================================================================================================
	//																											���񂾂�
	else if (g_Boss.BossState == BOSS_STATE_DEATH)
	{
		//�A�j���V��������
		g_Boss.nCountAnim++;
		g_Boss.nCounterState--;

		if (g_Boss.nCountAnim % 8 == 7)
		{
			g_Boss.nPatternAnim++;

			if (g_Boss.nPatternAnim >= 4)
			{
				g_Boss.nPatternAnim = 0;
			}
		}
		if (g_Boss.nCounterState == 10)
		{
			AddScore(15000);							//�X�R�A�̍X�V
		}

		//���_�J���[�̍X�V
		if (g_Boss.nPatternAnim % 2 == 0)
		{
			pVtx[0].col = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f * (g_Boss.nCounterState * 0.0033f));
			pVtx[1].col = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f * (g_Boss.nCounterState * 0.0033f));
			pVtx[2].col = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f * (g_Boss.nCounterState * 0.0033f));
			pVtx[3].col = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f * (g_Boss.nCounterState * 0.0033f));
		}
		else
		{
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f * (g_Boss.nCounterState * 0.0033f));
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f * (g_Boss.nCounterState * 0.0033f));
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f * (g_Boss.nCounterState * 0.0033f));
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f * (g_Boss.nCounterState * 0.0033f));
		}
		//�e�N�X�`�����W�̍X�V
		UpdateBossTex(6, 0.125f, 0.125f);
	}

#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_O) == true)
	{
		g_Boss.nLife--;

		g_Boss.nPatternAnim = 0;
		g_Boss.nCountAnim = 0;
	}

#endif // _DEBUG

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBoss->Unlock();

	if (g_Boss.BossState == BOSS_STATE_DEATH && g_Boss.nCounterState <= 0)
	{//���񂾂�A�v���C���[����������Ԃɂ���
		g_Boss.bUse = false;												//�{�X���g���Ă��Ȃ���Ԃɂ���
		pPlayer->state = PLAYERSTATE_WIN;									//�v���C���[����������Ԃɂ���
	}
}

//�{�X�e�N�X�`�����W�̍X�V����
void UpdateBossTex(int nSheetLine, float nU, float nV)
{
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);

	 //�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(nU + (g_Boss.nPatternAnim * nU), 0.0f + (nV * nSheetLine));
		pVtx[1].tex = D3DXVECTOR2(0.0f + (g_Boss.nPatternAnim * nU), 0.0f + (nV * nSheetLine));
		pVtx[2].tex = D3DXVECTOR2(nU + (g_Boss.nPatternAnim * nU), nV + (nV * nSheetLine));
		pVtx[3].tex = D3DXVECTOR2(0.0f + (g_Boss.nPatternAnim * nU), nV + (nV * nSheetLine));

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBoss->Unlock();
}

//�{�X�̏����擾
Boss*GetBoss(void)
{
	return &g_Boss;
}