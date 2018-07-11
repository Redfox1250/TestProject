#pragma once
//------------------------------------------------
// メッシュブロックの処理	[meshblock.h]
//------------------------------------------------

//------------------------------------------------
// インクルードファイル
//------------------------------------------------
#include "main.h"
#include "scene.h"

//------------------------------------------------
// メッシュブロッククラス
//------------------------------------------------
class CMeshBlock : public CScene
{
public:
	CMeshBlock();
	~CMeshBlock();
	CMeshBlock *Create();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	Vector3 GetPosition(void) { return m_pos; }
	void SetPosition(Vector3 pos) { m_pos = pos; }

	Vector3 GetRotation(void) { return m_rot; }
	void SetRotation(Vector3 rot) { m_rot = rot; }

	void LoadTexture(const char *pTextureName);
private:
	Vector3 m_pos;
	Vector3 m_rot;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;
	D3DXMATRIX m_mtxWorld;
	static const char *m_pTextureName[];
	void MakeVertex(LPDIRECT3DDEVICE9 pDevice);
	void MakeIndex(LPDIRECT3DDEVICE9 pDevice);	
};