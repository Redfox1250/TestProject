#pragma once
//------------------------------------------------
// �G�f�B�^�[���[�h�̏���	[editor.h]
//------------------------------------------------

//------------------------------------------------
// �C���N���[�h�t�@�C��
//------------------------------------------------
#include "main.h"
#include "scene.h"

//------------------------------------------------
// �G�f�B�^�[�N���X
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
	static const char *m_pStageDataName[MAX_STAGE];	// �X�e�[�W�f�[�^�̃e�L�X�g��
	void LoadStage(int iStageNum);				// �X�e�[�W�̓ǂݍ���
	void WriteStage(int iStageNum);				// �X�e�[�W�̏�������
	
};