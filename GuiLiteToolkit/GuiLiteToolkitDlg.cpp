
// GuiLiteToolkitDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GuiLiteToolkit.h"
#include "GuiLiteToolkitDlg.h"

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CGuiLiteToolkitDlg dialog
CGuiLiteToolkitDlg::CGuiLiteToolkitDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GUILITETOOLKIT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

BEGIN_MESSAGE_MAP(CGuiLiteToolkitDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CGuiLiteToolkitDlg::OnTabChanged)
END_MESSAGE_MAP()


// CGuiLiteToolkitDlg message handlers

BOOL CGuiLiteToolkitDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_tab = (CTabCtrl*)GetDlgItem(IDC_TAB1);
	m_fontDlg.Create(IDD_DIALOG_FONT, m_tab);
	m_bitmapDlg.Create(IDD_DIALOG_BITMAP, m_tab);
	m_tab->InsertItem(0, L"Font");
	m_tab->InsertItem(1, L"Bitmap");
	m_tab->SetCurSel(0);
	OnTabChanged(NULL, NULL);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGuiLiteToolkitDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGuiLiteToolkitDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGuiLiteToolkitDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CGuiLiteToolkitDlg::OnTabChanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	CRect rc;
	m_tab->GetClientRect(&rc);
	rc.top += 20;

	switch (m_tab->GetCurSel())
	{
	case 0:
		m_bitmapDlg.ShowWindow(SW_HIDE);
		m_fontDlg.MoveWindow(&rc);
		m_fontDlg.ShowWindow(SW_SHOW);
		break;
	case 1:
		m_fontDlg.ShowWindow(SW_HIDE);
		m_bitmapDlg.MoveWindow(&rc);
		m_bitmapDlg.ShowWindow(SW_SHOW);
		break;
	default:
		break;
	}
}
