#pragma once
//------------------------------------------------
// ���b�V���h�[���̏���	[meshdome.h]
//------------------------------------------------

//------------------------------------------------
// �C���N���[�h�t�@�C��
//------------------------------------------------
#include "main.h"
#include "scene.h"

//------------------------------------------------
// ���b�V���h�[���N���X
//------------------------------------------------
class CMeshDome : public CScene
{
public:
	CMeshDome();
	~CMeshDome();

	static CMeshDome *Create(Vector3 pos,Vector3 rot,float fLength,float fRadius,int iPolygonX,int iPolygonY);
	HRESULT Init(Vector3 pos, Vector3 rot, float fLength, float fRadius, int iPolygonX, int iPolygonY);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	Vector3 GetPosition(void) { return m_pos; }
	void SetPosition(Vector3 pos) { m_pos = pos; }

	Vector3 GetRotation(void) { return m_rot; }
	void SetRotation(Vector3 rot) { m_rot = rot; }

	void LoadTexture(const char *pTexName);
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// ���_�o�b�t�@�[
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;			// �C���f�b�N�X�o�b�t�@�[
	LPDIRECT3DTEXTURE9 m_pTexture;				// �e�N�X�`���[
	LPDIRECT3DVERTEXBUFFER9 m_pVtxTop;
	LPDIRECT3DINDEXBUFFER9 m_pIndexTop;
	int m_iVertex_X;							// ���̒��_��
	int m_iVertex_Y;							// �c�̒��_��
	int m_iIdx;									// �C���f�b�N�X��
	int m_iVer;									// ���_��
	int m_iPoly;								// �|���S����
	float m_fRadius;							// ���a
	float m_fLength;							// ����
	Vector3 m_pos;								// �ʒu���W
	Vector3 m_rot;								// ��]���W
 	D3DXMATRIX m_mtxWorld;						// �}�g���b�N�X
	static const char *m_pTextureName[];		// �e�N�X�`���[�̖��O
	void MakeVertex(LPDIRECT3DDEVICE9 pDevice);	// ���_�̐ݒ�
	void MakeIndex(LPDIRECT3DDEVICE9 pDevice);	// �C���f�b�N�X�̐ݒ�
	void MakeVertexTop(LPDIRECT3DDEVICE9 pDevice);	// 
	void MakeIndexTop(LPDIRECT3DDEVICE9 pDevice);
	void TopDraw(LPDIRECT3DDEVICE9 pDevice);
};