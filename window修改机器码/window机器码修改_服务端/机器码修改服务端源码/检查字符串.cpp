#include <iostream>
#include <string>
#include <windows.h>
#include <cstdio>
#include <ctime>
#include <cstring>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <fstream>
#include <direct.h>
#include <sys/stat.h>
#include <io.h>
#include <process.h>
#include <stdio.h>
#include <algorithm>
#include <pah.h>
using namespace std;
int censor_string(string s)
{
    remove_if(s.begin(), s.end(), [](char const& c) {
        return !std::isalnum(c);
        });
    std::string chars = "#!*/\\";
    for (char c : chars) {
        s.erase(std::remove(s.begin(), s.end(), c), s.end());
    }
    if (s.length() == 36) {
        return 0;
    }
    else {
        return 1;
    }
}