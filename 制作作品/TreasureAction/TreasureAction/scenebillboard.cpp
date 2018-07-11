//------------------------------------------------
// Billboard�I�u�W�F�N�g�̏��� [sceneBillboard.cpp]
//------------------------------------------------

//------------------------------------------------
//�C���N���[�h�t�@�C��
//------------------------------------------------
#include "sceneBillboard.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "mathlib.h"

//------------------------------------------------
// �}�N����`
//------------------------------------------------
#define	NUM_VERTEX			(4)		// ���_��
#define	NUM_POLYGON			(2)		// �|���S����

//------------------------------------------------
// �R���X�g���N�^
//------------------------------------------------
CSceneBillboard::CSceneBillboard(int nPriority, CScene::OBJECT_TYPE objType, CScene::SCENE_TYPE sceneType) : CScene(nPriority, objType, sceneType)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;

	m_pos = Vector3(0.0f, 0.0f, 0.0f);
	m_rot = Vector3(0.0f, 0.0f, 0.0f);

	m_nType = 0;
}

//------------------------------------------------
// �f�X�g���N�^
//------------------------------------------------
CSceneBillboard::~CSceneBillboard()
{
}

//------------------------------------------------
// ����������
//------------------------------------------------
HRESULT CSceneBillboard::Init(int nType, Vector3 pos, Vector3 rot, Vector2 textureSize)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �^�C�v��ݒ�
	m_nType = nType;

	// �|���S���̈ʒu��ݒ�
	m_pos = pos;

	// �|���S���̌�����ݒ�
	m_rot = rot;

	m_bEnable = true;

	m_bLighting = true;
	// �|���S���̑Ίp���̒�����ݒ�
	m_fLength = SetLength(textureSize.x, textureSize.y);
	// �|���S���̑Ίp���̊p�x��ݒ�
	m_fAngle = SetAngle(textureSize.x, textureSize.y);

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_BILLBOARD) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,					// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_BILLBOARD,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,					// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&m_pVtxBuff,						// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))								// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_BILLBOARD *pVtx;

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
		pVtx[0].nor = Vector3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = Vector3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = Vector3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = Vector3(0.0f, 0.0f, -1.0f);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = Vector2(0.0f, 0.0f);
		pVtx[1].tex = Vector2(1.0f, 0.0f);
		pVtx[2].tex = Vector2(0.0f, 1.0f);
		pVtx[3].tex = Vector2(1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		m_pVtxBuff->Unlock();
	}

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ���ʂ��J�����O
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Z�o�b�t�@���g�p
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h���s��
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��

																	// �T���v���[�X�e�[�g�p�����[�^�̐ݒ�
	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g�厞�̕�Ԑݒ�
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k�����̕�Ԑݒ�
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���t�l�̌J��Ԃ��ݒ�
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���u�l�̌J��Ԃ��ݒ�

	return S_OK;
}

//------------------------------------------------
// �I������
//------------------------------------------------
void CSceneBillboard::Uninit(void)
{
	// �e�N�X�`���̊J��
	if (m_pTexture)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (m_pVtxBuff)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//	// �I�u�W�F�N�g�����X�g����폜
	//	CScene::UnlinkList();
	// �I�u�W�F�N�g��j��
	Release();
}

//------------------------------------------------
// �X�V����
//------------------------------------------------
void CSceneBillboard::Update(void)
{
}

//------------------------------------------------
// �`�揈��
//------------------------------------------------
void CSceneBillboard::Draw(void)
{
	if (!m_bEnable)
		return;

	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxScale, mtxRot, mtxTranslate, mtxView;

	//���C�e�B���O���I�t�̏ꍇ���C�e�B���O��؂�
	if (!m_bLighting)
	{
		pDevice->SetRenderState(D3DRS_LIGHTING, false);
	}
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtxWorld);

		// �r���[�}�g���b�N�X���擾
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);
#if 1
		D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);
		m_mtxWorld._41 = 0.0f;
		m_mtxWorld._42 = 0.0f;
		m_mtxWorld._43 = 0.0f;
		//#else
		m_mtxWorld._11 = mtxView._11;
		m_mtxWorld._12 = mtxView._21;
		m_mtxWorld._13 = mtxView._31;
		m_mtxWorld._21 = mtxView._12;
		m_mtxWorld._22 = mtxView._22;
		m_mtxWorld._23 = mtxView._32;
		m_mtxWorld._31 = mtxView._13;
		m_mtxWorld._32 = mtxView._23;
		m_mtxWorld._33 = mtxView._33;
#endif

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		// ���_�o�b�t�@�������_�����O�p�C�v���C���ɐݒ�
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_BILLBOARD));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_BILLBOARD);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_pTexture);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}
	if (!m_bLighting)
	{
		pDevice->SetRenderState(D3DRS_LIGHTING, true);

	}
}


//------------------------------------------------
// �e�N�X�`�����W�ݒ�
//------------------------------------------------
void CSceneBillboard::SetTex(Vector2 tex0, Vector2 tex1, Vector2 tex2, Vector2 tex3)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_BILLBOARD *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = tex0;
		pVtx[1].tex = tex1;
		pVtx[2].tex = tex2;
		pVtx[3].tex = tex3;

		// ���_�f�[�^���A�����b�N����
		m_pVtxBuff->Unlock();
	}
}

//------------------------------------------------
// �e�N�X�`�����W�ݒ�
//------------------------------------------------
void CSceneBillboard::SetVtx(float fLength)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_BILLBOARD *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].pos.x = -sinf(m_fAngle) * fLength;
		pVtx[0].pos.y = cosf(m_fAngle) * fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = sinf(m_fAngle) * fLength;
		pVtx[1].pos.y = cosf(m_fAngle) * fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = -sinf(m_fAngle) * fLength;
		pVtx[2].pos.y = -cosf(m_fAngle) * fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = sinf(m_fAngle) * fLength;
		pVtx[3].pos.y = -cosf(m_fAngle) * fLength;
		pVtx[3].pos.z = 0.0f;

		// ���_�f�[�^���A�����b�N����
		m_pVtxBuff->Unlock();
	}
}

//------------------------------------------------
//�A���t�@�l�̐ݒ�
//------------------------------------------------
void CSceneBillboard::SetVertexAlpha(float fAlpha)
{
	VERTEX_BILLBOARD *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fAlpha);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fAlpha);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fAlpha);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fAlpha);

	m_pVtxBuff->Unlock();
}

//------------------------------------------------
//�F�̐ݒ�
//------------------------------------------------
void CSceneBillboard::SetVertexColor(D3DXCOLOR color)
{
	VERTEX_BILLBOARD *pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	pVtx[0].col =
		pVtx[1].col =
		pVtx[2].col =
		pVtx[3].col = color;

	m_pVtxBuff->Unlock();

}
//------------------------------------------------
//�e�N�X�`���[�ǂݍ���
//------------------------------------------------
void CSceneBillboard::LoadTexture(const char *pTextureName)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
		pTextureName,										// �t�@�C���̖��O
		&m_pTexture);										// �ǂݍ��ރ������[

}

//------------------------------------------------
//��]���W�̉��Z
//------------------------------------------------
void CSceneBillboard::AddRotation(Vector3 rot)
{
	m_rot += rot;
	if (m_rot.x > D3DX_PI)
	{
		m_rot.x -= D3DX_PI * 2.0f;
	}
	if (m_rot.x < -D3DX_PI)
	{
		m_rot.x += D3DX_PI * 2.0f;
	}
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}
	if (m_rot.z > D3DX_PI)
	{
		m_rot.z -= D3DX_PI * 2.0f;
	}
	if (m_rot.z < -D3DX_PI)
	{
		m_rot.z += D3DX_PI * 2.0f;
	}

}

//------------------------------------------------
//�ʒu���W�̐ݒ�
//------------------------------------------------
void CSceneBillboard::SetVertexPos(Vector3 RightUp, Vector3 RightDown, Vector3 LeftUp, Vector3 LeftDown)
{
	VERTEX_BILLBOARD *pVtx;
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