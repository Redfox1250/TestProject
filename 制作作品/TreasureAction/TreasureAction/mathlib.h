#pragma once
//------------------------------------------------
// �v�Z���C�u���� [mathlib.h]
//------------------------------------------------
//------------------------------------------------
// �C���N���[�h�t�@�C��
//------------------------------------------------
#include "main.h"

//------------------------------------------------
// �v���g�^�C�v�錾
//------------------------------------------------

// �Ίp���̌X��
float SetAngle(float x, float y);

// �Ίp���̒���
float SetLength(float x, float y);  

// �����̐ݒ�(int)
int  SetRand(int iMin, int iMax);

// ��]�l����(-��)�𒴂����ꍇ������l��߂�(float)
void RotateOverCheck(float &frot);

 // ��]�l����(-��)�𒴂����ꍇ������l��߂�(Vector3)
void RotateOverCheck(Vector3 &rot);

#pragma once