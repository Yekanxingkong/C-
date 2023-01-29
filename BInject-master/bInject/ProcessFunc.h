#pragma once
#include<map>
#include <windows.h>
using namespace std;

#define NT_SUCCESS(Status) ((NTSTATUS)(Status) >= 0)
#define STATUS_SUCCESS              ((NTSTATUS) 0x00000000)
#define SystemProcessesAndThreadsInformation    5 // ���ܺ�
#define NTAPI    __stdcall

typedef   struct ProcessInfo
{
	DWORD PID;
	CString FileName;
	CString WindowsTitle;
	CString ImagePath;
};

typedef struct ModuleInfo
{
	CString ModuleName;
	CString ImageBaseAddress;
	CString ImageBaseSize;
};

// �߳�״̬��ö�ٳ���
typedef enum _THREAD_STATE
{
	StateInitialized, // ��ʼ��״̬
	StateReady, // ׼��״̬
	StateRunning, // ����״̬
	StateStandby, // 
	StateTerminated,//�ر�
	StateWait, // �ȴ�
	StateTransition, // �л�???
	StateUnknown
}THREAD_STATE;

// �̴߳��ڵȴ���ԭ���ö�ٳ���
typedef enum _KWAIT_REASON
{
	Executive,
	FreePage,
	PageIn,
	PoolAllocation,
	DelayExecution,
	Suspended,
	UserRequest,
	WrExecutive,
	WrFreePage,
	WrPageIn,
	WrPoolAllocation,
	WrDelayExecution,
	WrSuspended,
	WrUserRequest,
	WrEventPair,
	WrQueue,
	WrLpcReceive,
	WrLpcReply,
	WrVirtualMemory,
	WrPageOut,
	WrRendezvous,
	Spare2,
	Spare3,
	Spare4,
	Spare5,
	Spare6,
	WrKernel,
	MaximumWaitReason
}KWAIT_REASON;




typedef LONG   NTSTATUS;
typedef LONG    KPRIORITY;

typedef struct _CLIENT_ID
{
	DWORD        UniqueProcess;
	DWORD        UniqueThread;
} CLIENT_ID, *PCLIENT_ID;


typedef struct _VM_COUNTERS
{
	SIZE_T        PeakVirtualSize;
	SIZE_T        VirtualSize;
	ULONG         PageFaultCount;
	SIZE_T        PeakWorkingSetSize;
	SIZE_T        WorkingSetSize;
	SIZE_T        QuotaPeakPagedPoolUsage;
	SIZE_T        QuotaPagedPoolUsage;
	SIZE_T        QuotaPeakNonPagedPoolUsage;
	SIZE_T        QuotaNonPagedPoolUsage;
	SIZE_T        PagefileUsage;
	SIZE_T        PeakPagefileUsage;
} VM_COUNTERS;

// �߳���Ϣ�ṹ��
typedef struct _SYSTEM_THREAD_INFORMATION
{
	LARGE_INTEGER   KernelTime;
	LARGE_INTEGER   UserTime;
	LARGE_INTEGER   CreateTime;
	ULONG           WaitTime;
	PVOID           StartAddress;
	CLIENT_ID       ClientId;
	KPRIORITY       Priority;
	KPRIORITY       BasePriority;
	ULONG           ContextSwitchCount;
	LONG            State;// ״̬,��THREAD_STATEö�������е�һ��ֵ
	LONG            WaitReason;//�ȴ�ԭ��, KWAIT_REASON�е�һ��ֵ
} SYSTEM_THREAD_INFORMATION, *PSYSTEM_THREAD_INFORMATION;


typedef struct _UNICODE_STRING
{
	USHORT Length;
	USHORT MaximumLength;
	PWSTR  Buffer;
} UNICODE_STRING, *PUNICODE_STRING;

// ������Ϣ�ṹ��
typedef struct _SYSTEM_PROCESS_INFORMATION
{
	ULONG            NextEntryDelta; // ָ����һ���ṹ���ָ��
	ULONG            ThreadCount; // �����̵����߳���
	ULONG            Reserved1[6]; // ����
	LARGE_INTEGER    CreateTime; // ���̵Ĵ���ʱ��
	LARGE_INTEGER    UserTime; // ���û����ʹ��ʱ��
	LARGE_INTEGER    KernelTime; // ���ں˲��ʹ��ʱ��
	UNICODE_STRING   ProcessName; // ������
	KPRIORITY        BasePriority; // 
	ULONG            ProcessId; // ����ID
	ULONG            InheritedFromProcessId;
	ULONG            HandleCount; // ���̵ľ������
	ULONG            Reserved2[2]; // ����
	VM_COUNTERS      VmCounters;
	IO_COUNTERS      IoCounters;
	SYSTEM_THREAD_INFORMATION Threads[5]; // ���߳���Ϣ����
}SYSTEM_PROCESS_INFORMATION, *PSYSTEM_PROCESS_INFORMATION;

map<DWORD, ProcessInfo> GetProcessList();
map<DWORD, ModuleInfo> GetProcessModule(DWORD dwPid);
int SuspendProcess(DWORD dwProcessID, BOOL fSuspend);
typedef DWORD(WINAPI* PQUERYSYSTEM)(UINT, PVOID, DWORD, PDWORD);
int IsThreadSuspend(DWORD dwProcessID, DWORD dwThreadID);