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

echo �������־
del /q /s /A-S C:\Windows\Temp\*.*
echo �����ļ�
del /q /s /A-S C:\Windows\LiveKernelReports\WATCHDOG
echo �˻���־
del /q /s /A-S C:\Windows\Logs\CBS
echo ���ܼ��
del /q /s /A-S C:\Windows\Performance\WinSAT
echo debug
del /q /s /A-S C:\Windows\debug
echo �ƻ�����������¼
del /q /s /A-S C:\Windows\Tasks
echo �û���־
del /q /s /A-S C:\Users\ADMINI~1\AppData\Local\Temp\*.*
echo ��������¼
del /q /s /A-S C:\Users\ADMINI~1\Recent\*.*
echo ���������¼
del /q /s /A-S C:\Users\ADMINI~1\Local Settings\*.*
echo ϵͳ���̲�����¼
del /q /s /A-S C:\Users\ADMINI~1\AppData\Roaming\Microsoft\Windows\Recent\AutomaticDestinations
echo ���˴��̲�����¼
del /q /s /A-S C:\Users\ADMINI~1\AppData\Roaming\Microsoft\Windows\Recent\CustomDestinations
echo ���˲�����¼
del /q /s /A-S C:\Users\ADMINI~1\AppData\Roaming\Microsoft\Windows\Recent\*.*
echo ��ջ���վ
rd /q /s C:$Recycle.Bin
echo �������ϵͳ��ʱ�ļ� *.tmp *._tmp *.log *.chk *.old �����Ե�... 
del /f /s /q %systemdrive%\*.tmp 
del /f /s /q %systemdrive%\*._mp 
del /f /s /q %systemdrive%\*.log 
del /f /s /q %systemdrive%\*.gid 
del /f /s /q %systemdrive%\*.chk 
del /f /s /q %systemdrive%\*.old 

echo -------------����ϵͳ�Ļ���Ͳ���--------------------------
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
echo ��ǰ���echoɾ��������������rmdir /q /s �ո�һ�¸�����·��
echo -------------����ϵͳ�Ļ���Ͳ���--------------------------

taskkill /f /im cmd.exe

exit