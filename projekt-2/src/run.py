from subprocess import Popen, PIPE

import argparse

def run(clients_amount):
    server = Popen(['terminator', '-e', 'python3 server.py'], stdout=PIPE, stderr=PIPE, stdin=PIPE)    
    clients = []
    for i in range(clients_amount):
        client = Popen(['terminator', '-e', 'python3 client.py'], stdout=PIPE, stderr=PIPE, stdin=PIPE)
        clients.append(client)

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="Projekt 2 - wielowatkowy server chatu.")
    parser.add_argument('--clients', '-c', type=int, nargs=1, help='Provide amount of clients to spawn.')
    
    args = parser.parse_args()
    run (args.clients[0])