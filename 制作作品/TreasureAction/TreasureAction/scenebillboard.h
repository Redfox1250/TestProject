#pragma once
//------------------------------------------------
// �r���{�[�h�I�u�W�F�N�g�̏��� [sceneBillboard.h]
//------------------------------------------------

//------------------------------------------------
//�C���N���[�h�t�@�C��
//------------------------------------------------
#include "main.h"
#include "scene.h"

//------------------------------------------------
// �}�N����`
//------------------------------------------------
// ���_�t�H�[�}�b�g( ���_���W / �@�� / ���_�J���[ / �e�N�X�`�����W )
#define	FVF_VERTEX_BILLBOARD	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//------------------------------------------------
// �\���̒�`
//------------------------------------------------
// ��L���_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	Vector3 pos;	// ���_���W
	Vector3 nor;	// �@��
	D3DCOLOR col;		// ���_�J���[
	Vector2 tex;	// �e�N�X�`�����W
} VERTEX_BILLBOARD;

//------------------------------------------------
// �N���X
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
	LPDIRECT3DTEXTURE9 m_pTexture;			// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^

	D3DXMATRIX m_mtxWorld;					// ���[���h�}�g���b�N�X

	Vector3 m_pos;						// �ʒu
	Vector3 m_rot;						// ����
	float m_fLength;						// �Ίp���̒���
	float m_fAngle;							// �Ίp���̊p�x
	bool m_bEnable;
	int m_nType;							// ���
	bool m_bLighting;						// ���C�e�B���O���邩�ǂ���

};