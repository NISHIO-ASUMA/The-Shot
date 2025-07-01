//---------------------------
//
//wave����(�����o��)
//Author:NISHIO ASUMA
//
//---------------------------

#include "edit.h"
#include "input.h"
#include "wave.h"
#include <stdio.h>

#define EDIT_MOVE (20.0f)		//�G�̈ړ���(�z�u��)

//�G�f�B�b�g���̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	int nType;			//���
	bool bUse;			//�g�p���
}EditInfo;

//�O���[�o���ϐ�
int g_nCntEdit;//�G��z�u���������J�E���g
EditInfo g_aEditInfo[MAX_ENEMY];	//���
LPDIRECT3DTEXTURE9 g_apTextureEdit[ENEMYTYPE_MAX] = {};//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEdit = NULL;//���_�o�b�t�@�̃|�C���^

//========================
//������
//========================
void InitEdit(void)
{
	int nCntEdit;	//���[�J���ϐ�

	//�\���̕ϐ��̏�����
	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		g_aEditInfo[nCnt].nType = 0;							//���
		g_aEditInfo[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu
		g_aEditInfo[nCnt].bUse = false;							//�g�p����
	}

	//�ŏ��̔ԍ������g�p����
	g_aEditInfo[0].bUse = true;	//�g�p����

	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	VERTEX_2D* pVtx;			//���_���̃|�C���^

	for (int nCnt = 0; nCnt < ENEMYTYPE_MAX; nCnt++)
	{
		//�G�̃e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			ENEMY_TEXTURE[nCnt],
			&g_apTextureEdit[nCnt]);
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEdit,
		NULL);

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffEdit->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEdit = 0; nCntEdit < MAX_ENEMY; nCntEdit++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhw�̐ݒ�(1.0f�ŌŒ�)
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
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//�A�����b�N
	g_pVtxBuffEdit->Unlock();
}
//========================
//�I��
//========================
void UninitEdit(void)
{
	int nCntEdit;//�G�̐�
	//�e�N�X�`���̔j��
	for (nCntEdit = 0; nCntEdit < ENEMYTYPE_MAX; nCntEdit++)
	{

		if (g_apTextureEdit[nCntEdit] != NULL)
		{
			g_apTextureEdit[nCntEdit]->Release();
			g_apTextureEdit[nCntEdit] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEdit != NULL)
	{
		g_pVtxBuffEdit->Release();
		g_pVtxBuffEdit = NULL;
	}
}
//========================
//�X�V
//========================
void UpdateEdit(void)
{
	//�ړ�����
	if (KeyboardTrigger(DIK_A) == true)
	{
		//A�P�̂̏���
		g_aEditInfo[g_nCntEdit].pos.x -= EDIT_MOVE;
	}
	else if (KeyboardTrigger(DIK_D) == true)
	{
		//D�P�̂̏���
		g_aEditInfo[g_nCntEdit].pos.x += EDIT_MOVE;
	}
	else if (KeyboardTrigger(DIK_W) == true)
	{
		//W�P�̂̏���
		g_aEditInfo[g_nCntEdit].pos.y -= EDIT_MOVE;
	}
	else if (KeyboardTrigger(DIK_S) == true)
	{
		//S�P�̂̏���
		g_aEditInfo[g_nCntEdit].pos.y += EDIT_MOVE;
	}

	if (KeyboardTrigger(DIK_UP) == true)
	{
		if (g_aEditInfo[g_nCntEdit].nType < ENEMYTYPE_MAX-1)
		{
			//�ő吔��菬�����Ƃ�
			g_aEditInfo[g_nCntEdit].nType++;
		}

	}
	else if (KeyboardTrigger(DIK_DOWN) == true)
	{
		if (g_aEditInfo[g_nCntEdit].nType > ENEMYTYPE_OWN)
		{
			//1���傫���Ƃ�
			g_aEditInfo[g_nCntEdit].nType--;
		}
	}

	//�G�̔z�u
	if (KeyboardTrigger(DIK_RETURN) == true)
	{
		//���̓G�̈ʒu��z�u�����G�Ɠ����ɂ���
		g_aEditInfo[g_nCntEdit + 1].pos = g_aEditInfo[g_nCntEdit].pos;

		//�g�p����ɂ���
		g_aEditInfo[g_nCntEdit + 1].bUse = true;	

		//�G�̐����C���N�������g
		g_nCntEdit++;
	}

	//�����o������
	if (KeyboardTrigger(DIK_F7) == true)
	{
		//�ۑ�����
		SaveEdit();
	}

	VERTEX_2D* pVtx;	//���_���̃|�C���^

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffEdit->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEdit = 0; nCntEdit < MAX_ENEMY; nCntEdit++)
	{
		if (g_aEditInfo[nCntEdit].bUse == true)
		{
			//���_���̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aEditInfo[nCntEdit].pos.x - MAX_ENEMY_SIZE, g_aEditInfo[nCntEdit].pos.y - MAX_ENEMY_SIZE, 0.0f);//1�ڂ̒��_���
			pVtx[1].pos = D3DXVECTOR3(g_aEditInfo[nCntEdit].pos.x + MAX_ENEMY_SIZE, g_aEditInfo[nCntEdit].pos.y - MAX_ENEMY_SIZE, 0.0f);//2�ڂ̒��_���
			pVtx[2].pos = D3DXVECTOR3(g_aEditInfo[nCntEdit].pos.x - MAX_ENEMY_SIZE, g_aEditInfo[nCntEdit].pos.y + MAX_ENEMY_SIZE, 0.0f);//3�ڂ̒��_���
			pVtx[3].pos = D3DXVECTOR3(g_aEditInfo[nCntEdit].pos.x + MAX_ENEMY_SIZE, g_aEditInfo[nCntEdit].pos.y + MAX_ENEMY_SIZE, 0.0f);//4�ڂ̒��_���
		}

		pVtx += 4;
	}
	//�A�����b�N
	g_pVtxBuffEdit->Unlock();

}
//========================
//�`��
//========================
void DrawEdit(void)
{
	int nCntEdit;//���[�J���ϐ�

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEdit, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntEdit = 0; nCntEdit < MAX_ENEMY; nCntEdit++)
	{
		if (g_aEditInfo[nCntEdit].bUse == true)
		{
			//�g�p����Ă�
			int nType = g_aEditInfo[nCntEdit].nType;
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureEdit[nType]);

			//�G�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEdit * 4, 2);//�n�_(0�Ԗځ`3�Ԗ�)

		}
	}
}
//========================
//�E�F�[�u����(��������)
//========================
void SaveEdit(void)
{

	FILE* pFile;	//�t�@�C���|�C���^��錾

	int nType;			//���
	D3DXVECTOR3 pos;	//���W

	//�t�@�C�����J��
	pFile = fopen(WAVEPATH_BIN_7,"wb");

	if (pFile != NULL)
	{

		fwrite(&g_nCntEdit, sizeof(int), 1, pFile);

		//�z�u�����G�̐���������
		for (int nCnt = 0; nCnt < g_nCntEdit; nCnt++)
		{
			if (g_aEditInfo[nCnt].bUse == true)
			{
				fwrite(&g_aEditInfo[nCnt], sizeof(EditInfo), 1, pFile);
			}

			//fprintf(pFile, "SETENEMY\n");

			//fprintf(pFile, "ENEMYTYPE %d\n", g_aEditInfo[nCnt].nType);
			//
			//fprintf(pFile, "POS %f %f %f\n", g_aEditInfo[nCnt].pos.x, g_aEditInfo[nCnt].pos.y, g_aEditInfo[nCnt].pos.z);
			//
			//fprintf(pFile, "END_SETENEMY\n");
		}

		//fprintf(pFile, "END_SCRIPT\n");

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{
		//�t�@�C�����J���Ȃ�������
		//���b�Z�[�WBOX�̕\��
		MessageBox(NULL, "�J���܂���", "�G���[", MB_OK);

		return;

	}
}
