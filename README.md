# YAVE - Yet Another Voxel Engine

### Testowy projekt mający na celu naukę OpenGL i shaderów (GLSL). Celem jest stworzenie silnika do gry Sylian.
Główne założenia tego silnika to:
    - ładne wyglądanie, efekty świetlne i graficzne
    - działać szybko i opierać się na karcie graficznej
    - obsługiwanie przez server, jest to de facto ( i ma być ) jedynie klient
    - musi być napisany w C++ ( z domieszką C ), może tymczasowo kożystac z LUA ( ale to raczej server )

## zależności potrzebne do uruchomienia
- glad - zobacz README.md w folderze .local lub postępuj zgodnie z "Setting up GLAD" na stronie : 

https://learnopengl.com/Getting-started/Creating-a-window

- glfw3 i glm
   
    na Fedorze 37:
```
sudo dnf install glfw-devel
sudo dnf install glm-devel
```

- stb-image.h
```
git clone https://github.com/nothings/stb.git
sudo cp stb/stb_image.h /usr/local/include/
```

- możliwe że potrzebne też do glfw3 ( fedora 37 instaluje je automatycznie )
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

- assimp
    na Fedorze 37:
```
sudo dnf install assimp-devel
```

- możliwe że potrzebne też do assimp ( fedora 37 instaluje je automatycznie )
```
assimp
irrXML
poly2tri
```