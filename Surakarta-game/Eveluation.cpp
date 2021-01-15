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
int CEveluation::Eveluate(BYTE position[6][6], BOOL IsBlackturn)//��λ����Ϣ���ֵ�˭����
{
	int BlackValue=0,RedValue=0;//��ʼ����ֵ��¼
	int BProtectValue=0,BAttactValue=0;//�ڹ�ֵ
	int RProtectValue=0,RAttactValue=0;//���ֵ
	int i,j;
	GetAttackInfo(position);//����ǰ�����attack
	GetProtectInfo(position);//����ǰ�����attack
	for (i=0;i<6;i++)
	{
		for (j=0;j<6;j++)
		{
			if (position[i][j]==1)//�˴��Ǻ���
			{

				if(i==4&&j==1 || i==1&&j==1 || i==4&&j==4 || i==1&&j==4 || i==2&&j==3 || i==2&&j==2 || i==3&&j==2 || i==3&&j==3 )
					BlackValue+=150;//��Ҫ��������㹲8��
				else if(i==0&&j==0|| i ==5 &&j == 5|| i ==0 &&j ==5 || i ==5 &&j ==0 )
					BlackValue+=90;
				else
					BlackValue=BlackValue+100;//������ռ�ݵ�����λ���ϵĵ�
				BProtectValue=BProtectValue+m_ProtectPos[i][j];
				BAttactValue=BAttactValue+m_AttackPos[i][j];
			}
			if(position[i][j]==2)//�˴��Ǻ��ӣ���������������//һֱ��black���ɼ��������Һ�����߼��ϵĸ���
			{
				RedValue=RedValue+100;//������ռ�ݵ�����λ���ϵĵ�
				RProtectValue=RProtectValue+m_ProtectPos[i][j];//����Ҫ֪���Է�ռ���˼�㣬��Ϊ�Է��ڼ�����޷��ı�ʲô��������Ϣ���ں��ӵı�������ʱ�Ѿ���������
				RAttactValue=RAttactValue+m_AttackPos[i][j];
			}
		}
	}

	if (IsBlackturn)//���ֵ���������ʱ
	{
		for (i=0;i<6;i++)
		{
			for(j=0;j<6;j++)
			{
				if(position[i][j]==2)//�˴��Ǻ���
				{
					if (m_AttackPos[i][j]-m_ProtectPos[i][j]>0)//�������ٱ������
						BlackValue=BlackValue+100;//������ж���ֵ
					if(m_AttackPos[i][j]-m_ProtectPos[i][j]==0)//���ӷ����뱣����ͬ
						RedValue=RedValue+50;//�����ж���ֵ���
				}
				if(position[i][j]==1)//�˴��Ǻ���
					if(m_ProtectPos[i][j]-m_AttackPos[i][j]<0)//�������ٱ������
						BlackValue=BlackValue-50;//���Ӳ����ٶ�
			
			}   
		}
	}
	else//���ֵ���������ʱ
	{
		for (i=0;i<6;i++)
		{
			for (j=0;j<6;j++)
			{
				if (position[i][j]==1)//�˴��Ǻ���
				{
					if(m_AttackPos[i][j]-m_ProtectPos[i][j]>0)//�������ٱ��Է���
						RedValue=RedValue+100;//������ж���ֵ
					if(m_AttackPos[i][j]-m_ProtectPos[i][j]>0)//���ӷ����뱣����ͬ
						BlackValue=BlackValue+50;//�����ж���ֵ���
				}
				if (position[i][j]==2)//�˴��Ǻ���
				{
					if(m_ProtectPos[i][j]-m_AttackPos[i][j]<0)//�������ٱ������
						RedValue=RedValue-50;//���Ӳ����ٶ�
				}
			}
		}
	}
	BlackValue=BlackValue-BAttactValue+BProtectValue;
	RedValue=RedValue+RProtectValue-RAttactValue;
	if (IsBlackturn)//�ߺ���
		return BlackValue-RedValue;//��-��
	else//�ߺ���
		return RedValue-BlackValue;//��-��
}




void CEveluation::GetAttackInfo(BYTE position[6][6])
{
	short int CurPosition[6][6];//������
	memset(m_AttackPos,0,36);//����ά����A��λ�ö�����
    memcpy(CurPosition,position,36);//����ǰ���渴ֵ��C������
	int flag=1,i,j,m,n;
	for (i=0;i<6;i++)
	{
		for (j=0;j<6;j++)
		{
			for (m=0;m<6;m++)
			{
				for(n=0;n<6;n++)
				{
					while (flag)//ִֻ��һ�ε�ѭ��
					{
						flag=0;
						if(m_pMg->IsValidMove(CurPosition,m,n,i,j) && CurPosition[m][n]+CurPosition[i][j]==3)//����1������2������0
						{
							m_AttackPos[i][j]++;//λ�ù���ֵ�ۼ�
							if(!m_pMg->IsValidMove(CurPosition,i,j,m,n))//�������ϱ��Եķ��գ������һ�
							{
								m_AttackPos[i][j]+=100;//λ�ù���ֵ����
								continue;
								
							}
							flag=1;//�ٴ�ѭ��
							n=-1;//��֤����ֵ���ظ��ۼ�++
							m=0;
							CurPosition[m][n]=0;//�����ַ���������������洢�ռ���׵�ַ����ǰƫ��һ����λ(Ҳ����ƫ��һ����ǰ������������Ӧ���ֽ���)����Ӧ�ĵ�ַ�������ַ����û�и�������ռ�һ���ʼ����
						}
					}
				}
			}
			memcpy(CurPosition,position,36);//����ǰ���渴ֵ��C������
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
						if(CurPosition[m][n]-CurPosition[i][j]==0 &&CurPosition[m][n])//��ͬ����Ӫ�����ӣ��ɾ�·��ȫ��ͬһ��
						{
							CurPosition[m][n]=3-CurPosition[i][j];//������ʼλ�û��ɶԼң��Լҿ��Գ����Լ�������ʵ����Ǽ���ռ�ţ����԰�ȫ
							if(m_pMg->IsValidMove(CurPosition,m,n,i,j))//�Ϸ�����
							{
								m_ProtectPos[i][j]++;//���Ӱ�ȫֵ
								flag=1;
								n=-1;
								m=0;
								CurPosition[m][n]=0;
							}
						}
					}
				}
			}
			memcpy(CurPosition,position,36);//���̵Ŀ�ʼλ�ò��䣬������λ�ò��ϱ仯
		}
	}
}
//��ǿ�����Ե�ֵ���Ա�Ϊ+2