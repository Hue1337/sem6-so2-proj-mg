import socket, threading

class Client:
    __ip = None
    __port = None
    __client = None

    def __init__(self, ip='127.0.0.1', port=5555):
        self.__ip = ip
        self.__port = port
        self.__client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    def run(self):
        self.__client.connect((self.__ip, self.__port))
        threceiving = threading.Thread(target=self.receving)
        thsending = threading.Thread(target=self.sending)
        threceiving.start()
        thsending.start()

    def receving(self):
        while True:
            response = self.__client.recv(4096)
            if len(response) > 0:
                print(f'{response}')

    def sending(self):
        while True:
            message = input("Send message: ")
            if message == '--quit':
                self.__client.close()
            self.__client.send(bytes(message.encode('utf-8')))

if __name__ == '__main__':
    newclient = Client()
    newclient.run()
