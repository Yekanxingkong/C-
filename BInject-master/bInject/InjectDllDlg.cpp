// InjectDllDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "bInject.h"
#include "InjectDllDlg.h"
#include "afxdialogex.h"
#include "ProcessFunc.h"
#include "ProcessListDlg.h"
#include "Utils.h"

// CInjectDllDlg �Ի���

IMPLEMENT_DYNAMIC(CInjectDllDlg, CDialogEx)

CInjectDllDlg::CInjectDllDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_INJECT_DLL_DIALOG, pParent)
{
	
}

CInjectDllDlg::~CInjectDllDlg()
{
}

void CInjectDllDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_COMBO_PROCESS1, m_process_combo);
	DDX_Control(pDX, IDC_EDIT_DLG1_PROCESS, m_edit_process);
	DDX_Control(pDX, IDC_EDIT_DLG1_PROCESS_ID, m_edit_process_id);
	DDX_Control(pDX, IDC_EDIT_DLL_PATH, m_edit_dll_path);
}


BEGIN_MESSAGE_MAP(CInjectDllDlg, CDialogEx)
	ON_BN_CLICKED(ID_INJECT_DLL_BTN, &CInjectDllDlg::OnBnClickedInjectDllBtn)
	ON_BN_CLICKED(ID_BUTTON_OPEN_PROCESS_DLG, &CInjectDllDlg::OnBnClickedButtonOpenProcessDlg)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()

BOOL CInjectDllDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	
	return TRUE;
}


// CInjectDllDlg ��Ϣ�������





void CInjectDllDlg::OnBnClickedInjectDllBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strDllPath, strProcessID;
	m_edit_dll_path.GetWindowTextA(strDllPath);
	m_edit_process_id.GetWindowTextA(strProcessID);
	DWORD processID = _ttoi(strProcessID);
	if (strProcessID == ""||processID<=0) {
		MessageBox("��ѡ��Ҫע��Ľ���!", _T("��ܰ��ʾ"));
		return;
	}
	if( strDllPath != ""){
	
		if (injectDll(processID, strDllPath.GetBuffer())){
			MessageBox(strDllPath+"ע��ɹ�!");
		}	
	}
	else {
		MessageBox("��������Ҫע���DLL�ļ�!", _T("��ܰ��ʾ"));
	}
}


void CInjectDllDlg::OnBnClickedButtonOpenProcessDlg()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HWND myHwnd=this->GetSafeHwnd();
	CProcessListDlg *processDlg = new  CProcessListDlg;
	processDlg->parentHwnd = myHwnd;
	processDlg->Create(IDD_PROCESS_DIALOG, this);
	processDlg->ShowWindow(SW_SHOW);
}




void CInjectDllDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	UINT nCount;
	TCHAR szPath[MAX_PATH];
	CString dropFile;
	nCount = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
	if (nCount)
	{
		for (UINT nIndex = 0; nIndex < nCount; ++nIndex)
		{
			DragQueryFile(hDropInfo, nIndex, szPath, _countof(szPath));
			dropFile = szPath;
			if (dropFile.Find(".dll") > 0) {
			m_edit_dll_path.SetWindowTextA(dropFile);
			}
			else {
				MessageBox("ֻ֧��DLL��׺,��������Ҫע���DLL�ļ�!", _T("WM_DROPFILES"));
			}
		}
	}

	DragFinish(hDropInfo);
	CDialogEx::OnDropFiles(hDropInfo);
}
