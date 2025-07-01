//---------------------------
//
//wave����(�ǂݍ���)
//Author:NISHIO ASUMA
//
//---------------------------

#ifndef _WAVE_H_
#define _WAVE_H_

#include "main.h"
#include "enemy.h"

//�}�N����`
#define WAVEPATH_BIN    ("WAVE\\wave000.bin")	//�E�F�[�u1�̃p�X
#define WAVEPATH_BIN_1  ("WAVE\\wave001.bin")	//�E�F�[�u2�̃p�X
#define WAVEPATH_BIN_2  ("WAVE\\wave002.bin")	//�E�F�[�u3�̃p�X
#define WAVEPATH_BIN_3  ("WAVE\\wave003.bin")	//�E�F�[�u4�̃p�X
#define WAVEPATH_BIN_4  ("WAVE\\wave004.bin")	//�E�F�[�u5�̃p�X
#define WAVEPATH_BIN_5  ("WAVE\\wave005.bin")	//�E�F�[�u6�̃p�X
#define WAVEPATH_BIN_6  ("WAVE\\wave006.bin")	//�E�F�[�u7�̃p�X
#define WAVEPATH_BIN_7  ("WAVE\\wave007.bin")	//�E�F�[�u8�̃p�X
#define WAVEPATH_BIN_8  ("WAVE\\wave008.bin")	//�E�F�[�u9�̃p�X
#define WAVEPATH_BIN_9  ("WAVE\\wave009.bin")	//�E�F�[�u10�̃p�X
#define WAVEPATH_BIN_10 ("WAVE\\wave010.bin")	//�E�F�[�u11�̃p�X


//�v���g�^�C�v�錾
void InitWave(void);			//�t�@�C���̏�����
void LoadWave(void);			//�t�@�C����ǂݍ���
int GetWave(void);				//�E�F�[�u���̎擾
bool GetFinish(void);			//�I������̎擾

#endif

//#define WAVEPATH ("WAVE\\wave.txt")	//�E�F�[�u�̃p�X
