#pragma once
//------------------------------------------------
// エディターモードの処理	[editor.h]
//------------------------------------------------

//------------------------------------------------
// インクルードファイル
//------------------------------------------------
#include "main.h"
#include "scene.h"

//------------------------------------------------
// エディタークラス
//------------------------------------------------
class CEditor : public CScene
{
public:
	CEditor();
	~CEditor();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	Vector3 GetPosition(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	void SetPosition(Vector3 pos) { }

	Vector3 GetRotation(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	void SetRotation(Vector3 rot) { }

private:
	static const char *m_pStageDataName[MAX_STAGE];	// ステージデータのテキスト名
	void LoadStage(int iStageNum);				// ステージの読み込み
	void WriteStage(int iStageNum);				// ステージの書き込み
	
};