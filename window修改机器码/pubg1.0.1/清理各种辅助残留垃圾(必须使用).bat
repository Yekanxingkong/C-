@echo off
TITLE ϵͳ��������
color 3B
echo.
echo ������Ϸ����س���
taskkill /f /im DNF.exe
taskkill /f /im TXPlatform.exe
taskkill /f /im CrossProxy.exe
taskkill /f /im TenSafe_1.exe
taskkill /f /im Client.exe
taskkill /f /im TenioDL.exe
taskkill /f /im uishell.exe
taskkill /f /im BackgroundDownloader.exe
echo ɾ����Ϸ��������
del C:\��Ѷ��Ϸ\���³�����ʿ\hid.dll
del C:\��Ѷ��Ϸ\���³�����ʿ\cryptsp.dll
del C:\��Ѷ��Ϸ\���³�����ʿ\wtsapi32.dll
del C:\��Ѷ��Ϸ\���³�����ʿ\cscapi.dll
del C:\��Ѷ��Ϸ\���³�����ʿ\AudioSea.dll
del C:\��Ѷ��Ϸ\���³�����ʿ\start\TenProtect\*.z
del D:\��Ѷ��Ϸ\���³�����ʿ\hid.dll
del D:\��Ѷ��Ϸ\���³�����ʿ\cryptsp.dll
del D:\��Ѷ��Ϸ\���³�����ʿ\wtsapi32.dll
del D:\��Ѷ��Ϸ\���³�����ʿ\cscapi.dll
del D:\��Ѷ��Ϸ\���³�����ʿ\AudioSea.dll
del D:\��Ѷ��Ϸ\���³�����ʿ\start\TenProtect\*.z
del E:\��Ѷ��Ϸ\���³�����ʿ\hid.dll
del E:\��Ѷ��Ϸ\���³�����ʿ\cryptsp.dll
del E:\��Ѷ��Ϸ\���³�����ʿ\wtsapi32.dll
del E:\��Ѷ��Ϸ\���³�����ʿ\cscapi.dll
del E:\��Ѷ��Ϸ\���³�����ʿ\AudioSea.dll
del E:\��Ѷ��Ϸ\���³�����ʿ\start\TenProtect\*.z
del F:\��Ѷ��Ϸ\���³�����ʿ\hid.dll
del F:\��Ѷ��Ϸ\���³�����ʿ\cryptsp.dll
del F:\��Ѷ��Ϸ\���³�����ʿ\wtsapi32.dll
del F:\��Ѷ��Ϸ\���³�����ʿ\cscapi.dll
del F:\��Ѷ��Ϸ\���³�����ʿ\AudioSea.dll
del F:\��Ѷ��Ϸ\���³�����ʿ\start\TenProtect\*.z
del C:\���³�����ʿ\hid.dll
del C:\���³�����ʿ\cryptsp.dll
del C:\���³�����ʿ\wtsapi32.dll
del C:\���³�����ʿ\cscapi.dll
del C:\���³�����ʿ\AudioSea.dll
del C:\���³�����ʿ\start\TenProtect\*.z
del D:\���³�����ʿ\hid.dll
del D:\���³�����ʿ\cryptsp.dll
del D:\���³�����ʿ\wtsapi32.dll
del D:\���³�����ʿ\cscapi.dll
del D:\���³�����ʿ\AudioSea.dll
del D:\���³�����ʿ\start\TenProtect\*.z
del E:\���³�����ʿ\hid.dll
del E:\���³�����ʿ\cryptsp.dll
del E:\���³�����ʿ\wtsapi32.dll
del E:\���³�����ʿ\cscapi.dll
del E:\���³�����ʿ\AudioSea.dll
del E:\���³�����ʿ\start\TenProtect\*.z
del F:\���³�����ʿ\hid.dll
del F:\���³�����ʿ\cryptsp.dll
del F:\���³�����ʿ\wtsapi32.dll
del F:\���³�����ʿ\cscapi.dll
del F:\���³�����ʿ\AudioSea.dll
del F:\���³�����ʿ\start\TenProtect\*.z
echo ɾ����Ϸ�������
del C:\Users\%username%\AppData\LocalLow\DNF\*.trc
del C:\Users\%username%\AppData\LocalLow\DNF\*.zip
echo ɾ����������Ŀ¼
RD %windir%\$hf_mig$ /Q /S
echo �Ѳ���ж���ļ��е����ֱ����2950800.txt
dir %windir%\$NtUninstall* /a:d /b >%windir%\2950800.txt
echo ��2950800.txt�ж�ȡ�ļ����б���ɾ���ļ���
for /f %%i in (%windir%\2950800.txt) do rd %windir%\%%i /s /q
echo ɾ��2950800.txt
del %windir%\2950800.txt /f /q
echo ɾ��������װ��¼����
del %windir%\KB*.log /f /q
echo ɾ��ϵͳ��Ŀ¼����ʱ�ļ�
del /f /s /q %systemdrive%\*.tmp
echo ɾ��ϵͳ��Ŀ¼����ʱ�ļ�
del /f /s /q %systemdrive%\*._mp
echo ɾ��ϵͳ��Ŀ¼����־�ļ�
del /f /s /q %systemdrive%\*.log
echo ɾ��ϵͳ��Ŀ¼��GID�ļ�(������ʱ�ļ����������ò���)
del /f /s /q %systemdrive%\*.gid
echo ɾ��ϵͳĿ¼��scandisk������ɨ�裩���µ������ļ�
del /f /s /q %systemdrive%\*.chk
echo ɾ��ϵͳĿ¼��old�ļ�
del /f /s /q %systemdrive%\*.old
echo ɾ������վ�������ļ�
del /f /s /q %systemdrive%\recycled\*.*
echo ɾ��ϵͳĿ¼�±����ļ�
del /f /s /q %windir%\*.bak
echo ɾ��Ӧ�ó�����ʱ�ļ�
del /f /s /q %windir%\prefetch\*.*
echo ɾ��ϵͳά���Ȳ�����������ʱ�ļ�
rd /s /q %windir%\temp md %windir%\temp
echo ɾ����ǰ�û���COOKIE��IE��
del /f /q %userprofile%\cookies\*.*
echo ɾ��internet��ʱ�ļ�
del /f /s /q "%userprofile%\local settings\temporary internet files\*.*"
echo ɾ����ǰ�û��ճ�������ʱ�ļ�
del /f /s /q "%userprofile%\local settings\temp\*.*"
echo ɾ�����ʼ�¼����ʼ�˵��е��ĵ�����Ķ�����
del /f /s /q "%userprofile%\recent\*.*"
echo.
echo ������Ϸ����س���+���ϵͳ�����ļ���ϣ���������˳�
pause