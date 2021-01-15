// Eveluation.cpp: implementation of the CEveluation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Surakarta.h"
#include "Eveluation.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEveluation::CEveluation()
{

}

CEveluation::~CEveluation()
{

}
int CEveluation::Eveluate(BYTE position[6][6], BOOL IsBlackturn)//存位置信息，轮到谁走棋
{
	int BlackValue=0,RedValue=0;//初始化估值记录
	int BProtectValue=0,BAttactValue=0;//黑估值
	int RProtectValue=0,RAttactValue=0;//红估值
	int i,j;
	GetAttackInfo(position);//传当前局面给attack
	GetProtectInfo(position);//传当前局面给attack
	for (i=0;i<6;i++)
	{
		for (j=0;j<6;j++)
		{
			if (position[i][j]==1)//此处是黑子
			{

				if(i==4&&j==1 || i==1&&j==1 || i==4&&j==4 || i==1&&j==4 || i==2&&j==3 || i==2&&j==2 || i==3&&j==2 || i==3&&j==3 )
					BlackValue+=150;//重要的内外轨尖点共8点
				else if(i==0&&j==0|| i ==5 &&j == 5|| i ==0 &&j ==5 || i ==5 &&j ==0 )
					BlackValue+=90;
				else
					BlackValue=BlackValue+100;//黑子所占据的其它位置上的点
				BProtectValue=BProtectValue+m_ProtectPos[i][j];
				BAttactValue=BAttactValue+m_AttackPos[i][j];
			}
			if(position[i][j]==2)//此处是红子？？？？？？？？//一直把black当成己方，并且红黑是逻辑上的概念
			{
				RedValue=RedValue+100;//红子所占据的其它位置上的点
				RProtectValue=RProtectValue+m_ProtectPos[i][j];//不需要知道对方占据了尖点，因为对方在尖点上无法改变什么，无用信息，在黑子的保护评估时已经评估过了
				RAttactValue=RAttactValue+m_AttackPos[i][j];
			}
		}
	}

	if (IsBlackturn)//当轮到黑子走棋时
	{
		for (i=0;i<6;i++)
		{
			for(j=0;j<6;j++)
			{
				if(position[i][j]==2)//此处是红子
				{
					if (m_AttackPos[i][j]-m_ProtectPos[i][j]>0)//红子面临被吃情况
						BlackValue=BlackValue+100;//黑提高行动价值
					if(m_AttackPos[i][j]-m_ProtectPos[i][j]==0)//红子风险与保护相同
						RedValue=RedValue+50;//红子行动价值提高
				}
				if(position[i][j]==1)//此处是黑子
					if(m_ProtectPos[i][j]-m_AttackPos[i][j]<0)//黑子面临被吃情况
						BlackValue=BlackValue-50;//黑子不能再动
			
			}   
		}
	}
	else//当轮到红子走棋时
	{
		for (i=0;i<6;i++)
		{
			for (j=0;j<6;j++)
			{
				if (position[i][j]==1)//此处是黑子
				{
					if(m_AttackPos[i][j]-m_ProtectPos[i][j]>0)//黑子面临被吃风险
						RedValue=RedValue+100;//红提高行动价值
					if(m_AttackPos[i][j]-m_ProtectPos[i][j]>0)//黑子风险与保护相同
						BlackValue=BlackValue+50;//黑子行动价值提高
				}
				if (position[i][j]==2)//此处是红子
				{
					if(m_ProtectPos[i][j]-m_AttackPos[i][j]<0)//红子面临被吃情况
						RedValue=RedValue-50;//红子不能再动
				}
			}
		}
	}
	BlackValue=BlackValue-BAttactValue+BProtectValue;
	RedValue=RedValue+RProtectValue-RAttactValue;
	if (IsBlackturn)//走黑棋
		return BlackValue-RedValue;//黑-红
	else//走红棋
		return RedValue-BlackValue;//红-黑
}




void CEveluation::GetAttackInfo(BYTE position[6][6])
{
	short int CurPosition[6][6];//空棋盘
	memset(m_AttackPos,0,36);//将二维棋盘A的位置都清零
    memcpy(CurPosition,position,36);//将当前局面复值给C空棋盘
	int flag=1,i,j,m,n;
	for (i=0;i<6;i++)
	{
		for (j=0;j<6;j++)
		{
			for (m=0;m<6;m++)
			{
				for(n=0;n<6;n++)
				{
					while (flag)//只执行一次的循环
					{
						flag=0;
						if(m_pMg->IsValidMove(CurPosition,m,n,i,j) && CurPosition[m][n]+CurPosition[i][j]==3)//黑子1，红子2，无棋0
						{
							m_AttackPos[i][j]++;//位置攻击值累加
							if(!m_pMg->IsValidMove(CurPosition,i,j,m,n))//面临马上被吃的风险，你死我活
							{
								m_AttackPos[i][j]+=100;//位置攻击值增加
								continue;
								
							}
							flag=1;//再次循环
							n=-1;//保证攻击值不重复累加++
							m=0;
							CurPosition[m][n]=0;//这个地址就是所申请的数组存储空间的首地址的向前偏移一个单位(也就是偏移一个当前数组类型所对应的字节数)所对应的地址。这个地址由于没有跟着数组空间一起初始化，
						}
					}
				}
			}
			memcpy(CurPosition,position,36);//将当前局面复值给C空棋盘
		}
	}
}



void CEveluation::GetProtectInfo(BYTE position[6][6])
{
	short int CurPosition[6][6];
	memset(m_ProtectPos,0,36);
    memcpy(CurPosition,position,36);
	int flag=1,i,j,m,n;
	for (i=0;i<6;i++)
	{
		for (j=0;j<6;j++)
		{
			for (m=0;m<6;m++)
			{
				for(n=0;n<6;n++)
				{
					while (flag)
					{
						flag=0;
						if(CurPosition[m][n]-CurPosition[i][j]==0 &&CurPosition[m][n])//相同的阵营且有子，可经路线全是同一方
						{
							CurPosition[m][n]=3-CurPosition[i][j];//假设起始位置换成对家，对家可以吃了自己，但真实情况是己方占着，所以安全
							if(m_pMg->IsValidMove(CurPosition,m,n,i,j))//合法可走
							{
								m_ProtectPos[i][j]++;//增加安全值
								flag=1;
								n=-1;
								m=0;
								CurPosition[m][n]=0;
							}
						}
					}
				}
			}
			memcpy(CurPosition,position,36);//棋盘的开始位置不变，所到的位置不断变化
		}
	}
}
//增强攻击性的值可以变为+2