@echo off
title Vyom Installer v0.2
color 0A

cls
echo ========================================
echo        Vyom v0.2 Installer
echo ========================================
echo.
echo A minimal scripting language
echo Created by Sanket Bharadwaj
echo.
echo ----------------------------------------
echo Initializing installer...
echo ----------------------------------------
timeout /t 1 >nul

set INSTALL_DIR=C:\Vyom

:: Step 1 — Create directory
echo [1/4] Preparing installation directory...
if not exist "%INSTALL_DIR%" (
    mkdir "%INSTALL_DIR%"
    echo     + Created %INSTALL_DIR%
) else (
    echo     + Directory already exists
)
timeout /t 1 >nul

:: Step 2 — Copy executable
echo [2/4] Installing Vyom executable...
if not exist "%~dp0vyom.exe" (
    color 0C
    echo     ! ERROR: vyom.exe not found
    echo     ! Please keep install.bat and vyom.exe in same folder
    pause
    exit /b 1
)

copy /Y "%~dp0vyom.exe" "%INSTALL_DIR%\vyom.exe" >nul
echo     + vyom.exe installed
timeout /t 1 >nul

:: Step 3 — Add to PATH
echo [3/4] Registering Vyom in system PATH...
setx PATH "%PATH%;%INSTALL_DIR%" >nul
echo     + PATH updated
timeout /t 1 >nul

:: Step 4 — Finish
echo [4/4] Finalizing installation...
timeout /t 1 >nul

color 0A
echo.
echo ========================================
echo  Installation completed successfully!
echo ========================================
echo.
echo You can now run Vyom from any terminal:
echo.
echo     vyom examples\main.vy
echo.
echo NOTE:
echo - Restart Command Prompt or PowerShell
echo   for PATH changes to take effect.
echo.
pause