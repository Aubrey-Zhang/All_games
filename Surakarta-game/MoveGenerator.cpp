// MoveGenerator.cpp: implementation of the CMoveGenerator class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Surakarta.h"

#include "MoveGenerator.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMoveGenerator::CMoveGenerator()
{

}

CMoveGenerator::~CMoveGenerator()
{

}
BOOL CMoveGenerator::IsValidMove(BYTE position[6][6],int nFromX,int nFromY,int nToX,int nToY)
{
	int type;
	int i,j=0,flag=0,m1=-1,m2=-1,n1=-1,n2=-1,arc=0,p1=-1,p2=-1,q1=-1,q2=-1;	
    Node Node1[24];
	Node Node2[24];
    Node1[0].i=2;Node1[0].j=2;Node1[0].arc=0;
    Node1[1].i=1;Node1[1].j=2;Node1[1].arc=0;
	Node1[2].i=0;Node1[2].j=2;Node1[2].arc=1;
	Node1[3].i=2;Node1[3].j=0;Node1[3].arc=0;
	Node1[4].i=2;Node1[4].j=1;Node1[4].arc=0;
	Node1[5].i=2;Node1[5].j=2;Node1[5].arc=0;
	Node1[6].i=2;Node1[6].j=3;Node1[6].arc=0;
	Node1[7].i=2;Node1[7].j=4;Node1[7].arc=0;
	Node1[8].i=2;Node1[8].j=5;Node1[8].arc=1;
	Node1[9].i=0;Node1[9].j=3;Node1[9].arc=0;
	Node1[10].i=1;Node1[10].j=3;Node1[10].arc=0;
	Node1[11].i=2;Node1[11].j=3;Node1[11].arc=0;
	Node1[12].i=3;Node1[12].j=3;Node1[12].arc=0;
	Node1[13].i=4;Node1[13].j=3;Node1[13].arc=0;
	Node1[14].i=5;Node1[14].j=3;Node1[14].arc=1;
	Node1[15].i=3;Node1[15].j=5;Node1[15].arc=0;
	Node1[16].i=3;Node1[16].j=4;Node1[16].arc=0;
	Node1[17].i=3;Node1[17].j=3;Node1[17].arc=0;
	Node1[18].i=3;Node1[18].j=2;Node1[18].arc=0;
	Node1[19].i=3;Node1[19].j=1;Node1[19].arc=0;
	Node1[20].i=3;Node1[20].j=0;Node1[20].arc=1;
    Node1[21].i=5;Node1[21].j=2;Node1[21].arc=0;
	Node1[22].i=4;Node1[22].j=2;Node1[22].arc=0;
	Node1[23].i=3;Node1[23].j=2;Node1[23].arc=0;
	Node2[0].i=1,Node2[0].j=1;Node2[0].arc=0;
    Node2[1].i=0,Node2[1].j=1;Node2[1].arc=1;
	Node2[2].i=1,Node2[2].j=0;Node2[2].arc=0;
	Node2[3].i=1,Node2[3].j=1;Node2[3].arc=0;
	Node2[4].i=1,Node2[4].j=2;Node2[4].arc=0;
	Node2[5].i=1,Node2[5].j=3;Node2[5].arc=0;
	Node2[6].i=1,Node2[6].j=4;Node2[6].arc=0;
	Node2[7].i=1,Node2[7].j=5;Node2[7].arc=1;
	Node2[8].i=0,Node2[8].j=4;Node2[8].arc=0;
	Node2[9].i=1,Node2[9].j=4;Node2[9].arc=0;
	Node2[10].i=2,Node2[10].j=4;Node2[10].arc=0;
	Node2[11].i=3,Node2[11].j=4;Node2[11].arc=0;
	Node2[12].i=4,Node2[12].j=4;Node2[12].arc=0;
	Node2[13].i=5,Node2[13].j=4;Node2[13].arc=1;
	Node2[14].i=4,Node2[14].j=5;Node2[14].arc=0;
	Node2[15].i=4,Node2[15].j=4;Node2[15].arc=0;
	Node2[16].i=4,Node2[16].j=3;Node2[16].arc=0;
	Node2[17].i=4,Node2[17].j=2;Node2[17].arc=0;
	Node2[18].i=4,Node2[18].j=1;Node2[18].arc=0;
	Node2[19].i=4,Node2[19].j=0;Node2[19].arc=1;
	Node2[20].i=5,Node2[20].j=1;Node2[20].arc=0;
	Node2[21].i=4,Node2[21].j=1;Node2[21].arc=0;
	Node2[22].i=3,Node2[22].j=1;Node2[22].arc=0;
	Node2[23].i=2,Node2[23].j=1;Node2[23].arc=0;
	for(i=0;i<24;i++)
		Node1[i].color=position[Node1[i].i][Node1[i].j];
	for(i=0;i<24;i++)
		Node2[i].color=position[Node2[i].i][Node2[i].j];
     if (position[nToX][nToY]==0)
	 {
		 if(fabs(nFromX-nToX)<2 && fabs(nFromY-nToY)<2)
		     return TRUE;
		 else
			 return FALSE;
	 }
	 else if (position[nToX][nToY]+position[nFromX][nFromY]==3)
	 {
		 type=position[nFromX][nFromY];
		 position[nFromX][nFromY]=0;
		 for(i=0;i<24;i++)
			 Node1[i].color=position[Node1[i].i][Node1[i].j];
		 for(i=0;i<24;i++)
			Node2[i].color=position[Node2[i].i][Node2[i].j];
		 m1=m2=n1=n2=-1;
	     p1=p2=q1=q2=-1;
		 for(i=0;i<24;i++)//big
		   {
			if(Node1[i].i==nFromX && Node1[i].j==nFromY)//起点
			{
				if(m1==-1)
					m1=i;
				else
					m2=i;
			}
			if(Node1[i].i==nToX && Node1[i].j==nToY)//终点
			{
				if(n1==-1)
					n1=i;
				else
					n2=i;
			}
		   }
		   for(i=0;i<24;i++)//small
		   {
			if(Node2[i].i==nFromX && Node2[i].j==nFromY)
			{
				if(p1==-1)
					p1=i;
				else
					p2=i;
			}
			if(Node2[i].i==nToX && Node2[i].j==nToY)
			{
				if(q1==-1)
					q1=i;
				else
					q2=i;
			}
		   }	   			   
		  if(m1!=-1 && n1!=-1)
			{
				flag=0;
				arc=0;
				for(i=m1;i!=n1;i=(i+1)%24)
				{
					if(Node1[i].color!=0 && i!=m1)
						flag=1;//有阻挡
					if(Node1[i].arc==1)
						arc=1;//有弧
				}
				if(!(flag==0 && arc==1))
				{
					flag=0;arc=0;
					for(i=n1;i!=m1;i=(i+1)%24)
					{
						if(Node1[i].color!=0 && i!=n1)
					          flag=1;
					    if(Node1[i].arc==1)
						      arc=1;
					}
				}
				if(!(flag==0 && arc==1))
				{
					if(n2!=-1)
					{
						flag=0;arc=0;
						for(i=n2;i!=m1;i=(i+1)%24)
						{
						if(Node1[i].color!=0 && i!=n2)
						    flag=1;
					    if(Node1[i].arc==1)
						    arc=1;
						}
						if(!(flag==0 && arc==1))
						{
							flag=0,arc=0;
							for(i=m1;i!=n2;i=(i+1)%24)
							{
						      if(Node1[i].color!=0 && i!=m1)
						         flag=1;
					          if(Node1[i].arc==1)
						         arc=1;
							}
						}
					}
					if(!(flag==0 && arc==1))
					{
						if(m2!=-1)
						{
							flag=0;arc=0;
					     	for(i=m2;i!=n1;i=(i+1)%24)
							{
						      if(Node1[i].color!=0 && i!=m2)
						         flag=1;
					          if(Node1[i].arc==1)
						         arc=1;
							}
							if(!(flag==0 && arc==1))
							{
								flag=0;arc=0;
					            for(i=n1;i!=m2;i=(i+1)%24)
								{
						           if(Node1[i].color!=0 && i!=n1)
						              flag=1;
					               if(Node1[i].arc==1)
						              arc=1;
								}
							}
							if(!(flag==0 && arc==1))
							{
								if(n2!=-1)
								{
									flag=0;arc=0;
									for(i=m2;i!=n2;i=(i+1)%24)
									{
						                if(Node1[i].color!=0  && i!=m2)
						                     flag=1;
					                    if(Node1[i].arc==1)
						                     arc=1;
									}
							        if(!(flag==0 && arc==1))
									{
								        flag=0;arc=0;
					                    for(i=n2;i!=m2;i=(i+1)%24)
										{
						                    if(Node1[i].color!=0  && i!=n2)
						                        flag=1;
					                        if(Node1[i].arc==1)
						                        arc=1;
										}
									}
								}
							}
						}
					}
				}
			}
			 if(q1!=-1 && p1!=-1 && !(flag==0 && arc==1))//小圈
			{
			
				flag=0;
				arc=0;
				for(i=p1;i!=q1;i=(i+1)%24)
				{
					if(Node2[i].color!=0 && i!=p1)
						flag=1;
					if(Node2[i].arc==1)
						arc=1;
				}
				if(!(flag==0 && arc==1))
				{
					flag=0;arc=0;
					for(i=q1;i!=p1;i=(i+1)%24)
					{
						if(Node2[i].color!=0 && i!=q1)
					          flag=1;
					    if(Node2[i].arc==1)
						      arc=1;
					}
				}
				if(!(flag==0 && arc==1))
				{
					if(q2!=-1)
					{
						flag=0;arc=0;
						for(i=q2;i!=p1;i=(i+1)%24)
						{
						if(Node2[i].color!=0 && i!=q2)
						flag=1;
					    if(Node2[i].arc==1)
						arc=1;
						}
						if(!(flag==0 && arc==1))
						{
							flag=0,arc=0;
							for(i=p1;i!=q2;i=(i+1)%24)
							{
						      if(Node2[i].color!=0 && i!=p1)
						         flag=1;
					          if(Node2[i].arc==1)
						         arc=1;
							}
						}
					}
					if(!(flag==0 && arc==1))
					{
						if(p2!=-1)
						{
							flag=0;arc=0;
					     	for(i=p2;i!=q1;i=(i+1)%24)
							{
						      if(Node2[i].color!=0 && i!=p2)
						         flag=1;
					          if(Node2[i].arc==1)
						         arc=1;
							}
							if(!(flag==0 && arc==1))
							{
								flag=0;arc=0;
					            for(i=q1;i!=p2;i=(i+1)%24)
								{
						           if(Node2[i].color!=0 && i!=q1)
						              flag=1;
					               if(Node2[i].arc==1)
						              arc=1;
								}
							}
							if(!(flag==0 && arc==1))
							{
								if(q2!=-1)
								{
									flag=0;arc=0;
									for(i=p2;i!=q2;i=(i+1)%24)
									{
						                if(Node2[i].color!=0  && i!=p2)
						                     flag=1;
					                    if(Node2[i].arc==1)
						                     arc=1;
									}
							        if(!(flag==0 && arc==1))
									{
								        flag=0;arc=0;
					                    for(i=q2;i!=p2;i=(i+1)%24)
										{
						                    if(Node2[i].color!=0  && i!=q2)
						                        flag=1;
					                        if(Node2[i].arc==1)
						                        arc=1;
										}
									}
								}
							}
						}
					}
				}
			}

			if(flag==0 && arc==1)
			{
				position[nFromX][nFromY]=type;return TRUE;
			}
				
			else
			{
				position[nFromX][nFromY]=type;return FALSE;
			}
	 }
	 else
		 return FALSE;
}
BOOL CMoveGenerator::IsValidMove(short int position[6][6], int nFromX, int nFromY, int nToX, int nToY)
{
	int type;
	int i, j=0, flag = 0, m1 = -1, m2 = -1, n1 = -1, n2 = -1, arc = 0, p1 = -1, p2 = -1, q1 = -1, q2 = -1;
	Node Node1[24];
	Node Node2[24];
	Node1[0].i = 2; Node1[0].j = 2; Node1[0].arc = 0;
	Node1[1].i = 1; Node1[1].j = 2; Node1[1].arc = 0;
	Node1[2].i = 0; Node1[2].j = 2; Node1[2].arc = 1;
	Node1[3].i = 2; Node1[3].j = 0; Node1[3].arc = 0;
	Node1[4].i = 2; Node1[4].j = 1; Node1[4].arc = 0;
	Node1[5].i = 2; Node1[5].j = 2; Node1[5].arc = 0;
	Node1[6].i = 2; Node1[6].j = 3; Node1[6].arc = 0;
	Node1[7].i = 2; Node1[7].j = 4; Node1[7].arc = 0;
	Node1[8].i = 2; Node1[8].j = 5; Node1[8].arc = 1;
	Node1[9].i = 0; Node1[9].j = 3; Node1[9].arc = 0;
	Node1[10].i = 1; Node1[10].j = 3; Node1[10].arc = 0;
	Node1[11].i = 2; Node1[11].j = 3; Node1[11].arc = 0;
	Node1[12].i = 3; Node1[12].j = 3; Node1[12].arc = 0;
	Node1[13].i = 4; Node1[13].j = 3; Node1[13].arc = 0;
	Node1[14].i = 5; Node1[14].j = 3; Node1[14].arc = 1;
	Node1[15].i = 3; Node1[15].j = 5; Node1[15].arc = 0;
	Node1[16].i = 3; Node1[16].j = 4; Node1[16].arc = 0;
	Node1[17].i = 3; Node1[17].j = 3; Node1[17].arc = 0;
	Node1[18].i = 3; Node1[18].j = 2; Node1[18].arc = 0;
	Node1[19].i = 3; Node1[19].j = 1; Node1[19].arc = 0;
	Node1[20].i = 3; Node1[20].j = 0; Node1[20].arc = 1;
	Node1[21].i = 5; Node1[21].j = 2; Node1[21].arc = 0;
	Node1[22].i = 4; Node1[22].j = 2; Node1[22].arc = 0;
	Node1[23].i = 3; Node1[23].j = 2; Node1[23].arc = 0;
	Node2[0].i = 1, Node2[0].j = 1; Node2[0].arc = 0;
	Node2[1].i = 0, Node2[1].j = 1; Node2[1].arc = 1;
	Node2[2].i = 1, Node2[2].j = 0; Node2[2].arc = 0;
	Node2[3].i = 1, Node2[3].j = 1; Node2[3].arc = 0;
	Node2[4].i = 1, Node2[4].j = 2; Node2[4].arc = 0;
	Node2[5].i = 1, Node2[5].j = 3; Node2[5].arc = 0;
	Node2[6].i = 1, Node2[6].j = 4; Node2[6].arc = 0;
	Node2[7].i = 1, Node2[7].j = 5; Node2[7].arc = 1;
	Node2[8].i = 0, Node2[8].j = 4; Node2[8].arc = 0;
	Node2[9].i = 1, Node2[9].j = 4; Node2[9].arc = 0;
	Node2[10].i = 2, Node2[10].j = 4; Node2[10].arc = 0;
	Node2[11].i = 3, Node2[11].j = 4; Node2[11].arc = 0;
	Node2[12].i = 4, Node2[12].j = 4; Node2[12].arc = 0;
	Node2[13].i = 5, Node2[13].j = 4; Node2[13].arc = 1;
	Node2[14].i = 4, Node2[14].j = 5; Node2[14].arc = 0;
	Node2[15].i = 4, Node2[15].j = 4; Node2[15].arc = 0;
	Node2[16].i = 4, Node2[16].j = 3; Node2[16].arc = 0;
	Node2[17].i = 4, Node2[17].j = 2; Node2[17].arc = 0;
	Node2[18].i = 4, Node2[18].j = 1; Node2[18].arc = 0;
	Node2[19].i = 4, Node2[19].j = 0; Node2[19].arc = 1;
	Node2[20].i = 5, Node2[20].j = 1; Node2[20].arc = 0;
	Node2[21].i = 4, Node2[21].j = 1; Node2[21].arc = 0;
	Node2[22].i = 3, Node2[22].j = 1; Node2[22].arc = 0;
	Node2[23].i = 2, Node2[23].j = 1; Node2[23].arc = 0;
	for (i = 0; i<24; i++)
		Node1[i].color = position[Node1[i].i][Node1[i].j];
	for (i = 0; i<24; i++)
		Node2[i].color = position[Node2[i].i][Node2[i].j];
	if (position[nToX][nToY] == 0)
	{
		if (fabs(nFromX - nToX)<2 && fabs(nFromY - nToY)<2)
			return TRUE;
		else
			return FALSE;
	}
	else if (position[nToX][nToY] + position[nFromX][nFromY] == 3)
	{
		type = position[nFromX][nFromY];
		position[nFromX][nFromY] = 0;
		for (i = 0; i<24; i++)
			Node1[i].color = position[Node1[i].i][Node1[i].j];
		for (i = 0; i<24; i++)
			Node2[i].color = position[Node2[i].i][Node2[i].j];
		m1 = m2 = n1 = n2 = -1;
		p1 = p2 = q1 = q2 = -1;
		for (i = 0; i<24; i++)//big
		{
			if (Node1[i].i == nFromX && Node1[i].j == nFromY)//起点
			{
				if (m1 == -1)
					m1 = i;
				else
					m2 = i;
			}
			if (Node1[i].i == nToX && Node1[i].j == nToY)//终点
			{
				if (n1 == -1)
					n1 = i;
				else
					n2 = i;
			}
		}
		for (i = 0; i<24; i++)//small
		{
			if (Node2[i].i == nFromX && Node2[i].j == nFromY)
			{
				if (p1 == -1)
					p1 = i;
				else
					p2 = i;
			}
			if (Node2[i].i == nToX && Node2[i].j == nToY)
			{
				if (q1 == -1)
					q1 = i;
				else
					q2 = i;
			}
		}
		if (m1 != -1 && n1 != -1)
		{
			flag = 0;
			arc = 0;
			for (i = m1; i != n1; i = (i + 1) % 24)
			{
				if (Node1[i].color != 0 && i != m1)
					flag = 1;//有阻挡
				if (Node1[i].arc == 1)
					arc = 1;//有弧
			}
			if (!(flag == 0 && arc == 1))
			{
				flag = 0; arc = 0;
				for (i = n1; i != m1; i = (i + 1) % 24)
				{
					if (Node1[i].color != 0 && i != n1)
						flag = 1;
					if (Node1[i].arc == 1)
						arc = 1;
				}
			}
			if (!(flag == 0 && arc == 1))
			{
				if (n2 != -1)
				{
					flag = 0; arc = 0;
					for (i = n2; i != m1; i = (i + 1) % 24)
					{
						if (Node1[i].color != 0 && i != n2)
							flag = 1;
						if (Node1[i].arc == 1)
							arc = 1;
					}
					if (!(flag == 0 && arc == 1))
					{
						flag = 0, arc = 0;
						for (i = m1; i != n2; i = (i + 1) % 24)
						{
							if (Node1[i].color != 0 && i != m1)
								flag = 1;
							if (Node1[i].arc == 1)
								arc = 1;
						}
					}
				}
				if (!(flag == 0 && arc == 1))
				{
					if (m2 != -1)
					{
						flag = 0; arc = 0;
						for (i = m2; i != n1; i = (i + 1) % 24)
						{
							if (Node1[i].color != 0 && i != m2)
								flag = 1;
							if (Node1[i].arc == 1)
								arc = 1;
						}
						if (!(flag == 0 && arc == 1))
						{
							flag = 0; arc = 0;
							for (i = n1; i != m2; i = (i + 1) % 24)
							{
								if (Node1[i].color != 0 && i != n1)
									flag = 1;
								if (Node1[i].arc == 1)
									arc = 1;
							}
						}
						if (!(flag == 0 && arc == 1))
						{
							if (n2 != -1)
							{
								flag = 0; arc = 0;
								for (i = m2; i != n2; i = (i + 1) % 24)
								{
									if (Node1[i].color != 0 && i != m2)
										flag = 1;
									if (Node1[i].arc == 1)
										arc = 1;
								}
								if (!(flag == 0 && arc == 1))
								{
									flag = 0; arc = 0;
									for (i = n2; i != m2; i = (i + 1) % 24)
									{
										if (Node1[i].color != 0 && i != n2)
											flag = 1;
										if (Node1[i].arc == 1)
											arc = 1;
									}
								}
							}
						}
					}
				}
			}
		}
		if (q1 != -1 && p1 != -1 && !(flag == 0 && arc == 1))//小圈
		{

			flag = 0;
			arc = 0;
			for (i = p1; i != q1; i = (i + 1) % 24)
			{
				if (Node2[i].color != 0 && i != p1)
					flag = 1;
				if (Node2[i].arc == 1)
					arc = 1;
			}
			if (!(flag == 0 && arc == 1))
			{
				flag = 0; arc = 0;
				for (i = q1; i != p1; i = (i + 1) % 24)
				{
					if (Node2[i].color != 0 && i != q1)
						flag = 1;
					if (Node2[i].arc == 1)
						arc = 1;
				}
			}
			if (!(flag == 0 && arc == 1))
			{
				if (q2 != -1)
				{
					flag = 0; arc = 0;
					for (i = q2; i != p1; i = (i + 1) % 24)
					{
						if (Node2[i].color != 0 && i != q2)
							flag = 1;
						if (Node2[i].arc == 1)
							arc = 1;
					}
					if (!(flag == 0 && arc == 1))
					{
						flag = 0, arc = 0;
						for (i = p1; i != q2; i = (i + 1) % 24)
						{
							if (Node2[i].color != 0 && i != p1)
								flag = 1;
							if (Node2[i].arc == 1)
								arc = 1;
						}
					}
				}
				if (!(flag == 0 && arc == 1))
				{
					if (p2 != -1)
					{
						flag = 0; arc = 0;
						for (i = p2; i != q1; i = (i + 1) % 24)
						{
							if (Node2[i].color != 0 && i != p2)
								flag = 1;
							if (Node2[i].arc == 1)
								arc = 1;
						}
						if (!(flag == 0 && arc == 1))
						{
							flag = 0; arc = 0;
							for (i = q1; i != p2; i = (i + 1) % 24)
							{
								if (Node2[i].color != 0 && i != q1)
									flag = 1;
								if (Node2[i].arc == 1)
									arc = 1;
							}
						}
						if (!(flag == 0 && arc == 1))
						{
							if (q2 != -1)
							{
								flag = 0; arc = 0;
								for (i = p2; i != q2; i = (i + 1) % 24)
								{
									if (Node2[i].color != 0 && i != p2)
										flag = 1;
									if (Node2[i].arc == 1)
										arc = 1;
								}
								if (!(flag == 0 && arc == 1))
								{
									flag = 0; arc = 0;
									for (i = q2; i != p2; i = (i + 1) % 24)
									{
										if (Node2[i].color != 0 && i != q2)
											flag = 1;
										if (Node2[i].arc == 1)
											arc = 1;
									}
								}
							}
						}
					}
				}
			}
		}

		if (flag == 0 && arc == 1)
		{
			position[nFromX][nFromY] = type; return TRUE;
		}

		else
		{
			position[nFromX][nFromY] = type; return FALSE;
		}
	}
	else
		return FALSE;
}

int CMoveGenerator::AddMove(int nFromX,int nFromY,int nToX,int nToY,int nPly)
{
	
	if(rand()%4==1)
	{
		m_nMoveList[nPly][m_nMoveCount].From.x=m_nMoveList[nPly][0].From.x;
		m_nMoveList[nPly][m_nMoveCount].From.y=m_nMoveList[nPly][0].From.y;
		m_nMoveList[nPly][m_nMoveCount].To.x=m_nMoveList[nPly][0].To.x;
		m_nMoveList[nPly][m_nMoveCount].To.y=m_nMoveList[nPly][0].To.y;
		m_nMoveList[nPly][0].From.x=nFromX;
		m_nMoveList[nPly][0].From.y=nFromY;
		m_nMoveList[nPly][0].To.x=nToX;
		m_nMoveList[nPly][0].To.y=nToY;
	}
	else
	{
 		m_nMoveList[nPly][m_nMoveCount].From.x=nFromX;
		m_nMoveList[nPly][m_nMoveCount].From.y=nFromY;
		m_nMoveList[nPly][m_nMoveCount].To.x=nToX;
		m_nMoveList[nPly][m_nMoveCount].To.y=nToY;
		
	}
	m_nMoveCount++;
	return m_nMoveCount;
}


int CMoveGenerator::CreatePossibleMove(BYTE position[6][6],int nPly,int nSide)//nside代表产生哪一方的走法
{	    
	int i,j,m,n;

	m_nMoveCount=0;

	for (i=0;i<6;i++)
	{
		for (j=0;j<6;j++)
		{
			if(position[i][j]==1&& nSide==1 || position[i][j]==2 &&nSide==0)
			{
				for(m=0;m<6;m++)
					for (n=0;n<6;n++)
					{
						if (position[i][j]-position[m][n])
						{
							
							if(IsValidMove(position, i, j, m, n))
								AddMove(i,j,m,n,nPly);							
						}
					}
			}
			
		}
	}
	
	return m_nMoveCount;//返回总的走法数
}
