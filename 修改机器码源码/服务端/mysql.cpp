#include "winsock2.h"  
#include "windows.h" 
#include <iostream>  
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <Python.h>
using namespace std;
int mysql(char* cdk) {
	Py_SetPythonHome(L"D:\\developer_tools\\python3.8.5");
	Py_Initialize();
	PyObject* pModule = NULL;//python�ļ�
	PyObject* pFunc = NULL;//����
	PyObject* pName = NULL;

	/* ���python�Ƿ��ʼ���ɹ���python��ʼ��ʧ�ܳ���ֱ�ӽ���������һ��Ļ������
	if (Py_IsInitialized() == 0) {
		cout << "fail" << endl;
	}
	*/
	//PyRun_SimpleString("print('hello world')\n");
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('./script')");
	pModule = PyImport_ImportModule("pubg_cdk");//python�ű���C++����ɹ������ɵ�.exe�ļ�����ͬһĿ¼�¡���д�ű�����
	pFunc = PyObject_GetAttrString(pModule, "main");
	PyObject* pArgs = PyTuple_New(2);
	// 0����һ������������ int ���͵�ֵ 2
	PyTuple_SetItem(pArgs, 0, Py_BuildValue("s", cdk));
	// 1���ڶ������������� int ���͵�ֵ 4
	//PyTuple_SetItem(pArgs, 1, Py_BuildValue("i", 6));
	// 6��ʹ��C++��python�ӿڵ��øú���
	PyObject* pReturn = PyEval_CallObject(pFunc, pArgs);
	int nResult;
	// i��ʾת����int�ͱ�����
	// ���������Ҫע����ǣ�PyArg_Parse�����һ��������������ϡ�&������
	PyArg_Parse(pReturn, "i", &nResult);
	cout << "return result is:" << nResult << endl;
	//cout << "this is c++" << endl;
	/*û�в�����python�������ã���Ҫ��say.py��def add
	* PyObject* pModule = PyImport_ImportModule("say");
	* 	if (pModule == NULL) {
		cout << "module not found" << endl;
	}
	PyObject* pFunc = PyObject_GetAttrString(pModule, "add");
	if (!pFunc || !PyCallable_Check(pFunc)) {
		cout << "not found function add_num" << endl;
		return 0;
	}
	*/
	//PyObject_CallObject(pFunc, NULL);
	Py_Finalize();
	return nResult;
}