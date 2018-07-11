#pragma once
//------------------------------------------------
// �`��ΏۃI�u�W�F�N�g�̏��� [scene.h]
//------------------------------------------------

//------------------------------------------------
// �C���N���[�h�t�@�C��
//------------------------------------------------
#include "main.h"
#include "manager.h"
//------------------------------------------------
// �}�N����`
//------------------------------------------------
#define	NUM_PRIORITY	(8)		// �`��D��x�g��

//------------------------------------------------
// �N���X
//------------------------------------------------
class CScene
{
public:
	// �I�u�W�F�N�g�^�C�v
	typedef enum
	{
		SCENE_TYPE_NONE = 0,
		SCENE_TYPE_2D,					// 2D�|���S��
		SCENE_TYPE_3D,					// 3D�|���S��
		SCENE_TYPE_X,					// X�t�@�C��
		SCENE_TYPE_BILLBOARD,			// �r���{�[�h
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
	// ���X�g�p
	static CScene *m_apTop[NUM_PRIORITY];	// ���X�g�̐擪�ʒu�ւ̃|�C���^
	static CScene *m_apCur[NUM_PRIORITY];	// ���X�g�̌��݈ʒu�ւ̃|�C���^
	CScene *m_pPrev;						// �O�̃I�u�W�F�ւ̃|�C���^
	CScene *m_pNext;						// ���̃I�u�W�F�ւ̃|�C���^

	int m_nPriority;						// �v���C�I���e�B�ԍ�

	SCENE_TYPE m_SceneType;						// �V�[���^�C�v
	OBJECT_TYPE m_ObjType;			// �I�u�W�F�N�g�^�C�v

	bool m_bDelete;
};