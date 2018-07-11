#pragma once
//------------------------------------------------
// メイン処理 [main.h]
//------------------------------------------------

//------------------------------------------------
// インクルードファイル
//------------------------------------------------
#include <Windows.h>
#include <time.h>
#include <string>
#include <iostream>
#include "d3dx9.h"
#include "stdio.h"
#include "XAudio2.h"
#ifndef MEMORY_LEAK_H
#define MEMORY_LEAK_H
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <list>
#ifdef _DEBUG
#define new new(_NORMAL_BLOCK,__FILE__,__LINE__)
#endif
#endif
#define DIRECTINPUT_VERSION (0x0800)	// 警告対策用
#include "dinput.h"						// DirectInput関連のヘッダー

using namespace std;

//------------------------------------------------
// ライブラリファイル
//------------------------------------------------
#pragma comment (lib,"d3d9.lib")
#pragma comment (lib,"d3dx9.lib")
#pragma comment (lib,"dxguid.lib")
#pragma comment (lib,"winmm.lib")
#pragma comment (lib,"dinput8.lib")

//------------------------------------------------
// マクロ定義
//------------------------------------------------
#define SCREEN_WIDTH	(1280)	//ウィンドウの横幅
#define SCREEN_HEIGHT	(720)	//ウィンドウの縦幅
#define CENTER_WIDTH	(SCREEN_WIDTH / 2) //ウィンドウの横幅の中心
#define CENTER_HEIGHT	(SCREEN_HEIGHT / 2)  //ウィンドウの縦幅の中心

#define Vector3 D3DXVECTOR3
#define Vector2 D3DXVECTOR2

namespace vector3NS
{
	const Vector3 ZERO = Vector3(0.0f, 0.0f, 0.0f);
	const Vector3 ONE = Vector3(1.0f, 1.0f, 1.0f);
	const Vector3 CENTER = Vector3(CENTER_WIDTH, CENTER_HEIGHT, 0.0f);
}

namespace colorNS
{
	const D3DXCOLOR WHITE = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	const D3DXCOLOR RED = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	const D3DXCOLOR GREEN = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	const D3DXCOLOR BLUE = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	const D3DXCOLOR BLACK = D3DXCOLOR(0.0f, 0.0f, 0.0f,1.0f);
}

template<typename T>
void SafeUninit(T &p)
{
	if (p)
	{
		p->Uninit();
		p = NULL;
	}
}

template<typename T>
void SafeRelease(T &p)
{
	if (p)
	{
		p->Release();
		p = NULL;
	}
}

template<typename T>
void SafeUninitDelete(T &p)
{
	if (p)
	{
		p->Uninit();
		delete p;
		p = NULL;
	}
}