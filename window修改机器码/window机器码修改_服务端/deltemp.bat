start

echo f=shift delete /s=del all flie /q=quiet del.

taskkill /f /t /im steam.exe

if exist C:\Users\%username%\AppData\Local\Steam (
del /f /s /q  C:\Users\%username%\AppData\Local\Steam
)
if exist C:\Users\%username%\AppData\Local\WELLBIA (
del /f /s /q  C:\Users\%username%\AppData\Local\WELLBIA
)
if exist C:\Users\%username%\AppData\Local\WWCEF (
del /f /s /q  C:\Users\%username%\AppData\Local\WWCEF
)
if exist C:\Users\%username%\AppData\Local\TslGame (
del /f /s /q  C:\Users\%username%\AppData\Local\TslGame
)                      
if exist C:\Users\%username%\AppData\Local\BattlEye (
del /f /s /q  C:\Users\%username%\AppData\Local\BattlEye
)
echo AntiCheat Expert!!!!
if exist C:\Program Files\AntiCheatExpert  (
del /f /s /q  C:\Program Files\AntiCheatExpert
)

del /q /A-S C:\Users\%username%\AppData\Local\Temp 

del /q /A-S C:\Windows\Temp 

taskkill /f /im cmd.exe

exit