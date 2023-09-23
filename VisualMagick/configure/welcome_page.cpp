// welcome_page.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "welcome_page.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CWelcomePage, CPropertyPage)


/////////////////////////////////////////////////////////////////////////////
// CWelcomePage property page

CWelcomePage::CWelcomePage() : CPropertyPage(CWelcomePage::IDD)
{
	//{{AFX_DATA_INIT(CWelcomePage)
	m_welcomeText = _T("");
	//}}AFX_DATA_INIT
}

CWelcomePage::~CWelcomePage()
{
}

void CWelcomePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWelcomePage)
	DDX_Text(pDX, IDC_WELCOME_TEXT, m_welcomeText);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWelcomePage, CPropertyPage)
	//{{AFX_MSG_MAP(CWelcomePage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



BOOL CWelcomePage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	m_welcomeText  =
	"Welcome!\n"
	"\n"
	"This is the VisualMagick configuration wizard. It will set up your "
	"GraphicsMagick build environment and customize the build process "
	"for your needs. It's purpose is to create Visual Studio 2003 solution "
	"(SLN) and project files (VCPROJ) which are upgraded using the version "
	"of Visual Studio actually used.\n"
	"\n"
	"When the build environment has been created and upgraded, you can build "
	"the system in the Visual Studio IDE.\n"
	"\n"
	"NOTE: You cannot compile GraphicsMagick with Visual Studio older than "
	"2008 and Visual Studio 2013 or later is required to compile 64 bit code.\n"
	"\n"
	"Good Luck - and thanks for all the fish!";

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CWelcomePage::OnSetActive() 
{
	CPropertySheet* psheet = (CPropertySheet*) GetParent();
	psheet->SetWizardButtons(PSWIZB_NEXT);
	
	return CPropertyPage::OnSetActive();
}

// vim: set ts=8 sts=8 sw=8 noet:

// Local Variables:
// mode: c
// c-basic-offset: 8
// fill-column: 78
// indent-tabs-mode: true
// End:
