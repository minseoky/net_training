#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <cstring>
#include <arpa/inet.h>

using namespace std;

void error_handling(char *message)
{
    cerr << "[E] " << message << '\n' << endl;
}

int main(int argc, char *argv[]) //need server ip, port
{

    if(argc != 3)
    {
        cerr << "Usage: " << argv[0] << " <IP> <port>" << endl;
        return 1;
    }


    char buf[100];
    memset(&buf, 0, sizeof(buf));
    //socket
    int h_sock = socket(PF_INET, SOCK_DGRAM, 0);
    if(h_sock == -1) error_handling("sock() error");


    //connect
    sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(stoi(argv[2]));

    if(connect(h_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
        error_handling("conn() error");

    while(1)
    {
        cout << "message to server: ";
        cin >> buf;

        send(h_sock, buf, sizeof(buf), 0);
        socklen_t serv_addr_size = sizeof(serv_addr);
        recv(h_sock, buf, sizeof(buf), 0);

        cout << "message from server: " << buf << endl;
    }

    close(h_sock);
    return 0;
}