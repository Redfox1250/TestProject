#pragma once
//------------------------------------------------
// 描画対象オブジェクトの処理 [scene.h]
//------------------------------------------------

//------------------------------------------------
// インクルードファイル
//------------------------------------------------
#include "main.h"
#include "manager.h"
//------------------------------------------------
// マクロ定義
//------------------------------------------------
#define	NUM_PRIORITY	(8)		// 描画優先度枠数

//------------------------------------------------
// クラス
//------------------------------------------------
class CScene
{
public:
	// オブジェクトタイプ
	typedef enum
	{
		SCENE_TYPE_NONE = 0,
		SCENE_TYPE_2D,					// 2Dポリゴン
		SCENE_TYPE_3D,					// 3Dポリゴン
		SCENE_TYPE_X,					// Xファイル
		SCENE_TYPE_BILLBOARD,			// ビルボード
		SCENE_TYPE_FADE,
		SCENE_TYPE_MAX,
	} SCENE_TYPE;

	typedef enum
	{
		OBJECT_NONE = 0,
		OBJECT_BLOCK,
		OBJECT_PLAYER,
		OBJECT_GOAL,
		OBJECT_MOVEBLOCK,
		OBJECT_WALL,
		OBJECT_WHEEL,
		OBJECT_COIN,
		OBJECT_SWITCH,
		OBJECT_MAX,
	}OBJECT_TYPE;

	CScene(int nPriority = 3, OBJECT_TYPE objType = OBJECT_NONE, SCENE_TYPE SceneType = SCENE_TYPE_NONE);
	virtual ~CScene();

	virtual HRESULT Init(void) { return S_OK; }
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	void LinkList(int nPriority);
	void UnlinkList(void);
	void Release(void);

	static void UpdateAll(void);
	static void DrawAll(void);
	static void ReleaseAll(void);

	static void InitList(void);
	static void UninitList(void);

	virtual void SetPosition(Vector3 pos) = 0;
	virtual Vector3 GetPosition(void) = 0;

	virtual void SetRotation(Vector3 rot) = 0;
	virtual Vector3 GetRotation(void) = 0;

	virtual void SetMove(float x, float y, float z) {}
	virtual Vector3 GetMove(void) { return Vector3(0.0f, 0.0f, 0.0f); }

	void SetSceneType(SCENE_TYPE sceneType) { m_SceneType = sceneType; }
	SCENE_TYPE GetSceneType(void) { return m_SceneType; }

	void SetObjType(OBJECT_TYPE objType) { m_ObjType = objType; }
	OBJECT_TYPE GetObjType(void) { return m_ObjType; }

	static CScene *GetListTop(int nPriority = 3);
	CScene *GetNext() { return m_pNext; }

	virtual Vector3 GetPositionMin(void) { return Vector3(0.0f, 0.0f, 0.0f); }
	virtual Vector3 GetPositionMax(void) { return Vector3(0.0f, 0.0f, 0.0f); }

	void Listchange(int nPrinity);
private:
	// リスト用
	static CScene *m_apTop[NUM_PRIORITY];	// リストの先頭位置へのポインタ
	static CScene *m_apCur[NUM_PRIORITY];	// リストの現在位置へのポインタ
	CScene *m_pPrev;						// 前のオブジェへのポインタ
	CScene *m_pNext;						// 次のオブジェへのポインタ

	int m_nPriority;						// プライオリティ番号

	SCENE_TYPE m_SceneType;						// シーンタイプ
	OBJECT_TYPE m_ObjType;			// オブジェクトタイプ

	bool m_bDelete;
};