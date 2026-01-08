@echo off
echo Installing Vyom...

REM Check for admin privileges
net session >nul 2>&1
if %errorLevel% neq 0 (
    echo Please run this file as Administrator.
    pause
    exit /b
)

REM Create install directory
if not exist C:\Vyom (
    mkdir C:\Vyom
)

REM Copy executable
copy vyom.exe C:\Vyom\vyom.exe >nul

REM Add to PATH
setx PATH "%PATH%;C:\Vyom" /M >nul

echo.
echo ✅ Vyom installed successfully!
echo You can now run: vyom test.vy
echo.
pause