@echo off

TITLE setup Yave
cls
pushd %~dp0
if not "%1"=="am_admin" (
    powershell -Command "Start-Process -Verb RunAs -FilePath '%0' -ArgumentList 'am_admin'"
    exit /b
)

echo by KK
echo instalowanie cmake, postepuj zgodnie z instrukcjami instalatora. Jesli masz cmake to po prostu anuluj.
pause

cd cmake
start /b cmake-3.26.0-rc6-windows-x86_64.msi
cd ../


cls
echo kopiowanie MinGW...
xcopy /s MinGW C:\
ren C:\mingw64 MinGW 
echo skopiowano!

echo dodawanie MinGW do zmiennych srodowiskowych
echo w razie czego: %PATH%
setx PATH "%PATH%;C:\MinGW\bin;C:\MinGW\msys\1.0\bin;"
echo dodano!

echo kopiowanie glada
cd glad
xcopy /s include C:\MinGW\include\
xcopy /s lib C:\MinGW\lib\
cd ../
echo skopiowano!

echo konfiguracja glfw
cd GLFW
xcopy /s include C:\MinGW\include\
cd lib-mingw-w64
xcopy libglfw3.a C:\MinGW\lib\
cd ../
cd ../
echo skonfigurowano!


echo czas na glm ;)
xcopy /s glm C:\MinGW\include\
echo poszlo

echo stb_image.h ...
cd stb_image
xcopy stb_image.h C:\MinGW\include\
cd ../
echo jest i on!

echo i na koniec assimp
cd assimp
xcopy /s assimp C:\MinGW\include\assimp\
xcopy /s lib C:\MinGW\lib\
cd ../
echo skopiowany!
pause
cls
echo jesli wszystko przebieglo bez komplikacji powinienes teraz tylko z folderu assimp
echo  skopiowac plik libassimp-5.dll do miejsca gdzie bedzie twoj plik wykonywalny
echo jesli to zrobisz to powinienes byc w stanie skompilowac i uruchomic projekt
echo milej zabawy ;)
pause