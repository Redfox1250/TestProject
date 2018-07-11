#pragma once
//------------------------------------------------
// ���b�V���t�B�[���h�̏���	[meshfiled.h]
//------------------------------------------------

//------------------------------------------------
// �C���N���[�h�t�@�C��
//------------------------------------------------
#include "scene3D.h"

//------------------------------------------------
// ���b�V���t�B�[���h�N���X
//------------------------------------------------
class CMeshFiled : public CScene
{
public:
	CMeshFiled();
	~CMeshFiled();
	static CMeshFiled *Create(Vector3 pos, Vector3 rot, int iVertexX, int iVertexY, Vector2 size);
	HRESULT Init(Vector3 pos,Vector3 rot,int iVertexX,int iVertexY,Vector2 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	Vector3 GetPosition(void) { return m_pos; }
	void SetPosition(Vector3 pos) { m_pos = pos; }

	Vector3 GetRotation(void) { return m_rot; }
	void SetRotation(Vector3 rot) { m_rot = rot; }

	void LoadTexture(const char *pTexName);
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�[
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	// �C���f�b�N�X�o�b�t�@�[
	LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`���[
	int m_iVertex_X;					// ���̒��_��
	int m_iVertex_Y;					// �c�̒��_��
	int m_iIdx;							// �C���f�b�N�X��
	int m_iVer;							// ���_��
	int m_iPoly;						// �|���S����
	Vector3 m_pos;					// �ʒu���W
	Vector3 m_rot;					// ��]���W
	Vector2 m_Size;					// �傫��
	D3DXMATRIX m_mtxWorld;				// �}�g���b�N�X
	static const char *m_pTextureName[];	// �e�N�X�`���[�̖��O
	void MakeVertex(LPDIRECT3DDEVICE9 pDevice);	// ���_�̐ݒ�
	void MakeIndex(LPDIRECT3DDEVICE9 pDevice);	// �C���f�b�N�X�̐ݒ�
	
};