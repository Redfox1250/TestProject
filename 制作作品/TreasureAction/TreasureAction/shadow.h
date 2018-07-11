#pragma once
//------------------------------------------------
// �e�̏���	[shadow.h]
//------------------------------------------------

//------------------------------------------------
// �C���N���[�h�t�@�C��
//------------------------------------------------
#include "scene.h"
#include "main.h"

//------------------------------------------------
// �e�N���X
//------------------------------------------------
class CShadow : public CScene
{
public:
	CShadow();
	~CShadow();
	HRESULT Init(Vector3 pos, Vector2 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	Vector3 GetPosition(void) { return m_pos; }
	void SetPosition(Vector3 pos) { m_pos = pos; }
	void LoadPosition(Vector3 pos);

	Vector3 GetRotation(void) { return m_rot; }
	void SetRotation(Vector3 rot) { m_rot = rot; }

	void LoadTexture(const char *pTexName);

private:
	Vector3 m_pos;
	Vector3 m_rot;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�[
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	// �C���f�b�N�X�o�b�t�@�[
	LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`���[
	int m_iVertex_X;					// ���̒��_��
	int m_iVertex_Y;					// �c�̒��_��
	int m_iIdx;							// �C���f�b�N�X��
	int m_iVer;							// ���_��
	int m_iPoly;						// �|���S����

	static const char *pTextureName[];
	void MakeVertex(LPDIRECT3DDEVICE9 pDevice);
	void MakeIndex(LPDIRECT3DDEVICE9 pDevice);
};