## instrukcja dla Manjaro
- cmake
```
sudo pacman -S cmake
```
***
- glad - zobacz README.md  w folderze `additional/glad/linux/.local` (nierekomendowane) aby użyć skompilowanego glada lub postępuj zgodnie z "Setting up GLAD" na stronie( rekomendowane ) : 

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
sudo pacman -S glfw-wayland
sudo pacman -S glm
```

***

- stb-image.h
```
git clone https://github.com/nothings/stb.git
sudo cp stb/stb_image.h /usr/local/include/
```

***

- assimp
```
sudo dnf install assimp-devel
```
***
