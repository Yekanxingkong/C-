
// bInjectDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"



// CbInjectDlg �Ի���
class CbInjectDlg : public CDialogEx
{
// ����
public:
	CbInjectDlg(CWnd* pParent = NULL);	// ��׼���캯��
	
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BINJECT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tab;
	//CComboBox m_process_combo;
	afx_msg void OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void ChooseProcess(WPARAM wParam, LPARAM lParam);
	void InitTabControl();
	int m_CurSelTab;
	CInjectDllDlg m_page1;
	CInjectCodeDlg m_page2;
	CDialog* pDialog[2];  //��������Ի������ָ��
};


