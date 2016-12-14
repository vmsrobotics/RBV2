@echo off
FOR /F %%I IN ('DIR "%LOCALAPPDATA%\github\PortableGit_*" /B') DO set gitPath=%LOCALAPPDATA%\github\%%I\cmd\git.exe
Echo GitPath= %gitPath%
copy /Y "RBV2\RBV2.ino" "%USERPROFILE%\desktop\Temp_RBV2.ino"
rem %gitPath% reset --hard
%gitPath% init
%gitPath% pull
copy /Y "%USERPROFILE%\desktop\Temp_RBV2.ino" "RBV2\RBV2.ino"
