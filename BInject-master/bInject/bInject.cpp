
// bInject.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "bInject.h"
#include "bInjectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CbInjectApp

BEGIN_MESSAGE_MAP(CbInjectApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CbInjectApp ����

CbInjectApp::CbInjectApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CbInjectApp ����

CbInjectApp theApp;


// CbInjectApp ��ʼ��

BOOL CbInjectApp::InitInstance()
{
	WNDCLASS wc;
	// ��ȡ��������Ϣ��MFCĬ�ϵ����жԻ���Ĵ�������Ϊ #32770
	::GetClassInfo(AfxGetInstanceHandle(), _T("#32770"), &wc);
	// �ı䴰������
	wc.lpszClassName = _T("bInjectHelper");
	// ע���´����࣬ʹ������ʹ����
	AfxRegisterClass(&wc);

	CWinApp::InitInstance();

	//AfxRegisterClass(&wc);
	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CbInjectDlg dlg;
	m_pMainWnd = &dlg;
	//m_pMainWnd->DragAcceptFiles(TRUE);
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}


