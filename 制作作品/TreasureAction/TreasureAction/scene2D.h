#pragma once
//------------------------------------------------
//2D�I�u�W�F�N�g�̏���	[scene2D.h]
//------------------------------------------------
 
//------------------------------------------------
//�C���N���[�h�t�@�C��
//------------------------------------------------
#include "main.h"
#include "scene.h"

//------------------------------------------------
//�}�N����`
//------------------------------------------------

//���_�t�H�[�}�b�g(���_���W[2D] / ���_�J���[ /  �e�N�X�`�����W)
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define NUM_TEXTURE_MAX	(3)

//------------------------------------------------
//�\���̒�`
//------------------------------------------------
//��L���_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	Vector3 pos;	//���_���W
	float		rhw;	//���W�ϐ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR	col;	//���_�J���[
	Vector2	tex;	//�e�N�X�`�����W
}VERTEX_2D;

//------------------------------------------------
//2D�I�u�W�F�N�g�N���X
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
	LPDIRECT3DTEXTURE9 m_pTexture;			// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXCOLOR m_Color;
	Vector3 m_pos;						// �ʒu�W
	Vector3 m_rot;						// ����
	float m_fLength;						// �Ίp���̒���
	float m_fAngle;							// �Ίp���̌X��
	bool m_bEnable;

};
 