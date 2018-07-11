//------------------------------------------------
//�����̂̏���	[objectsphere.cpp]
//------------------------------------------------

//------------------------------------------------
// �C���N���[�h�t�@�C��
//------------------------------------------------
#include "meshdome.h"
#include "renderer.h"
#include "manager.h"
#include "verlib.h"
#include "scene3D.h"

const char *CMeshDome::m_pTextureName[] = 
{
	"data/texture/sky000.jpg",
};
//------------------------------------------------
// �R���X�g���N�^
//------------------------------------------------
CMeshDome::CMeshDome()
{
	m_pVtxBuff = NULL;
	m_pTexture = NULL;
	m_pIdxBuff = NULL;
	m_pVtxTop = NULL;
	m_pIndexTop = NULL;
}

//------------------------------------------------
// �f�X�g���N�^
//------------------------------------------------
CMeshDome::~CMeshDome()
{

}

//------------------------------------------------
// ����
//------------------------------------------------
CMeshDome *CMeshDome::Create(Vector3 pos, Vector3 rot, float fLength, float fRadius, int iPolygonX, int iPolygonY)
{
	CMeshDome *pDome = new CMeshDome;
	pDome->Init(pos, rot, fLength, fRadius, iPolygonX, iPolygonY);

	return pDome;
}

//------------------------------------------------
// ����������
//------------------------------------------------
HRESULT CMeshDome::Init(Vector3 pos, Vector3 rot, float fLength, float fRadius, int iPolygonX, int iPolygonY)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �ʒu��ݒ�
	m_pos = pos;

	// ������ݒ�
	m_rot = rot;

	// ���a��ݒ�
	m_fRadius = fRadius;

	// �����̐ݒ�
	m_fLength = fLength;

	// ���_���̐ݒ�
	m_iVertex_X = iPolygonX;
	m_iVertex_Y = iPolygonY;

	// ���b�V���̊e���̐ݒ�
	VertexNumSet(m_iIdx, m_iVer, m_iPoly, iPolygonX, iPolygonY);

	LoadTexture(m_pTextureName[0]);

	MakeVertex(pDevice);
	MakeIndex(pDevice);
	MakeVertexTop(pDevice);
	MakeIndexTop(pDevice);
	return S_OK;
}

//------------------------------------------------
// �I������
//------------------------------------------------
void CMeshDome::Uninit(void)
{
	SafeRelease(m_pIdxBuff);
	SafeRelease(m_pVtxBuff);
	SafeRelease(m_pTexture);
	Release();
}

//------------------------------------------------
// �X�V����
//------------------------------------------------
void CMeshDome::Update(void)
{

}

//------------------------------------------------
// �`�揈��
//------------------------------------------------
void CMeshDome::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;

	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0,
			m_pVtxBuff,
			0,
			sizeof(VERTEX_3D));

		// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetIndices(m_pIdxBuff);

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// �e�N�X�`���̓ǂݍ���
		pDevice->SetTexture(0, m_pTexture);

		// �|���S���̕`��
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
			0,
			0,
			m_iVer,
			0,
			m_iPoly);
	}
	TopDraw(pDevice);
}

//------------------------------------------------
// ���_���̐ݒ�
//------------------------------------------------
void CMeshDome::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*m_iVer,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// ���_�o�b�t�@�𐶐�
	VERTEX_3D *pVtx;

	// ���_����ݒ�
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	for (int iCntV = 0; iCntV <= m_iVertex_Y; iCntV++)
	{
		for (int iCntH = 0; iCntH <= m_iVertex_X; iCntH++)
		{
			float fAngle = -D3DX_PI * 2.0f * ((float)iCntH / m_iVertex_X - 1);
			float fAngleH = (float)iCntV / (float)(m_iVertex_Y - 1);

			float fRadius = cosf(fAngleH)*m_fLength;

			pVtx[0].pos.x = sinf(fAngle)*fRadius;
			pVtx[0].pos.y = sinf(fAngleH)*m_fLength;
			pVtx[0].pos.z = cosf(fAngle)*fRadius;

			pVtx[0].nor = Vector3(1.0f, 1.0f, 1.0f);
			pVtx[0].col = colorNS::WHITE;
			pVtx[0].tex = Vector2((float)iCntH / m_iVertex_X, ((float)(m_iVertex_Y - iCntV) / (m_iVertex_Y + 2)) + 0.01f);
			pVtx++;
		}
	}
	m_pVtxBuff->Unlock();
}

//------------------------------------------------
// �C���f�b�N�X���̐ݒ�
//------------------------------------------------
void CMeshDome::MakeIndex(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->CreateIndexBuffer(sizeof(WORD)*m_iIdx,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	WORD *pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
	IndexSet(pIdx, m_iVertex_X, m_iVertex_Y);
	m_pIdxBuff->Unlock();
}

void CMeshDome::MakeVertexTop(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (m_iVertex_X + 1),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxTop,
		NULL);

	VERTEX_3D *pVtx;
	m_pVtxTop->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[0].pos.x = 0.0f;
	pVtx[0].pos.y = m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[0].nor = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[0].tex = D3DXVECTOR2(0.5f, 0.003f);		

	for (int iCntVertex = 0; iCntVertex < m_iVertex_X; iCntVertex++)
	{
		pVtx++;
		float fAngle = -D3DX_PI * 2.0f * ((float)iCntVertex / (m_iVertex_X));
		float fAngleH = ((float)m_iVertex_Y / (m_iVertex_Y - 1));

		float fRadius = cosf(fAngleH)*m_fLength;

		pVtx[0].pos.x = sinf(fAngle)*fRadius;
		pVtx[0].pos.y = sinf(fAngleH)*m_fLength;
		pVtx[0].pos.z = cosf(fAngle)*fRadius;

		pVtx[0].nor = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.01f);
	}
	m_pVtxTop->Unlock();
}
void CMeshDome::MakeIndexTop(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->CreateIndexBuffer(sizeof(WORD) * (m_iVertex_X + 2),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIndexTop,
		NULL);

	WORD *pIdx;
	m_pIndexTop->Lock(0, 0, (void**)&pIdx, 0);
	for (int i = 0; i <= m_iVertex_X; i++)
	{
		pIdx[i] = i;
	}
	pIdx[m_iVertex_X + 1] = 1;
	pIdx[m_iVertex_X + 2] = 0;
	m_pIndexTop->Unlock();
}
void CMeshDome::TopDraw(LPDIRECT3DDEVICE9 pDevice)
{
	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X�̐ݒ�
	D3DXMatrixIdentity(&m_mtxWorld);

	//��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0,
		m_pVtxTop,
		0,
		sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIndexTop);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLEFAN,
		0,
		0,
		m_iVertex_X + 1,
		0,
		m_iVertex_X);
}

//------------------------------------------------
// �e�N�X�`���[�̓ǂݍ���
//------------------------------------------------
void CMeshDome::LoadTexture(const char *pTexName)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXCreateTextureFromFile(pDevice,
		pTexName,
		&m_pTexture);
}