#pragma once
//------------------------------------------------
// メッシュフィールドの処理	[meshfiled.h]
//------------------------------------------------

//------------------------------------------------
// インクルードファイル
//------------------------------------------------
#include "scene3D.h"

//------------------------------------------------
// メッシュフィールドクラス
//------------------------------------------------
class CMeshFiled : public CScene
{
public:
	CMeshFiled();
	~CMeshFiled();
	static CMeshFiled *Create(Vector3 pos, Vector3 rot, int iVertexX, int iVertexY, Vector2 size);
	HRESULT Init(Vector3 pos,Vector3 rot,int iVertexX,int iVertexY,Vector2 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	Vector3 GetPosition(void) { return m_pos; }
	void SetPosition(Vector3 pos) { m_pos = pos; }

	Vector3 GetRotation(void) { return m_rot; }
	void SetRotation(Vector3 rot) { m_rot = rot; }

	void LoadTexture(const char *pTexName);
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファー
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	// インデックスバッファー
	LPDIRECT3DTEXTURE9 m_pTexture;		// テクスチャー
	int m_iVertex_X;					// 横の頂点数
	int m_iVertex_Y;					// 縦の頂点数
	int m_iIdx;							// インデックス数
	int m_iVer;							// 頂点数
	int m_iPoly;						// ポリゴン数
	Vector3 m_pos;					// 位置座標
	Vector3 m_rot;					// 回転座標
	Vector2 m_Size;					// 大きさ
	D3DXMATRIX m_mtxWorld;				// マトリックス
	static const char *m_pTextureName[];	// テクスチャーの名前
	void MakeVertex(LPDIRECT3DDEVICE9 pDevice);	// 頂点の設定
	void MakeIndex(LPDIRECT3DDEVICE9 pDevice);	// インデックスの設定
	
};