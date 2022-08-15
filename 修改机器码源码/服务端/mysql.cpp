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
	PyObject* pModule = NULL;//python文件
	PyObject* pFunc = NULL;//函数
	PyObject* pName = NULL;

	/* 检查python是否初始化成功，python初始化失败程序直接结束，还有一屏幕的问题
	if (Py_IsInitialized() == 0) {
		cout << "fail" << endl;
	}
	*/
	//PyRun_SimpleString("print('hello world')\n");
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('./script')");
	pModule = PyImport_ImportModule("pubg_cdk");//python脚本和C++编译成功后生成的.exe文件放在同一目录下。填写脚本名字
	pFunc = PyObject_GetAttrString(pModule, "main");
	PyObject* pArgs = PyTuple_New(2);
	// 0：第一个参数，传入 int 类型的值 2
	PyTuple_SetItem(pArgs, 0, Py_BuildValue("s", cdk));
	// 1：第二个参数，传入 int 类型的值 4
	//PyTuple_SetItem(pArgs, 1, Py_BuildValue("i", 6));
	// 6、使用C++的python接口调用该函数
	PyObject* pReturn = PyEval_CallObject(pFunc, pArgs);
	int nResult;
	// i表示转换成int型变量。
	// 在这里，最需要注意的是：PyArg_Parse的最后一个参数，必须加上“&”符号
	PyArg_Parse(pReturn, "i", &nResult);
	cout << "return result is:" << nResult << endl;
	//cout << "this is c++" << endl;
	/*没有参数的python函数调用，需要有say.py和def add
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