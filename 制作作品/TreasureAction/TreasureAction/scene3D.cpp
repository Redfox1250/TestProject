//------------------------------------------------
// 3D�I�u�W�F�N�g�̏��� [scene3D.cpp]
//------------------------------------------------

//------------------------------------------------
//�C���N���[�h�t�@�C��
//------------------------------------------------
#include "scene3D.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "mathlib.h"

//------------------------------------------------
// �}�N����`
//------------------------------------------------
#define	NUM_VERTEX		(4)		// ���_��
#define	NUM_POLYGON		(2)		// �|���S���� 

//------------------------------------------------
// �ÓI�ϐ�
//------------------------------------------------
const char *CScene3D::m_apTextureName[] =
{
	"",
};

//------------------------------------------------
// CScene3D����
//------------------------------------------------
CScene3D *CScene3D::Create(Vector3 pos, Vector3 rot, Vector2 ObjSize)
{
	CScene3D *pScene3D;

	pScene3D = new CScene3D;
	pScene3D->Init(pos, rot, ObjSize);

	return pScene3D;
}

//------------------------------------------------
// �R���X�g���N�^
//------------------------------------------------
CScene3D::CScene3D(int nPriority, CScene::OBJECT_TYPE objtype, CScene::SCENE_TYPE SceneType) : CScene(nPriority, objtype, SceneType)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
}

//------------------------------------------------
// CScene3D�f�X�g���N�^
//------------------------------------------------
CScene3D::~CScene3D()
{
}

//------------------------------------------------
// ����������
//------------------------------------------------
HRESULT CScene3D::Init(Vector3 pos, Vector3 rot, Vector2 Objsize)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// �ʒu��ݒ�
	m_pos = pos;

	// ������ݒ�
	m_rot = rot;

	// �g��ݒ�
	m_Objsize = Objsize;

	//�`��̐ݒ�
	m_bEnable = true;

	//�J���[�̐ݒ�
	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �Ίp���̒����E�p�x��ݒ�
	m_fLength = SetLength(Objsize.x, Objsize.y);
	m_fAngle = SetAngle(Objsize.x, Objsize.y);

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&m_pVtxBuff,				// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].pos.x = -sinf(m_fAngle) * m_fLength;
		pVtx[0].pos.y = cosf(m_fAngle) * m_fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = sinf(m_fAngle) * m_fLength;
		pVtx[1].pos.y = cosf(m_fAngle) * m_fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = -sinf(m_fAngle) * m_fLength;
		pVtx[2].pos.y = -cosf(m_fAngle) * m_fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = sinf(m_fAngle) * m_fLength;
		pVtx[3].pos.y = -cosf(m_fAngle) * m_fLength;
		pVtx[3].pos.z = 0.0f;

		// �@���̐ݒ�
		pVtx[0].nor = Vector3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = Vector3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = Vector3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = Vector3(0.0f, 1.0f, 0.0f);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = m_Color;
		pVtx[1].col = m_Color;
		pVtx[2].col = m_Color;
		pVtx[3].col = m_Color;

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = Vector2(0.0f, 0.0f);
		pVtx[1].tex = Vector2(1.0f, 0.0f);
		pVtx[2].tex = Vector2(0.0f, 1.0f);
		pVtx[3].tex = Vector2(1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		m_pVtxBuff->Unlock();
	}
	return S_OK;
}

//------------------------------------------------
// �I������
//------------------------------------------------
void CScene3D::Uninit(void)
{
	// �e�N�X�`���̊J��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �I�u�W�F�N�g�����X�g����폜
	//	CScene::UnlinkList();

	// �I�u�W�F�N�g��j��
	Release();
}

//------------------------------------------------
// �X�V����
//------------------------------------------------
void CScene3D::Update(void)
{
}

//------------------------------------------------
// �`�揈��
//------------------------------------------------
void CScene3D::Draw(void)
{
	if (!m_bEnable)
		return;

	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxScale, mtxRot, mtxTranslate;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//// �g�k�𔽉f
	//D3DXMatrixScaling(&mtxScale, m_size.x, m_size.y, m_size.z);
	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//------------------------------------------------
//�e�N�X�`���[�̓ǂݍ���
//------------------------------------------------
void CScene3D::LoadTexture(const char *TextureName)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// �^�C�v��ݒ�

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
		TextureName,		// �t�@�C���̖��O
		&m_pTexture);				// �ǂݍ��ރ������[

}

//------------------------------------------------
//���_�̈ʒu���W�̐ݒ�
//------------------------------------------------
void CScene3D::SetVertexPos(Vector3 RightUp, Vector3 RightDown, Vector3 LeftUp, Vector3 LeftDown)
{
	VERTEX_3D *pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//pVtx[0].pos = RightUp;
	//pVtx[1].pos = LeftUp;
	//pVtx[2].pos = RightDown;
	//pVtx[3].pos = LeftDown;

	pVtx[0].pos = LeftUp;
	pVtx[1].pos = RightUp;
	pVtx[2].pos = LeftDown;
	pVtx[3].pos = RightDown;

	m_pVtxBuff->Unlock();

}

//------------------------------------------------
//���_�̐F�̐ݒ�
//------------------------------------------------
void CScene3D::SetVertexColor(D3DXCOLOR color)
{
	m_Color = color;

	if (m_Color.r > 1.0f)
	{
		m_Color.r = 1.0f;
	}
	if (m_Color.r < 0.0f)
	{
		m_Color.r = 0.0f;
	}

	if (m_Color.g > 1.0f)
	{
		m_Color.g = 1.0f;
	}
	if (m_Color.g < 0.0f)
	{
		m_Color.g = 0.0f;
	}

	if (m_Color.b > 1.0f)
	{
		m_Color.b = 1.0f;
	}
	if (m_Color.b < 0.0f)
	{
		m_Color.b = 0.0f;
	}

	if (m_Color.a > 1.0f)
	{
		m_Color.a = 1.0f;
	}
	if (m_Color.a < 0.0f)
	{
		m_Color.a = 0.0f;
	}

	VERTEX_3D *pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = m_Color;
	pVtx[1].col = m_Color;
	pVtx[2].col = m_Color;
	pVtx[3].col = m_Color;

	m_pVtxBuff->Unlock();

}

//------------------------------------------------
//���_�̃A���t�@�l�̐ݒ�
//------------------------------------------------
void CScene3D::SetVertexAlpha(float fAlpha)
{
	m_Color.a = fAlpha;

	if (m_Color.a > 1.0f)
	{
		m_Color.a = 1.0f;
	}
	if (m_Color.a < 0.0f)
	{
		m_Color.a = 0.0f;
	}

	VERTEX_3D *pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = m_Color;
	pVtx[1].col = m_Color;
	pVtx[2].col = m_Color;
	pVtx[3].col = m_Color;

	m_pVtxBuff->Unlock();

}

//------------------------------------------------
//���_��uv�l�̐ݒ�
//------------------------------------------------
void CScene3D::SetVertexTexture(Vector2 tex0, Vector2 tex1, Vector2 tex2, Vector2 tex3)
{
	VERTEX_3D *pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	pVtx[0].tex = tex0;
	pVtx[1].tex = tex1;
	pVtx[2].tex = tex2;
	pVtx[3].tex = tex3;

	m_pVtxBuff->Unlock();
}