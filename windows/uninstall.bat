@echo off
echo Uninstalling Vyom...

REM Check for admin privileges
net session >nul 2>&1
if %errorLevel% neq 0 (
    echo Please run this file as Administrator.
    pause
    exit /b
)

REM Remove folder
if exist C:\Vyom (
    rmdir /s /q C:\Vyom
)

REM Remove from PATH
setx PATH "%PATH:C:\Vyom;=%" /M >nul

echo.
echo ❌ Vyom uninstalled successfully.
echo.
pause