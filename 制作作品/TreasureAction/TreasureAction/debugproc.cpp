//------------------------------------------------
//デバッグ処理	[debugproc.cpp]
//------------------------------------------------

//------------------------------------------------
//インクルードファイル
//------------------------------------------------
#include <stdio.h>
#include <stdarg.h>
#include "debugproc.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"

//------------------------------------------------
// 静的変数
//------------------------------------------------
LPD3DXFONT CDebugProc::m_pFont = NULL;
char CDebugProc::m_aStr[LENGTH_STRING_BUFF] = { "\0" };
bool CDebugProc::m_bDisp = true;

//------------------------------------------------
// コンストラクタ
//------------------------------------------------
CDebugProc::CDebugProc()
{
	// バッファクリア
	memset(m_aStr, 0, sizeof m_aStr);
}

//------------------------------------------------
// デストラクタ
//------------------------------------------------
CDebugProc::~CDebugProc()
{

}

//------------------------------------------------
// 初期化処理
//------------------------------------------------
void CDebugProc::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//// 情報表示用フォントを設定
	//D3DXCreateFont(pDevice, 60, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
	//	OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "k8x12.ttf", &m_pFont);


	//AddFontResource("data/font/k8x12.ttf");

	// 情報表示用フォントを設定
	D3DXCreateFont(pDevice, 30, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "", &m_pFont);
}

//------------------------------------------------
// 終了処理
//------------------------------------------------
void CDebugProc::Uninit(void)
{
	if (m_pFont != NULL)
	{// 情報表示用フォントの開放
		m_pFont->Release();
		m_pFont = NULL;
	}
}
//------------------------------------------------
// インクルードファイル
//------------------------------------------------
void CDebugProc::Print(const char *fmt, ...)
{
#ifdef _DEBUG
#if 0
	long *pParam;
	static char aBuf[256];

	pParam = (long*)&fmt;
	sprintf_s(aBuf, 256, fmt, pParam[1], pParam[2], pParam[3], pParam[4],
		pParam[5], pParam[6], pParam[7], pParam[8],
		pParam[9], pParam[10], pParam[11], pParam[12]);
#else

	va_list list;			// 可変引数を処理する為に使用する変数
	const char *pCur;
	char aBuf[256] = { "\0" };
	char aWk[32];

	// 可変引数にアクセスする前の初期処理
	va_start(list, fmt);

	pCur = fmt;
	for (; *pCur; ++pCur)
	{
		if (*pCur != '%')
		{
			sprintf_s(aWk, 32, "%c", *pCur);

		}
		else
		{
			pCur++;

			switch (*pCur)
			{
			case 'd':
				// 可変引数にアクセスしてその変数を取り出す処理
				sprintf_s(aWk, 32, "%d", va_arg(list, int));
				break;

			case 'f':
				// 可変引数にアクセスしてその変数を取り出す処理
				sprintf_s(aWk, 32, "%f", va_arg(list, double));		// double型で指定
				break;

			case 's':
				// 可変引数にアクセスしてその変数を取り出す処理
				sprintf_s(aWk, 32, "%s", va_arg(list, char*));
				break;

			case 'c':
				// 可変引数にアクセスしてその変数を取り出す処理
				sprintf_s(aWk, 32, "%c", va_arg(list, char));
				break;

			default:
				sprintf_s(aWk, 32, "%c", *pCur);
				break;
			}
		}

		strcat_s(aBuf, 256, aWk);
	}

	// 可変引数にアクセスした後の終了処理
	va_end(list);

#endif
	if ((strlen(m_aStr) + strlen(aBuf)) < sizeof m_aStr - 1)
	{
		strcat_s(m_aStr, 1024, aBuf);
	}
#endif
}

//------------------------------------------------
// 描画処理
//------------------------------------------------
void CDebugProc::Draw(void)
{
#ifdef _DEBUG

	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	if (pInputKeyboard->GetKeyTrigger(DIK_F3))
	{
		m_bDisp = !m_bDisp;
	}

	if (m_bDisp)
	{
		RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

		m_pFont->DrawText(NULL, m_aStr, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(255, 0, 255, 0));

		// バッファクリア
		memset(m_aStr, 0, sizeof m_aStr);
	}
#endif
}