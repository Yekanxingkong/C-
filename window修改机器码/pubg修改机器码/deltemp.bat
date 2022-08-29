start

echo f=shift delete /s=del all flie /q=quiet del.

>NUL 2>&1 REG.exe query "HKU\S-1-5-19" || (
    ECHO SET UAC = CreateObject^("Shell.Application"^) > "%TEMP%\GetAdmin.vbs"
    ECHO UAC.ShellExecute "%~f0", "%1", "", "runas", 1 >> "%TEMP%\GetAdmin.vbs"
    "%TEMP%\GetAdmin.vbs"
    DEL /f /q "%TEMP%\GetAdmin.vbs" 2>NUL
    Exit /b
)

start %windir%\system32\sfc.exe

start %windir%\system32\defrag.exe

echo 计算机日志
del /q /s /A-S C:\Windows\Temp\*.*
echo 蓝屏文件
del /q /s /A-S C:\Windows\LiveKernelReports\WATCHDOG
echo 人机日志
del /q /s /A-S C:\Windows\Logs\CBS
echo 性能监控
del /q /s /A-S C:\Windows\Performance\WinSAT
echo debug
del /q /s /A-S C:\Windows\debug
echo 计划程序启动记录
del /q /s /A-S C:\Windows\Tasks
echo 用户日志
del /q /s /A-S C:\Users\ADMINI~1\AppData\Local\Temp\*.*
echo 程序点击记录
del /q /s /A-S C:\Users\ADMINI~1\Recent\*.*
echo 网络操作记录
del /q /s /A-S C:\Users\ADMINI~1\Local Settings\*.*
echo 系统磁盘操作记录
del /q /s /A-S C:\Users\ADMINI~1\AppData\Roaming\Microsoft\Windows\Recent\AutomaticDestinations
echo 个人磁盘操作记录
del /q /s /A-S C:\Users\ADMINI~1\AppData\Roaming\Microsoft\Windows\Recent\CustomDestinations
echo 个人操作记录
del /q /s /A-S C:\Users\ADMINI~1\AppData\Roaming\Microsoft\Windows\Recent\*.*
echo 清空回收站
rd /q /s C:$Recycle.Bin
echo 正在清除系统临时文件 *.tmp *._tmp *.log *.chk *.old ，请稍等... 
del /f /s /q %systemdrive%\*.tmp 
del /f /s /q %systemdrive%\*._mp 
del /f /s /q %systemdrive%\*.log 
del /f /s /q %systemdrive%\*.gid 
del /f /s /q %systemdrive%\*.chk 
del /f /s /q %systemdrive%\*.old 

echo -------------个人系统的缓存和残留--------------------------
rmdir /q /s C:\Users\%username%\AppData\Local\Mozilla\Firefox\Profiles\ua23w2he.default-release
\cache2\entries
rmdir /q /s C:\Users\%username%\AppData\Local\Mozilla\Firefox\Profiles\ua23w2he.default-release
\thumbnails
rmdir /q /s C:\Users\%username%\AppData\Local\bitwarden-updater
rmdir /q /s C:\Users\%username%\AppData\Local\Qingfeng
rmdir /q /s C:\Users\%username%\AppData\Local\UnrealEngine
rmdir /q /s C:\Users\%username%\AppData\Local\BlueStacks X
rmdir /q /s C:\Users\%username%\AppData\Local\cache
rmdir /q /s C:\Users\%username%\AppData\Local\CrashDumps
rmdir /q /s C:\Users\%username%\AppData\Local\CrashRpt
rmdir /q /s C:\Users\%username%\AppData\Local\ElevatedDiagnostics
rmdir /q /s C:\Users\%username%\AppData\Local\FTMod
rmdir /q /s C:\Users\%username%\AppData\Local\Mindjet
rmdir /q /s C:\Users\%username%\AppData\Local\SalSoft
rmdir /q /s H:\steam\steamapps\common\PUBG\TslGame\Binaries\ThirdParty\BroCrashReporter\L10N
rmdir /q /s H:\steam\userdata
rmdir /q /s H:\steam\logs
echo 把前面的echo删掉就是清理命令rmdir /q /s 空格一下跟绝对路径
echo -------------个人系统的缓存和残留--------------------------

taskkill /f /im cmd.exe

exit