//===================================================//
//                                                   //
//     �A�N�V�����Q�[���^�C�g����ʂ� �t�@�C��   �@  //  
//                Author: Ricci Alex				 //
//                                                   //
//===================================================//

//�C���N���[�h�t�@�C��
#include "title.h"
#include "fade.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureTitle = NULL;	    //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_apTextureStart = NULL;	    //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;		//���_�o�b�t�@�ւ̃|�C���^
int g_AnimStart, g_PatternStart;
float  g_ShrinkStart;

//�^�C�g���̏���������
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;					//���_���ւ̃|�C���^

	pDevice = GetDevice();			//�f�o�C�X�̎擾
	g_AnimStart = 0;
	g_PatternStart = 1;
	g_ShrinkStart = 0.0f;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Title.png",
		&g_apTextureTitle);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\PressStart.png",
		&g_apTextureStart);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 6,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//���_�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	pVtx[4].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();

	PlaySound(SOUND_LABEL_BGMTITLE);
}

//�^�C�g���̏I������
void UninitTitle(void)
{
	//�e�N�X�`���̔j��
	if (g_apTextureTitle != NULL)
	{
		g_apTextureTitle->Release();
		g_apTextureTitle = NULL;
	}
	if (g_apTextureStart != NULL)
	{			   
		g_apTextureStart->Release();
		g_apTextureStart = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
}

//�^�C�g���̍X�V����
void UpdateTitle(void)
{
	if (g_PatternStart > 0)
	{
		g_ShrinkStart += 1.0f;
	}
	else
	{
		g_ShrinkStart -= 1.0f;
	}

	if (g_ShrinkStart > 100.0f || g_ShrinkStart < 0.0f)
	{
		g_PatternStart *= -1;
	}

	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[4].pos = D3DXVECTOR3(0.0f - g_ShrinkStart, 0.0f - (g_ShrinkStart * 0.4f), 0.0f);
	pVtx[5].pos = D3DXVECTOR3(SCREEN_WIDTH + g_ShrinkStart, 0.0f - (g_ShrinkStart * 0.4f), 0.0f);
	pVtx[6].pos = D3DXVECTOR3(0.0f - g_ShrinkStart, SCREEN_HEIGHT + (g_ShrinkStart * 0.4f), 0.0f);
	pVtx[7].pos = D3DXVECTOR3(SCREEN_WIDTH + g_ShrinkStart, SCREEN_HEIGHT + (g_ShrinkStart * 0.4f), 0.0f);

	pVtx[4].col = D3DXCOLOR(0.7f +  (g_ShrinkStart * 0.003), 0.7f + (g_ShrinkStart * 0.003), 0.7f + (g_ShrinkStart * 0.003), 1.0f);
	pVtx[5].col = D3DXCOLOR(0.7f +  (g_ShrinkStart * 0.003), 0.7f + (g_ShrinkStart * 0.003), 0.7f + (g_ShrinkStart * 0.003), 1.0f);
	pVtx[6].col = D3DXCOLOR(0.7f +  (g_ShrinkStart * 0.003), 0.7f + (g_ShrinkStart * 0.003), 0.7f + (g_ShrinkStart * 0.003), 1.0f);
	pVtx[7].col = D3DXCOLOR(0.7f +  (g_ShrinkStart * 0.003), 0.7f + (g_ShrinkStart * 0.003), 0.7f + (g_ShrinkStart * 0.003), 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{//���̉�ʂɐi��

		PlaySound(SOUND_LABEL_SE_CLICK);

		SetFade(MODE_GAME_FIRSTSTAGE_1);
	}
}

//�^�C�g���̕`�揈��
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_apTextureTitle);

	//�l�p�`��`�悷��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	pDevice->SetTexture(0, g_apTextureStart);

	//�l�p�`��`�悷��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4, 2);
}