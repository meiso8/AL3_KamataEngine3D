#include "GameScene.h"
// #include "ImGuiManager.h"
// #include "PrimitiveDrawer.h"
//#include "AxisIndicator.h"

using namespace KamataEngine;

#define WIN_WIDTH  1280
#define WIN_HEIGHT 720

void GameScene::Initialize() {

	// メンバ変数への代入処理

	// ここにインゲームの初期化処理を書く

	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("test.jpg");

	// スプライトインスタンスの生成
	sprite_ = Sprite::Create(textureHandle_, {128, 128}, {1, 1, 1, 1}, {0.0f, 0.0f}, false, false);
	sprite_->SetColor(Vector4(0.5f, 0.5f, 0.5f, 1.0f));

	// 3Dモデルの生成
	model_ = Model::Create();
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// カメラの初期化
	camera_.Initialize();

	// サウンドデータの読み込み
	soundDataHandle_ = Audio::GetInstance()->LoadWave("mokugyo.wav");
	// 音声再生
	voiceHandle_ = Audio::GetInstance()->PlayWave(soundDataHandle_, true);
	// ライン描画が参照するカメラを指定する（アドレス渡し）
	PrimitiveDrawer::GetInstance()->SetCamera(&camera_);

	// デバックカメラ
	debugCamera_ = new DebugCamera(WIN_WIDTH, WIN_HEIGHT);

	//軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向表示が参照するビュープロジェクションを指定する（アドレス渡し）
	AxisIndicator::GetInstance()->SetTargetCamera(&debugCamera_->GetCamera());
};

void GameScene::Update() {

	// ここにインゲームの更新処理を書く

	// スプライトの今の座標を取得
	Vector2 position = sprite_->GetPosition();
	// 座標を{2,1}移動
	position.x += 2.0f;
	position.y += 1.0f;
	// 移動した座標をスプライトに反映
	sprite_->SetPosition(position);

	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		// 音声停止
		Audio::GetInstance()->StopWave(voiceHandle_);
	}

	// デバッグテキストの表示

#ifdef _DEBUG
	ImGui::Begin("Debug1");

	ImGui::Text("Yoshida Tomoka %d.%d.%d", 2025, 4, 8);
	ImGui::InputFloat3("InputFloat3", inputFloat3);
	ImGui::SliderFloat3("SliderFloat3", inputFloat3, 0.0f, 1.0f);
	// デモウィンドウの表示を有効化
	ImGui::ShowDemoWindow();

	ImGui::End();
#endif

	// デバッグカメラの更新
	debugCamera_->Update();
};

void GameScene::Draw() {

	// DirectXCommonのインスタンスの取得 描画コマンドリストの取得のため
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// スプライトの描画前処理
	 Sprite::PreDraw(dxCommon->GetCommandList());

	// ここにスプライトのインスタンスの描画処理を記述する
	 sprite_->Draw();

	// スプライト描画後処理
	 Sprite::PostDraw();

	/*3Dモデル描画前処理*/
	Model::PreDraw(dxCommon->GetCommandList());

	//// 3Dモデルの描画
	//model_->Draw(worldTransform_, camera_, textureHandle_);

	// 3Dモデルの描画
	model_->Draw(worldTransform_, debugCamera_->GetCamera(), textureHandle_);

	// 3Dモデル描画語処理
	Model::PostDraw();

	// ラインを描画する //始点終点色をそれぞれ指定 4096本まで

    PrimitiveDrawer::GetInstance()->DrawLine3d({0, 0, 0}, {0, 10, 0}, {1.0f, 0.0f, 0.0f, 1.0f});

};

GameScene::~GameScene() {
	delete sprite_;
	delete model_;
	delete debugCamera_;
}