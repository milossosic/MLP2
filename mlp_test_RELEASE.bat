@echo off &setlocal enabledelayedexpansion
@echo off
for %%i in (.\instances\random\*.xml) do for /L %%A in (1,1,1) do call "D:\Milos\faks\master\MLP2\Release\MLP.exe" %%i

pause

