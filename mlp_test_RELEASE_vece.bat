@echo off &setlocal enabledelayedexpansion
@echo off
for %%i in (.\instances\*.xml) do for /L %%A in (1,1,1) do call "D:\Milos\faks\master\MLP2\Release\MLP.exe" %%i

pause

