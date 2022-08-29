@echo off
TITLE 系统垃圾清理
color 3B
echo.
echo 结束游戏跟相关程序
taskkill /f /im DNF.exe
taskkill /f /im TXPlatform.exe
taskkill /f /im CrossProxy.exe
taskkill /f /im TenSafe_1.exe
taskkill /f /im Client.exe
taskkill /f /im TenioDL.exe
taskkill /f /im uishell.exe
taskkill /f /im BackgroundDownloader.exe
echo 删除游戏辅助残留
del C:\腾讯游戏\地下城与勇士\hid.dll
del C:\腾讯游戏\地下城与勇士\cryptsp.dll
del C:\腾讯游戏\地下城与勇士\wtsapi32.dll
del C:\腾讯游戏\地下城与勇士\cscapi.dll
del C:\腾讯游戏\地下城与勇士\AudioSea.dll
del C:\腾讯游戏\地下城与勇士\start\TenProtect\*.z
del D:\腾讯游戏\地下城与勇士\hid.dll
del D:\腾讯游戏\地下城与勇士\cryptsp.dll
del D:\腾讯游戏\地下城与勇士\wtsapi32.dll
del D:\腾讯游戏\地下城与勇士\cscapi.dll
del D:\腾讯游戏\地下城与勇士\AudioSea.dll
del D:\腾讯游戏\地下城与勇士\start\TenProtect\*.z
del E:\腾讯游戏\地下城与勇士\hid.dll
del E:\腾讯游戏\地下城与勇士\cryptsp.dll
del E:\腾讯游戏\地下城与勇士\wtsapi32.dll
del E:\腾讯游戏\地下城与勇士\cscapi.dll
del E:\腾讯游戏\地下城与勇士\AudioSea.dll
del E:\腾讯游戏\地下城与勇士\start\TenProtect\*.z
del F:\腾讯游戏\地下城与勇士\hid.dll
del F:\腾讯游戏\地下城与勇士\cryptsp.dll
del F:\腾讯游戏\地下城与勇士\wtsapi32.dll
del F:\腾讯游戏\地下城与勇士\cscapi.dll
del F:\腾讯游戏\地下城与勇士\AudioSea.dll
del F:\腾讯游戏\地下城与勇士\start\TenProtect\*.z
del C:\地下城与勇士\hid.dll
del C:\地下城与勇士\cryptsp.dll
del C:\地下城与勇士\wtsapi32.dll
del C:\地下城与勇士\cscapi.dll
del C:\地下城与勇士\AudioSea.dll
del C:\地下城与勇士\start\TenProtect\*.z
del D:\地下城与勇士\hid.dll
del D:\地下城与勇士\cryptsp.dll
del D:\地下城与勇士\wtsapi32.dll
del D:\地下城与勇士\cscapi.dll
del D:\地下城与勇士\AudioSea.dll
del D:\地下城与勇士\start\TenProtect\*.z
del E:\地下城与勇士\hid.dll
del E:\地下城与勇士\cryptsp.dll
del E:\地下城与勇士\wtsapi32.dll
del E:\地下城与勇士\cscapi.dll
del E:\地下城与勇士\AudioSea.dll
del E:\地下城与勇士\start\TenProtect\*.z
del F:\地下城与勇士\hid.dll
del F:\地下城与勇士\cryptsp.dll
del F:\地下城与勇士\wtsapi32.dll
del F:\地下城与勇士\cscapi.dll
del F:\地下城与勇士\AudioSea.dll
del F:\地下城与勇士\start\TenProtect\*.z
echo 删除游戏相关数据
del C:\Users\%username%\AppData\LocalLow\DNF\*.trc
del C:\Users\%username%\AppData\LocalLow\DNF\*.zip
echo 删除补丁备份目录
RD %windir%\$hf_mig$ /Q /S
echo 把补丁卸载文件夹的名字保存成2950800.txt
dir %windir%\$NtUninstall* /a:d /b >%windir%\2950800.txt
echo 从2950800.txt中读取文件夹列表并且删除文件夹
for /f %%i in (%windir%\2950800.txt) do rd %windir%\%%i /s /q
echo 删除2950800.txt
del %windir%\2950800.txt /f /q
echo 删除补丁安装记录内容
del %windir%\KB*.log /f /q
echo 删除系统盘目录下临时文件
del /f /s /q %systemdrive%\*.tmp
echo 删除系统盘目录下临时文件
del /f /s /q %systemdrive%\*._mp
echo 删除系统盘目录下日志文件
del /f /s /q %systemdrive%\*.log
echo 删除系统盘目录下GID文件(属于临时文件，具体作用不详)
del /f /s /q %systemdrive%\*.gid
echo 删除系统目录下scandisk（磁盘扫描）留下的无用文件
del /f /s /q %systemdrive%\*.chk
echo 删除系统目录下old文件
del /f /s /q %systemdrive%\*.old
echo 删除回收站的无用文件
del /f /s /q %systemdrive%\recycled\*.*
echo 删除系统目录下备份文件
del /f /s /q %windir%\*.bak
echo 删除应用程序临时文件
del /f /s /q %windir%\prefetch\*.*
echo 删除系统维护等操作产生的临时文件
rd /s /q %windir%\temp md %windir%\temp
echo 删除当前用户的COOKIE（IE）
del /f /q %userprofile%\cookies\*.*
echo 删除internet临时文件
del /f /s /q "%userprofile%\local settings\temporary internet files\*.*"
echo 删除当前用户日常操作临时文件
del /f /s /q "%userprofile%\local settings\temp\*.*"
echo 删除访问记录（开始菜单中的文档里面的东西）
del /f /s /q "%userprofile%\recent\*.*"
echo.
echo 结束游戏跟相关程序+清除系统垃圾文件完毕，按任意键退出
pause