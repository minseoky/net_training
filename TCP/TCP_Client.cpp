#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <cstring>
#include <unistd.h>
#include <cstdlib>
using namespace std;

void error_handler(char *message)
{
    fputs("[E] ", stderr);
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        cerr << "Usage: " << argv[0] << " <IP> <port>" << endl;
        return 1;
    }

    char buf[100] = {};
    char read_buf[100] = {};

    // socket
    int h_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(h_sock == -1) error_handler("socket() error");

    sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(stoi(argv[2]));

    //connect
    if(connect(h_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
    {
        error_handler("connect() error");
    }

    cout << "message to server: ";
    cin >> buf;

    write(h_sock, buf, strlen(buf));

    if(read(h_sock, read_buf, sizeof(read_buf)-1) != 0)
        cout << "echo from server: " << read_buf << endl;


    close(h_sock);

    return 0;
}