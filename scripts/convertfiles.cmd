@echo off
setlocal

REM mac2unix, unix2dos at https://waterlan.home.xs4all.nl/dos2unix.html

pushd %~dp0\..

mac2unix src\*.c src\*.h *.md
unix2dos src\*.c src\*.h *.md

popd

endlocal

exit /b %ErrorLevel%
