@echo off
title Vyom Installer v0.2

echo ----------------------------------------
echo Vyom v0.2 Installation
echo ----------------------------------------
echo.

set INSTALL_DIR=C:\Vyom

echo Creating installation directory...
if not exist "%INSTALL_DIR%" (
    mkdir "%INSTALL_DIR%"
)

echo Copying Vyom executable...
copy /Y "%~dp0vyom.exe" "%INSTALL_DIR%\vyom.exe" >nul

echo Registering Vyom in system PATH...
setx PATH "%PATH%;%INSTALL_DIR%" >nul

echo.
echo Installation completed successfully.
echo.
echo You can now run Vyom from any terminal using:
echo     vyom main.vy
echo.
echo NOTE:
echo Please restart Command Prompt or PowerShell
echo for PATH changes to take effect.
echo.
pause