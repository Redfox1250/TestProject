#pragma once
//------------------------------------------------
// ビルボードオブジェクトの処理 [sceneBillboard.h]
//------------------------------------------------

//------------------------------------------------
//インクルードファイル
//------------------------------------------------
#include "main.h"
#include "scene.h"

//------------------------------------------------
// マクロ定義
//------------------------------------------------
// 頂点フォーマット( 頂点座標 / 法線 / 頂点カラー / テクスチャ座標 )
#define	FVF_VERTEX_BILLBOARD	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//------------------------------------------------
// 構造体定義
//------------------------------------------------
// 上記頂点フォーマットに合わせた構造体を定義
typedef struct
{
	Vector3 pos;	// 頂点座標
	Vector3 nor;	// 法線
	D3DCOLOR col;		// 頂点カラー
	Vector2 tex;	// テクスチャ座標
} VERTEX_BILLBOARD;

//------------------------------------------------
// クラス
//------------------------------------------------
class CSceneBillboard : public CScene
{
public:
	CSceneBillboard(int nPriority = 4, CScene::OBJECT_TYPE objType = CScene::OBJECT_NONE, CScene::SCENE_TYPE SceneType = CScene::SCENE_TYPE_BILLBOARD);
	~CSceneBillboard();

	HRESULT Init(int nType, Vector3 pos, Vector3 rot, Vector2 textureSize);
	void Uninit(void);
	void Update(void);
	void Draw(void);


	void SetPosition(Vector3 pos) { m_pos = pos; }
	Vector3 GetPosition(void) { return m_pos; }
	void AddPostion(Vector3 Addpos) { m_pos += Addpos; }

	void SetRotation(Vector3 rot) { m_rot = rot; }
	Vector3 GetRotation(void) { return m_rot; }
	void AddRotation(Vector3 rot);

	void SetType(int nType) { m_nType = nType; }

	void SetVtx(float fLength);
	void SetVertexPos(Vector3 RightUp, Vector3 RightDown, Vector3 LeftUp, Vector3 LeftDown);
	void SetTex(Vector2 tex0, Vector2 tex1, Vector2 tex2, Vector2 tex3);
	void SetVertexAlpha(float fAlpha);
	void SetVertexColor(D3DXCOLOR color);
	void LoadTexture(const char *pTextureName);
	void SetEnable(bool bEnable) { m_bEnable = bEnable; }
	bool GetEnable(void) { return m_bEnable; }
	void SetLightMode(bool bLight) { m_bLighting = bLight; }
	bool GetLigntMode(void) { return m_bLighting; }

protected:
	LPDIRECT3DTEXTURE9 m_pTexture;			// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ

	D3DXMATRIX m_mtxWorld;					// ワールドマトリックス

	Vector3 m_pos;						// 位置
	Vector3 m_rot;						// 向き
	float m_fLength;						// 対角線の長さ
	float m_fAngle;							// 対角線の角度
	bool m_bEnable;
	int m_nType;							// 種類
	bool m_bLighting;						// ライティングするかどうか

};