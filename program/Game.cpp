#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Float2.h"
#include "Hit.h"

// 画像を描画するよう変数
int bg_image;							// 背景用イメージ変数
int bullet_image;						// 弾用イメージ変数
int player_image;						// プレイヤー用イメージ変数

// 弾をON：OFFで移動の切り替えをする
int bullet_mode;

// 弾の変数
Float2 bullet_pos[BULLET_NUM];			// 発射する弾の座標
float bullet_r[BULLET_NUM];				// 弾の半径
Float2 bullet_mov[BULLET_NUM];			// 弾の移動量
float bullet_roll;						// 弾の左右用変数
int bullet_num;

bool mouse_drag;						// マウスがドラッグ中かどうか
Float2 mouse;							// マウス座標を入れる用変数

Float2 click_pos;						// クリックした瞬間の変数(始点)
Float2 click_pos_2;						// 引っ張った時の終点

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	// 描画だけ
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
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	for (int i = 0; i < BULLET_NUM; i++)
	{
		// 弾を飛ばす角度
		if (CheckHitKey(KEY_INPUT_RIGHT))
		{
			bullet_roll += 3.0f;
		}
		if (CheckHitKey(KEY_INPUT_LEFT))
		{
			bullet_roll -= 3.0f;
		}
		// 弾を発射
		if (PushHitKey(KEY_INPUT_SPACE))
		{
			// 弾を飛ばすかどうかのオンオフ
			bullet_mode = ON;
		}
		// 上に到着で止まる
		if (bullet_pos[bullet_num].y < 65.0f)
		{
			bullet_mode = OFF;
			
			bullet_pos[bullet_num].y = 65.0f;
		}
		// 横に到着で止まる
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
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	// ステージの描画
	DrawRotaGraph(SCREEN_W / 2.0f, SCREEN_H / 2.0f, 0.38f, 0.0f, bg_image, TRUE);

	// ゲームオーバーライン
	DrawLine( 0, SCREEN_H - 100, SCREEN_W, SCREEN_H - 100, GetColor( 255, 255, 255), TRUE);

	// 弾が飛んでいく方向の描画
	DrawLine(SCREEN_W / 2, SCREEN_H - 63.0f, SCREEN_W / 2, SCREEN_H - 63.0f - 100.0f, GetColor(0, 255, 255), TRUE);

	// 弾の描画
	for (int i = 0; i < BULLET_NUM; i++)
	{
		DrawCircle(bullet_pos[i].x, bullet_pos[i].y, bullet_r[i], GetColor(0, 255, 255), FALSE);
		DrawRotaGraph(bullet_pos[i].x, bullet_pos[i].y, 1.0f, 0.0f,  bullet_image, TRUE);
	}
	

}

//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	
}
