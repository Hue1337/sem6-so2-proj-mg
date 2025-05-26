import socket, threading

class Server:
    __ip = None
    __port = None
    __server = None
    __connections = None
    __messages = None

    def __init__(self, ip='127.0.0.1', port=5555):
        self.__ip = ip
        self.__port = port
        self.__server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.__threads = []
        self.__connections = []
        self.__messages = []

    def run(self):
        self.__server.bind((self.__ip, self.__port))
        self.__server.listen(5)

        while True:
            try:
                client, address = self.__server.accept()
                print(f"[*] Accepted connection from {address[0]}:{address[1]}")
                self.__threads.append(threading.Thread(target=self.handle_client, args=(client, )))
                self.__threads[len(self.__threads)-1].start()
                self.__connections.append(client)
                for i in self.__messages:
                    client.send(bytes(str(i[0] + ': ' + i[1] + '\n').encode("utf-8")))
            except Exception as e:
                print('[-] Error occured!')
                

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


    def append_message(self, message):
        splitmess = message.split(':')
        self.__messages.append((splitmess[0], ':'.join(splitmess[1:])))
        print(self.__messages)

    def update_clients(self):
        for i in range(len(self.__connections)):
            # Wychodzi po za rozmiar connections. Zobaczyc czemu i poprawic.
            if not self.client_is_alive(self.__connections[i]):
                try:
                    self.__connections[i].close()
                except:
                    print("Not worked killing")
                self.__connections.pop(i)

    def client_is_alive(self, client):
        try:
            client.send(b'')
            return True
        except:
            return False


if __name__ == '__main__':
    newserver = Server()
    newserver.run()