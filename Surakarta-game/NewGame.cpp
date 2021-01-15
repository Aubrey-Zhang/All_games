// NewGame.cpp : implementation file
//

#include "stdafx.h"
#include "Surakarta.h"
#include "NewGame.h"
#include <iomanip>
#include <fstream>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
using namespace std;
/////////////////////////////////////////////////////////////////////////////
// CNewGame dialog


CNewGame::CNewGame(CWnd* pParent /*=NULL*/)
	: CDialog(CNewGame::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewGame)
	m_nEdit = 0;
	//}}AFX_DATA_INIT
}


void CNewGame::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewGame)
	DDX_Control(pDX, IDC_LISTENGINE, m_SearchEngineList);
	DDX_Control(pDX, IDC_PLY, m_SetPly);
	DDX_Text(pDX, IDC_EDIT1, m_nEdit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewGame, CDialog)
	//{{AFX_MSG_MAP(CNewGame)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewGame message handlers

BOOL CNewGame::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_SearchEngineList.AddString("NegaScout search Engine");
	m_SearchEngineList.SetCurSel(0);
	m_SetPly.SetRange(1,12);
	m_SetPly.SetPos(7);
	m_nEdit = m_SetPly.GetPos();
	ofstream f1("./SU.txt");
	f1<<"#2018-08-04|"<<endl;
	f1<<"#先手方:1队|后手方:2队|"<<endl;
	f1.close();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNewGame::OnOK() 
{
	// TODO: Add extra validation here
	
	m_nSelectedEngine=m_SearchEngineList.GetCurSel();
	m_nSelectedPly=m_SetPly.GetPos();
	CDialog::OnOK();
}
