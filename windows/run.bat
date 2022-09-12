start

>NUL 2>&1 REG.exe query "HKU\S-1-5-19" || (
    ECHO SET UAC = CreateObject^("Shell.Application"^) > "%TEMP%\GetAdmin.vbs"
    ECHO UAC.ShellExecute "%~f0", "%1", "", "runas", 1 >> "%TEMP%\GetAdmin.vbs"
    "%TEMP%\GetAdmin.vbs"
    DEL /f /q "%TEMP%\GetAdmin.vbs" 2>NUL
    Exit /b
)

rmdir /q /s C:\Users\Administrator\AppData\Local\CEF
rmdir /q /s C:\Users\Administrator\AppData\Local\360Chrome
rmdir /q /s C:\Users\Administrator\AppData\Local\bitwarden-updater
rmdir /q /s C:\Users\Administrator\AppData\Local\Qingfeng
rmdir /q /s C:\Users\Administrator\AppData\Local\Steam
rmdir /q /s C:\Users\Administrator\AppData\Local\xweb_webview
rmdir /q /s C:\Users\Administrator\AppData\Local\Rufus
rmdir /q /s C:\Users\Administrator\AppData\Local\UCBrowser
rmdir /q /s C:\Users\Administrator\AppData\LocalLow\Pixonic
rmdir /q /s C:\Users\Administrator\AppData\Roaming\Baidu
rmdir /q /s C:\Users\Administrator\AppData\Roaming\Bitwarden
rmdir /q /s C:\Users\Administrator\AppData\Roaming\FFRenamePro
rmdir /q /s C:\Users\Administrator\AppData\Roaming\lddownloader
rmdir /q /s C:\Users\Administrator\AppData\Roaming\wirednetrepaire
rmdir /q /s C:\Users\Administrator\AppData\Roaming\TPDownloadProxy
rmdir /q /s C:\Users\Administrator\AppData\Roaming\RenamePro
rmdir /q /s C:\Users\Administrator\AppData\Roaming\QMLogEx
rmdir /q /s C:\Program Files\AntiCheatExpert
rmdir /q /s C:\Program Files\Bitwarden
rmdir /q /s C:\Program Files\Common Files\PUBG
rmdir /q /s C:\Program Files\Common Files\Tencent
rmdir /q /s C:\Program Files (x86)\Common Files\BattlEye
rmdir /q /s C:\Program Files (x86)\Common Files\DESIGNER
echo rmdir /q /s 
del /q /f C:\Users\Administrator\AppData\Roaming\heybox_acc.log
del /q/a/f/s C:\Users\Administrator\AppData\LocalLow\Microsoft\CryptnetUrlCache\Content\*.*
del /q/a/f/s C:\Users\Administrator\AppData\LocalLow\Microsoft\CryptnetUrlCache\MetaData\*.*
del /q/a/f/s C:\Users\Administrator\Recent\*.*
del /q/a/f/s C:\Users\Administrator\AppData\Roaming\Microsoft\Windows\Recent\*.*
del /q/a/f/s C:\Users\Administrator\AppData\Local\Temp\*.*
echo del /q/a/f/s É¾³ý±£ÁôÎÄ¼þ¼Ð
taskkill /f /im cmd.exe

exit




