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
        self.__connections = []
        self.__messages = []

    def run(self):
        self.__server.bind((self.__ip, self.__port))
        self.__server.listen(5)

        while True:
            client, address = self.__server.accept()
            print(f"[*] Accepted connection from {address[0]}:{address[1]}")
            self.__connections.append(threading.Thread(target=self.handle_client, args=(client, )))
            self.__connections[len(self.__connections)-1].start()

    def handle_client(self, client_socket):
        with client_socket as sock:
            request = sock.recv(1024)
            print(f'[*] Received: {request.decode("utf-8")}')
            sock.send(b'ACK')

if __name__ == '__main__':
    newserver = Server()
    newserver.run()