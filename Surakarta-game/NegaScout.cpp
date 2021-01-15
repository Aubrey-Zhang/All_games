// NegaScout.cpp: implementation of the CNegaScout class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Surakarta.h"
#include "NegaScout.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNegaScout::CNegaScout()
{
//	top=-1;
	flag1=0;
	flag2=0;
}

CNegaScout::~CNegaScout()
{

}
CHESSMOVE CNegaScout::SearchAGoodMove(BYTE position[6][6])
{
	memcpy(CurPosition, position, 36);
	m_nMaxDepth = m_nSearchDepth;
	CalculateInitHashKey(CurPosition);
	ResetHistoryTable();	
	NegaScout_TT_HH(m_nMaxDepth, -20000, 20000);
	MakeMove(&m_cmBestMove);
// 	top=(top+1)%2;
// 	if(top==0)
// 		flag1=1;
// 	if(top==1)
// 		flag2=1;
//	m_bsetMove[top]=m_cmBestMove;
	memcpy(position, CurPosition, 36);
	return m_cmBestMove;
}

int CNegaScout::NegaScout_TT_HH(int depth, int alpha, int beta)
{
	int Count,i;
	BYTE type;
	int a,b,t;
	int side;
	int score;
	
	i = IsGameOver(CurPosition, depth);
	if (i != 0)
		return i;
	
	side = (m_nMaxDepth-depth)%2;
	
	score = LookUpHashTable(alpha, beta, depth, side); 
	if (score != 66666) 
		return score;
	
	if (depth <= 0)	//叶子节点取估值
	{
		score = m_pEval->Eveluate(CurPosition, side );
		EnterHashTable(exact, score, depth, side );
		return score;
	}
	
	Count = m_pMG->CreatePossibleMove(CurPosition, depth, side);
	
	for (i=0;i<Count;i++) 
	{
		m_pMG->m_nMoveList[depth][i].Score = 
			GetHistoryScore(&m_pMG->m_nMoveList[depth][i]);
	}
	MergeSort(m_pMG->m_nMoveList[depth], Count, 0);
	
	int bestmove=-1;
	
    a = alpha;
    b = beta;
    int eval_is_exact = 0;
    for ( i = 0; i < Count; i++ ) 
	{
// 		if(flag1 && depth==m_nMaxDepth)
// 		{
// 			if(m_pMG->m_nMoveList[depth][i]==m_bsetMove[0] )
// 				continue;
// 		}
// 		if(flag2 && depth==m_nMaxDepth)
// 		{
// 			if(m_pMG->m_nMoveList[depth][i]==m_bsetMove[1] )
// 				continue;
// 		}
		Hash_MakeMove(&m_pMG->m_nMoveList[depth][i], CurPosition);
		type = MakeMove(&m_pMG->m_nMoveList[depth][i]);
		
		t = -NegaScout_TT_HH(depth-1 , -b, -a );
		
		if (t > a && t < beta && i > 0) 
		{
			a = -NegaScout_TT_HH (depth-1, -beta, -t );     /* re-search */
			eval_is_exact = 1;
			if(depth == m_nMaxDepth)
				m_cmBestMove = m_pMG->m_nMoveList[depth][i];
			bestmove = i;
		}
	
		Hash_UnMakeMove(&m_pMG->m_nMoveList[depth][i],type, CurPosition); 
		UnMakeMove(&m_pMG->m_nMoveList[depth][i],type); 
		if (a < t)
		{
			eval_is_exact = 1;
			a=t;
			if(depth == m_nMaxDepth)
				m_cmBestMove = m_pMG->m_nMoveList[depth][i];
		}
		if ( a >= beta ) 
		{
			EnterHashTable(lower_bound, a, depth,side);
			EnterHistoryScore(&m_pMG->m_nMoveList[depth][i], depth);
			return a;
		}       
		b = a + 1;                      /* set new null window */
	}
	if (bestmove != -1)
		EnterHistoryScore(&m_pMG->m_nMoveList[depth][bestmove], depth);
	if (eval_is_exact) 
		EnterHashTable(exact, a, depth,side);
	else 
		EnterHashTable(upper_bound, a, depth,side);
	return a;
}