@echo off
openfiles > NUL 2>&1 
if not %ERRORLEVEL% == 0 (
  rem 一般権限で実行されたため管理者権限で再実行
  powershell start-process \"%~f0\" -Verb runas
  goto exit
)

echo %~dpn0
cd /d %~dp0
echo %WINDIR%\System32\regsvr32 /u ..\bin\x64\Release\ComServer.dll
%WINDIR%\System32\regsvr32 /u ..\bin\x64\Release\ComServer.dll

pause