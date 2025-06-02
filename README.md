# Wielowątkowy serwer chatu
- Autor: Mateusz Głuchowski

## <font color='orange'>Wymagania i opis projektu</font>
**Wymaganie systemowe**
- Rodzina systemów Linux. Preferowane:
    - Fedora
    - Debian
    - Ubuntu

- Python. Preferowana wersja - `3.13.3`
- Zainstalowany terminal [`terminator`](https://gnome-terminator.readthedocs.io) 
    - `sudo dnf install terminator`
    - `sudo apt install terminator`


**Opis projektu**
- Serwer tworzy osobny wątek dla każdego połączenia od klienta.
- Serwer dba o synchronizację wiadomości od klientów.
- Klient widzi wiadomości na chacie.
- Klient posiada możliwości wysyłania wiadomości na chacie.


## <font color='orange'>Instrukcja uruchomienia projektu</font>
```
usage: main.py [-h] [--clients CLIENTS]

Projekt 2 - wielowatkowy server chatu.

options:
  -h, --help            show this help message and exit
  --clients, -c CLIENTS
                        Provide amount of clients to spawn.
```

## <font color='orange'>Dokumentacja</font>
1. Uruchomienie środowiska wirtualnego w pythonie
```bash
cd src
mkdir venv
python3 -m venv ./venv/
source ./venv/bin/activate
```

To leave `venv` mode
```bash
deactivate
```


2. Zainstalowanie wymaganych paczek systemowych
```bash
sudo {dnf|apt} install terminator
```

3. Uruchomienie programu
```bash
python3 run.py -c 3
```
*Zamiast cyfry 3 można wpisać inną cyfrę bądź liczbę.*