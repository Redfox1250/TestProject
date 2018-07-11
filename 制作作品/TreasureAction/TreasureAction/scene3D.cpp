//------------------------------------------------
// 3Dオブジェクトの処理 [scene3D.cpp]
//------------------------------------------------

//------------------------------------------------
//インクルードファイル
//------------------------------------------------
#include "scene3D.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "mathlib.h"

//------------------------------------------------
// マクロ定義
//------------------------------------------------
#define	NUM_VERTEX		(4)		// 頂点数
#define	NUM_POLYGON		(2)		// ポリゴン数 

//------------------------------------------------
// 静的変数
//------------------------------------------------
const char *CScene3D::m_apTextureName[] =
{
	"",
};

//------------------------------------------------
// CScene3D生成
//------------------------------------------------
CScene3D *CScene3D::Create(Vector3 pos, Vector3 rot, Vector2 ObjSize)
{
	CScene3D *pScene3D;

	pScene3D = new CScene3D;
	pScene3D->Init(pos, rot, ObjSize);

	return pScene3D;
}

//------------------------------------------------
// コンストラクタ
//------------------------------------------------
CScene3D::CScene3D(int nPriority, CScene::OBJECT_TYPE objtype, CScene::SCENE_TYPE SceneType) : CScene(nPriority, objtype, SceneType)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
}

//------------------------------------------------
// CScene3Dデストラクタ
//------------------------------------------------
CScene3D::~CScene3D()
{
}

//------------------------------------------------
// 初期化処理
//------------------------------------------------
HRESULT CScene3D::Init(Vector3 pos, Vector3 rot, Vector2 Objsize)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// 位置を設定
	m_pos = pos;

	// 向きを設定
	m_rot = rot;

	// 拡大設定
	m_Objsize = Objsize;

	//描画の設定
	m_bEnable = true;

	//カラーの設定
	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// 対角線の長さ・角度を設定
	m_fLength = SetLength(Objsize.x, Objsize.y);
	m_fAngle = SetAngle(Objsize.x, Objsize.y);

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_3D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&m_pVtxBuff,				// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
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

		// 法線の設定
		pVtx[0].nor = Vector3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = Vector3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = Vector3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = Vector3(0.0f, 1.0f, 0.0f);

		// 頂点カラーの設定
		pVtx[0].col = m_Color;
		pVtx[1].col = m_Color;
		pVtx[2].col = m_Color;
		pVtx[3].col = m_Color;

		// テクスチャ座標の設定
		pVtx[0].tex = Vector2(0.0f, 0.0f);
		pVtx[1].tex = Vector2(1.0f, 0.0f);
		pVtx[2].tex = Vector2(0.0f, 1.0f);
		pVtx[3].tex = Vector2(1.0f, 1.0f);

		// 頂点データをアンロックする
		m_pVtxBuff->Unlock();
	}
	return S_OK;
}

//------------------------------------------------
// 終了処理
//------------------------------------------------
void CScene3D::Uninit(void)
{
	// テクスチャの開放
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	// 頂点バッファの開放
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// オブジェクトをリストから削除
	//	CScene::UnlinkList();

	// オブジェクトを破棄
	Release();
}

//------------------------------------------------
// 更新処理
//------------------------------------------------
void CScene3D::Update(void)
{
}

//------------------------------------------------
// 描画処理
//------------------------------------------------
void CScene3D::Draw(void)
{
	if (!m_bEnable)
		return;

	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxScale, mtxRot, mtxTranslate;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//// 拡縮を反映
	//D3DXMatrixScaling(&mtxScale, m_size.x, m_size.y, m_size.z);
	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTranslate);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 頂点バッファをレンダリングパイプラインに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//------------------------------------------------
//テクスチャーの読み込み
//------------------------------------------------
void CScene3D::LoadTexture(const char *TextureName)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// タイプを設定

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
		TextureName,		// ファイルの名前
		&m_pTexture);				// 読み込むメモリー

}

//------------------------------------------------
//頂点の位置座標の設定
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
//頂点の色の設定
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

	// 頂点カラーの設定
	pVtx[0].col = m_Color;
	pVtx[1].col = m_Color;
	pVtx[2].col = m_Color;
	pVtx[3].col = m_Color;

	m_pVtxBuff->Unlock();

}

//------------------------------------------------
//頂点のアルファ値の設定
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

	// 頂点カラーの設定
	pVtx[0].col = m_Color;
	pVtx[1].col = m_Color;
	pVtx[2].col = m_Color;
	pVtx[3].col = m_Color;

	m_pVtxBuff->Unlock();

}

//------------------------------------------------
//頂点のuv値の設定
//------------------------------------------------
void CScene3D::SetVertexTexture(Vector2 tex0, Vector2 tex1, Vector2 tex2, Vector2 tex3)
{
	VERTEX_3D *pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点カラーの設定
	pVtx[0].tex = tex0;
	pVtx[1].tex = tex1;
	pVtx[2].tex = tex2;
	pVtx[3].tex = tex3;

	m_pVtxBuff->Unlock();
}