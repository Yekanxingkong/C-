#pragma once
#include "afxwin.h"


// CInjectDllDlg �Ի���

class CInjectDllDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInjectDllDlg)

public:
	CInjectDllDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInjectDllDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INJECT_DLL_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:	
	afx_msg void OnBnClickedInjectDllBtn();
	afx_msg void OnBnClickedButtonOpenProcessDlg();
	CEdit m_edit_process;
	CEdit m_edit_process_id;
	afx_msg void OnDropFiles(HDROP hDropInfo);
	CEdit m_edit_dll_path;
};
