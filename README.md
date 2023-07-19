# YAVE - Yet Another Voxel Engine

### Testowy projekt mający na celu naukę OpenGL i shaderów (GLSL). Celem jest stworzenie silnika do gry Sylian.
Główne założenia tego silnika to:
- ładne wyglądanie, efekty świetlne i graficzne
- działać szybko i opierać się na karcie graficznej
- obsługiwanie przez server, jest to de facto ( i ma być ) jedynie klient
- musi być napisany w C++ ( z domieszką C ), może tymczasowo kożystac z LUA ( ale to raczej server )



Należy zainstalować wszystkie zależności( instrukcja niżej w sekcji Zależności ) a następnie:
- stworzyć jakiś folder w którym znajdą się utworzone pliki( np. **build** )
- z katalogu głównego Yave - tam gdzie **README**
```
cmake -S . -B <ścieżka do folderu na utworzone pliki>
czyli np (kiedy utworzyliśmy folder build )
cmake -S . -B build
```
lub

Otworzyć program *cmake* jako źródło podać **katalog główny Yave**, a jako miejsce docelowe **folder na utworzone pliki**

wcisnąć *configure*, a następnie *generate*


### Jeśli chcesz korzystać z debugowania np za pomocą gdb to dodaj na końcu jeszcze:
```
-DCMAKE_BUILD_TYPE=Debug
```
Na windowsie w cmake-gui options>Debug output

później po każdej zmianie w kodzie wystarczy użyć polecenia z katalogu głównego Yave(zarówno w terminalu jak i cmd):
```
cmake --build <ścieżka do folderu na utworzone pliki>
czyli np.
cmake --build build
```

To tyle!

PS. Za pierwszym razem kompilacja może zająć długo

PS2. O nie! wyskoczył błąd:
```
CMake 3.26.4 or higher is required.
```
- sprawdź wersję cmake'a jaką masz: `cmake --version`
- wejdź do pliku CMakeLists.txt
- w pierwszej linijce zmień na tą wersję cmake'a którą posiadasz
- sprawdź czy działa, jeśli tak to pozostaw tą zmianę przy commicie, jeśli nie zaktualizuj cmake'a

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
- python

A poza tym? 

**Nie ma!** - no dobra są, ale cmake robi to za nas, nie musimy nic instalować a mamy najnowsze wersje ;)

### Instrukcje instalacji zależności

- Manjaro/Arch/Arch-pochodne:
```
sudo pacman -S cmake
sudo pacman -S python3
sudo pacman -S pip
```
- Fedora/Centos/RHEL: (niesprawdzone)
```
sudo dnf install cmake
sudo dnf install python3
sudo dnf install pip
```
- Ubuntu/Debian/Debiano-pochodne: (niesprawdzone)
```
sudo apt-get install cmake
sudo apt-get install python3
sudo apt-get install pip
```
- Windows

Zainstaluj cmake ze strony: https://cmake.org/download/

Pythona z microsoft store, prawdopodobnie wystarczy wpisać python w cmd.
pip - z lini poleceń:
```
curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py
python get-pip.py
```
I jeśli nie masz to jakiś generator (np. Mingw : https://sourceforge.net/projects/mingw/)