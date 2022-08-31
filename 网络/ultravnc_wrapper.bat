@ECHO OFF
SET S=%1
SET S=###%S%###
SET S=%S:"###=%
SET S=%S:###"=%
SET S=%S:###=%
SET S=%S:vnc://=%
start "VNCViewer" "D:\developer_tools\EVE-NG-Win-Client-Pack-2.0\UltraVNC\vncviewer.exe" -connect %S% -shared
