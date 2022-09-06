@echo off
rem del /f /s /q "%userprofile%\AppData\Local\Microsoft\Windows\Temporary Internet Files\*.*"
rem del /f /s /q "%temp%\*.*"
RunDll32.exe InetCpl.cpl,ClearMyTracksByProcess 8
RunDll32.exe InetCpl.cpl,ClearMyTracksByProcess 2
RunDll32.exe InetCpl.cpl,ClearMyTracksByProcess 1 
RunDll32.exe InetCpl.cpl,ClearMyTracksByProcess 16 
RunDll32.exe InetCpl.cpl,ClearMyTracksByProcess 32 
RunDll32.exe InetCpl.cpl,ClearMyTracksByProcess 255 
RunDll32.exe InetCpl.cpl,ClearMyTracksByProcess 4351