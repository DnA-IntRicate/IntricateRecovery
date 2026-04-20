:: Setup the project

@echo off
echo Installing Intrynzic Raptor...
python -m pip install -r requirements.txt
echo Done.
echo.
raptor setup all
echo.
raptor premake default
echo.
pause
