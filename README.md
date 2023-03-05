# YAVE - Yet Another Voxel Engine

### Testowy projekt mający na celu naukę OpenGL i shaderów (GLSL). Celem jest stworzenie silnika do gry Sylian.
Główne założenia tego silnika to:
- ładne wyglądanie, efekty świetlne i graficzne
- działać szybko i opierać się na karcie graficznej
- obsługiwanie przez server, jest to de facto ( i ma być ) jedynie klient
- musi być napisany w C++ ( z domieszką C ), może tymczasowo kożystac z LUA ( ale to raczej server )



Należy zainstalować wszystkie zależności( instrukcja niżej w sekcji Zależności ) a następnie wywołać w terminalu polecenie( z folderu głównego Yave ):
- na linuxie
```
cmake -S . -B .
```
- na windowsie:
```
cmake -S . -B build -G "MinGW Makefiles"
```
później po każdej zmianie w kodzie wystarczy użyć polecenia:
```
cmake --build .
```

## Zależności:
### [Fedora 37](readme-fedora.md)
### [Manjaro](readme-manjaro.md)
### [Windows 10](readme-windows.md)


### Ogólnie
- glad
- glfw3 i glm
- stb-image.h
```
git clone https://github.com/nothings/stb.git
sudo cp stb/stb_image.h /usr/local/include/
```

- możliwe że potrzebne też do glfw3
```
gl-manpages  
libXcursor-devel
libXext-devel
libXfixes-devel
libXi-devel
libXinerama-devel
libXrandr-devel
libdrm-devel
libglvnd-core-devel
libglvnd-devel
libpciaccess-devel
mesa-libGL-devel
mesa-libGLU-devel
valgrind
valgrind-devel
```

- assimp: tutaj sie sprawy komplikują, jeśli chcemy uruchomić tylko "tańczącego wampira" to wystarczy assimp-devel


- możliwe że potrzebne też do assimp
```
assimp
irrXML
poly2tri
```

- kiedy chcemy uruchomić dowolną przykładową animacje z mixamo.com to musimy zainstalować najnowszego assimpa:

https://github.com/assimp/assimp/blob/master/Build.md

najpierw potrzebny Cmake

Assimp:
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



