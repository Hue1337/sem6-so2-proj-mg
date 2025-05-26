import socket, threading

class Client:
    __name = None
    __ip = None
    __port = None
    __client = None

    def __init__(self, name='test', ip='127.0.0.1', port=5555):
        self.__name = name
        self.__ip = ip
        self.__port = port
        self.__client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    def run(self):
        self.__client.connect((self.__ip, self.__port))
        threceiving = threading.Thread(target=self.receving)
        threceiving.start()

        thsending = threading.Thread(target=self.sending)
        thsending.start()

    def receving(self):
        print('[*] Synchronizing messages...')
        while True:
            response = self.__client.recv(4096)
            if len(response) > 0:
                print(f'{response.decode()}')

    def sending(self):
        while True:
            message = input("Send message: ")
            if message == '--quit':
                self.__client.close()
            message = self.__name + ': ' + message
            self.__client.send(bytes(message.encode('utf-8')))

if __name__ == '__main__':
    name = input("Name: ")
    newclient = Client(name)
    newclient.run()
