#pragma once
//------------------------------------------------
//3Dオブジェクトの処理	[scene3D.h]
//------------------------------------------------

//------------------------------------------------
//インクルードファイル
//------------------------------------------------
#include "main.h"
#include "scene.h"

//------------------------------------------------
//マクロ定義
//------------------------------------------------
//頂点フォーマット(頂点座標 / 法線 / 頂点カラー / テクスチャ座標)
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//------------------------------------------------
//構造体定義
//------------------------------------------------
typedef struct
{
	Vector3 pos;	//頂点座標
	Vector3 nor;	//法線
	D3DCOLOR col;		//頂点カラー
	Vector2 tex;	//テクスチャ座標
}VERTEX_3D;

//------------------------------------------------
//3Dオブジェクトクラス
//------------------------------------------------
class CScene3D : public CScene
{
public:
	CScene3D(int nPriority = 3, CScene::OBJECT_TYPE objType = CScene::OBJECT_NONE, CScene::SCENE_TYPE SCenetype = CScene::SCENE_TYPE_3D);
	~CScene3D();

	static CScene3D *Create(Vector3 pos, Vector3 rot, Vector2 ObjSize);

	HRESULT Init(Vector3 pos, Vector3 rot, Vector2 ObjSize);
	HRESULT Init(void) { return S_OK; }
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(Vector3 pos) { m_pos = pos; }
	Vector3 GetPosition(void) { return m_pos; }

	void SetRotation(Vector3 rot) { m_rot = rot; }
	Vector3 GetRotation(void) { return m_rot; }
	void LoadTexture(const char *TextureName);
	//void SetType(int nType) { m_nType = nType; }

	void SetVertexPos(Vector3 RightUp, Vector3 RightDown, Vector3 LeftUp, Vector3 LeftDown);
	void SetEnable(bool bEnable) { m_bEnable = bEnable; }
	bool GetEnable(void) { return m_bEnable; }

	D3DXCOLOR GetColor(void) { return m_Color; }
	void SetVertexColor(D3DXCOLOR color);
	void SetVertexAlpha(float fAlpha);
	void SetVertexTexture(Vector2 RightUp, Vector2 RightDown, Vector2 LeftUp, Vector2 LeftDown);
protected:
	LPDIRECT3DTEXTURE9 m_pTexture;			// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ

	D3DXMATRIX m_mtxWorld;					// ワールドマトリックス

	Vector3 m_pos;						// 位置
	Vector3 m_rot;						// 向き
	Vector2 m_Objsize;					// 大きさ
	float m_fLength;						// 対角線の長さ
	float m_fAngle;							// 対角線の角度

	D3DXCOLOR m_Color;						// 頂点カラー

	bool m_bEnable;							//描画の切り替え
	static const char *m_apTextureName[];

};
