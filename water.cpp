//===================================================//
//                                                   //
//            �A�N�V�����Q�[�����t�@�C��             //  
//                Author: Ricci Alex				 //
//                                                   //
//===================================================//

//�C���N���[�h�t�@�C��
#include "water.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureWater = NULL;				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureWaterVertical = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureFire = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWater = NULL;			//���_�o�b�t�@�ւ̃|�C���^
WATER g_aWater[MAX_WATER];								//���^�̔z���錾����
int g_nAnimWater;										//���̃A�j���[�V�����J�E���^�[
int g_nAnimPattern;										//���̃A�j���[�V�����p�^�[��
int g_nAnimPatternFire;										//���̃A�j���[�V�����p�^�[��
float g_fMoveWater;										//��𓮂����J�E���^�[

//���̏���������
void InitWater(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̏��ւ̃|�C���^
	VERTEX_2D*pVtx;					//���_���ւ̃|�C���^
	int nCount;						//�����J�E���g����ϐ���錾

	//�O���[�o���ϐ��̏�����
	g_nAnimWater = 0;
	g_nAnimPattern = 0;
	g_fMoveWater = 0.0f;
	g_nAnimPatternFire = 0;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Acqua.png",
		&g_pTextureWater);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\AcquaVerticale.png",
		&g_pTextureWaterVertical);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Fire.png",
		&g_pTextureFire);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_WATER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWater,
		NULL);


	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffWater->Lock(0, 0, (void**)&pVtx, 0);

	for (nCount = 0; nCount < MAX_WATER; nCount++)
	{
		//���^�̕ϐ��̊e�p�����[�^�̏�����
		g_aWater[nCount].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu
		g_aWater[nCount].fHeight = 0.0f;						//����
		g_aWater[nCount].fWidth = 0.0f;							//��
		g_aWater[nCount].nType = 0;								//���
		g_aWater[nCount].nNumSwitch = 0;						//�X�C�b�`�̔ԍ�
		g_aWater[nCount].wState = WATERSTATE_READY;				//���̏��
		g_aWater[nCount].bUse = false;							//�g�p����Ă��邩�ǂ���

		//���_�ݒ�
		pVtx[1].pos = D3DXVECTOR3(g_aWater[nCount].pos.x + g_aWater[nCount].fWidth, g_aWater[nCount].pos.y - g_aWater[nCount].fHeight, 0.0f);
		pVtx[0].pos = D3DXVECTOR3(g_aWater[nCount].pos.x - g_aWater[nCount].fWidth, g_aWater[nCount].pos.y - g_aWater[nCount].fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aWater[nCount].pos.x + g_aWater[nCount].fWidth, g_aWater[nCount].pos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aWater[nCount].pos.x - g_aWater[nCount].fWidth, g_aWater[nCount].pos.y, 0.0f);

		//rhw�ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(0.8f, 0.73f, 0.5f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.8f, 0.73f, 0.5f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.8f, 0.73f, 0.5f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.8f, 0.73f, 0.5f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffWater->Unlock();
}

//���̏I������
void UninitWater(void)
{
	//�e�N�X�`���|�C���^�̔j��
	if (g_pTextureWater != NULL)
	{			   
		g_pTextureWater->Release();
		g_pTextureWater = NULL;
	}			   
	if (g_pTextureWaterVertical != NULL)
	{			  
		g_pTextureWaterVertical->Release();
		g_pTextureWaterVertical = NULL;
	}
	if (g_pTextureFire != NULL)
	{			  
		g_pTextureFire->Release();
		g_pTextureFire = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffWater != NULL)
	{
		g_pVtxBuffWater->Release();
		g_pVtxBuffWater = NULL;
	}
}

//���̍X�V
void UpdateWater(void)
{
	VERTEX_2D*pVtx;					//���_���ւ̃|�C���^
	int nCount;						//�����J�E���g����ϐ���錾

	MODE mode;						//���[�h

	mode = GetMode();				//���[�h�̎擾

	g_fMoveWater -= 0.01f;			

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffWater->Lock(0, 0, (void**)&pVtx, 0);

	for (nCount = 0; nCount < MAX_WATER; nCount++)
	{
		//�A�j���[�V��������
		if (g_aWater[nCount].bUse == true)
		{
			g_nAnimWater++;

			if (g_aWater[nCount].nType == 0)
			{//���ʐ��̏ꍇ

				if (g_nAnimWater % 30 == 29)
				{
					g_nAnimPattern ^= 1;
				}

				if (g_nAnimPattern == 0)
				{

					pVtx[(nCount * 4) + 0].tex = D3DXVECTOR2(0.01f - (g_fMoveWater * 3), 0.1f);
					pVtx[(nCount * 4) + 1].tex = D3DXVECTOR2(1.0f * (g_aWater[nCount].fWidth / 50.0f) - (g_fMoveWater * 3), 0.1f);
					pVtx[(nCount * 4) + 2].tex = D3DXVECTOR2(0.01f - (g_fMoveWater * 3), 1.0f);
					pVtx[(nCount * 4) + 3].tex = D3DXVECTOR2(1.0f * (g_aWater[nCount].fWidth / 50.0f) - (g_fMoveWater * 3), 1.0f);
				}
				else
				{
					pVtx[(nCount * 4) + 1].tex = D3DXVECTOR2(0.01f + (g_fMoveWater * 3), 0.1f);
					pVtx[(nCount * 4) + 0].tex = D3DXVECTOR2(1.0f * (g_aWater[nCount].fWidth / 50.0f) + (g_fMoveWater * 3), 0.1f);
					pVtx[(nCount * 4) + 3].tex = D3DXVECTOR2(0.01f + (g_fMoveWater * 3), 1.0f);
					pVtx[(nCount * 4) + 2].tex = D3DXVECTOR2(1.0f * (g_aWater[nCount].fWidth / 50.0f) + (g_fMoveWater * 3), 1.0f);
				}

				if (mode == MODE_GAME_FIRSTSTAGE_BOSS)
				{
					//���_�J���[�̐ݒ�
					pVtx[(nCount * 4) + 1].col = D3DXCOLOR(0.1f, 0.4f, 0.1f, 1.0f);
					pVtx[(nCount * 4) + 0].col = D3DXCOLOR(0.1f, 0.4f, 0.1f, 1.0f);
					pVtx[(nCount * 4) + 3].col = D3DXCOLOR(0.1f, 0.4f, 0.1f, 1.0f);
					pVtx[(nCount * 4) + 2].col = D3DXCOLOR(0.1f, 0.4f, 0.1f, 1.0f);
				}

			}
			else if (g_aWater[nCount].nType == 1)
			{//��̏ꍇ

				if (g_nAnimWater % 30 == 29)
				{
					g_nAnimPattern ^= 1;
				}

				if (g_nAnimPattern == 0)
				{
					pVtx[(nCount * 4) + 0].tex = D3DXVECTOR2(0.01f, g_fMoveWater);
					pVtx[(nCount * 4) + 1].tex = D3DXVECTOR2(1.0f * (g_aWater[nCount].fWidth / 50.0f), g_fMoveWater);
					pVtx[(nCount * 4) + 2].tex = D3DXVECTOR2(0.01f, g_fMoveWater + 1.0f * (g_aWater[nCount].fHeight / 130.0f));
					pVtx[(nCount * 4) + 3].tex = D3DXVECTOR2(1.0f * (g_aWater[nCount].fWidth / 50.0f), g_fMoveWater + 1.0f * (g_aWater[nCount].fHeight / 130.0f));
				}
				else
				{
					pVtx[(nCount * 4) + 1].tex = D3DXVECTOR2(0.01f, g_fMoveWater);
					pVtx[(nCount * 4) + 0].tex = D3DXVECTOR2(1.0f * (g_aWater[nCount].fWidth / 50.0f), g_fMoveWater);
					pVtx[(nCount * 4) + 3].tex = D3DXVECTOR2(0.01f, g_fMoveWater + 1.0f * (g_aWater[nCount].fHeight / 130.0f));
					pVtx[(nCount * 4) + 2].tex = D3DXVECTOR2(1.0f * (g_aWater[nCount].fWidth / 50.0f), g_fMoveWater + 1.0f * (g_aWater[nCount].fHeight / 130.0f));
				}

				//�����~�߂鏈��
				if (g_aWater[nCount].wState == WATERSTATE_CLOSING)
				{
					g_aWater[nCount].pos.y += 5.0f;
					g_aWater[nCount].fHeight -= 5.0f;
				}
				if (g_aWater[nCount].pos.y >= SCREEN_HEIGHT && g_aWater[nCount].fHeight <= 0.0f)
				{
					g_aWater[nCount].pos.y = 0.0f;
					g_aWater[nCount].fHeight = 0.0f;
					g_aWater[nCount].wState = WATERSTATE_READY;
				}
				//�����J���鏈��
				if (g_aWater[nCount].wState == WATERSTATE_OPEN)
				{
					if (g_aWater[nCount].fHeight < 650.0f)
					{
						g_aWater[nCount].fHeight += 5.0f;
					}
				}
			}
			else if (g_aWater[nCount].nType == 2)
			{
				if (g_nAnimWater % 25 == 24)
				{
					g_nAnimPatternFire++;
				}

				if (g_nAnimPatternFire >= 4)
				{
					g_nAnimPatternFire = 0;
				}

				pVtx[(nCount * 4) + 0].tex = D3DXVECTOR2(0.0f, 0.0f + (0.25f * g_nAnimPatternFire));
				pVtx[(nCount * 4) + 1].tex = D3DXVECTOR2(1.0f * (g_aWater[nCount].fWidth / 50.0f), 0.f + (0.25f * g_nAnimPatternFire));
				pVtx[(nCount * 4) + 2].tex = D3DXVECTOR2(0.0f, 0.25f + (0.25f * g_nAnimPatternFire));
				pVtx[(nCount * 4) + 3].tex = D3DXVECTOR2(1.0f * (g_aWater[nCount].fWidth / 50.0f), 0.25f + (0.25f * g_nAnimPatternFire));
			}

			//���_�ݒ�
			pVtx[(nCount * 4) + 1].pos = D3DXVECTOR3(g_aWater[nCount].pos.x + g_aWater[nCount].fWidth, g_aWater[nCount].pos.y, 0.0f);
			pVtx[(nCount * 4) + 0].pos = D3DXVECTOR3(g_aWater[nCount].pos.x - g_aWater[nCount].fWidth, g_aWater[nCount].pos.y, 0.0f);
			pVtx[(nCount * 4) + 3].pos = D3DXVECTOR3(g_aWater[nCount].pos.x + g_aWater[nCount].fWidth, g_aWater[nCount].pos.y + g_aWater[nCount].fHeight, 0.0f);
			pVtx[(nCount * 4) + 2].pos = D3DXVECTOR3(g_aWater[nCount].pos.x - g_aWater[nCount].fWidth, g_aWater[nCount].pos.y + g_aWater[nCount].fHeight, 0.0f);
			
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffWater->Unlock();
}

//���̕`�揈��
void DrawWater(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCount;							//�����J�E���g����ϐ���錾

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffWater, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCount = 0; nCount < MAX_WATER; nCount++)
	{
		if (g_aWater[nCount].bUse == true)
		{
			if (g_aWater[nCount].nType == 0)
			{
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureWater);
			}
			else if (g_aWater[nCount].nType == 1)
			{
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureWaterVertical);
			}
			else if (g_aWater[nCount].nType == 2)
			{
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureFire);
			}
			//�l�p�`��`�悷��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
		}
	}
}

//���̐ݒ�
void SetWater(D3DXVECTOR3 pos, int type, float width, float height, int nSwitch, WATERSTATE state)
{
	int nCount;						//�����J�E���g����ϐ���錾
	VERTEX_2D*pVtx;					//���_���ւ̃|�C���^
	
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffWater->Lock(0, 0, (void**)&pVtx, 0);

	for (nCount = 0; nCount < MAX_WATER; nCount++)
	{
		if (g_aWater[nSwitch].bUse == false)
		{
			g_aWater[nSwitch].pos = pos;				//�ʒu�̐ݒ�
			g_aWater[nSwitch].fHeight = height;			//�����̐ݒ�
			g_aWater[nSwitch].fWidth = width;			//���̐ݒ�
			g_aWater[nSwitch].nType = type;				//��ނ̐ݒ�
			g_aWater[nSwitch].nNumSwitch = nSwitch;		//�X�C�b�`�̔ԍ�
			g_aWater[nSwitch].wState = state;			//���̏��
			g_aWater[nSwitch].bUse = true;				//�g�p����Ă����Ԃɂ���

			//���_���W�̐ݒ�
			pVtx[(nSwitch * 4) + 0].pos = D3DXVECTOR3(g_aWater[nSwitch].pos.x - g_aWater[nSwitch].fWidth, g_aWater[nSwitch].pos.y, 0.0f);
			pVtx[(nSwitch * 4) + 1].pos = D3DXVECTOR3(g_aWater[nSwitch].pos.x + g_aWater[nSwitch].fWidth, g_aWater[nSwitch].pos.y, 0.0f);
			pVtx[(nSwitch * 4) + 2].pos = D3DXVECTOR3(g_aWater[nSwitch].pos.x - g_aWater[nSwitch].fWidth, g_aWater[nSwitch].pos.y + g_aWater[nSwitch].fHeight, 0.0f);
			pVtx[(nSwitch * 4) + 3].pos = D3DXVECTOR3(g_aWater[nSwitch].pos.x + g_aWater[nSwitch].fWidth, g_aWater[nSwitch].pos.y + g_aWater[nSwitch].fHeight, 0.0f);

			//�e�N�X�`�����W�̐ݒ�
			if (type == 0)
			{
				pVtx[(nSwitch * 4) + 0].tex = D3DXVECTOR2(0.01f, 0.1f);
				pVtx[(nSwitch * 4) + 1].tex = D3DXVECTOR2(1.0f * (g_aWater[nSwitch].fWidth / 50.0f), 0.1f);
				pVtx[(nSwitch * 4) + 2].tex = D3DXVECTOR2(0.01f, 1.0f);
				pVtx[(nSwitch * 4) + 3].tex = D3DXVECTOR2(1.0f * (g_aWater[nSwitch].fWidth / 50.0f), 1.0f);


				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(0.8f, 0.73f, 0.5f, 1.0f);
				pVtx[1].col = D3DXCOLOR(0.8f, 0.73f, 0.5f, 1.0f);
				pVtx[2].col = D3DXCOLOR(0.8f, 0.73f, 0.5f, 1.0f);
				pVtx[3].col = D3DXCOLOR(0.8f, 0.73f, 0.5f, 1.0f);


			}
			else if (type == 1)
			{
				pVtx[(nSwitch * 4) + 0].tex = D3DXVECTOR2(0.01f, g_fMoveWater);
				pVtx[(nSwitch * 4) + 1].tex = D3DXVECTOR2(1.0f * (g_aWater[nSwitch].fWidth / 50.0f), g_fMoveWater);
				pVtx[(nSwitch * 4) + 2].tex = D3DXVECTOR2(0.01f, g_fMoveWater + 1.0f * (g_aWater[nSwitch].fHeight / 130.0f));
				pVtx[(nSwitch * 4) + 3].tex = D3DXVECTOR2(1.0f * (g_aWater[nSwitch].fWidth / 50.0f), g_fMoveWater + 1.0f * (g_aWater[nSwitch].fHeight / 130.0f));

				//���_�J���[�̐ݒ�
				pVtx[(nSwitch * 4) + 0].col = D3DXCOLOR(0.8f, 0.73f, 0.5f, 0.6f);
				pVtx[(nSwitch * 4) + 1].col = D3DXCOLOR(0.8f, 0.73f, 0.5f, 0.6f);
				pVtx[(nSwitch * 4) + 2].col = D3DXCOLOR(0.8f, 0.73f, 0.5f, 0.6f);
				pVtx[(nSwitch * 4) + 3].col = D3DXCOLOR(0.8f, 0.73f, 0.5f, 0.6f);
			}
			if (type == 2)
			{
				//���_���W�̐ݒ�
				pVtx[(nCount * 4) + 0].pos = D3DXVECTOR3(g_aWater[nCount].pos.x - g_aWater[nCount].fWidth, g_aWater[nCount].pos.y - g_aWater[nCount].fHeight, 0.0f);
				pVtx[(nCount * 4) + 1].pos = D3DXVECTOR3(g_aWater[nCount].pos.x + g_aWater[nCount].fWidth, g_aWater[nCount].pos.y - g_aWater[nCount].fHeight, 0.0f);
				pVtx[(nCount * 4) + 2].pos = D3DXVECTOR3(g_aWater[nCount].pos.x - g_aWater[nCount].fWidth, g_aWater[nCount].pos.y, 0.0f);
				pVtx[(nCount * 4) + 3].pos = D3DXVECTOR3(g_aWater[nCount].pos.x + g_aWater[nCount].fWidth, g_aWater[nCount].pos.y, 0.0f);
					   
				pVtx[(nCount * 4) + 0].tex = D3DXVECTOR2(0.0f, 0.f);
				pVtx[(nCount * 4) + 1].tex = D3DXVECTOR2(1.0f * (g_aWater[nCount].fWidth / 50.0f), 0.f);
				pVtx[(nCount * 4) + 2].tex = D3DXVECTOR2(0.0f, 0.5f);
				pVtx[(nCount * 4) + 3].tex = D3DXVECTOR2(1.0f * (g_aWater[nCount].fWidth / 50.0f), 0.5f);


				//���_�J���[�̐ݒ�
				pVtx[(nCount * 4) + 0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.9f);
				pVtx[(nCount * 4) + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.9f);
				pVtx[(nCount * 4) + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.9f);
				pVtx[(nCount * 4) + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.9f);


			}

			break;
		}

	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffWater->Unlock();
}

//���̓����蔻��
int WaterInteraction(D3DXVECTOR3*pPos,			//���݂̈ʒu
	D3DXVECTOR3*pMove,
	float fWidth,								//��
	float fHeight)								//����)
{
	int nCount;						//�����J�E���g����ϐ���錾
	int nInWater = 0;

	for (nCount = 0; nCount < MAX_WATER; nCount++)
	{
		if (g_aWater[nCount].bUse == true)
		{//���̒��ɂ���ꍇ
			if (pPos->x + (fWidth * 0.5f) >= g_aWater[nCount].pos.x - g_aWater[nCount].fWidth &&
				pPos->x - (fWidth * 0.5f) <= g_aWater[nCount].pos.x + g_aWater[nCount].fWidth &&
				pPos->y >= g_aWater[nCount].pos.y&&
				pPos->y - fHeight <= g_aWater[nCount].pos.y + g_aWater[nCount].fHeight)
			{
				nInWater = 1;
			}
		}
	}

	return nInWater;
}

//���̏����擾
WATER*GetWater(void)
{
	return &g_aWater[0];
}