// Eveluation.h: interface for the CEveluation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVELUATION_H__D5138E45_7853_40AB_80A8_5D7BB3E091F8__INCLUDED_)
#define AFX_EVELUATION_H__D5138E45_7853_40AB_80A8_5D7BB3E091F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MoveGenerator.h"
class CEveluation  
{
public:
	CEveluation();
	virtual ~CEveluation();
	virtual int Eveluate(BYTE position[6][6],BOOL bIsBlackTurn);//估值函数，对传入的棋盘打分，bIsBlackTurn代表轮到谁走棋
	void GetAttackInfo(BYTE position[6][6]);
	void GetProtectInfo(BYTE position[6][6]);
	BYTE m_AttackPos[6][6];
	BYTE m_ProtectPos[6][6];
	CMoveGenerator *m_pMg;
};

#endif // !defined(AFX_EVELUATION_H__D5138E45_7853_40AB_80A8_5D7BB3E091F8__INCLUDED_)
