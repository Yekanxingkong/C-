@ECHO OFF
SET USERNAME="root"
SET PASSWORD="password"

SET S=%1
SET S=%S:192.168.2.1://=%
ECHO INT 路由是网口
FOR /f "tokens=1,2 delims=/ " %%a IN ("%S%") DO SET HOST=%%a&SET INT="eth2"
IF "%INT%" == "eth0" SET FILTER=" not port 22"

ECHO "Connecting to %USERNAME%@%HOST%..."

"C:\Program Files\EVE-NG\plink.exe" -ssh -batch -pw %PASSWORD% %USERNAME%@%HOST% "tcpdump -U -i %INT% -s 0 -w -%FILTER%" | "D:\developer_tools\Wireshark_(64bit)_v3.0.6\Wireshark\Wireshark.exe" -k -i -
