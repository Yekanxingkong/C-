@echo off
@ ECHO.
@ ECHO.
@ ECHO.                              ˵    ��
@ ECHO -----------------------------------------------------------------------
@ ECHO ���ļ�û���ر����壬������D�̽���һ�����ط�ɾ�ļ��С�ghost�����ڱ��ݡ�
@ ECHO ����������߳����������
@ ECHO ���ļ�Ҳ�������������޸�IE��ҳ�Ĵ��룬������������ȡ�
@ ECHO -----------------------------------------------------------------------
@ ECHO           
@ ECHO                    
@ ECHO.
md d:\ghost
md d:\ghost\xd..\
attrib d:\ghost +s +h

@echo off

reg add "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\OEMInformation" /v Manufacturer /t reg_sz /d ΢���й� /f

reg add "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\OEMInformation" /v Model /t reg_sz /d Win7_64λ�콢�� /f

@ ECHO �����������벻�����У�Ҫ���е������뽫ǰ��ġ�@ ECHO ��ɾ��
@ ECHO reg add "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\OEMInformation" /v SupportHours /t reg_sz /d ����һ��������8��00-17��00 /f

@ ECHO �����������벻�����У�Ҫ���е������뽫ǰ��ġ�@ ECHO ��ɾ��
@ ECHO reg add "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\OEMInformation" /v SupportPhone /t reg_sz /d 0755-88888888 /f

@ ECHO �����������벻�����У�Ҫ���е������뽫ǰ��ġ�@ ECHO ��ɾ��
@ ECHO reg add "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\OEMInformation" /v SupportURL /t reg_sz /d http://www.microsoft.com/china/ /f

@ ECHO *�뽫�����õ�ϵͳ����ͼƬ����ΪOEMLOGO.bmp           *
@ ECHO *�ŵ�C:\Windows\system32\oobe\info\OEMLOGO.bmp       *
@ ECHO *�����������벻�ùܣ�Ĭ�Ϸ�ϵͳ����ͼƬ��ָ��λ�ü���*

@ ECHO reg add "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\OEMInformation" /v Logo /t reg_sz /d "C:\Windows\system32\oobe\info\OEMLOGO.bmp" /f

regedit /s "C:\Program Files\tool\Win7�Ż�.reg"
regedit /s "C:\Program Files\tool\IE�������.reg"

@ ECHO ɾ������QQ��Ϸͼ��
@ ECHO ��Ҫ������������ɾ�����롰@ ECHO ��
@ ECHO del /f /q C:\Users\Administrator\Desktop\QQ��Ϸ.lnk

@ ECHO ����Ĵ�����ͨ��֤��ģʽ�������Ĭ�ϲ�������
@ ECHO ��Ҫ������������ɾ��regeditǰ��Ĵ��롰@ ECHO ��

@ ECHO regedit /s "C:\Program Files\tool\��ֹ360��װ.reg"
@ ECHO regedit /s "C:\Program Files\tool\��ֹ��ɽ��װ.reg"
@ ECHO regedit /s "C:\Program Files\tool\��ֹ���ǰ�װ.reg"
@ ECHO regedit /s "C:\Program Files\tool\��ֹ�ٶ�ɱ����ʿ���.reg"

@ ECHO ����Ĵ�����ɾ������IEͼ�꣬Ĭ�ϲ�������
@ ECHO ��Ҫ������������ɾ��regǰ��Ĵ��롰@ ECHO ��
@ ECHO reg delete "HKEY_CLASSES_ROOT\CLSID\{B416D21B-3B22-B6D4-BBD3-BBD452DB3D5B" /f
@ ECHO reg delete "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\Desktop\NameSpace\{B416D21B-3B22-B6D4-BBD3-BBD452DB3D5B}" /f


@ ECHO. �� ������ġ�XX���� 13800138000���ĳɡ����Ե��� �绰���롱     ��
@ ECHO. ��            ���������Ϊ�޸�IE�ı���                         ��
@ ECHO. �� �����������벻�����У�Ҫ���е������뽫ǰ��ġ�@ ECHO ��ɾ�� ��

@ ECHO reg add "HKEY_CURRENT_USER\Software\Microsoft\Internet Explorer\Main" /v "window title" /t reg_sz /d "XX���� 13800138000" /f

del D:\Favorites\Links\��ҳ��Ѷ��.url /f /q

del %0