start

>NUL 2>&1 REG.exe query "HKU\S-1-5-19" || (
    ECHO SET UAC = CreateObject^("Shell.Application"^) > "%TEMP%\GetAdmin.vbs"
    ECHO UAC.ShellExecute "%~f0", "%1", "", "runas", 1 >> "%TEMP%\GetAdmin.vbs"
    "%TEMP%\GetAdmin.vbs"
    DEL /f /q "%TEMP%\GetAdmin.vbs" 2>NUL
    Exit /b
)
CD /d %~dp0

if %PROCESSOR_ARCHITECTURE%==AMD64 (set AMIDE=AMIDEWINx64.EXE) else (set AMIDE=AMIDEWIN.EXE)

set "DmiVar0100010500=1WJB22719R25VES"
set "DmiVar0100010700=HVK3Q4XOZ65CTTC"
set "DmiVar0100010600=T7L489A39F0776I"
set "DmiVar0100011a00=JIGM2NYF48D8068"
set "DmiVar0200020600=924B6186BO2GBHS"
set "DmiVar0300030800=QR316Q0I7NVH85O30"
set "DmiVar0300030700=GS3B8P0L21219X4"
set "DmiVar0300030900=KV0Y73E8WS10J1S51"

%AMIDE% /SP "%DmiVar0100010500%"
%AMIDE% /SS "%DmiVar0100010700%"
%AMIDE% /SV "%DmiVar0100010600%"
%AMIDE% /SF "%DmiVar0100011a00%"
%AMIDE% /SU AUTO
%AMIDE% /BV "%DmiVar0200020600%"
%AMIDE% /CA "%DmiVar0300030800%"
%AMIDE% /CS "%DmiVar0300030700%"
%AMIDE% /BS "%DmiVar0300030900%"

taskkill /f /im cmd.exe
exit