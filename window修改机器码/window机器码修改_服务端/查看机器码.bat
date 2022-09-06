ECHO OFF
TITLE Munch HWID Checker
ECHO **********************************
ECHO [*]  Checking ALL Spoofed Serials...
Color 1A
ECHO [*] New PC Serials:
ECHO **********************************
ECHO Diskdrive Serials:
:start
cls
wmic diskdrive get serialnumber
ECHO New CPU Serials:
wmic cpu get serialnumber
ECHO New Bios Serials:
wmic bios get serialnumber
ECHO New Baseboard Serials:
wmic baseboard get serialnumber
ECHO New Mac Serials:
getmac
pause>nul
goto start