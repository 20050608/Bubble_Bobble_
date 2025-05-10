#pragma once

#define SCREEN_W	800
#define SCREEN_H	450


enum
{
	ON,
	OFF,
};


//---------------------------------------------------------------------------------
//	’è”
//---------------------------------------------------------------------------------
#define BULLET_NUM		100
#define BULLET_COLOR	3
#define BULLET_SPEED	0.2f;

void GameInit();	//	‰Šú‰»ˆ—
void GameUpdate();	//	XVˆ—
void GameRender();	//	•`‰æˆ—
void GameExit();	//	I—¹ˆ—
