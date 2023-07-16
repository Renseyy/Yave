# Lone
### Objektowy, węzłowy i bazujący na zdarzeniach LUA

## Założenia:
- wszystko jest `węzłem` czyli objektem zawierających coś w sobie.
- wszystkie akcje powinny być przekazywane przez `zdarzenia`. Zdarzenia zaczynają się w kodzie zawsze od znaku podkreślenia `_` czyli zdarzenie naciśnięcia przycisku `click` powinno być oznaczone jako `_click`
- objekty tworzymy przez przypisanie na nich `.new`. Objekt powinien zawsze być do czegoś przypisany
- Objekty przypisujemy do `node'ów` poprzez `:add`. Ta funkcja zawsze zwraca node'a
- Objekty możemy też tworzyć z domyślnym konstruktorem przekazując je po porstu jako klasy w pierwszym argumencie do `:add`
- Drugi argument add będzie uruchomiony jako przypisanie dla argumentu pierwszego
## Jak pisać:

// Poniższy kod jest tylko zarysem
```lua
local engine = getEngine()
engine._preinit = function(e)
    local gui = engine:add(ImGUI.new())   
    gui:add(ImGUI.Button, {
        _click = function()
            print("Kliknięto")
        end
        text = "Kliknij mnie"
    })
    local button = gui.add(ImGUI.Button)
end

```
[To samo w CSL:]
```CSL
&engine: @getEngine
&engine:preInit{
    &gui: ImGUI(){
        ImGUI::Button(){
            "Kliknij mnie"
            
            :click{
                @print "Kliknięto
            }
        }
        &button: ImGUI::Button()
    }
}
```


Struktura powyszego kodu:
```
[Yave] engine
    |
    + [Function] _preinit
        |
        +[ImGUI] gui 
            |
            + [Button] (annonymus)
            |   |
            |   + [Function] _click
            |   |
            |   + [String] text
            |
            + [Button] button
```