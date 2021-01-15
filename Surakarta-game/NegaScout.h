// NegaScout.h: interface for the CNegaScout class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NEGASCOUT_H__F7857B67_4C28_429B_8DE7_2F6F7CBE3572__INCLUDED_)
#define AFX_NEGASCOUT_H__F7857B67_4C28_429B_8DE7_2F6F7CBE3572__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SearchEngine.h"
#include "HistoryHeuristic.h"
#include "TranspositionTable.h"

class CNegaScout : 
	public CSearchEngine, 
	public CTranspositionTable, 
	public CHistoryHeuristic  
{
public:
	CNegaScout();
	virtual ~CNegaScout();
	virtual CHESSMOVE SearchAGoodMove(BYTE position[6][6]);
protected:
	int  NegaScout_TT_HH(int depth,int alpha,int beta);
    CHESSMOVE m_bsetMove[2];
//	int top;
	int flag1;
	int flag2;

};

#endif // !defined(AFX_NEGASCOUT_H__F7857B67_4C28_429B_8DE7_2F6F7CBE3572__INCLUDED_)
