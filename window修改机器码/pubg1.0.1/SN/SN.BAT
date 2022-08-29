@ECHO OFF&TITLE 

>NUL 2>&1 REG.exe query "HKU\S-1-5-19" || (
    ECHO SET UAC = CreateObject^("Shell.Application"^) > "%TEMP%\GetAdmin.vbs"
    ECHO UAC.ShellExecute "%~f0", "%1", "", "runas", 1 >> "%TEMP%\GetAdmin.vbs"
    "%TEMP%\GetAdmin.vbs"
    DEL /f /q "%TEMP%\GetAdmin.vbs" 2>NUL
    Exit /b
)
CD /d %~dp0

if %PROCESSOR_ARCHITECTURE%==AMD64 (set AMIDE=AMIDEWINx64.EXE) else (set AMIDE=AMIDEWIN.EXE)

set "DmiVar0100010500=AAV77BRD6AHJFAE"
set "DmiVar0100010700=AAIOVOIBOUJAKSH"
set "DmiVar0100010600=AAPBODJBNRBGASE"
set "DmiVar0100011a00=AAGHDHGKBJBRAEE"
set "DmiVar0200020600=AAGJDKBRKBAW3RW"
set "DmiVar0300030800=AAGIJIDSOURIOANBRR"
set "DmiVar0300030700=AANUASBDJKBBSBEAE"
set "DmiVar0300030900=AAGUASHIDUAIE4IBSE"

%AMIDE% /SP "%DmiVar0100010500%"
%AMIDE% /SS "%DmiVar0100010700%"
%AMIDE% /SV "%DmiVar0100010600%"
%AMIDE% /SF "%DmiVar0100011a00%"
%AMIDE% /SU AUTO
%AMIDE% /BV "%DmiVar0200020600%"
%AMIDE% /CA "%DmiVar0300030800%"
%AMIDE% /CS "%DmiVar0300030700%"
%AMIDE% /BS "%DmiVar0300030900%"


echo Done. Press any key to exit.
pause>nul
goto :exit

::备注
::进去
::可
::写入
::编写
::执行
::
::ASCII存储的DMI值，前后均有一个0x00作为分隔符
::UUID错
::操作.
::BIOS
timeout /t 6
:exit