#include <iostream>  
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include "winsock2.h"  
#include "windows.h"  
#include "mysql.h"  
#pragma comment(lib,"libmySQL.lib") 
using namespace std;
int mysql(string cdk) {
    const char host[] = "192.168.2.175";    //MySQL服务器IP地址；若是本地可填写“localhost”或127.0.0.1  
    const char user[] = "root";         //MySQL的用户名  
    const char pswd[] = "123456";         //密码  
    const char table[] = "CDK";        //数据库名称  
    unsigned int port = 3306;           //MySQL服务端口号，默认是3306          
    MYSQL myCont;//创建MYSQL对象，定义数据库连接句柄  
    MYSQL_RES* result = NULL;//查询结果集，存放查询结果  
    MYSQL_ROW sql_row;//存放一行查询结果的字符串数组  
    MYSQL_FIELD* fd; // 包含字段信息的结构
    char column[32][32];
    int res;
    mysql_library_init(0, NULL, NULL);//初始化MySQL库  
    mysql_init(&myCont);//初始化连接处理程序  
    if (mysql_real_connect(&myCont, host, user, pswd, table, port, NULL, 0))
    {//通过调用mysql_real_connect()连接到服务器 
        cout << "connect succeed!" << endl;
        mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式,否则在cmd下无法显示中文  
        //
        char Sqlcommand[255];
        char a[255];
        strcpy_s(a,cdk.c_str());
        strcpy_s(Sqlcommand, "select * from PUBGcdk WHERE PUBG_CKD='");
        strcat_s(Sqlcommand,a);      
        strcat_s(Sqlcommand, "'");
        res = mysql_query(&myCont,Sqlcommand);//执行语句，mysql_query如果执行成功，零；如果出现一个错误，非零。 
        if (!res)
        {
            result = mysql_store_result(&myCont);//保存查询到的数据到result  
            int i, j;
            cout << "number of result: " << (unsigned long)mysql_num_rows(result) << endl;
            int sql_mun = (unsigned long)mysql_num_rows(result);
            if (sql_mun != 0) {
                for (i = 0; fd = mysql_fetch_field(result); i++)//获取列名  
                {
                    strcpy_s(column[i],fd->name);
                    //strcpy_s(column[i], strlen(fd->name) + 1, fd->name);
                }
                j = mysql_num_fields(result);
                for (i = 0; i < j; i++)
                {
                    printf("%s", column[i]);
                }
                /*
                while (sql_row = mysql_fetch_row(result))//获取具体的数据  
                {
                    for (i = 0; i < j; i++)
                    {
                        char num[10];
                        strcpy_s(num, sql_row[i]);
                        //printf("%s\n", sql_row[i]);
                    }

                }*/
                strcpy_s(Sqlcommand, "DELETE FROM PUBGcdk WHERE PUBG_CKD='");
                strcat_s(Sqlcommand, a);
                strcat_s(Sqlcommand, "'");
                cout<< Sqlcommand <<endl;
                res = mysql_query(&myCont, Sqlcommand);
                if (!res) {
                    cout << "sql删除成功" << endl;
                }
                else {
                    cout << "sql删除失败" << endl;
                }
                if (result != NULL) {
                    mysql_free_result(result);//释放结果资源  
                }
                mysql_close(&myCont);//关闭MySQL连接  
                mysql_library_end();//关闭MySQL库  
                return 1;
            }
            else {
                cout << "Sql未查询到数据，查询语句：" << Sqlcommand << endl;
            }

        }
        else
        {
            cout << "query sql failed!" << endl;
        }

    }
    else
    {
        cout << "connect failed!" << endl;
    }
    //注意用完数据库要及时回收资源  
    if (result != NULL) {
        mysql_free_result(result);//释放结果资源  
    }
    mysql_close(&myCont);//关闭MySQL连接  
    mysql_library_end();//关闭MySQL库  
    return 0;



}