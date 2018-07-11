//------------------------------------------------
//マネージャーの処理	[manager.cpp]
//------------------------------------------------

//------------------------------------------------
// インクルードファイル
//------------------------------------------------
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "fade.h"
#include "input.h"
#include "light.h"
#include "camera.h"
#include "light.h"
#include "sound.h"
#include "meshfiled.h"
#include "editor.h"

//------------------------------------------------
//マクロ定義
//------------------------------------------------

//------------------------------------------------
//静的変数
//------------------------------------------------
CManager::MODE CManager::m_mode;
CManager::GAME_STATE CManager::m_GameState;

CRenderer *CManager::m_pRenderer = NULL;
CSound *CManager::m_pSound = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CLight *CManager::m_pLight = NULL;
CCamera *CManager::m_pCamera = NULL;
CInputJoypad *CManager::m_pJoypad = NULL;
CFade *CManager::m_pFade = NULL;
CEditor *CManager::m_pEditor = NULL;
#ifdef _DEBUG
CDebugProc *CManager::m_pDebugProc = NULL;
#endif // _DEBUG
//------------------------------------------------
//コンストラクタ
//------------------------------------------------
CManager::CManager()
{

}

//------------------------------------------------
//デストラクタ
//------------------------------------------------
CManager::~CManager()
{

}

//------------------------------------------------
//初期化処理
//------------------------------------------------
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{

	//レンダリング処理の初期化処理
	m_pRenderer = new CRenderer;
	m_pRenderer->Init(hWnd, bWindow);

	//キー操作の初期化処理
	m_pInputKeyboard = new CInputKeyboard;
	m_pInputKeyboard->Init(hInstance, hWnd);

	//カメラ処理の初期化処理
	m_pCamera = new CCamera;
	m_pCamera->Init();

	//ライト処理の初期化処理
	m_pLight = new CLight;
	m_pLight->Init();

	//サウンド処理の初期化処理
	m_pSound = new CSound;
	m_pSound->Init(hWnd);

	//ジョイパッド操作の初期化処理
	m_pJoypad = new CInputJoypad;
	m_pJoypad->Init(hInstance, hWnd);

	//フェード
	m_pFade = CFade::Create();

	MODE mode;
	mode = MODE::MODE_EDITER;

#ifdef _DEBUG
	m_pDebugProc = new CDebugProc;
	m_pDebugProc->Init();

	//char buffer[256];
	//FILE *fp;
	//fopen_s(&fp, "data/SETTING/mode.ini", "r");
	//if (!fp)
	//{
	//	MessageBox(NULL, "SETTINGフォルダにmode.iniが入っていません。", NULL, NULL);
	//}
	//fgets(buffer, sizeof(buffer), fp);
	//mode = (MODE)atoi(buffer);
	//fclose(fp);

	m_pFade->Start(CFade::STATUS_FADEIN, 60);
#endif // _DEBUG
 	SetMode(mode);
 	return S_OK;
}

//------------------------------------------------
//終了処理
//------------------------------------------------
void CManager::Uninit(void)
{
	//レンダリング処理の終了処理
	SafeUninitDelete(m_pRenderer);
	SafeUninitDelete(m_pSound);
	SafeUninitDelete(m_pInputKeyboard);
	SafeUninitDelete(m_pLight);
	SafeUninitDelete(m_pCamera);
	SafeUninitDelete(m_pJoypad);
	SafeUninit(m_pFade);

#ifdef _DEBUG
	SafeUninitDelete(m_pDebugProc);
#endif //_DEBUG

	//描画対象オブジェクトの破棄
	CScene::ReleaseAll();

}

//------------------------------------------------
//更新処理
//------------------------------------------------
void CManager::Update(void)
{
	//キーボードの更新処理
	if (m_pInputKeyboard)
	{
		m_pInputKeyboard->Update();
	}

	//ジョイパッドの更新処理
	if (m_pJoypad)
	{
		m_pJoypad->Update();
	}

	//カメラの更新処理
	if (m_pCamera)
	{
		m_pCamera->Update();
	}

	//オブジェクトの更新処理
	if (m_pRenderer)
	{
		m_pRenderer->Update();
	}
}

//------------------------------------------------
// 描画処理
//------------------------------------------------
void CManager::Draw(void)
{
	//オブジェクトの描画処理
	if (m_pRenderer)
	{
		m_pRenderer->Draw();
	}
}

//------------------------------------------------
//モードの変更
//------------------------------------------------
void CManager::SetMode(MODE mode) {

	m_pCamera->Initialize();
	m_pSound->Stop();

	switch (m_mode)
	{
	case MODE_EDITER:
		SafeUninit(m_pEditor);
		break;
	//case MODE_TUTORIAL:
	//	SafeUninit(m_pTutorial);
	//	break;
	//case MODE_STAGE001:
	//	SafeUninit(m_pStage1);
	//	break;
	//case MODE_GAMECLEAR:
	//	SafeUninit(m_pGameClear);
	//	break;
	//case MODE_GAMEOVER:
	//	SafeUninit(m_pGameOver);
	//	break;
	//case MODE_DEBUG:
	//	SafeUninit(m_pDebugStage);
	//	break;
	//case MODE_RANKING:
	//	SafeUninit(m_apRanking);
	//	break;
	//case MODE_EDITOR:
	//	SafeUninit(m_apEditor);
	//	break;
	}
	 switch (mode)
	 {
	case MODE_EDITER:
		if (!m_pEditor)
		{
			m_pEditor = new CEditor;
			m_pEditor->Init();
			m_pFade->Start(CFade::STATUS_FADEIN, 60);
		}
		break;
	//case MODE_TUTORIAL:
	//	if (!m_pTutorial)
	//	{
	//		m_pTutorial = new CTutorial;
	//		m_pTutorial->Init();
	//		m_pFade->Start(CFade::STATUS_FADEIN, 60);
	//	}
	//	break;
	//case MODE_STAGE001:
	//	if (!m_pStage1)
	//	{
	//		m_pStage1 = new CStage1();
	//		m_pStage1->Init();
	//		m_pFade->Start(CFade::STATUS_FADEIN, 60);
	//	}
	//	break;
	//case MODE_GAMECLEAR:
	//	if (!m_pGameClear)
	//	{
	//		m_pGameClear = new CGameClear;
	//		m_pGameClear->Init();
	//		m_pFade->Start(CFade::STATUS_FADEIN, 60);
	//	}
	//	break;
	//case MODE_GAMEOVER:
	//	if (!m_pGameOver)
	//	{
	//		m_pGameOver = new CGameOver;
	//		m_pGameOver->Init();
	//		m_pFade->Start(CFade::STATUS_FADEIN, 60);
	//	}
	//	break;
	//case MODE_RANKING:
	//	if (!m_apRanking)
	//	{
	//		m_apRanking = new CRanking;
	//		m_apRanking->Init();
	//		m_pFade->Start(CFade::STATUS_FADEIN, 60);
	//	}
	//	break;
	//case MODE_DEBUG:
	//	if (!m_pDebugStage)
	//	{
	//		m_pDebugStage = new CDebugStage;
	//		m_pDebugStage->Init();
	//		m_pFade->Start(CFade::STATUS_FADEIN, 60);
	//	}
	//	break;
	//case MODE_EDITOR:
	//	if (!m_apEditor)
	//	{
	//		m_apEditor = new CEditor;
	//		m_apEditor->Init();
	//		m_pFade->Start(CFade::STATUS_FADEIN, 60);
	//	}
	//	break;
	case MODE_EXIT:
		PostQuitMessage(0);
		break;
	}

	m_mode = mode;
}
//------------------------------------------------
// モードの取得
//------------------------------------------------
CManager::MODE CManager::GetMode(void)
{
	return m_mode;
}

//------------------------------------------------
// ゲームの状態の変更
//------------------------------------------------
void CManager::SetGameState(GAME_STATE GameState)
{
	m_GameState = GameState;
}

//------------------------------------------------
// ゲームの状態の取得
//------------------------------------------------
CManager::GAME_STATE CManager::GetGameState(void)
{
	return m_GameState;
}
