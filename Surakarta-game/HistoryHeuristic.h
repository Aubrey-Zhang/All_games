// HistoryHeuristic.h: interface for the CHistoryHeuristic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HISTORYHEURISTIC_H__8CF71349_3539_44FD_ADE5_6BAE55F71A3F__INCLUDED_)
#define AFX_HISTORYHEURISTIC_H__8CF71349_3539_44FD_ADE5_6BAE55F71A3F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Define.h"
class CHistoryHeuristic  
{
public:
	CHistoryHeuristic();
	virtual ~CHistoryHeuristic();
	void ResetHistoryTable();
	int GetHistoryScore(CHESSMOVE *move);
	void EnterHistoryScore(CHESSMOVE *move,int depth);
	void MergeSort(CHESSMOVE *source,int n,BOOL direction);
protected:
	void MergePass(CHESSMOVE *source,CHESSMOVE *target,const int s,const int n,const BOOL direction);
	void Merge(CHESSMOVE *source,CHESSMOVE *target,int l,int m,int r);
	void Merge_A(CHESSMOVE *source,CHESSMOVE *target,int l,int m,int r);
	int m_HistoryTable[36][36];
	CHESSMOVE m_TargetBuff[100];
};

#endif // !defined(AFX_HISTORYHEURISTIC_H__8CF71349_3539_44FD_ADE5_6BAE55F71A3F__INCLUDED_)
