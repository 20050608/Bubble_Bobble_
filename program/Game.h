#pragma once

#define SCREEN_W	800
#define SCREEN_H	450

enum
{
	ON,
	OFF,
};

//---------------------------------------------------------------------------------
//	�萔
//---------------------------------------------------------------------------------
#define BULLET_NUM		3
#define BULLET_SPEED	5.0f;

void GameInit();	//	����������
void GameUpdate();	//	�X�V����
void GameRender();	//	�`�揈��
void GameExit();	//	�I������
