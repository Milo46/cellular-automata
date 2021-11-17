@echo off

if "%~1" == ""          goto PrintHelp
if "%~1" == "compile"   goto Compile

build-controls\premake5.exe %1
goto Done

::
:: Prints out 'how to use' when user provides no arguments
::
:PrintHelp

echo.
echo Enter 'build.bat action' where action is one of the following:
echo.
echo   compile           Will generate make file then compile using the make file.
echo   clean             Remove all binaries and intermediate binaries and project files.
echo   codelite          Generate CodeLite project files
echo   gmake             Generate GNU makefiles for Linux
echo   vs2005            Generate Visual Studio 2005 project files
echo   vs2008            Generate Visual Studio 2008 project files
echo   vs2010            Generate Visual Studio 2010 project files
echo   vs2012            Generate Visual Studio 2012 project files
echo   vs2013            Generate Visual Studio 2013 project files
echo   vs2015            Generate Visual Studio 2015 project files
echo   vs2017            Generate Visual Studio 2017 project files
echo   vs2019            Generate Visual Studio 2019 project files
echo   xcode4            Generate Apple Xcode 4 project files

goto Done

::
:: Obviously, compiles the project/s
::
:Compile

BuildControls\premake5.exe vs2019

if not defined DevEnvDir (
    call "C:\Program Files(x86)\Microsoft Visual Studio\2019\Community\Common7\Tools\VsDevCmd.bat"
)

set solutionFile = "Worskpace.sln"

:: Visual studio developer cmd command
msbuild /t:Build /p:Configuration=Debug /p:Platform=x64 %solutionFile%

::
:: End of the script
::
:Done
