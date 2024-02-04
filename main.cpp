#include <Novice.h>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include <corecrt_math.h>

bool isBulletColliding(Bullet& bullet, Enemy& enemy) {
	int dx = bullet.bulletGetX() - enemy.enemyGetPosX();
	int dy = bullet.bulletGetY() - enemy.enemyGetPosY();
	int distance = (int)sqrt(dx * dx + dy * dy);

	return distance < 50;
}

bool isPlayerColliding(Player& player, Enemy& enemy) {
	int dx = player.playerGetPosX() - enemy.enemyGetPosX();
	int dy = player.playerGetPosY() - enemy.enemyGetPosY();
	int distance = (int)sqrt(dx * dx + dy * dy);

	return distance < 50;
}

enum Scene
{
	title = 0,
	game = 1,
	clear = 2,
	over = 3,
};

int Scene = title;

const char kWindowTitle[] = "GC1D_07_タカブ_コウキ_shooting_Gun";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	const int kWindowWidth = 1280; // ウィンドウの横幅
	const int kWindowHeight = 720; // ウィンドウの縦幅

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	int titleImges = Novice::LoadTexture("./PGtitle.png");//タイトル
	int gameImges = Novice::LoadTexture("./PGgame.png");//ゲーム
	int clearImges = Novice::LoadTexture("./PGclear.png");//クリア
	int overImges = Novice::LoadTexture("./PGover.png");//オーバー

	Player* player = new Player;
	Enemy* enemy = new Enemy;;
	Bullet* bullet = new Bullet;
	bool gameOver = 0;
	int timer = 50;
	//Enemy* enemy = new Enemy();

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		switch (Scene) {

		case title:

			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE])
			{
				Scene = game;
				player->Initalize();
				bullet->Initalize();
			}

			break;

		case game:

			player->move(keys);


			enemy->move();

			bullet->shot(keys, preKeys, player->playerGetPosX(), player->playerGetPosY());

			if (isBulletColliding(*bullet, *enemy)) {
				//Scene = clear;
				gameOver = true;

				bullet->Initalize();
			}
			if (gameOver == 1) {
				timer--;
			}
			if (timer <= 0) {
				gameOver = 0;
				timer = 50;
			}
			if (isPlayerColliding(*player, *enemy)) {
				Scene = over;

				bullet->Initalize();
			}

			break;

		case clear:

			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE])
			{
				Scene = title;
			}

			break;

		case over:

			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE])
			{
				Scene = title;
			}

			break;
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから

		Novice::ScreenPrintf(0, 180, "timer=%d", timer);
		Novice::ScreenPrintf(0, 300, "gameOver=%d", gameOver);

		switch (Scene) {

		case title:

			Novice::DrawSprite(0, 0, titleImges, 1, 1, 0.0f, WHITE);

			break;

		case game:


			Novice::DrawSprite(0, 0, gameImges, 1, 1, 0.0f, WHITE);

			player->Draw();
			if (gameOver == 0) {
				enemy->Draw();
			}
			bullet->Draw();

			break;

		case clear:

			Novice::DrawSprite(0, 0, clearImges, 1, 1, 0.0f, WHITE);

			break;

		case over:

			Novice::DrawSprite(0, 0, overImges, 1, 1, 0.0f, WHITE);

			break;
		}



		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	delete bullet;

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
