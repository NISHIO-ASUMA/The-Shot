//---------------------------
//
//�X�R�A����
//Author:NISHIO ASUMA
//
//---------------------------

#ifndef  _SCORE_H_
#define  _SCORE_H_

#include "main.h"

//�}�N����`
#define MAX_NUM_SCORE (8)			//���̍ő吔

//�v���g
void InitScore(void);				//�X�R�A�̏�����
void UninitScore(void);				//�X�R�A�̏I��
void UpdateScore(void);				//�X�R�A�̍X�V
void DrawScore(void);				//�X�R�A�̕`��
void SetScore(int nScore);			//�X�R�A�̐ݒ�
void AddScore(int nValue);			//�X�R�A�̉��Z
int ScoreCounter(int nScore);		//�X�R�A��0���J�E���g
int GetScore(void);					//�X�R�A���擾
void SaveScore(void);				//�X�R�A�̏����o��

#endif // ! _SCORE_H_
