## instrukcja dla Windowsa 10

uprzedzam że skonfigurowanie aby wszystko zadziałało na windowsie jest zasadniczo dłuższe niż na Linuxie więc zachęcam do korzystania jednak z Linuxa ;)
***
- cmake

wejdź na stronę https://cmake.org/download/ i pobierz installer cmake dla windowsa ( prawdopodobnie rozszerzenie *msi ) i zainstaluj
***
- MinGW

możesz pobrać i zainstalować stąd: https://winlibs.com/ , wybierając najnowszą wersę (sprawdzona że działa: **URCT runtime - GCC 12.1.0: Win64**)
po pobraniu i rozpakowaniu plików przenieś te pliki, najlepiej do C:\ i dodaj do zmiennej środowiskowej _PATH_ ścieżki:

 ```
 <miejsce instalacji MinGW>\mingw64\bin
 <miejsce instalacji MinGW>\mingw64\msys\1.0\bin
 ```

***

 - glad

zasadniczo wystarczy wykonać kroki opisane na https://learnopengl.com/Getting-started/Creating-a-window czyli:
1. wejść na stronę https://glad.dav1d.de/
2. w polu `Language` wybrać **C/C++**, w `Specification` - **OpenGL**, w `Profile` - **Core**, `gl` wybrać **4.6** a reszte **none**
3. na dole zaznaczyć **generate a loader**, resztę odznaczyć
4. nacisnąć przycisk **Generate**
5. pojawi się lista plików - nacisnąć na plik ***zip** i go pobrać
6. rozpakować, folder `src` przekopiować do folderu `additional/glad`
7. natomiast zawartość folderu `include` należy przekopiować do: `<miejsce instalacji MinGW>\MinGW\include`
8. przejść do folderu `additional/glad` w terminalu/cmd i uruchomić komendy:
```
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
```
9. jeśli nie wystąpiły błędy to powinien się pojawić folder `build`, a w nim plik **libglad.a** - należy go przekopiować do folderu: `<miejsce instalacji MinGW>\MinGW\lib`

***

 - glfw

Pobierz glfw z https://www.glfw.org/download wybierając wersję dla windowsa.

Rozpakuj, a następnie z rozpakowanego folderu `glfw-x.x.x.bin/include/GLFW` skopiuj plik **glfw3.h** i **glfw3native.h** do:
 `<miejsce instalacji MinGW>\MinGW\include\GLFW` 
jeśli nie ma tam folderu GLFW to go stwórz

natomiast z folderu `lib-mingw` skopiuj plik **libglfw3.a** do folderu: `<miejsce instalacji MinGW>\MinGW\lib`

następnie skopiuj zmień nazwę przekopiowanego pliku na libglfw.a

***

 - glm

 1. wejdź na stronę https://glm.g-truc.net/0.9.9/index.html
 2. kliknij `Downloads`
 3. wybierz najnowszą wersję i pobierz ***.zip**
 4. rozpakuj i wejdź do folderu `glm`, powinieneś dobaczyć kilka folderów i plików, wśród nich folder `glm`, skopiuj go do folderu:
 `<miejsce instalacji MinGW>\MinGW\include`

***

- stb_image.h

1. wejdź na stronę https://github.com/nothings/stb
2. pobierz kod źródłowy w formie zip, lub po prostu skopiuj zawartość pliku **stb_image.h**
3. rozpakuj i/lub plik **stb_image.h** umieść w folderze: `<miejsce instalacji MinGW>\MinGW\include`

***

- assimp
 
 możesz pobrać assimpa stąd: https://sourceforge.net/projects/assimp/files/assimp-3.1/ lub z jego githuba
 najlepiej wybierz wersję **win-binaries**

 rozpakuj i zawartość folderu `include` skopiuj do `<miejsce instalacji MinGW>\MinGW\include`

 a z folderu `lib64` przekopiuj plik **assimp.lib** do folderu `<miejsce instalacji MinGW>\MinGW\lib`



może się jednak okazać że podczas próby kompilacji wystąpią błędy rodzaju:
```
undefined reference to `Assimp::Importer`
```
wtedy należy:
1. 