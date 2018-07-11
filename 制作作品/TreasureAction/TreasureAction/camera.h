#pragma once
//------------------------------------------------
// カメラの処理	[camera.h]
//------------------------------------------------
#ifndef _CAMERA_H_
#define _CAMERA_H_

//------------------------------------------------
//インクルードファイル
//------------------------------------------------
#include "main.h"

//------------------------------------------------
//カメラのクラス
//------------------------------------------------
class CCamera
{
public:
	CCamera();
	~CCamera();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Initialize(void);
	void SetPosition(Vector3 posP, Vector3 posR);

	Vector3 GetPosP(void) { return m_posP; }
	Vector3 GetPosR(void) { return m_posR; }
	Vector3 GetVecU(void) { return m_vecU; }

	void SetRot(Vector3 rot) { m_rot = rot; }
	Vector3 GetRot(void) { return m_rot; }

	void SetCamera(void);
 	D3DXMATRIX GetViewMatrix(void) { return m_mtxView; }
	D3DXMATRIX GetProjectionMatrix(void) { return m_mtxProjection; }
 	void posPRotate(Vector3 rot);
	void SetLength(float fLength);
	void AddLength(float fLength);
 private:
	D3DXMATRIX m_mtxView;			// ビューマトリックス
	D3DXMATRIX m_mtxProjection;		// プロジェクションマトリックス

	Vector3 m_posP;				// 視点
	Vector3 m_posPDest;			// 視点の慣性
	Vector3 m_posR;				// 注視点
	Vector3 m_posRDest;			// 注視点の慣性

	Vector3 m_vecU;				// 上方向ベクトル
	Vector3 m_rot;				// 向き
	float m_fLength;				// 視点から注視点の距離
	float m_fLengthInterval;		// 視点から注視点までの距離
	float m_fLengthIntervalXZ;		// 視点から注視点までの距離(XZ平面)


	D3DXQUATERNION m_quatRot;
	D3DXMATRIX m_mtxRot;

#ifdef _DEBUG
	bool m_bCameraDebug;			// デバッグ用	キー操作でカメラ移動
#endif // _DEBUG
};

#endif
