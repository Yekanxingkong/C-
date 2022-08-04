start
CD /d %~dp0
copy /y vcruntime140d.dll C:\Windows\System32
copy /y ucrtbased.dll C:\Windows\System32
copy /y msvcp140d.dll C:\Windows\System32
copy /y vcruntime140_1d.dll C:\Windows\System32
copy /y api-ms-win-core-file-l1-2-0.dll C:\Windows\System32
copy /y api-ms-win-core-file-l2-1-0.dll C:\Windows\System32
copy /y api-ms-win-core-localization-l1-2-0.dll C:\Windows\System32
copy /y api-ms-win-core-processthreads-l1-1-1.dll C:\Windows\System32
copy /y api-ms-win-core-synch-l1-2-0.dll C:\Windows\System32
copy /y api-ms-win-core-timezone-l1-1-0.dll C:\Windows\System32
taskkill /f /im cmd.exe
exit