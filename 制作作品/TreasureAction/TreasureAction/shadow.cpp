//------------------------------------------------
// 影の処理	[shadow.cpp]
//------------------------------------------------

//------------------------------------------------
// インクルードファイル
//------------------------------------------------
#include "shadow.h"
#include "manager.h"
#include "renderer.h"
#include "scene3D.h"

//------------------------------------------------
// 静的変数
//------------------------------------------------
const char *CShadow::pTextureName[] = 
{
	"data/texture/shadow.png",
};

//------------------------------------------------
// コンストラクタ
//------------------------------------------------
CShadow::CShadow()
{
	m_pVtxBuff = NULL;
	m_pTexture = NULL;
	m_pIdxBuff = NULL;
}

//------------------------------------------------
// デストラクタ
//------------------------------------------------
CShadow::~CShadow()
{

}

//------------------------------------------------
// 初期化処理
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
// 終了処理
//------------------------------------------------
void CShadow::Uninit(void)
{
	SafeRelease(m_pVtxBuff);
	SafeRelease(m_pIdxBuff);
	SafeRelease(m_pTexture);
	Release();
}

//------------------------------------------------
// 更新処理
//------------------------------------------------
void CShadow::Update(void)
{

}

//------------------------------------------------
// 描画処理
//------------------------------------------------
void CShadow::Draw(void)
{

}

//------------------------------------------------
// 頂点情報の設定
//------------------------------------------------
void CShadow::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D *pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	
	m_pVtxBuff->Unlock();
}

//------------------------------------------------
// インデックス情報の設定
//------------------------------------------------
void CShadow::MakeIndex(LPDIRECT3DDEVICE9 pDevice)
{

}

//------------------------------------------------
// テクスチャーの読み込み
//------------------------------------------------
void CShadow::LoadTexture(const char *pTexName)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXCreateTextureFromFile(pDevice,
		pTexName,
		&m_pTexture);
}

//------------------------------------------------
// 位置座標の更新
//------------------------------------------------
void CShadow::LoadPosition(Vector3 pos)
{
	m_pos.x = pos.x;
	m_pos.y = 0.0f;
	m_pos.z = pos.z;

	// オブジェクトと影の距離
	float fLength = pos.y - m_pos.y;

	
}