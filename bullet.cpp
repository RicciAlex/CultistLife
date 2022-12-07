//===================================================//
//                                                   //
//     �@	 �A�N�V�����Q�[���e�̃t�@�C��	         //  
//                Author: Ricci Alex				 //
//                                                   //
//===================================================//

//�C���N���[�h�t�@�C��
#include "bullet.h"
#include "sound.h"

//�}�N����`
#define MAX_BULLET		(128)							//�e�̍ő吔

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureBulletBoss = NULL;				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureSlashBoss = NULL;
LPDIRECT3DTEXTURE9 g_pTextureDevil = NULL;
LPDIRECT3DTEXTURE9 g_pTextureSun = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Bullet g_aBullet[MAX_BULLET];							//Bullet�^�̔z���錾����

//�e�̏���������
void InitBullet(void)
{
	int nCntBullet;					//�����J�E���g����ϐ���錾����
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	VERTEX_2D*pVtx;					//���_���ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bulletBlue001.png",
		&g_pTextureBulletBoss);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Slash.png",
		&g_pTextureSlashBoss);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\DevilBullet.png",
		&g_pTextureDevil);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\SunBullet.png",
		&g_pTextureSun);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ʒu
		g_aBullet[nCntBullet].LastPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�O��̈ʒu
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ړ���
		g_aBullet[nCntBullet].Accel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����
		g_aBullet[nCntBullet].nLife = 120;									
		g_aBullet[nCntBullet].nType = 0;									//���
		g_aBullet[nCntBullet].nCntDelay = 0;								
		g_aBullet[nCntBullet].nCounterAnim = 0;								//�A�j���[�V�����J�E���^�[
		g_aBullet[nCntBullet].nPatternAnim = 0;								//�e�̃A�j���[�V�����p�^�[��
		g_aBullet[nCntBullet].bUse = false;									//�g�p���Ă��邩�ǂ���

		//�e���W�̐ݒ�
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10.0f, g_aBullet[nCntBullet].pos.y - 10.0f, 0.0f);
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10.0f, g_aBullet[nCntBullet].pos.y - 10.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10.0f, g_aBullet[nCntBullet].pos.y + 10.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10.0f, g_aBullet[nCntBullet].pos.y + 10.0f, 0.0f);

		//rth�̐ݒ�
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
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}


//�e�̏I������
void UninitBullet(void)
{
	//�e�N�X�`���̃|�C���^�̔j��
	if (g_pTextureBulletBoss != NULL)
	{
		g_pTextureBulletBoss->Release();
		g_pTextureBulletBoss = NULL;
	}
	if (g_pTextureSlashBoss != NULL)
	{			  
		g_pTextureSlashBoss->Release();
		g_pTextureSlashBoss = NULL;
	}
	if (g_pTextureDevil != NULL)
	{			  
		g_pTextureDevil->Release();
		g_pTextureDevil = NULL;
	}
	if (g_pTextureSun != NULL)
	{			  
		g_pTextureSun->Release();
		g_pTextureSun = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//�e�̍X�V����
void UpdateBullet(void)
{
	int nCntBullet;		//�e���J�E���g����ϐ���錾
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^
	int nInteraction;	
	Player*pPlayer;

	pPlayer = GetPlayer();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			//�ʒu�ƈړ��ʂ̍X�V
			g_aBullet[nCntBullet].pos.y += g_aBullet[nCntBullet].move.y;
			g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;
			if (g_aBullet[nCntBullet].nType != 2)
			{
				g_aBullet[nCntBullet].move += g_aBullet[nCntBullet].Accel;
			}
			else
			{
				if (g_aBullet[nCntBullet].move.x * g_aBullet[nCntBullet].Accel.x < 0)
				{
					g_aBullet[nCntBullet].move += g_aBullet[nCntBullet].Accel;
				}
				else
				{
					g_aBullet[nCntBullet].nLife -= 2;
					g_aBullet[nCntBullet].move.x = 0.0f;
				}
			}

			g_aBullet[nCntBullet].nLife--;	
			
			if (g_aBullet[nCntBullet].nType == 0)
			{
				//�u���b�N�̓����蔻��
				nInteraction = BlockInteractionBullet(&g_aBullet[nCntBullet].pos, &g_aBullet[nCntBullet].LastPos, &g_aBullet[nCntBullet].move, 10.0f, 20.0f);

				if (nInteraction == 1)
				{//�u���b�N�̏�ɓ���������
					g_aBullet[nCntBullet].bUse = false;
				}

			}
			else if (g_aBullet[nCntBullet].nType == 1)
			{
				if ((pPlayer->pos.y - g_aBullet[nCntBullet].pos.y) * g_aBullet[nCntBullet].Accel.y < 0)
				{
					g_aBullet[nCntBullet].move.y *= 0.5f;
					g_aBullet[nCntBullet].Accel.y *= -1;
				}
			}

			if (g_aBullet[nCntBullet].pos.y < pPlayer->pos.y && g_aBullet[nCntBullet].pos.y > pPlayer->pos.y - PLAYER_HEIGHT && 
				g_aBullet[nCntBullet].pos.x > pPlayer->pos.x - (PLAYER_WIDTH * 0.5) && g_aBullet[nCntBullet].pos.x < pPlayer->pos.x + (PLAYER_WIDTH * 0.5) &&
				pPlayer->state != PLAYERSTATE_DAMAGE && pPlayer->state != PLAYERSTATE_DEATH)
			{//�v���C���[�ɓ���������A�_���[�W��Ԃɂ���
				g_aBullet[nCntBullet].bUse = false;
				pPlayer->state = PLAYERSTATE_DAMAGE;
				pPlayer->nCounterState = 180;
				AddScore(-250);
				SetSChange(D3DXVECTOR3(pPlayer->pos.x - (50.0f * pPlayer->nDirectionMove), pPlayer->pos.y - PLAYER_HEIGHT, 0.0f), D3DXVECTOR3(pPlayer->move.x, pPlayer->move.y, 0.0f), 0, CHANGEVALUE_MINUS250);

				if (g_aBullet[nCntBullet].nType == 4 || g_aBullet[nCntBullet].nType == 5)
				{//�΂̉�
					PlaySound(SOUND_LABEL_SE_FIRE);
				}
				else if (g_aBullet[nCntBullet].nType == 2)
				{//�؂���̉�
					PlaySound(SOUND_LABEL_SE_SLASH);
				}
				else
				{//���ʍU���̉�
					PlaySound(SOUND_LABEL_SE_NORMALDAMAGE);
				}
			}

			if (g_aBullet[nCntBullet].nType == 2)
			{
				//�e���_�̈ʒu�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10.0f, g_aBullet[nCntBullet].pos.y - 30.0f, g_aBullet[nCntBullet].pos.z);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10.0f, g_aBullet[nCntBullet].pos.y - 30.0f, g_aBullet[nCntBullet].pos.z);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10.0f, g_aBullet[nCntBullet].pos.y + 30.0f, g_aBullet[nCntBullet].pos.z);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10.0f, g_aBullet[nCntBullet].pos.y + 30.0f, g_aBullet[nCntBullet].pos.z);
			}
			else if (g_aBullet[nCntBullet].nType == 3)
			{
				g_aBullet[nCntBullet].nCounterAnim++;

				if (g_aBullet[nCntBullet].nCounterAnim % 15 == 14)
				{
					g_aBullet[nCntBullet].nPatternAnim ^= 1;
				}

				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 15.0f, g_aBullet[nCntBullet].pos.y - 15.0f, g_aBullet[nCntBullet].pos.z);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 15.0f, g_aBullet[nCntBullet].pos.y - 15.0f, g_aBullet[nCntBullet].pos.z);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 15.0f, g_aBullet[nCntBullet].pos.y + 15.0f, g_aBullet[nCntBullet].pos.z);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 15.0f, g_aBullet[nCntBullet].pos.y + 15.0f, g_aBullet[nCntBullet].pos.z);

				pVtx[0].tex = D3DXVECTOR2(0.0f + (0.5f * g_aBullet[nCntBullet].nPatternAnim), 1.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f + (0.5f * g_aBullet[nCntBullet].nPatternAnim), 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.5f + (0.5f * g_aBullet[nCntBullet].nPatternAnim), 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.5f + (0.5f * g_aBullet[nCntBullet].nPatternAnim), 0.0f);
			}
			else if (g_aBullet[nCntBullet].nType == 4)
			{
				if (g_aBullet[nCntBullet].move.x > 0)
				{
					if (g_aBullet[nCntBullet].pos.x > 640.0f)
					{
						g_aBullet[nCntBullet].bUse = false;
					}

					pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 30.0f, g_aBullet[nCntBullet].pos.y - 15.0f, 0.0f);
					pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 30.0f, g_aBullet[nCntBullet].pos.y - 15.0f, 0.0f);
					pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 30.0f, g_aBullet[nCntBullet].pos.y + 15.0f, 0.0f);
					pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 30.0f, g_aBullet[nCntBullet].pos.y + 15.0f, 0.0f);
				}
				else
				{
					if (g_aBullet[nCntBullet].pos.x < 640.0f)
					{
						g_aBullet[nCntBullet].bUse = false;
					}

					pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 30.0f, g_aBullet[nCntBullet].pos.y - 15.0f, 0.0f);
					pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 30.0f, g_aBullet[nCntBullet].pos.y - 15.0f, 0.0f);
					pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 30.0f, g_aBullet[nCntBullet].pos.y + 15.0f, 0.0f);
					pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 30.0f, g_aBullet[nCntBullet].pos.y + 15.0f, 0.0f);
				}
			}
			else if (g_aBullet[nCntBullet].nType == 5)
			{
				if (g_aBullet[nCntBullet].pos.y < 500.0f)
				{
					g_aBullet[nCntBullet].bUse = false;
				}

				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 15.0f, g_aBullet[nCntBullet].pos.y - 30.0f, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 15.0f, g_aBullet[nCntBullet].pos.y - 30.0f, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 15.0f, g_aBullet[nCntBullet].pos.y + 30.0f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 15.0f, g_aBullet[nCntBullet].pos.y + 30.0f, 0.0f);
			}
			else
			{
				//�e���_�̈ʒu�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10.0f, g_aBullet[nCntBullet].pos.y - 10.0f, g_aBullet[nCntBullet].pos.z);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10.0f, g_aBullet[nCntBullet].pos.y - 10.0f, g_aBullet[nCntBullet].pos.z);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10.0f, g_aBullet[nCntBullet].pos.y + 10.0f, g_aBullet[nCntBullet].pos.z);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10.0f, g_aBullet[nCntBullet].pos.y + 10.0f, g_aBullet[nCntBullet].pos.z);
			}
			

			//�O��̈ʒu�̍X�V
			g_aBullet[nCntBullet].LastPos = g_aBullet[nCntBullet].pos;

			if (g_aBullet[nCntBullet].nLife <= 0)
			{
				if (g_aBullet[nCntBullet].nCounterAnim != 0)
				{
					g_aBullet[nCntBullet].nCounterAnim = 0;
					g_aBullet[nCntBullet].nPatternAnim = 0;
				}

				g_aBullet[nCntBullet].bUse = false;					//�g�p����Ă��Ȃ���Ԃɂ���
			}
		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}

//�e�̕`�揈��
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;						//�J�E���g����ϐ���錾����

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			if (g_aBullet[nCntBullet].nType == 2)
			{
				pDevice->SetTexture(0, g_pTextureSlashBoss);
			}
			else if (g_aBullet[nCntBullet].nType == 3)
			{
				pDevice->SetTexture(0, g_pTextureDevil);
			}
			else if (g_aBullet[nCntBullet].nType == 4 || g_aBullet[nCntBullet].nType == 5)
			{
				pDevice->SetTexture(0, g_pTextureSun);
			}
			else
			{
				pDevice->SetTexture(0, g_pTextureBulletBoss);
			}

			//�l�p�`��`�悷��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);
		}

	}
}

//�e�̐ݒ菈��
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 acc, int type)
{
	int nCntBullet;		//�J�E���g����ϐ���錾����

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{//�e���g�p����Ă��Ȃ��ꍇ

		 //�e�̈ʒu�̐ݒ�
			g_aBullet[nCntBullet].pos = pos;

			g_aBullet[nCntBullet].LastPos = pos;			//�O��̈ʒu�̐ݒ�

			//�e���_�̈ʒu�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(pos.x - 10.0f, pos.y - 10.0f, pos.z);
			pVtx[1].pos = D3DXVECTOR3(pos.x + 10.0f, pos.y - 10.0f, pos.z);
			pVtx[2].pos = D3DXVECTOR3(pos.x - 10.0f, pos.y + 10.0f, pos.z);
			pVtx[3].pos = D3DXVECTOR3(pos.x + 10.0f, pos.y + 10.0f, pos.z);

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);


			//�e�̈ړ��ʂ̐ݒ�
			g_aBullet[nCntBullet].move = move;

			//�e�̉���
			g_aBullet[nCntBullet].Accel = acc;
			//�e�̎��
			g_aBullet[nCntBullet].nType = type;
			//�e�̗̑͂̐ݒ�
			g_aBullet[nCntBullet].nLife = 200;

			g_aBullet[nCntBullet].nCntDelay = 0;

			//�e���g�p����Ă����Ԃɂ���
			g_aBullet[nCntBullet].bUse = true;

			switch (g_aBullet[nCntBullet].nType)
			{
			case 0:

				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(0.0f, 0.5f, 0.2f, 1.0f);
				pVtx[1].col = D3DXCOLOR(0.0f, 0.5f, 0.2f, 1.0f);
				pVtx[2].col = D3DXCOLOR(0.0f, 0.5f, 0.2f, 1.0f);
				pVtx[3].col = D3DXCOLOR(0.0f, 0.5f, 0.2f, 1.0f);
				break;

			case 1:

				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(0.38f, 0.05f, 0.2f, 0.75f);
				pVtx[1].col = D3DXCOLOR(0.38f, 0.05f, 0.2f, 0.75f);
				pVtx[2].col = D3DXCOLOR(0.38f, 0.05f, 0.2f, 0.75f);
				pVtx[3].col = D3DXCOLOR(0.38f, 0.05f, 0.2f, 0.75f);

				break;

			case 2:

				pVtx[0].pos = D3DXVECTOR3(pos.x - 10.0f, pos.y - 30.0f, pos.z);
				pVtx[1].pos = D3DXVECTOR3(pos.x + 10.0f, pos.y - 30.0f, pos.z);
				pVtx[2].pos = D3DXVECTOR3(pos.x - 10.0f, pos.y + 30.0f, pos.z);
				pVtx[3].pos = D3DXVECTOR3(pos.x + 10.0f, pos.y + 30.0f, pos.z);

				if (move.x > 0)
				{
					//�e�N�X�`�����W�̐ݒ�
					pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
					pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
					pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
					pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				}
				else
				{
					//�e�N�X�`�����W�̐ݒ�
					pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);
					pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
					pVtx[0].tex = D3DXVECTOR2(1.0f, 0.0f);
				}

				//���_�J���[�̐ݒ�
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);

				break;

			case 3:

				pVtx[0].pos = D3DXVECTOR3(pos.x - 15.0f, pos.y - 15.0f, pos.z);
				pVtx[1].pos = D3DXVECTOR3(pos.x + 15.0f, pos.y - 15.0f, pos.z);
				pVtx[2].pos = D3DXVECTOR3(pos.x - 15.0f, pos.y + 15.0f, pos.z);
				pVtx[3].pos = D3DXVECTOR3(pos.x + 15.0f, pos.y + 15.0f, pos.z);

				//���_�J���[�̐ݒ�
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);

				pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.5f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.5f, 0.0f);

				break;

			case 4:

				if (move > 0)
				{
					pVtx[0].pos = D3DXVECTOR3(pos.x - 30.0f, pos.y - 15.0f, pos.z);
					pVtx[1].pos = D3DXVECTOR3(pos.x + 30.0f, pos.y - 15.0f, pos.z);
					pVtx[2].pos = D3DXVECTOR3(pos.x - 30.0f, pos.y + 15.0f, pos.z);
					pVtx[3].pos = D3DXVECTOR3(pos.x + 30.0f, pos.y + 15.0f, pos.z);
				}
				else
				{
					pVtx[1].pos = D3DXVECTOR3(pos.x - 30.0f, pos.y - 15.0f, pos.z);
					pVtx[0].pos = D3DXVECTOR3(pos.x + 30.0f, pos.y - 15.0f, pos.z);
					pVtx[3].pos = D3DXVECTOR3(pos.x - 30.0f, pos.y + 15.0f, pos.z);
					pVtx[2].pos = D3DXVECTOR3(pos.x + 30.0f, pos.y + 15.0f, pos.z);
				}
				

				//���_�J���[�̐ݒ�
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);

				pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.5f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.5f, 0.0f);

				break;

			case 5:

				pVtx[0].pos = D3DXVECTOR3(pos.x - 15.0f, pos.y - 30.0f, pos.z);
				pVtx[1].pos = D3DXVECTOR3(pos.x + 15.0f, pos.y - 30.0f, pos.z);
				pVtx[2].pos = D3DXVECTOR3(pos.x - 15.0f, pos.y + 30.0f, pos.z);
				pVtx[3].pos = D3DXVECTOR3(pos.x + 15.0f, pos.y + 30.0f, pos.z);

				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);

				pVtx[0].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 1.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);

				break;
			}

			break;
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}