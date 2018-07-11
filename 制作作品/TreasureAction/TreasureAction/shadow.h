#pragma once
//------------------------------------------------
// 影の処理	[shadow.h]
//------------------------------------------------

//------------------------------------------------
// インクルードファイル
//------------------------------------------------
#include "scene.h"
#include "main.h"

//------------------------------------------------
// 影クラス
//------------------------------------------------
class CShadow : public CScene
{
public:
	CShadow();
	~CShadow();
	HRESULT Init(Vector3 pos, Vector2 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	Vector3 GetPosition(void) { return m_pos; }
	void SetPosition(Vector3 pos) { m_pos = pos; }
	void LoadPosition(Vector3 pos);

	Vector3 GetRotation(void) { return m_rot; }
	void SetRotation(Vector3 rot) { m_rot = rot; }

	void LoadTexture(const char *pTexName);

private:
	Vector3 m_pos;
	Vector3 m_rot;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファー
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	// インデックスバッファー
	LPDIRECT3DTEXTURE9 m_pTexture;		// テクスチャー
	int m_iVertex_X;					// 横の頂点数
	int m_iVertex_Y;					// 縦の頂点数
	int m_iIdx;							// インデックス数
	int m_iVer;							// 頂点数
	int m_iPoly;						// ポリゴン数

	static const char *pTextureName[];
	void MakeVertex(LPDIRECT3DDEVICE9 pDevice);
	void MakeIndex(LPDIRECT3DDEVICE9 pDevice);
};