@echo off &setlocal enabledelayedexpansion
@echo off
for %%i in (.\instances\*.xml) do for /L %%A in (1,1,1) do call ".\Release\MLP.exe" %%i

pause

