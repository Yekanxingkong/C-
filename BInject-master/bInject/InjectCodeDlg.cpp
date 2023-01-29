// InjectCodeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "bInject.h"
#include "InjectCodeDlg.h"
#include "afxdialogex.h"
#include "ProcessFunc.h"
#include "ProcessListDlg.h"
#include "Utils.h"
#include <vector>

HINSTANCE m_XEDParseInst;
myXEDParseAssembleFunc mXEDParseAssemble;
// CInjectCodeDlg �Ի���

IMPLEMENT_DYNAMIC(CInjectCodeDlg, CDialogEx)

CInjectCodeDlg::CInjectCodeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_INJECT_CODE_DIALOG, pParent)
{

}

CInjectCodeDlg::~CInjectCodeDlg()
{
}

void CInjectCodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_DLG1_PROCESS, m_edit_process);
	DDX_Control(pDX, IDC_EDIT_DLG1_PROCESS_ID, m_edit_process_id);
	DDX_Control(pDX, IDC_EDIT_DLL_PATH, m_edit_code);
	DDX_Control(pDX, IDC_EDIT_OPCODE, m_edit_opcode);
}


BEGIN_MESSAGE_MAP(CInjectCodeDlg, CDialogEx)
	ON_BN_CLICKED(ID_BUTTON_OPEN_PROCESS_DLG, &CInjectDllDlg::OnBnClickedButtonOpenProcessDlg)
	ON_BN_CLICKED(IDOK, &CInjectCodeDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CInjectCodeDlg::OnBnClickedCancel)
	ON_BN_CLICKED(ID_GENERATE_CODE, &CInjectCodeDlg::OnBnClickedGenerateCode)
END_MESSAGE_MAP()


// CInjectCodeDlg ��Ϣ�������
BOOL CInjectCodeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	if (PathFileExistsA("Lib/XEDParse_dll/x32/XEDParse.dll")){
		m_XEDParseInst = LoadLibrary("Lib/XEDParse_dll/x32/XEDParse.dll");
		if (m_XEDParseInst == NULL)
		{
			FreeLibrary(m_XEDParseInst);
			return TRUE;
		}
		 mXEDParseAssemble = (myXEDParseAssembleFunc)GetProcAddress(m_XEDParseInst, "XEDParseAssemble");
		if (mXEDParseAssemble == NULL)
		{
			MessageBox("�޷����ػ�������!");
			FreeLibrary(m_XEDParseInst);
			return TRUE;
		}
	}
	else {
		MessageBox("û�л�������ģ��!");
	}
	//m_edit_opcode.SetLimitText(8);
	return TRUE;
}



void CInjectCodeDlg::OnBnClickedButtonOpenProcessDlg()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HWND myHwnd = this->GetSafeHwnd();
	CProcessListDlg *processDlg = new  CProcessListDlg;
	processDlg->parentHwnd = myHwnd;
	processDlg->Create(IDD_PROCESS_DIALOG, this);
	processDlg->ShowWindow(SW_SHOW);
}

int  CInjectCodeDlg::GetInjectShellCode(char* shellcode) {
	CString opCode;
	m_edit_opcode.GetWindowText(opCode);
	CStringArray strArr;
	SplitString(opCode, ",", &strArr);
	int shellcodeSize = strArr.GetSize();
	for (int i = 0; i <shellcodeSize; i++) {
		CString tempStr(strArr.GetAt(i));
		int toNum = htoi(tempStr.GetBuffer());
		*(shellcode + sizeof(char)*i) = toNum;  // _ttoi(strArr.GetAt(i));
	}
	return shellcodeSize;
}

void CInjectCodeDlg::OnBnClickedOk()
{
	CString opCode;
	m_edit_opcode.GetWindowText(opCode);
	CStringArray strArr;
	SplitString(opCode, ",", &strArr);
	int shellcodeSize = strArr.GetSize();
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char *shellcode = (char*)malloc(sizeof(char)*shellcodeSize);
	if (shellcodeSize <= 0) {
		OnBnClickedGenerateCode(); //��һ�ε�ע�룬���û��shellcode,Ĭ���Զ����ɻ�����һ��		
	}
	shellcodeSize = GetInjectShellCode(shellcode);
	if (shellcodeSize <= 0) {
		MessageBox("��������shellcode�����ֶ�����shellcode������");
		return;
	}

	CString strProcessID;
	m_edit_process_id.GetWindowTextA(strProcessID);
	DWORD processID = _ttoi(strProcessID);
	if (strProcessID == "" || processID <= 0) {
		MessageBox("��ѡ��Ҫע��Ľ���!", _T("��ܰ��ʾ"));
		return;
	}
	bool injectFlag=InjectShellCode(processID,shellcode, shellcodeSize);
	if (!injectFlag) {
		MessageBox("ע��ʧ��,����Ȩ�޻���shellcode������");
	}
	else {
		MessageBox("shellcodeִ�гɹ�!");
	}
}



void CInjectCodeDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MessageBox("������!");
}





BOOL CInjectCodeDlg::GenerateOPcode(XED_STRUCT* my_xed)
{
	//char dest[XEDPARSE_MAXBUFSIZE] = { 0 };
	my_xed->OPCodeStr.Empty();
	my_xed->ShellCode.Empty();
	my_xed->ShellcodeLen = 0;
	XEDPARSE* parse = new XEDPARSE;
	parse->x64 = 0;
	parse->cip = 0;
	//memset(parse, 0, sizeof(parse));
	CString tempStr;
	for (int i = 0; i < my_xed->AsmCodeArray.GetSize(); i++) {
		CString asmCode = my_xed->AsmCodeArray.GetAt(i);
		int setLen = asmCode.GetLength()> XEDPARSE_MAXBUFSIZE ? XEDPARSE_MAXBUFSIZE : asmCode.GetLength();
		memset(parse->instr, 0, XEDPARSE_MAXBUFSIZE);
		memcpy(parse->instr, asmCode.GetString(), setLen);
		XEDPARSE_STATUS status = mXEDParseAssemble(parse);//XEDParseAssemble(parse);
		if (status == XEDPARSE_ERROR)   //if(status== XEDPARSE_OK)		
		{
			MessageBox("����������ʧ��,���������!");
			return false;
		}
		for (int len = 0; len < parse->dest_size; len++) {
			if (my_xed->OPCodeStr.GetLength() > 0) {
				my_xed->OPCodeStr.Format("%s,0x%02x", my_xed->OPCodeStr, *(parse->dest + len));
			}
			else {
				my_xed->OPCodeStr.Format("0x%02x", *(parse->dest + len));
			}
			my_xed->ShellCode.AppendChar(*(parse->dest + len));
		}
		my_xed->ShellcodeLen += parse->dest_size;
	}
	//memcpy(dest, parse->dest, parse->dest_size);
	return true;
}


void CInjectCodeDlg::OnBnClickedGenerateCode()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//char dest[XEDPARSE_MAXBUFSIZE] = { 0 };
	XED_STRUCT my_xed = { 0 };
	XEDPARSE parse = {0};
	m_edit_code.GetWindowText(my_xed.AsmCode);
	SplitString(my_xed.AsmCode, CString("\r\n"), &my_xed.AsmCodeArray);
	this->GenerateOPcode(&my_xed);
	char* sas = my_xed.ShellCode.GetBuffer();
	m_edit_opcode.SetWindowTextA(my_xed.OPCodeStr);
}


