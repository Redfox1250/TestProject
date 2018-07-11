//------------------------------------------------
// 頂点設定のライブラリ [vermath.cpp]
//------------------------------------------------

//------------------------------------------------
// インクルードファイル
//------------------------------------------------
#include "verlib.h"

//------------------------------------------------
// 頂点情報用の数値の設定
//------------------------------------------------
void VertexNumSet(int &index, int &vertex, int &polygon, int XPoly, int YPoly)
{
	index = XPoly * (YPoly * 2) + (YPoly * 4) - 2;
	vertex = (XPoly + 1)*(YPoly + 1);
	polygon = index - 2;
}

//------------------------------------------------
// インデックス情報の設定
//------------------------------------------------
void IndexSet(WORD *pIdx, int vertexX, int vertexY)
{
	int index = vertexX * (vertexY * 2) + (vertexY * 4) - 2;
	int iNext = 1;
	int iCount = 0;
	for (int i = 0; i < index; i+= 2)
	{
		if (((vertexX + 1) + iCount) % ((vertexX + 1) * 2) == 0)
		{
			pIdx[i] = pIdx[i - 1];
			pIdx[i + 1] = pIdx[i] + vertexX + 2;
			iNext++;
			iCount = 0;
			continue;
		}
		pIdx[i] = iNext * (vertexX + 1) + iCount;
		pIdx[i + 1] = pIdx[i] - (vertexX + 1);
		iCount++;
	}
}