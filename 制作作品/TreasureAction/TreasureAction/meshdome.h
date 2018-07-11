#pragma once
//------------------------------------------------
// メッシュドームの処理	[meshdome.h]
//------------------------------------------------

//------------------------------------------------
// インクルードファイル
//------------------------------------------------
#include "main.h"
#include "scene.h"

//------------------------------------------------
// メッシュドームクラス
//------------------------------------------------
class CMeshDome : public CScene
{
public:
	CMeshDome();
	~CMeshDome();

	static CMeshDome *Create(Vector3 pos,Vector3 rot,float fLength,float fRadius,int iPolygonX,int iPolygonY);
	HRESULT Init(Vector3 pos, Vector3 rot, float fLength, float fRadius, int iPolygonX, int iPolygonY);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	Vector3 GetPosition(void) { return m_pos; }
	void SetPosition(Vector3 pos) { m_pos = pos; }

	Vector3 GetRotation(void) { return m_rot; }
	void SetRotation(Vector3 rot) { m_rot = rot; }

	void LoadTexture(const char *pTexName);
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// 頂点バッファー
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;			// インデックスバッファー
	LPDIRECT3DTEXTURE9 m_pTexture;				// テクスチャー
	LPDIRECT3DVERTEXBUFFER9 m_pVtxTop;
	LPDIRECT3DINDEXBUFFER9 m_pIndexTop;
	int m_iVertex_X;							// 横の頂点数
	int m_iVertex_Y;							// 縦の頂点数
	int m_iIdx;									// インデックス数
	int m_iVer;									// 頂点数
	int m_iPoly;								// ポリゴン数
	float m_fRadius;							// 半径
	float m_fLength;							// 距離
	Vector3 m_pos;								// 位置座標
	Vector3 m_rot;								// 回転座標
 	D3DXMATRIX m_mtxWorld;						// マトリックス
	static const char *m_pTextureName[];		// テクスチャーの名前
	void MakeVertex(LPDIRECT3DDEVICE9 pDevice);	// 頂点の設定
	void MakeIndex(LPDIRECT3DDEVICE9 pDevice);	// インデックスの設定
	void MakeVertexTop(LPDIRECT3DDEVICE9 pDevice);	// 
	void MakeIndexTop(LPDIRECT3DDEVICE9 pDevice);
	void TopDraw(LPDIRECT3DDEVICE9 pDevice);
};