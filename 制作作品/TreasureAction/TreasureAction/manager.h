#pragma once
//------------------------------------------------
//マネージャーの処理	[manager.h]
//------------------------------------------------

//------------------------------------------------
//インクルードファイル
//------------------------------------------------
#include "main.h"
#include "mathlib.h"

//------------------------------------------------
//マクロ定義
//------------------------------------------------
#define OBJECT_SIZE	(50.0f)
#define MAX_STAGE	(10)
//------------------------------------------------
//プロトタイプ宣言
//------------------------------------------------
class CRenderer;
class CDebugProc;
class CSound;
class CFade;
class CInputKeyboard;
class CLight;
class CCamera;
class CInputJoypad;
class CEditor;

//------------------------------------------------
//マネージャークラス
//------------------------------------------------
class CManager
{
public:
	CManager();
	~CManager();

	//ゲームモード
	typedef enum
	{
		MODE_NONE = 0,
		MODE_TITLE,
		MODE_EDITER,
		MODE_EXIT,
		MODE_MAX,
	}MODE;

	//ゲームの状態
	typedef enum
	{
		GAME_STATE_NONE = 0,
		GAME_STATE_START,
		GAME_STATE_MAIN,
		GAME_STATE_GOAL,
		GAME_STATE_BOSS,
		GAME_STATE_MAX,
	}GAME_STATE;


	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static void SetMode(MODE mode);
	static MODE GetMode(void);
	static void SetGameState(GAME_STATE gamestate);
	static GAME_STATE GetGameState(void);

	static CRenderer *GetRenderer(void) { return m_pRenderer; }
	static CSound *GetSound(void) { return m_pSound; }
	static CFade *Getfade(void) { return m_pFade; }
	static CInputKeyboard *GetInputKeyboard(void) { return m_pInputKeyboard; }
	static CLight *GetLight(void) { return m_pLight; }
	static CCamera *GetCamera(void) { return m_pCamera; }
	static CInputJoypad *GetInputJoypad(void) { return m_pJoypad; }
	static CEditor *GetEditor(void) { return m_pEditor; }

private:
	static MODE m_mode;
	static GAME_STATE m_GameState;
	static CRenderer *m_pRenderer;
	static CFade *m_pFade;
	static CSound *m_pSound;
	static CInputKeyboard *m_pInputKeyboard;
	static CLight *m_pLight;
	static CCamera *m_pCamera;
	static CInputJoypad *m_pJoypad;
	static CEditor *m_pEditor;

#ifdef _DEBUG
	static CDebugProc *m_pDebugProc;
#endif 
};
 