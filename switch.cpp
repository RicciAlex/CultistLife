//===================================================//
//                                                   //
//    �@ �@  �A�N�V�����Q�[���X�C�b�` �֐�       �@  //  
//                Author: Ricci Alex				 //
//                                                   //
//===================================================//

//�C���N���[�h�t�@�C��
#include "switch.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureSwitch = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSwitch = NULL;	//���_�o�b�t�@�ւ̃|�C���^
SWITCH g_aSwitch[MAX_SWITCH];						//�v���b�g�t�H�[���^�̔z���錾����
int g_nCountDelaySwitch[MAX_SWITCH];				
int g_nActive;

//�X�C�b�`�̏���������
void InitSwitch(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̏��ւ̃|�C���^
	VERTEX_2D*pVtx;					//���_���ւ̃|�C���^
	int nCount;						//�����J�E���g����ϐ���錾
	g_nActive = 0;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\LevaSprite.png",
		&g_apTextureSwitch);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SWITCH,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSwitch,
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffSwitch->Lock(0, 0, (void**)&pVtx, 0);

	for (nCount = 0; nCount < MAX_SWITCH; nCount++)
	{
		//�X�C�b�`�^�̕ϐ��̊e�p�����[�^�̏�����
		g_aSwitch[nCount].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSwitch[nCount].nCountSwitch = 0;
		g_aSwitch[nCount].bActive = false;
		g_aSwitch[nCount].bUse = false;

		g_nCountDelaySwitch[nCount] = 0;
		
		//���_���W�̐ݒ�
		pVtx[(nCount * 4) + 0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[(nCount * 4) + 1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[(nCount * 4) + 2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[(nCount * 4) + 3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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

		//�e�N�X�`�����_�̐ݒ�
		pVtx[(nCount * 4) + 0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[(nCount * 4) + 1].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[(nCount * 4) + 2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[(nCount * 4) + 3].tex = D3DXVECTOR2(0.5f, 1.0f);
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSwitch->Unlock();
}

//�X�C�b�`�̏I������
void UninitSwitch(void)
{
	//�e�N�X�`���|�C���^�̔j��
	if (g_apTextureSwitch != NULL)
	{			   
		g_apTextureSwitch->Release();
		g_apTextureSwitch = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffSwitch != NULL)
	{			  
		g_pVtxBuffSwitch->Release();
		g_pVtxBuffSwitch = NULL;
	}
}

//�X�C�b�`�̍X�V����
void UpdateSwitch(void)
{
	Player*pPlayer;					//�v���C���[�̏��ւ̃|�C���^
	VERTEX_2D*pVtx;					//���_���ւ̃|�C���^
	WATER*pWater;					//���̏��ւ̃|�C���^
	MODE mode;

	mode = GetMode();
	pWater = GetWater();			//���̏����擾
	pPlayer = GetPlayer();			//�v���C���[�̏��̎擾

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffSwitch->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < MAX_SWITCH; nCount++, pWater++)
	{
		if (g_aSwitch[nCount].bUse == true)
		{
			if (mode == MODE_GAME_FIRSTSTAGE_BOSS && g_nActive == 0 || mode == MODE_GAME_SECONDSTAGE_BOSS && g_nActive == 0)
			{
				g_aSwitch[nCount].bActive = true;
			}

			if (g_nCountDelaySwitch[nCount] > 0)
			{
				g_nCountDelaySwitch[nCount]--;
			}

			if (g_aSwitch[nCount].Pos.x >= pPlayer->pos.x - PLAYER_WIDTH / 2 &&
				g_aSwitch[nCount].Pos.x <= pPlayer->pos.x + PLAYER_WIDTH / 2 &&
				g_aSwitch[nCount].Pos.y <= pPlayer->pos.y &&
				g_aSwitch[nCount].Pos.y >= pPlayer->pos.y - PLAYER_HEIGHT &&
				g_nCountDelaySwitch[nCount] <= 0)
			{

				if (GetKeyboardTrigger(DIK_RETURN) == true)
				{
					if (g_aSwitch[nCount].bActive == true)
					{
						g_aSwitch[nCount].bActive = false;
						if (mode == MODE_GAME_FIRSTSTAGE_1 || mode == MODE_GAME_FIRSTSTAGE_2)
						{
							pWater->wState = WATERSTATE_CLOSING;
						}
						else if (mode == MODE_GAME_FIRSTSTAGE_BOSS || mode == MODE_GAME_BONUSSTAGE || mode == MODE_GAME_SECONDSTAGE_BOSS)
						{
							g_nActive++;
						}
					}
					else if (g_aSwitch[nCount].bActive == false)
					{
						g_aSwitch[nCount].bActive = true;
						if (mode == MODE_GAME_FIRSTSTAGE_1 || mode == MODE_GAME_FIRSTSTAGE_2)
						{
							pWater->wState = WATERSTATE_OPEN;
						}
						else if (mode == MODE_GAME_FIRSTSTAGE_BOSS || mode == MODE_GAME_BONUSSTAGE || mode == MODE_GAME_SECONDSTAGE_BOSS)
						{
							g_nActive--;
						}
					}
					g_nCountDelaySwitch[nCount] = 180;

				}

			}
			
			//�e�N�X�`�����W�̍X�V
			if (g_aSwitch[nCount].bActive == true)
			{
				pVtx[(nCount * 4) + 0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[(nCount * 4) + 1].tex = D3DXVECTOR2(0.5f, 0.0f);
				pVtx[(nCount * 4) + 2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[(nCount * 4) + 3].tex = D3DXVECTOR2(0.5f, 1.0f);
			}
			else
			{
				pVtx[(nCount * 4) + 0].tex = D3DXVECTOR2(0.5f, 0.0f);
				pVtx[(nCount * 4) + 1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[(nCount * 4) + 2].tex = D3DXVECTOR2(0.5f, 1.0f);
				pVtx[(nCount * 4) + 3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}

			//===================================================================
			if (mode == MODE_GAME_BONUSSTAGE)
			{
				if (g_aSwitch[nCount].Pos.y < pPlayer->pos.y + 55.0f && g_aSwitch[nCount].Pos.y > pPlayer->pos.y - 130.0f &&
					g_aSwitch[nCount].Pos.x < pPlayer->pos.x + 120.0f && g_aSwitch[nCount].Pos.x > pPlayer->pos.x - 120.0f)
				{
					pVtx[(nCount * 4) + 0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[(nCount * 4) + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[(nCount * 4) + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[(nCount * 4) + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				}
				else
				{
					pVtx[(nCount * 4) + 0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
					pVtx[(nCount * 4) + 1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
					pVtx[(nCount * 4) + 2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
					pVtx[(nCount * 4) + 3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
				}
			}
			//===================================================================
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSwitch->Unlock();
}

//�X�C�b�`�̕`�揈��
void DrawSwitch(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCount;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffSwitch, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCount = 0; nCount < MAX_SWITCH; nCount++)
	{
		if (g_aSwitch[nCount].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureSwitch);


			//�l�p�`��`�悷��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
		}
	}
}

//�X�C�b�`�̐ݒ菈��
void SetSwitch(D3DXVECTOR3 pos, int nNumberSwitch, bool Active)
{
	int nCount;
	VERTEX_2D*pVtx;					//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffSwitch->Lock(0, 0, (void**)&pVtx, 0);

	for (nCount = 0; nCount < MAX_SWITCH; nCount++)
	{
		if (g_aSwitch[nCount].bUse == false)
		{
			//�X�C�b�`�̊e�p�����[�^�̐ݒ�
			g_aSwitch[nCount].Pos = pos;							//�X�C�b�`�̈ʒu
			g_aSwitch[nCount].nCountSwitch = nNumberSwitch;			//�X�C�b�`�̔ԍ�
			g_aSwitch[nCount].bActive = Active;						//�X�C�b�`�̏��
			g_aSwitch[nCount].bUse = true;							//�X�C�b�`���g�p����Ă����Ԃɂ���

			//���_���W�̐ݒ�
			pVtx[(nCount * 4) + 0].pos = D3DXVECTOR3(g_aSwitch[nCount].Pos.x - 15.0f, g_aSwitch[nCount].Pos.y - 15.0f, 0.0f);
			pVtx[(nCount * 4) + 1].pos = D3DXVECTOR3(g_aSwitch[nCount].Pos.x + 15.0f, g_aSwitch[nCount].Pos.y - 15.0f, 0.0f);
			pVtx[(nCount * 4) + 2].pos = D3DXVECTOR3(g_aSwitch[nCount].Pos.x - 15.0f, g_aSwitch[nCount].Pos.y + 15.0f, 0.0f);
			pVtx[(nCount * 4) + 3].pos = D3DXVECTOR3(g_aSwitch[nCount].Pos.x + 15.0f, g_aSwitch[nCount].Pos.y + 15.0f, 0.0f);

			//�e�N�X�`�����W�̐ݒ�
			if (Active == true)
			{
				pVtx[(nCount * 4) + 0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[(nCount * 4) + 1].tex = D3DXVECTOR2(0.5f, 0.0f);
				pVtx[(nCount * 4) + 2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[(nCount * 4) + 3].tex = D3DXVECTOR2(0.5f, 1.0f);
			}
			else
			{
				pVtx[(nCount * 4) + 0].tex = D3DXVECTOR2(0.5f, 0.0f);
				pVtx[(nCount * 4) + 1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[(nCount * 4) + 2].tex = D3DXVECTOR2(0.5f, 1.0f);
				pVtx[(nCount * 4) + 3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}
			break;
		}
		
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSwitch->Unlock();
}

int*GetActiveSwitch(void)
{
	return &g_nActive;
}