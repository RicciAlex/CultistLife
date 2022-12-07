//===================================================//
//                                                   //
//     �@   �A�N�V�����Q�[�������̃t�@�C��  �@       //  
//                Author: Ricci Alex				 //
//                                                   //
//===================================================//

//�C���N���[�h�t�@�C��
#include "explosion.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;			//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Explosion g_aExplosion[MAX_EXPLOSION];					//�����^�̔z���錾����

//�����̏���������
void InitExplosion(void)
{
	int nCntExplosion;				//�����J�E���g����ϐ���錾����
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();			//�f�o�C�X�̎擾

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\explosion000.png",
		&g_pTextureExplosion);

	//�����̊e�p�����[�^������������
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ʒu
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		//�J���[
		g_aExplosion[nCntExplosion].nCounterAnim = 0;								//�A�j���[�V�����J�E���^�[
		g_aExplosion[nCntExplosion].nPatternAnim = 0;								//�A�j���[�V�����p�^�[���̔ԍ�
		g_aExplosion[nCntExplosion].nSize = 1;										//�傫��
		g_aExplosion[nCntExplosion].bUse = false;									//�g�p���Ă���J�E���^�[���ǂ���
	}
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//���_�̐ݒ�
		pVtx[1].pos = D3DXVECTOR3((g_aExplosion[nCntExplosion].pos.x + 30.0f) * g_aExplosion[nCntExplosion].nSize, (g_aExplosion[nCntExplosion].pos.y - 30.0f) * g_aExplosion[nCntExplosion].nSize, 0.0f);
		pVtx[0].pos = D3DXVECTOR3((g_aExplosion[nCntExplosion].pos.x - 30.0f) * g_aExplosion[nCntExplosion].nSize, (g_aExplosion[nCntExplosion].pos.y - 30.0f) * g_aExplosion[nCntExplosion].nSize, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((g_aExplosion[nCntExplosion].pos.x + 30.0f) * g_aExplosion[nCntExplosion].nSize, (g_aExplosion[nCntExplosion].pos.y + 30.0f) * g_aExplosion[nCntExplosion].nSize, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((g_aExplosion[nCntExplosion].pos.x - 30.0f) * g_aExplosion[nCntExplosion].nSize, (g_aExplosion[nCntExplosion].pos.y + 30.0f) * g_aExplosion[nCntExplosion].nSize, 0.0f);

		//rhw�ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 0.5f, 0.05f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.5f, 0.05f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.5f, 0.05f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.5f, 0.05f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffExplosion->Unlock();
}

//�����̏I������
void UninitExplosion(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//�����̍X�V����
void UpdateExplosion(void)
{
	int nCntExplosion;	//�����J�E���g����ϐ���錾����
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^
	Player*pPlayer;

	pPlayer = GetPlayer();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//�e�N�X�`���̍X�V
		g_aExplosion[nCntExplosion].nCounterAnim++;

		if (g_aExplosion[nCntExplosion].bUse == true)
		{

			//���_�̐ݒ�
			pVtx[1].pos = D3DXVECTOR3((g_aExplosion[nCntExplosion].pos.x) + 30.0f * g_aExplosion[nCntExplosion].nSize, (g_aExplosion[nCntExplosion].pos.y) - 30.0f * g_aExplosion[nCntExplosion].nSize, 0.0f);
			pVtx[0].pos = D3DXVECTOR3((g_aExplosion[nCntExplosion].pos.x) - 30.0f * g_aExplosion[nCntExplosion].nSize, (g_aExplosion[nCntExplosion].pos.y) - 30.0f * g_aExplosion[nCntExplosion].nSize, 0.0f);
			pVtx[3].pos = D3DXVECTOR3((g_aExplosion[nCntExplosion].pos.x) + 30.0f * g_aExplosion[nCntExplosion].nSize, (g_aExplosion[nCntExplosion].pos.y) + 30.0f * g_aExplosion[nCntExplosion].nSize, 0.0f);
			pVtx[2].pos = D3DXVECTOR3((g_aExplosion[nCntExplosion].pos.x) - 30.0f * g_aExplosion[nCntExplosion].nSize, (g_aExplosion[nCntExplosion].pos.y) + 30.0f * g_aExplosion[nCntExplosion].nSize, 0.0f);

			//�A�j���[�V��������
			if ((g_aExplosion[nCntExplosion].nCounterAnim % 5) == 0)			//�A�j���[�V�����̑��������߂����
			{
				g_aExplosion[nCntExplosion].nPatternAnim += 1;				//�J�E���^�[No.���X�V����

				if (g_aExplosion[nCntExplosion].nPatternAnim == 9)
				{
					g_aExplosion[nCntExplosion].bUse = false;
				}

				if (pPlayer->state != PLAYERSTATE_DAMAGE && pPlayer->state != PLAYERSTATE_DEATH)
				{
					if ((pPlayer->pos.x - g_aExplosion[nCntExplosion].pos.x) * (pPlayer->pos.x - g_aExplosion[nCntExplosion].pos.x) +
						((pPlayer->pos.y - 37.5f) - g_aExplosion[nCntExplosion].pos.y) * ((pPlayer->pos.y - 37.5f) - g_aExplosion[nCntExplosion].pos.y) <
						(g_aExplosion[nCntExplosion].nSize * 30.0f) * (g_aExplosion[nCntExplosion].nSize * 30.0f))
					{
						pPlayer->nCounterState = 180;
						pPlayer->state = PLAYERSTATE_DAMAGE;
						AddScore(-500);
						SetSChange(D3DXVECTOR3(pPlayer->pos.x - (50.0f * pPlayer->nDirectionMove), pPlayer->pos.y - PLAYER_HEIGHT, 0.0f), D3DXVECTOR3(pPlayer->move.x, pPlayer->move.y, 0.0f), 0, CHANGEVALUE_MINUS500);
					}
				}

				//�e�N�X�`�����W�̐ݒ�
				pVtx[2].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * 0.125f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * 0.125f + 0.125f, 1.0f);
				pVtx[0].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * 0.125f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * 0.125f + 0.125f, 0.0f);
			}
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffExplosion->Unlock();
}

//�����̕`�揈��
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureExplosion);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{//�g�p����Ă���ꍇ
		 //�l�p�`��`�悷��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntExplosion * 4, 2);
		}
	}
}

//�����̐ݒ�
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col, int size)
{
	int nCntExplosion;		//�����J�E���g����ϐ���錾����

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	//������
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{//�g�p����Ă��Ȃ��ꍇ

		 //�����̈ʒu�̐ݒ�
			g_aExplosion[nCntExplosion].pos = pos;

			//�����̐F�̐ݒ�
			g_aExplosion[nCntExplosion].col = col;

			//�����̑傫���̐ݒ�
			g_aExplosion[nCntExplosion].nSize = size;

			//���_�̐ݒ�
			pVtx[1].pos = D3DXVECTOR3((g_aExplosion[nCntExplosion].pos.x + 30.0f) * size, (g_aExplosion[nCntExplosion].pos.y - 30.0f) * size, 0.0f);
			pVtx[0].pos = D3DXVECTOR3((g_aExplosion[nCntExplosion].pos.x - 30.0f) * size, (g_aExplosion[nCntExplosion].pos.y - 30.0f) * size, 0.0f);
			pVtx[3].pos = D3DXVECTOR3((g_aExplosion[nCntExplosion].pos.x + 30.0f) * size, (g_aExplosion[nCntExplosion].pos.y + 30.0f) * size, 0.0f);
			pVtx[2].pos = D3DXVECTOR3((g_aExplosion[nCntExplosion].pos.x - 30.0f) * size, (g_aExplosion[nCntExplosion].pos.y + 30.0f) * size, 0.0f);



			//�e�N�X�`�����W�̐ݒ�
			pVtx[2].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * 0.125f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * 0.125f + 0.125f, 1.0f);
			pVtx[0].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * 0.125f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * 0.125f + 0.125f, 0.0f);
			
			//�e�N�X�`���J�E���^�[�̐ݒ�
			g_aExplosion[nCntExplosion].nCounterAnim = 0;
			//�A�j���[�V�����J�E���^�[No.�̐ݒ�
			g_aExplosion[nCntExplosion].nPatternAnim = 0;
			//�g�p����Ă����Ԃɂ���
			g_aExplosion[nCntExplosion].bUse = true;

			PlaySound(SOUND_LABEL_SE_EXPLOSION);
			break;
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffExplosion->Unlock();
}