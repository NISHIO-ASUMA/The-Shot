//---------------------------
//
//wave����(�ǂݍ���)
//Author:NISHIO ASUMA
//
//---------------------------

#include "wave.h"
#include "input.h"
#include <stdio.h>
#include <string.h>
#include "enemy.h"

//�}�N��
#define MAX_WORD (4096)		//�ő啶����

//�\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	int nType;			//���
	bool bUse;			//�g�p���
}LoadInfo;

//�O���[�o��
LoadInfo g_aInfo[MAX_ENEMY];		//�\���̏��
int g_nCntEnemy;					//�G���J�E���g
int g_nWave;						//�E�F�[�u���Ǘ�
bool g_bFinish;						//�E�F�[�u���I�������

//==============================
// ������
//==============================
void InitWave(void)
{
	//�\���̂̏�����
	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		g_aInfo[nCnt].bUse = false;
		g_aInfo[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aInfo[nCnt].nType = 0;
	}

	 g_nCntEnemy = 0;		//�G���J�E���g
	 g_nWave = 0;			//�E�F�[�u���Ǘ�
	 g_bFinish = false;		//�E�F�[�u�̏I������

}
//==============================
//�E�F�[�u����(�ǂݍ���)
//==============================
void LoadWave(void)
{
	FILE* pFile = NULL;		//�t�@�C���|�C���^
	int nType;				//�^�C�v
	D3DXVECTOR3 pos;		//���W

	//�G�̎擾
	g_nCntEnemy = GetNumEnemy();

	//�E�F�[�u�֌W
	switch (g_nWave)
	{

	case 0:
		//�����E�F�u
		//�t�@�C���J��
		pFile = fopen(WAVEPATH_BIN, "rb");
		break;

	case 1:

		//�t�@�C���J��
		pFile = fopen(WAVEPATH_BIN_1, "rb");

		break;

	case 2:
		//�t�@�C�����J��
		pFile = fopen(WAVEPATH_BIN_2, "rb");

		break;

	case 3:
		//�t�@�C�����J��
		pFile = fopen(WAVEPATH_BIN_3, "rb");

		break;

	case 4:
		//�t�@�C�����J��
		pFile = fopen(WAVEPATH_BIN_4, "rb");

		break;

	case 5:
		//�t�@�C�����J��
		pFile = fopen(WAVEPATH_BIN_5, "rb");

		break;

	case 6:
		//�t�@�C�����J��
		pFile = fopen(WAVEPATH_BIN_6, "rb");

		break;

	case 7:
		//�t�@�C�����J��
		pFile = fopen(WAVEPATH_BIN_7, "rb");

		break;

	case 8:
		//�t�@�C�����J��
		pFile = fopen(WAVEPATH_BIN_8, "rb");

		break;

	case 9:
		//�t�@�C�����J��
		pFile = fopen(WAVEPATH_BIN_9, "rb");

		break;

	default:
		pFile = NULL;
		g_bFinish = true;	//�E�F�[�u�̏I��
		break;
	}

	//�J������
	if (pFile != NULL)
	{
		fread(&g_nCntEnemy, sizeof(int), 1, pFile);					//�G�̐�
		fread(&g_aInfo[0], sizeof(LoadInfo), g_nCntEnemy, pFile);	//�G�̓ǂݍ���

		for (int nCnt = 0; nCnt < g_nCntEnemy; nCnt++)
		{
			SetEnemy(g_aInfo[nCnt].pos, g_aInfo[nCnt].nType);		//�G�̐ݒ�
		}

		//�t�@�C�������
		fclose(pFile);

		//�E�F�[�u�̃J�E���g�A�b�v
		g_nWave++;

	}
	else
	{
		//�J���Ȃ�������
		return;
	}

}
//====================
//�E�F�[�u�̒l��Ԃ�
//====================
int GetWave(void)
{
	return g_nWave;
}
//====================
//�E�F�[�u�̏I�������Ԃ�
//====================
bool GetFinish(void)
{
	return g_bFinish;
}

//while (1)
//{
//	char aString[MAX_WORD];//�ǂݍ��ޕ�����

//	//�t�@�C������ǂݍ���
//	fscanf(pFile, "%s", &aString[0]);

//	//SETENEMY��ǂݎ������
//	if (strcmp(aString, "SETENEMY") == 0)
//	{
//		while (1)
//		{
//			//�t�@�C������ǂݍ���
//			fscanf(pFile, "%s", &aString[0]);

//			if (strcmp(aString, "ENEMYTYPE") == 0)
//			{
//				//�G�̎��
//				fscanf(pFile, "%d", &nType);

//			}
//			else if (strcmp(aString, "POS") == 0)
//			{
//				//�G�̍��W
//				fscanf(pFile, "%f", &pos.x);
//				fscanf(pFile, "%f", &pos.y);
//				fscanf(pFile, "%f", &pos.z);

//			}
//			else if (strcmp(aString, "END_SETENEMY") == 0)
//			{
//				//END_SETENEMY��ǂݎ������
//				SetEnemy(pos, nType);
//				break;
//			}
//		}
//	}
//	//�f�[�^����
//	if (strcmp(aString, "END_SCRIPT") == 0)
//	{
//		
//	}

//}

