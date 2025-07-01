//---------------------------
//
//�Q�[������
//Author:NISHIO ASUMA
//
//---------------------------

#include "game.h"
#include "Player.h"
#include "background.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "fade.h"
#include "score.h"
#include "item.h"
#include "title.h"
#include "tutorial.h"
#include "effect.h"
#include "pause.h"
#include "wave.h"
#include "edit.h"
#include "ranking.h"
#include "rankscore.h"
#include "particle.h"
#include "Timer.h"
#include "sound.h"

//�O���[�o��
GAMESTATE g_gameState = GAMESTATE_NONE;		//�Q�[�����
int g_nCounterGameState = 0;				//��ԊǗ��J�E���^�[
bool g_bPause = false;						//�|�[�Y�����ǂ���

//===================
//�Q�[���̏�����
//===================
void InitGame(void)
{
	InitBackground();		//�w�i

	InitBullet();			//�e

	InitPlayer();			//�v���C���[

	InitWave();				//�E�F�[�u

	InitEnemy();			//�G

	InitExplosion();		//����

	InitScore();			//�X�R�A

	InitItem();				//�A�C�e��

	InitEffect();			//�G�t�F�N�g

	InitParticle();			//�p�[�e�B�N��

	InitPause();			//�|�[�Y

	InitTimer();			//�^�C�}�[

	InitPlayerLifeBar();	//���C�t�o�[

	g_gameState = GAMESTATE_NORMAL;	//�ʏ���
	g_nCounterGameState = 0;
	g_bPause = false;				//�|�[�Y��ʂ̏�����(�|�[�Y����)

	LoadWave();						//�E�F�[�u�ǂݍ���

	PlaySound(SOUND_LABEL_GAME);
}
//===================
//�Q�[���̏I��
//===================
void UninitGame(void)
{
	StopSound();

	SaveScore();			//�X�R�A��ۑ�

	UninitBackground();		//�w�i

	UninitBullet();			//�e

	UninitPlayer();			//�v���C���[

	UninitEnemy();			//�G�̏I��

	UninitExplosion();		//����

	UninitScore();			//�X�R�A�I��

	UninitItem();			//�A�C�e��

	UninitEffect();			//�G�t�F�N�g

	UninitParticle();		//�p�[�e�B�N��

	UninitPause();			//�|�[�Y

	UninitTimer();			//�^�C�}�[

	UninitPlayerLifeBar();	//���C�t�o�[

}
//===================
//�Q�[���̍X�V
//===================
void UpdateGame(void)
{
	int nNum;//���[�J���ϐ�

	//�v���C���[�̎擾
	Player* pPlayer = GetPlayer();

	//�G�̎擾
	nNum = GetNumEnemy();

	//�E�F�[�u���擾
	int nWave = GetWave();

	//�^�C�}�[���擾
	int nTime = GetTimer();

	if (nNum <= 0)
	{
		//�E�F�[�u��ǂݍ���
		LoadWave();
	}

	//�E�F�[�u�̏I��������擾
	bool bFinish = GetFinish();


	if ((pPlayer->bDisp == false || bFinish == true || nTime <= 0) && g_gameState != GAMESTATE_NONE)
	{
		g_gameState = GAMESTATE_END;  //�I�����
	}
	switch(g_gameState)
	{
	case GAMESTATE_NORMAL://�ʏ���
		break;

	case GAMESTATE_END:
  		g_nCounterGameState++;
		if (g_nCounterGameState >= 30)
		{
			//�J�E���^�[��������
			g_nCounterGameState = 0;

			//1�b�o��
			g_gameState = GAMESTATE_NONE;//�������Ă��Ȃ����
			//��ʐݒ�
			SetFade(MODE_RESULT);

			//�ǂݍ���
			ResetRanking();

			//�����L���O�̐ݒ�
			SetRanking(GetScore());
		}
		break;
	}

	//�|�[�Y���
	if (KeyboardTrigger(DIK_P) == true || JoypadTrigger(JOYKEY_START))
	{
		//p�������ꂽ or start�{�^��
		g_bPause = g_bPause ? false : true;
	}

#ifdef _DEBUG

	if (KeyboardTrigger(DIK_F1) == true)
	{

		SaveEdit();//�G�f�B�b�g���

	}

#endif // DEBUG

	if (g_bPause == true)
	{
		//�|�[�Y��
		//�|�[�Y�̍X�V����
		UpdatePause();
	}
	else 
	{
		//�|�[�Y���Ŗ������
		UpdateBackground();			//�w�i

		UpdatePlayer();				//�v���C���[

		UpdateBullet();				//�e

		UpdateEnemy();				//�G

		UpdateExplosion();			//����

		UpdateScore();				//�X�R�A�X�V

		UpdateItem();				//�A�C�e��

		UpdateEffect();				//�G�t�F�N�g

		UpdateParticle();			//�p�[�e�B�N��

		UpdateTimer();				//�^�C�}�[

		UpdatePlayerLifeBar();		//���C�t�o�[
	}
}
//===================
//�Q�[���̕`��
//===================
void DrawGame(void)
{
	//�w�i
	DrawBackground();

	//�A�C�e��
	DrawItem();

	//�e
	DrawBullet();

	//�v���C���[
	DrawPlayer();

	//�G
	DrawEnemy();

	//���j
	DrawExplosion();

	//�X�R�A
	DrawScore();

	//�G�t�F�N�g
	DrawEffect();

	//�p�[�e�B�N��
	DrawParticle();

	//�^�C�}�[
	DrawTimer();

	//���C�t�o�[
	DrawPlayerLifeBar();

	if (g_bPause == true)
	{
		//�|�[�Y��
		//�|�[�Y�̕`��
		DrawPause();
	}
}
//=====================
//�|�[�Y�̗L�������ݒ�
//=====================
void SetEnablePause(bool bPause)
{
	g_bPause = bPause;
}
//=====================
//���[�ޏ�Ԑݒ�
//=====================
void SetGamestate(GAMESTATE state)
{
	g_gameState = state;
	g_nCounterGameState = 0;
}
//=====================
//���[�ޏ�Ԏ擾
//=====================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}
