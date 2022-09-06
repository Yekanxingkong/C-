@echo off
@ ECHO.
@ ECHO.
@ ECHO.                              说    明
@ ECHO -----------------------------------------------------------------------
@ ECHO 本文件没有特别意义，用于在D盘建立一个隐藏防删文件夹“ghost”用于备份。
@ ECHO 另外可以免疫常见的浏览器
@ ECHO 本文件也可以用来增加修改IE主页的代码，调用其它程序等。
@ ECHO -----------------------------------------------------------------------
@ ECHO           
@ ECHO                    
@ ECHO.
md d:\ghost
md d:\ghost\xd..\
attrib d:\ghost +s +h

@echo off

reg add "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\OEMInformation" /v Manufacturer /t reg_sz /d 微软中国 /f

reg add "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\OEMInformation" /v Model /t reg_sz /d Win7_64位旗舰版 /f

@ ECHO 下面这条代码不会运行，要运行的朋友请将前面的“@ ECHO ”删除
@ ECHO reg add "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\OEMInformation" /v SupportHours /t reg_sz /d 星期一至星期五8：00-17：00 /f

@ ECHO 下面这条代码不会运行，要运行的朋友请将前面的“@ ECHO ”删除
@ ECHO reg add "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\OEMInformation" /v SupportPhone /t reg_sz /d 0755-88888888 /f

@ ECHO 下面这条代码不会运行，要运行的朋友请将前面的“@ ECHO ”删除
@ ECHO reg add "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\OEMInformation" /v SupportURL /t reg_sz /d http://www.microsoft.com/china/ /f

@ ECHO *请将制作好的系统属性图片命名为OEMLOGO.bmp           *
@ ECHO *放到C:\Windows\system32\oobe\info\OEMLOGO.bmp       *
@ ECHO *下面这条代码不用管，默认放系统属性图片到指定位置即可*

@ ECHO reg add "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\OEMInformation" /v Logo /t reg_sz /d "C:\Windows\system32\oobe\info\OEMLOGO.bmp" /f

regedit /s "C:\Program Files\tool\Win7优化.reg"
regedit /s "C:\Program Files\tool\IE窗口最大化.reg"

@ ECHO 删除桌面QQ游戏图标
@ ECHO 需要开启的朋友请删除代码“@ ECHO ”
@ ECHO del /f /q C:\Users\Administrator\Desktop\QQ游戏.lnk

@ ECHO 下面的代码是通过证书模式禁用软件默认不会运行
@ ECHO 需要开启的朋友请删除regedit前面的代码“@ ECHO ”

@ ECHO regedit /s "C:\Program Files\tool\禁止360安装.reg"
@ ECHO regedit /s "C:\Program Files\tool\禁止金山安装.reg"
@ ECHO regedit /s "C:\Program Files\tool\禁止瑞星安装.reg"
@ ECHO regedit /s "C:\Program Files\tool\禁止百度杀毒卫士软件.reg"

@ ECHO 下面的代码是删除桌面IE图标，默认不会运行
@ ECHO 需要开启的朋友请删除reg前面的代码“@ ECHO ”
@ ECHO reg delete "HKEY_CLASSES_ROOT\CLSID\{B416D21B-3B22-B6D4-BBD3-BBD452DB3D5B" /f
@ ECHO reg delete "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\Desktop\NameSpace\{B416D21B-3B22-B6D4-BBD3-BBD452DB3D5B}" /f


@ ECHO. ▏ 将下面的“XX电脑 13800138000”改成“电脑店名 电话号码”     ▏
@ ECHO. ▏            代码的作用为修改IE的标题                         ▏
@ ECHO. ▏ 下面这条代码不会运行，要运行的朋友请将前面的“@ ECHO ”删除 ▏

@ ECHO reg add "HKEY_CURRENT_USER\Software\Microsoft\Internet Explorer\Main" /v "window title" /t reg_sz /d "XX电脑 13800138000" /f

del D:\Favorites\Links\网页快讯库.url /f /q

del %0