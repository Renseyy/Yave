## Dodatkowe zasoby
***
Uwaga wstępna: dodatkowe zasoby zostały umieszczone na dysku google a nie w githubie ze względu na to że są duże, a nie zawsze jest potrzeba ich pobierania.

 Ich pobieranie może również trochę potrwać.

***

Aby użyć dodatkowych zasobów dla *Windowsa* ( takich jak skompilowane biblioteki itp ) należy je najpierw pobrać z
 [tej](https://drive.google.com/drive/folders/19Eq9odwMRxMV4-nfNJ2w9UY0d7Hvx44y?usp=sharing) strony.
 
 Można łatwo pobrać wszystkie zasoby pobierając gotowego zipa: **windows.zip**

następnie należy rozpakować pobrane zasoby do tego folderu gdzie obecnie jesteś( tak aby się znajdowały w folderze `additional/windows` a nie `additional/windows/windows` )

***

Wtedy można albo użyć skryptu: **setup.bat**, który jeśli zadziała poprawnie szybko skonfiguruje wszystkie zależności

albo po prostu użyć tych zasobów aby skonfigurować sprawdzoną wersję.

### Opis poszczególnych folderów

- cmake - zawiera installer do cmake *.msi
- MinGW - zawiera mingw URCT runtime - 11.3.0: Win64
- glad - zawiera foldery: `include` i `src` domyślnie dostępne w gladzie oraz folder `lib` z przekompilowaną biblioteką
- GLFW - zawiera glfw 3.3.8 na win64
- glm - zawiera sam folder bibliotek do glm ( należy go dać do folderu include zgodnie z readme-windows.md )
- stb_image - zawiera plik stb_image.h
- assimp - znajdują się tam dwa foldery i plik:
    1. `include` - zawiera folder `assimp/` który należy przekopiować do MinGW/include ( zobacz readme-windows )
    **! Uwaga plik config.h jest już tam zawarty !**
    2. `lib` - zawiera bibliotekę do kompilowania z użyciem biblioteki współdzielonej ( wrzucić do MinGW/lib )
    3. plik **libassimp-5.dll** biblioteka współdzielona, ma być zawsze tam gdzie aplikacja.