//------------------------------------------------
// �e�̏���	[shadow.cpp]
//------------------------------------------------

//------------------------------------------------
// �C���N���[�h�t�@�C��
//------------------------------------------------
#include "shadow.h"
#include "manager.h"
#include "renderer.h"
#include "scene3D.h"

//------------------------------------------------
// �ÓI�ϐ�
//------------------------------------------------
const char *CShadow::pTextureName[] = 
{
	"data/texture/shadow.png",
};

//------------------------------------------------
// �R���X�g���N�^
//------------------------------------------------
CShadow::CShadow()
{
	m_pVtxBuff = NULL;
	m_pTexture = NULL;
	m_pIdxBuff = NULL;
}

//------------------------------------------------
// �f�X�g���N�^
//------------------------------------------------
CShadow::~CShadow()
{

}

//------------------------------------------------
// ����������
//------------------------------------------------
HRESULT CShadow::Init(Vector3 pos,Vector2 size)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	m_pos = pos;

	MakeVertex(pDevice);
	MakeIndex(pDevice);

	return S_OK;
}

//------------------------------------------------
// �I������
//------------------------------------------------
void CShadow::Uninit(void)
{
	SafeRelease(m_pVtxBuff);
	SafeRelease(m_pIdxBuff);
	SafeRelease(m_pTexture);
	Release();
}

//------------------------------------------------
// �X�V����
//------------------------------------------------
void CShadow::Update(void)
{

}

//------------------------------------------------
// �`�揈��
//------------------------------------------------
void CShadow::Draw(void)
{

}

//------------------------------------------------
// ���_���̐ݒ�
//------------------------------------------------
void CShadow::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D *pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	
	m_pVtxBuff->Unlock();
}

//------------------------------------------------
// �C���f�b�N�X���̐ݒ�
//------------------------------------------------
void CShadow::MakeIndex(LPDIRECT3DDEVICE9 pDevice)
{

}

//------------------------------------------------
// �e�N�X�`���[�̓ǂݍ���
//------------------------------------------------
void CShadow::LoadTexture(const char *pTexName)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXCreateTextureFromFile(pDevice,
		pTexName,
		&m_pTexture);
}

//------------------------------------------------
// �ʒu���W�̍X�V
//------------------------------------------------
void CShadow::LoadPosition(Vector3 pos)
{
	m_pos.x = pos.x;
	m_pos.y = 0.0f;
	m_pos.z = pos.z;

	// �I�u�W�F�N�g�Ɖe�̋���
	float fLength = pos.y - m_pos.y;

	
}