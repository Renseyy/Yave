## instrukcja dla Windowsa 10
- cmake
wejdź na stronę https://cmake.org/download/ i pobierz installer cmake dla windowsa ( prawdopodobnie rozszerzenie *msi ) i zainstaluj

- MinGW
możesz pobrać i zainstalować stąd: https://sourceforge.net/projects/mingw/ , kiedy otworzy ci się okienko z wyborem paczek do pobrania
możesz albo pobrać wszystko( jak ja ) albo teoretycznie powinno ci też starczyć mingw-developer-toolkit i mingw-gcc-g++.

następnym krokie jest sprawdzenie czy jest zainstalowane poprawnie: wpisz w terminalu w VScode lub w cmd
```
g++
```
jeśli wyskoczy błąd:
```
The term 'g++' is not recognized as the name of a cmdlet, function, script file, or operable program...
```
to należy dodać ścieżki:
 ```
 <miejsce instalacji MinGW>\MinGW\bin
 <miejsce instalacji MinGW>\MinGW\msys\1.0\bin
 ```
 czyli domyślnie:
 ```
 C:\MinGW\bin
 C:\MinGW\msys\1.0\bin
 ```
 do zmiennej środowiskowej PATH

 - glad
zasadniczo wystarczy wykonać kroki opisane na https://learnopengl.com/Getting-started/Creating-a-window czyli:
1. wejść na stronę https://glad.dav1d.de/
2. w polu "Language" wybrać C/C++, w "Specification" - OpenGL, w "Profile" - Core, gl wybrać 4.6 a reszte none
3. na dole zaznaczyć "generate a loader", resztę odznaczyć
4. nacisnąć przycisk "Generate"
5. pojawi się lista plików - nacisnąć na plik *zip i go pobrać

 - glfw

Pobierz glfw z https://www.glfw.org/download wybierając wersję dla windowsa.

Rozpakuj, a następnie z rozpakowanego folderu glfw-x.x.x.bin/include/GLFW skopiuj plik glfw3.h do:
```
<miejsce instalacji MinGW>\MinGW\include\GLFW
```
jeśli nie ma tam folderu GLFW to go stwórz

natomiast z folderu lib-mingw skopiuj plki libglfw3.a i libglfwdll3.a do folderu:
```
<miejsce instalacji MinGW>\MinGW\lib 
```
następnie skopiuj plik glfw3.dll do głównego katalogu Yave ( do tego gdzie jest README )