@echo off
title Vyom Uninstaller

echo ----------------------------------------
echo Vyom Uninstallation
echo ----------------------------------------
echo.

set INSTALL_DIR=C:\Vyom

if exist "%INSTALL_DIR%" (
    echo Removing installation files...
    rmdir /S /Q "%INSTALL_DIR%"
) else (
    echo Vyom is not installed.
)

echo.
echo Vyom has been removed from this system.
echo.
echo NOTE:
echo If Vyom was added to PATH, you may need
echo to remove C:\Vyom manually from PATH.
echo.
pause