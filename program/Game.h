#pragma once

#define SCREEN_W	800
#define SCREEN_H	450


enum
{
	ON,
	OFF,
};


//---------------------------------------------------------------------------------
//	定数
//---------------------------------------------------------------------------------
#define BULLET_NUM		100
#define BULLET_COLOR	3
#define BULLET_SPEED	0.2f;

void GameInit();	//	初期化処理
void GameUpdate();	//	更新処理
void GameRender();	//	描画処理
void GameExit();	//	終了処理
