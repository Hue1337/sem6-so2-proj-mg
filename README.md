# Projekt 1 - Systemy Operacyjne 2

## Dokumentacja programu
### Podstawowe informacje
Docelowe systemy operacyjne:
- Rodzina UNIX

System operacyjny, pod którym było tworzone oprogramownie:
- Fedora Linux 41 (Workstation Edition) x86_64

Język programowania:
- C Programming Language

### Instrukcja uruchomienia programu
1. Pobranie repozytorium z *github.com*
```bash
git clone git@github.com:Hue1337/sem6-so2-proj-mg.git
```

2. Przejście do folderu `src`
```bash
cd src
```

3. Wykorzystanie pliku `makefile` w celu zbudowanie i uruchomienia programu
```bash
make
```

### Opis problemu jedzących filozofów
**Problem jedzących filozofów** jest klasycznym problemem współbieżności polegającym na $N$ filozofaf zasiadających do stołu. Każdy z nich posiada przed sobą talerz oraz po jednym wpólnym widelcy po każdej ze stron (lewej oraz prawej). Widelców jest dokładnie taka sama ilość jak filozofów (co wynika z poprzedniego zdania). Każdy filozof myśli. Gdy zgłodnieje próbuje sięgnąć po widelce i zaczyna jeść (jeżeli owe był w stanie podnieść). Filozofowie mogą jeść wyłącznie w momencie kiedy posiadają oba widelce w dłoni. Gdy filozof zje, ponownie oddaje się myśleniu, a widelce odkłada na ich miejsce. Fiilozofowie mogą jedynie korzystać z widelców znajdujących się bezpośrednio obok nich.

### Wylistowanie sekcji krytycznych oraz rozwiązania problemu synchronizacji
1. Funkcja `take_forks(int index)`.
- Funkcja modyfikuje wspólny zasób dla wszystkich wątków (`enum Philosopher state[]`). Do rozwiązania problemu synchronizaji zostały wykorzystane `mutexy`. Umożliwiają one blokowanie dostępu do zasobu krytycznego na czas jego modyfikacji bądź dostępu przez sekcję krytyczną.

2. Funkcja `put_forks(int index)`. 
- Fukncja ta działa na podobnej zasadzie jak `take_forks(int index)`. Do rozwiązania problemu współbierzności i dostępu do zasobu krytycznego zasosowano indentyczny sposób jak powyżej - `mutexy`.

3. Funcja `test(int index)`.
- Funkcja `test(int index)` sprawdza, czy filozof jest głodny oraz wysyła sygnał, że może jeść. 

### Opis wątków
Program posiada 2 typy wątków:
1. Wątek główny - inicjalizacja oraz alokacja.
2. Wątki poboczne (*każdy z filozofów*) - pętla życia filozofa, przechodzenie z cyklu do cyklu.


