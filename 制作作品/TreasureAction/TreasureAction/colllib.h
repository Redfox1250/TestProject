//------------------------------------------------
// ����̃��C�u���� [colllib.h]
//------------------------------------------------
#pragma once

//------------------------------------------------
// �C���N���[�h�t�@�C��
//------------------------------------------------
#include "main.h"

// �~�Ɖ~�̓����蔻��(2D)
bool CircleCollision2D(Vector2 pos1, Vector2 pos2, float fRad1, float fRad2);

// �~�Ɖ~�̓����蔻��
bool CircleCollision(Vector3 pos1, Vector3 pos2, float fRad1, float fRad2);

// �����̌�������(2D)
bool LineCollision2D(Vector2 Line1S, Vector2 Line1G, Vector2 Line2S, Vector2 Line2G);

// ��`�̓����蔻��(AABB)
bool CollisionAABB(Vector3 BBMin0, Vector3 BBMax0, Vector3 BBMin1, Vector3 BBMax1);

// ��`��2D�����蔻��(AABB)
bool CollisionAABB2D(Vector3 BBMin0, Vector3 BBMax0, Vector3 BBMin1, Vector3 BBMax1);