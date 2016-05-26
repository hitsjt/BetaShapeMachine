@echo off

echo !!! Please ensure all support libraries have already been installed !!!
echo.
echo To specify a installation directory for SNL other than the directory
echo containing this script, pass this directory as the first argument to
echo the script. This should also be the directory containing the support
echo libraries.
echo.
echo Installing SNL...

pushd %~dp0

if "%1"=="" (
  set SNL_PREFIX="%CD%"
) else (
  set SNL_PREFIX="%1"
)

cd ..\Build
cmake "-DCMAKE_INSTALL_PREFIX=%SNL_PREFIX%" -G "Visual Studio 12 Win64" .

REM devenv /Build Release SNLv2.sln
REM devenv /Build Release /Project INSTALL SNLv2.sln

REM devenv /Build Debug SNLv2.sln
REM devenv /Build Debug /Project INSTALL SNLv2.sln

set SNL_PREFIX=

popd
