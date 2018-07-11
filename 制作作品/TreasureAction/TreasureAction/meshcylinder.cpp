//------------------------------------------------
// メッシュシリンダーの処理	[meshcylinder.cpp]
//------------------------------------------------

//------------------------------------------------
// インクルードファイル
//------------------------------------------------
#include "meshcylinder.h"
#include "manager.h"
#include "renderer.h"
#include "scene3D.h"
#include "verlib.h"

//------------------------------------------------
// 静的変数
//------------------------------------------------
const char *CMeshCylinder::m_pTextureName[] =
{
	"data/texture/field004.jpg",
	"data/texture/mesh000.jpg"
};

//------------------------------------------------
// コンストラクタ
//------------------------------------------------
CMeshCylinder::CMeshCylinder()
{
	m_pIdxBuff = NULL;
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
}

//------------------------------------------------
// デストラクタ
//------------------------------------------------
CMeshCylinder::~CMeshCylinder()
{

}

//------------------------------------------------
// 生成
//------------------------------------------------
CMeshCylinder *CMeshCylinder::Create(Vector3 pos, Vector3 rot, int iVertexX, int iVertexY, float fLength, float fRadius)
{
	CMeshCylinder *pObj = new CMeshCylinder;
	pObj->Init(pos, rot, iVertexX, iVertexY, fLength,fRadius);

	return pObj;
}

//------------------------------------------------
// 初期化処理
//------------------------------------------------
HRESULT CMeshCylinder::Init(Vector3 pos, Vector3 rot, int iVertexX, int iVertexY, float fLength, float fRadius)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	m_pos = pos;
	m_rot = rot;
	m_fRadius = fRadius;
	m_fLength = fLength;
	
	m_iVertex_X = iVertexX;
	m_iVertex_Y = iVertexY;

	VertexNumSet(m_iIdx, m_iVer, m_iPoly, iVertexX, iVertexY);
	
	MakeVertex(pDevice);
	MakeIndex(pDevice);

	LoadTexture(m_pTextureName[0]);
	return S_OK;
}

//------------------------------------------------
// 終了処理
//------------------------------------------------
void CMeshCylinder::Uninit(void)
{
	SafeRelease(m_pIdxBuff);
	SafeRelease(m_pTexture);
	SafeRelease(m_pVtxBuff);
	Release();
}

//------------------------------------------------
// 更新処理
//------------------------------------------------
void CMeshCylinder::Update(void)
{

}

//------------------------------------------------
// 描画処理
//------------------------------------------------
void CMeshCylinder::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxrot, mtxtrans;
 
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	{
		D3DXMatrixIdentity(&m_mtxWorld);

		// 回転の反映
		D3DXMatrixRotationYawPitchRoll(&mtxrot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxrot);

		// 位置の反映
		D3DXMatrixTranslation(&mtxtrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxtrans);

		// ワールドマトリックスの初期化
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		// 頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0,
			m_pVtxBuff,
			0,
			sizeof(VERTEX_3D));

		//インデックスバッファをデータストリームに設定
		pDevice->SetIndices(m_pIdxBuff);

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//テクスチャの設定
		pDevice->SetTexture(0, m_pTexture);

		//ポリゴンの描画
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
			0,
			0,
			m_iVer,
			0,
			m_iPoly);
	}
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

}

//------------------------------------------------
// 頂点情報の設定
//------------------------------------------------
void CMeshCylinder::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_iVer,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D *pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int iCntV = 0; iCntV < m_iVertex_Y + 1; iCntV++)
	{
		for (int iCntH = 0; iCntH < m_iVertex_X + 1; iCntH++)
		{
			float fAngle = D3DX_PI * 2.0f * ((float)iCntH / m_iVertex_X);
			float fHight = m_fLength * ((float)iCntV / m_iVertex_Y);
 
			pVtx[0].pos.x = sinf(fAngle)*m_fRadius;
			pVtx[0].pos.y = fHight;
			pVtx[0].pos.z = cosf(fAngle)*m_fRadius;

			pVtx[0].nor = Vector3(0.0f, 1.0f, 0.0f);
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[0].tex = Vector2((float)iCntH, (float)iCntV);
			pVtx++;
		}
	}
	m_pVtxBuff->Unlock();

}

//------------------------------------------------
// インデックス情報の設定
//------------------------------------------------
void CMeshCylinder::MakeIndex(LPDIRECT3DDEVICE9 pDevice)
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
//	テクスチャーの読み込み
//------------------------------------------------
void CMeshCylinder::LoadTexture(const char *pTexName)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXCreateTextureFromFile(pDevice,
		pTexName,
		&m_pTexture);
}