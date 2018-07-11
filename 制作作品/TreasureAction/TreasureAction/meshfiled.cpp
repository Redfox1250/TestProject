//------------------------------------------------
// ���b�V���t�B�[���h�̏���	[meshfiled.cpp]
//------------------------------------------------

//------------------------------------------------
// �C���N���[�h�t�@�C��
//------------------------------------------------
#include "meshfiled.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "verlib.h"

//------------------------------------------------
//�ÓI�ϐ�
//------------------------------------------------
const char *CMeshFiled::m_pTextureName[] =
{
	"data/texture/field004.jpg"
};

//------------------------------------------------
// �R���X�g���N�^
//------------------------------------------------
CMeshFiled::CMeshFiled()
{
	m_pIdxBuff = NULL;
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
}

//------------------------------------------------
// �f�X�g���N�^
//------------------------------------------------
CMeshFiled::~CMeshFiled()
{

}

//------------------------------------------------
// ����
//------------------------------------------------
CMeshFiled *CMeshFiled::Create(Vector3 pos, Vector3 rot, int iVertexX, int iVertexY, Vector2 size)
{
	CMeshFiled *pFiled = new CMeshFiled;
	pFiled->Init(pos, rot, iVertexX, iVertexY, size);

	return pFiled;
}

//------------------------------------------------
// ����������
//------------------------------------------------
HRESULT CMeshFiled::Init(Vector3 pos, Vector3 rot, int iVertexX, int iVertexY, Vector2 size)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	m_pos = pos - Vector3(size.x / 2.0f, 0.0f, size.y / 2.0f);
	m_rot = rot;
	m_Size = size;
	LoadTexture(m_pTextureName[0]);


	VertexNumSet(m_iIdx, m_iVer, m_iPoly, iVertexX, iVertexY);

	m_iVertex_X = iVertexX;
	m_iVertex_Y = iVertexY;
	MakeVertex(pDevice);
	MakeIndex(pDevice);

	return S_OK;
}

//------------------------------------------------
// �I������
//------------------------------------------------
void CMeshFiled::Uninit(void)
{
	SafeRelease(m_pIdxBuff);
	SafeRelease(m_pTexture);
	SafeRelease(m_pVtxBuff);
	Release();
}

//------------------------------------------------
// �X�V����
//------------------------------------------------
void CMeshFiled::Update(void)
{

}

//------------------------------------------------
// �`�揈��
//------------------------------------------------
void CMeshFiled::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxrot, mtxtrans;

   	{
		D3DXMatrixIdentity(&m_mtxWorld);

		// ��]�̔��f
		D3DXMatrixRotationYawPitchRoll(&mtxrot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxrot);

		// �ʒu�̔��f
		D3DXMatrixTranslation(&mtxtrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxtrans);

		// ���[���h�}�g���b�N�X�̏�����
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0,
			m_pVtxBuff,
			0,
			sizeof(VERTEX_3D));

		//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetIndices(m_pIdxBuff);

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_pTexture);

		//�|���S���̕`��
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
			0,
			0,
			m_iVer,
			0,
			m_iPoly);
	}
}

//------------------------------------------------
// ���_���̐ݒ�
//------------------------------------------------
void CMeshFiled::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_iVer,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D *pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int iCntY = 0; iCntY < m_iVertex_Y + 1; iCntY++)
	{
		for (int iCntX = 0; iCntX < m_iVertex_X + 1; iCntX++)
		{
			float iX = (float)iCntX / (m_iVertex_X);
			float iY = ((float)m_iVertex_Y - iCntY) / (m_iVertex_Y);

			pVtx[0].pos = Vector3(iX * m_Size.x, 0.0f, iY * m_Size.y);
			pVtx[0].nor = Vector3(0.0f, 1.0f, 0.0f);
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[0].tex = Vector2((float)iCntX, (float)iCntY);
			pVtx++;
		}
	}
	m_pVtxBuff->Unlock();
}

//------------------------------------------------
// �C���f�b�N�X���̐ݒ�
//------------------------------------------------
void CMeshFiled::MakeIndex(LPDIRECT3DDEVICE9 pDevice)
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

//------------------------------------------------
// �e�N�X�`���[�̓ǂݍ���
//------------------------------------------------
void CMeshFiled::LoadTexture(const char *pTexName)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXCreateTextureFromFile(pDevice,
		pTexName,
		&m_pTexture);
}