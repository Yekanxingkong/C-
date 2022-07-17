#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <fstream>  
#include <direct.h>
using namespace std;
char* rand_str(char* str, const int len)
{
    srand(time(NULL));
    wb = "";
    int i;
    for (i = 0; i < len; ++i)
    {
        switch ((rand() % 2))
        {
        case 1:
            str[i] = 'A' + rand() % 26;
            wb = wb + str[i];
            break;
        //case 2:
            //str[i] = 'a' + rand() % 26;
            //break;
        default:
            str[i] = '0' + rand() % 10;
            wb = wb + str[i];
            break;
        }
    }
    //str[++i] = ''
    //str = (char*)wb.data();
    return 0;
}
std::string current_working_directory()
{
    char buff[250];
    _getcwd(buff, 250);
    std::string current_working_directory(buff);
    return current_working_directory;
}

void func(const std::string& list)
{
    
    ofstream outfile("D:\\Project3\\x64\\Debug\\ck.txt", ofstream::app);
    //ofstream outfile("E:\\myfile.txt", ofstream::app);  

    string temp = list;  //Ð´ÈëÄÚÈÝ
    if (outfile.is_open())
    {
        outfile << temp << "\n";
        outfile.close();
    }
    else
    {
        cout << "can not open the file \n" << endl;
        
    }

}

int inf()
{
    ifstream infile("D:\\Project3\\x64\\Debug\\SN.BAT");
    //ifstream infile("E:\\myfile.txt");  

    string temp;
    if (!infile.is_open())
    {
        cout << "can not open the file \n" << endl;
        return -1;
    }
    while (getline(infile, temp))
    {
        cout << temp << "\n";
    }
    infile.close();
    return 0;
}
int main(void)
{
    char name[15];
    string x = "\"\n";
    string suimaths = rand_str(name, 15);
    cout << wb << endl;
    string a1;
    //string a2 = "set \"DmiVar0100010700=";
    a1 = "set \"DmiVar0100010500=" + suimaths + x;
    cout << a1 << endl;
    string getcwd = current_working_directory();
    
    //cout << rand_str(name, 20) << getcwd << endl;
    system("pause");
    return 0;
}





