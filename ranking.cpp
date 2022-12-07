#include "Ranking.h"
#include "score.h"
#include "sound.h"
#include "input.h"
#include "fade.h"
#include <stdio.h>

//�}�N����`
#define FILENAME_RANKING	"RankingSave"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureRanking = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureRankingScore = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureRankingLogo = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureRankingBg = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;		//���_�o�b�t�@�ւ̃|�C���^
int g_nRankPlayer;
int g_aSavedRank[5];
int g_nRankMemory;
int g_nCountAnimRank, g_nAnimPatternRank;
int g_nPatternRankLogo, g_nAnimRankLogo;
int g_nDelayReturn;

//�����L���O�̏���������
void InitRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;					//���_���ւ̃|�C���^
	int nCount, nCount2;			//�����J�E���g����ϐ���錾
	g_nRankMemory = 5;				//�v���C���[�̃����L���O��ۑ�����ϐ���錾

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�O���[�o���ϐ�������������
	g_nCountAnimRank = 0;
	g_nAnimPatternRank = -100;
	g_nAnimRankLogo = 0.0f;
	g_nPatternRankLogo = 3;
	g_nDelayReturn = 0;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ranking_rank.png",
		&g_pTextureRanking);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number000.png",
		&g_pTextureRankingScore);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ranking_logo.png",
		&g_pTextureRankingLogo);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Ranking.png",
		&g_pTextureRankingBg);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 47,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRanking,
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	pVtx[4].pos = D3DXVECTOR3(340.0f, 100.0f, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(940.0f, 100.0f, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(340.0f, 200.0f, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(940.0f, 200.0f, 0.0f);

	for (nCount = 2; nCount < 7; nCount++)
	{
		pVtx[nCount * 4].pos = D3DXVECTOR3(400.0f, 275.0f + (75.0f * (nCount - 2)), 0.0f);
		pVtx[(nCount * 4) + 1].pos = D3DXVECTOR3(450.0f, 275.0f + (75.0f * (nCount - 2)), 0.0f);
		pVtx[(nCount * 4) + 2].pos = D3DXVECTOR3(400.0f, 325.0f + (75.0f * (nCount - 2)), 0.0f);
		pVtx[(nCount * 4) + 3].pos = D3DXVECTOR3(450.0f, 325.0f + (75.0f * (nCount - 2)), 0.0f);
	}

	for (nCount = 0; nCount < 5; nCount++)
	{
		for (nCount2 = 0; nCount2 < 8; nCount2++)
		{
			pVtx[(nCount * 32) + 28 + (nCount2 * 4)].pos = D3DXVECTOR3(500.0f + (50.0f * (nCount2)), 275.0f + ((75.0f * (nCount))), 0.0f);
			pVtx[(nCount * 32) + 29 + (nCount2 * 4)].pos = D3DXVECTOR3(550.0f + (50.0f * (nCount2)), 275.0f + ((75.0f * (nCount))), 0.0f);
			pVtx[(nCount * 32) + 30 + (nCount2 * 4)].pos = D3DXVECTOR3(500.0f + (50.0f * (nCount2)), 325.0f + ((75.0f * (nCount))), 0.0f);
			pVtx[(nCount * 32) + 31 + (nCount2 * 4)].pos = D3DXVECTOR3(550.0f + (50.0f * (nCount2)), 325.0f + ((75.0f * (nCount))), 0.0f);
		}
	}

	for (nCount = 0; nCount < 7; nCount++)
	{
		//rhw�̐ݒ�
		pVtx[(nCount * 4) + 0].rhw = 1.0f;
		pVtx[(nCount * 4) + 1].rhw = 1.0f;
		pVtx[(nCount * 4) + 2].rhw = 1.0f;
		pVtx[(nCount * 4) + 3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[(nCount * 4) + 0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[(nCount * 4) + 1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[(nCount * 4) + 2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[(nCount * 4) + 3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	for (nCount = 7; nCount < 47; nCount++)
	{
		//rhw�̐ݒ�
		pVtx[(nCount * 4) + 0].rhw = 1.0f;
		pVtx[(nCount * 4) + 1].rhw = 1.0f;
		pVtx[(nCount * 4) + 2].rhw = 1.0f;
		pVtx[(nCount * 4) + 3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[(nCount * 4) + 0].col = D3DCOLOR_RGBA(25, 25, 25, 255);
		pVtx[(nCount * 4) + 1].col = D3DCOLOR_RGBA(25, 25, 25, 255);
		pVtx[(nCount * 4) + 2].col = D3DCOLOR_RGBA(25, 25, 25, 255);
		pVtx[(nCount * 4) + 3].col = D3DCOLOR_RGBA(25, 25, 25, 255);
	}

	//�e�N�X�`�����W�̐ݒ�
	for (nCount = 0; nCount < 2; nCount++)
	{
		pVtx[(nCount * 4) + 0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[(nCount * 4) + 1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[(nCount * 4) + 2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[(nCount * 4) + 3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	for (nCount = 2; nCount < 7; nCount++)
	{
		pVtx[(nCount * 4) + 0].tex = D3DXVECTOR2(0.0f, 0.0f + ((nCount - 2) * 0.2f));
		pVtx[(nCount * 4) + 1].tex = D3DXVECTOR2(1.0f, 0.0f + ((nCount - 2) * 0.2f));
		pVtx[(nCount * 4) + 2].tex = D3DXVECTOR2(0.0f, 0.2f + ((nCount - 2) * 0.2f));
		pVtx[(nCount * 4) + 3].tex = D3DXVECTOR2(1.0f, 0.2f + ((nCount - 2) * 0.2f));
	}
	for (nCount = 7; nCount < 47; nCount++)
	{
		pVtx[(nCount * 4) + 0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[(nCount * 4) + 1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[(nCount * 4) + 2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[(nCount * 4) + 3].tex = D3DXVECTOR2(0.1f, 1.0f);
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRanking->Unlock();

	//�����L���O���̃��[�h����
	LoadRanking();
}

//�����L���O�̏I������
void UninitRanking(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureRanking != NULL)
	{
		g_pTextureRanking->Release();
		g_pTextureRanking = NULL;
	}
	if (g_pTextureRankingScore != NULL)
	{
		g_pTextureRankingScore->Release();
		g_pTextureRankingScore = NULL;
	}
	if (g_pTextureRankingLogo != NULL)
	{
		g_pTextureRankingLogo->Release();
		g_pTextureRankingLogo = NULL;
	}
	if (g_pTextureRankingBg != NULL)
	{
		g_pTextureRankingBg->Release();
		g_pTextureRankingBg = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRanking != NULL)
	{
		g_pVtxBuffRanking->Release();
		g_pVtxBuffRanking = NULL;
	}
}

//�����L���O�̍X�V����
void UpdateRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;					//���_���ւ̃|�C���^
	int nCount;						//�����J�E���g����ϐ���錾

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	//�����L���O���S�̃A�j���[�V��������
	g_nCountAnimRank++;
	g_nDelayReturn++;

	g_nAnimRankLogo += g_nPatternRankLogo;

	if (g_nCountAnimRank % 35 == 34)
	{
		g_nPatternRankLogo *= -1;
	}

	pVtx[4].col = D3DCOLOR_RGBA(150 + g_nAnimRankLogo, 150 + g_nAnimRankLogo, 150 + g_nAnimRankLogo, 255);
	pVtx[5].col = D3DCOLOR_RGBA(150 + g_nAnimRankLogo, 150 + g_nAnimRankLogo, 150 + g_nAnimRankLogo, 255);
	pVtx[6].col = D3DCOLOR_RGBA(150 + g_nAnimRankLogo, 150 + g_nAnimRankLogo, 150 + g_nAnimRankLogo, 255);
	pVtx[7].col = D3DCOLOR_RGBA(150 + g_nAnimRankLogo, 150 + g_nAnimRankLogo, 150 + g_nAnimRankLogo, 255);

	//�v���C���[�̃����L���O�A�j���[�V��������

	if (g_nRankMemory <= 4)
	{
		if (g_nCountAnimRank % 5 == 4)
		{
			g_nAnimPatternRank *= -1;
		}

		for (nCount = 0; nCount < 8; nCount++)
		{
			//���_�J���[�̐ݒ�
			pVtx[28 + (g_nRankMemory * 32) + (nCount * 4)].col = D3DCOLOR_RGBA(155 + g_nAnimPatternRank, 155 + g_nAnimPatternRank, 155 + g_nAnimPatternRank, 255);
			pVtx[29 + (g_nRankMemory * 32) + (nCount * 4)].col = D3DCOLOR_RGBA(155 + g_nAnimPatternRank, 155 + g_nAnimPatternRank, 155 + g_nAnimPatternRank, 255);
			pVtx[30 + (g_nRankMemory * 32) + (nCount * 4)].col = D3DCOLOR_RGBA(155 + g_nAnimPatternRank, 155 + g_nAnimPatternRank, 155 + g_nAnimPatternRank, 255);
			pVtx[31 + (g_nRankMemory * 32) + (nCount * 4)].col = D3DCOLOR_RGBA(155 + g_nAnimPatternRank, 155 + g_nAnimPatternRank, 155 + g_nAnimPatternRank, 255);
		}
	}
	
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRanking->Unlock();

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{//�G���^�[�L�[�������ꍇ
		//�����L���O�̃Z�[�u����
		SaveRanking();

		PlaySound(SOUND_LABEL_SE_CLICK);

		//�t�F�[�h�̐ݒ�
		SetFade(MODE_TITLE);
	}
	if (g_nDelayReturn >= 800)
	{
		g_nDelayReturn = 0;
		SetFade(MODE_TITLE);
	}
}

//�����L���O�̕`�揈��
void DrawRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCount;							//�����J�E���g����ϐ���錾

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRanking, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureRankingBg);

	//�����L���O�̔w�i��`�悷��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	pDevice->SetTexture(0, g_pTextureRankingLogo);

	//�����L���O�̃��S��`�悷��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4, 2);

	pDevice->SetTexture(0, g_pTextureRanking);

	for (nCount = 2; nCount < 7; nCount++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}

	pDevice->SetTexture(0, g_pTextureRankingScore);

	for (nCount = 7; nCount < 47; nCount++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
}

//�v���C���[�̃X�R�A���擾
void GetRank(int nRank)
{
	g_nRankPlayer = nRank;
}

//�����L���O�̃Z�[�u����
void SaveRanking(void)
{
	FILE*pFile;				//�t�@�C���|�C���^��錾����

	//�t�@�C�����J��
	pFile = fopen("data/RankingSave/FILENAME_RANKING", "wb");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		//�t�@�C���Ƀ����L���O���������o��
		fwrite(&g_aSavedRank[0], sizeof(int), 5, pFile);

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
		printf("XXXXX �Z�[�u�t�@�C�����J���܂���ł��� XXXXX");
	}
}

//�����L���O�̃��[�h����
void LoadRanking(void)
{
	FILE*pFile;				//�t�@�C���|�C���^��錾����

	//�t�@�C�����J��
	pFile = fopen("data/RankingSave/FILENAME_RANKING", "rb");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		//�t�@�C�����烉���L���O����ǂݍ���
		fread(&g_aSavedRank[0], sizeof(int), 5, pFile);

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
		printf("XXXXX �Z�[�u�t�@�C�����J���܂���ł��� XXXXX");
	}
}

//�����L���O�̐ݒ菈��
void SetRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;					//���_���ւ̃|�C���^
	int nCount, nCount2;			//�����J�E���g����ϐ���錾
	int nMemory;					//�����L���O�����i�[����ϐ���錾����
	int aPosTexU[5][8];

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�v���C���[�̃X�R�A�͕ۑ����ꂽ�����L���O���傫�����ǂ����m�F����
	for (nCount = 4; nCount >= 0; nCount--)
	{
		if (g_nRankPlayer > g_aSavedRank[nCount])
		{
			g_nRankMemory = nCount;
		}
	}

	//�o�u���\�[�g�A���S���Y��
	if (g_nRankPlayer > g_aSavedRank[4])
	{
		g_aSavedRank[4] = g_nRankPlayer;

		for (nCount = 0; nCount < 4; nCount++)
		{
			for (nCount2 = nCount + 1; nCount2 < 5; nCount2++)
			{
				if (g_aSavedRank[nCount] < g_aSavedRank[nCount2])
				{
					nMemory = g_aSavedRank[nCount2];
					g_aSavedRank[nCount2] = g_aSavedRank[nCount];
					g_aSavedRank[nCount] = nMemory;
				}
			}
		}
	}

	for (nCount = 0; nCount < 5; nCount++)
	{
		//�X�R�A�̊e�����v�Z����
		aPosTexU[nCount][0] = (g_aSavedRank[nCount] % 100000000) / 10000000;
		aPosTexU[nCount][1] = (g_aSavedRank[nCount] % 10000000) / 1000000;
		aPosTexU[nCount][2] = (g_aSavedRank[nCount] % 1000000) / 100000;
		aPosTexU[nCount][3] = (g_aSavedRank[nCount] % 100000) / 10000;
		aPosTexU[nCount][4] = (g_aSavedRank[nCount] % 10000) / 1000;
		aPosTexU[nCount][5] = (g_aSavedRank[nCount] % 1000) / 100;
		aPosTexU[nCount][6] = (g_aSavedRank[nCount] % 100) / 10;
		aPosTexU[nCount][7] = (g_aSavedRank[nCount] % 10);
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	//�e���̃e�N�X�`�����W�̐ݒ�
	for (nCount = 0; nCount < 5; nCount++)
	{
		for (nCount2 = 0; nCount2 < 8; nCount2++)
		{
			pVtx[(nCount * 32) + 28 + (nCount2 * 4)].tex = D3DXVECTOR2(0.0f + (aPosTexU[nCount][nCount2] * 0.1f), 0.0f);
			pVtx[(nCount * 32) + 29 + (nCount2 * 4)].tex = D3DXVECTOR2(0.1f + (aPosTexU[nCount][nCount2] * 0.1f), 0.0f);
			pVtx[(nCount * 32) + 30 + (nCount2 * 4)].tex = D3DXVECTOR2(0.0f + (aPosTexU[nCount][nCount2] * 0.1f), 1.0f);
			pVtx[(nCount * 32) + 31 + (nCount2 * 4)].tex = D3DXVECTOR2(0.1f + (aPosTexU[nCount][nCount2] * 0.1f), 1.0f);
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRanking->Unlock();
}