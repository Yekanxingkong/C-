
// bInjectDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "bInject.h"
#include "bInjectDlg.h"
#include "afxdialogex.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//��������


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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



// CbInjectDlg �Ի���



CbInjectDlg::CbInjectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_BINJECT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CbInjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_MAIN, m_tab);

}

BEGIN_MESSAGE_MAP(CbInjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, &CbInjectDlg::OnTcnSelchangeTabMain)
	ON_MESSAGE(WM_CHOOSEPROCESS, (LRESULT(__thiscall CWnd::*)(WPARAM, LPARAM))ChooseProcess)
END_MESSAGE_MAP()


// CbInjectDlg ��Ϣ�������

BOOL CbInjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	this->InitTabControl();
	if (PathFileExistsA("SkinH.dll") && PathFileExistsA("skinh.she")) {
		typedef int(*DLL_SkinH_Attach)();
		HINSTANCE m_myDllHInst = LoadLibrary("SkinH.dll");
		if (m_myDllHInst == NULL)
		{
			FreeLibrary(m_myDllHInst);
			return TRUE;
		}
		DLL_SkinH_Attach ddl_SkinH_Attach = (DLL_SkinH_Attach)GetProcAddress(m_myDllHInst, "SkinH_Attach");
		if (ddl_SkinH_Attach == NULL)
		{
			FreeLibrary(m_myDllHInst);
			return TRUE;
		}
		ddl_SkinH_Attach();
		//FreeLibrary(m_myDllHInst);
		//SkinH_Attach();
		//::SkinH_AttachEx("skinh.she", NULL);
	}
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CbInjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CbInjectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CbInjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CbInjectDlg::OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//�ѵ�ǰ��ҳ����������
	pDialog[m_CurSelTab]->ShowWindow(SW_HIDE);
	//�õ��µ�ҳ������
	m_CurSelTab = m_tab.GetCurSel();
	//���µ�ҳ����ʾ����
	pDialog[m_CurSelTab]->ShowWindow(SW_SHOW);

	*pResult = 0;
}

void  CbInjectDlg::InitTabControl() 
{
	m_tab.InsertItem(0, _T("ע��DLL"));
	m_tab.InsertItem(1, _T("ע����"));
	//���������Ի���
	m_page1.Create(IDD_INJECT_DLL_DIALOG, &m_tab);
	m_page2.Create(IDD_INJECT_CODE_DIALOG, &m_tab);
	//�趨��Tab����ʾ�ķ�Χ
	CRect rc;
	m_tab.GetClientRect(rc);
	rc.top += 20;
	rc.bottom -= 0;
	rc.left += 0;
	rc.right -= 0;
	
	m_page1.MoveWindow(&rc);
	m_page2.MoveWindow(&rc);

	//�ѶԻ������ָ�뱣������
	pDialog[0] = &m_page1;
	pDialog[1] = &m_page2;
	//��ʾ��ʼҳ��
	pDialog[0]->ShowWindow(SW_SHOW);
	pDialog[1]->ShowWindow(SW_HIDE);
	//���浱ǰѡ��
	m_CurSelTab = 0;
}

void CbInjectDlg::ChooseProcess(WPARAM wParam, LPARAM lParam)
{
	CString msgName,msgID;
	//msg = (char*)wParam;
	msgName.Format("%s",wParam);
	msgID.Format("%d", (LPARAM)lParam);
	m_page1.m_edit_process.SetWindowText(msgName);
	m_page1.m_edit_process_id.SetWindowText(msgID);
	m_page2.m_edit_process.SetWindowText(msgName);
	m_page2.m_edit_process_id.SetWindowText(msgID);
	pDialog[0]->UpdateWindow();
}