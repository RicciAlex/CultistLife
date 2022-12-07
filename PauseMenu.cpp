#include "main.h"
#include "PauseMenu.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "game.h"

LPDIRECT3DTEXTURE9 g_apTexturePauseMenu = NULL;	    //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_apTexturePauseMenuWritings = NULL;	    //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_apTexturePauseMenuRetry = NULL;	    //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseMenu = NULL;		//���_�o�b�t�@�ւ̃|�C���^
int g_SelectPauseOption;
bool g_bPause;

void InitPauseMenu(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;					//���_���ւ̃|�C���^
	int nCount;

	pDevice = GetDevice();
	g_SelectPauseOption = MENUOPTION_CONTINUE;
	g_bPause = false;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\PauseMenu.png",
		&g_apTexturePauseMenu);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\PauseMenu_Writings.png",
		&g_apTexturePauseMenuWritings);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Retry.png",
		&g_apTexturePauseMenuRetry);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 5,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseMenu,
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPauseMenu->Lock(0, 0, (void**)&pVtx, 0);

	//���_�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);

	pVtx[4].pos = D3DXVECTOR3(100.0f, 80.0f, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(SCREEN_WIDTH - 100.0f, 80.0f, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(100.0f, SCREEN_HEIGHT - 80.0f, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(SCREEN_WIDTH - 100.0f, SCREEN_HEIGHT - 80.0f, 0.0f);

	pVtx[8].pos = D3DXVECTOR3(540.0f, 270.0f, 0.0f);
	pVtx[9].pos = D3DXVECTOR3(740.0f, 270.0f, 0.0f);
	pVtx[10].pos = D3DXVECTOR3(540.0f, 320.0f, 0.0f);
	pVtx[11].pos = D3DXVECTOR3(740.0f, 320.0f, 0.0f);

	pVtx[12].pos = D3DXVECTOR3(540.0f, 400.0f, 0.0f);
	pVtx[13].pos = D3DXVECTOR3(740.0f, 400.0f, 0.0f);
	pVtx[14].pos = D3DXVECTOR3(540.0f, 450.0f, 0.0f);
	pVtx[15].pos = D3DXVECTOR3(740.0f, 450.0f, 0.0f);

	pVtx[16].pos = D3DXVECTOR3(440.0f, 335.0f, 0.0f);
	pVtx[17].pos = D3DXVECTOR3(840.0f, 335.0f, 0.0f);
	pVtx[18].pos = D3DXVECTOR3(440.0f, 385.0f, 0.0f);
	pVtx[19].pos = D3DXVECTOR3(840.0f, 385.0f, 0.0f);

	for (nCount = 1; nCount < 5; nCount++)
	{
		//rhw�̐ݒ�
		pVtx[(nCount * 4)].rhw = 1.0f;
		pVtx[(nCount * 4) + 1].rhw = 1.0f;
		pVtx[(nCount * 4) + 2].rhw = 1.0f;
		pVtx[(nCount * 4) + 3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[(nCount * 4)].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[(nCount * 4) + 1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[(nCount * 4) + 2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[(nCount * 4) + 3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[9].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[10].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[11].tex = D3DXVECTOR2(1.0f, 0.5f);

	pVtx[12].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[13].tex = D3DXVECTOR2(1.0f, 0.5f);
	pVtx[14].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[15].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx[16].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[17].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[18].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[19].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPauseMenu->Unlock();
}

//���j���[�̏I������
void UninitPauseMenu(void)
{
	//�e�N�X�`���̔j��
	if (g_apTexturePauseMenu != NULL)
	{
		g_apTexturePauseMenu->Release();
		g_apTexturePauseMenu = NULL;
	}
	if (g_apTexturePauseMenuWritings != NULL)
	{
		g_apTexturePauseMenuWritings->Release();
		g_apTexturePauseMenuWritings = NULL;
	}
	if (g_apTexturePauseMenuRetry != NULL)
	{
		g_apTexturePauseMenuRetry->Release();
		g_apTexturePauseMenuRetry = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPauseMenu != NULL)
	{
		g_pVtxBuffPauseMenu->Release();
		g_pVtxBuffPauseMenu = NULL;
	}
}

//���j���[�̍X�V����
void UpdatePauseMenu(void)
{
	VERTEX_2D*pVtx;					//���_���ւ̃|�C���^

	if (g_bPause == true)
	{

		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			switch (g_SelectPauseOption)
			{
			case MENUOPTION_CONTINUE:
				break;

			case MENUOPTION_RETRY:

				SetFade(MODE_GAME_FIRSTSTAGE_1);

				break;

			case MENUOPTION_QUIT:

				//�t�F�[�h�̐ݒ�
				SetFade(MODE_TITLE);

				break;
			}

			PlaySound(SOUND_LABEL_SE_CLICK);

			g_bPause = false;

		}

		if (GetKeyboardTrigger(DIK_W) == true || GetKeyboardTrigger(DIK_UP) == true)
		{
			g_SelectPauseOption--;

			PlaySound(SOUND_LABEL_SE_SELOPTION);

			if (g_SelectPauseOption <= -1)
			{
				g_SelectPauseOption = 2;
			}
		}
		if (GetKeyboardTrigger(DIK_S) == true || GetKeyboardTrigger(DIK_DOWN) == true)
		{
			g_SelectPauseOption++;

			PlaySound(SOUND_LABEL_SE_SELOPTION);

			if (g_SelectPauseOption >= 3)
			{
				g_SelectPauseOption = 0;
			}
		}

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffPauseMenu->Lock(0, 0, (void**)&pVtx, 0);

		switch (g_SelectPauseOption)
		{
		case MENUOPTION_CONTINUE:

			pVtx[8].pos = D3DXVECTOR3(490.0f, 170.0f, 0.0f);
			pVtx[9].pos = D3DXVECTOR3(790.0f, 170.0f, 0.0f);
			pVtx[10].pos = D3DXVECTOR3(490.0f, 320.0f, 0.0f);
			pVtx[11].pos = D3DXVECTOR3(790.0f, 320.0f, 0.0f);

			pVtx[12].pos = D3DXVECTOR3(540.0f, 400.0f, 0.0f);
			pVtx[13].pos = D3DXVECTOR3(740.0f, 400.0f, 0.0f);
			pVtx[14].pos = D3DXVECTOR3(540.0f, 450.0f, 0.0f);
			pVtx[15].pos = D3DXVECTOR3(740.0f, 450.0f, 0.0f);

			pVtx[16].pos = D3DXVECTOR3(440.0f, 300.0f, 0.0f);
			pVtx[17].pos = D3DXVECTOR3(840.0f, 300.0f, 0.0f);
			pVtx[18].pos = D3DXVECTOR3(440.0f, 390.0f, 0.0f);
			pVtx[19].pos = D3DXVECTOR3(840.0f, 390.0f, 0.0f);

			pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			pVtx[12].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[13].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[14].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[15].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

			pVtx[16].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[17].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[18].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[19].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

			break;

		case MENUOPTION_RETRY:

			pVtx[8].pos = D3DXVECTOR3(540.0f, 210.0f, 0.0f);
			pVtx[9].pos = D3DXVECTOR3(740.0f, 210.0f, 0.0f);
			pVtx[10].pos = D3DXVECTOR3(540.0f, 260.0f, 0.0f);
			pVtx[11].pos = D3DXVECTOR3(740.0f, 260.0f, 0.0f);

			pVtx[12].pos = D3DXVECTOR3(540.0f, 400.0f, 0.0f);
			pVtx[13].pos = D3DXVECTOR3(740.0f, 400.0f, 0.0f);
			pVtx[14].pos = D3DXVECTOR3(540.0f, 450.0f, 0.0f);
			pVtx[15].pos = D3DXVECTOR3(740.0f, 450.0f, 0.0f);

			pVtx[16].pos = D3DXVECTOR3(390.0f, 270.0f, 0.0f);
			pVtx[17].pos = D3DXVECTOR3(890.0f, 270.0f, 0.0f);
			pVtx[18].pos = D3DXVECTOR3(390.0f, 420.0f, 0.0f);
			pVtx[19].pos = D3DXVECTOR3(890.0f, 420.0f, 0.0f);

			pVtx[8].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[9].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[10].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[11].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

			pVtx[12].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[13].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[14].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[15].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

			pVtx[16].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[17].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[18].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[19].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			break;

		case MENUOPTION_QUIT:

			pVtx[8].pos = D3DXVECTOR3(540.0f, 210.0f, 0.0f);
			pVtx[9].pos = D3DXVECTOR3(740.0f, 210.0f, 0.0f);
			pVtx[10].pos = D3DXVECTOR3(540.0f, 260.0f, 0.0f);
			pVtx[11].pos = D3DXVECTOR3(740.0f, 260.0f, 0.0f);

			pVtx[12].pos = D3DXVECTOR3(490.0f, 370.0f, 0.0f);
			pVtx[13].pos = D3DXVECTOR3(790.0f, 370.0f, 0.0f);
			pVtx[14].pos = D3DXVECTOR3(490.0f, 520.0f, 0.0f);
			pVtx[15].pos = D3DXVECTOR3(790.0f, 520.0f, 0.0f);

			pVtx[16].pos = D3DXVECTOR3(440.0f, 300.0f, 0.0f);
			pVtx[17].pos = D3DXVECTOR3(840.0f, 300.0f, 0.0f);
			pVtx[18].pos = D3DXVECTOR3(440.0f, 390.0f, 0.0f);
			pVtx[19].pos = D3DXVECTOR3(840.0f, 390.0f, 0.0f);

			pVtx[8].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[9].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[10].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[11].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

			pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[14].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[15].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			pVtx[16].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[17].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[18].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[19].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

			break;
		}
	}

}

void DrawPauseMenu(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPauseMenu, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_bPause == true)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);

		//�l�p�`��`�悷��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTexturePauseMenu);

		//�l�p�`��`�悷��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4, 2);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTexturePauseMenuWritings);

		//�l�p�`��`�悷��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 8, 2);

		//�l�p�`��`�悷��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 12, 2);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTexturePauseMenuRetry);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 16, 2);
	}
}

void SetPauseMenu(void)
{
	g_bPause = true;
}

bool GetPauseMenu(void)
{
	return g_bPause;
}