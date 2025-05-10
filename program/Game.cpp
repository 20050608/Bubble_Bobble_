#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Float2.h"
#include "Hit.h"

// �摜��`�悷��悤�ϐ�
int bg_image;							// �w�i�p�C���[�W�ϐ�
int bullet_image;						// �e�p�C���[�W�ϐ�
int player_image;						// �v���C���[�p�C���[�W�ϐ�

// �e��ON�FOFF�ňړ��̐؂�ւ�������
int bullet_mode;

// �e�̕ϐ�
Float2 bullet_pos[BULLET_NUM];			// ���˂���e�̍��W
float bullet_r[BULLET_NUM];				// �e�̔��a
Float2 bullet_mov[BULLET_NUM];			// �e�̈ړ���
float bullet_roll;						// �e�̍��E�p�ϐ�
int bullet_num;

bool mouse_drag;						// �}�E�X���h���b�O�����ǂ���
Float2 mouse;							// �}�E�X���W������p�ϐ�

Float2 click_pos;						// �N���b�N�����u�Ԃ̕ϐ�(�n�_)
Float2 click_pos_2;						// �������������̏I�_

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	// �`�悾��
	bg_image = LoadGraph("data/stage_.png");
	bullet_image = LoadGraph("data/bullet_g.png");
	player_image = LoadGraph(" ");


	bullet_mode = OFF;

	for(int i = 0; i < BULLET_NUM; i++)
	{
		bullet_pos[i].x = SCREEN_W / 2.0f;
		bullet_pos[i].y = SCREEN_H - 63.0f;
		bullet_r[i] = 10.0f;
	}
	bullet_roll = 0.0f;
	bullet_num = 0;
}

//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	for (int i = 0; i < BULLET_NUM; i++)
	{
		// �e���΂��p�x
		if (CheckHitKey(KEY_INPUT_RIGHT))
		{
			bullet_roll += 3.0f;
		}
		if (CheckHitKey(KEY_INPUT_LEFT))
		{
			bullet_roll -= 3.0f;
		}
		// �e�𔭎�
		if (PushHitKey(KEY_INPUT_SPACE))
		{
			// �e���΂����ǂ����̃I���I�t
			bullet_mode = ON;
		}
		// ��ɓ����Ŏ~�܂�
		if (bullet_pos[bullet_num].y < 65.0f)
		{
			bullet_mode = OFF;
			
			bullet_pos[bullet_num].y = 65.0f;
		}
		// ���ɓ����Ŏ~�܂�
		if (bullet_pos[bullet_num].x < 150.0f )
		{
			bullet_pos[bullet_num].x = 150.0f;
		}
		if (bullet_pos[bullet_num].x > SCREEN_W - 150.0f)
		{
			bullet_pos[bullet_num].x = SCREEN_W - 150.0f;
		}

		if (bullet_mode == ON)
		{
			bullet_pos[bullet_num].y -= BULLET_SPEED;
		}
	}
	
}

//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	// �X�e�[�W�̕`��
	DrawRotaGraph(SCREEN_W / 2.0f, SCREEN_H / 2.0f, 0.38f, 0.0f, bg_image, TRUE);

	// �Q�[���I�[�o�[���C��
	DrawLine( 0, SCREEN_H - 100, SCREEN_W, SCREEN_H - 100, GetColor( 255, 255, 255), TRUE);

	// �e�����ł��������̕`��
	DrawLine(SCREEN_W / 2, SCREEN_H - 63.0f, SCREEN_W / 2, SCREEN_H - 63.0f - 100.0f, GetColor(0, 255, 255), TRUE);

	// �e�̕`��
	for (int i = 0; i < BULLET_NUM; i++)
	{
		DrawCircle(bullet_pos[i].x, bullet_pos[i].y, bullet_r[i], GetColor(0, 255, 255), FALSE);
		DrawRotaGraph(bullet_pos[i].x, bullet_pos[i].y, 1.0f, 0.0f,  bullet_image, TRUE);
	}
	

}

//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	
}
