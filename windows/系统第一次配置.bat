start

>NUL 2>&1 REG.exe query "HKU\S-1-5-19" || (
    ECHO SET UAC = CreateObject^("Shell.Application"^) > "%TEMP%\GetAdmin.vbs"
    ECHO UAC.ShellExecute "%~f0", "%1", "", "runas", 1 >> "%TEMP%\GetAdmin.vbs"
    "%TEMP%\GetAdmin.vbs"
    DEL /f /q "%TEMP%\GetAdmin.vbs" 2>NUL
    Exit /b
)

taskkill /f /im 1__5000422__3f7372633d6c6d266c733d6e34656335323035313962__68616f2e3336302e636e__0c66.exe
taskkill /f /im 3__5000423__3f7372633d6c6d266c733d6e34656335323035313962__68616f2e3336302e636e__0c66.exe
taskkill /f /im 360sd_177981DL00040.exe
taskkill /f /im 2345Explorer_501608_silence.exe
taskkill /f /im QQliveSetup_30_606.exe
taskkill /f /im huanglisetup.exe

reg delete "HKEY_LOCAL_MACHINE\System\CurrentControlSet\Control\Session Manager" /f /v BootExecute
reg delete "HKEY_CURRENT_USER\Software\360safe" /f >NUL 2>NUL
reg delete "HKEY_CURRENT_USER\Software\360SoftMgr" /f >NUL 2>NUL
reg delete "HKEY_CURRENT_USER\Software\LiveUpdate360" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SOFTWARE\360Safe" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SOFTWARE\360softmgr" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SOFTWARE\LiveUpdate360" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\360安全卫士" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SOFTWARE\Classes\*\shellex\ContextMenuHandlers\Safe360Ext" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SOFTWARE\Classes\*\shellex\ContextMenuHandlers\SoftMgrExt" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SOFTWARE\Classes\Directory\shellex\ContextMenuHandlers\Safe360Ext" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SOFTWARE\Classes\Directory\Background\shellex\ContextMenuHandlers\SoftMgrExt" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SOFTWARE\Classes\Folder\ShellEx\ContextMenuHandlers\Safe360Ext" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\ShellIconOverlayIdentifiers\360UDiskGuard Icon Overlay" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\Browser Helper Objects\{B69F34DD-F0F9-42DC-9EDD-957187DA688D}" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\services\dsmainsrv" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\services\ZhuDongFangYu" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\services\360AntiHacker" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\services\360AntiHijack" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\services\360Box" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\services\360Camera" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\services\360netmon" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\services\360qpesv" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\services\360reskit" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\services\360SelfProtection" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\services\360Sensor" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\services\BAPIDRV" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\services\EfiMon" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\services\HookPort" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\services\qutmdserv" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\services\qutmipc" /f >NUL 2>NUL
reg delete "HKEY_CURRENT_USER\Software\360\360se6" /f >NUL 2>NUL
reg delete "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Uninstall\360se6" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SOFTWARE\360SD" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SOFTWARE\Classes\*\shellex\ContextMenuHandlers\SD360" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SOFTWARE\Classes\Directory\shellex\ContextMenuHandlers\SD360" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SOFTWARE\Classes\Folder\ShellEx\ContextMenuHandlers\SD360" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\ShellIconOverlayIdentifiers" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\services\360rp" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\services\360AvFlt" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\services\BAPIDRV" /f >NUL 2>NUL
reg delete "HKEY_CURRENT_USER\Software\2345.com" /f >NUL 2>NUL
reg delete "HKEY_CURRENT_USER\Software\2345Explorer" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SOFTWARE\2345BrowserSdk" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SOFTWARE\2345Explorer" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\2345Explorer" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\services\Protect_2345Explorer" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\services\2345CPort" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\services\2345NsProtect" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\services\2345Port" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\services\2345WebProtectFrame" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\services\ttmtor" /f >NUL 2>NUL
reg delete "HKEY_CURRENT_USER\Software\Tencent\bugReport\QQLiveBrowser" /f >NUL 2>NUL
reg delete "HKEY_CURRENT_USER\Software\Tencent\qqlive" /f >NUL 2>NUL
reg delete "HKEY_CURRENT_USER\Software\Tencent\qqliveEx" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SOFTWARE\tencent\qqlive" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SOFTWARE\tencent\qqliveocx" /f >NUL 2>NUL
reg delete "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\services\QQLiveService" /f >NUL 2>NUL
echo reg delete "" /f >NUL 2>NUL
echo del /q /s /A-S /A-A C:\Users\Administrator\Desktop\新建文件夹\*.*

rmdir /q /s C:\Users\Administrator\AppData\Local\360Chrome
rmdir /q /s C:\Users\Administrator\AppData\Local\360
rmdir /q /s C:\Users\Administrator\AppData\Local\360ChromeX
rmdir /q /s C:\Users\Administrator\AppData\Local\360Chrome
rmdir /q /s C:\Users\Administrator\AppData\Local\liebao
rmdir /q /s C:\Program Files\360\360safe
rmdir /q /s C:\Program Files (x86)\360\360safe
rmdir /q /s C:\ProgramData\360safe
rmdir /q /s C:\Users\Administrator\AppData\Roaming\360mobilemgr
rmdir /q /s C:\Users\Administrator\AppData\Roaming\360Quarant
rmdir /q /s C:\Users\Administrator\AppData\Roaming\360Safe
rmdir /q /s C:\Users\Default\AppData\Roaming\360Safe
rmdir /q /s C:\Users\Administrator\AppData\Roaming\360se6
rmdir /q /s C:\Users\Default\AppData\Roaming\360se6
rmdir /q /s C:\Program Files\360\360sd
rmdir /q /s C:\Program Files\360\360safe\360SD
rmdir /q /s C:\Program Files\Common Files\360SD
rmdir /q /s C:\Program Files (x86)\360\360sd
rmdir /q /s C:\Program Files (x86)\360\360safe\360SD
rmdir /q /s C:\Program Files (x86)\Common Files\360SD
rmdir /q /s C:\ProgramData\360SD
rmdir /q /s C:\Program Files\2345Soft\2345Explorer
rmdir /q /s C:\Program Files (x86)\2345Soft\2345Explorer
rmdir /q /s C:\Users\Administrator\AppData\Local\2345Explorer
rmdir /q /s C:\Users\Administrator\AppData\Roaming\2345DomainMon
rmdir /q /s C:\Users\Administrator\AppData\Roaming\2345PCSafe
rmdir /q /s C:\Users\Administrator\AppData\Roaming\GameHall_2345
rmdir /q /s C:\Users\Administrator\AppData\Roaming\Helper_2345
rmdir /q /s C:\Users\Administrator\AppData\Roaming\Shield_2345Explorer
rmdir /q /s C:\Program Files\Tencent\QQLive
rmdir /q /s C:\Program Files (x86)\Tencent\QQLive
rmdir /q /s C:\ProgramData\Tencent\QQLive
rmdir /q /s C:\Users\Administrator\AppData\Local\Temp\QQLive
rmdir /q /s C:\Users\Administrator\AppData\Roaming\Tencent\QQLive

taskkill /f /im cmd.exe


exit