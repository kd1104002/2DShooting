#pragma once
#include "Player.h"

class Scene
{
private:

	C_Player m_player;

	KdTexture m_playerTex;

	float playerX;
	float playerY;
	int playerFlg;  //自分（自機）の生存状態（０は死亡、１は生存）

	// テクスチャ ・・・ 画像データ
	KdTexture backTex;


	KdTexture teki1Tex;
	KdTexture tamaTex;
	KdTexture teki2Tex;
	KdTexture SitemTex;
	KdTexture expTex;
	KdTexture teki3Tex;
	KdTexture gameoverTex;
	KdTexture startbackTex;
	KdTexture gamestartTex;
	KdTexture clearTex;

	// 行列 ・・・ 座標などの情報
	//自機
    Math::Matrix playerMat;
	Math::Matrix playerScaleMat;//拡大行列
	Math::Matrix playerTransMat;

	Math::Matrix playerbyuunn;//曲がるときのやつ
	Math::Matrix playerbyuunnScaleMat;
	Math::Matrix playerTransbyuunnMat;

	

	//敵3
	Math::Matrix teki3ScaleMat;//拡大行列
	Math::Matrix teki3TransMat;

	static const int teki3Num = 4;  //敵の数(置き換え不可能

	Math::Matrix teki3Mat[teki3Num];
	float teki3X[teki3Num];
	float teki3Y[teki3Num];
	int teki3HP[teki3Num];   //敵３のHP
	int teki3Flg[teki3Num];  //敵3の生存状態（０は死亡、１は生存）

	static const int teki3animyade = 6;

	float teki3anim[teki3animyade];




	//敵2
	Math::Matrix teki2ScaleMat;//拡大行列
	Math::Matrix teki2TransMat;
	
	static const int teki2Num = 4;  //敵の数(置き換え不可能

	Math::Matrix teki2Mat[teki2Num];
	float teki2X[teki2Num];
	float teki2Y[teki2Num];
	int teki2Flg[teki2Num];  //敵2の生存状態（０は死亡、１は生存）


	static const int teki2animyade = 4;

	float teki2anim[teki2animyade];

	//自機の弾
	static const int tamaNum = 30;

	Math::Matrix tamaMat[tamaNum];
	float tamaX[tamaNum];
	float tamaY[tamaNum];
	int tamaFlg[tamaNum];
	int tamamati;

	//敵2の弾
	static const int teki2tamaNum = 10;

	Math::Matrix teki2tamaMat[teki2tamaNum];
	float teki2tamaX[teki2tamaNum];
	float teki2tamaY[teki2tamaNum];
	int teki2tamaFlg[teki2tamaNum];
	int teki2tamamati[teki2tamaNum];


	Math::Matrix tamaTransMat;

	//敵１
	Math::Matrix teki1ScaleMat;//拡大行列
	Math::Matrix teki1TransMat;

	static const int teki1Num = 5;  //敵の数(置き換え不可能)

	Math::Matrix teki1Mat[teki1Num];
	float teki1X[teki1Num];
	float teki1XMove[teki1Num];
	float teki1Y[teki1Num];
	int teki1Flg[teki1Num];  //敵1の生存状態（０は死亡、１は生存）

	static const int teki1animyade = 5;
	float teki1anim[teki1animyade];

	//スコア
	int score;


	//スコアポイントUPアイテム
	Math::Matrix SitemScaleMat;//拡大行列
	Math::Matrix SitemTransMat;

	Math::Matrix SitemMat;
	float SitemX;
	float SitemY;
	int SitemFlg;  //スコアの箱の状態（０はない、１はある）


	//爆破用
	static const int expNum = 10;

	Math::Matrix expMat[expNum];
	float expX[expNum];
	float expY[expNum];
	int expFlg[expNum];
	float expAnimCnt[expNum]; //アニメーション用




	int roketnohonounotokoro;

	//背景
	Math::Matrix backMat;
	Math::Matrix backScaleMat;//拡大行列
	Math::Matrix backtransMat;
	Math::Matrix backMat2;
	float backY;
	int backFlg;
	Math::Matrix startbackMat;
	Math::Matrix startbackScale;
	Math::Matrix startbacktrans;


	//ゲームオーバー
	Math::Matrix gameoverMat;
	Math::Matrix gameoverScaleMat;//拡大行列
	Math::Matrix gameoverTransMat;

	//スタート
	Math::Matrix gamestartMat;
	Math::Matrix gamestartScaleMat;
	Math::Matrix gamestartTransMat;
	int startFlg;

	//クリア
	Math::Matrix gameclearMat;
	Math::Matrix gameclearScaleMat;
	int clearFlg;



public:

	// 初期設定
	void Init();

	// 解放
	void Release();


	// 更新処理
	void Update();

	// 描画処理
	void Draw2D();

	// GUI処理
	void ImGuiUpdate();

	//爆破処理
	void Explosion(float x, float y);

	//リセット
	void RESET();

	int test = 0;


private:

	Scene() {}

public:
	static Scene& GetInstance()
	{
		static Scene instance;
		return instance;
	}
};

#define SCENE Scene::GetInstance()
