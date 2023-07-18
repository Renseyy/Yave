# YAVE - Yet Another Voxel Engine

### Testowy projekt mający na celu naukę OpenGL i shaderów (GLSL). Celem jest stworzenie silnika do gry Sylian.
Główne założenia tego silnika to:
- ładne wyglądanie, efekty świetlne i graficzne
- działać szybko i opierać się na karcie graficznej
- obsługiwanie przez server, jest to de facto ( i ma być ) jedynie klient
- musi być napisany w C++ ( z domieszką C ), może tymczasowo kożystac z LUA ( ale to raczej server )



Należy zainstalować wszystkie zależności( instrukcja niżej w sekcji Zależności ) a następnie:
- stworzyć jakiś folder w którym znajdą się utworzone pliki( np. **build** )
- na linuxie z katalogu głównego Yave - tam gdzie **README**
```
cmake -S . -B <ścieżka do folderu na utworzone pliki>
czyli np (kiedy utworzyliśmy folder build )
cmake -S . -B build
```
- na windowsie:

Otworzyć program *cmake* jako źródło podać **katalog główny Yave**, a jako miejsce docelowe **folder na utworzone pliki**

wcisnąć *configure*, a następnie *build*


### Jeśli chcesz korzystać z debugowania np za pomocą gdb to dodaj na końcu jeszcze:
```
-DCMAKE_BUILD_TYPE=Debug
```


później po każdej zmianie w kodzie wystarczy użyć polecenia:
```
cmake --build <ścieżka do folderu na utworzone pliki>
czyli np.
cmake --build build
```

To tyle!

PS. Za pierwszym razem kompilacja może zająć długo

### Animacje

Aby użyć animacji:

1. w main() przed *render loop*:
- zmień **Shader** na shader dla animacji: 
```
Shader <nazwa_shadera>(DIRECT_DIR("shaders/animations/anim_model.vs"), DIRECT_DIR("shaders/animations/anim_model.fs"));
```
- ustaw **Model** ***nazwa_modelu*** na ten, który ma być animowany ( zazwyczaj po prostu plik animacji )
- ustaw **Animation** ***nazwa_animacji*** na plik animacji
- ustaw **Animator** ***nazwa_animatora*** na adres twojej animacji `&<nazwa_animacji>`
2. w pętli render:
- przygotuj do renderowania: `YAVE_prepareRender(&<nazwa_shadera>);`
- wykonaj klatke animacji i przygotuj do wyrysowania: `YAVE_execAnimation(&<nazwa_animatora>,&<nazwa_shadera>);`
- wyrenderuj model: `YAVE_renderModel(&<nazwa_shadera>,&<nazwa_modelu>);`

## Zależności:

### Ogólnie
- cmake
- openGL 4.0 lub wyższy

A poza tym? 

**Nie ma!** - no dobra są, ale cmake robi to za nas, nie musimy nic instalować a mamy najnowsze wersje ;)
