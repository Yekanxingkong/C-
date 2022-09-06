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
    const char host[] = "192.168.2.175";    //MySQL������IP��ַ�����Ǳ��ؿ���д��localhost����127.0.0.1  
    const char user[] = "root";         //MySQL���û���  
    const char pswd[] = "123456";         //����  
    const char table[] = "CDK";        //���ݿ�����  
    unsigned int port = 3306;           //MySQL����˿ںţ�Ĭ����3306          
    MYSQL myCont;//����MYSQL���󣬶������ݿ����Ӿ��  
    MYSQL_RES* result = NULL;//��ѯ���������Ų�ѯ���  
    MYSQL_ROW sql_row;//���һ�в�ѯ������ַ�������  
    MYSQL_FIELD* fd; // �����ֶ���Ϣ�Ľṹ
    char column[32][32];
    int res;
    mysql_library_init(0, NULL, NULL);//��ʼ��MySQL��  
    mysql_init(&myCont);//��ʼ�����Ӵ������  
    if (mysql_real_connect(&myCont, host, user, pswd, table, port, NULL, 0))
    {//ͨ������mysql_real_connect()���ӵ������� 
        cout << "connect succeed!" << endl;
        mysql_query(&myCont, "SET NAMES GBK"); //���ñ����ʽ,������cmd���޷���ʾ����  
        //
        char Sqlcommand[255];
        char a[255];
        strcpy_s(a,cdk.c_str());
        strcpy_s(Sqlcommand, "select * from PUBGcdk WHERE PUBG_CKD='");
        strcat_s(Sqlcommand,a);      
        strcat_s(Sqlcommand, "'");
        res = mysql_query(&myCont,Sqlcommand);//ִ����䣬mysql_query���ִ�гɹ����㣻�������һ�����󣬷��㡣 
        if (!res)
        {
            result = mysql_store_result(&myCont);//�����ѯ�������ݵ�result  
            int i, j;
            cout << "number of result: " << (unsigned long)mysql_num_rows(result) << endl;
            int sql_mun = (unsigned long)mysql_num_rows(result);
            if (sql_mun != 0) {
                for (i = 0; fd = mysql_fetch_field(result); i++)//��ȡ����  
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
                while (sql_row = mysql_fetch_row(result))//��ȡ���������  
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
                    cout << "sqlɾ���ɹ�" << endl;
                }
                else {
                    cout << "sqlɾ��ʧ��" << endl;
                }
                if (result != NULL) {
                    mysql_free_result(result);//�ͷŽ����Դ  
                }
                mysql_close(&myCont);//�ر�MySQL����  
                mysql_library_end();//�ر�MySQL��  
                return 1;
            }
            else {
                cout << "Sqlδ��ѯ�����ݣ���ѯ��䣺" << Sqlcommand << endl;
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
    //ע���������ݿ�Ҫ��ʱ������Դ  
    if (result != NULL) {
        mysql_free_result(result);//�ͷŽ����Դ  
    }
    mysql_close(&myCont);//�ر�MySQL����  
    mysql_library_end();//�ر�MySQL��  
    return 0;



}