//---------------------------
//
//�|�[�Y����
//Author:NISHIO ASUMA
//
//---------------------------

#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"

#define MAX_PAUSE_TEX (4)  //�|�[�Y��ʂ̃e�N�X�`��

//�|�[�Y���j���[
typedef enum
{
	PAUSE_MENU_CONTINUE = 0,//�Q�[���ɖ߂�
	PAUSE_MENU_RETRY,       //�Q�[������蒼��
	PAUSE_MENU_QUIT,        //�^�C�g���ɖ߂�
	PAUSE_MENU_RANKING,     //�����L���O�ɍs��
	PAUSE_MENU_MAX
}PAUSE_MENU;


//�v���g�^�C�v�錾
void InitPause(void);		//�|�[�Y��ʂ̏�����
void UninitPause(void);		//�|�[�Y��ʂ̏I��
void UpdatePause(void);		//�|�[�Y��ʂ̍X�V
void DrawPause(void);		//�|�[�Y��ʂ̕`��

#endif