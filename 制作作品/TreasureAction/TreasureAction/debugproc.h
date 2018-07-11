#pragma once
//------------------------------------------------
//	デバッグ処理	[debugproc.h]
//------------------------------------------------
 
//------------------------------------------------
//インクルードファイル
//------------------------------------------------
#include "main.h"

//------------------------------------------------
//マクロ定義
//------------------------------------------------
#define	LENGTH_STRING_BUFF		(1024)		// デバッグ表示のバッファ

//------------------------------------------------
//デバッグ処理クラス
//------------------------------------------------
class CDebugProc
{
public:
	CDebugProc();
	~CDebugProc();

	void Init(void);
	void Uninit(void);

	static void Print(const char *fmt, ...);
	static void Draw(void);

	static bool IsEnableDisp(void) { return m_bDisp; }
	static void EnableDisp(bool bDisp) { m_bDisp = bDisp; }

private:
	static LPD3DXFONT m_pFont;				// フォントへのポインタ
	static char m_aStr[LENGTH_STRING_BUFF];	// デバッグ表示のバッファ

	static bool m_bDisp;					// デバッグ表示ON/OFF
};

 