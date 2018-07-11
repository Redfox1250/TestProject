#pragma once
//------------------------------------------------
//2Dオブジェクトの処理	[scene2D.h]
//------------------------------------------------
 
//------------------------------------------------
//インクルードファイル
//------------------------------------------------
#include "main.h"
#include "scene.h"

//------------------------------------------------
//マクロ定義
//------------------------------------------------

//頂点フォーマット(頂点座標[2D] / 頂点カラー /  テクスチャ座標)
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define NUM_TEXTURE_MAX	(3)

//------------------------------------------------
//構造体定義
//------------------------------------------------
//上記頂点フォーマットに合わせた構造体を定義
typedef struct
{
	Vector3 pos;	//頂点座標
	float		rhw;	//座標変数用係数(1.0fで固定)
	D3DCOLOR	col;	//頂点カラー
	Vector2	tex;	//テクスチャ座標
}VERTEX_2D;

//------------------------------------------------
//2Dオブジェクトクラス
//------------------------------------------------
class CScene2D : public CScene
{
public:
	CScene2D(int nPriority = 6, CScene::OBJECT_TYPE = CScene::OBJECT_NONE, CScene::SCENE_TYPE objType = CScene::SCENE_TYPE_2D);
	~CScene2D();

	static CScene2D *Create(Vector3 pos, Vector3 rot, Vector2 polygonSize, const char *pFileName = "");

	HRESULT Init(Vector3 pos, Vector3 rot, Vector2 polygonSize, const char *pFileName);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(Vector3 pos);
	Vector3 GetPosition(void) { return m_pos; }

	void SetRotation(Vector3 rot) { m_rot = rot; }
	Vector3 GetRotation(void) { return m_rot; }
	void InitBack(const char* pFileName = "");
	void SetVertexPos(Vector3 vtx0, Vector3 vtx1, Vector3 vtx2, Vector3 vtx3);
	void SetVertexCol(D3DXCOLOR col);
	void SetVertexTex(Vector2 tex0, Vector2 tex1, Vector2 tex2, Vector2 tex3);
	void SetVertexAlpha(float fAlpha);
	D3DXCOLOR GetColor(void) { return m_Color; }
	void LoadTexture(const char *pTextureName);
	void SetLengthPos(float fLength);
	float GetLength(void) { return m_fLength; }
	bool GetbEnable(void) { return m_bEnable; }
	void SetEnable(bool bEnable) { m_bEnable = bEnable; }
	void AddPostion(Vector3 pos);
	void SetSize(Vector2 vSize);

protected:
	void SetVertexPos(void);
	void SetVertexTex(void);
	Vector2 m_posTex;
	LPDIRECT3DTEXTURE9 m_pTexture;			// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
	D3DXCOLOR m_Color;
	Vector3 m_pos;						// 位置標
	Vector3 m_rot;						// 向き
	float m_fLength;						// 対角線の長さ
	float m_fAngle;							// 対角線の傾き
	bool m_bEnable;

};
 