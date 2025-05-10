#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Float2.h"
#include "Hit.h"

// �摜��`�悷��悤�ϐ�
int bg_image;							// �w�i�p�C���[�W�ϐ�
int bullet_image[BULLET_COLOR];						// �e�p�C���[�W�ϐ�
int stand_image;						// �ҋ@�p�C���[�W�ϐ�
int firing_image;						// ���˗p�C���[�W�ϐ�

// �e��ON�FOFF�ňړ��̐؂�ւ�������
int bullet_mode;

// �e�̕ϐ�
Float2 bullet_pos[BULLET_NUM];			// ���˂���e�̍��W
float bullet_r[BULLET_NUM];				// �e�̔��a
Float2 bullet_mov[BULLET_NUM];			// �e�̈ړ���
float bullet_roll;						// �e�̍��E�p�ϐ�
int bullet_num;							// �e�̃J�E���g
int bullet_color_type;					// �e�̃J���[�𐔂���

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
	bg_image = LoadGraph("data/stage_0.png");
	for(int i = 0; i < BULLET_COLOR; i++)
	{
		
		char fname[64];
		sprintf(fname, "data/bullet_%d.png", i);
		bullet_image[i] = LoadGraph(fname);

	}
	stand_image = LoadGraph("data/stand.png");
	firing_image = LoadGraph("data/firing.png");


	bullet_mode = OFF;

	for(int i = 0; i < BULLET_NUM; i++)
	{
		bullet_pos[i].x = SCREEN_W / 2.0f;
		bullet_pos[i].y = SCREEN_H - 63.0f;
		bullet_r[i] = 10.0f;
	}
	bullet_roll = 0.0f;
	bullet_num = 0;
	bullet_color_type = GetRandomI(0, 2);
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
			bullet_roll += 0.05f;
		}
		if (CheckHitKey(KEY_INPUT_LEFT))
		{
			bullet_roll -= 0.05f;
		}
		// �e�𔭎�
		if (PushHitKey(KEY_INPUT_SPACE))
		{
			// �e���΂����ǂ����̃I���I�t
			bullet_mode = ON;
		}


		// ��ɓ����Ŏ~�܂�
		if (bullet_pos[bullet_num].y < 55.0f)
		{
			// ��Ŏ~�܂����烂�[�h���I�t
			bullet_mode = OFF;
			
			bullet_pos[bullet_num].y = 55.0f;
			bullet_num++;
		}
		// ���ɓ����Ŏ~�܂�
		if (bullet_pos[bullet_num].x < 150.0f )
		{
			// ���Ŏ~�܂����烂�[�h���I�t
			bullet_mode = OFF;

			bullet_pos[bullet_num].x = 150.0f;
			bullet_num++;
		}
		if (bullet_pos[bullet_num].x > SCREEN_W - 150.0f)
		{
			// �E�Ŏ~�܂����烂�[�h���I�t
			bullet_mode = OFF;

			bullet_pos[bullet_num].x = SCREEN_W - 150.0f;
			bullet_num++;
		}
		// 90�x�Ŏ~�܂�
		if (bullet_roll > 50.0f)
		{
			bullet_roll = 50.0f;
		}
		if (bullet_roll < -50.0f)
		{
			bullet_roll = -50.0f;
		}

		// ���[�h���I���̎��ɒe���΂�
		if (bullet_mode == ON)
		{
			// ��ɔ��ł���
			bullet_pos[bullet_num].y -= BULLET_SPEED;

			//// �e�̃J���[�������_���ŕς���
			//for(int i = 0; i < BULLET_COLOR; i++)
			//{
			//	bullet_image[i] = GetRandomI(0, 2);
			//}
		}
	}

	// �e���Ȃ��Ȃ�����߂�
	if (bullet_num > BULLET_NUM)
	{
		bullet_num = 0;
	}
	
}

//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	// �X�e�[�W�̕`��
	DrawRotaGraph(SCREEN_W / 2.0f, SCREEN_H / 2.0f, 0.7f, 0.0f, bg_image, TRUE);
	if(bullet_mode == OFF)
	{
		DrawRotaGraph(SCREEN_W / 2.0f - 50.0f, SCREEN_H - 50.0f, 1.5f, 0.0f, stand_image, TRUE);
	}
	if (bullet_mode == ON)
	{
		DrawRotaGraph(SCREEN_W / 2.0f - 50.0f, SCREEN_H - 50.0f, 1.5f, 0.0f, firing_image, TRUE);
	}

	// �Q�[���I�[�o�[���C��
	DrawLine( 0, SCREEN_H - 100, SCREEN_W, SCREEN_H - 100, GetColor( 255, 255, 255), TRUE);

	// �e�����ł��������̕`��
	DrawLine(SCREEN_W / 2, SCREEN_H - 63.0f, SCREEN_W / 2, SCREEN_H - 63.0f - 100.0f, GetColor(0, 255, 255), TRUE);

	// �e�̕`��
	for (int i = 0; i < BULLET_NUM; i++)
	{
		DrawCircle(bullet_pos[i].x, bullet_pos[i].y, bullet_r[i], GetColor(0, 255, 255), FALSE);

		//for(int j = 0; j < BULLET_COLOR; j++)
		//{
		//	DrawRotaGraph(bullet_pos[i].x, bullet_pos[i].y, 1.5f, TO_RADIAN(bullet_roll), bullet_image[j], TRUE);
		//}
		DrawRotaGraph(bullet_pos[i].x, bullet_pos[i].y, 1.5f, TO_RADIAN(bullet_roll), bullet_image[bullet_color_type], TRUE);
	}
	

}

//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph(bg_image);
	for (int i = 0; i < BULLET_COLOR; i++)
	{
		DeleteGraph(bullet_image[i]);
	}
	DeleteGraph(bg_image);
}
