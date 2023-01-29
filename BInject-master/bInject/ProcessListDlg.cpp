// ProcessList.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "bInject.h"
#include "ProcessListDlg.h"
#include "afxdialogex.h"
#include <tlhelp32.h>
#include <windows.h>
#include "ProcessFunc.h"
#include "Utils.h"
using namespace std;




// CProcessListDlg �Ի���

IMPLEMENT_DYNAMIC(CProcessListDlg, CDialogEx)

CProcessListDlg::CProcessListDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PROCESS_DIALOG, pParent)
{

}

CProcessListDlg::~CProcessListDlg()
{
}

void CProcessListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PROCESS, m_list_process);
	DDX_Control(pDX, IDC_LIST_MODULE, m_list_module);
	
}


BEGIN_MESSAGE_MAP(CProcessListDlg, CDialogEx)
	//ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_PROCESS, &CProcessListDlg::OnLvnItemchangedListProcess)
	ON_NOTIFY(NM_CLICK, IDC_LIST_PROCESS, &CProcessListDlg::OnNMClickListProcess)
	ON_BN_CLICKED(IDBTN_PROCESS_SELECT, &CProcessListDlg::OnBnClickedProcessSelect)
	ON_BN_CLICKED(IDBTN_PROCESS_REFRESH, &CProcessListDlg::OnBnClickedProcessRefresh)
	ON_BN_CLICKED(IDC_BUTTON_UNINSTALL_DLL, &CProcessListDlg::OnBnClickedButtonUninstallDll)
	ON_EN_CHANGE(IDC_EDIT_PROCESS_TIPS, &CProcessListDlg::OnEnChangeEditProcessTips)
	ON_BN_CLICKED(IDC_BUTTON_SUSPEND_THREAT, &CProcessListDlg::OnBnClickedButtonSuspendThreat)
	ON_BN_CLICKED(IDC_BUTTON_RESUME_THREAT, &CProcessListDlg::OnBnClickedButtonResumeThreat)
END_MESSAGE_MAP()


// CProcessListDlg ��Ϣ�������
BOOL CProcessListDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CRect rect;

	// �����б��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	m_list_process.GetClientRect(&rect);
	// Ϊ�����б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_list_process.SetExtendedStyle(m_list_process.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES| LVS_SHOWSELALWAYS);
	CString itemArray[] = { CString("����ID"),CString("�ļ���"),CString("����"),CString("·��") };
	// Ϊ�����б���ͼ�ؼ������ 
	int arrayLen = sizeof(itemArray) / sizeof(CString);
	for (int index = 0; index <arrayLen; index++) {
		if (index==0){
		m_list_process.InsertColumn(index, itemArray[index], LVCFMT_LEFT, (rect.Width() / arrayLen)*0.5,index);
		}else if (index == 3) {
			m_list_process.InsertColumn(index, itemArray[index], LVCFMT_LEFT, (rect.Width() / arrayLen)*1.5, index);
		}
		else {
			m_list_process.InsertColumn(index, itemArray[index], LVCFMT_LEFT, (rect.Width() / arrayLen), index);
		}
	}


	// ģ���б��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	m_list_module.GetClientRect(&rect);
	// Ϊģ���б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_list_module.SetExtendedStyle(m_list_module.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES| LVS_SHOWSELALWAYS);
	CString moduleItemArray[] = { CString("ģ��"),CString("ӳ���ַ"),CString("ӳ���С") };
	// Ϊģ���б���ͼ�ؼ�������� 
	 arrayLen = sizeof(moduleItemArray) / sizeof(CString);
	for (int index = 0; index <arrayLen; index++) {
		if (index == 0) {
			m_list_module.InsertColumn(index, moduleItemArray[index], LVCFMT_LEFT, (rect.Width() / arrayLen + 1)*1.6, index);
		}
		else {
			m_list_module.InsertColumn(index, moduleItemArray[index], LVCFMT_LEFT, (rect.Width() / arrayLen + 1)*0.7, index);
		}
	}
	//��ȡ�����б�����
	this->InitListItem();
	return TRUE;
}

void CProcessListDlg::InitListItem() {
	map<DWORD, ProcessInfo> processMap = GetProcessList();
	map<DWORD, ProcessInfo>::iterator it;
	int index = 0, imageIndex = 0;
	CImageList *m_ImageList = new CImageList();
	m_ImageList->Create(16, 16, ILC_COLOR32, 0, 1);
	for (it = processMap.begin(); it != processMap.end(); it++) {
		CString PID;
		PID.Format("%d", (it->first));
		if (it->second.ImagePath != "") {
			HICON icon = fileIcon(it->second.ImagePath);
			m_ImageList->Add(icon);
			m_list_process.SetImageList(m_ImageList, LVSIL_SMALL);
			LVITEM lvItem;
			lvItem.mask = LVIF_IMAGE | LVIF_TEXT;
			lvItem.iImage = imageIndex;
			lvItem.iItem = index;
			lvItem.iSubItem = 0;
			lvItem.pszText = PID.GetBuffer();
			m_list_process.InsertItem(&lvItem);
			imageIndex++;

		}
		else {
			m_list_process.InsertItem(index, PID);
		}
		m_list_process.SetItemText(index, 1, it->second.FileName);
		m_list_process.SetItemText(index, 2, it->second.WindowsTitle);
		m_list_process.SetItemText(index, 3, it->second.ImagePath);
		index++;
	}
}



void CProcessListDlg::OnNMClickListProcess(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strProcessID;    // ѡ��Ľ��� strProcessName,  
	NMLISTVIEW *pNMListView = (NMLISTVIEW*)pNMHDR;
	*pResult = 0;
	//m_list_process
	if (-1 != pNMListView->iItem)        // ���iItem����-1����˵�����б��ѡ��   
	{
		// ��ȡ��ѡ���б����PID��ProcessName 
		strProcessID = m_list_process.GetItemText(pNMListView->iItem, 0);
		strProcessName = m_list_process.GetItemText(pNMListView->iItem, 1);
		//DWORD pid= _ttoi(strProcessID);
		selectProcessID= _ttoi(strProcessID);
		//SetDlgItemText(IDC_EDIT_PROCESS_TIPS, strProcessName);
		selectProcessWPARAM = (WPARAM)strProcessName.GetString();
		InitModalIndirect(selectProcessID);
	}
}


void CProcessListDlg::InitModalIndirect(DWORD PID) 
{
	m_list_module.DeleteAllItems();
	map<DWORD, ModuleInfo> moduleMap = GetProcessModule(PID);
	map<DWORD, ModuleInfo>::iterator it;
	int index = 0;
	for (it = moduleMap.begin(); it != moduleMap.end(); it++) {
		m_list_module.InsertItem(index,it->second.ModuleName);
		m_list_module.SetItemText(index, 1, it->second.ImageBaseAddress);
		m_list_module.SetItemText(index, 2, it->second.ImageBaseSize);
		index++;
	}
	


}




void CProcessListDlg::OnBnClickedProcessSelect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (selectProcessID > 0&& selectProcessWPARAM!=NULL) {
	HWND DLG1Hwnd = ::FindWindow("bInjectHelper", NULL);
	::SendMessage(DLG1Hwnd, WM_CHOOSEPROCESS, selectProcessWPARAM, (LPARAM)selectProcessID);
	this->DestroyWindow();
	this->OnClose();
	}
	else {
		MessageBox("û��ѡ�н���!");
	}
}


void CProcessListDlg::OnBnClickedProcessRefresh()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_list_process.DeleteAllItems();
	m_list_module.DeleteAllItems();
	this->InitListItem();
}


void CProcessListDlg::OnBnClickedButtonUninstallDll()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	CString str,str1;
	BOOL uninstallFlag = true;
	POSITION pos = m_list_module.GetFirstSelectedItemPosition(); //posѡ�е�����λ��
	if (pos == NULL|| selectProcessID<=0)
		AfxMessageBox("��û��ѡ��ģ��DLL!");
	else
	{
		while (pos)   //�����ѡ�����
		{
			int nIdx = -1;
			nIdx = m_list_module.GetNextSelectedItem(pos);
			if (nIdx >= 0 && nIdx<m_list_module.GetItemCount())
			{
				
				str = m_list_module.GetItemText(nIdx, 1);//��ȡָ���У�Ϊ�ַ�����ʽ
				DWORD baseAddress;
				sscanf(str.GetBuffer(), "%x", &baseAddress);//strtol(str.GetString(), &charBaseAddress, 16);
				uninstallFlag= UnInjectDll(selectProcessID, (LPVOID)baseAddress);

			}
		}
		if (uninstallFlag) {
			MessageBox("��ж������ѡ�е�DLL!");
		}
		else {
			MessageBox("��ж�ز���ѡ�е�DLL!");
		}
	}
}


void CProcessListDlg::OnEnChangeEditProcessTips()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int itemCount=m_list_process.GetItemCount();
	CString searchKey;
	GetDlgItemTextA(IDC_EDIT_PROCESS_TIPS, searchKey);
	if (searchKey != "") {		
	for (int index = 0; index < itemCount; index++) {
		m_list_process.SetItemState(index, 0, -1);
		CString itemValue = m_list_process.GetItemText(index, 1);
		if (itemValue.Find(searchKey)>=0) {
			m_list_process.SetItemState(index, LVIS_SELECTED| LVNI_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
			m_list_process.EnsureVisible(index, FALSE);
			}
		}
	}
}


void CProcessListDlg::OnBnClickedButtonSuspendThreat()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������	
	if (SuspendProcess(selectProcessID, TRUE) == 1) {
	MessageBox("Ŀ������ѹ���!");
	}
	else {
		MessageBox("Ŀ��������ǹ���״̬!");
	}
}


void CProcessListDlg::OnBnClickedButtonResumeThreat()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (SuspendProcess(selectProcessID, FALSE) == 1) {
	MessageBox("Ŀ������ѻָ�!");
	}
	else {
		MessageBox("Ŀ�������������״̬!");
	}
}
