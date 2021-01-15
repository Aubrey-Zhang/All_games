// MoveGenerator.h: interface for the CMoveGenerator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOVEGENERATOR_H__70DFE443_B8BC_48BB_871B_68E756817EAE__INCLUDED_)
#define AFX_MOVEGENERATOR_H__70DFE443_B8BC_48BB_871B_68E756817EAE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Define.h"

class CMoveGenerator  
{
public:
	CMoveGenerator();
	virtual ~CMoveGenerator();
	//检查下一个走法是否合法
	static BOOL IsValidMove(BYTE position[6][6],int nFromX,int nFromY,int nToX,int nToY);
	static BOOL IsValidMove(short int position[6][6], int nFromX, int nFromY, int nToX, int nToY);
	//产生给定棋盘上的所有合法的走法
	int CreatePossibleMove(BYTE position[6][6],int nPly,int nSide);
    
	//存放走法队列
	CHESSMOVE m_nMoveList[12][100];
	//插入一个走法
	int AddMove(int nFromX,int nToX,int nFromY,int nToY,int nPly);
protected: 
	
	
	//记录m_nMoveList中走法的数量
	int m_nMoveCount;
};

#endif // !defined(AFX_MOVEGENERATOR_H__70DFE443_B8BC_48BB_871B_68E756817EAE__INCLUDED_)
