//------------------------------------------------
// 判定のライブラリ [colllib.h]
//------------------------------------------------
#pragma once

//------------------------------------------------
// インクルードファイル
//------------------------------------------------
#include "main.h"

// 円と円の当たり判定(2D)
bool CircleCollision2D(Vector2 pos1, Vector2 pos2, float fRad1, float fRad2);

// 円と円の当たり判定
bool CircleCollision(Vector3 pos1, Vector3 pos2, float fRad1, float fRad2);

// 線分の交差判定(2D)
bool LineCollision2D(Vector2 Line1S, Vector2 Line1G, Vector2 Line2S, Vector2 Line2G);

// 矩形の当たり判定(AABB)
bool CollisionAABB(Vector3 BBMin0, Vector3 BBMax0, Vector3 BBMin1, Vector3 BBMax1);

// 矩形の2D当たり判定(AABB)
bool CollisionAABB2D(Vector3 BBMin0, Vector3 BBMax0, Vector3 BBMin1, Vector3 BBMax1);