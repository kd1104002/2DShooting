#include "main.h"
#include "Scene.h"


void Scene::Draw2D()
{
	//背景１
	if (backFlg == 0)
	{
	SHADER.m_spriteShader.SetMatrix(backMat);
	SHADER.m_spriteShader.DrawTex(&backTex, Math::Rectangle{ 0,0,1280,720 }, 1.0f);
	}

	//背景2
	if(backFlg==0)
	{
		SHADER.m_spriteShader.SetMatrix(backMat2);
		SHADER.m_spriteShader.DrawTex(&backTex, Math::Rectangle{ 0,0,1280,720 }, 1.0f);
	}
	
	m_player.Draw();


	//敵1anime
	for (int e = 0; e <teki1animyade ; e++)
	{
		if (teki1Flg[e] == 1)
		{
			SHADER.m_spriteShader.SetMatrix(teki1Mat[e]);
			SHADER.m_spriteShader.DrawTex(&teki1Tex, Math::Rectangle{ (int)teki1anim[e]*16,0,16,16}, 1.0f);

		}
		
	}

	//敵2anime
	for (int e = 0; e < teki2animyade; e++)
	{
		if (teki2Flg[e] == 1)
		{
			SHADER.m_spriteShader.SetMatrix(teki2Mat[e]);
			SHADER.m_spriteShader.DrawTex(&teki2Tex, Math::Rectangle{ (int)teki2anim[e] * 16,0,16,16 }, 1.0f);

		}

	}

	//敵3anime
	for (int e = 0; e < teki3animyade; e++)
	{
		if (teki3Flg[e] == 1)
		{
			SHADER.m_spriteShader.SetMatrix(teki3Mat[e]);
			SHADER.m_spriteShader.DrawTex(&teki3Tex, Math::Rectangle{ (int)teki3anim[e] * 16,0,16,16 }, 1.0f);

		}

	}

	//弾
	for (int e = 0; e < tamaNum; e++)
	{
		if (tamaFlg[e] == 1)
		{
			SHADER.m_spriteShader.SetMatrix(tamaMat[e]);
			SHADER.m_spriteShader.DrawTex(&tamaTex, Math::Rectangle{ 0,0,16,16 }, 1.0f);
		}
	}


	//敵２弾
	for (int e = 0; e < teki2tamaNum; e++)
	{
		if (teki2tamaFlg[e] == 1)
		{
			SHADER.m_spriteShader.SetMatrix(teki2tamaMat[e]);
			SHADER.m_spriteShader.DrawTex(&tamaTex, Math::Rectangle{ 16,0,16,16 }, 1.0f);
		}
	}
	//スコアアイテム
	if (SitemFlg == 1)
	{
		SHADER.m_spriteShader.SetMatrix(SitemMat);
		SHADER.m_spriteShader.DrawTex(&SitemTex, Math::Rectangle{ 16,0,16,16 }, 1.0f);
	}

	for (int ex = 0; ex < expNum; ex++)
	{
		if (expFlg[ex] == 1)
		{

			SHADER.m_spriteShader.SetMatrix(expMat[ex]);               //↓一時的にint型として扱う
			SHADER.m_spriteShader.DrawTex(&expTex, Math::Rectangle{ (int)expAnimCnt[ex] * 64,0,64,64 }, 1.0f);

		}
	}

	if (playerFlg == 0)
	{
		SHADER.m_spriteShader.SetMatrix(gameoverMat);
		SHADER.m_spriteShader.DrawTex(&gameoverTex, Math::Rectangle{ 0,0,72,8 }, 1.0f);
	}

	


	if (backFlg == 1)
	{
		SHADER.m_spriteShader.SetMatrix(startbackMat);
		SHADER.m_spriteShader.DrawTex(&startbackTex, Math::Rectangle{ 0,0,1280,720 }, 1.0f);
	}

	if (startFlg == 1)
	{
		SHADER.m_spriteShader.SetMatrix(gamestartMat);
		SHADER.m_spriteShader.DrawTex(&gamestartTex, Math::Rectangle{ 0,0,48,8 }, 1.0f);
	}

	if (clearFlg == 1)
	{
		SHADER.m_spriteShader.SetMatrix(gameclearMat);
		SHADER.m_spriteShader.DrawTex(&clearTex, Math::Rectangle{ 0,0,460,55 }, 1.0f);
	}

	if (backFlg == 0)
	{
		// スコア表示
		char text[200];//①文字列格納用の配列作成
		sprintf_s(text, sizeof(text), "Score:%d", score);//②" "内のの文字列がtextに格納される
		//③描画！
		SHADER.m_spriteShader.DrawString(-640, 360, text, Math::Vector4(1, 1, 0, 1));
	}
	

	


}

void Scene::Update()
{

	m_player.Update();

	if (roketnohonounotokoro == 16)
	{
		roketnohonounotokoro = 0;
	}
	else
	{
		roketnohonounotokoro = 16;
	}

	if (playerFlg == 1)
	{


		if (GetAsyncKeyState(VK_SPACE) & 0x8000)//スペースで弾発射
		{
			if (tamamati == 0)
			{
				for (int ta = 0; ta < tamaNum; ta++)
				{
					if (tamaFlg[ta] == 0)
					{
						tamaFlg[ta] = 1;
						tamaX[ta] = playerX;
						tamaY[ta] = playerY;

						tamamati = 15;
						break;//1発「発射状態」にしたので弾のくり返しを抜ける
					}
				}
			}
		}

		//両端判定
		if (playerX > 610)
		{
			playerX = 610;
		}

		if (playerX < -610)
		{
			playerX = -610;
		}
		if (playerY > 330)
		{
			playerY = 330;
		}

		if (playerY < -330)
		{
			playerY = -330;
		}

		

	}

	//スコアアイテムの移動--------------
	if (SitemFlg == 1)
	{
		SitemY -= 5;
		if (playerFlg == 1)
		{
			//自機とアイテム当たり判定
			float a = SitemX - playerX;//底辺(X座標の差)
			float b = SitemY - playerY;//高さ(Y座標の差)
			float c = sqrt(a * a + b * b);//斜辺(距離)

			if (c < 40)//衝突したら↓
			{
				SitemFlg = 0;//スコアアイテムを消す

				score += 300;
			}


		}
		

		if (SitemY < -1800)//スコアアイテムが一番下に行ったら上にテレポート
		{
			SitemY = 1300;
			SitemX = rand() % (1280 - 64) + 1 - (640 - 32);
		}
	}
	
	if (SitemFlg == 0)
	{
		//スコアアイテムを取ったら上にテレポート
		SitemFlg = 1;
		SitemX= rand() % (1280 - 64) + 1 - (640 - 32);
		SitemY = 2000;
	}





	for (int e = 0; e < teki1Num; e++)
	{
		teki1Y[e] -= 3;

		if (teki1Flg[e] == 1)
		{


			teki1X[e] += teki1XMove[e];

			if (teki1X[e] > 640 - 32|| teki1X[e] < -640 + 32)
			{
					teki1XMove[e] *= -1;
			}

			if (3 > rand () % 100)
			{
				teki1XMove[e] *= -1;
			}

			if (teki1Y[e] < -360 - 32)//敵１が一番下に行ったら上にテレポート
			{
				teki1Y[e] = 360 + 32;
				teki1Flg[e] = 0;
			}

			for(int e=0;e<teki1animyade;e++)
			//teki1アニメーション
			teki1anim[e] += 0.05f;

			if (teki1anim[e] >= 5)
			{
			  	teki1anim[e] = 0;
			}



			if (playerFlg == 1)
			{
				//自機との当たり判定
				float a = teki1X[e] - playerX;//底辺(X座標の差)
				float b = teki1Y[e] - playerY;//高さ(Y座標の差)
				float c = sqrt(a * a + b * b);//斜辺(距離)

				if (c < 40)//衝突したら↓
				{
					teki1Flg[e] = 0;//敵を倒す

					playerFlg = 0;//自機も死ぬようにする

					Explosion(playerX, playerY);
				}

			}
	
		}

	}
	//敵3の処理
	//=============================================================--
	for (int e = 0; e < teki3Num; e++)
	{
		teki3Y[e] -= 3;

		if (teki3Flg[e] == 1)
		{

			if (teki3Y[e] < -360 - 32)//敵１が一番下に行ったら上にテレポート
			{
				teki3Flg[e] = 0;
				teki3Y[e] = 360 + 32;
			}

			for (int e = 0; e < teki3animyade; e++)
				//teki3アニメーション
				teki3anim[e] += 0.08f;

			if (teki3anim[e] >= 6)
			{
				teki3anim[e] = 0;
			}



			if (playerFlg == 1)
			{
				//自機との当たり判定
				float a = teki3X[e] - playerX;//底辺(X座標の差)
				float b = teki3Y[e] - playerY;//高さ(Y座標の差)
				float c = sqrt(a * a + b * b);//斜辺(距離)

				if (c < 40)//衝突したら↓
				{
					teki3Flg[e] = 0;//敵を倒す

					playerFlg = 0;//自機も死ぬようにする

					Explosion(playerX, playerY);
				}

			}

		}

	}

	//===============================================================-

	for (int e = 0; e < teki2Num; e++)
	{
		teki2Y[e] -= 3;
	}


	for (int e = 0; e < teki2Num; e++)
	{

		if (teki2Flg[e] == 1)
		{
			//敵の攻撃のクールダウン
			if (teki2tamamati[e] < 0)
			{
				for (int ta = 0; ta < teki2tamaNum; ta++)
				{



					if (teki2tamaFlg[ta] == 0)
					{
						teki2tamaFlg[ta] = 1;
						teki2tamaX[ta] = teki2X[e];
						teki2tamaY[ta] = teki2Y[e];

						teki2tamamati[e] = 60;

						break;//1発「発射状態」にしたので弾のくり返しを抜ける
					}

				}
			}
			else
			{
				teki2tamamati[e]--;
			}
		

			if (teki2Y[e] < -360 - 32)//敵2が一番下に行ったら上にテレポート
			{
				teki2Flg[e] = 0;
				teki2Y[e] = 360 + 32;
			}

			//teki2アニメーション
			teki2anim[e] += 0.05f;

			if (teki2anim[e] >= 5)
			{
				teki2anim[e] = 0;
			}



			if (playerFlg == 1)
			{
				//自機との当たり判定
				float a = teki2X[e] - playerX;//底辺(X座標の差)
				float b = teki2Y[e] - playerY;//高さ(Y座標の差)
				float c = sqrt(a * a + b * b);//斜辺(距離)

				if (c < 40)//衝突したら↓
				{
					teki2Flg[e] = 0;//敵を倒す

					playerFlg = 0;//自機も死ぬようにする

					Explosion(teki2X[e], teki2Y[e]);


				}

			}

		}

	}

	//============================================



	//弾発射後の処理
	for (int ta = 0; ta < tamaNum; ta++)
	{
		if (tamaFlg[ta] == 1)
		{
			tamaY[ta] += 15;
			//弾が画面外に出たら未発射状態にする

			if (tamaY[ta] > 360 + 8)

			{
				tamaFlg[ta] = 0;
			}
			//弾と敵の当たり判定

			for (int e = 0; e < teki1Num; e++)

			{
				if (teki1Flg[e] == 1)  //敵が生きてるか
				{
					float a = teki1X[e] - tamaX[ta];
					float b = teki1Y[e] - tamaY[ta];
					float c = sqrt(a * a + b * b);

					if (c < 24)//衝突した後の処理
					{
						//敵を倒す
						teki1Flg[e] = 0;
						//弾も倒す（消す）
						tamaFlg[ta] = 0;

						score += 30;

						Explosion(teki1X[e], teki1Y[e]);

						break;//弾が未発射状態になったので敵の繰り返しを抜ける
					}
				}

			}




			for (int e = 0; e < teki2Num; e++)

			{
				if (teki2Flg[e] == 1)  //敵が生きてるか
				{
					float a = teki2X[e] - tamaX[ta];
					float b = teki2Y[e] - tamaY[ta];
					float c = sqrt(a * a + b * b);

					if (c < 24)//衝突した後の処理
					{
						//敵を倒す
						teki2Flg[e] = 0;
						//弾も倒す（消す）
						tamaFlg[ta] = 0;

						score += 50;

						Explosion(teki2X[e], teki2Y[e]);

						break;//弾が未発射状態になったので敵の繰り返しを抜ける
					}
				}

			}

			for (int e = 0; e < teki3Num; e++)

			{
				if (teki3Flg[e] == 1)  //敵が生きてるか
				{
					float a = teki3X[e] - tamaX[ta];
					float b = teki3Y[e] - tamaY[ta];
					float c = sqrt(a * a + b * b);

					if (c < 24)//衝突した後の処理
					{
						teki3HP[e]--;
						//弾も倒す（消す）
						tamaFlg[ta] = 0;

						if (teki3HP[e] <= 0)
						{
							//敵を倒す
							teki3Flg[e] = 0;
						
							score += 50;
						}

						Explosion(teki3X[e], teki3Y[e]);

						break;//弾が未発射状態になったので敵の繰り返しを抜ける
					}
				}
			}


		}

	}





	for (int ta = 0; ta < teki2tamaNum; ta++)
	{
		if (teki2tamaFlg[ta] == 1)
		{
			teki2tamaY[ta] -= 8;

			//弾が画面外に出たら未発射状態にする
			if (teki2tamaY[ta] < -360 + 8)
			{
				teki2tamaFlg[ta] = 0;
				
			}


			if (playerFlg == 1) 
			{
				//自機と敵2の弾の当たり判定------------------------
				float a = teki2tamaX[ta] - playerX;//底辺(X座標の差)
				float b = teki2tamaY[ta] - playerY;//高さ(Y座標の差)
				float c = sqrt(a * a + b * b);//斜辺(距離)

				if (c < 30)//衝突したら↓
				{
					teki2tamaFlg[ta] = 0;//敵の弾を倒す

					playerFlg = 0;//自機も死ぬようにする

					Explosion(teki2tamaX[ta], teki2tamaY[ta]);
				}
				//------------------------
			}


		}

	}





	//自機の弾のクールダウン
	tamamati--;
	if (tamamati < 0)
	{
		tamamati = 0;
	}

	

	//敵の復活(敵１)
	for (int e = 0; e < teki1Num; e++) 
	{
		if (teki1Flg[e] == 0)
		{
			teki1Flg[e] = 1;//敵を蘇生
			teki1X[e] = rand() % (1280 - 64) + 1 - (640 - 32);  // 敵をランダムな場所に設置
			teki1Y[e] = rand() % (700 + 1 - 36) + (360 - 18);;
		}
		

	}

	//敵の復活(敵2)
	for (int e = 0; e < teki2Num; e++)
	{
		if (teki2Flg[e] == 0)
		{
			teki2Flg[e] = 1;//敵を蘇生
			teki2X[e] = rand() % (1280 - 64) + 1 - (640 - 32);  // 敵をランダムな場所に設置
			teki2Y[e] = rand() % (700 + 1 - 36) + (360 - 18);;
		}
	}
	//敵の復活(敵３)
	for (int e = 0; e < teki3Num; e++)
	{
		if (teki3Flg[e] == 0)
		{
			teki3Flg[e] = 1;//敵を蘇生
			teki3HP[e] = 3;
			teki3X[e] = rand() % (1280 - 64) + 1 - (640 - 32);  // 敵をランダムな場所に設置
			teki3Y[e] = rand() % (700 + 1 - 36) + (360 - 18);;
		}
	}
	
	//アニメーション
	for (int ex = 0; ex < expNum; ex++)
	{
		if (expFlg[ex] == 1)
		{
			expAnimCnt[ex] += 0.3f;

			//終了チェック
			if (expAnimCnt[ex] > 7)
			{
				expFlg[ex] = 0;
			}

		}
	}

	//リセット
	RESET();

	//背景をスクロール
	backY -= 3;

	if (backY < -720)
	{
		backY = 0;
	}

	//自機
	playerTransMat = Math::Matrix::CreateTranslation(playerX, playerY, 0);
	playerScaleMat = Math::Matrix::CreateScale(3, 3, 0);
	playerMat = playerScaleMat * playerTransMat;
	//自機のブースター
	playerTransbyuunnMat = Math::Matrix::CreateTranslation(playerX, playerY-38, 0);
	playerbyuunnScaleMat = Math::Matrix::CreateScale(2, 2, 0);
	playerbyuunn = playerbyuunnScaleMat * playerTransbyuunnMat;

	//ゲームオーバー表示
	gameoverMat = Math::Matrix::CreateScale(6, 6, 0);

	//敵１
	for (int e = 0; e < teki1Num; e++)
	{
		teki1TransMat = Math::Matrix::CreateTranslation(teki1X[e], teki1Y[e], 0);
		teki1ScaleMat = Math::Matrix::CreateScale(3, 3, 0);
		teki1Mat[e] = teki1ScaleMat * teki1TransMat;

	}

	//敵2
	for (int e = 0; e < teki2Num; e++)
	{
		teki2TransMat = Math::Matrix::CreateTranslation(teki2X[e], teki2Y[e], 0);
		teki2ScaleMat = Math::Matrix::CreateScale(3, 3, 0);
		teki2Mat[e] = teki2ScaleMat * teki2TransMat;

	}

	//敵3
	for (int e = 0; e < teki3Num; e++)
	{
		teki3TransMat = Math::Matrix::CreateTranslation(teki3X[e], teki3Y[e], 0);
		teki3ScaleMat = Math::Matrix::CreateScale(3, 3, 0);
		teki3Mat[e] = teki3ScaleMat * teki3TransMat;

	}

	//爆発
	for (int ex = 0; ex < expNum; ex++)
	{
		expMat[ex] = Math::Matrix::CreateTranslation(expX[ex], expY[ex], 0);
	}

	//スコアアイテム
	teki2TransMat = Math::Matrix::CreateTranslation(SitemX, SitemY, 0);
	teki2ScaleMat = Math::Matrix::CreateScale(3, 3, 0);
	SitemMat = teki2ScaleMat * teki2TransMat;


	//背景//
	backtransMat = Math::Matrix::CreateTranslation(0, backY+360, 0);

	backMat2 = Math::Matrix::CreateTranslation(0, backY, 0);

	backScaleMat = Math::Matrix::CreateScale(2, 3.6, 0);
	backMat = backScaleMat * backtransMat;
	backMat2 = backScaleMat * backtransMat;

	gamestartMat = Math::Matrix::CreateScale(13, 13, 0);

	gameclearMat = Math::Matrix::CreateScale(2, 2, 0);

	for (int ta = 0; ta < tamaNum; ta++)
	{
		//自分の弾
		tamaMat[ta] = Math::Matrix::CreateTranslation(tamaX[ta], tamaY[ta], 0);
	}

	for (int ta = 0; ta < teki2tamaNum; ta++)
	{
		//敵の弾
		teki2tamaMat[ta] = Math::Matrix::CreateTranslation(teki2tamaX[ta], teki2tamaY[ta], 0);
	}
	//ある程度スコアが上がったら敵２が出てくる
	for (int e = 0; e < teki2Num; e++)
	{
		if (score <= 50)
		{
			teki2Flg[e] = 0;
		}
	}
	for (int e = 0; e < teki3Num; e++)
	{
		if (score <= 200)
		{
			teki3Flg[e] = 0;
		}
	}

	
	//クリアに必要な点数の設定
	if (score >= 1000)
	{
		clearFlg = 1;
		backFlg = 1;
	}

}

//最初の一回だけ実行!
void Scene::Init()
{

	m_player.Init();

	//乱数の初期化をする
	srand(time(0));
	rand();

	//スコア初期化
	score = 0;

	backFlg = 1;
	startFlg = 1;
	clearFlg = 0;

	for (int e = 0; e < teki1Num; e++)
	{
		teki1XMove[e] = 3;
	}

	SitemFlg = 1;
	SitemX = rand() % (1280 - 64) + 1 - (640 - 32);
	SitemY = 1800;

	for (int ta = 0; ta < teki2tamaNum; ta++)
	{
		teki2tamaFlg[ta] = 0;
	}

	for (int ta = 0; ta < tamaNum; ta++)
	{
		tamaFlg[ta] = 0;
	}

	for (int e = 0; e < teki1Num; e++)
	{
		teki1Flg[e] = 1;
	}


	for (int e = 0; e < teki2Num; e++)
	{
		teki2Flg[e] = 1;
		teki2tamamati[e] = 60;
	}

	for (int e = 0; e < teki3Num; e++)
	{
		teki3Flg[e] = 1;
	}


	playerFlg = 1;


	// 画像の読み込み処理
	backTex.Load("texture/Space Background.png");
	m_playerTex.Load("texture/Player_ship (16 x 16).png");

	teki1Tex.Load("texture/Lips (16 x 16).png");
	tamaTex.Load("texture/bullet.png");
	teki2Tex.Load("texture/Bon_Bon (16 x 16).png");
	SitemTex.Load("texture/Circle_+_Square_+_Missile_pick-ups (16 x 16).png");
	expTex.Load("texture/explosion.png");
	teki3Tex.Load("texture/Alan (16 x 16).png");
	gameoverTex.Load("texture/GAME_OVER (72 x 8).png");
	startbackTex.Load("texture/Space Background.png");
	gamestartTex.Load("texture/START (48 x 8).png");
	clearTex.Load("texture/Cool Text - game clear 484904783661098.png");

	//敵1
	for (int e = 0; e < teki1Num; e++)
	{
		teki1X[e] = rand() % (1280 + 1 - 64) - (640 - 32);//-640～640
		teki1Y[e] = rand() % (700 + 1 - 36) + (360 - 18);;
		teki1Flg[e] = 1;
	}
	//敵2
	for (int e = 0; e < teki2Num; e++)
	{
		teki2X[e] = rand() % (1280 + 1 - 64) - (640 - 32);//-640～640
		teki2Y[e] = rand() % (700+1-36)+(360-18);
		teki2Flg[e] = 1;
	}
	//敵3
	for (int e = 0; e < teki2Num; e++)
	{
		teki3X[e] = rand() % (1280 + 1 - 64) - (640 - 32);//-640～640
		teki3Y[e] = rand() % (700 + 1 - 36) + (360 - 18);
		teki3HP[e] = 3;
		teki3Flg[e] = 1;
	}

	for (int ta = 0; ta < tamaNum; ta++)
	{
		tamaX[ta] = 0;
		tamaY[ta] = 0;
		tamaFlg[ta] = 0;
	}
	tamamati = 0;


	for (int ta = 0; ta < teki2tamaNum; ta++)
	{
		teki2tamaX[ta] = 0;
		teki2tamaY[ta] = 0;
		teki2tamaFlg[ta] = 0;
		teki2tamamati[ta] = 0;
	}
	

}

void Scene::Release()
{
	// 画像の解放処理(忘れずに!)
	backTex.Release();
	m_playerTex.Release();
	teki1Tex.Release();
	tamaTex.Release();
	teki2Tex.Release();
	SitemTex.Release();
	expTex.Release();
	teki3Tex.Release();
	gameoverTex.Release();
	startbackTex.Release();
	gamestartTex.Release();
	clearTex.Release();
}

void Scene::ImGuiUpdate()
{
	return;

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Once);

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d", APP.m_fps);
	}
	ImGui::End();
}

void Scene::Explosion(float x, float y)
{
	//爆発発生させる
	for (int ex = 0; ex < expNum; ex++)
	{
		if (expFlg[ex] == 0)
		{
			expFlg[ex] = 1;
			expX[ex] = x;
			expY[ex] = y;
			expAnimCnt[ex] = 0;

			//爆破生成したら終わり
			break;
		}
	}
}

void Scene::RESET()
{

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		startFlg = 0;
		backFlg = 0;
		playerFlg = 1;
		playerX = 0;
		playerY = -200;
		clearFlg = 0;
		
		for (int e = 0; e < teki1Num; e++) 
		{
			teki1Flg[e] = 0;
		}

		for (int e = 0; e < teki2Num; e++)
		{
			teki2Flg[e] = 0;
		}

		for (int e = 0; e < teki2tamaNum; e++)
		{
			teki2tamaFlg[e] = 0;
		}

		for (int e = 0; e < teki3Num; e++)
		{
			teki3Flg[e] = 0;
		}
		score = 0;

		SitemFlg = 0;
	}

}
