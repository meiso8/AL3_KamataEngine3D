#include "GameScene.h"
#include "KamataEngine.h"
#include <Windows.h>

// KamataEngineを構成する各クラスは基本的に KamataEngine namespaceに所属している
// 　これを宣言することで毎度 KamataEngine:: と入力する必要がなくなる
using namespace KamataEngine;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// エンジンの初期化
	KamataEngine::Initialize(L"LE2A_18_ヨシダ_トモカ_AL3");

	// DirectXCommonのインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// ImGuiManagerインスタンスの取得 外部ライブラリを使用してデバックテキストの表示を行う
	ImGuiManager* imguiManager = ImGuiManager::GetInstance();

	// ゲームシーンのインスタンスの取得
	GameScene* gameScene = new GameScene();
	// ゲームシーンの初期化
	gameScene->Initialize();

	// =======================
	// メインループ
	// =======================

	while (true) {

		// エンジンの更新
		if (KamataEngine::Update()) {
			break;
		}

		// ImGui受付開始
		imguiManager->Begin();

		// ゲームシーンの更新
		gameScene->Update();

		// ImGui受付終了　開始から終了までに命令を複数貯めておく
		imguiManager->End();

		// =======================
		// 描画開始　描画ターゲットなどの設定
		// =======================

		//貯め始める
		dxCommon->PreDraw();

		//
		// ここに描画処理を記述する
		//

		// ゲームシーンの描画
		gameScene->Draw();

		//軸表示の描画
		AxisIndicator::GetInstance()->Draw();

		// ImGuiの描画 コマンドリストに積む
		imguiManager->Draw();

		// =======================
		// 描画終了　描画コマンドの実行
		// =======================

		dxCommon->PostDraw();
	}

	// ゲームシーンの解放
	delete gameScene;
	// nullptrの代入
	gameScene = nullptr;

	// エンジンの終了処理
	KamataEngine::Finalize();

	return 0;
}
