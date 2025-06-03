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
usage: run.py [-h] [--clients CLIENTS]

Projekt 2 - wielowatkowy server chatu.

options:
  -h, --help            show this help message and exit
  --clients, -c CLIENTS
                        Provide amount of clients to spawn.
```

## <font color='orange'>Dokumentacja</font>
### Uruchomienie programu
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

### Działanie i synchronizacja
1. Synchronizacja z nowo połączonymi klientami odbywa się poprzez wysłanie zapisanych w prywatnej liście (`self.__messages`) wiadomości.

```py
client, address = self.__server.accept()
                print(f"[*] Accepted connection from {address[0]}:{address[1]}")
                self.__threads.append(threading.Thread(target=self.handle_client, args=(client, )))
                self.__threads[len(self.__threads)-1].start()
                self.__connections.append(client)
                for i in self.__messages:
                    client.send(bytes(str(i[0] + ': ' + i[1] + '\n').encode("utf-8")))
```

2. Przesyłanie wiadomości między klientami odbywa się poprzez przekazania przez serwer wiadomości do wszystkich, z wyłączeniem nadawcy. 

```py
def handle_client(self, client_socket):
        while True:
            request = client_socket.recv(1024)
            if len(request) > 0:
                print(f'[*] {request.decode("utf-8")}')
                self.append_message(request.decode("utf-8"))
                for i in range(len(self.__connections)):
                    if self.__connections[i] != client_socket:
                        self.__connections[i].send(request)
                self.update_clients()
```