#pragma once
//------------------------------------------------
// ���C������ [main.h]
//------------------------------------------------

//------------------------------------------------
// �C���N���[�h�t�@�C��
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
#define DIRECTINPUT_VERSION (0x0800)	// �x���΍��p
#include "dinput.h"						// DirectInput�֘A�̃w�b�_�[

using namespace std;

//------------------------------------------------
// ���C�u�����t�@�C��
//------------------------------------------------
#pragma comment (lib,"d3d9.lib")
#pragma comment (lib,"d3dx9.lib")
#pragma comment (lib,"dxguid.lib")
#pragma comment (lib,"winmm.lib")
#pragma comment (lib,"dinput8.lib")

//------------------------------------------------
// �}�N����`
//------------------------------------------------
#define SCREEN_WIDTH	(1280)	//�E�B���h�E�̉���
#define SCREEN_HEIGHT	(720)	//�E�B���h�E�̏c��
#define CENTER_WIDTH	(SCREEN_WIDTH / 2) //�E�B���h�E�̉����̒��S
#define CENTER_HEIGHT	(SCREEN_HEIGHT / 2)  //�E�B���h�E�̏c���̒��S

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