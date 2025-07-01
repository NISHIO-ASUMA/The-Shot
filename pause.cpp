//---------------------------
//
//�|�[�Y����
//Author:NISHIO ASUMA
//
//---------------------------

#include "pause.h"
#include "fade.h"
#include "input.h"
#include "game.h"
#include "sound.h"


//�O���[�o��
LPDIRECT3DTEXTURE9 g_apTexturePause[MAX_PAUSE_TEX] = {};	//�e�N�X�`���ւ̃|�C���^(4����)
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;				//���_�o�b�t�@�̃|�C���^

LPDIRECT3DTEXTURE9 g_apTexturearufa = NULL;					//�e�N�X�`���ւ̃|�C���^(����)
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffarufa = NULL;				//���_�o�b�t�@�̃|�C���^

PAUSE_MENU g_pauseMenu;		//�|�[�Y���j���[
int g_nSelect;				//�I��p�̕ϐ�

//=========================
//�|�[�Y�̏�����
//=========================
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���(����)
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\arufa.png",
		&g_apTexturearufa);

	//�e�N�X�`��1�̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\pause000.png",
		&g_apTexturePause[0]);

	//�e�N�X�`��2�̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\pause001.png",
		&g_apTexturePause[1]);

	//�e�N�X�`��3�̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\pause002.png",
		&g_apTexturePause[2]);

	//�e�N�X�`����4�ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\rankingrogo.png",
		&g_apTexturePause[3]);

	g_nSelect = PAUSE_MENU_CONTINUE;  //�����̑I�����[�h
	VERTEX_2D* pVtx;		//���_���̃|�C���^


	//=====================
	//�����|���S���̐ݒ�
	//=====================

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffarufa,
		NULL);

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffarufa->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W1�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//1�ڂ̒��_���
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);		//2�ڂ̒��_���
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);		//3�ڂ̒��_���
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);	//4�ڂ̒��_���

	//rhw�̐ݒ�(1.0f�ŌŒ�)
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//�A�����b�N
	g_pVtxBuffarufa->Unlock();

	//=========================
	//3�̃|���S���ݒ�
	//=========================

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_PAUSE_TEX,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL);


	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_PAUSE_TEX; nCnt++)
	{
		//���_���W1�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(470.0f,100.0f + (nCnt * 120.0f),0.0f);	//1�ڂ̒��_���
		pVtx[1].pos = D3DXVECTOR3(870.0f,100.0f + (nCnt * 120.0f),0.0f);	//2�ڂ̒��_���
		pVtx[2].pos = D3DXVECTOR3(470.0f,200.0f +(nCnt * 120.0f),0.0f);		//3�ڂ̒��_���
		pVtx[3].pos = D3DXVECTOR3(870.0f,200.0f +(nCnt * 120.0f),0.0f);		//4�ڂ̒��_���
		 
		//rhw�̐ݒ�(1.0f�ŌŒ�)
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
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//�A�����b�N
	g_pVtxBuffPause->Unlock();

}
//=========================
//�|�[�Y�̏I��
//=========================
void UninitPause(void)
{
	StopSound();

	//=========================
	//�����̏I��
	//=========================
	//�e�N�X�`���̏I��
	if (g_apTexturearufa != NULL)
	{			   
		g_apTexturearufa->Release();
		g_apTexturearufa = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffarufa != NULL)
	{
		g_pVtxBuffarufa->Release();
		g_pVtxBuffarufa = NULL;
	}

	//=========================
	//4�̃|���S���̏I��
	//=========================
	//�e�N�X�`���̏I��
	for (int nCnt = 0; nCnt < MAX_PAUSE_TEX; nCnt++)
	{
		if (g_apTexturePause[nCnt] != NULL)
		{
			g_apTexturePause[nCnt]->Release();
			g_apTexturePause[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
}
//=========================
//�|�[�Y�̍X�V
//=========================
void UpdatePause(void)
{
	VERTEX_2D* pVtx;		//���_���̃|�C���^

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < MAX_PAUSE_TEX; nCount++)
	{
		//���_�J���[��ݒ�(��)
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx += 4;
	}

	pVtx -= 4 * MAX_PAUSE_TEX;		//pVtx��߂�
	
	//���j���[�̑I��
	if (KeyboardTrigger(DIK_UP) == true || JoypadTrigger(JOYKEY_UP) == true)
	{
		//�㉟����
		g_nSelect--;//�f�N�������g
	
		if (g_nSelect < PAUSE_MENU_CONTINUE)
		{
			//��ԉ�
			g_nSelect = PAUSE_MENU_RANKING;
		}


	}

	else if (KeyboardTrigger(DIK_DOWN) == true || JoypadTrigger(JOYKEY_DOWN) == true)
	{
		//���������Ƃ�
		g_nSelect++;//�C���N�������g
		
		if (g_nSelect >= PAUSE_MENU_MAX)
		{
			//��ԏ�
			g_nSelect = PAUSE_MENU_CONTINUE;
		}

	}

	pVtx += 4 * g_nSelect;		//�I����


	pVtx[0].col = D3DXCOLOR(0.0f,0.0f,1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.0f,0.0f,1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.0f,0.0f,1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.0f,0.0f,1.0f, 1.0f);

	//�A�����b�N
	g_pVtxBuffPause->Unlock();

	if (KeyboardTrigger(DIK_RETURN) == true || JoypadTrigger(JOYKEY_A) == true)
	{
		//�G���^�[�L�[�������ꂽ
		//�e��ʂɈړ�
		switch (g_nSelect)
		{
		case PAUSE_MENU_CONTINUE:
			SetEnablePause(false);
			break;

		case PAUSE_MENU_RETRY:
			SetFade(MODE_GAME);
			break;

		case PAUSE_MENU_QUIT:
			SetFade(MODE_TITLE);
			break;

		case PAUSE_MENU_RANKING:
			SetFade(MODE_RANKING);
			break;

		}
		PlaySound(SOUND_LABEL_PAUSE);
	}
}
//=========================
//�|�[�Y�̕`��
//=========================
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//=========================
	//�����|���S���̏I��
	//=========================
	
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffarufa, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_apTexturearufa);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);		//�n�_

	//=========================
	//4�̃|���S���̕`��
	//=========================

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	VERTEX_2D* pVtx = 0;//���_���̃|�C���^


	for (int nCnt = 0; nCnt < MAX_PAUSE_TEX; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTexturePause[nCnt]);

		//�`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);//�|���S��

	}
}
