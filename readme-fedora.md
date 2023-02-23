## instrukcja dla Fedory 37
- glad - zobacz README.md w folderze .local lub postępuj zgodnie z "Setting up GLAD" na stronie : 

https://learnopengl.com/Getting-started/Creating-a-window


- glfw3 i glm

```
sudo dnf install glfw-devel
sudo dnf install glm-devel
```

- stb-image.h
```
git clone https://github.com/nothings/stb.git
sudo cp stb/stb_image.h /usr/local/include/
```

- assimp: tutaj sie sprawy komplikują, jeśli chcemy uruchomić tylko "tańczącego wampira" to wystarczy
```
sudo dnf install assimp-devel
```

- kiedy chcemy uruchomić dowolną przykładową animacje z mixamo.com to musimy zainstalować najnowszego assimpa:

https://github.com/assimp/assimp/blob/master/Build.md

(najpierw CMake)
```
sudo dnf install cmake
```
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