//===================================//
//                                   //
//	     �w�i��\������t�@�C��		 //
//         Author: Ricci Alex	     //
//                                   //
//===================================//

//�C���N���[�h�t�@�C��
#include "bg.h"

//�}�N����`
#define NUM_BG		(3)								//�w�i�̐�

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureBg[NUM_BG] = {};	    //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_apTextureBlack = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBg = NULL;		//���_�o�b�t�@�ւ̃|�C���^
float g_aPosTexV[NUM_BG];							//�e�N�X�`�����W�̊J�n�ʒu					

//�w�i�̏���������
void InitBg(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;					//���_���ւ̃|�C���^

	g_aPosTexV[0] = 0.0f;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\BgStoneWall.png",
		&g_apTextureBg[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bg102.png",
		&g_apTextureBg[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bg101.png",
		&g_apTextureBg[2]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\BlackBG.png",
		&g_apTextureBlack);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_BG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBg,
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBg->Lock(0, 0, (void**)&pVtx, 0);

	//�w�i�̈ʒu�̏�����
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	pVtx[4].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.0f, 0.0f, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.0f, SCREEN_HEIGHT, 0.0f);

	pVtx[8].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[9].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.0f, 0.0f, 0.0f);
	pVtx[10].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[11].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.0f, SCREEN_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;

	pVtx[8].rhw = 1.0f;
	pVtx[9].rhw = 1.0f;
	pVtx[10].rhw = 1.0f;
	pVtx[11].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 180);
	pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 180);
	pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 180);
	pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 180);

	pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 180);
	pVtx[9].col = D3DCOLOR_RGBA(255, 255, 255, 180);
	pVtx[10].col = D3DCOLOR_RGBA(255, 255, 255, 180);
	pVtx[11].col = D3DCOLOR_RGBA(255, 255, 255, 180);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(g_aPosTexV[0], 0.0f);
	pVtx[1].tex = D3DXVECTOR2(g_aPosTexV[0] + 1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(g_aPosTexV[0], 1.0f);
	pVtx[3].tex = D3DXVECTOR2(g_aPosTexV[0] + 1.0f, 1.0f);

	pVtx[4].tex = D3DXVECTOR2(0.0f, g_aPosTexV[0]);
	pVtx[5].tex = D3DXVECTOR2(1.0f, g_aPosTexV[0]);
	pVtx[6].tex = D3DXVECTOR2(0.0f, g_aPosTexV[0] + 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, g_aPosTexV[0] +1.0f);

	pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[9].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[11].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBg->Unlock();
}

//�w�i�̏I������
void UninitBg(void)
{

	//�e�N�X�`���̔j��
	if (g_apTextureBg[0] != NULL)
	{
		g_apTextureBg[0]->Release();
		g_apTextureBg[0] = NULL;
	}
	if (g_apTextureBg[1] != NULL)
	{
		g_apTextureBg[1]->Release();
		g_apTextureBg[1] = NULL;
	}
	if (g_apTextureBg[2] != NULL)
	{				  
		g_apTextureBg[2]->Release();
		g_apTextureBg[2] = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBg != NULL)
	{
		g_pVtxBuffBg->Release();
		g_pVtxBuffBg = NULL;
	}
}

//�w�i�̍X�V����
void UpdateBg(void)
{
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	g_aPosTexV[0] += 0.001f;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBg->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̍X�V
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f + 1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.0f + 1.0f, 1.0f);

	pVtx[4].tex = D3DXVECTOR2(0.0f, -0.7f * g_aPosTexV[0]);
	pVtx[5].tex = D3DXVECTOR2(1.0f, -0.7f * g_aPosTexV[0]);
	pVtx[6].tex = D3DXVECTOR2(0.0f, -0.7f * g_aPosTexV[0] + 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, -0.7f * g_aPosTexV[0] + 1.0f);

	pVtx[8].tex = D3DXVECTOR2(0.5f * g_aPosTexV[0], -0.4f * g_aPosTexV[0]);
	pVtx[9].tex = D3DXVECTOR2(0.5f * g_aPosTexV[0] + 1.0f, -0.4f * g_aPosTexV[0]);
	pVtx[10].tex = D3DXVECTOR2(0.5f * g_aPosTexV[0], -0.4f * g_aPosTexV[0] + 1.0f);
	pVtx[11].tex = D3DXVECTOR2(0.5f * g_aPosTexV[0] + 1.0f, -0.4f * g_aPosTexV[0] + 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBg->Unlock();
}

//�w�i�̕`�揈��
void DrawBg(void)
{
	MODE mode;
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//���[�h�̎擾
	mode = GetMode();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBg, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (mode == MODE_GAME_BONUSSTAGE)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureBlack);
	}
	else
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureBg[0]);
	}
	
	//�l�p�`��`�悷��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	pDevice->SetTexture(0, g_apTextureBg[1]);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4, 2);

	pDevice->SetTexture(0, g_apTextureBg[2]);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 8, 2);
}