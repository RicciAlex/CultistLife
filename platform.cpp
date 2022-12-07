//===================================================//
//                                                   //
//      �A�N�V�����Q�[���v���b�g�t�H�[�� �֐�        //  
//                Author: Ricci Alex				 //
//                                                   //
//===================================================//

//�C���N���[�h�t�@�C��
#include "platform.h"
#include "player.h"
#include "Enemy.h"
#include "input.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTexturePlatform = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_apTexturePlatformG = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_apTexturePipe = NULL;			
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlatform = NULL;	//���_�o�b�t�@�ւ̃|�C���^
PLATFORM g_aPlatform[MAX_PLATFORM];					//�v���b�g�t�H�[���^�̔z���錾����

//�v���b�g�t�H�[���̏���������
void InitPlatform(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̏��ւ̃|�C���^
	VERTEX_2D*pVtx;					//���_���ւ̃|�C���^
	int nCount;						//�����J�E���g����ϐ���錾

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Block.png",
		&g_apTexturePlatform);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Griglia.png",
		&g_apTexturePlatformG);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Pipe_Sprite.png",
		&g_apTexturePipe);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_PLATFORM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlatform,
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlatform->Lock(0, 0, (void**)&pVtx, 0);

	for (nCount = 0; nCount < MAX_PLATFORM; nCount++)
	{
		//�e�v���b�g�t�H�[���̕ϐ��̏�����
		g_aPlatform[nCount].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPlatform[nCount].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPlatform[nCount].Memorymove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPlatform[nCount].fwidth = 5.0f;
		g_aPlatform[nCount].fHeight = 12.5f;
		g_aPlatform[nCount].fMaxX = 1280.0f;
		g_aPlatform[nCount].fMaxY = 780.0f;
		g_aPlatform[nCount].fMinX = 0.0f;
		g_aPlatform[nCount].fMinY = 0.0f;
		g_aPlatform[nCount].nType = 0;
		g_aPlatform[nCount].nMemory = 0;
		g_aPlatform[nCount].nCntStatus = 0;
		g_aPlatform[nCount].bUse = false;

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

		//�e�N�X�`�����W�̐ݒ�
		pVtx[(nCount * 4) + 0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[(nCount * 4) + 1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[(nCount * 4) + 2].tex = D3DXVECTOR2(0.0f, 0.3f);
		pVtx[(nCount * 4) + 3].tex = D3DXVECTOR2(1.0f, 0.3f);

	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlatform->Unlock();
}

//�v���b�g�t�H�[���̏I������
void UninitPlatform(void)
{

	//�e�N�X�`���|�C���^�̔j��
	if (g_apTexturePlatform != NULL)
	{
		g_apTexturePlatform->Release();
		g_apTexturePlatform = NULL;
	}
	if (g_apTexturePlatformG != NULL)
	{
		g_apTexturePlatformG->Release();
		g_apTexturePlatformG = NULL;
	}
	if (g_apTexturePipe != NULL)
	{			  
		g_apTexturePipe->Release();
		g_apTexturePipe = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPlatform != NULL)
	{
		g_pVtxBuffPlatform->Release();
		g_pVtxBuffPlatform = NULL;
	}
}

//�v���b�g�t�H�[���̍X�V����
void UpdatePlatform(void)
{
	VERTEX_2D*pVtx;					//���_���ւ̃|�C���^
	int nWater;
	Player*pPlayer;
	MODE mode;
	int*pSwitch;

	mode = GetMode();
	pPlayer = GetPlayer();
	pSwitch = GetActiveSwitch();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlatform->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < MAX_PLATFORM; nCount++)
	{
		if (g_aPlatform[nCount].bUse == true)
		{
			//��Ԃ̍X�V
			if (g_aPlatform[nCount].nCntStatus != 0)
			{
				g_aPlatform[nCount].nCntStatus--;

				if (g_aPlatform[nCount].nCntStatus <= 0)
				{
					g_aPlatform[nCount].nCntStatus = 0;

					g_aPlatform[nCount].nType = g_aPlatform[nCount].nMemory;
				}
			}

			//���̓����蔻��
			if (g_aPlatform[nCount].Memorymove != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
			{
				nWater = WaterInteraction(&g_aPlatform[nCount].Pos, &g_aPlatform[nCount].move, g_aPlatform[nCount].fwidth, g_aPlatform[nCount].fHeight);
				
				if (nWater == 1)
				{//���ɂ���ꍇ
					g_aPlatform[nCount].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}
				else if (nWater != 1 && g_aPlatform[nCount].move == D3DXVECTOR3(0.0f, 0.0f, 0.0f))
				{
					g_aPlatform[nCount].move = g_aPlatform[nCount].Memorymove;
				}

			}
			
			//�v���b�g�t�H�[���̈ʒu�̍X�V
			g_aPlatform[nCount].Pos += g_aPlatform[nCount].move;

			if ((g_aPlatform[nCount].Pos.x <= g_aPlatform[nCount].fMinX || g_aPlatform[nCount].Pos.x >= g_aPlatform[nCount].fMaxX) && g_aPlatform[nCount].move != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
			{
				g_aPlatform[nCount].move.x *= -1;
			}
			if ((g_aPlatform[nCount].Pos.y <= g_aPlatform[nCount].fMinY || g_aPlatform[nCount].Pos.y >= g_aPlatform[nCount].fMaxY) && g_aPlatform[nCount].move != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
			{
				g_aPlatform[nCount].move.y *= -1;
			}
			
			//���_���W�̍X�V
			pVtx[(nCount * 4) + 0].pos = D3DXVECTOR3(g_aPlatform[nCount].Pos.x - g_aPlatform[nCount].fwidth, g_aPlatform[nCount].Pos.y - g_aPlatform[nCount].fHeight, 0.0f);
			pVtx[(nCount * 4) + 1].pos = D3DXVECTOR3(g_aPlatform[nCount].Pos.x + g_aPlatform[nCount].fwidth, g_aPlatform[nCount].Pos.y - g_aPlatform[nCount].fHeight, 0.0f);
			pVtx[(nCount * 4) + 2].pos = D3DXVECTOR3(g_aPlatform[nCount].Pos.x - g_aPlatform[nCount].fwidth, g_aPlatform[nCount].Pos.y + g_aPlatform[nCount].fHeight, 0.0f);
			pVtx[(nCount * 4) + 3].pos = D3DXVECTOR3(g_aPlatform[nCount].Pos.x + g_aPlatform[nCount].fwidth, g_aPlatform[nCount].Pos.y + g_aPlatform[nCount].fHeight, 0.0f);

			//���_�J���[�̍X�V
			if (g_aPlatform[nCount].nType == 0)
			{
				pVtx[(nCount * 4) + 0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[(nCount * 4) + 1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[(nCount * 4) + 2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[(nCount * 4) + 3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

				if (mode == MODE_GAME_BONUSSTAGE && *pSwitch == 2)
				{
					g_aPlatform[nCount].bUse = false;
				}
			}
			else if (g_aPlatform[nCount].nType == 1)
			{
				pVtx[(nCount * 4) + 0].col = D3DCOLOR_RGBA(130, 230, 130, 255);
				pVtx[(nCount * 4) + 1].col = D3DCOLOR_RGBA(130, 230, 130, 255);
				pVtx[(nCount * 4) + 2].col = D3DCOLOR_RGBA(130, 230, 130, 255);
				pVtx[(nCount * 4) + 3].col = D3DCOLOR_RGBA(130, 230, 130, 255);
			}
			else if (g_aPlatform[nCount].nType == 2)
			{
				pVtx[(nCount * 4) + 0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[(nCount * 4) + 1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[(nCount * 4) + 2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[(nCount * 4) + 3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			}
			else if (g_aPlatform[nCount].nType == 3)
			{
				pVtx[(nCount * 4) + 0].col = D3DCOLOR_RGBA(55, 55, 200, 255);
				pVtx[(nCount * 4) + 1].col = D3DCOLOR_RGBA(55, 55, 200, 255);
				pVtx[(nCount * 4) + 2].col = D3DCOLOR_RGBA(55, 55, 200, 255);
				pVtx[(nCount * 4) + 3].col = D3DCOLOR_RGBA(55, 55, 200, 255);
			}
			else if (g_aPlatform[nCount].nType == 4)
			{
				pVtx[(nCount * 4) + 0].col = D3DCOLOR_RGBA(0, 255, 0, 255);
				pVtx[(nCount * 4) + 1].col = D3DCOLOR_RGBA(0, 255, 0, 255);
				pVtx[(nCount * 4) + 2].col = D3DCOLOR_RGBA(0, 255, 0, 255);
				pVtx[(nCount * 4) + 3].col = D3DCOLOR_RGBA(0, 255, 0, 255);
			}
			else if (g_aPlatform[nCount].nType == 5)
			{
				pVtx[(nCount * 4) + 0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[(nCount * 4) + 1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[(nCount * 4) + 2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[(nCount * 4) + 3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			}
			if (mode == MODE_GAME_BONUSSTAGE)
			{
				if (g_aPlatform[nCount].Pos.y < pPlayer->pos.y + 55.0f && g_aPlatform[nCount].Pos.y > pPlayer->pos.y - 130.0f &&
					g_aPlatform[nCount].Pos.x < pPlayer->pos.x + 125.0f && g_aPlatform[nCount].Pos.x > pPlayer->pos.x - 125.0f)
				{
					pVtx[(nCount * 4) + 0].col = D3DCOLOR_RGBA(150, 150, 150, 255);
					pVtx[(nCount * 4) + 1].col = D3DCOLOR_RGBA(150, 150, 150, 255);
					pVtx[(nCount * 4) + 2].col = D3DCOLOR_RGBA(150, 150, 150, 255);
					pVtx[(nCount * 4) + 3].col = D3DCOLOR_RGBA(150, 150, 150, 255);
				}
				else
				{
					pVtx[(nCount * 4) + 0].col = D3DCOLOR_RGBA(0, 0, 0, 255);
					pVtx[(nCount * 4) + 1].col = D3DCOLOR_RGBA(0, 0, 0, 255);
					pVtx[(nCount * 4) + 2].col = D3DCOLOR_RGBA(0, 0, 0, 255);
					pVtx[(nCount * 4) + 3].col = D3DCOLOR_RGBA(0, 0, 0, 255);
				}
			}
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlatform->Unlock();	
}

//�v���b�g�t�H�[���̕`�揈��
void DrawPlatform(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCount;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPlatform, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCount = 0; nCount < MAX_PLATFORM; nCount++)
	{
		if (g_aPlatform[nCount].bUse == true)
		{
			if (g_aPlatform[nCount].nMemory == 2)
			{
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_apTexturePlatformG);
			}
			else if(g_aPlatform[nCount].nMemory == 5)
			{
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_apTexturePipe);
			}
			else
			{
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_apTexturePlatform);
			}

			//�l�p�`��`�悷��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
		}
	}
}

//�v���b�g�t�H�[���̐ݒ菈��
void SetPlatform(D3DXVECTOR3 pos, D3DXVECTOR3 move, float width, float height, int Type, float fMaxX, float fMinX, float fMaxY, float fMinY)
{
	int nCount;
	VERTEX_2D*pVtx;					//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlatform->Lock(0, 0, (void**)&pVtx, 0);

	for (nCount = 0; nCount < MAX_PLATFORM; nCount++)
	{
		if (g_aPlatform[nCount].bUse == false)
		{
			g_aPlatform[nCount].Pos = pos;					//�v���b�g�t�H�[���̈ʒu�̐ݒ�
			g_aPlatform[nCount].move = move;				//�ړ���
			g_aPlatform[nCount].Memorymove = move;			//�ړ��ʂ̕ۑ�
			g_aPlatform[nCount].fwidth = width;				//�v���b�g�t�H�[���̕��̐ݒ�
			g_aPlatform[nCount].fHeight = height;			//�v���b�g�t�H�[���̍����̐ݒ�
			g_aPlatform[nCount].fMaxX = fMaxX;				
			g_aPlatform[nCount].fMinX = fMinX;
			g_aPlatform[nCount].fMinY = fMinY;
			g_aPlatform[nCount].fMaxY = fMaxY;
			g_aPlatform[nCount].nType = Type;				//�v���b�g�t�H�[���̎�ނ̐ݒ�
			g_aPlatform[nCount].nMemory = Type;				//��ނ̕ۑ�
			g_aPlatform[nCount].nCntStatus = 0;				//�X�e�[�^�X�J�E���^�[
			g_aPlatform[nCount].bUse = true;				//�v���b�g�t�H�[�����g�p����Ă���ɂ���

			//���_���W�̐ݒ�
			pVtx[(nCount * 4) + 0].pos = D3DXVECTOR3(g_aPlatform[nCount].Pos.x - g_aPlatform[nCount].fwidth, g_aPlatform[nCount].Pos.y - g_aPlatform[nCount].fHeight, 0.0f);
			pVtx[(nCount * 4) + 1].pos = D3DXVECTOR3(g_aPlatform[nCount].Pos.x + g_aPlatform[nCount].fwidth, g_aPlatform[nCount].Pos.y - g_aPlatform[nCount].fHeight, 0.0f);
			pVtx[(nCount * 4) + 2].pos = D3DXVECTOR3(g_aPlatform[nCount].Pos.x - g_aPlatform[nCount].fwidth, g_aPlatform[nCount].Pos.y + g_aPlatform[nCount].fHeight, 0.0f);
			pVtx[(nCount * 4) + 3].pos = D3DXVECTOR3(g_aPlatform[nCount].Pos.x + g_aPlatform[nCount].fwidth, g_aPlatform[nCount].Pos.y + g_aPlatform[nCount].fHeight, 0.0f);

			//�e�N�X�`�����W�̐ݒ�
			pVtx[(nCount * 4) + 0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[(nCount * 4) + 1].tex = D3DXVECTOR2(1.0f * (width / 50.0f), 0.0f);
			pVtx[(nCount * 4) + 2].tex = D3DXVECTOR2(0.0f, 0.3f * (height / 12.5f));
			pVtx[(nCount * 4) + 3].tex = D3DXVECTOR2(1.0f * (width / 50.0f), 0.3f * (height / 12.5f));

			//���_�J���[�̐ݒ�
			if (g_aPlatform[nCount].nType == 0)
			{
				pVtx[(nCount * 4) + 0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[(nCount * 4) + 1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[(nCount * 4) + 2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[(nCount * 4) + 3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			}
			else if(g_aPlatform[nCount].nType == 1)
			{
				pVtx[(nCount * 4) + 0].col = D3DCOLOR_RGBA(130, 230, 130, 255);
				pVtx[(nCount * 4) + 1].col = D3DCOLOR_RGBA(130, 230, 130, 255);
				pVtx[(nCount * 4) + 2].col = D3DCOLOR_RGBA(130, 230, 130, 255);
				pVtx[(nCount * 4) + 3].col = D3DCOLOR_RGBA(130, 230, 130, 255);
			}
			else if (g_aPlatform[nCount].nType == 2)
			{
				pVtx[(nCount * 4) + 0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[(nCount * 4) + 1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[(nCount * 4) + 2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[(nCount * 4) + 3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			}
			else if (g_aPlatform[nCount].nType == 3)
			{
				pVtx[(nCount * 4) + 0].col = D3DCOLOR_RGBA(55, 55, 200, 255);
				pVtx[(nCount * 4) + 1].col = D3DCOLOR_RGBA(55, 55, 200, 255);
				pVtx[(nCount * 4) + 2].col = D3DCOLOR_RGBA(55, 55, 200, 255);
				pVtx[(nCount * 4) + 3].col = D3DCOLOR_RGBA(55, 55, 200, 255);
			}
			else if (g_aPlatform[nCount].nType == 4)
			{
				pVtx[(nCount * 4) + 0].col = D3DCOLOR_RGBA(0, 0, 255, 255);
				pVtx[(nCount * 4) + 1].col = D3DCOLOR_RGBA(0, 0, 255, 255);
				pVtx[(nCount * 4) + 2].col = D3DCOLOR_RGBA(0, 0, 255, 255);
				pVtx[(nCount * 4) + 3].col = D3DCOLOR_RGBA(0, 0, 255, 255);
			}
			else if (g_aPlatform[nCount].nType == 5)
			{
				pVtx[(nCount * 4) + 0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[(nCount * 4) + 1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[(nCount * 4) + 2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[(nCount * 4) + 3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

				if (pos.x < 600.0f)
				{
					//�e�N�X�`�����W�̐ݒ�
					pVtx[(nCount * 4) + 0].tex = D3DXVECTOR2(0.0f, 0.0f);
					pVtx[(nCount * 4) + 1].tex = D3DXVECTOR2(0.5f, 0.0f);
					pVtx[(nCount * 4) + 2].tex = D3DXVECTOR2(0.0f, 0.5f);
					pVtx[(nCount * 4) + 3].tex = D3DXVECTOR2(0.5f, 0.5f);
				}
				else
				{
					pVtx[(nCount * 4) + 1].tex = D3DXVECTOR2(0.0f, 0.0f);
					pVtx[(nCount * 4) + 0].tex = D3DXVECTOR2(0.5f, 0.0f);
					pVtx[(nCount * 4) + 3].tex = D3DXVECTOR2(0.0f, 0.5f);
					pVtx[(nCount * 4) + 2].tex = D3DXVECTOR2(0.5f, 0.5f);
				}
				
			}
			else if (g_aPlatform[nCount].nType == 6)
			{
				pVtx[(nCount * 4) + 0].col = D3DCOLOR_RGBA(0, 0, 0, 255);
				pVtx[(nCount * 4) + 1].col = D3DCOLOR_RGBA(0, 0, 0, 255);
				pVtx[(nCount * 4) + 2].col = D3DCOLOR_RGBA(0, 0, 0, 255);
				pVtx[(nCount * 4) + 3].col = D3DCOLOR_RGBA(0, 0, 0, 255);
			}
			else if (g_aPlatform[nCount].nType == 7)
			{
				pVtx[(nCount * 4) + 0].col = D3DCOLOR_RGBA(255, 255, 255, 150);
				pVtx[(nCount * 4) + 1].col = D3DCOLOR_RGBA(255, 255, 255, 150);
				pVtx[(nCount * 4) + 2].col = D3DCOLOR_RGBA(255, 255, 255, 150);
				pVtx[(nCount * 4) + 3].col = D3DCOLOR_RGBA(255, 255, 255, 150);
			}

			break;
		}
	
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlatform->Unlock();
}

//�v���b�g�t�H�[���̏��̎擾
PLATFORM*GetPlatform(void)
{
	return &g_aPlatform[0];
}

//�v���b�g�t�H�[���̓����蔻��
int BlockInteraction(D3DXVECTOR3*pPos,			//���݂̈ʒu
	D3DXVECTOR3*pLastPos,						//�O��̈ʒu
	D3DXVECTOR3*pMove,							//�ړ���
	float fWidth,								//��
	float fHeight)								//����
{
	int nInteraction = 0;		

	Player*pPlayer;			//�v���C���[���ւ̃|�C���^
	Enemy*pEnemy;

	pPlayer = GetPlayer();	//�v���C���[�����擾
	pEnemy = GetEnemy();

	for (int nCntBlock = 0; nCntBlock < MAX_PLATFORM; nCntBlock++)
	{
		if (g_aPlatform[nCntBlock].bUse == true)
		{//�v���b�g�t�H�[�����g�p����Ă���ꍇ
			/*if (pPlayer->nCurrentPlatform == nCntBlock && 
				pPos->x + fWidth > g_aPlatform[nCntBlock].Pos.x - g_aPlatform[nCntBlock].fwidth &&
				pPos->x - fWidth < g_aPlatform[nCntBlock].Pos.x + g_aPlatform[nCntBlock].fwidth)
			{
				
				
					pPlayer->pos.y = g_aPlatform[nCntBlock].Pos.y - g_aPlatform[nCntBlock].fHeight;
					pMove->y = g_aPlatform[nCntBlock].move.y;
				
			}*/
			if (pPos->y > g_aPlatform[nCntBlock].Pos.y - (g_aPlatform[nCntBlock].fHeight) &&
				pLastPos->y <= g_aPlatform[nCntBlock].Pos.y - (g_aPlatform[nCntBlock].fHeight) - g_aPlatform[nCntBlock].move.y &&
				pPos->x > g_aPlatform[nCntBlock].Pos.x - g_aPlatform[nCntBlock].fwidth - (fWidth * 0.5f) &&
				pPos->x < g_aPlatform[nCntBlock].Pos.x + g_aPlatform[nCntBlock].fwidth + (fWidth * 0.5f))
			{//�v���b�g�t�H�[���ɒ��n
				nInteraction = 1;
				pPos->y = g_aPlatform[nCntBlock].Pos.y - (g_aPlatform[nCntBlock].fHeight);
				pMove->y = 0.0f + g_aPlatform[nCntBlock].move.y;
				if (g_aPlatform[nCntBlock].move.x != 0.0f)
				{
					pPos->x = pLastPos->x + g_aPlatform[nCntBlock].move.x + pMove->x;
				}
				
				if (g_aPlatform[nCntBlock].nType == 3)
				{
					nInteraction = 4;
				}
				else if (g_aPlatform[nCntBlock].nType == 4)
				{
					nInteraction = 5;
				}
				else if (g_aPlatform[nCntBlock].nType == 7)
				{
					nInteraction = 0;
					g_aPlatform[nCntBlock].bUse = false;
				}
				pPlayer->nCurrentPlatform = nCntBlock;
			}

			if (pLastPos->y  >= g_aPlatform[nCntBlock].Pos.y + (g_aPlatform[nCntBlock].fHeight) + fHeight &&
				pPos->y  < g_aPlatform[nCntBlock].Pos.y + (g_aPlatform[nCntBlock].fHeight) + fHeight &&
				pPos->x > (g_aPlatform[nCntBlock].Pos.x - pMove->x) - g_aPlatform[nCntBlock].fwidth - fWidth * 0.5f &&
				pPos->x < (g_aPlatform[nCntBlock].Pos.x + pMove->x) + g_aPlatform[nCntBlock].fwidth + fWidth * 0.5f &&
				pPlayer->MoveState == MOVESTATE_JUMP && g_aPlatform[nCntBlock].nType != 1)
			{//�����ɓ�����ꍇ
				pPos->y = g_aPlatform[nCntBlock].Pos.y + fHeight + (g_aPlatform[nCntBlock].fHeight);
				nInteraction = 2;
				if (pMove->y < 0.0f)
				{
					pMove->y = 0.0f;
				}
			}

			if (pLastPos->y == g_aPlatform[nCntBlock].Pos.y - (g_aPlatform[nCntBlock].fHeight) &&
				pLastPos->x <= g_aPlatform[nCntBlock].Pos.x + g_aPlatform[nCntBlock].fwidth + (fWidth * 0.5f)
				&& pLastPos->x >= g_aPlatform[nCntBlock].Pos.x - g_aPlatform[nCntBlock].fwidth - (fWidth * 0.5f)
				&& pPos->x < g_aPlatform[nCntBlock].Pos.x - g_aPlatform[nCntBlock].fwidth - (fWidth  * 0.5f) ||
				pLastPos->y == g_aPlatform[nCntBlock].Pos.y - (g_aPlatform[nCntBlock].fHeight) &&
				pLastPos->x <= g_aPlatform[nCntBlock].Pos.x + g_aPlatform[nCntBlock].fwidth + (fWidth * 0.5f)
				&& pLastPos->x >= g_aPlatform[nCntBlock].Pos.x - g_aPlatform[nCntBlock].fwidth - (fWidth  * 0.5f)
				&& pPos->x > g_aPlatform[nCntBlock].Pos.x + g_aPlatform[nCntBlock].fwidth + (fWidth * 0.5f))
			{//�v���b�g�t�H�[�����痎����ꍇ
				if (nInteraction != 1)
				{
					if (pEnemy->EncounterState != ENEMYSTATE_ENCOUNTER_TRUE)
					{
						nInteraction = 3;
					}
				}
			}

			if (pLastPos->x >= g_aPlatform[nCntBlock].Pos.x + (g_aPlatform[nCntBlock].fwidth) + (fWidth * 0.5f) &&
				pPos->x > g_aPlatform[nCntBlock].Pos.x - (g_aPlatform[nCntBlock].fwidth) - (fWidth * 0.5f) &&
				pPos->x < g_aPlatform[nCntBlock].Pos.x + (g_aPlatform[nCntBlock].fwidth) + (fWidth * 0.5f) &&
				pPos->y > g_aPlatform[nCntBlock].Pos.y - (g_aPlatform[nCntBlock].fHeight)
				&& pPos->y - fHeight < g_aPlatform[nCntBlock].Pos.y + (g_aPlatform[nCntBlock].fHeight))
			{//�E���ɓ�����ꍇ
				

					pPos->x = g_aPlatform[nCntBlock].Pos.x + (g_aPlatform[nCntBlock].fwidth) + (fWidth * 0.5f);
					pMove->x += g_aPlatform[nCntBlock].move.x;
				
			}

			if (pLastPos->x <= g_aPlatform[nCntBlock].Pos.x - (g_aPlatform[nCntBlock].fwidth) - (fWidth * 0.5f) &&
				pPos->x < g_aPlatform[nCntBlock].Pos.x + (g_aPlatform[nCntBlock].fwidth) + (fWidth * 0.5f) &&
				pPos->x > g_aPlatform[nCntBlock].Pos.x - (g_aPlatform[nCntBlock].fwidth) - (fWidth * 0.5f) &&
				pPos->y > g_aPlatform[nCntBlock].Pos.y - (g_aPlatform[nCntBlock].fHeight)
				&& pPos->y - fHeight < g_aPlatform[nCntBlock].Pos.y + (g_aPlatform[nCntBlock].fHeight))
			{//�����ɓ�����ꍇ
				
					pPos->x = g_aPlatform[nCntBlock].Pos.x - (g_aPlatform[nCntBlock].fwidth) - (fWidth * 0.5f) + g_aPlatform[nCntBlock].move.x;
					pMove->x += g_aPlatform[nCntBlock].move.x;
			}

			if (pPos->x > g_aPlatform[nCntBlock].Pos.x - (g_aPlatform[nCntBlock].fwidth) - (fWidth * 0.5f) &&
				pPos->x < g_aPlatform[nCntBlock].Pos.x + (fWidth * 0.5f) &&
				pPos->y > g_aPlatform[nCntBlock].Pos.y - (g_aPlatform[nCntBlock].fHeight)
				&& pPos->y - fHeight < g_aPlatform[nCntBlock].Pos.y + (g_aPlatform[nCntBlock].fHeight)
				&& g_aPlatform[nCntBlock].nType != 1 && g_aPlatform[nCntBlock].nType != 6)
			{
				pPos->x = g_aPlatform[nCntBlock].Pos.x - (g_aPlatform[nCntBlock].fwidth) - (fWidth * 0.5f);
			}
			if (pPos->x < g_aPlatform[nCntBlock].Pos.x + (g_aPlatform[nCntBlock].fwidth) + (fWidth * 0.5f) &&
				pPos->x > g_aPlatform[nCntBlock].Pos.x - (fWidth * 0.5f) &&
				pPos->y > g_aPlatform[nCntBlock].Pos.y - (g_aPlatform[nCntBlock].fHeight)
				&& pPos->y - fHeight < g_aPlatform[nCntBlock].Pos.y + (g_aPlatform[nCntBlock].fHeight)
					&& g_aPlatform[nCntBlock].nType != 1 && g_aPlatform[nCntBlock].nType != 6)
			{
				pPos->x = g_aPlatform[nCntBlock].Pos.x + (g_aPlatform[nCntBlock].fwidth) + (fWidth * 0.5f);
			}
		}
	}

	return nInteraction;				//�ϐ��̒l��Ԃ�
}

//�e�̓����蔻��
int BlockInteractionBullet(D3DXVECTOR3*pPos,
	D3DXVECTOR3*pLastPos,
	D3DXVECTOR3*pMove,
	float fWidth,
	float fHeight)
{
	int nInteraction = 0;

	for (int nCntBlock = 0; nCntBlock < MAX_PLATFORM; nCntBlock++)
	{
		if (g_aPlatform[nCntBlock].bUse == true)
		{//�v���b�g�t�H�[�����g�p����Ă���ꍇ
			if (pPos->y > g_aPlatform[nCntBlock].Pos.y - (g_aPlatform[nCntBlock].fHeight) + fHeight &&
				pLastPos->y <= g_aPlatform[nCntBlock].Pos.y - (g_aPlatform[nCntBlock].fHeight) - g_aPlatform[nCntBlock].move.y + fHeight&&
				pPos->x > g_aPlatform[nCntBlock].Pos.x - g_aPlatform[nCntBlock].fwidth - (fWidth * 0.5f) &&
				pPos->x < g_aPlatform[nCntBlock].Pos.x + g_aPlatform[nCntBlock].fwidth + (fWidth * 0.5f))
			{
				nInteraction = 1;

				g_aPlatform[nCntBlock].nType = 4;
				g_aPlatform[nCntBlock].nCntStatus = 300;
				
			}
		}
	}

	return nInteraction;
}

//�ŏ��̃X�e�[�W�̐ݒ�
void FirstStage(void)
{
	SetPlatform(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT - 25.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 700.0f, 25.0f, 0, 0.0f, 0.0f, 0.0f, 0.0f);				//�n��

	SetPlatform(D3DXVECTOR3(0.0f, 300.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10.0f, 310.0f, 0, 0.0f, 0.0f, 0.0f, 0.0f);
	SetPlatform(D3DXVECTOR3(SCREEN_WIDTH, 400.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10.0f, 200.0f, 0, 0.0f, 0.0f, 0.0f, 0.0f);

	//���̃v���b�g�t�H�[��
	SetPlatform(D3DXVECTOR3(45.0f, 605.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 115.0f, 12.5f, 0, 0.0f, 0.0f, 0.0f, 0.0f);												//1
	SetPlatform(D3DXVECTOR3((SCREEN_WIDTH * 0.2f) + 138.0f, 605.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 156.0f, 12.5f, 0, 0.0f, 0.0f, 0.0f, 0.0f);					//2
	SetPlatform(D3DXVECTOR3(909.0f, 605.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 179.0f, 12.5f, 0, 0.0f, 0.0f, 0.0f, 0.0f);											//3
	SetPlatform(D3DXVECTOR3(1257.0f, 605.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 90.0f, 12.5f, 0, 0.0f, 0.0f, 0.0f, 0.0f);											//4

	SetPlatform(D3DXVECTOR3(45.0f, SCREEN_HEIGHT - 707.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 115.0f, 12.5f, 0, 0.0f, 0.0f, 0.0f, 0.0f);								//�V��(1)
	SetPlatform(D3DXVECTOR3((SCREEN_WIDTH * 0.2f) + 138.0f, SCREEN_HEIGHT - 707.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 156.0f, 12.5f, 0, 0.0f, 0.0f, 0.0f, 0.0f);	//�V��(2)				
	SetPlatform(D3DXVECTOR3(909.0f, SCREEN_HEIGHT - 707.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 179.0f, 12.5f, 0, 0.0f, 0.0f, 0.0f, 0.0f);							//�V��(3)
	SetPlatform(D3DXVECTOR3(1237.0f, SCREEN_HEIGHT - 707.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 70.0f, 12.5f, 0, 0.0f, 0.0f, 0.0f, 0.0f);							//�V��(4)

																																										//���̃v���b�g�t�H�[��
	SetPlatform(D3DXVECTOR3(45.0f, 400.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 115.0f, 12.5f, 0, 0.0f, 0.0f, 0.0f, 0.0f);												//1
	SetPlatform(D3DXVECTOR3((SCREEN_WIDTH * 0.2f) + 138.0f, 400.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 156.0f, 12.5f, 0, 0.0f, 0.0f, 0.0f, 0.0f);					//2
	SetPlatform(D3DXVECTOR3(909.0f, 400.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 179.0f, 12.5f, 1, 0.0f, 0.0f, 0.0f, 0.0f);											//3
	SetPlatform(D3DXVECTOR3(1377.0f, 400.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 210.0f, 12.5f, 0, 0.0f, 0.0f, 0.0f, 0.0f);											//4

	SetPlatform(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 320.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), 50.0f, 12.5f, 1, 540.0f, 650.0f, 580.0f, 200.0f);						//�����v���b�g�t�H�[��
																																										//SetPlatform(D3DXVECTOR3(1005.0f, 500.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 12.5f, 0, 0.0f, 0.0f, 0.0f, 0.0f);											//�E���̃v���b�g�t�H�[��

	SetPlatform(D3DXVECTOR3(45.0f, 200.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 115.0f, 12.5f, 0, 0.0f, 0.0f, 0.0f, 0.0f);
	SetPlatform(D3DXVECTOR3(SCREEN_WIDTH * 0.87f + 5.0f, 200.0f, 0.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), 50.0f, 12.5f, 1, 1118.0f, 600.0f, 190.0f, 210.0f);						//��ԏ�̃v���b�g�t�H�[��
	SetPlatform(D3DXVECTOR3((SCREEN_WIDTH * 0.2f) + 138.0f, 200.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 156.0f, 12.5f, 1, 0.0f, 0.0f, 0.0f, 0.0f);					//��ԏ�̃v���b�g�t�H�[��
	SetPlatform(D3DXVECTOR3(1237.0f, 200.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 70.0f, 12.5f, 0, 0.0f, 0.0f, 0.0f, 0.0f);

	//�O���b�h
	SetPlatform(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 605.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 90.0f, 12.5f, 2, 0.0f, 0.0f, 0.0f, 0.0f);								//���̃O���b�h�i���j
	SetPlatform(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT - 707.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 90.0f, 12.5f, 2, 0.0f, 0.0f, 0.0f, 0.0f);				//���̃O���b�h�i��j
	SetPlatform(D3DXVECTOR3(SCREEN_WIDTH * 0.88f, 400.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 12.5f, 2, 0.0f, 0.0f, 0.0f, 0.0f);								//��̃O���b�h
	SetPlatform(D3DXVECTOR3(198.0f, 200.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 12.5f, 2, 0.0f, 0.0f, 0.0f, 0.0f);
	SetPlatform(D3DXVECTOR3(198.0f, 400.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 12.5f, 2, 0.0f, 0.0f, 0.0f, 0.0f);
	SetPlatform(D3DXVECTOR3(198.0f, SCREEN_HEIGHT - 707.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 12.5f, 2, 0.0f, 0.0f, 0.0f, 0.0f);								//�V��̃O���b�h�i1�j
	SetPlatform(D3DXVECTOR3(SCREEN_WIDTH * 0.88f, SCREEN_HEIGHT - 707.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 12.5f, 2, 0.0f, 0.0f, 0.0f, 0.0f);				//�V��̃O���b�h�i3�j
	SetPlatform(D3DXVECTOR3(SCREEN_WIDTH * 0.88f, 605.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 12.5f, 2, 0.0f, 0.0f, 0.0f, 0.0f);								//���̃O���b�h�i3�j
	SetPlatform(D3DXVECTOR3(198.0f, 605.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 12.5f, 2, 0.0f, 0.0f, 0.0f, 0.0f);												//���̃O���b�h�i1�j


	//��
	SetWater(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 620.0f, 0.0f), 0, SCREEN_WIDTH * 0.5f, 100.0f, 3, WATERSTATE_OPEN);													//���̐�
	SetWater(D3DXVECTOR3(198.0f, 0.0f, 0.0f), 1, 40.0f, 650.0f, 1, WATERSTATE_OPEN);																				//���̑�
	SetWater(D3DXVECTOR3(SCREEN_WIDTH * 0.88f, 0.0f, 0.0f), 1, 40.0f, 650.0f, 0, WATERSTATE_OPEN);																	//�E�̑�
	SetWater(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 0.0f, 0.0f), 1, 90.0f, 650.0f, 2, WATERSTATE_OPEN);																	//��
	
																																										//�X�C�b�`
	SetSwitch(D3DXVECTOR3(65.0f, 120.0f, 0.0f), 1, true);
	SetSwitch(D3DXVECTOR3(1250.0f, 330.0f, 0.0f), 2, true);
	SetSwitch(D3DXVECTOR3(1250.0f, 520.0f, 0.0f), 3, true);

	SetItem(D3DXVECTOR3(50.0f, 350.0f, 0.0f), D3DXVECTOR3(0.0f, 0.1f, 0.0f), 0);

	SetArrow(D3DXVECTOR3(1200.0f, 100.0f, 0.0f), D3DXVECTOR3(0.3f, 0.0f, 0.0f), 0);
}

//�ŏ��̃{�X�X�e�[�W�̐ݒ�
void SecondStage(void)
{
	SetPlatform(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT - 25.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 700.0f, 25.0f, 0, 0.0f, 0.0f, 0.0f, 0.0f);				//�n��
	SetPlatform(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 700.0f, 25.0f, 0, 0.0f, 0.0f, 0.0f, 0.0f);
	SetPlatform(D3DXVECTOR3(-10.0f, SCREEN_HEIGHT * 0.5, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10.0f, SCREEN_HEIGHT * 0.55, 0, 0.0f, 0.0f, 0.0f, 0.0f);
	SetPlatform(D3DXVECTOR3(SCREEN_WIDTH + 10.0f, SCREEN_HEIGHT * 0.5, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10.0f, SCREEN_HEIGHT * 0.55, 0, 0.0f, 0.0f, 0.0f, 0.0f);

	SetPlatform(D3DXVECTOR3(60, 610.0f, 0.0f), D3DXVECTOR3(0.0f, -2.0f, 0.0f), 50.0f, 12.5f, 1, 1230.0f, 600.0f, 610.0f, 240.0f);
	SetPlatform(D3DXVECTOR3(640, 250.0f, 0.0f), D3DXVECTOR3(0.0f, 2.0f, 0.0f), 80.0f, 12.5f, 1, 1230.0f, 600.0f, 610.0f, 240.0f);
	SetPlatform(D3DXVECTOR3(1220, 610.0f, 0.0f), D3DXVECTOR3(0.0f, -2.0f, 0.0f), 50.0f, 12.5f, 1, 1230.0f, 600.0f, 610.0f, 240.0f);

	SetPlatform(D3DXVECTOR3(215.0f, 450.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 90.0f, 12.5f, 1, 0.0f, 0.0f, 0.0f, 0.0f);												//1
	SetPlatform(D3DXVECTOR3((SCREEN_WIDTH * 0.2f) + 175.0f, 450.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 90.0f, 12.5f, 1, 0.0f, 0.0f, 0.0f, 0.0f);
	SetPlatform(D3DXVECTOR3(1065.0f, 450.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 90.0f, 12.5f, 1, 0.0f, 0.0f, 0.0f, 0.0f);												//1
	SetPlatform(D3DXVECTOR3(850.0f, 450.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 90.0f, 12.5f, 1, 0.0f, 0.0f, 0.0f, 0.0f);

	SetPlatform(D3DXVECTOR3(205.0f, 250.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 90.0f, 12.5f, 1, 0.0f, 0.0f, 0.0f, 0.0f);												//1
	SetPlatform(D3DXVECTOR3((SCREEN_WIDTH * 0.2f) + 195.0f, 250.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 90.0f, 12.5f, 1, 0.0f, 0.0f, 0.0f, 0.0f);
	SetPlatform(D3DXVECTOR3(1075.0f, 250.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 90.0f, 12.5f, 1, 0.0f, 0.0f, 0.0f, 0.0f);												//1
	SetPlatform(D3DXVECTOR3(830.0f, 250.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 90.0f, 12.5f, 1, 0.0f, 0.0f, 0.0f, 0.0f);

	SetPlatform(D3DXVECTOR3(-40.0f, 350.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, 5, 0.0f, 0.0f, 0.0f, 0.0f);
	SetPlatform(D3DXVECTOR3(SCREEN_WIDTH + 40.0f, 350.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, 5, 0.0f, 0.0f, 0.0f, 0.0f);
	SetPlatform(D3DXVECTOR3(-40.0f, 150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, 5, 0.0f, 0.0f, 0.0f, 0.0f);
	SetPlatform(D3DXVECTOR3(SCREEN_WIDTH + 40.0f, 150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, 5, 0.0f, 0.0f, 0.0f, 0.0f);


	SetWater(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 620.0f, 0.0f), 0, SCREEN_WIDTH * 0.5f, 130.0f, 3, WATERSTATE_OPEN);													//���̐�

	SetSwitch(D3DXVECTOR3(190.0f, 180.0f, 0.0f), 1, true);
	SetSwitch(D3DXVECTOR3(630.0f, 330.0f, 0.0f), 2, true);
	SetSwitch(D3DXVECTOR3(840.0f, 380.0f, 0.0f), 3, true);
	SetSwitch(D3DXVECTOR3(400.0f, 600.0f, 0.0f), 4, true);
}

void ThirdStage(void)
{
	SetPlatform(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 700.0f, 10.0f, 2, 0.0f, 0.0f, 0.0f, 0.0f);
	SetPlatform(D3DXVECTOR3(-10.0f, SCREEN_HEIGHT *0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10.0f, SCREEN_WIDTH * 0.6f, 0, 0.0f, 0.0f, 0.0f, 0.0f);
	SetPlatform(D3DXVECTOR3(SCREEN_WIDTH + 10.0f, SCREEN_HEIGHT *0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10.0f, SCREEN_WIDTH * 0.6f, 0, 0.0f, 0.0f, 0.0f, 0.0f);

	SetPlatform(D3DXVECTOR3(325.0f, 550.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 12.5f, 3, 0.0f, 0.0f, 0.0f, 0.0f);
	SetPlatform(D3DXVECTOR3(SCREEN_WIDTH - 325.0f, 550.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 12.5f, 3, 0.0f, 0.0f, 0.0f, 0.0f);
	SetPlatform(D3DXVECTOR3(30.0f, 200.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 12.5f, 3, 0.0f, 0.0f, 0.0f, 0.0f);
	SetPlatform(D3DXVECTOR3(SCREEN_WIDTH - 30.0f, 200.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 12.5f, 3, 0.0f, 0.0f, 0.0f, 0.0f);

	SetPlatform(D3DXVECTOR3(127.5f, 500.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 147.5f, 12.5f, 0, 0.0f, 0.0f, 0.0f, 0.0f);
	SetPlatform(D3DXVECTOR3(SCREEN_WIDTH - 127.5f, 500.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 147.5f, 12.5f, 0, 0.0f, 0.0f, 0.0f, 0.0f);
	SetPlatform(D3DXVECTOR3(127.5f, 300.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 147.5f, 12.5f, 0, 0.0f, 0.0f, 0.0f, 0.0f);
	SetPlatform(D3DXVECTOR3(SCREEN_WIDTH - 127.5f, 300.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 147.5f, 12.5f, 0, 0.0f, 0.0f, 0.0f, 0.0f);

	SetPlatform(D3DXVECTOR3(SCREEN_WIDTH *0.5, 400.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 12.5f, 1, 0.0f, 0.0f, 0.0f, 0.0f);
	SetPlatform(D3DXVECTOR3(SCREEN_WIDTH *0.5, 150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 400.0f, 12.5f, 3, 0.0f, 0.0f, 0.0f, 0.0f);


	SetSwitch(D3DXVECTOR3(50.0f, 625.0f, 0.0f), 1, true);
	SetSwitch(D3DXVECTOR3(1230.0f, 625.0f, 0.0f), 2, true);
	SetSwitch(D3DXVECTOR3(50.0f, 425.0f, 0.0f), 3, true);
	SetSwitch(D3DXVECTOR3(1230.0f, 425.0f, 0.0f), 4, true);
	SetSwitch(D3DXVECTOR3(50.0f, 250.0f, 0.0f), 5, true);
	SetSwitch(D3DXVECTOR3(1230.0f, 250.0f, 0.0f), 6, true);
	SetSwitch(D3DXVECTOR3(640.0f, 325.0f, 0.0f), 7, true);
	SetSwitch(D3DXVECTOR3(640.0f, 75.0f, 0.0f), 8, true);

	SetWater(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT - 25.0f, 0.0f), 2, SCREEN_WIDTH * 0.5f, 50.0f, 0, WATERSTATE_OPEN);

	

	/*SetMinion(D3DXVECTOR3(810.0f, 0.0f, 0.0f), D3DXVECTOR3(-10.0f, 0.0f, 0.0f), 1);
	SetMinion(D3DXVECTOR3(600.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2);
	SetMinion(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
	SetMinion(D3DXVECTOR3(640.0f, SCREEN_HEIGHT + 180.0f, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), 4);*/
}

void BonusStage(void)
{
	int nCnt;

	SetPlatform(D3DXVECTOR3(-10.0f, 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10.0f, 500.0f, 0, 0.0f, 0.0f, 0.0f, 0.0f);
	SetPlatform(D3DXVECTOR3(1290.0f, 250.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10.0f, 270.0f, 0, 0.0f, 0.0f, 0.0f, 0.0f);

	for (nCnt = 0; nCnt < 26; nCnt++)
	{
		SetPlatform(D3DXVECTOR3((nCnt * 50.0f) + 25.0f, SCREEN_HEIGHT - 25.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 26.0f, 25.0f, 6, 0.0f, 0.0f, 0.0f, 0.0f);
	}
	//SetPlatform(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT - 25.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 700.0f, 25.0f, 6, 0.0f, 0.0f, 0.0f, 0.0f);

	for (nCnt = 0; nCnt < 10; nCnt++)
	{
		SetPlatform(D3DXVECTOR3(25.0f + (nCnt * 50.0f), 520.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 26.0f, 12.5f, 6, 0.0f, 0.0f, 0.0f, 0.0f);
		SetPlatform(D3DXVECTOR3(801.0f + (nCnt * 50.0f), 520.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 26.0f, 12.5f, 6, 0.0f, 0.0f, 0.0f, 0.0f);
	}
	//SetPlatform(D3DXVECTOR3(250.0f, 520.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 250.0f, 12.5f, 6, 0.0f, 0.0f, 0.0f, 0.0f);
	//SetPlatform(D3DXVECTOR3(1030.0f, 520.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 250.0f, 12.5f, 6, 0.0f, 0.0f, 0.0f, 0.0f);

	SetPlatform(D3DXVECTOR3(640.0f, 530.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), 50.0f, 12.5f, 1, 0.0f, 0.0f, 655.0f, 520.0f);

	for (nCnt = 0; nCnt < 11; nCnt++)
	{
		SetPlatform(D3DXVECTOR3(350.0f + (nCnt * 50.0f), 330.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 26.0f, 12.5f, 6, 0.0f, 0.0f, 0.0f, 0.0f);
	}
	for (nCnt = 0; nCnt < 5; nCnt++)
	{
		SetPlatform(D3DXVECTOR3(25.0f + (nCnt * 50.0f), 330.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 26.0f, 12.5f, 6, 0.0f, 0.0f, 0.0f, 0.0f);
		SetPlatform(D3DXVECTOR3(1255.0f - (nCnt * 50.0f), 330.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 26.0f, 12.5f, 6, 0.0f, 0.0f, 0.0f, 0.0f);
	}
	/*SetPlatform(D3DXVECTOR3(120.0f, 330.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 120.0f, 12.5f, 6, 0.0f, 0.0f, 0.0f, 0.0f);
	SetPlatform(D3DXVECTOR3(1160.0f, 330.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 120.0f, 12.5f, 6, 0.0f, 0.0f, 0.0f, 0.0f);*/

	SetPlatform(D3DXVECTOR3(286.0f, 340.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), 38.0f, 12.5f, 1, 0.0f, 0.0f, 445.0f, 330.0f);
	SetPlatform(D3DXVECTOR3(952.0f, 340.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), 76.5f, 12.5f, 1, 0.0f, 0.0f, 445.0f, 330.0f);

	SetPlatform(D3DXVECTOR3(487.5f, 425.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 12.5f, 82.5f, 6, 0.0f, 0.0f, 0.0f, 0.0f);
	SetPlatform(D3DXVECTOR3(787.5f, 601.25f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 12.5f, 93.75f, 0, 0.0f, 0.0f, 0.0f, 0.0f);

	for (nCnt = 0; nCnt < 11; nCnt++)
	{
		SetPlatform(D3DXVECTOR3(350.0f + (nCnt * 50.0f), 185.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 26.0f, 12.5f, 6, 0.0f, 0.0f, 0.0f, 0.0f);
	}

	SetSwitch(D3DXVECTOR3(440.0f, 440.0f, 0.0f), 0, true);
	SetSwitch(D3DXVECTOR3(640.0f, 130.0f, 0.0f), 0, true);

	SetItem(D3DXVECTOR3(1250.0f, 620.0f, 0.0f), D3DXVECTOR3(0.0f, -0.1f, 0.0f), 0);

	SetArrow(D3DXVECTOR3(1150.0f, 600.0f, 0.0f), D3DXVECTOR3(0.3f, 0.0f, 0.0f), 0);
}

void FourthStage(void)
{
	SetPlatform(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT - 10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 700.0f, 10.0f, 0, 0.0f, 0.0f, 0.0f, 0.0f);

	SetPlatform(D3DXVECTOR3(0.0f - 10.0f, 300.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10.0f, 400.0f, 0, 0.0f, 0.0f, 0.0f, 0.0f);
	SetPlatform(D3DXVECTOR3(SCREEN_WIDTH + 10.0f, 400.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10.0f, 280.0f, 0, 0.0f, 0.0f, 0.0f, 0.0f);
	SetPlatform(D3DXVECTOR3(378.0f, 380.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10.0f, 85.0f, 0, 0.0f, 0.0f, 0.0f, 0.0f);

	SetPlatform(D3DXVECTOR3(45.0f, 605.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 115.0f, 10.0f, 1, 0.0f, 0.0f, 0.0f, 0.0f);												//1
	SetPlatform(D3DXVECTOR3((SCREEN_WIDTH * 0.2f) + 163.0f, 605.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 181.0f, 10.0f, 0, 0.0f, 0.0f, 0.0f, 0.0f);					//2
	SetPlatform(D3DXVECTOR3(884.0f, 605.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 204.0f, 10.0f, 0, 0.0f, 0.0f, 0.0f, 0.0f);											//3
	SetPlatform(D3DXVECTOR3(1257.0f, 605.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 90.0f, 10.0f, 7, 0.0f, 0.0f, 0.0f, 0.0f);											//4
	

	SetPlatform(D3DXVECTOR3(1257.0f, 405.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 90.0f, 10.0f, 7, 0.0f, 0.0f, 0.0f, 0.0f);


	SetPlatform(D3DXVECTOR3(45.0f, 455.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 115.0f, 10.0f, 0, 0.0f, 0.0f, 0.0f, 0.0f);
	SetPlatform(D3DXVECTOR3(313.0f, 455.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 75.0f, 10.0f, 0, 0.0f, 0.0f, 0.0f, 0.0f);


	SetPlatform(D3DXVECTOR3(45.0f, 305.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 115.0f, 10.0f, 0, 0.0f, 0.0f, 0.0f, 0.0f);
	SetPlatform(D3DXVECTOR3(313.0f, 305.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 75.0f, 10.0f, 0, 0.0f, 0.0f, 0.0f, 0.0f);


	SetPlatform(D3DXVECTOR3(640.0f, 500.0f, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), 40.0f, 10.0f, 1, 0.0f, 0.0f, 525.0f, 305.0f);
	SetPlatform(D3DXVECTOR3(1100.0f, 315.0f, 0.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), 40.0f, 10.0f, 1, 1100.0f, 740.0f, 315.0f, 125.0f);
	SetPlatform(D3DXVECTOR3(1100.0f, 315.0f, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), 40.0f, 10.0f, 1, 1100.0f, 740.0f, 315.0f, 125.0f);

	SetPlatform(D3DXVECTOR3(30.0f, 175.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 40.0f, 5, 0.0f, 0.0f, 0.0f, 0.0f);
	SetPlatform(D3DXVECTOR3(SCREEN_WIDTH - 35.0f, 160.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 40.0f, 5, 0.0f, 0.0f, 0.0f, 0.0f);


	SetPlatform(D3DXVECTOR3(SCREEN_WIDTH * 0.88f, 605.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 10.0f, 2, 0.0f, 0.0f, 0.0f, 0.0f);
	SetPlatform(D3DXVECTOR3(198.0f, 605.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 10.0f, 2, 0.0f, 0.0f, 0.0f, 0.0f);
	SetPlatform(D3DXVECTOR3(640.0f, 605.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 10.0f, 2, 0.0f, 0.0f, 0.0f, 0.0f);

	SetPlatform(D3DXVECTOR3(198.0f, 455.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 10.0f, 2, 0.0f, 0.0f, 0.0f, 0.0f);
	SetPlatform(D3DXVECTOR3(198.0f, 435.0f, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), 40.0f, 10.0f, 1, 0.0f, 0.0f, 435.0f, 125.0f);

	SetWater(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 640.0f, 0.0f), 0, SCREEN_WIDTH * 0.5f, 90.0f, 3, WATERSTATE_OPEN);													//���̐�
	SetWater(D3DXVECTOR3(198.0f, 0.0f, 0.0f), 1, 40.0f, 690.0f, 1, WATERSTATE_OPEN);																				//���̑�
	SetWater(D3DXVECTOR3(SCREEN_WIDTH * 0.88f, 0.0f, 0.0f), 1, 15.0f, 690.0f, 0, WATERSTATE_OPEN);																	//�E�̑�
	SetWater(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 0.0f, 0.0f), 1, 40.0f, 690.0f, 2, WATERSTATE_OPEN);

	//SetPlatform(D3DXVECTOR3(SCREEN_WIDTH - 50.0f, 400.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 280.0f, 0, 0.0f, 0.0f, 0.0f, 0.0f);

	SetSwitch(D3DXVECTOR3(30.0f, 75.0f, 0.0f), 0, true);
	SetSwitch(D3DXVECTOR3(320.0f, 400.0f, 0.0f), 1, true);
	SetSwitch(D3DXVECTOR3(50.0f, 650.0f, 0.0f), 2, true);

	SetItem(D3DXVECTOR3(1250.0f, 350.0f, 0.0f), D3DXVECTOR3(0.0f, 0.1f, 0.0f), 0);

	SetArrow(D3DXVECTOR3(1200.0f, 75.0f, 0.0f), D3DXVECTOR3(0.3f, 0.0f, 0.0f), 0);
}

void FifthStage(void)
{
	SetPlatform(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT - 10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 700.0f, 10.0f, 0, 0.0f, 0.0f, 0.0f, 0.0f);

	SetPlatform(D3DXVECTOR3(-10.0f, 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10.0f, 450.0f, 0, 0.0f, 0.0f, 0.0f, 0.0f);
	SetPlatform(D3DXVECTOR3(1290.0f, 510.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10.0f, 360.0f, 0, 0.0f, 0.0f, 0.0f, 0.0f);

	SetPlatform(D3DXVECTOR3(350.0f, 630.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10.0f, 80.0f, 0, 0.0f, 0.0f, 0.0f, 0.0f);
	SetPlatform(D3DXVECTOR3(350.0f, 420.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10.0f, 80.0f, 0, 0.0f, 0.0f, 0.0f, 0.0f);
	SetPlatform(D3DXVECTOR3(740.0f, 510.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10.0f, 50.0f, 0, 0.0f, 0.0f, 0.0f, 0.0f);

	SetPlatform(D3DXVECTOR3(80, 610.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 10.0f, 3, 0.0f, 0.0f, 0.0f, 0.0f);
	SetPlatform(D3DXVECTOR3(240, 560.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 10.0f, 3, 0.0f, 0.0f, 0.0f, 0.0f);
	SetPlatform(D3DXVECTOR3(40, 440.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 10.0f, 3, 0.0f, 0.0f, 0.0f, 0.0f);
	SetPlatform(D3DXVECTOR3(240, 390.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 10.0f, 3, 0.0f, 0.0f, 0.0f, 0.0f);

	SetPlatform(D3DXVECTOR3(700.0f, 160.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 450.0f, 10.0f, 0, 0.0f, 0.0f, 0.0f, 0.0f);
	SetPlatform(D3DXVECTOR3(125.0f, 160.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 125.0f, 10.0f, 7, 0.0f, 0.0f, 0.0f, 0.0f);

	SetPlatform(D3DXVECTOR3(1180.0f, 610.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 10.0f, 3, 0.0f, 0.0f, 0.0f, 0.0f);
	SetPlatform(D3DXVECTOR3(850.0f, 610.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 10.0f, 3, 0.0f, 0.0f, 0.0f, 0.0f);
	SetPlatform(D3DXVECTOR3(965.0f, 490.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 10.0f, 3, 0.0f, 0.0f, 0.0f, 0.0f);
	SetPlatform(D3DXVECTOR3(1180.0f, 420.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 10.0f, 3, 0.0f, 0.0f, 0.0f, 0.0f);

	SetPlatform(D3DXVECTOR3(1210.0f, 300.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 70.0f, 10.0f, 1, 0.0f, 0.0f, 0.0f, 0.0f);

	SetPlatform(D3DXVECTOR3(1210.0f, 230.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 70.0f, 10.0f, 1, 0.0f, 0.0f, 0.0f, 0.0f);


	SetEnemy(D3DXVECTOR3(1200.0f, 550.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMYTYPE_CARD_HEART);
	SetEnemy(D3DXVECTOR3(640.0f, 125.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMYTYPE_CARD_HEART);
	SetEnemy(D3DXVECTOR3(1200.0f, 390.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMYTYPE_CARD_DIAMOND);
	SetEnemy(D3DXVECTOR3(720.0f, 550.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMYTYPE_CARD_DIAMOND);
	SetEnemy(D3DXVECTOR3(1200.0f, 670.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMYTYPE_CARD_CLUB);
	SetEnemy(D3DXVECTOR3(30.0f, 290.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMYTYPE_CARD_SPADE);
	SetEnemy(D3DXVECTOR3(1250.0f, 290.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMYTYPE_CARD_SPADE);
	SetItem(D3DXVECTOR3(100.0f, 100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.1f, 0.0f), 0);

	SetArrow(D3DXVECTOR3(1200.0f, 75.0f, 0.0f), D3DXVECTOR3(0.3f, 0.0f, 0.0f), 0);
}