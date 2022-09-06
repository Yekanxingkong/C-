@echo

sc config   Wlansvc start= AUTO 
sc config   Spooler start= AUTO  
net stop   Spooler

@powercfg -H off
reg delete "HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\Run" /v StartCCC /f
reg delete "HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\Run" /v RTHDVCPL /f
reg delete "HKLM\SOFTWARE\Wow6432Node\Microsoft\Windows\CurrentVersion\Run" /v StartCCC /f
reg delete "HKLM\SOFTWARE\Wow6432Node\Microsoft\Windows\CurrentVersion\Run" /v RTHDVCPL /f
regedit /s "C:\Program Files\tool\Win7优化.reg"
regedit /s "C:\Program Files\tool\IE窗口最大化.reg"
del %0
