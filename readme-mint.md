## instrukcja dla Linux Mint (i Ubuntu)
- cmake
```
sudo apt install cmake
```
***
- glad - zobacz [README.md](additional/linux/REDME.md)  w folderze `additional/linux` (nierekomendowane) aby użyć skompilowanego glada lub postępuj zgodnie z "Setting up GLAD" na stronie( rekomendowane ) :  

https://learnopengl.com/Getting-started/Creating-a-window

czyli szczegółowo:
1. wejść na stronę https://glad.dav1d.de/
2. w polu "Language" wybrać **C/C++**, w "Specification" - **OpenGL**, w "Profile" - **Core**, gl wybrać **4.6** a reszte **none**
3. na dole zaznaczyć "generate a loader", resztę odznaczyć
4. nacisnąć przycisk "Generate"
5. pojawi się lista plików - nacisnąć na plik *zip i go pobrać
6. rozpakować, folder `src` przekopiować do folderu `additional/glad`
7. natomiast zawartość folderu `include` należy przekopiować do: `/usr/include`
8. przejść do folderu `additional/glad` w terminalu i uruchomić komendy:
```
cmake -S . -B build
cmake --build build
```
9. jeśli nie wystąpiły błędy to powinien się pojawić folder `build`, a w nim plik **libglad.a** - należy go przekopiować do folderu: `/usr/lib`

***

- glfw3 i glm

```
sudo apt install libgltf-dev
sudo apt install libglm-dev
```

***

- stb-image.h
```
git clone https://github.com/nothings/stb.git
sudo cp stb/stb_image.h /usr/local/include/
```

***

- Assimp: 

tutaj sie sprawy komplikują, jeśli chcemy uruchomić tylko "tańczącego wampira" to wystarczy
```
sudo apt install libassimp-dev
```

kiedy chcemy uruchomić dowolną przykładową animacje z mixamo.com to musimy zainstalować najnowszego assimpa:

https://github.com/assimp/assimp/blob/master/Build.md

```
git clone https://github.com/assimp/assimp.git
cd assimp
cmake CMakeLists.txt 
cmake --build .
sudo make install
```

Może się okazać że wystąpi błąd:
```
assimp: error while loading shared libraries: libassimp.so.5: cannot open shared object file: No such file or directory
```
lub podobny

wtedy za pomocą polecenia:
```
find / | grep libassimp.so
```
szukamy wymienionego pliku i wykonujemy:
```
export LD_LIBRARY_PATH=<ścieżka do tego pliku bez jego nazwy>
```
czyli np:
```
export LD_LIBRARY_PATH=/usr/local/lib64/
```
można oczywiście powyższe polecenie dodać do pliku .bashrc aby nie musieć go wykonywać po każdym restarcie komputera

-irrklang
1. należy pobrać irrKlang ze strony https://www.ambiera.com/irrklang/downloads.html
2. rozpakować
3. z folderu `bin/linux-gcc-64` skopiować pliki do `/usr/lib`
4. z folderu `include` skopiować pliki do folderu `/usr/lib/irrklang`, jeśli nie istnieje - utworzyć