#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Float2.h"
#include "Hit.h"

// 画像を描画するよう変数
int bg_image;							// 背景用イメージ変数
int bullet_image[BULLET_COLOR];						// 弾用イメージ変数
int stand_image;						// 待機用イメージ変数
int firing_image;						// 発射用イメージ変数

// 弾をON：OFFで移動の切り替えをする
int bullet_mode;

// 弾の変数
Float2 bullet_pos[BULLET_NUM];			// 発射する弾の座標
float bullet_r[BULLET_NUM];				// 弾の半径
Float2 bullet_mov[BULLET_NUM];			// 弾の移動量
float bullet_roll;						// 弾の左右用変数
int bullet_num;							// 弾のカウント
int bullet_color_type;					// 弾のカラーを数える

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
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	for (int i = 0; i < BULLET_NUM; i++)
	{
		// 弾を飛ばす角度
		if (CheckHitKey(KEY_INPUT_RIGHT))
		{
			bullet_roll += 0.05f;
		}
		if (CheckHitKey(KEY_INPUT_LEFT))
		{
			bullet_roll -= 0.05f;
		}
		// 弾を発射
		if (PushHitKey(KEY_INPUT_SPACE))
		{
			// 弾を飛ばすかどうかのオンオフ
			bullet_mode = ON;
		}


		// 上に到着で止まる
		if (bullet_pos[bullet_num].y < 55.0f)
		{
			// 上で止まったらモードをオフ
			bullet_mode = OFF;
			
			bullet_pos[bullet_num].y = 55.0f;
			bullet_num++;
		}
		// 横に到着で止まる
		if (bullet_pos[bullet_num].x < 150.0f )
		{
			// 左で止まったらモードをオフ
			bullet_mode = OFF;

			bullet_pos[bullet_num].x = 150.0f;
			bullet_num++;
		}
		if (bullet_pos[bullet_num].x > SCREEN_W - 150.0f)
		{
			// 右で止まったらモードをオフ
			bullet_mode = OFF;

			bullet_pos[bullet_num].x = SCREEN_W - 150.0f;
			bullet_num++;
		}
		// 90度で止まる
		if (bullet_roll > 50.0f)
		{
			bullet_roll = 50.0f;
		}
		if (bullet_roll < -50.0f)
		{
			bullet_roll = -50.0f;
		}

		// モードがオンの時に弾を飛ばす
		if (bullet_mode == ON)
		{
			// 上に飛んでいく
			bullet_pos[bullet_num].y -= BULLET_SPEED;

			//// 弾のカラーをランダムで変える
			//for(int i = 0; i < BULLET_COLOR; i++)
			//{
			//	bullet_image[i] = GetRandomI(0, 2);
			//}
		}
	}

	// 弾がなくなったら戻る
	if (bullet_num > BULLET_NUM)
	{
		bullet_num = 0;
	}
	
}

//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	// ステージの描画
	DrawRotaGraph(SCREEN_W / 2.0f, SCREEN_H / 2.0f, 0.7f, 0.0f, bg_image, TRUE);
	if(bullet_mode == OFF)
	{
		DrawRotaGraph(SCREEN_W / 2.0f - 50.0f, SCREEN_H - 50.0f, 1.5f, 0.0f, stand_image, TRUE);
	}
	if (bullet_mode == ON)
	{
		DrawRotaGraph(SCREEN_W / 2.0f - 50.0f, SCREEN_H - 50.0f, 1.5f, 0.0f, firing_image, TRUE);
	}

	// ゲームオーバーライン
	DrawLine( 0, SCREEN_H - 100, SCREEN_W, SCREEN_H - 100, GetColor( 255, 255, 255), TRUE);

	// 弾が飛んでいく方向の描画
	DrawLine(SCREEN_W / 2, SCREEN_H - 63.0f, SCREEN_W / 2, SCREEN_H - 63.0f - 100.0f, GetColor(0, 255, 255), TRUE);

	// 弾の描画
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
//	終了処理
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
