## instrukcja dla Manjaro
- glad - zobacz README.md w folderze .local lub postępuj zgodnie z "Setting up GLAD" na stronie : 

https://learnopengl.com/Getting-started/Creating-a-window

- glfw3 i glm

```
sudo pacman -S glfw-wayland
sudo pacman -S glm
```

- stb-image.h
```
git clone https://github.com/nothings/stb.git
sudo cp stb/stb_image.h /usr/local/include/
```

- assimp
```
sudo dnf install assimp-devel
```

- dodatkowe
aby kompilować na windowsa potrzebujesz mingw
```
sudo pacman -S mingw-w64
```

prawdopodobnie ukaże się 5 pakietów do wyboru,
domyślnie zostaną zainstalowane wszystkie:
```
mingw-w64-binutils
mingw-w64-crt
mingw-w64-gcc
mingw-w64-headers
mingw-w64-winpthreads

```