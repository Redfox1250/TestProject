#pragma once
//------------------------------------------------
//3D�I�u�W�F�N�g�̏���	[scene3D.h]
//------------------------------------------------

//------------------------------------------------
//�C���N���[�h�t�@�C��
//------------------------------------------------
#include "main.h"
#include "scene.h"

//------------------------------------------------
//�}�N����`
//------------------------------------------------
//���_�t�H�[�}�b�g(���_���W / �@�� / ���_�J���[ / �e�N�X�`�����W)
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//------------------------------------------------
//�\���̒�`
//------------------------------------------------
typedef struct
{
	Vector3 pos;	//���_���W
	Vector3 nor;	//�@��
	D3DCOLOR col;		//���_�J���[
	Vector2 tex;	//�e�N�X�`�����W
}VERTEX_3D;

//------------------------------------------------
//3D�I�u�W�F�N�g�N���X
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
	LPDIRECT3DTEXTURE9 m_pTexture;			// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^

	D3DXMATRIX m_mtxWorld;					// ���[���h�}�g���b�N�X

	Vector3 m_pos;						// �ʒu
	Vector3 m_rot;						// ����
	Vector2 m_Objsize;					// �傫��
	float m_fLength;						// �Ίp���̒���
	float m_fAngle;							// �Ίp���̊p�x

	D3DXCOLOR m_Color;						// ���_�J���[

	bool m_bEnable;							//�`��̐؂�ւ�
	static const char *m_apTextureName[];

};
