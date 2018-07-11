
#include "colllib.h"

//------------------------------------------------
// �~�Ɖ~�̓����蔻��(2D)
//------------------------------------------------
bool CircleCollision2D(Vector2 pos1, Vector2 pos2, float fRad1, float fRad2)
{
	float dx, dy, dr;

	dx = abs(pos1.x - pos2.x);	// ���������̋���
	dy = abs(pos1.y - pos2.y);	// ���������̋���
	dr = fRad1 + fRad2;			// ���a�̘a

	if (sqrtf(dx * dx + dy * dy) < dr)
	{
		return true;
	}
	return false;
}

//------------------------------------------------
// �~�Ɖ~�̓����蔻��
//------------------------------------------------
bool CircleCollision(Vector3 pos1, Vector3 pos2, float fRad1, float fRad2)
{
	float dx, dy,dz, dr;

	dx = abs(pos1.x - pos2.x);	// ���������̋���
	dy = abs(pos1.y - pos2.y);	// ���������̋���
	dz = abs(pos1.z - pos2.z);	// 

	dr = fRad1 + fRad2;			// ���a�̘a

	if (sqrtf(dx * dx + dy * dy + dz * dz) < dr)
	{
		return true;
	}
	return false;
}

//------------------------------------------------
//��`�̓����蔻��(AABB)
//------------------------------------------------
bool  CollisionAABB(Vector3 BBMin0, Vector3 BBMax0, Vector3 BBMin1, Vector3 BBMax1)
{
	if (BBMin0.x < BBMax1.x && BBMax0.x > BBMin1.x &&
		BBMin0.y < BBMax1.y && BBMax0.y > BBMin1.y &&
		BBMin0.z < BBMax1.z && BBMax0.z > BBMin1.z)
	{
		return true;
	}
	return false;
}

//------------------------------------------------
//��`��2D�����蔻��(AABB)
//------------------------------------------------
bool  CollisionAABB2D(Vector3 BBMin0, Vector3 BBMax0, Vector3 BBMin1, Vector3 BBMax1)
{
	if (BBMin0.x < BBMax1.x && BBMax0.x > BBMin1.x &&
		BBMin0.y < BBMax1.y && BBMax0.y > BBMin1.y)
	{
		return true;
	}
	return false;
}

//------------------------------------------------
//�����̌�������2D
//------------------------------------------------
bool LineCollision2D(Vector2 Line1S, Vector2 Line1G, Vector2 Line2S, Vector2 Line2G)
{
	Vector2 v1 = Line1S - Line2S;
	Vector2 vA = Line1G - Line1S;
	Vector2 vB = Line2G - Line2S;

	if (Line1S.x != Line1G.x || Line1S.y != Line1G.y)
	{

	}
	else
	{
		//�������_�̂Ƃ��͌������Ă��Ȃ��Ƃ���
		return false;
	}
	if (Line2S.x != Line2G.x || Line2S.y != Line2G.y)
	{

	}
	else
	{
		return false;//�������_�̂Ƃ��͌������Ă��Ȃ��Ƃ���
	}

	float fDeno = vA.x * vB.y - vA.y * vB.x;//�O�ς̒���

	//���ꂪ�O�ŁA���s�ȂƂ���
	if (fDeno != 0.0f)
	{

	}
	else
	{
		return false;//�������Ă��Ȃ����Ƃɂ���
	}

	float t = (v1.y * vB.x - v1.x * vB.y) / fDeno;
	float s = (v1.y * vA.x - v1.x * vA.y) / fDeno;

	if (t < 0.0f || t > 1.0f || s < 0.0f || s > 1.0f)
	{
		return false;//�������Ă��Ȃ�
	}

	return true;

}
