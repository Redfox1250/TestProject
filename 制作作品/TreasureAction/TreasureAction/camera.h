#pragma once
//------------------------------------------------
// �J�����̏���	[camera.h]
//------------------------------------------------
#ifndef _CAMERA_H_
#define _CAMERA_H_

//------------------------------------------------
//�C���N���[�h�t�@�C��
//------------------------------------------------
#include "main.h"

//------------------------------------------------
//�J�����̃N���X
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
	D3DXMATRIX m_mtxView;			// �r���[�}�g���b�N�X
	D3DXMATRIX m_mtxProjection;		// �v���W�F�N�V�����}�g���b�N�X

	Vector3 m_posP;				// ���_
	Vector3 m_posPDest;			// ���_�̊���
	Vector3 m_posR;				// �����_
	Vector3 m_posRDest;			// �����_�̊���

	Vector3 m_vecU;				// ������x�N�g��
	Vector3 m_rot;				// ����
	float m_fLength;				// ���_���璍���_�̋���
	float m_fLengthInterval;		// ���_���璍���_�܂ł̋���
	float m_fLengthIntervalXZ;		// ���_���璍���_�܂ł̋���(XZ����)


	D3DXQUATERNION m_quatRot;
	D3DXMATRIX m_mtxRot;

#ifdef _DEBUG
	bool m_bCameraDebug;			// �f�o�b�O�p	�L�[����ŃJ�����ړ�
#endif // _DEBUG
};

#endif
