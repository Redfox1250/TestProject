//------------------------------------------------
//半球体の処理	[objectsphere.cpp]
//------------------------------------------------

//------------------------------------------------
// インクルードファイル
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
// コンストラクタ
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
// デストラクタ
//------------------------------------------------
CMeshDome::~CMeshDome()
{

}

//------------------------------------------------
// 生成
//------------------------------------------------
CMeshDome *CMeshDome::Create(Vector3 pos, Vector3 rot, float fLength, float fRadius, int iPolygonX, int iPolygonY)
{
	CMeshDome *pDome = new CMeshDome;
	pDome->Init(pos, rot, fLength, fRadius, iPolygonX, iPolygonY);

	return pDome;
}

//------------------------------------------------
// 初期化処理
//------------------------------------------------
HRESULT CMeshDome::Init(Vector3 pos, Vector3 rot, float fLength, float fRadius, int iPolygonX, int iPolygonY)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 位置を設定
	m_pos = pos;

	// 向きを設定
	m_rot = rot;

	// 半径を設定
	m_fRadius = fRadius;

	// 長さの設定
	m_fLength = fLength;

	// 頂点数の設定
	m_iVertex_X = iPolygonX;
	m_iVertex_Y = iPolygonY;

	// メッシュの各情報の設定
	VertexNumSet(m_iIdx, m_iVer, m_iPoly, iPolygonX, iPolygonY);

	LoadTexture(m_pTextureName[0]);

	MakeVertex(pDevice);
	MakeIndex(pDevice);
	MakeVertexTop(pDevice);
	MakeIndexTop(pDevice);
	return S_OK;
}

//------------------------------------------------
// 終了処理
//------------------------------------------------
void CMeshDome::Uninit(void)
{
	SafeRelease(m_pIdxBuff);
	SafeRelease(m_pVtxBuff);
	SafeRelease(m_pTexture);
	Release();
}

//------------------------------------------------
// 更新処理
//------------------------------------------------
void CMeshDome::Update(void)
{

}

//------------------------------------------------
// 描画処理
//------------------------------------------------
void CMeshDome::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;

	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&m_mtxWorld);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		// 頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0,
			m_pVtxBuff,
			0,
			sizeof(VERTEX_3D));

		// インデックスバッファをデータストリームに設定
		pDevice->SetIndices(m_pIdxBuff);

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		// テクスチャの読み込み
		pDevice->SetTexture(0, m_pTexture);

		// ポリゴンの描画
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
// 頂点情報の設定
//------------------------------------------------
void CMeshDome::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*m_iVer,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// 頂点バッファを生成
	VERTEX_3D *pVtx;

	// 頂点情報を設定
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
// インデックス情報の設定
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

	//ワールドマトリックスの設定
	D3DXMatrixIdentity(&m_mtxWorld);

	//回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0,
		m_pVtxTop,
		0,
		sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIndexTop);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLEFAN,
		0,
		0,
		m_iVertex_X + 1,
		0,
		m_iVertex_X);
}

//------------------------------------------------
// テクスチャーの読み込み
//------------------------------------------------
void CMeshDome::LoadTexture(const char *pTexName)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXCreateTextureFromFile(pDevice,
		pTexName,
		&m_pTexture);
}