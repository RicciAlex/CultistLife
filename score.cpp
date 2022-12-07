#include "main.h"
#include "score.h"

//�O���[�o���ϐ���錾����
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;		//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posScore;
int g_nScore;

//�X�R�A�̏���������
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;					//���_���ւ̃|�C���^
	int nCount;						//�����J�E���g����ϐ���錾����

									//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number000.png",
		&g_pTextureScore);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 8,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	//�O���[�o���ϐ��̏�����
	g_posScore = D3DXVECTOR3(900.0f, 35.0f, 0.0f);

	g_nScore = 1500;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCount = 0; nCount < 8; nCount++)
	{
		//���_�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(900.0f + (25.0f * nCount), 35.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(925.0f + (25.0f * nCount), 35.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(900.0f + (25.0f * nCount), 75.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(925.0f + (25.0f * nCount), 75.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}

//�X�R�A�̏I������
void UninitScore(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

//�X�R�A�̍X�V����
void UpdateScore(void)
{
	Player*pPlayer;

	pPlayer = GetPlayer();

	//�X�R�A�̐ݒ�
	SetScore(g_nScore);

	if (g_nScore <= 0)
	{
		pPlayer->state = PLAYERSTATE_DEATH;
	}
}

//�X�R�A�̕`�揈��
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCount;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureScore);

	for (nCount = 0; nCount < 8; nCount++)
	{
		//�l�p�`��`�悷��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
}

//�X�R�A�̐ݒ菈��
void SetScore(int nScore)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;					//���_���ւ̃|�C���^
	int aPosTexU[8];
	int nCount;						//�����J�E���g����ϐ���錾����

									//�f�o�C�X�̎擾
	pDevice = GetDevice();
	g_nScore = nScore;

	//�X�R�A�̊e�����v�Z����
	aPosTexU[0] = (g_nScore % 100000000) / 10000000;
	aPosTexU[1] = (g_nScore % 10000000) / 1000000;
	aPosTexU[2] = (g_nScore % 1000000) / 100000;
	aPosTexU[3] = (g_nScore % 100000) / 10000;
	aPosTexU[4] = (g_nScore % 10000) / 1000;
	aPosTexU[5] = (g_nScore % 1000) / 100;
	aPosTexU[6] = (g_nScore % 100) / 10;
	aPosTexU[7] = (g_nScore % 10);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCount = 0; nCount < 8; nCount++)
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + (aPosTexU[nCount] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (aPosTexU[nCount] * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (aPosTexU[nCount] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (aPosTexU[nCount] * 0.1f), 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();

	//�X�R�A�̎擾
	GetRank(g_nScore);
}

void AddScore(int nValue)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;					//���_���ւ̃|�C���^
	int aPosTexU[8];
	int nCount;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�X�R�A�ɉ��Z����
	g_nScore += nValue;

	//�X�R�A�̊e�����v�Z����
	aPosTexU[0] = (g_nScore % 100000000) / 10000000;
	aPosTexU[1] = (g_nScore % 10000000) / 1000000;
	aPosTexU[2] = (g_nScore % 1000000) / 100000;
	aPosTexU[3] = (g_nScore % 100000) / 10000;
	aPosTexU[4] = (g_nScore % 10000) / 1000;
	aPosTexU[5] = (g_nScore % 1000) / 100;
	aPosTexU[6] = (g_nScore % 100) / 10;
	aPosTexU[7] = (g_nScore % 10);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCount = 0; nCount < 8; nCount++)
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + (aPosTexU[nCount] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (aPosTexU[nCount] * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (aPosTexU[nCount] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (aPosTexU[nCount] * 0.1f), 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}